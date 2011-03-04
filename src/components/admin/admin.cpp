#include "admin.h"

#include "support/configfile.h"
#include "support/alarm.h"
#include "support/list.hpp"
#include "support/async_delayed_call.hpp"
#include "support/crc32.h"
#include "support/re/RegExp.h"
#include "components/request_response.hpp"


#include "msg_admin.h"


#include <stdlib.h>     //  exit

#define  ADMIN_PENDING_IMPLEMENTATION  throw mtk::Alarm(MTK_HERE, "PENDING IMPLEMENTATION", mtk::alPriorCritic, mtk::alTypeNoPermisions);
#define  ADMIN_PROVISIONAL_IMPLEMENTATION   mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "PENDING IMPLEMENTATION", mtk::alPriorCritic, mtk::alTypeNoPermisions));


namespace {

    
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //          class admin_status
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class admin_status   :  public  mtk::SignalReceptor
    {
        typedef  admin_status  CLASS_NAME;
        
        struct command_info {
            mtk::non_copyable nc;
            
            command_info(const std::string& _group, const std::string& _name, const std::string& _description)
                :   group(_group), name(_name), description(_description), 
                    signal_command_received(mtk::make_cptr(new mtk::Signal<const std::string& /*cmd*/, const std::string& /*params*/, const std::string& /*rqcode*/> ))   {}
                
            const std::string group;
            const std::string name;
            const std::string description;
            mtk::CountPtr<  mtk::Signal<    const std::string& /*cmd*/, 
                                            const std::string& /*params*/, 
                                            const std::string& /*reqcode*/> >   signal_command_received;
        };
        
    public:
            void                  init                (const std::string& config_file_name);
            
            mtk::ConfigFile&      get_config_file     (void)    { return config_file;  };
        
            static admin_status*  i(void);
            static void           release(void);

            void NotifyAlarm (const mtk::Alarm& alarm);
            
            
            mtk::CountPtr<mtk::Signal<const std::string& /*cmd*/, const std::string& /*params*/, const std::string& /*rqcode*/> >
            register_command(const std::string& group, const std::string& name, const std::string& description);
            
            
            

    //private:
            enum en_process_priority { ppVeryLow, ppLow, ppNormal, ppHigh, ppCritical };
            en_process_priority   process_priority;
            admin_status() : process_priority(ppVeryLow), ka_interval_send(mtk::dtSeconds(50)), ka_interval_check(mtk::dtSeconds(50)) {}
    

            static admin_status*  admin_status_instance;
            
            mtk::ConfigFile                         config_file;
            mtk::CountPtr< mtk::qpid_session >      session_admin;
            std::string                             location;
            std::string                             machine;
            std::string                             session_id;
            mtk::dtTimeQuantity                     ka_interval_send;
            mtk::dtTimeQuantity                     ka_interval_check;

            mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::admin::msg::command>      > hqpid_commands;
            
            void                                send_enter_and_start_keepalive(void);
            std::string                         get_mandatory_property(const std::string& path_and_property);
            mtk::admin::msg::sub_admin_header   get_sub_admin_header(void);

            void                                send_keep_alive(void);


            void __direct_NotifyAlarm (const mtk::Alarm& alarm);

            MTK_ASYNC_DELAYED_CALL_DI(NotifyAlarmErrorCritic, mtk::Alarm , 5, mtk::dtMilliseconds(20), 1000)
                __direct_NotifyAlarm(p);
            MTK_ASYNC_DELAYED_CALL_END_I

            MTK_ASYNC_DELAYED_CALL_DI(NotifyAlarm_noerror   , mtk::Alarm, 5, mtk::dtMilliseconds(330), 200)
                __direct_NotifyAlarm(p);
            MTK_ASYNC_DELAYED_CALL_END_I
            
            void AsyncDelayedCall_Overflow(std::string description)
            {
                MTK_EXEC_MAX_FREC_S(mtk::dtSeconds(15))
                    __direct_NotifyAlarm(mtk::Alarm(MTK_HERE, description, mtk::alPriorError, mtk::alTypeOverflow));
                MTK_END_EXEC_MAX_FREC
            }


            void send_single_response(const std::string& response, const std::string& request_code);
            mtk::map<std::string, mtk::CountPtr<command_info> >             map_commands;
            mtk::map<std::string/*group*/, std::string/*cmds help*/ >       map_commands_groupped_help;
            void on_command_received(const mtk::admin::msg::command& command_msg);
            void command_help(const std::string& command, const std::string& param, const std::string& request_code);
            void command_stats(const std::string& command, const std::string& param, const std::string& request_code);
            void command_infoapp(const std::string& command, const std::string& param, const std::string& request_code);
            void command_config(const std::string& command, const std::string& param, const std::string& request_code);
            void command_ping(const std::string& command, const std::string& param, const std::string& request_code);
    };
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //          class admin_status
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    
    admin_status* admin_status::admin_status_instance=0;
    
