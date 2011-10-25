#include <iostream>

#include "components/admin/admin.h"
#include "components/admin/msg_admin.h"
#include "support/call_later.h"
#include "components/request_response.hpp"



namespace
{

    const char*   APP_NAME          = "ex_admin";
    const char*   APP_VER           = "2011-03-16";
    const char*   APP_DESCRIPTION   = "small example of admin component";
    const char*   APP_MODIFICATIONS = "example, no modifications info";




    //  testing registering static commands for this file

    void command_version(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
    {
        response_lines.push_back(MTK_SS(__FILE__ << ":  " << APP_VER));
    }

    void command_modifications  (const std::string& /*command*/, const std::string& /*param*/,  mtk::list<std::string>&  response_lines)
    {
        response_lines.push_back(__FILE__);
        response_lines.push_back(".......................................");
        response_lines.push_back(APP_MODIFICATIONS);
    }


    void register_global_commands (void)
    {
        mtk::admin::register_command("__GLOBAL__",  "ver",   "")->connect(command_version);
        mtk::admin::register_command("__GLOBAL__",  "modifs",   "")->connect(command_modifications);
    }


    MTK_ADMIN_REGISTER_GLOBAL_COMMANDS(register_global_commands)
}




void stop(const int&)
{
    mtk::stop_timer();
}

void on_command_response (const mtk::list<mtk::admin::msg::res_command>& responses)        //  <1>
{
    mtk::list<mtk::admin::msg::res_command>::const_iterator it = responses.begin();
    while(it != responses.end())
    {
        std::cout << *it << std::endl;
        ++it;
    }
}


void request_command(const std::string& command)
{

    mtk::msg::sub_request_info request_info(mtk::admin::get_request_info());


    //  subscription to multiresponse
    MTK_RECEIVE_MULTI_RESPONSE_F(   mtk::admin::msg::res_command,
                                    mtk::admin::msg::sub_command_rd,
                                    mtk::admin::get_url("client"),
                                    mtk::admin::msg::res_command::get_in_subject(request_info.process_info.process_uuid, request_info.req_id.req_code),
                                    on_command_response,
				    "ex_admin_req_res")

    //  sending hello command
    mtk::admin::msg::req_command   command_request_msg  (request_info, mtk::admin::get_process_info(), command);
    mtk_send_message("client", command_request_msg);

}


void command_hello(const std::string& /*command*/, const std::string& /*param*/, mtk::list<std::string>& response_lines)
{
    response_lines.push_back("good by");
}




int main(int /*argc*/, char ** /*argv*/)
{
    try
    {
        mtk::admin::init("./config.cfg", APP_NAME, APP_VER, APP_DESCRIPTION, APP_MODIFICATIONS);


        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::admin::msg::req_command>      >   hqpid_response;

        MTK_CALL_LATER1S_F(mtk::dtSeconds(10), 0, stop);
        MTK_CALL_LATER1S_F(mtk::dtSeconds(1),  std::string("help"),  request_command);
        MTK_CALL_LATER1S_F(mtk::dtSeconds(3),  std::string("hello"), request_command);


        //MTK_CONNECT_THIS(*mtk::admin::register_command("testing", "hello", ""),   command_hello)  //if you are connecting to this class
        mtk::admin::register_command("testing", "hello", "")->connect(command_hello);               //  conencting to a function


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
