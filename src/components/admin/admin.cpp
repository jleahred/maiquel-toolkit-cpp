#include "admin.h"


#if MTK_PLATFORM == MTK_LINUX_PLATFORM

    #include <unistd.h>

#endif



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






namespace {
    const char*   VERSION = "2012-02-03";

    const char*   MODIFICATIONS =
                        "           2011-03-16     first version\n"
                        "           2012-02-03     restoring session and  cerr \n"
                        "           2012-03-12     removed cerr\n"
                        ;






    bool  auto_close_canceled=false;
    void  timer_check_auto_close(void);
    void  timer_check_resynchr_monotonic(void);
    void command_autoclose_show         (const std::string& command, const std::string& param,  mtk::list<std::string>&  response_lines);
    void command_autoclose_cancel       (const std::string& command, const std::string& param,  mtk::list<std::string>&  response_lines);
    void command_autoclose_reactivate   (const std::string& command, const std::string& param,  mtk::list<std::string>&  response_lines);
    void command_resynchr_monotonic     (const std::string& command, const std::string& param,  mtk::list<std::string>&  response_lines);


    mtk::Signal<>*           signal_admin_ready  = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //          class admin_status
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class admin_status   :  public  mtk::SignalReceptor
    {
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
            mtk::acs::msg::res_login::IC_session_info     client_login_confirmation;
            bool                  full_initialized;

            void                  init                ( const std::string& config_file_name,
                                                        const std::string& app_name,
                                                        const std::string& app_version,
                                                        const std::string& app_description,
                                                        const std::string& app_modifications);

            void                  close_application   ( const std::string& reason );
            void                  close_delayed       ( const std::string& reason );


            mtk::ConfigFile&      get_config_file     (void)    { return config_file;  };

            std::string                  get_session_id   (void);
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


            admin_status()  :   client_login_confirmation("", "", ""),
                                full_initialized(false),
                                signal_alarm_error_critic(new mtk::Signal<const mtk::Alarm&> ),
                                signal_alarm_nonerror(new mtk::Signal<const mtk::Alarm&> ),
                                process_priority(ppVeryLow),
                                process_info(mtk::msg::sub_process_info(mtk::msg::sub_location("", ""), "", "", "", "")),
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
            std::string                                 get_config_mandatory_property (const std::string& path);
            void                                        set_config_property(const std::string& path, const std::string&  property_value);

            mtk::list<std::string>                      get_config_nodes    (const std::string& path);
            mtk::Nullable<mtk::list<std::string> >      get_config_list     (const std::string& path);
            void                                        set_config_list     (const std::string& path, const mtk::list<std::string>&  list);


            mtk::msg::sub_control_fluct                 get_control_fluct_info(void);
            void                                        check_control_fluct(const mtk::msg::sub_control_fluct&  cf);
            void                                        check_control_fluct__info_on_times( const mtk::msg::sub_control_fluct&  cf,
                                                                                            const mtk::dtTimeQuantity&  critic_on,
                                                                                            const mtk::dtTimeQuantity&  error_on,
                                                                                            const mtk::dtTimeQuantity&  warning_on);

            std::string                                 app_name;
            std::string                                 app_version;
            std::string                                 app_description;
            std::string                                 app_modifications;
            std::string                                 role;
            std::string                                 mon_subject_role;

            mtk::msg::sub_process_info                  process_info;
            //std::string                                 session_id;
            mtk::dtTimeQuantity                         ka_interval_send;
            mtk::dtTimeQuantity                         ka_interval_check;

            mtk::DateTime                               start_date_time;

            mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::admin::msg::req_command_cli>            > hqpid_commands_cli;
            mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::admin::msg::req_command_srv>            > hqpid_commands_srv;
            mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::admin::msg::pub_central_keep_alive> > hqpid_central_keepalive;

            void                                        send_enter_and_start_keepalive(void);
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

            void on_command_received2       (const mtk::admin::msg::req_command2& command_msg);
            void on_command_received_cli    (const mtk::admin::msg::req_command_cli& command_msg);
            void on_command_received_srv    (const mtk::admin::msg::req_command_srv& command_msg);
            void command_help               (const std::string& command, const std::string& param,  mtk::list<std::string>&  response_lines);
            void command_version            (const std::string& command, const std::string& param,  mtk::list<std::string>&  response_lines);
            void command_version_app        (const std::string& command, const std::string& param,  mtk::list<std::string>&  response_lines);
            void command_modifications      (const std::string& command, const std::string& param,  mtk::list<std::string>&  response_lines);
            void command_modifications_app  (const std::string& command, const std::string& param,  mtk::list<std::string>&  response_lines);
            void command_stats              (const std::string& command, const std::string& param,  mtk::list<std::string>&  response_lines);
            void command_realtime           (const std::string& command, const std::string& param,  mtk::list<std::string>&  response_lines);
            void command_infoapp            (const std::string& command, const std::string& param,  mtk::list<std::string>&  response_lines);
            void command_config             (const std::string& command, const std::string& param,  mtk::list<std::string>&  response_lines);
            void command_set_config_property(const std::string& command, const std::string& param,  mtk::list<std::string>&  response_lines);
            void command_del_config_property(const std::string& command, const std::string& param,  mtk::list<std::string>&  response_lines);
            void command_ping               (const std::string& command, const std::string& param,  mtk::list<std::string>&  response_lines);
            void command_date_time          (const std::string& command, const std::string& param,  mtk::list<std::string>&  response_lines);
            void command_set_machine_code   (const std::string& command, const std::string& param,  mtk::list<std::string>&  response_lines);
            void command_rqclose            (const std::string& command, const std::string& param,  mtk::list<std::string>&  response_lines);

            std::string  get_stats_simulating_command(void);
            std::string  get_vers_simulating_command(void);
            void         send_stats_periodically(void);
            void         send_vers_periodically(void);

            mtk::ControlFluctuacionesMulti<std::string>     control_flucts;
            void                                            check_fluct(const std::string&  id,  const mtk::DateTime&  dt);
            void                                            check_fluct(const std::string&  id,  const mtk::dtTimeQuantity&  tq);
            void                                            check_fluct(const std::string&  id,  const mtk::dtTimeQuantity&  tq,
                                                                                                    const mtk::dtTimeQuantity&  critic_on,
                                                                                                    const mtk::dtTimeQuantity&  error_on,
                                                                                                    const mtk::dtTimeQuantity&  warning_on);
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


    void  admin_status::close_delayed(const std::string& reason)
    {
        static bool  exit_message_sent = false;
        if(exit_message_sent==false)
        {
            __direct_NotifyAlarm(mtk::Alarm(MTK_HERE, "admin.app_exit", MTK_SS("Exiting application  (in 20 secs)" << reason), mtk::alPriorDebug, mtk::alTypeUnknown));
            __direct_NotifyAlarm(mtk::Alarm(MTK_HERE, "admin.app_exit_stats", get_stats_simulating_command(), mtk::alPriorDebug, mtk::alTypeUnknown));
            mtk::admin::get_signal_admin_close_delayed()->emit();
        }
        MTK_CALL_LATER1S_THIS(mtk::dtSeconds(20), reason, close_application)
    }

    void  admin_status::close_application(const std::string& reason)
    {
        static bool  exit_message_sent = false;
        if(exit_message_sent==false)
        {
            //  send exit message
            mtk::admin::msg::pub_exit exit_msg(admin_status_instance->get_process_info(), reason);
            //std::cout << exit_msg << std::endl;
            mtk_send_message("admin", exit_msg);
            exit_message_sent = true;
        }
        mtk::admin::get_signal_admin_close()->emit();
        if(role=="server")
            mtk::stop_timer();
        else if(role=="client")
            return;
        else
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "admin", "invalid role trying to close the application", mtk::alPriorCritic, mtk::alTypeNoPermisions));
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
            #if MTK_PLATFORM == MTK_LINUX_PLATFORM