    admin_status* admin_status::i(void)
    {
        if(admin_status_instance == 0)
            admin_status_instance = new admin_status();
        return admin_status_instance;
    }
    
    void  admin_status::release(void)
    {
        if(admin_status_instance==0)        return;
        
        //  send exit message
        mtk::admin::msg::exit exit_msg(admin_status_instance->get_sub_admin_header(), "closing application");
        //std::cout << exit_msg << std::endl;
        mtk::send_message(admin_status_instance->session_admin, exit_msg);
        
        if(admin_status_instance != 0)
            delete admin_status_instance;
        admin_status_instance = 0;
    }
    
    void admin_status::init(const std::string& config_file_name)
    {
        if(config_file.IsLoaded() == false)
            config_file.LoadFromFile(config_file_name);
        else
            throw mtk::Alarm(MTK_HERE, "file already loaded", mtk::alPriorError, mtk::alTypeNoPermisions);
            
        if(config_file.GetValue("ADMIN.role").HasValue() == false)
        {
            std::cerr << "cannot open ADMIN.role on   " << MTK_HERE << std::endl;
            exit(-1);
        }
        std::string role = config_file.GetValue("ADMIN.role").Get();
        if(role != "client"  &&  role != "server")
        {
            std::cerr << "invalid ADMIN.role on   " << MTK_HERE  << std::endl;
            exit(-1);
        }


        if(role=="client")
            process_priority = ppNormal;
        else
        {
            std::string priority = get_mandatory_property("ADMIN.priority");
            if(priority=="very_low")
                process_priority = ppVeryLow;
            else if(priority=="low")
                process_priority = ppLow;
            else if(priority=="normal")
                process_priority = ppNormal;
            else if(priority=="high")
                process_priority = ppHigh;
            else if(priority=="critical")
                process_priority = ppCritical;
            else
                throw mtk::Alarm(MTK_HERE, "invalid priority code", mtk::alPriorCritic, mtk::alTypeNoPermisions);            
        }
        
            
        if(process_priority==ppVeryLow)
        {
            ka_interval_send  = mtk::dtSeconds(55);
            ka_interval_check = mtk::dtSeconds(75);
        }
        else if(process_priority==ppLow)
        {
            ka_interval_send  = mtk::dtSeconds(30);
            ka_interval_check = mtk::dtSeconds(40);
        }
        else if(process_priority==ppNormal)
        {
            ka_interval_send  = mtk::dtSeconds(10);
            ka_interval_check = mtk::dtSeconds(13);
        }
        else if(process_priority==ppHigh)
        {
            ka_interval_send  = mtk::dtSeconds(8);
            ka_interval_check = mtk::dtSeconds(10);
        }
        else if(process_priority==ppCritical)
        {
            ka_interval_send  = mtk::dtSeconds(4);
            ka_interval_check = mtk::dtSeconds(5);
        }
        else
            throw mtk::Alarm(MTK_HERE, "invalid priority code", mtk::alPriorCritic, mtk::alTypeNoPermisions);            
        
        location        = get_mandatory_property("ADMIN.CLIENT.location");
        machine         = get_mandatory_property("ADMIN.CLIENT.machine_code");


        if(role=="client")
        {
            session_admin = mtk::admin::get_qpid_session("admin", "ADMCLI");
            MTK_QPID_RECEIVER_CONNECT_THIS(
                                    hqpid_commands,
                                    mtk::admin::get_url("admin"),
                                    "ADMCLI",
                                    mtk::admin::msg::command::get_in_subject(location, machine),
                                    mtk::admin::msg::command,
                                    on_command_received)
            
        }
        else
            session_admin = mtk::admin::get_qpid_session("admin", "ADMSRV");
        
            
        send_enter_and_start_keepalive();
        
        //register_command("ADMIN", "help", "")->connect(this, &CLASS_NAME::command_help);
        MTK_CONNECT_THIS(*register_command("ADMIN", "help", ""),                                command_help)
        MTK_CONNECT_THIS(*register_command("ADMIN", "stats", "some stats"),                     command_stats)
        MTK_CONNECT_THIS(*register_command("ADMIN", "infoapp", "info about the application"),   command_infoapp)
        MTK_CONNECT_THIS(*register_command("ADMIN", "config", "config information"),            command_config)
        MTK_CONNECT_THIS(*register_command("ADMIN", "ping", "returns a pong"),                  command_ping)
    }

