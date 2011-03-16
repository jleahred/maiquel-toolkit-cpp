#include <iostream>

#include "components/admin/admin.h"
#include "components/admin/msg_admin.h"
#include "support/call_later.h"
#include "components/request_response.hpp"
#include "components/gen/msg_tree_server.h"
#include "support/configfile.h"



namespace
{
    
    const char*   APP_NAME          = "GEN_TREESERVER";
    const char*   APP_VER           = "0.1";
    const char*   APP_DESCRIPTION   = "This process will send, the markets and groups.\n"
                                      "It also check the permisions\n"
                                      "It doesn't have the full information, there are others specific THREESERVERS cooperating.";
}




void on_request_tree_received(const mtk::gen::msg::tree_request_items& tree_request);
mtk::CountPtr< mtk::qpid_session > cli_session;

mtk::CountPtr<mtk::ConfigFile>   data_file;



int main(int argc, char ** argv)
{
    mtk::gen::msg::tree_request_items(mtk::admin::get_request_info(), "ROOT");
    
    try
    {
        if(argc==1)
            mtk::admin::init("./config.cfg", APP_NAME, APP_VER, APP_DESCRIPTION);
        else
            mtk::admin::init(argv[1], APP_NAME, APP_VER, APP_DESCRIPTION);

        cli_session =  mtk::admin::get_qpid_session("client", "CLITESTING");
        
        std::string dataf = mtk::admin::get_config_property("MISC.data").Get();
        data_file = mtk::make_cptr(new mtk::ConfigFile(dataf));
    
        //  suscription to request
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::gen::msg::tree_request_items> >    hqpid_tree_request;
        MTK_QPID_RECEIVER_CONNECT_F(
                                hqpid_tree_request,
                                mtk::admin::get_url("client"),
                                "CLITESTING",
                                mtk::gen::msg::tree_request_items::get_in_subject("*"),     //  from anyone
                                mtk::gen::msg::tree_request_items,
                                on_request_tree_received)
        
    
        mtk::start_timer_wait_till_end();
        

        cli_session = mtk::CountPtr< mtk::qpid_session > ();
        data_file = mtk::CountPtr<mtk::ConfigFile>   ();
        std::cout << "FIN..... " << std::endl;
        #include "support/release_on_exit.hpp"
        return 0;
    }
    MTK_CATCH_CALLFUNCION (std::cout<< , "main", "nothing more")

    std::cout << "MAL..... " << std::endl;
    #include "support/release_on_exit.hpp"
    return -1;

}
 

void on_request_tree_received(const mtk::gen::msg::tree_request_items& tree_request)
{
    mtk::list<mtk::gen::msg::sub_tree_item>  data_list;
    
    mtk::list<std::string>  nodes = data_file->GetNodes(tree_request.branch);
    
    mtk::list<std::string>::iterator it = nodes.begin();
    while(it != nodes.end())
    {
        std::string name = *it;
        std::string description = data_file->GetValue(MTK_SS(tree_request.branch<<"."<<*it<<".description")).Get();
        std::string market_code = data_file->GetValue(MTK_SS(tree_request.branch<<"."<<*it<<".market")).Get();
        std::string full_branch = MTK_SS(tree_request.branch << "." <<*it);
        if(market_code != "")
        {
            mtk::msg::sub_product_code pc ( mtk::msg::sub_sys_product_code(mtk::msg::sub_single_product_code(market_code, *it), description), 
                                            mtk::nullable<mtk::msg::sub_adic_product_code> ());
            data_list.push_back(mtk::gen::msg::sub_tree_item(full_branch, description, mtk::make_nullable(pc)));
        }
        else
            data_list.push_back(mtk::gen::msg::sub_tree_item(full_branch, description, mtk::nullable<mtk::msg::sub_product_code>()));
        
        ++it;
    }
    
    //  sending multiresponses in asyncronous way
    MTK_SEND_MULTI_RESPONSE(        mtk::gen::msg::tree_response_items,
                                    mtk::gen::msg::sub_tree_item, 
                                    cli_session,
                                    tree_request.request_info,
                                    data_list)
}
