#include "check_request.h"


#include <fstream>
#include "components/admin/admin.h"
#include "msg_config_data.h"
#include "components/prices/msg_ps_prices.h"



namespace {
mtk::CountPtr<mtk::map<std::string, emarket::sub_product_config> >   get_map_product_config(void)
{
    static auto result = mtk::make_cptr(new mtk::map<std::string, emarket::sub_product_config>);
    return result;
}
}



void __load_config(void)
{
//        {         generate yaml data file
//                mtk::list<emarket::sub_product_config>  list_product_config;
//                list_product_config.push_back(emarket::sub_product_config("PRD1", "PRODUCT 1", "GRP1", "GROUP 1", mtk::fnExt(mtk::fnDec(2), mtk::fnInc(2))));
//                list_product_config.push_back(emarket::sub_product_config("PRD2", "PRODUCT 2", "GRP1", "GROUP 1", mtk::fnExt(mtk::fnDec(0), mtk::fnInc(1))));
//                list_product_config.push_back(emarket::sub_product_config("PRD3", "PRODUCT 3", "GRP3", "GROUP 3", mtk::fnExt(mtk::fnDec(2), mtk::fnInc(5))));
//                std::ofstream file_save;
//                file_save.open ("config_data.yaml");
//
//
//                try
//                {
//                    YAML::Emitter out;
//                    out  <<  YAML::BeginMap  <<  YAML::Key << "product_config" << YAML::Value;
//                        out << list_product_config;
//                    out  <<  YAML::EndMap;
//                        
//                    file_save << out.c_str();
//                    file_save.close();
//                }
//                MTK_CATCH_CALLFUNCION(mtk::AlarmMsg, "...", "error saving data")
//        }
    
    
        //std::ifstream file("../data/config_data.yaml");
        //std::ifstream file("config_data.yaml");
        std::string   file_name = mtk::admin::get_config_property("MISC.markets_conf").Get();
        std::ifstream file(file_name.c_str());
        
        try
        {
            YAML::Parser parser(file);

            YAML::Node doc;
            parser.GetNextDocument(doc);
            std::string config_version;
            
            
            mtk::list<emarket::sub_product_config>  list_product_config_temp;
            doc["product_config"] >>  list_product_config_temp;
            (*get_map_product_config()) = get_map_from_list_with_key(list_product_config_temp);
            
            
            file.close();
        }
        MTK_CATCH_CALLFUNCION(mtk::AlarmMsg, "accmgr_db", "error loading db")
}



check_request::check_request()
{
}

check_request::~check_request()
{
}


void  check_request::init(void)
{
    __load_config();
    //mtk::CountPtr<mtk::map<std::string, emarket::sub_product_config> >   get_map_product_config(void)
    for(auto it=get_map_product_config()->begin(); it!=get_map_product_config()->end(); ++it)
        sig_add_product.emit(it->second);

    static  std::string   oms_from = mtk::admin::get_config_property("OMS_CHAIN.from").Get();
    
    std::cout << "connecting oms_RQ_NW_LS... ";
    MTK_QPID_RECEIVER_CONNECT_THIS(
                            hqpid_rqnwls,
                            mtk::admin::get_url("server"),
                            "SRVTESTING",
                            mtk::trd::msg::oms_RQ_NW_LS::get_in_subject("MARKET", "*", oms_from),
                            mtk::trd::msg::oms_RQ_NW_LS,
                            oms_RQ_NW_LS)
    std::cout << " ok" << std::endl;
    
    std::cout << "connecting oms_RQ_MD_LS... ";
    MTK_QPID_RECEIVER_CONNECT_THIS(
                            hqpid_rqmdls,
                            mtk::admin::get_url("server"),
                            "SRVTESTING",
                            mtk::trd::msg::oms_RQ_MD_LS::get_in_subject("MARKET", "*", oms_from),
                            mtk::trd::msg::oms_RQ_MD_LS,
                            oms_RQ_MD_LS)
    std::cout << " ok" << std::endl;

    std::cout << "connecting oms_RQ_CC_LS... ";
    MTK_QPID_RECEIVER_CONNECT_THIS(
                            hqpid_rqccls,
                            mtk::admin::get_url("server"),
                            "SRVTESTING",
                            mtk::trd::msg::oms_RQ_CC_LS::get_in_subject("MARKET", "*", oms_from),
                            mtk::trd::msg::oms_RQ_CC_LS,
                            oms_RQ_CC_LS)
    std::cout << " ok" << std::endl;
    
    mtk::prices::msg::ps_pub_prod_info_mtk_ready__from_publisher   
                    ps_pub_prod_info_mtk_ready__from_publisher  (mtk::prices::msg::ps_pub_prod_info_mtk_ready("MARKET"));
    mtk::send_message(mtk::admin::get_qpid_session("server", "SRVTESTING"), ps_pub_prod_info_mtk_ready__from_publisher);
}



std::string check_request_pos (const emarket::sub_product_config&  pc, const mtk::trd::msg::sub_position_ls&   pos)
{
    std::string  result;
    if(pos.price.GetExt() !=  pc.price_fnext)
        result += " extended on price doesn't match";
    if(pos.quantity.GetExt() !=  mtk::fnExt(mtk::fnDec(0), mtk::fnInc(1)))
        result += " extended on quantity doesn't match";
    return result;
}



//std::string verif_is_valid_request(const mtk::trd::msg::oms_RQ_NW_LS& rq)
template<typename  RQ_TYPE>
std::string verif_is_valid_request(const RQ_TYPE& rq)
{
    std::string result;
    if(rq.reject_description != "")
        result += rq.reject_description;
    //  check product name
    auto itpc = get_map_product_config()->find(rq.invariant.product_code.product);
    if(itpc == get_map_product_config()->end())
        result += MTK_SS("product code " << rq.invariant.product_code.product << " not configured");
    result += check_request_pos(itpc->second, rq.request_pos);
    
    return result;
}

void check_request::oms_RQ_CC_LS(const mtk::trd::msg::oms_RQ_CC_LS& rq)
{
    std::cout << mtk::dtNowLocal() << "  received... " << __FUNCTION__ << std::endl;
    std::string reject_reason = verif_is_valid_request(rq);
    sig_oms_rq_cc.emit(mtk::trd::msg::oms_RQ_CC_LS(rq, reject_reason, ""));
}

void check_request::oms_RQ_MD_LS(const mtk::trd::msg::oms_RQ_MD_LS& rq)
{
    std::cout << mtk::dtNowLocal() << "  received... " << __FUNCTION__ << std::endl;
    std::string reject_reason = verif_is_valid_request(rq);
    sig_oms_rq_md.emit(mtk::trd::msg::oms_RQ_MD_LS(rq, reject_reason, ""));
}

void check_request::oms_RQ_NW_LS(const mtk::trd::msg::oms_RQ_NW_LS& rq)
{
    std::cout << mtk::dtNowLocal() << "  received... " << __FUNCTION__ << std::endl;
    std::string reject_reason = verif_is_valid_request(rq);
    sig_oms_rq_nw.emit(mtk::trd::msg::oms_RQ_NW_LS(rq, reject_reason, ""));
}