                if(mtk::admin::is_production())
                {
                    if(daemon(1,0) == -1)
                    {
                        perror("error daemon call");
                        exit(1);
                    }
                }

            #endif

            app_name = get_config_mandatory_property("ADMIN.server_name");
            std::string priority = get_config_mandatory_property("ADMIN.priority");
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
            mon_subject_role = "CLI";
            process_info = mtk::msg::sub_process_info(mtk::msg::sub_process_info(mtk::msg::sub_location(get_config_mandatory_property("ADMIN.CLIENT.location"),
                                                            MTK_SS(get_config_mandatory_property("ADMIN.CLIENT.machine_code") << "@" << mtk::GetMachineCode())),
                                                            app_name,
                                                            mtk::crc32_as_string(MTK_SS(app_name<<get_config_mandatory_property("ADMIN.CLIENT.machine_code") << "@" << mtk::GetMachineCode()<<mtk::rand())),
                                                            app_version,
                                                            std::string("CLI")));

            mtk::msg::sub_process_info  temp_process_info = get_process_info();
            MTK_QPID_RECEIVER_CONNECT_THIS(
                                    hqpid_commands_cli,
                                    mtk::admin::get_url("admin"),
                                    mtk::admin::msg::req_command_cli::get_in_subject(
                                                                             temp_process_info.location.broker_code,
                                                                             temp_process_info.location.machine,
                                                                             temp_process_info.process_name,
                                                                             temp_process_info.process_uuid),
                                    mtk::admin::msg::req_command_cli,
                                    on_command_received_cli)

