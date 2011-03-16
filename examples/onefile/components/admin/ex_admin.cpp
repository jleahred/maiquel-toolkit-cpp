#include <iostream>

#include "components/admin/admin.h"
#include "components/admin/msg_admin.h"
#include "support/call_later.h"
#include "components/request_response.hpp"



namespace
{

    const char*   APP_NAME          = "ex_admin";
    const char*   APP_VER           = "0.1";
    const char*   APP_DESCRIPTION   = "small example of admin component";
}




void stop(const int&)
{
    mtk::stop_timer();
}

void on_command_response (const mtk::list<mtk::admin::msg::command_response>& responses)        //  <1>
{
    mtk::list<mtk::admin::msg::command_response>::const_iterator it = responses.begin();
    while(it != responses.end())
    {
        std::cout << *it << std::endl;
        ++it;
    }
}


void request_command(const std::string& command)
{

    mtk::msg::sub_request_info request_info(mtk::admin::get_request_info());
    /*static*/ mtk::CountPtr<mtk::qpid_session>  qpid_session = mtk::admin::get_qpid_session("admin", "ADMCLI");


    //  subscription to multiresponse
    MTK_RECEIVE_MULTI_RESPONSE_F(   mtk::admin::msg::command_response, 
                                    mtk::admin::msg::sub_command_rd, 
                                    qpid_session,
                                    mtk::admin::msg::command_response::get_in_subject(request_info.process_location.process_uuid, request_info.req_id.req_code),
                                    on_command_response)

    //  sending hello command
    mtk::admin::msg::command command_request_msg( request_info, mtk::admin::get_process_location(), command);
    mtk::send_message(qpid_session, command_request_msg);

}


void command_hello(const std::string& /*command*/, const std::string& /*param*/, mtk::list<std::string>& response_lines)
{
    response_lines.push_back("good by");
}




int main(int /*argc*/, char ** /*argv*/)
{
    try
    {
        mtk::admin::init("./config.cfg", APP_NAME, APP_VER, APP_DESCRIPTION);
        
    
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::admin::msg::command>      >   hqpid_response;

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
