#include "admin.h"

#include "support/configfile.h"
#include "support/alarm.h"
#include "support/list.hpp"
#include "support/async_delayed_call.hpp"
#include "support/crc32.h"
#include "support/re/RegExp.h"
#include "components/request_response.hpp"
#include "support/version.hpp"
#include "support/misc.h"
#include "support/controlfluctuaciones.h"



#include "msg_admin.h"


#include <stdlib.h>     //  exit

#define  ADMIN_PENDING_IMPLEMENTATION  throw mtk::Alarm(MTK_HERE, "PENDING IMPLEMENTATION", mtk::alPriorError, mtk::alTypeNoPermisions);
#define  ADMIN_PROVISIONAL_IMPLEMENTATION   mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "PENDING IMPLEMENTATION", mtk::alPriorError, mtk::alTypeNoPermisions));





namespace {
    const char*   VERSION = "2011-03-16";
    
    const char*   MODIFICATIONS =
                        "           2011-03-16     first version\n";









   
    mtk::Signal<>*           signal_admin_ready  = 0;
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //          class admin_status
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class admin_status   :  public  mtk::SignalReceptor
    {
        typedef  admin_status  CLASS_NAME;
        
        struct command_info {
            mtk::non_copyable nc;
            
            command_info(const std::string& _group, const std::string& _name, const std::string& _description, bool _confirmation_requiered)
                :   group(_group), name(_name), description(_description), confirmation_requiered(_confirmation_requiered),
                    signal_command_received(mtk::make_cptr(new mtk::Signal<const std::string& /*cmd*/, const std::string& /*params*/, mtk::list<std::string>& /*lines response*/> ))   {}
                
            const std::string   group;
            const std::string   name;
            const std::string   description;
            const bool          confirmation_requiered;
            mtk::CountPtr<  mtk::Signal<    const std::string&      /*cmd*/, 
                                            const std::string&      /*params*/, 
                                            mtk::list<std::string>& /*respnose lines to fill*/> >   signal_command_received;
        };
        
    public:
            mtk::acs::msg::res_login::IC_login_response_info     client_login_confirmation;
            bool                  full_initialized;
            
            void                  init                ( const std::string& config_file_name,
                                                        const std::string& app_name,
                                                        const std::string& app_version,
                                                        const std::string& app_description,
                                                        const std::string& app_modifications);  
                                                        
            void                  close_application   ( const std::string& reason );
            
            
            
            mtk::ConfigFile&      get_config_file     (void)    { return config_file;  };

            mtk::msg::sub_request_info   get_request_info (void);


            static admin_status*  i(void);
            static void           release(void);

            void NotifyAlarm (const mtk::Alarm& alarm);
            
            
            mtk::CountPtr<mtk::Signal<const std::string& /*cmd*/, const std::string& /*params*/, mtk::list<std::string>& /*response lines*/> >
            register_command(const std::string& group, const std::string& name, const std::string& description, bool confirmation_requeried=false);


            mtk::CountPtr<mtk::Signal<const mtk::Alarm&> >       signal_alarm_error_critic;
            mtk::CountPtr<mtk::Signal<const mtk::Alarm&> >       signal_alarm_nonerror    ;
            
            
            

    //private:
            enum en_process_priority { ppVeryLow, ppLow, ppNormal, ppHigh, ppCritical };
            en_process_priority   process_priority;
            
            
            admin_status()  :   client_login_confirmation("", ""),
                                full_initialized(false),
                                signal_alarm_error_critic(new mtk::Signal<const mtk::Alarm&> ),
                                signal_alarm_nonerror(new mtk::Signal<const mtk::Alarm&> ),
                                process_priority(ppVeryLow), 
                                process_info(mtk::msg::sub_process_info(mtk::msg::sub_location("", ""), "", "", "")),
                                ka_interval_send(mtk::dtSeconds(50)), 
                                ka_interval_check(mtk::dtSeconds(50)),
                                start_date_time(mtk::dtNowLocal()),
                                signal_no_receiving_messages  (new mtk::Signal<const mtk::dtTimeQuantity&> ),
                                signal_receiving_messages_back(new mtk::Signal<> ),
                                next_central_keep_alive_to_receive(mtk::dtNowLocal()+mtk::dtSeconds(20))
                                {}
    

            static admin_status*  admin_status_instance;
            
            mtk::ConfigFile                             config_file;
            mtk::Nullable<std::string>                  get_config_property(const std::string& path);
            void                                        set_config_property(const std::string& path, const std::string&  property_value);

            mtk::list<std::string>                      get_config_nodes    (const std::string& path);


            mtk::msg::sub_control_fluct                 get_control_fluct_info(void);
            void                                        check_control_fluct(const mtk::msg::sub_control_fluct&  cf);

            
            std::string                                 app_name;
            std::string                                 app_version;
            std::string                                 app_description;
            std::string                                 app_modifications;
            std::string                                 role;
            
            mtk::CountPtr< mtk::qpid_session >          session_admin;
            mtk::msg::sub_process_info                  process_info;
            //std::string                                 session_id;
            mtk::dtTimeQuantity                         ka_interval_send;
            mtk::dtTimeQuantity                         ka_interval_check;
            
            mtk::DateTime                               start_date_time;

            mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::admin::msg::req_command>            > hqpid_commands;
            mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::admin::msg::pub_central_keep_alive> > hqpid_central_keepalive;
            
            void                                        send_enter_and_start_keepalive(void);
            std::string                                 get_mandatory_property(const std::string& path_and_property);
            mtk::msg::sub_process_info                  get_process_info(void) const { return process_info; }

            void                                        send_keep_alive(void);
            void                                        check_last_received_message(void);


            //  messages reception control
            mtk::CountPtr<mtk::Signal<const mtk::dtTimeQuantity&> > signal_no_receiving_messages;
            mtk::CountPtr<mtk::Signal<> >                           signal_receiving_messages_back;
            mtk::nullable<mtk::DateTime>                            last_not_receiving_messages_notification;
            //  messages reception control


            //  central keep alive control
            void                           check_central_keep_alive(void);
            mtk::dtDateTime                next_central_keep_alive_to_receive;
            void                           on_central_ka_received(const mtk::admin::msg::pub_central_keep_alive& ka_msg);
            //  central keep alive control


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
                    __direct_NotifyAlarm(mtk::Alarm(MTK_HERE, "admin", description, mtk::alPriorError, mtk::alTypeOverflow));
                MTK_END_EXEC_MAX_FREC
            }


