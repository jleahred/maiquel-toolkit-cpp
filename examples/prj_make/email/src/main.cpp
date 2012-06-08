#include <iostream>

#include "components/admin/admin.h"
#include "mtk_qpid/mtk_qpid.h"
#include "components/gen/msg_email.h"
#include "support/exec_command.h"



namespace
{

    const char*   APP_NAME          = "MAIL";
    const char*   APP_VER           = "2012-06-07";
    const char*   APP_DESCRIPTION   = "Send emails\n"
                                      "";

    const char*   APP_MODIFICATIONS = "           2012-06-07     first version\n";



    void command_test_email(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);

    void register_global_commands (void)
    {
        mtk::admin::register_command("email",  "test",       "<destination>  it will send a qpid message with email request to test")->connect(command_test_email);
    }

    MTK_ADMIN_REGISTER_GLOBAL_COMMANDS(register_global_commands)


    void  suscribe_email_request(void);
    void  timer_check_emails(void);

}






int main(int argc, char ** argv)
{
    try
    {
        if(argc==1)
            mtk::admin::init("./config.cfg", APP_NAME, APP_VER, APP_DESCRIPTION, APP_MODIFICATIONS);
        else
            mtk::admin::init(argv[1], APP_NAME, APP_VER, APP_DESCRIPTION, APP_MODIFICATIONS);


        suscribe_email_request();
        MTK_TIMER_1SF(timer_check_emails);


        mtk::start_timer_wait_till_end();


        std::cout << "FIN..... " << std::endl;
        #include "support/release_on_exit.hpp"
        return 0;
    }
    MTK_CATCH_CALLFUNCION (std::cout<< , "main", "nothing more")

    std::cout << "MAL..... " << std::endl;
    #include "support/release_on_exit.hpp"
    return -1;

}







namespace {


mtk::list<mtk::gen::msg::pub_email>&   get_pending_emails(void)
{
    static  mtk::list<mtk::gen::msg::pub_email>  result;
    return  result;
}




void  on_email_request(const  mtk::gen::msg::pub_email&  msg)
{
    if(get_pending_emails().size() > 500)
    {
        MTK_EXEC_MAX_FREC_S(mtk::dtMinutes(1))
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "email", MTK_SS("Too many emails queued (" << get_pending_emails().size() << ") ignoring..."), mtk::alPriorError));
        MTK_END_EXEC_MAX_FREC
        return;
    }
    get_pending_emails().push_back(msg);
}


void  suscribe_email_request(void)
{
    static  mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::gen::msg::pub_email> >               handle;
    MTK_QPID_RECEIVER_CONNECT_F(
                            handle,
                            mtk::admin::get_url("server"),
                            mtk::gen::msg::pub_email::get_in_subject(),
                            mtk::gen::msg::pub_email,
                            on_email_request)
}


void command_test_email(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
{
    if(params == "")
    {
        response_lines.push_back("You have to specify the address destination");
        return;
    }

    mtk::gen::msg::pub_email  pub_email(params, "Testing... hello there", "Hello, bird witout tail.\n see you.\n");

    mtk_send_message("server", pub_email);

    response_lines.push_back(MTK_SS("message sent to... " << params));
}



void  terminated_command (bool ok, const std::string&  desc, const mtk::DateTime& started, const mtk::dtTimeQuantity& time);


mtk::exec_command&  get_command_send_email(void)
{
    static  mtk::exec_command*       ec = 0;
    if(ec== 0)
    {
        ec = new mtk::exec_command{mtk::dtSeconds{10}};
        ec->set_command("./bin/send_email.py");
        ec->signal_terminated.connect(terminated_command);
    }

    return *ec;
}


std::string  get_lines_as_string(const mtk::list<std::string>&  lines)
{
    std::string  result;

    for(auto it = lines.begin(); it!= lines.end(); ++it)
        result += MTK_SS(*it  <<  std::endl);
    return result;
}


void  terminated_command (bool ok, const std::string&  desc, const mtk::DateTime& started, const mtk::dtTimeQuantity& time)
{
    if(ok == false)
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "email", MTK_SS(desc << " End sending email...  " << started << "  " << time  <<  " " << get_command_send_email().get_all_last_lines_as_string()), mtk::alPriorError));
    else
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "email", MTK_SS(desc << " End sending email...  " << started << "  " << time  <<  " " << get_command_send_email().get_all_last_lines_as_string()), mtk::alPriorDebug));
}





void  timer_check_emails(void)
{
    MTK_EXEC_MAX_FREC_S(mtk::dtSeconds(4))
        if(get_command_send_email().is_running() == false  &&  get_pending_emails().size() > 0)
        {
            mtk::gen::msg::pub_email  email  =  get_pending_emails().front();
            get_pending_emails().pop_front();

            std::string  email_info = MTK_SS(
                   "to_addr = '"            <<  email.eto       << "'"  <<  std::endl
                << "subj = '"               <<  email.esubject  <<"'"   <<  std::endl
                << "message_text = \"\"\""  <<  email.emessage  << "\"\"\"" <<  std::endl
                << std::endl << ".END."  << std::endl
            );



            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "email", MTK_SS("Sending email... " << email_info), mtk::alPriorWarning));
            get_command_send_email().run();
            get_command_send_email().write(email_info);
        }
    MTK_END_EXEC_MAX_FREC
}


};  //  end namespace
