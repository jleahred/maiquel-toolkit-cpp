#include <iostream>

#include "components/admin/admin.h"
#include "components/admin/msg_admin.h"
#include "support/call_later.h"
#include "components/request_response.hpp"



namespace
{

    const char*   APP_NAME          = "ex_request_response";
    const char*   APP_VER           = "0.1";
    const char*   APP_DESCRIPTION   = "Example file working with request response pattern";
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



void init_request_response(const int&)
{
    mtk::msg::sub_request_info request_info(mtk::admin::get_request_info());
    /*static*/ mtk::CountPtr<mtk::qpid_session>  qpid_session = mtk::admin::get_qpid_session("admin", "testing");

    //  subscription to multiresponse       <2>
    MTK_RECEIVE_MULTI_RESPONSE_F(   mtk::admin::msg::command_response, 
                                    mtk::admin::msg::sub_command_rd, 
                                    qpid_session,
                                    mtk::admin::msg::command_response::get_in_subject(request_info.process_location.location),
                                    on_command_response)



    //  preparing sending multiresponses in asyncronous way       <3>
    //  filling response list
    mtk::list<mtk::admin::msg::sub_command_rd>  data_list;
    for(int i=0; i < 100; ++i)
        data_list.push_back(mtk::admin::msg::sub_command_rd(MTK_SS("response line  "  <<  i << std::endl)));

    //  sending multiresponses in asyncronous way           <4>
    MTK_SEND_MULTI_RESPONSE(        mtk::admin::msg::command_response, 
                                    mtk::admin::msg::sub_command_rd, 
                                    qpid_session,
                                    request_info,
                                    data_list)
}



int main(int /*argc*/, char ** /*argv*/)
{
    try
    {
        mtk::admin::init("./config.cfg", APP_NAME, APP_VER, APP_DESCRIPTION);
    
    
    
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::admin::msg::command>      >   hqpid_response;

        MTK_CALL_LATER1S_F(mtk::dtSeconds(7), 0, stop);
        MTK_CALL_LATER1S_F(mtk::dtSeconds(1), 0, init_request_response);
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