            mtk::map<std::string, mtk::CountPtr<command_info> >             map_commands;
            mtk::map<std::string/*group*/, std::string/*cmds help*/ >       map_commands_groupped_help;
            
            void on_command_received        (const mtk::admin::msg::req_command& command_msg);
            void command_help               (const std::string& command, const std::string& param,  mtk::list<std::string>&  response_lines);
            void command_version            (const std::string& command, const std::string& param,  mtk::list<std::string>&  response_lines);
            void command_version_app        (const std::string& command, const std::string& param,  mtk::list<std::string>&  response_lines);
            void command_modifications      (const std::string& command, const std::string& param,  mtk::list<std::string>&  response_lines);
            void command_modifications_app  (const std::string& command, const std::string& param,  mtk::list<std::string>&  response_lines);
            void command_stats              (const std::string& command, const std::string& param,  mtk::list<std::string>&  response_lines);
            void command_realtime           (const std::string& command, const std::string& param,  mtk::list<std::string>&  response_lines);
            void command_infoapp            (const std::string& command, const std::string& param,  mtk::list<std::string>&  response_lines);
            void command_config             (const std::string& command, const std::string& param,  mtk::list<std::string>&  response_lines);
            void command_ping               (const std::string& command, const std::string& param,  mtk::list<std::string>&  response_lines);
            void command_date_time          (const std::string& command, const std::string& param,  mtk::list<std::string>&  response_lines);
            void command_set_machine_code   (const std::string& command, const std::string& param,  mtk::list<std::string>&  response_lines);
            void command_rqclose            (const std::string& command, const std::string& param,  mtk::list<std::string>&  response_lines);
            
            std::string  get_stats_simulating_command(void);
            void         send_stats_periodically(void);