    std::string admin_status::get_mandatory_property(const std::string& path_and_property)
    {
        mtk::Nullable<std::string>  value = config_file.GetValue(path_and_property);
        if(value.HasValue() == false)
            throw mtk::Alarm(MTK_HERE, MTK_SS("mising mandatory property " << path_and_property), mtk::alPriorError, mtk::alTypeNoPermisions);
        else
            return value.Get();
    }

    void admin_status::send_enter_and_start_keepalive(void)
    {
        mtk::admin::msg::enter enter_msg(get_sub_admin_header(), ka_interval_send, ka_interval_check);
        //std::cout << enter_msg << std::endl;
        mtk::send_message(session_admin, enter_msg);
        
        MTK_TIMER_1S(send_keep_alive)
    }
    
    void  admin_status::send_keep_alive(void)
    {
        MTK_EXEC_MAX_FREC_NO_FIRST_S(ka_interval_send)
            mtk::admin::msg::keep_alive keep_alive_msg(get_sub_admin_header(), ka_interval_send, ka_interval_check);
            //std::cout << keep_alive_msg << std::endl;
            mtk::send_message(session_admin, keep_alive_msg);
        MTK_END_EXEC_MAX_FREC
    }
    
    mtk::admin::msg::sub_admin_header admin_status::get_sub_admin_header(void)
    {
        return mtk::admin::msg::sub_admin_header(location, machine, mtk::dtNowLocal());
    }





    void admin_status::NotifyAlarm (const mtk::Alarm& alarm)
    {
        if(alarm.priority == mtk::alPriorCritic  ||  alarm.priority == mtk::alPriorError)
            NotifyAlarmErrorCritic(alarm);
        else
            NotifyAlarm_noerror(alarm);
    }

    void admin_status::__direct_NotifyAlarm (const mtk::Alarm& alarm)
    {
        //std::cout << alarm << std::endl;
        mtk::admin::msg::alarm alarm_msg(get_sub_admin_header(), alarm.codeSource, alarm.message, alarm.priority, alarm.type, alarm.dateTime, int16_t(alarm.alarmID));
        mtk::send_message(session_admin, alarm_msg);
    }



    void admin_status::send_single_response(const std::string& response, const std::string& request_code)
    {
        mtk::list<mtk::admin::msg::sub_command_rd>  data_list;
        data_list.push_back(mtk::admin::msg::sub_command_rd(
                                    mtk::admin::msg::sub_admin_header(mtk::admin::get_location(), mtk::admin::get_machine(), mtk::dtNowLocal()),
                                    response));
        MTK_SEND_MULTI_RESPONSE(        mtk::admin::msg::command_response, 
                                        mtk::admin::msg::sub_command_rd, 
                                        session_admin,
                                        mtk::msg::sub_request_r(request_code),
                                        data_list)
    }

    void admin_status::on_command_received(const mtk::admin::msg::command& command_msg)
    {
        mtk::RegExp re_command_params(mtk::RegExp(" *([^ ]+) *(.*) *"));
        re_command_params.Match(command_msg.command_line);
        std::string command = re_command_params.GetString(0);
        std::string params  = re_command_params.GetString(1);
        
        
        mtk::map<std::string, mtk::CountPtr<command_info> >::iterator it = map_commands.find(command);
        if(it==map_commands.end())
            send_single_response(MTK_SS(command << "  unknow command"), command_msg.request_code.request_code);
        else
        {
            if(it->second->signal_command_received->emit(command, params, command_msg.request_code.request_code) == 0)
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, MTK_SS(command << "  has no signal connected"), mtk::alPriorError));
        }
    }

    void admin_status::command_help(const std::string& /*command*/, const std::string& /*params*/, const std::string& request_code)
    {
        //  preparing sending multiresponses in asyncronous way
        //  filling response list
        mtk::list<mtk::admin::msg::sub_command_rd>  data_list;
        
        mtk::map<std::string, std::string>::iterator it=map_commands_groupped_help.begin();
        while(it!=map_commands_groupped_help.end())
        {
            //std::string help_line = MTK_SS( mtk::s_AlignLeft (it->second->group, 10) << mtk::s_AlignLeft (it->second->name, 10)  <<  it->second->description << std::endl);
            data_list.push_back(mtk::admin::msg::sub_command_rd(
                                    mtk::admin::msg::sub_admin_header(mtk::admin::get_location(), mtk::admin::get_machine(), mtk::dtNowLocal()),
                                    MTK_SS(std::endl << std::endl << it->first << std::endl << "....................")));
            data_list.push_back(mtk::admin::msg::sub_command_rd(
                                    mtk::admin::msg::sub_admin_header(mtk::admin::get_location(), mtk::admin::get_machine(), mtk::dtNowLocal()),
                                    MTK_SS("           " << it->second)));
                                    //help_line));
            ++it;
        }
                                    
        //  sending multiresponses in asyncronous way
        MTK_SEND_MULTI_RESPONSE(        mtk::admin::msg::command_response, 
                                        mtk::admin::msg::sub_command_rd, 
                                        session_admin,
                                        mtk::msg::sub_request_r(request_code),
                                        data_list)
    }
    void admin_status::command_stats(const std::string& command, const std::string& /*param*/, const std::string& request_code)
    {
        send_single_response(MTK_SS(command << "  pending implementation"), request_code);
    }
    
    void admin_status::command_infoapp(const std::string& command, const std::string& /*param*/, const std::string& request_code)
    {
        send_single_response(MTK_SS(command << "  pending implementation"), request_code);
    }

    void admin_status::command_config(const std::string& command, const std::string& /*param*/, const std::string& request_code)
    {
        send_single_response(MTK_SS(command << "  pending implementation"), request_code);
    }
    
    void admin_status::command_ping(const std::string& /*command*/, const std::string& /*param*/, const std::string& request_code)
    {
        send_single_response(MTK_SS("pong  " << mtk::dtNowLocal()), request_code);
    }
    
    mtk::CountPtr<mtk::Signal<const std::string& /*cmd*/, const std::string& /*params*/, const std::string& /*reqcode*/> >
    admin_status::register_command(const std::string& group, const std::string& name, const std::string& description)
    {
        if(map_commands.find(name) != map_commands.end())
        {
            MTK_EXEC_MAX_FREC(mtk::dtSeconds(5))
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, MTK_SS(name << " is already registered, ignoring group and desciption (could be more commands affected)"), mtk::alPriorDebug));
            MTK_END_EXEC_MAX_FREC
        }
        else
        {
            map_commands[name] = mtk::make_cptr(new command_info(group, name, description));
            std::string help_line = MTK_SS( "        " << mtk::s_AlignLeft (name, 10)  <<  description);
            map_commands_groupped_help[group] = MTK_SS(map_commands_groupped_help[group] << std::endl  <<  help_line);
        }
        return map_commands[name]->signal_command_received;
    }


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //          class admin_status  end implementation
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
};