            MTK_QPID_RECEIVER_CONNECT_THIS(
                                    hqpid_central_keepalive,
                                    mtk::admin::get_url("admin"),
                                    mtk::admin::msg::pub_central_keep_alive::get_in_subject("*"),
                                    mtk::admin::msg::pub_central_keep_alive,
                                    on_central_ka_received)
        }
        else
        {
            mon_subject_role = "SRV";
            process_info = mtk::msg::sub_process_info(mtk::msg::sub_process_info(mtk::msg::sub_location(get_config_mandatory_property("ADMIN.SERVER.broker_code"),
                                                            mtk::GetMachineCode()), app_name,
                                                            mtk::crc32_as_string(MTK_SS(app_name<< mtk::GetMachineCode()<<mtk::rand())),
                                                            app_version,
                                                            std::string("SRV")));

            mtk::msg::sub_process_info  temp_process_info = get_process_info();
            MTK_QPID_RECEIVER_CONNECT_THIS(
                                    hqpid_commands_srv,
                                    mtk::admin::get_url("admin"),
                                    mtk::admin::msg::req_command_srv::get_in_subject("*",       //  GSx   origin_broker_code
                                                                             temp_process_info.location.broker_code,
                                                                             temp_process_info.location.machine,
                                                                             temp_process_info.process_name,
                                                                             temp_process_info.process_uuid),
                                    mtk::admin::msg::req_command_srv,
                                    on_command_received_srv)

            MTK_QPID_RECEIVER_CONNECT_THIS(
                                    hqpid_central_keepalive,
                                    mtk::admin::get_url("admin"),
                                    mtk::admin::msg::pub_central_keep_alive::get_in_subject("*"),
                                    mtk::admin::msg::pub_central_keep_alive,
                                    on_central_ka_received)
        }
        if(role == "server")
            mtk::set_control_fluct_key(MTK_SS(process_info.location.broker_code << "." << process_info.location.machine));
        else
            mtk::set_control_fluct_key(MTK_SS("_" << process_info.location.broker_code << "." << process_info.location.machine));


        full_initialized = true;
        if(signal_admin_ready)
            signal_admin_ready->emit();
        send_enter_and_start_keepalive();


        MTK_CONNECT_THIS(*register_command("__GLOBAL__",    "help",                 ""),                                                command_help)

        MTK_CONNECT_THIS(*register_command("__GLOBAL__",    "ver",                  ""),                                                command_version_app)
        MTK_CONNECT_THIS(*register_command("__GLOBAL__",    "ver",                  ""),                                                command_version)
        MTK_CONNECT_THIS(*register_command("ADMIN",         "ver",                  ""),                                                command_version)

        MTK_CONNECT_THIS(*register_command("__GLOBAL__",    "modifs",               "brief information about modifications"),           command_modifications_app)
        MTK_CONNECT_THIS(*register_command("__GLOBAL__",    "modifs",               "brief information about modifications"),           command_modifications)
        MTK_CONNECT_THIS(*register_command("ADMIN",         "modifs",               ""),                                                command_modifications)

        MTK_CONNECT_THIS(*register_command("__GLOBAL__",    "stats",                "some stats"),                                      command_stats)
        MTK_CONNECT_THIS(*register_command("ADMIN",         "stats",                "some stats"),                                      command_stats)

        MTK_CONNECT_THIS(*register_command("__GLOBAL__",    "infoapp",              "info about the application"),                      command_infoapp)
        MTK_CONNECT_THIS(*register_command("ADMIN",         "config",               "config information"),                              command_config)
        MTK_CONNECT_THIS(*register_command("ADMIN",         "set_config_property",  "<path> <value> modif property on config file" , true), command_set_config_property)
        MTK_CONNECT_THIS(*register_command("ADMIN",         "del_config_property",  "<path> delete property on config file", true),         command_del_config_property)
        MTK_CONNECT_THIS(*register_command("ADMIN",         "date_time",            "returns de local current time on the machine"),    command_date_time)
        MTK_CONNECT_THIS(*register_command("ADMIN",         "ping",                 "returns a pong"),                                  command_ping)
        MTK_CONNECT_THIS(*register_command("ADMIN",         "rqclose",              "request close application (confirmation requiered)"
                                        " on clients will produce a non ordered close", true),                                  command_rqclose)

        MTK_CONNECT_THIS(*register_command("ADMIN",         "realtime",             "some realtime stats"),                             command_realtime)
        MTK_CONNECT_THIS(*register_command("__GLOBAL__",    "stats",                "some stats"),                                      command_realtime)
        MTK_CONNECT_THIS(*register_command("ADMIN",         "stats",                "some stats"),                                      command_realtime)

        MTK_CONNECT_THIS(*register_command("ADMIN",         "set_machine_code",     "write a machine code on config file", true),       command_set_machine_code)

        register_command("ADMIN",                           "autoclose.show",       "Shows autoclose configured time" )->connect(&command_autoclose_show);
        register_command("ADMIN",                           "autoclose.cancel",     "cancel autoclose",      true     )->connect(&command_autoclose_cancel);
        register_command("ADMIN",                           "autoclose.reactivate", "reactivate autoclose",  true     )->connect(&command_autoclose_reactivate);
        register_command("ADMIN",                           "resynchr",             "DANGEROUS.  resynchr monotonic clock with system clock",  true     )->connect(&command_resynchr_monotonic);

        MTK_TIMER_1SF(timer_check_auto_close);
        MTK_TIMER_1SF(timer_check_resynchr_monotonic);
    }


    void admin_status::send_enter_and_start_keepalive(void)
    {
        mtk::admin::msg::pub_enter enter_msg(get_process_info(), ka_interval_send, ka_interval_check);
        //std::cout << enter_msg << std::endl;
        mtk_send_message("admin", enter_msg);

        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "admin.app_enter", MTK_SS("Entering application  mtk_ver: " << mtk::MTK_VERSION), mtk::alPriorDebug, mtk::alTypeUnknown));

        MTK_TIMER_1S(send_keep_alive)
        MTK_TIMER_1S(check_last_received_message)
        MTK_TIMER_1S(check_central_keep_alive)
        MTK_TIMER_1S(send_stats_periodically)
        MTK_TIMER_1S(send_vers_periodically)

        MTK_TIMER_1S(check_local_fluct)
    }

    void  admin_status::send_keep_alive(void)
    {
        MTK_EXEC_MAX_FREC_NO_FIRST_S(ka_interval_send)
            if(role=="server")
            {
                mtk::admin::msg::pub_keep_alive_srv keep_alive_msg(get_process_info(), ka_interval_send, ka_interval_check);
                //std::cout << keep_alive_msg << std::endl;
                mtk_send_message("admin", keep_alive_msg);
            }
            else if(role=="client")
            {
                mtk::admin::msg::pub_keep_alive_cli keep_alive_msg(mtk::admin::msg::pub_keep_alive_srv(get_process_info(), ka_interval_send, ka_interval_check), client_login_confirmation);
                mtk_send_message("admin", keep_alive_msg);
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

        if(ka_msg.is_production !=  mtk::admin::is_production())
        {
            MTK_EXEC_MAX_FREC_S(mtk::dtMinutes(1))
                if(mtk::admin::is_production())
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "admin", MTK_SS("local configuration PRODUCTION, received on ka  not production "), mtk::alPriorError, mtk::alTypeLogicError));
                else
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "admin", MTK_SS("local configuration NOT production, received on ka  production "), mtk::alPriorError, mtk::alTypeLogicError));
            MTK_END_EXEC_MAX_FREC
        }
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

        if(alarm.message.size() > 2048)
        {
            MTK_EXEC_MAX_FREC(mtk::dtSeconds(30))
                mtk::AlarmMsg(mtk::Alarm("admin::__direct_NotifyAlarm", "admin", MTK_SS("message too long, truncating  " << alarm.message.substr(0,100)), mtk::alPriorError, mtk::alTypeOverflow));
            MTK_END_EXEC_MAX_FREC
        }

        if(alarm.subject.size() > 2048)
        {
            MTK_EXEC_MAX_FREC(mtk::dtSeconds(30))
                mtk::AlarmMsg(mtk::Alarm("admin::__direct_NotifyAlarm", "admin", MTK_SS("subject too long, truncating  " << alarm.subject.substr(0,100)), mtk::alPriorError, mtk::alTypeOverflow));
            MTK_END_EXEC_MAX_FREC
        }

        if(alarm.codeSource.size() > 2048)
        {
            MTK_EXEC_MAX_FREC(mtk::dtSeconds(30))
                mtk::AlarmMsg(mtk::Alarm("admin::__direct_NotifyAlarm", "admin", MTK_SS("codeSource too long, truncating  " << alarm.codeSource.substr(0,100)), mtk::alPriorError, mtk::alTypeOverflow));
            MTK_END_EXEC_MAX_FREC
        }

        int16_t alarm_id = int16_t(alarm.alarmID);
        {
            mtk::admin::msg::pub_alarm alarm_msg(get_process_info(), alarm.codeSource.substr(0,2048), alarm.subject.substr(0,2048), alarm.message.substr(0,2048), alarm.priority, alarm.type, alarm.dateTime, int16_t(alarm_id));
            mtk_send_message("admin", alarm_msg);
        }
        {
            std::list<mtk::BaseAlarm>::const_iterator it = alarm.stackAlarms.begin();
            while (it != alarm.stackAlarms.end())
            {
                mtk::admin::msg::pub_alarm   alarm_msg(get_process_info(), it->codeSource, it->subject, it->message, it->priority, it->type, it->dateTime, int16_t(alarm_id));
                mtk_send_message("admin", alarm_msg);
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

    void admin_status::send_vers_periodically(void)
    {
        static mtk::dtTimeQuantity   frequency =  mtk::dtMinutes(mtk::rand()%30+45);     //  random frecuency from  45  min to 1h 15min
        MTK_EXEC_MAX_FREC_NO_FIRST(frequency)
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "admin.vers", get_vers_simulating_command(), mtk::alPriorDebug, mtk::alTypeUnknown));
        MTK_END_EXEC_MAX_FREC
    }


    void admin_status::check_fluct(const std::string&  ref,  const mtk::DateTime&  dt)
    {
        static mtk::DateTime  _init (mtk::dtNowLocal());
        check_fluct(ref, dt - _init);
    }

    void admin_status::check_fluct(const std::string&  _ref,  const mtk::dtTimeQuantity&  tq,   const mtk::dtTimeQuantity& tqcritic,
                                                                                                const mtk::dtTimeQuantity& tqerror,
                                                                                                const mtk::dtTimeQuantity& tqwarning)
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

            if(max_prev_fluct > tqcritic)
            {
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, ref, MTK_SS("prev: " << flucts._0), mtk::alPriorCritic, mtk::alTypeRealTime));
            }
            else if(max_prev_fluct > tqerror)
            {
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, ref, MTK_SS("prev: " << flucts._0), mtk::alPriorError, mtk::alTypeRealTime));
            }
            else if(max_prev_fluct > tqwarning)
            {
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, ref, MTK_SS("prev: " << flucts._0), mtk::alPriorWarning, mtk::alTypeRealTime));
            }
        }

        if(max_5min_fluct < mtk::abs(flucts._1))
        {
            max_5min_fluct = mtk::abs(flucts._1);

            if(max_5min_fluct > tqcritic)
            {
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, ref, MTK_SS("5min: " << flucts._1), mtk::alPriorCritic, mtk::alTypeRealTime));
            }
            else if(max_5min_fluct > tqerror)
            {
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, ref, MTK_SS("5min: " << flucts._1), mtk::alPriorError, mtk::alTypeRealTime));
            }
            else if(max_5min_fluct > tqwarning)
            {
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, ref, MTK_SS("5min: " << flucts._1), mtk::alPriorWarning, mtk::alTypeRealTime));
            }
        }

        MTK_EXEC_MAX_FREC(mtk::dtSeconds(10))
            max_prev_fluct = mtk::dtSeconds(0);
            max_5min_fluct = mtk::dtSeconds(0);
        MTK_END_EXEC_MAX_FREC
    }

    void admin_status::check_fluct(const std::string&  _ref,  const mtk::dtTimeQuantity&  tq)
    {
        if(process_priority == ppCritical)
        {
            check_fluct(_ref, tq, mtk::dtMilliseconds(1000), mtk::dtMilliseconds(200), mtk::dtMilliseconds(150));
        }
        else if(process_priority == ppHigh  ||  process_priority == ppNormal )
        {
            check_fluct(_ref, tq, mtk::dtMilliseconds(5000), mtk::dtMilliseconds(500), mtk::dtMilliseconds(200));
        }
        else
        {
            check_fluct(_ref, tq, mtk::dtMilliseconds(20000), mtk::dtMilliseconds(2000), mtk::dtMilliseconds(1000));
        }
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

    std::string  admin_status::get_vers_simulating_command(void)
    {
        std::string  result;
        mtk::list<std::string>  response_lines;
        std::string command = "ver";
        mtk::map<std::string, mtk::CountPtr<command_info> >::iterator it = map_commands.find(command);
        if(it == map_commands.end())
            throw mtk::Alarm(MTK_HERE, "admin", "not defined command ver???", mtk::alPriorCritic, mtk::alTypeNoPermisions);
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



    std::string  fake_process_name(std::string  process_name)
    {
        size_t pos;
        if(process_name.size() > 2)
            pos = mtk::rand() %  (process_name.size()-2)+1;
        else
            pos = 1;
        process_name[pos] = char(process_name[pos] + char(mtk::rand()%4+1));
        return process_name;
    }
    void admin_status::on_command_received2(const mtk::admin::msg::req_command2& command_msg)
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
                {
                    response_lines.push_back(MTK_SS(command_msg.command_line << "  incorrect confirmation code, expected... "));
                    int options=4;
                    if(mtk::admin::is_production()==false)
                        options=1;
                    int no_fake = mtk::rand()%options;
                    for(int ii=0; ii<options; ++ii)
                    {
                        if(no_fake == ii)
                            response_lines.push_back(current_confirmation_code  +  "   "  + this->process_info.location.broker_code + "." + (this->process_info.process_name));
                        else
                            response_lines.push_back(std::string("__cf") + mtk::crc32_as_string(MTK_SS(mtk::rand()<<mtk::dtNowLocal()))  +  "   "
                                                            + this->process_info.location.broker_code + "." + fake_process_name(this->process_info.process_name));
                    }
                }
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
        int max_lines_to_respond = 600;
        while(it2 != response_lines.end())
        {
            if(it2->size() > 500)
            {
                mtk::vector<std::string>  splitted_lines  =  mtk::s_split(*it2, "\n");
                if(splitted_lines.size() > unsigned(max_lines_to_respond))
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "admin", MTK_SS("too many lines  " << splitted_lines.size()  << " >" << max_lines_to_respond+splitted_lines.size() << "   truncating" << command), mtk::alPriorError));
                for(unsigned ii=0; ii<splitted_lines.size()  &&  max_lines_to_respond ; ++ii, --max_lines_to_respond)
                {
                    if(splitted_lines[ii].size() > 600)
                    {
                        auto truncated_line = splitted_lines[ii].substr(0, 600);
                        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "admin", MTK_SS("line too long in command response" << splitted_lines[ii].substr(0, 200)  << " >600 " <<  " truncating"), mtk::alPriorError));
                        data_list.push_back(mtk::admin::msg::sub_command_rd(MTK_SS(splitted_lines[ii].substr(0, 600) << std::endl << " truncated line... " << std::endl)));
                    }
                    else
                        data_list.push_back(mtk::admin::msg::sub_command_rd(MTK_SS(splitted_lines[ii] << std::endl)));
                }
            }
            else
                data_list.push_back(mtk::admin::msg::sub_command_rd(MTK_SS(*it2 << std::endl)));

            ++it2;
            --max_lines_to_respond;
            if(max_lines_to_respond <= 0)
            {
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "admin", MTK_SS("too many lines to respond on  " << command << " truncating"), mtk::alPriorError));
                data_list.push_back(mtk::admin::msg::sub_command_rd(MTK_SS("too many lines in response, truncating...  " << std::endl)));
                break;
            }
        }

        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "admin.command", MTK_SS("from  " << command_msg.request_info.process_info << std::endl <<  "command " << command << std::endl
                                                            << "response first line " << data_list.front().text), mtk::alPriorDebug));
        //  sending multiresponses in asyncronous way
        MTK_SEND_MULTI_RESPONSE(        mtk::admin::msg::res_command,
                                        mtk::admin::msg::sub_command_rd,
                                        mtk::admin::get_url("admin"),
                                        command_msg.request_info,
                                        data_list)
    }

    void admin_status::on_command_received_cli(const mtk::admin::msg::req_command_cli& command_msg)
    {
        on_command_received2(command_msg);
    }
    void admin_status::on_command_received_srv(const mtk::admin::msg::req_command_srv& command_msg)
    {
        on_command_received2(command_msg);
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

    bool  check_and_split_params(const std::string& params, mtk::list<std::string>&  response_lines, int number_of_params, mtk::vector<std::string>& vparams)
    {
        mtk::vector<std::string> temp_vparams = mtk::s_split(mtk::s_trim(params, ' '), " ");
        //  remove empty params
        vparams.clear();
        for(unsigned i=0; i<temp_vparams.size(); ++i)
        {
            std::string param = mtk::s_trim(temp_vparams[i], ' ');
            if(param != "")
                vparams.push_back(param);
        }
        if(vparams.size() != unsigned(number_of_params))
        {
            response_lines.push_back(MTK_SS("invalid number of params. There is needed "  <<  number_of_params  <<  "  params:   "  << params));
            return  false;
        }
        return true;
    }
    void admin_status::command_set_config_property(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string>  vparams;
        if(check_and_split_params(params, response_lines, 2, vparams)  == false)     return;
        std::string  key(vparams[0]);
        std::string  value(vparams[1]);

        try
        {
            config_file.ModifOrCreate(key, value);
            config_file.SaveToFile();
            response_lines.push_back("mofied and saved");
        }
        catch (mtk::Alarm& __alarm__)
        {
            response_lines.push_back(MTK_SS(__alarm__));
            mtk::AlarmMsg(__alarm__);
        }
    }

    void admin_status::command_del_config_property(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
    {
        mtk::vector<std::string>  vparams;
        if(check_and_split_params(params, response_lines, 1, vparams)  == false)     return;
        std::string  key(vparams[0]);

        try
        {
            config_file.Delete(key);
            config_file.SaveToFile();
            response_lines.push_back("deleted");
        }
        catch (mtk::Alarm& __alarm__)
        {
            response_lines.push_back(MTK_SS(__alarm__));
            mtk::AlarmMsg(__alarm__);
        }
    }

    void admin_status::command_ping(const std::string& /*command*/, const std::string& /*param*/, mtk::list<std::string>&  response_lines)
    {
        response_lines.push_back(MTK_SS("pong  " << mtk::dtNowLocal()));
    }

    void admin_status::command_rqclose(const std::string& /*command*/, const std::string& /*param*/, mtk::list<std::string>&  response_lines)
    {
        response_lines.push_back("closing as you demand...");
        __direct_NotifyAlarm(mtk::Alarm(MTK_HERE, "command_rqclose", MTK_SS("Exiting application  requested by command"), mtk::alPriorError, mtk::alTypeUnknown));
        close_application("requested by interactive admin command");
    }

    void admin_status::command_date_time(const std::string& /*command*/, const std::string& /*param*/, mtk::list<std::string>&  response_lines)
    {
        response_lines.push_back(MTK_SS("current_date_time       " << mtk::dtNowLocal()  << std::endl
                                  <<    "current_date_time_utc   " << mtk::dtNowUTC()));
        response_lines.push_back(MTK_SS("current_date_time      non_monotonic   " << mtk::dtNowLocal__non_monotonic()  << std::endl
                                  <<    "current_date_time_utc  non_monotonic    " << mtk::dtNowUTC__non_monotonic()));
        response_lines.push_back(MTK_SS("diference monotonic and non_monotonic   " << mtk::dtNowLocal()  -  mtk::dtNowLocal__non_monotonic()));

    }

    void admin_status::command_set_machine_code(const std::string& /*command*/, const std::string& param, mtk::list<std::string>&  response_lines)
    {
        this->set_config_property("ADMIN.CLIENT.machine_code", mtk::s_trim(param, " \t"));
        response_lines.push_back(MTK_SS("writed machine code... " << this->get_config_mandatory_property("ADMIN.CLIENT.machine_code")));
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

    std::string   admin_status::get_config_mandatory_property(const std::string& path_and_property)
    {
        mtk::Nullable<std::string>  value = config_file.GetValue(path_and_property);
        if(value.HasValue() == false)
            throw mtk::Alarm(MTK_HERE, "admin", MTK_SS("mising mandatory property " << path_and_property), mtk::alPriorError, mtk::alTypeNoPermisions);
        else
            return value.Get();
    }

    mtk::list<std::string>   admin_status::get_config_nodes    (const std::string& path)
    {
        return config_file.GetNodes(path);
    }
    mtk::Nullable<mtk::list<std::string> >    admin_status::get_config_list  (const std::string& path)
    {
        return config_file.GetList(path);
    }

    void         admin_status::set_config_list               (const std::string& path, const mtk::list<std::string>&  list)
    {
        config_file.ModifOrCreateList(path, list);
        config_file.SaveToFile();
    }


    mtk::msg::sub_control_fluct     admin_status::get_control_fluct_info(void)
    {
        return mtk::msg::sub_control_fluct(MTK_SS(process_info.location.broker_code << "." << process_info.location.machine), mtk::dtNowLocal());
    }
    void  admin_status::check_control_fluct(const mtk::msg::sub_control_fluct&  cf)
    {
        MTK_EXEC_MAX_FREC_S(mtk::dtMilliseconds(500))
            check_fluct(cf.key,  cf.datetime);
        MTK_END_EXEC_MAX_FREC
    }

    void  admin_status::check_control_fluct__info_on_times(const mtk::msg::sub_control_fluct&  cf,
                                                                                            const mtk::dtTimeQuantity&  critic_on,
                                                                                            const mtk::dtTimeQuantity&  error_on,
                                                                                            const mtk::dtTimeQuantity&  warning_on)
    {
        MTK_EXEC_MAX_FREC_S(mtk::dtMilliseconds(500))
            static mtk::DateTime  _init (mtk::dtNowLocal());
            check_fluct(cf.key, cf.datetime - _init, critic_on, error_on, warning_on);
        MTK_END_EXEC_MAX_FREC
    }


    void admin_status::set_config_property(const std::string& path, const std::string& property_value)
    {
        config_file.ModifOrCreate(path, property_value);
        config_file.SaveToFile();
    }

    std::string                  admin_status::get_session_id   (void)
    {
        if(role=="server")
        {
            return app_name;
        }
        else if(role=="client")
        {
            std::string session_id = client_login_confirmation.session_id;
            if(session_id=="")
                session_id = "provisional";
            return session_id;
        }
        else
            throw mtk::Alarm(MTK_HERE, "admin", MTK_SS(role << "  request info with invalid role"), mtk::alPriorCritic, mtk::alTypeNoPermisions);
    }

    mtk::msg::sub_request_info   admin_status::get_request_info (void)
    {
        if(role=="server")
        {
            static int counter=0;
            return mtk::msg::sub_request_info (mtk::msg::sub_request_id(get_session_id(), MTK_SS(++counter)), get_process_info());
        }
        else if(role=="client")
        {
            static int contador =1;
            return mtk::msg::sub_request_info(mtk::msg::sub_request_id(get_session_id(), MTK_SS(++contador)), get_process_info());
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


mtk::Signal<>*           get_signal_admin_close(void)
{
    static mtk::Signal<>*  result = new mtk::Signal<>;
    return result;
}

mtk::Signal<>*           get_signal_admin_close_delayed(void)
{
    static mtk::Signal<>*  result = new mtk::Signal<>;
    return result;
}


void init(const std::string& config_file_name, const std::string& app_name,
            const std::string& app_version, const std::string& app_description, const std::string& app_modifications )
{
    admin_status::admin_status_instance = new admin_status();
    admin_status::i()->init(config_file_name, app_name, app_version, app_description, app_modifications);
}





mtk::CountPtr< mtk::mtkqpid_receiver >     get_qpid_receiver(const std::string&  url_for, const mtk::t_qpid_address& address, const mtk::t_qpid_filter& filter)
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


    return mtk::get_from_factory< mtk::mtkqpid_receiver >(mtk::make_tuple(get_url(url_for), address, filter));
}




mtk::CountPtr< mtk::mtkqpid_sender2 >     get_qpid_sender(const std::string&  url_for, const mtk::t_qpid_address& address)
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


    return mtk::get_from_factory< mtk::mtkqpid_sender2 >(mtk::make_tuple(get_url(url_for), address));
}



std::string     get_session_id   (void)
{
    return admin_status::i()->get_session_id();
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


t_qpid_url      get_url             (const std::string& url_for)
{
    mtk::Nullable<std::string> url = admin_status::i()->get_config_file().GetValue(MTK_SS("ADMIN.URLS." << url_for));
    if(url.HasValue()==false)
        throw mtk::Alarm(MTK_HERE, "admin", MTK_SS("'" << url_for  << "'   is an invalid url"), mtk::alPriorCritic);
    else
        return t_qpid_url(url.Get());
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

std::string   get_config_mandatory_property(const std::string& path)
{
    return admin_status::i()->get_config_mandatory_property(path);
}

mtk::list<std::string>     get_config_nodes    (const std::string& path)
{
    return admin_status::i()->get_config_nodes(path);
}

mtk::Nullable<mtk::list<std::string> >      get_config_list  (const std::string& path)
{
    return admin_status::i()->get_config_list(path);
}


void     set_config_list   (const std::string& path, const mtk::list<std::string>&  list)
{
    admin_status::i()->set_config_list(path, list);
}


void set_config_property(const std::string& path, const std::string& property_value)
{
    admin_status::i()->set_config_property(path, property_value);
}


void client_login_ok_confirmation   (const mtk::acs::msg::res_login::IC_session_info& client_login_confirmation)
{
    admin_status::i()->client_login_confirmation = client_login_confirmation;
    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "admin", MTK_SS("registered login ok: " << client_login_confirmation), mtk::alPriorDebug));
}

void client_logout_confirmation     (const std::string& description)
{
    admin_status::i()->client_login_confirmation = mtk::acs::msg::res_login::IC_session_info("", "", "");
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

void  check_control_fluct__info_on_times(const mtk::msg::sub_control_fluct&  cf,
                                                                                            const mtk::dtTimeQuantity&  critic_on,
                                                                                            const mtk::dtTimeQuantity&  error_on,
                                                                                            const mtk::dtTimeQuantity&  warning_on)
{
    return admin_status::i()->check_control_fluct__info_on_times(cf, critic_on, error_on, warning_on);
}



bool   is_production(void)
{
    static std::string   config__is_production = get_config_mandatory_property("ADMIN.production");
    if (config__is_production == "true")
        return true;
    else if (config__is_production == "false")
        return false;
    else
    {
        MTK_EXEC_MAX_FREC_S(mtk::dtSeconds(30))
            AlarmMsg(mtk::Alarm(MTK_HERE, "admin", MTK_SS("invalid value on config  ADMIN.production   "  << config__is_production  << " expected true or false"),
                                                        mtk::alPriorCritic, mtk::alTypeLogicError));
        MTK_END_EXEC_MAX_FREC
        return false;
    }
}




};     //namespace admin {


void check_control_fields_flucts    (const std::string&  key, const mtk::DateTime&  dt)
{
    if(key!= ""   &&  key[0] != '_')
       mtk::admin::check_control_fluct(mtk::msg::sub_control_fluct(key, dt));
}


void AlarmMsg (const Alarm& alarm)
{
    try
    {
        if(admin_status::admin_status_instance!=0   &&  admin_status::i()->full_initialized)
            admin_status::i()->NotifyAlarm(alarm);
        else
        {
            std::cerr << alarm << std::endl;
        }
    }
    catch(...)
    {
        std::cerr << __PRETTY_FUNCTION__ << "(" << __FILE__ << ":" << __LINE__ << ")"  << "exception publishing alarm"  <<  std::endl;
    }
}







void  __internal_admin_nevercall_me____release_on_exit(void)
{
    admin_status::release();
}



std::string  get_cli_srv(void)
{
    return  mtk::admin::get_process_info().cli_srv;
}



};  //namespace mtk {

namespace {
    void  timer_check_auto_close(void)
    {
        if(auto_close_canceled)
        {
            MTK_EXEC_MAX_FREC_S(mtk::dtMinutes(5))
                AlarmMsg(mtk::Alarm(MTK_HERE, "admin", MTK_SS("autoclose:   CANCELED BY COMMAND    "),
                                                            mtk::alPriorWarning, mtk::alTypeUnknown));
            MTK_END_EXEC_MAX_FREC
            return;
        }

        MTK_EXEC_MAX_FREC_S(mtk::dtMinutes(1))
            static  std::string  config_auto_close_time  =  mtk::admin::get_config_mandatory_property("ADMIN.autoclose_time");
            if(config_auto_close_time == "never")
            {
                MTK_EXEC_MAX_FREC_S_A(mtk::dtMinutes(30), A)
                    AlarmMsg(mtk::Alarm(MTK_HERE, "admin", MTK_SS("autoclose:   configured never    "),
                                                                mtk::alPriorWarning, mtk::alTypeUnknown));
                MTK_END_EXEC_MAX_FREC
                return;
            }

            auto  autoclose_converted = mtk::s_TRY_stotq(config_auto_close_time, mtk::dtSeconds(0));
            if(autoclose_converted._1 == false)
            {
                AlarmMsg(mtk::Alarm(MTK_HERE, "admin", MTK_SS("autoclose:   wrong format string   " << config_auto_close_time),
                                                            mtk::alPriorError, mtk::alTypeUnknown));
            }
            static  mtk::DateTime auto_close_on  = mtk::dtToday_0Time() + autoclose_converted._0;


            MTK_EXEC_MAX_FREC_S_A(mtk::dtMinutes(30), A)
                AlarmMsg(mtk::Alarm(MTK_HERE, "admin", MTK_SS("autoclose:  process will be closed at    "  << auto_close_on   <<  "   in "  << (auto_close_on - mtk::dtNowLocal())),
                                                            mtk::alPriorWarning, mtk::alTypeUnknown));
            MTK_END_EXEC_MAX_FREC


            mtk::dtDateTime  now = mtk::dtNowLocal();
            if(now > auto_close_on)
                admin_status::i()->close_delayed(MTK_SS("autoclose   configured to close at   "  << auto_close_on   <<  "   in "  << (auto_close_on - mtk::dtNowLocal())));
            else if(now > (auto_close_on - mtk::dtMinutes(30)))
            {
                MTK_EXEC_MAX_FREC_S_A(mtk::dtMinutes(5), A)
                        AlarmMsg(mtk::Alarm(MTK_HERE, "admin", MTK_SS("autoclose:  process will be closed at    "  << auto_close_on
                                                        <<  "   in "  << (auto_close_on - mtk::dtNowLocal())  << "   you can cancel close with admin.autclose.cancel command"),
                                                                    mtk::alPriorError, mtk::alTypeUnknown));
                MTK_END_EXEC_MAX_FREC
            }
        MTK_END_EXEC_MAX_FREC
    }
    void  timer_check_resynchr_monotonic(void)
    {
        MTK_EXEC_MAX_FREC_S(mtk::dtMinutes(1))
            //const char*   PROPERTY_NAME = "autosyncr_time";
            //static  std::string  config_auto_synchr  =  mtk::admin::get_config_mandatory_property(MTK_SS("ADMIN." <<  PROPERTY_NAME));

            //auto  autosynchr_converted = mtk::s_TRY_stotq(config_auto_synchr, mtk::dtSeconds(0));
            //if(autosynchr_converted._1 == false)
            //    throw mtk::Alarm(MTK_HERE, "admin", MTK_SS(PROPERTY_NAME  <<  ":   wrong format string   " << config_auto_synchr),
            //                                                mtk::alPriorError, mtk::alTypeUnknown);
            //static  mtk::DateTime autosynchr  = mtk::dtToday_0Time() + autosynchr_converted._0;


            static  mtk::DateTime autosynchr  = mtk::dtToday_0Time() + mtk::dtHours(3);
            mtk::dtDateTime  now = mtk::dtNowLocal();
            if(now > autosynchr)
            {
                auto  next_resynchr  =  autosynchr + mtk::dtDays(1);
                AlarmMsg(mtk::Alarm(MTK_HERE, "admin", MTK_SS("calling resynchr,  next resynchr...  "  <<  next_resynchr), mtk::alPriorWarning, mtk::alTypeUnknown));
                mtk::dtResynchr_monotonic();
                autosynchr  = next_resynchr;
            }
        MTK_END_EXEC_MAX_FREC
    }

    void command_autoclose_show         (const std::string& /*command*/, const std::string& param,  mtk::list<std::string>&  response_lines)
    {
        if(param.size() != 0)
        {
            response_lines.push_back("no param requeried");
            response_lines.push_back("command ingnored");
            return;
        }
        response_lines.push_back(mtk::admin::get_config_mandatory_property("ADMIN.autoclose_time"));
        if(auto_close_canceled)
            response_lines.push_back("autoclose has been DEACTIVATED, to reactivate use auto_close_reactivate command");
    }

    void command_autoclose_cancel       (const std::string& /*command*/, const std::string& param,  mtk::list<std::string>&  response_lines)
    {
        if(param.size() != 0)
        {
            response_lines.push_back("no param requeried");
            response_lines.push_back("command ingnored");
            return;
        }
        auto_close_canceled = true;
        if(auto_close_canceled)
            response_lines.push_back("autoclose has been DEACTIVATED, to reactivate use auto_close_reactivate command");
        else
            response_lines.push_back("autoclose is ACTIVE, to reactivate use auto_close_reactivate command");
    }

    void command_autoclose_reactivate   (const std::string& /*command*/, const std::string& param,  mtk::list<std::string>&  response_lines)
    {
        if(param.size() != 0)
        {
            response_lines.push_back("no param requeried");
            response_lines.push_back("command ingnored");
            return;
        }
        auto_close_canceled = false;
        if(auto_close_canceled)
            response_lines.push_back("autoclose has been DEACTIVATED, to reactivate use auto_close_reactivate command");
        else
            response_lines.push_back("autoclose is ACTIVE, to reactivate use auto_close_reactivate command");
    }

    void command_resynchr_monotonic     (const std::string& /*command*/, const std::string& /*param*/,  mtk::list<std::string>&  response_lines)
    {
        response_lines.push_back(MTK_SS("date time before synchr... "  << mtk::dtNowLocal()));
        mtk::dtResynchr_monotonic();
        response_lines.push_back(MTK_SS("date time after synchr... "  << mtk::dtNowLocal()));
    }

};