            mtk::ControlFluctuacionesMulti<std::string>     control_flucts;
            void                                            check_fluct(const std::string&  id,  const mtk::DateTime&  dt);
            void                                            check_fluct(const std::string&  id,  const mtk::dtTimeQuantity&  tq);
            void                                            check_local_fluct(void);
    };
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //          class admin_status
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    
    admin_status* admin_status::admin_status_instance=0;
    
    admin_status* admin_status::i(void)
    {
        if(admin_status_instance == 0)
        {
            mtk::Alarm alarm = mtk::Alarm(MTK_HERE, "admin", "requested admin instace not intialized", mtk::alPriorCritic, mtk::alTypeNoPermisions);
            std::cerr << alarm << std::endl;
            throw alarm;
        }
            //  admin_status_instance = new admin_status();
        return admin_status_instance;
    }
    
    void  admin_status::release(void)
    {
        if(admin_status_instance  &&  i()->full_initialized)
            i()->close_application("from admin_status::release");
        
        delete signal_admin_ready;
        signal_admin_ready = 0;
        delete admin_status_instance;
        admin_status_instance = 0;
    }
    void  admin_status::close_application(const std::string& reason)
    {
        static bool  exit_message_sent = false;
        if(exit_message_sent==false)
        {
            __direct_NotifyAlarm(mtk::Alarm(MTK_HERE, "admin.app_exit_stats", get_stats_simulating_command(), mtk::alPriorDebug, mtk::alTypeUnknown));
            __direct_NotifyAlarm(mtk::Alarm(MTK_HERE, "admin.app_exit", MTK_SS("Exiting application  " << reason), mtk::alPriorDebug, mtk::alTypeUnknown));
            
            
            //  send exit message
            mtk::admin::msg::pub_exit exit_msg(admin_status_instance->get_process_info(), reason);
            //std::cout << exit_msg << std::endl;
            mtk::send_message(admin_status_instance->session_admin, exit_msg);
            exit_message_sent = true;
        }
    }
    
    
    void admin_status::init (const std::string& config_file_name,   const std::string& _app_name,
                                                                    const std::string& _app_version,
                                                                    const std::string& _app_description,
                                                                    const std::string& _app_modifications)
    {
        if(config_file.IsLoaded() == false)
            config_file.LoadFromFile(config_file_name);
        else
            throw mtk::Alarm(MTK_HERE, "admin.init", "file already loaded", mtk::alPriorError, mtk::alTypeNoPermisions);
            
        if(config_file.GetValue("ADMIN.role").HasValue() == false)
        {
            std::cerr << "cannot open ADMIN.role on   " << MTK_HERE << std::endl;
            exit(-1);
        }
        role = config_file.GetValue("ADMIN.role").Get();
        if(role != "client"  &&  role != "server")
        {
            std::cerr << "invalid ADMIN.role on   " << MTK_HERE  << std::endl;
            exit(-1);
        }

        app_name            = _app_name;
        app_version         = _app_version;
        app_description     = _app_description;
        app_modifications   = _app_modifications;

        if(role=="client")
            process_priority = ppNormal;
        else
        {
            app_name = get_mandatory_property("ADMIN.server_name");
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
                throw mtk::Alarm(MTK_HERE, "admin", "invalid priority code", mtk::alPriorCritic, mtk::alTypeNoPermisions);            
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
            throw mtk::Alarm(MTK_HERE, "admin", "invalid priority code", mtk::alPriorCritic, mtk::alTypeNoPermisions);            
        

        if(role=="client")
        {
            process_info = mtk::msg::sub_process_info(mtk::msg::sub_process_info(mtk::msg::sub_location(get_mandatory_property("ADMIN.CLIENT.location"), 
                                                            MTK_SS(get_mandatory_property("ADMIN.CLIENT.machine_code") << "@" << mtk::GetMachineCode())),
                                                            app_name, 
                                                            mtk::crc32_as_string(MTK_SS(app_name<<get_mandatory_property("ADMIN.CLIENT.machine_code") << "@" << mtk::GetMachineCode()<<mtk::rand())),
                                                            app_version));
            
            session_admin = mtk::admin::get_qpid_session("client", "CLITESTING");
            mtk::msg::sub_process_info  temp_process_info = get_process_info();
            MTK_QPID_RECEIVER_CONNECT_THIS(
                                    hqpid_commands,
                                    mtk::admin::get_url("client"),
                                    "CLITESTING",
                                    mtk::admin::msg::req_command::get_in_subject(temp_process_info.location.client_code, 
                                                                             temp_process_info.location.machine,
                                                                             temp_process_info.process_name,
                                                                             temp_process_info.process_uuid),
                                    mtk::admin::msg::req_command,
                                    on_command_received)
            
            MTK_QPID_RECEIVER_CONNECT_THIS(
                                    hqpid_central_keepalive,
                                    mtk::admin::get_url("client"),
                                    "CLITESTING",
                                    mtk::admin::msg::pub_central_keep_alive::get_in_subject(),
                                    mtk::admin::msg::pub_central_keep_alive,
                                    on_central_ka_received)
        }
        else
        {
            process_info = mtk::msg::sub_process_info(mtk::msg::sub_process_info(mtk::msg::sub_location("SYS", mtk::GetMachineCode()), app_name, 
                                                            mtk::crc32_as_string(MTK_SS(app_name<< mtk::GetMachineCode()<<mtk::rand())), app_version));
            session_admin   = mtk::admin::get_qpid_session("admin", "SRVTESTING");
            mtk::msg::sub_process_info  temp_process_info = get_process_info();
            MTK_QPID_RECEIVER_CONNECT_THIS(
                                    hqpid_commands,
                                    mtk::admin::get_url("admin"),
                                    "SRVTESTING",
                                    mtk::admin::msg::req_command::get_in_subject(temp_process_info.location.client_code, 
                                                                             temp_process_info.location.machine,
                                                                             temp_process_info.process_name,
                                                                             temp_process_info.process_uuid),
                                    mtk::admin::msg::req_command,
                                    on_command_received)

            MTK_QPID_RECEIVER_CONNECT_THIS(
                                    hqpid_central_keepalive,
                                    mtk::admin::get_url("admin"),
                                    "SRVTESTING",
                                    mtk::admin::msg::pub_central_keep_alive::get_in_subject(),
                                    mtk::admin::msg::pub_central_keep_alive,
                                    on_central_ka_received)
        }
        if(role == "server")
            mtk::set_control_fluct_key(MTK_SS(process_info.location.client_code << "." << process_info.location.machine));
        else
            mtk::set_control_fluct_key(MTK_SS("_" << process_info.location.client_code << "." << process_info.location.machine));
        
        
        full_initialized = true;
        if(signal_admin_ready)
            signal_admin_ready->emit();
        send_enter_and_start_keepalive();

            
        //register_command("ADMIN", "help", "")->connect(this, &CLASS_NAME::command_help);
        MTK_CONNECT_THIS(*register_command("__GLOBAL__",    "help",         ""),                                                command_help)
        
        MTK_CONNECT_THIS(*register_command("__GLOBAL__",    "ver",          ""),                                                command_version_app)
        MTK_CONNECT_THIS(*register_command("__GLOBAL__",    "ver",          ""),                                                command_version)
        MTK_CONNECT_THIS(*register_command("ADMIN",         "ver",          ""),                                                command_version)
        
        MTK_CONNECT_THIS(*register_command("__GLOBAL__",    "modifs",       "brief information about modifications"),           command_modifications_app)
        MTK_CONNECT_THIS(*register_command("__GLOBAL__",    "modifs",       "brief information about modifications"),           command_modifications)
        MTK_CONNECT_THIS(*register_command("ADMIN",         "modifs",       ""),                                                command_modifications)

        MTK_CONNECT_THIS(*register_command("__GLOBAL__",    "stats",        "some stats"),                                      command_stats)
        MTK_CONNECT_THIS(*register_command("ADMIN",         "stats",        "some stats"),                                      command_stats)
        
        MTK_CONNECT_THIS(*register_command("__GLOBAL__",    "infoapp",      "info about the application"),                      command_infoapp)
        MTK_CONNECT_THIS(*register_command("ADMIN",         "config",       "config information"),                              command_config)
        MTK_CONNECT_THIS(*register_command("ADMIN",         "date_time",    "returns de local current time on the machine"),    command_date_time)
        MTK_CONNECT_THIS(*register_command("ADMIN",         "ping",         "returns a pong"),                                  command_ping)
        MTK_CONNECT_THIS(*register_command("ADMIN",         "rqclose",      "request close application (confirmation requiered)"
                                        " on clients will produce a non ordered close", true),                                  command_rqclose)
                                        
        MTK_CONNECT_THIS(*register_command("ADMIN",         "realtime",     "some realtime stats"),                             command_realtime)
        MTK_CONNECT_THIS(*register_command("__GLOBAL__",    "stats",        "some stats"),                                      command_realtime)
        MTK_CONNECT_THIS(*register_command("ADMIN",         "stats",        "some stats"),                                      command_realtime)

        MTK_CONNECT_THIS(*register_command("ADMIN",         "set_machine_code",        "write a machine code on config file"),  command_set_machine_code)
    }

    std::string admin_status::get_mandatory_property(const std::string& path_and_property)
    {
        mtk::Nullable<std::string>  value = config_file.GetValue(path_and_property);
        if(value.HasValue() == false)
            throw mtk::Alarm(MTK_HERE, "admin", MTK_SS("mising mandatory property " << path_and_property), mtk::alPriorError, mtk::alTypeNoPermisions);
        else
            return value.Get();
    }

    void admin_status::send_enter_and_start_keepalive(void)
    {
        mtk::admin::msg::pub_enter enter_msg(get_process_info(), ka_interval_send, ka_interval_check);
        //std::cout << enter_msg << std::endl;
        mtk::send_message(session_admin, enter_msg);
        
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "admin.app_enter", "Entering application", mtk::alPriorDebug, mtk::alTypeUnknown));
        
        MTK_TIMER_1S(send_keep_alive)
        MTK_TIMER_1S(check_last_received_message)
        MTK_TIMER_1S(check_central_keep_alive)
        MTK_TIMER_1S(send_stats_periodically)
        
        MTK_TIMER_1S(check_local_fluct)
    }
    
    void  admin_status::send_keep_alive(void)
    {
        MTK_EXEC_MAX_FREC_NO_FIRST_S(ka_interval_send)
            if(role=="server")
            {
                mtk::admin::msg::pub_keep_alive_srv keep_alive_msg(get_process_info(), ka_interval_send, ka_interval_check);
                //std::cout << keep_alive_msg << std::endl;
                mtk::send_message(session_admin, keep_alive_msg);
            }
            else if(role=="client")
            {
                mtk::admin::msg::pub_keep_alive_clients keep_alive_msg(mtk::admin::msg::pub_keep_alive_srv(get_process_info(), ka_interval_send, ka_interval_check), client_login_confirmation);
                mtk::send_message(session_admin, keep_alive_msg);
            }
            else
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "admin", "invalid role trying to close the application", mtk::alPriorCritic, mtk::alTypeNoPermisions));            
        MTK_END_EXEC_MAX_FREC
    }
    void admin_status::check_last_received_message(void)
    {
        MTK_EXEC_MAX_FREC_NO_FIRST_S(mtk::dtSeconds(2))
            mtk::dtTimeQuantity  tq_no_receiving_messages(mtk::dtNowLocal() - mtk::mtk_qpid_stats::last_received_message());

            if(tq_no_receiving_messages > mtk::dtSeconds(2))
            {
                signal_no_receiving_messages->emit(tq_no_receiving_messages);
                last_not_receiving_messages_notification = mtk::dtNowLocal();
            }
            else  if(last_not_receiving_messages_notification.HasValue())
            {
                signal_receiving_messages_back->emit();
                last_not_receiving_messages_notification = mtk::nullable<mtk::dtDateTime>();
            }   
            if(tq_no_receiving_messages > mtk::dtSeconds(10))
            {
                MTK_EXEC_MAX_FREC_S_A(mtk::dtSeconds(10), A)
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "admin", MTK_SS("too long no receiving any message " << tq_no_receiving_messages), mtk::alPriorError, mtk::alTypeRealTime));
                MTK_END_EXEC_MAX_FREC
            }
        MTK_END_EXEC_MAX_FREC
    }
    
    void  admin_status::on_central_ka_received(const mtk::admin::msg::pub_central_keep_alive& ka_msg)
    {
        next_central_keep_alive_to_receive = mtk::dtNowLocal() + ka_msg.ka_interval_check;
        check_fluct("central.ka",  ka_msg.__internal_warning_control_fields->sent_date_time);
    }
    void  admin_status::check_central_keep_alive(void)
    {
        static bool notified_lost_keep_alive = false;
        if(next_central_keep_alive_to_receive < mtk::dtNowLocal())
        {
            MTK_EXEC_MAX_FREC_S(mtk::dtSeconds(10))
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "admin", MTK_SS("missing central keep alive.     Expected on " 
                                            << next_central_keep_alive_to_receive  << " local time " << mtk::dtNowLocal()), 
                                            mtk::alPriorError, mtk::alTypeRealTime));
                notified_lost_keep_alive=true;
            MTK_END_EXEC_MAX_FREC
                                            
        }
        else if(notified_lost_keep_alive == true)
        {
            notified_lost_keep_alive = false;
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "admin", MTK_SS("receiving back central keep alive.   Next expected on" 
                                        << next_central_keep_alive_to_receive  << " local time " << mtk::dtNowLocal()), 
                                        mtk::alPriorError, mtk::alTypeRealTime));
        }
    }


    void admin_status::NotifyAlarm (const mtk::Alarm& alarm)
    {
        if(alarm.priority == mtk::alPriorCritic  ||  alarm.priority == mtk::alPriorError)
        {
            NotifyAlarmErrorCritic(alarm);
            signal_alarm_error_critic->emit(alarm);
        }
        else
        {
            NotifyAlarm_noerror(alarm);
            signal_alarm_nonerror->emit(alarm);
        }
    }

    void admin_status::__direct_NotifyAlarm (const mtk::Alarm& alarm)
    {
        //if(alarm.priority == mtk::alPriorCritic  ||  alarm.priority == mtk::alPriorError)
        //    std::cout << alarm << std::endl;
        int16_t alarm_id = int16_t(alarm.alarmID);
        {
            mtk::admin::msg::pub_alarm alarm_msg(get_process_info(), alarm.codeSource, alarm.subject, alarm.message, alarm.priority, alarm.type, alarm.dateTime, int16_t(alarm_id));
            mtk::send_message(session_admin, alarm_msg);
        }
        {
            std::list<mtk::BaseAlarm>::const_iterator it = alarm.stackAlarms.begin();
            while (it != alarm.stackAlarms.end())
            {
                mtk::admin::msg::pub_alarm   alarm_msg(get_process_info(), it->codeSource, it->subject, it->message, it->priority, it->type, it->dateTime, int16_t(alarm_id));
                mtk::send_message(session_admin, alarm_msg);
                ++it;
            }
        }
    }



    void admin_status::send_stats_periodically(void)
    {
        MTK_EXEC_MAX_FREC_NO_FIRST(mtk::dtMinutes(45))
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "admin.stats", get_stats_simulating_command(), mtk::alPriorDebug, mtk::alTypeUnknown));
        MTK_END_EXEC_MAX_FREC
    }


    void admin_status::check_fluct(const std::string&  ref,  const mtk::DateTime&  dt)
    {
        static mtk::DateTime  _init (mtk::dtNowLocal());
        check_fluct(ref, dt - _init);
    }
    
    void admin_status::check_fluct(const std::string&  _ref,  const mtk::dtTimeQuantity&  tq)
    {
        std::string ref = MTK_SS("fluct." << _ref);
        mtk::tuple<mtk::dtTimeQuantity, mtk::dtTimeQuantity> flucts = control_flucts.CheckFluctuacion(ref, tq);

        //enum en_process_priority { ppVeryLow, ppLow, ppNormal, ppHigh, ppCritical };
        //en_process_priority   process_priority;
        
        static mtk::dtTimeQuantity  max_prev_fluct = mtk::dtSeconds(0);
        static mtk::dtTimeQuantity  max_5min_fluct = mtk::dtSeconds(0);
        
        if(max_prev_fluct < mtk::abs(flucts._0))
        {
            max_prev_fluct = mtk::abs(flucts._0);
            
            if(process_priority == ppCritical)
            {
                if(max_prev_fluct > mtk::dtMilliseconds(1000))
                {
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, ref, MTK_SS("prev: " << flucts._0), mtk::alPriorCritic, mtk::alTypeRealTime));
                }
                else if(max_prev_fluct > mtk::dtMilliseconds(200))
                {
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, ref, MTK_SS("prev: " << flucts._0), mtk::alPriorError, mtk::alTypeRealTime));
                }
                if(max_prev_fluct > mtk::dtMilliseconds(150))
                {
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, ref, MTK_SS("prev: " << flucts._0), mtk::alPriorWarning, mtk::alTypeRealTime));
                }
            }
            else if(process_priority == ppHigh  ||  process_priority == ppNormal )
            {
                if(max_prev_fluct > mtk::dtMilliseconds(5000))
                {
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, ref, MTK_SS("prev: " << flucts._0), mtk::alPriorCritic, mtk::alTypeRealTime));
                }
                else if(max_prev_fluct > mtk::dtMilliseconds(500))
                {
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, ref, MTK_SS("prev: " << flucts._0), mtk::alPriorError, mtk::alTypeRealTime));
                }
                if(max_prev_fluct > mtk::dtMilliseconds(200))
                {
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, ref, MTK_SS("prev: " << flucts._0), mtk::alPriorWarning, mtk::alTypeRealTime));
                }
            }
            else
            {
                if(max_prev_fluct > mtk::dtMilliseconds(20000))
                {
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, ref, MTK_SS("prev: " << flucts._0), mtk::alPriorCritic, mtk::alTypeRealTime));
                }
                else if(max_prev_fluct > mtk::dtMilliseconds(2000))
                {
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, ref, MTK_SS("prev: " << flucts._0), mtk::alPriorError, mtk::alTypeRealTime));
                }
                if(max_prev_fluct > mtk::dtMilliseconds(1000))
                {
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, ref, MTK_SS("prev: " << flucts._0), mtk::alPriorWarning, mtk::alTypeRealTime));
                }
            }
            
        }

        if(max_5min_fluct < mtk::abs(flucts._1))
        {
            max_5min_fluct = mtk::abs(flucts._1);
            
            if(process_priority == ppCritical)
            {
                if(max_5min_fluct > mtk::dtMilliseconds(1000))
                {
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, ref, MTK_SS("5min: " << flucts._1), mtk::alPriorCritic, mtk::alTypeRealTime));
                }
                else if(max_5min_fluct > mtk::dtMilliseconds(200))
                {
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, ref, MTK_SS("5min: " << flucts._1), mtk::alPriorError, mtk::alTypeRealTime));
                }
                if(max_5min_fluct > mtk::dtMilliseconds(150))
                {
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, ref, MTK_SS("5min: " << flucts._1), mtk::alPriorWarning, mtk::alTypeRealTime));
                }
            }
            else if(process_priority == ppHigh  ||  process_priority == ppNormal )
            {
                if(max_5min_fluct > mtk::dtMilliseconds(5000))
                {
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, ref, MTK_SS("5min: " << flucts._1), mtk::alPriorCritic, mtk::alTypeRealTime));
                }
                else if(max_5min_fluct > mtk::dtMilliseconds(500))
                {
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, ref, MTK_SS("5min: " << flucts._1), mtk::alPriorError, mtk::alTypeRealTime));
                }
                if(max_5min_fluct > mtk::dtMilliseconds(200))
                {
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, ref, MTK_SS("5min: " << flucts._1), mtk::alPriorWarning, mtk::alTypeRealTime));
                }
            }
            else
            {
                if(max_5min_fluct > mtk::dtMilliseconds(20000))
                {
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, ref, MTK_SS("5min: " << flucts._1), mtk::alPriorCritic, mtk::alTypeRealTime));
                }
                else if(max_5min_fluct > mtk::dtMilliseconds(2000))
                {
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, ref, MTK_SS("5min: " << flucts._1), mtk::alPriorError, mtk::alTypeRealTime));
                }
                if(max_5min_fluct > mtk::dtMilliseconds(1000))
                {
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, ref, MTK_SS("5min: " << flucts._1), mtk::alPriorWarning, mtk::alTypeRealTime));
                }
            }
            
        }

        MTK_EXEC_MAX_FREC(mtk::dtSeconds(10))
            max_prev_fluct = mtk::dtSeconds(0);
            max_5min_fluct = mtk::dtSeconds(0);
        MTK_END_EXEC_MAX_FREC
    }

    void admin_status::check_local_fluct(void)
    {
        static std::string  ref = MTK_SS("local_pp:" << int(process_priority));
        check_fluct(ref,  mtk::dtMachineGetTotalMillisecs());
    }

    std::string  admin_status::get_stats_simulating_command(void)
    {
        std::string  result;
        mtk::list<std::string>  response_lines;
        std::string command = "stats";
        mtk::map<std::string, mtk::CountPtr<command_info> >::iterator it = map_commands.find(command);
        if(it == map_commands.end())
            throw mtk::Alarm(MTK_HERE, "admin", "not defined command stats???", mtk::alPriorCritic, mtk::alTypeNoPermisions);
        else if( it->second->signal_command_received->emit(command, "", response_lines) == 0)
            throw  mtk::Alarm(MTK_HERE, "admin", MTK_SS(command << "  has no signal connected"), mtk::alPriorError);
        
        mtk::list<std::string>::iterator  it_response_lines = response_lines.begin();
        while (it_response_lines !=  response_lines.end())
        {
            result += *it_response_lines + "\n";
            ++it_response_lines;
        }
        return result;
    }

    void admin_status::on_command_received(const mtk::admin::msg::req_command& command_msg)
    {
        mtk::list<std::string>  response_lines;
        std::string command;
        std::string params;
        std::string confirmation_code;
        {
            mtk::RegExp re_command_params_confirmation_code(mtk::RegExp("^ *([^ ]+) *(.*) *(__cf[^ ]+) *$"));
            mtk::RegExp re_command_params(mtk::RegExp("^ *([^ ]+) *(.*) *$"));
            if(re_command_params_confirmation_code.Match(command_msg.command_line))
            {
                command = re_command_params_confirmation_code.GetString(0);
                params  = re_command_params_confirmation_code.GetString(1);
                confirmation_code  = re_command_params_confirmation_code.GetString(2);
            }
            else if(re_command_params.Match(command_msg.command_line))
            {
                command = re_command_params.GetString(0);
                params  = re_command_params.GetString(1);
                confirmation_code  = "";
            }
            else
            {
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "admin", MTK_SS(command_msg.command_line << "   incorrect format"), mtk::alPriorError));
                return;
            }
        }
        
        mtk::map<std::string, mtk::CountPtr<command_info> >::iterator it = map_commands.find(command);
        if(it==map_commands.end())
            response_lines.push_back(MTK_SS(command << "  unknow command"));
        else
        {
            if(it->second->confirmation_requiered)
            {
                //  if missing or incorrect confirmation code, request for it
                mtk::DateTime current_dt(mtk::dtNowLocal());
                std::string current_confirmation_code = std::string("__cf") + 
                                mtk::crc32_as_string(MTK_SS(process_info 
                                                << command
                                                << params
                                                << current_dt.GetDay().WarningDontDoThisGetInternal() 
                                                << current_dt.GetHours().WarningDontDoThisGetInternal() 
                                                << current_dt.GetMinutes().WarningDontDoThisGetInternal()));
                if(current_confirmation_code != confirmation_code)
                    response_lines.push_back(MTK_SS(command_msg.command_line << "  incorrect confirmation code, expected... "  << current_confirmation_code));
                //  else, process command
                else if(it->second->signal_command_received->emit(command, params, response_lines) == 0)
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "admin", MTK_SS(command << "  has no signal connected"), mtk::alPriorError));
            }
            else
            {
                if(confirmation_code=="")
                {
                    if( it->second->signal_command_received->emit(command, params, response_lines) == 0)
                        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "admin", MTK_SS(command << "  has no signal connected"), mtk::alPriorError));
                }
                else
                {
                    response_lines.push_back(MTK_SS(command << "  doesn't requieres confirmation code, ignoring command"));
                }
            }
        }
        mtk::list<mtk::admin::msg::sub_command_rd>  data_list;
        mtk::list<std::string>::iterator it2 = response_lines.begin();
        while(it2 != response_lines.end())
        {
            if(it2->size() > 500)
            {
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "admin", MTK_SS("line too long in response to command " << command << " truncating"), mtk::alPriorError));
                (*it2) = it2->substr(0, 200) + std::string("  ... truncated line");
            }
                
            data_list.push_back(mtk::admin::msg::sub_command_rd(MTK_SS(*it2 << std::endl)));
            ++it2;
        }
                                    
        //  sending multiresponses in asyncronous way
        MTK_SEND_MULTI_RESPONSE(        mtk::admin::msg::res_command, 
                                        mtk::admin::msg::sub_command_rd, 
                                        session_admin,
                                        command_msg.request_info,
                                        data_list)
    }

    void admin_status::command_help(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
    {
        mtk::map<std::string, std::string>::iterator it=map_commands_groupped_help.begin();
        while(it!=map_commands_groupped_help.end())
        {
            //std::string help_line = MTK_SS( mtk::s_AlignLeft (it->second->group, 10) << mtk::s_AlignLeft (it->second->name, 10)  <<  it->second->description << std::endl);
            response_lines.push_back(MTK_SS(std::endl << std::endl << it->first << std::endl << "------------------------------------"));
            {
                mtk::vector<std::string>   lines  = mtk::s_split(it->second, "\n");
                for(unsigned int j=0; j<lines.size(); ++j)
                {
                    response_lines.push_back(lines[j]);
                }
            }
            //response_lines.push_back(MTK_SS("           " << it->second));
                                    //help_line));
            ++it;
        }
    }
    void admin_status::command_version(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
    {
        response_lines.push_back(MTK_SS("admin: " << VERSION));
        response_lines.push_back(MTK_SS("mtk: " << mtk::MTK_VERSION));
    }
    void admin_status::command_version_app(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
    {
        response_lines.push_back(MTK_SS(app_name << ": " << app_version));
    }

    void admin_status::command_modifications_app  (const std::string& /*command*/, const std::string& /*param*/,  mtk::list<std::string>&  response_lines)
    {
        response_lines.push_back(app_name);
        response_lines.push_back(".......................................");
        response_lines.push_back(app_modifications);
    }
    
    void admin_status::command_modifications  (const std::string& /*command*/, const std::string& /*param*/,  mtk::list<std::string>&  response_lines)
    {
        response_lines.push_back("admin");
        response_lines.push_back(".......................................");
        response_lines.push_back(MODIFICATIONS);
    }

    void admin_status::command_stats(const std::string& /*command*/, const std::string& /*param*/, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string> lines = mtk::s_split(mtk::mtk_qpid_stats::get_mtk_qpid_stats_string(), "\n");
        for(unsigned j=0; j<lines.size(); ++j)
            response_lines.push_back(lines[j]);
        response_lines.push_back(MTK_SS("adm_start : " << start_date_time));
        response_lines.push_back(MTK_SS("adm_runing: " << mtk::dtNowLocal() - start_date_time));
    }

    void admin_status::command_realtime(const std::string& /*command*/, const std::string& /*param*/, mtk::list<std::string>&  response_lines)
    {
        response_lines.push_back("realtime-----------------------------------");
        mtk::list<std::string>  partial_result = control_flucts.GetReport();
        for(mtk::list<std::string>::iterator it2=partial_result.begin(); it2!=partial_result.end(); ++it2)
            response_lines.push_back(*it2);
    }


    void admin_status::command_infoapp(const std::string& /*command*/, const std::string& /*param*/, mtk::list<std::string>&  response_lines)
    {
        response_lines.push_back(app_description);
    }

    void admin_status::command_config(const std::string& /*command*/, const std::string& /*param*/, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string> lines = mtk::s_split(config_file.GetStringConfigFileLines(), "\n");
        for(unsigned j=0; j<lines.size(); ++j)
            response_lines.push_back(lines[j]);
    }
    
    void admin_status::command_ping(const std::string& /*command*/, const std::string& /*param*/, mtk::list<std::string>&  response_lines)
    {
        response_lines.push_back(MTK_SS("pong  " << mtk::dtNowLocal()));
    }

    void admin_status::command_rqclose(const std::string& /*command*/, const std::string& /*param*/, mtk::list<std::string>&  response_lines)
    {
        response_lines.push_back("closing as you demand...");
        close_application("requested by interactive admin command");
        
        if(role=="server")
            mtk::stop_timer();
        else if(role=="client")
            exit(-1);
        else
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "admin", "invalid role trying to close the application", mtk::alPriorCritic, mtk::alTypeNoPermisions));            
    }

    void admin_status::command_date_time(const std::string& /*command*/, const std::string& /*param*/, mtk::list<std::string>&  response_lines)
    {
        response_lines.push_back(MTK_SS("current_date_time       " << mtk::dtNowLocal()  << std::endl
                                  <<    "current_date_time_utc   " << mtk::dtNowUTC()));
    }

    void admin_status::command_set_machine_code(const std::string& /*command*/, const std::string& param, mtk::list<std::string>&  response_lines)
    {
        this->set_config_property("ADMIN.CLIENT.machine_code", mtk::s_trim(param, " \t"));
        response_lines.push_back(MTK_SS("writed machine code... " << this->get_mandatory_property("ADMIN.CLIENT.machine_code")));
        response_lines.push_back(MTK_SS("It will be ready on next execution"));
    }

    mtk::CountPtr<mtk::Signal<const std::string& /*cmd*/, const std::string& /*params*/, mtk::list<std::string>& /*response lines*/> >
    admin_status::register_command(const std::string& group, const std::string& name, const std::string& description, bool confirmation_requiered)
    {
        std::string full_command_name;
        if(group=="__GLOBAL__")
            full_command_name = name;
        else
            full_command_name = MTK_SS(mtk::s_toLower(group) << "." << name);
            
        if(map_commands.find(full_command_name) == map_commands.end())
        {
            map_commands[full_command_name] = mtk::make_cptr(new command_info(group, full_command_name, description, confirmation_requiered));
            std::string help_line = MTK_SS( "        " << mtk::s_AlignLeft (name, 30, '.')  <<  " " << description);
            map_commands_groupped_help[group] = MTK_SS(map_commands_groupped_help[group] << std::endl  <<  help_line);
        }
        return map_commands[full_command_name]->signal_command_received;
    }



    mtk::Nullable<std::string>   admin_status::get_config_property(const std::string& path)
    {
        return config_file.GetValue(path);
    }
    
    mtk::list<std::string>   admin_status::get_config_nodes    (const std::string& path)
    {
        return config_file.GetNodes(path);
    }
    
    
    mtk::msg::sub_control_fluct     admin_status::get_control_fluct_info(void)
    {
        return mtk::msg::sub_control_fluct(MTK_SS(process_info.location.client_code << "." << process_info.location.machine), mtk::dtNowLocal());
    }
    void  admin_status::check_control_fluct(const mtk::msg::sub_control_fluct&  cf)
    {
        MTK_EXEC_MAX_FREC_S(mtk::dtMilliseconds(500))
            check_fluct(cf.key,  cf.datetime);
        MTK_END_EXEC_MAX_FREC
    }
    

    void admin_status::set_config_property(const std::string& path, const std::string& property_value)
    {
        config_file.ModifOrCreate(path, property_value);
        config_file.SaveToFile();
    }

    
    mtk::msg::sub_request_info   admin_status::get_request_info (void)
    {
        if(role=="server")
        {
            static int counter=0;
            return mtk::msg::sub_request_info (mtk::msg::sub_request_id(app_name, MTK_SS(++counter)), get_process_info());
        }
        else if(role=="client")
        {
            static int contador =1;
            std::string session_id = client_login_confirmation.session_id;
            if(session_id=="")
                session_id = "provisional";
            return mtk::msg::sub_request_info(mtk::msg::sub_request_id(session_id, MTK_SS(++contador)), get_process_info());
        }
        else
            throw mtk::Alarm(MTK_HERE, "admin", MTK_SS(role << "  request info with invalid role"), mtk::alPriorCritic, mtk::alTypeNoPermisions);
    }
    


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //          class admin_status  end implementation
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
};


