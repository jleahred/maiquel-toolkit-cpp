#include <iostream>

#include "components/admin/admin.h"
#include "components/admin/msg_admin.h"
#include "support/call_later.h"
#include "components/request_response.hpp"




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

    mtk::msg::sub_request_r request_code(mtk::admin::get_request_code());
    /*static*/ mtk::CountPtr<mtk::qpid_session>  qpid_session = mtk::admin::get_qpid_session("admin", "ADMCLI");


    //  subscription to multiresponse
    MTK_RECEIVE_MULTI_RESPONSE_F(   mtk::admin::msg::command_response, 
                                    mtk::admin::msg::sub_command_rd, 
                                    qpid_session,
                                    mtk::admin::msg::command_response::get_in_subject(request_code.request_code),
                                    on_command_response)

    //  sending hello command
    mtk::admin::msg::command command_request_msg(   request_code, 
                                                    mtk::admin::msg::sub_admin_header(  mtk::admin::get_location(), 
                                                                                        mtk::admin::get_machine(), 
                                                                                        mtk::dtNowLocal()), 
                                                                                        command);
    mtk::send_message(qpid_session, command_request_msg);

}


void command_hello(const std::string& /*command*/, const std::string& /*param*/, const std::string& request_code)
{
    /*static*/ mtk::CountPtr<mtk::qpid_session>  qpid_session = mtk::admin::get_qpid_session("admin", "ADMCLI");
    //  preparing sending multiresponses in asyncronous way
    //  filling response list
    mtk::list<mtk::admin::msg::sub_command_rd>  data_list;
    data_list.push_back(mtk::admin::msg::sub_command_rd(
                                mtk::admin::msg::sub_admin_header(mtk::admin::get_location(), mtk::admin::get_machine(), mtk::dtNowLocal()),
                                "good bye"));
                                
    //  sending multiresponses in asyncronous way
    MTK_SEND_MULTI_RESPONSE(        mtk::admin::msg::command_response, 
                                    mtk::admin::msg::sub_command_rd, 
                                    qpid_session,
                                    mtk::msg::sub_request_r(request_code),
                                    data_list)
}



int main(int /*argc*/, char ** /*argv*/)
{
    try
    {
        mtk::admin::init("./config.cfg");
        
    
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::admin::msg::command>      >   hqpid_response;

        MTK_CALL_LATER1S_F(mtk::dtSeconds(20), 0, stop);
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
