#include <iostream>

#include "components/admin/admin.h"
#include "components/admin/msg_admin.h"
#include "support/call_later.h"
#include "components/request_response.hpp"
#include "components/gen/msg_tree_server.h"
#include "support/configfile.h"
#include "components/prices/msg_prices.h"
#include "components/prices/msg_ps_prices.h"
#include "components/acs/serv/acs_synchr.h"

#include "db/tree_db.h"


namespace
{

    const char*   APP_NAME          = "GEN_TREESERVER2";
    const char*   APP_VER           = "2012-05-28";
    const char*   APP_DESCRIPTION   = "This process will send, the markets and groups.\n"
                                      "It also check the permisions\n"
                                      "It doesn't have the full information, there are others specific THREESERVERS cooperating.";

    const char*   APP_MODIFICATIONS =   "           2011-03-16     first version\n"
                                        "           2011-08-10     working with grants and bypass (cfg on separated yaml file)\n"
                                        "           2012-05-16     updated grants file and policy\n"
                                        "           2012-05-28     commands to colapse branch and load struct file\n"
                                        ;



    void command_colapse_branch(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);


    void register_global_commands (void)
    {
        mtk::admin::register_command("ts",  "colapse_branch",  "send a message to clients to colapse a branch (ROOT to full colapse)",  true)->connect(command_colapse_branch);
    }


    MTK_ADMIN_REGISTER_GLOBAL_COMMANDS(register_global_commands)
}




void on_request_tree_received(const mtk::gen::msg::req_tree_items& tree_request);
void on_request_prodinf_received(const mtk::prices::msg::req_product_info&  pi_request);





int main(int argc, char ** argv)
{
    try
    {
        if(argc==1)
            mtk::admin::init("./config.cfg", APP_NAME, APP_VER, APP_DESCRIPTION, APP_MODIFICATIONS);
        else
            mtk::admin::init(argv[1], APP_NAME, APP_VER, APP_DESCRIPTION, APP_MODIFICATIONS);

        tree_server2::db::init(     mtk::admin::get_config_property("MISC.data_tree").Get(),
                                    mtk::admin::get_config_property("MISC.data_grants").Get());
        mtk::acs_server::synchr::init();



        //  suscription to request tree item
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::gen::msg::req_tree_items> >    hqpid_tree_request;
        MTK_QPID_RECEIVER_CONNECT_F(
                                hqpid_tree_request,
                                mtk::admin::get_url("client"),
                                mtk::gen::msg::req_tree_items::get_in_subject("*"),     //  from anyone
                                mtk::gen::msg::req_tree_items,
                                on_request_tree_received)

        mtk::start_timer_wait_till_end();


        tree_server2::db::save();
        std::cout << "FIN..... " << std::endl;
        #include "support/release_on_exit.hpp"
        return 0;
    }
    MTK_CATCH_CALLFUNCION (std::cout<< , "main", "nothing more")

    std::cout << "MAL..... " << std::endl;
    #include "support/release_on_exit.hpp"
    return -1;

}



void on_request_tree_received(const mtk::gen::msg::req_tree_items& tree_request)
{
    mtk::list<mtk::gen::msg::sub_tree_item>  data_list = tree_server2::db::get_items_for_branch__ifso(tree_request);
    //  sending multiresponses in asyncronous way
    MTK_SEND_MULTI_RESPONSE(        mtk::gen::msg::res_tree_items,
                                    mtk::gen::msg::sub_tree_item,
                                    mtk::admin::get_url("client"),
                                    tree_request.request_info,
                                    data_list)
}




namespace {

void command_colapse_branch(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
{
    mtk::gen::msg::pub_tree_colapse_branch  msg  (mtk::admin::get_process_info().location.broker_code, mtk::s_trim(params, ' '));
    mtk_send_message("client", msg);

    response_lines.push_back(MTK_SS("colapse branch for " <<  mtk::s_trim(params, ' ')  << " sent"));
}


};      //  namespace {