namespace mtk {
namespace admin {

    
void init(const std::string& config_file_name, const std::string& app_name, 
            const std::string& app_version, const std::string& app_description, const std::string& app_modifications )
{
    admin_status::admin_status_instance = new admin_status();
    admin_status::i()->init(config_file_name, app_name, app_version, app_description, app_modifications);
}






mtk::CountPtr< mtk::qpid_session >     get_qpid_session(const std::string&  url_for, const std::string& address)
{
    static int counter;
    if(++counter > 500)
    {
        MTK_EXEC_MAX_FREC_S(mtk::dtSeconds(5))
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "admin", "too many calls" , mtk::alPriorError, mtk::alTypeOverflow));
        MTK_END_EXEC_MAX_FREC
    }
    else if(++counter > 100)
    {
        MTK_EXEC_MAX_FREC_S(mtk::dtSeconds(5))
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "admin", "too many calls" , mtk::alPriorWarning, mtk::alTypeOverflow));
        MTK_END_EXEC_MAX_FREC
    }
    
    if(admin_status::i()->role=="client")
    {
        if(url_for != "client"  ||  address != "CLITESTING")
        {
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "admin", MTK_SS("url_for: " << url_for << "  address: " << address
                        << "  weird for a client") , mtk::alPriorWarning, mtk::alTypeOverflow));
        }
    }
    
    return mtk::get_from_factory< mtk::qpid_session >(mtk::make_tuple(get_url(url_for), address));
}


    
    