namespace mtk {
namespace admin {

    
void init(const std::string& config_file_name)
{
    admin_status::i()->init(config_file_name);
}






mtk::CountPtr< mtk::qpid_session >     get_qpid_session(const std::string&  url_for, const std::string& address)
{
    static int counter;
    if(++counter > 500)
    {
        MTK_EXEC_MAX_FREC_S(mtk::dtSeconds(5))
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "too many calls" , mtk::alPriorError, mtk::alTypeOverflow));
        MTK_END_EXEC_MAX_FREC
    }
    else if(++counter > 100)
    {
        MTK_EXEC_MAX_FREC_S(mtk::dtSeconds(5))
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "too many calls" , mtk::alPriorWarning, mtk::alTypeOverflow));
        MTK_END_EXEC_MAX_FREC
    }
    
    return mtk::get_from_factory< mtk::qpid_session >(mtk::make_tuple(get_url(url_for), address));
}


    
    
mtk::msg::sub_request_info   client_get_request_info (void)
{
    ADMIN_PROVISIONAL_IMPLEMENTATION
    
    static int i=0;
    static const std::string session = MTK_SS(mtk::dtNowLocal());
    return mtk::msg::sub_request_info (mtk::msg::sub_request_id(session, MTK_SS("pending"<<++i)), "CLIENT");
}

std::string                             get_location(void)
{
    return admin_status::i()->location;
}

std::string                             get_machine (void)
{
    return admin_status::i()->machine;
}

std::string                             get_session (void)
{
    return admin_status::i()->session_id;
}


std::string                             get_request_code    (void)
{
    return mtk::crc32_as_string( MTK_SS(admin_status::i()->machine <<  admin_status::i()->location << admin_status::i()->session_id << mtk::rand()));
}


std::string                             get_url             (const std::string& url_for)
{
    mtk::Nullable<std::string> url = admin_status::i()->get_config_file().GetValue(MTK_SS("ADMIN.URLS." << url_for));
    if(url.HasValue()==false)
        throw mtk::Alarm(MTK_HERE, MTK_SS("requested invalid url  " << url_for), mtk::alPriorCritic);
    else
        return url.Get();
}


mtk::CountPtr<mtk::Signal<const std::string& /*cmd*/, const std::string& /*params*/, const std::string& /*rqcode*/> >
register_command(const std::string& group, const std::string& name, const std::string& description)
{
    return admin_status::i()->register_command(group, name, description);
}



};     //namespace admin {
      
      
      
void AlarmMsg (const Alarm& alarm)
{
    admin_status::i()->NotifyAlarm(alarm);
}



void  __internal_admin_nevercall_me____release_on_exit(void)
{
    admin_status::release();
}




      
};  //namespace mtk {




namespace {
    
    
    
};