mtk::msg::sub_request_info   get_request_info (void)
{
    return admin_status::i()->get_request_info();
}


mtk::msg::sub_process_info         get_process_info(void)
{
    return admin_status::i()->get_process_info();
}


std::string                             get_request_code    (void)
{
    return mtk::crc32_as_string( MTK_SS(admin_status::i()->get_process_info() <<  mtk::rand()));
}


std::string                             get_url             (const std::string& url_for)
{
    mtk::Nullable<std::string> url = admin_status::i()->get_config_file().GetValue(MTK_SS("ADMIN.URLS." << url_for));
    if(url.HasValue()==false)
        throw mtk::Alarm(MTK_HERE, "admin", MTK_SS(url_for  << "   requested invalid url"), mtk::alPriorCritic);
    else
        return url.Get();
}


mtk::CountPtr<mtk::Signal<const std::string& /*cmd*/, const std::string& /*params*/, mtk::list<std::string>& /*rsponse lines*/> >
register_command(const std::string& group, const std::string& name, const std::string& description, bool confirmation_requiered)
{
    return admin_status::i()->register_command(group, name, description, confirmation_requiered);
}


mtk::CountPtr<mtk::Signal<const mtk::Alarm&> >       get_signal_alarm_error_critic(void)
{
    return admin_status::i()->signal_alarm_error_critic;
}

mtk::CountPtr<mtk::Signal<const mtk::Alarm&> >       get_signal_alarm_nonerror    (void)
{
    return admin_status::i()->signal_alarm_nonerror;
}

mtk::CountPtr<mtk::Signal<const mtk::dtTimeQuantity&> >   get_signal_no_receiving_messages(void)
{
    return admin_status::i()->signal_no_receiving_messages;
}

mtk::CountPtr<mtk::Signal<> >                           get_signal_receiving_messages_back(void)
{
    return admin_status::i()->signal_receiving_messages_back;
}


mtk::Nullable<std::string>   get_config_property(const std::string& path)
{
    return admin_status::i()->get_config_property(path);
}

mtk::list<std::string>     get_config_nodes    (const std::string& path)
{
    return admin_status::i()->get_config_nodes(path);
}


void set_config_property(const std::string& path, const std::string& property_value)
{
    admin_status::i()->set_config_property(path, property_value);    
}


void client_login_ok_confirmation   (const mtk::acs::msg::res_login::IC_login_response_info& client_login_confirmation)
{
    admin_status::i()->client_login_confirmation = client_login_confirmation;
    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "admin", MTK_SS("registered login ok: " << client_login_confirmation), mtk::alPriorDebug));
}

void client_logout_confirmation     (const std::string& description)
{
    admin_status::i()->client_login_confirmation = mtk::acs::msg::res_login::IC_login_response_info("", "");
    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "admin", MTK_SS("registered logout: " << description), mtk::alPriorDebug));
}


mtk::Signal<>*           get_signal_admin_ready(void)
{
    static bool initialized = false;
    if(signal_admin_ready == 0  &&  initialized==false)
    {
        signal_admin_ready = new mtk::Signal<>;
        initialized = true;
    }
    return signal_admin_ready;
}



mtk::msg::sub_control_fluct     get_control_fluct_info(void)
{
    return admin_status::i()->get_control_fluct_info();
}

void  check_control_fluct(const mtk::msg::sub_control_fluct&  cf)
{
    return admin_status::i()->check_control_fluct(cf);
}



bool   is_production(void)
{
    return false;
}




};     //namespace admin {
      
      
      
void AlarmMsg (const Alarm& alarm)
{
    if(admin_status::admin_status_instance!=0   &&  admin_status::i()->full_initialized)
        admin_status::i()->NotifyAlarm(alarm);
    else
    {
        std::cerr << "admin not initialized" << std::endl;
        std::cerr << alarm << std::endl;
    }
}


void check_control_flields_flucts    (const std::string&  key, const mtk::DateTime&  dt)
{
    if(key!= ""   &&  key[0] != '_')
        mtk::admin::check_control_fluct(mtk::msg::sub_control_fluct(key, dt));
}



void  __internal_admin_nevercall_me____release_on_exit(void)
{
    admin_status::release();
}




      
};  //namespace mtk {

