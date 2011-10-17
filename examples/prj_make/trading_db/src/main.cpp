#include <iostream>

#include "components/trading/msg_trd_cli_ls.h"
#include "components/trading/msg_trd_cli_mk.h"
#include "components/admin/admin.h"
#include "components/admin/msg_admin.h"
#include "support/call_later.h"
#include "components/request_response.hpp"
#include "components/fb/fbinsert.h"
#include "support/nullable.hpp"



namespace
{

    const char*   APP_NAME          = "ADM_TRADING_DB";
    const char*   APP_VER           = "2011-06-13";
    const char*   APP_DESCRIPTION   = "This process save alarms on database\n"
                                      "";

    const char*   APP_MODIFICATIONS = "           2011-06-13     first version\n";

}




struct  record_info
{
        mtk::nullable<mtk::DateTime>    REC_TIME;
        mtk::nullable<mtk::DateTime>    SENT_TIME;
        mtk::nullable<std::string>      MARKET_ORDER_ID;
        mtk::nullable<std::string>      OID_SESSION_ID;
        mtk::nullable<std::string>      OID_RQ_CODE;
        mtk::nullable<std::string>      PC_MARKET;
        mtk::nullable<std::string>      PC_PRODUCT_CODE;
        mtk::nullable<std::string>      SIDE;
        mtk::nullable<std::string>      ACCOUNT_CC;
        mtk::nullable<std::string>      ACCOUNT_NAME;
        mtk::nullable<std::string>      RID_SESSION_ID;
        mtk::nullable<std::string>      RID_RQ_CODE;
        mtk::nullable<std::string>      CLI_REF;
        mtk::nullable<std::string>      CFLUCT_KEY;
        mtk::nullable<mtk::DateTime>    CFLUCT_DATE_TIME;
        mtk::nullable<std::string>      ORDER_TYPE;
        mtk::nullable<int>              RQ_POS_PRICE;
        mtk::nullable<int>              RQ_POS_PRICE_DEC;
        mtk::nullable<int>              RQ_POS_PRICE_INC;
        mtk::nullable<int>              RQ_POS_QUANTITY;
        mtk::nullable<int>              RQ_POS_QUANTITY_DEC;
        mtk::nullable<int>              RQ_POS_QUANTITY_INC;
        mtk::nullable<int>              CF_POS_PRICE;
        mtk::nullable<int>              CF_POS_PRICE_DEC;
        mtk::nullable<int>              CF_POS_PRICE_INC;
        mtk::nullable<int>              CF_POS_QUANTITY;
        mtk::nullable<int>              CF_POS_QUANTITY_DEC;
        mtk::nullable<int>              CF_POS_QUANTITY_INC;
        mtk::nullable<std::string>      EXCF_EXEC_ID;
        mtk::nullable<int>              EXCF_EXEC_PRICE;
        mtk::nullable<int>              EXCF_EXEC_PRICE_DEC;
        mtk::nullable<int>              EXCF_EXEC_PRICE_INC;
        mtk::nullable<int>              EXCF_EXEC_QUANTITY;
        mtk::nullable<int>              EXCF_EXEC_QUANTITY_DEC;
        mtk::nullable<int>              EXCF_EXEC_QUANTITY_INC;
        mtk::nullable<double>           TEX_SUM_PRICE_QTY;
        mtk::nullable<int>              TEX_ACC_QTY;
        mtk::nullable<int>              TEX_ACC_QTY_DEC;
        mtk::nullable<int>              TEX_ACC_QTY_INC;
        mtk::nullable<int>              TEX_REM_QTY;
        mtk::nullable<int>              TEX_REM_QTY_DEC;
        mtk::nullable<int>              TEX_REM_QTY_INC;
        mtk::nullable<std::string>      REJECT_DESCRIPTION;
        mtk::nullable<std::string>      REMARKS;
};


void insert_record (const record_info&  record)
{
    static mtk::fbInsert fbi("DB_TRADING",  "INSERT INTO TRADING (REC_TIME, SENT_TIME, MARKET_ORDER_ID, OID_SESSION_ID, OID_RQ_CODE, "
                                            "PC_MARKET, PC_PRODUCT_CODE, SIDE, ACCOUNT_CC, ACCOUNT_NAME, RID_SESSION_ID, RID_RQ_CODE, "
                                            "CLI_REF, CFLUCT_KEY, CFLUCT_DATE_TIME, ORDER_TYPE, RQ_POS_PRICE, RQ_POS_PRICE_DEC, RQ_POS_PRICE_INC, "
                                            "RQ_POS_QUANTITY, RQ_POS_QUANTITY_DEC, RQ_POS_QUANTITY_INC, CF_POS_PRICE, CF_POS_PRICE_DEC, "
                                            "CF_POS_PRICE_INC, CF_POS_QUANTITY, CF_POS_QUANTITY_DEC, CF_POS_QUANTITY_INC, EXCF_EXEC_ID, "
                                            "EXCF_POS_PRICE, EXCF_POS_PRICE_DEC, EXCF_POS_PRICE_INC, EXCF_POS_QUANTITY, EXCF_POS_QUANTITY_DEC, "
                                            "EXCF_POS_QUANTITY_INC, TEX_SUM_PRICE_QTY, TEX_ACC_QTY, TEX_ACC_QTY_DEC, TEX_ACC_QTY_INC, TEX_REM_QTY, "
                                            "TEX_REM_QTY_DEC, TEX_REM_QTY_INC, REJECT_DESCRIPTION, REMARKS)"
                                " VALUES ( ?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");

    mtk::fbInsertParams params;

    #define ADD_OPTIONAL_FIELD(__FIELD_NAME__) \
        if(record.__FIELD_NAME__.HasValue())    \
            params.Add(record.__FIELD_NAME__.Get());  \
        else    \
            params.AddNull();

        params.Add(record.REC_TIME.Get());
        params.Add(record.SENT_TIME.Get());
        ADD_OPTIONAL_FIELD(MARKET_ORDER_ID);
        params.Add(record.OID_SESSION_ID.Get());
        params.Add(record.OID_RQ_CODE.Get());
        params.Add(record.PC_MARKET.Get());
        params.Add(record.PC_PRODUCT_CODE.Get());
        params.Add(record.SIDE.Get());
        params.Add(record.ACCOUNT_CC.Get());
        params.Add(record.ACCOUNT_NAME.Get());
        params.Add(record.RID_SESSION_ID.Get());
        params.Add(record.RID_RQ_CODE.Get());
        params.Add(record.CLI_REF.Get());
        params.Add(record.CFLUCT_KEY.Get());
        params.Add(record.CFLUCT_DATE_TIME.Get());
        params.Add(record.ORDER_TYPE.Get());
        ADD_OPTIONAL_FIELD(RQ_POS_PRICE);
        ADD_OPTIONAL_FIELD(RQ_POS_PRICE_DEC);
        ADD_OPTIONAL_FIELD(RQ_POS_PRICE_INC);
        ADD_OPTIONAL_FIELD(RQ_POS_QUANTITY);
        ADD_OPTIONAL_FIELD(RQ_POS_QUANTITY_DEC);
        ADD_OPTIONAL_FIELD(RQ_POS_QUANTITY_INC);
        ADD_OPTIONAL_FIELD(CF_POS_PRICE);
        ADD_OPTIONAL_FIELD(CF_POS_PRICE_DEC);
        ADD_OPTIONAL_FIELD(CF_POS_PRICE_INC);
        ADD_OPTIONAL_FIELD(CF_POS_QUANTITY);
        ADD_OPTIONAL_FIELD(CF_POS_QUANTITY_DEC);
        ADD_OPTIONAL_FIELD(CF_POS_QUANTITY_INC);
        ADD_OPTIONAL_FIELD(EXCF_EXEC_ID);
        ADD_OPTIONAL_FIELD(EXCF_EXEC_PRICE);
        ADD_OPTIONAL_FIELD(EXCF_EXEC_PRICE_DEC);
        ADD_OPTIONAL_FIELD(EXCF_EXEC_PRICE_INC);
        ADD_OPTIONAL_FIELD(EXCF_EXEC_QUANTITY);
        ADD_OPTIONAL_FIELD(EXCF_EXEC_QUANTITY_DEC);
        ADD_OPTIONAL_FIELD(EXCF_EXEC_QUANTITY_INC);
        ADD_OPTIONAL_FIELD(TEX_SUM_PRICE_QTY);
        ADD_OPTIONAL_FIELD(TEX_ACC_QTY);
        ADD_OPTIONAL_FIELD(TEX_ACC_QTY_DEC);
        ADD_OPTIONAL_FIELD(TEX_ACC_QTY_INC);
        ADD_OPTIONAL_FIELD(TEX_REM_QTY);
        ADD_OPTIONAL_FIELD(TEX_REM_QTY_DEC);
        ADD_OPTIONAL_FIELD(TEX_REM_QTY_INC);
        ADD_OPTIONAL_FIELD(REJECT_DESCRIPTION);
        ADD_OPTIONAL_FIELD(REMARKS);

        //  Request asynchronous write
        fbi.Insert(params);

}



//      COMMON
#define FILL_FIXED_NUMBER(__RECORD_FIELD_NAME__, __FIELD_VALUE__)  \
    __RECORD_FIELD_NAME__ = __FIELD_VALUE__.GetIntCode();   \
    __RECORD_FIELD_NAME__##_DEC = __FIELD_VALUE__.GetExt().GetDec();   \
    __RECORD_FIELD_NAME__##_INC = __FIELD_VALUE__.GetExt().GetInc();

void  fill_invariant  (record_info& full_record, const mtk::trd::msg::sub_invariant_order_info& invariant)
{
    full_record.ACCOUNT_CC =  invariant.account.client_code;
    full_record.ACCOUNT_NAME =  invariant.account.name;

    full_record.OID_RQ_CODE = invariant.order_id.req_code;
    full_record.OID_SESSION_ID = invariant.order_id.session_id;

    full_record.PC_MARKET = invariant.product_code.market;
    full_record.PC_PRODUCT_CODE = invariant.product_code.product;

    if(invariant.side == mtk::trd::msg::buy)
        full_record.SIDE = "buy";
    else if(invariant.side == mtk::trd::msg::sell)
        full_record.SIDE = "sell";
    else
        full_record.SIDE = "???";
}

void  fill_req_info  (record_info& full_record, const mtk::msg::sub_request_info& req_info)
{
    full_record.RID_RQ_CODE = req_info.req_id.req_code;
    full_record.RID_SESSION_ID = req_info.req_id.session_id;

    full_record.REMARKS = MTK_SS("from: " << req_info.process_info.location
                << " " << req_info.process_info.process_name  << "  " <<  req_info.process_info.version);
}

void  fill_control_fluct  (record_info& full_record, const mtk::msg::sub_control_fluct& cf)
{
    full_record.CFLUCT_KEY = cf.key;
    full_record.CFLUCT_DATE_TIME = cf.datetime;
}


void fill_total_executions(record_info& full_record, const mtk::trd::msg::sub_total_executions& total_execs)
{
    full_record.TEX_SUM_PRICE_QTY = total_execs.sum_price_by_qty.get()._0;
    FILL_FIXED_NUMBER(full_record.TEX_ACC_QTY, total_execs.acc_quantity);
    FILL_FIXED_NUMBER(full_record.TEX_REM_QTY, total_execs.remaining_qty);
}



void  fill_rq_xx(record_info& full_record, const mtk::trd::msg::RQ_XX & rq)
{
    fill_invariant  (full_record, rq.invariant);
    fill_req_info   (full_record, rq.request_info);
    full_record.CLI_REF =  rq.cli_ref;
    fill_control_fluct (full_record,  rq.orig_control_fluct);
}

void  fill_cf_xx(record_info& full_record, const mtk::trd::msg::CF_XX & cf)
{
    fill_invariant  (full_record, cf.invariant);
    full_record.MARKET_ORDER_ID = cf.market_order_id;
    full_record.RID_RQ_CODE = cf.req_id.req_code;
    full_record.RID_SESSION_ID = cf.req_id.session_id;
    full_record.CLI_REF =  cf.cli_ref;
    fill_control_fluct (full_record,  cf.orig_control_fluct);

    fill_total_executions(full_record, cf.total_execs);
}


void  fill_ex_xx(record_info& full_record, const mtk::trd::msg::sub_exec_conf& executed_pos)
{
    full_record.EXCF_EXEC_ID = executed_pos.exec_id;
    FILL_FIXED_NUMBER(full_record.EXCF_EXEC_PRICE,        executed_pos.price);
    FILL_FIXED_NUMBER(full_record.EXCF_EXEC_QUANTITY,        executed_pos.quantity);
}





//      LIMIT ORDERS
template<typename T>        //  ie:  mtk::trd::msg::RQ_NW_LS
void on_rq_xx_ls(const T&  rq)
{
    record_info  full_record;

    //  RQ_XX_LS   position
    FILL_FIXED_NUMBER(full_record.RQ_POS_PRICE,        rq.request_pos.price);
    FILL_FIXED_NUMBER(full_record.RQ_POS_QUANTITY,     rq.request_pos.quantity);

    fill_rq_xx(full_record, rq);
    full_record.SENT_TIME  =  rq.__internal_warning_control_fields->sent_date_time;
    full_record.ORDER_TYPE =  rq.__internal_warning_control_fields->message_type;
    full_record.REC_TIME   =  mtk::dtNowLocal();
    insert_record(full_record);
}


void  fill_cf_xx_ls(record_info& full_record, const mtk::trd::msg::CF_XX_LS & cf)
{
    FILL_FIXED_NUMBER(full_record.CF_POS_PRICE,        cf.market_pos.price);
    FILL_FIXED_NUMBER(full_record.CF_POS_QUANTITY,     cf.market_pos.quantity);

    fill_cf_xx(full_record, cf);
}

template<typename T>        //  ie:  mtk::trd::msg::CF_NW_LS
void on_cf_xx_ls(const T&  cf)
{
    record_info  full_record;

    fill_cf_xx_ls(full_record, cf);
    full_record.SENT_TIME  =  cf.__internal_warning_control_fields->sent_date_time;
    full_record.ORDER_TYPE =  cf.__internal_warning_control_fields->message_type;
    full_record.REC_TIME   =  mtk::dtNowLocal();
    insert_record(full_record);
}

template<typename T>        //  ie:  mtk::trd::msg::CF_NW_LS
void on_cf_ex_ls(const T&  ex)
{
    record_info  full_record;

    fill_cf_xx_ls(full_record, ex);
    fill_ex_xx(full_record, ex.executed_pos);
    full_record.SENT_TIME  =  ex.__internal_warning_control_fields->sent_date_time;
    full_record.ORDER_TYPE =  ex.__internal_warning_control_fields->message_type;
    full_record.REC_TIME   =  mtk::dtNowLocal();
    insert_record(full_record);
}

template<typename T>        //  ie:  mtk::trd::msg::RJ_NW_LS
void on_rj_xx_ls(const T&  rj)
{
    record_info  full_record;

    fill_cf_xx_ls(full_record, rj);
    full_record.REJECT_DESCRIPTION = rj.reject_description;
    full_record.SENT_TIME  =  rj.__internal_warning_control_fields->sent_date_time;
    full_record.ORDER_TYPE =  rj.__internal_warning_control_fields->message_type;
    full_record.REC_TIME   =  mtk::dtNowLocal();
    insert_record(full_record);
}





//      MARKET ORDERS
template<typename T>        //  ie:  mtk::trd::msg::RQ_NW_MK
void on_rq_xx_mk(const T&  rq)
{
    record_info  full_record;

    //  RQ_XX_LS   position
    FILL_FIXED_NUMBER(full_record.RQ_POS_QUANTITY,     rq.request_pos.quantity);

    fill_rq_xx(full_record, rq);
    full_record.SENT_TIME  =  rq.__internal_warning_control_fields->sent_date_time;
    full_record.ORDER_TYPE =  rq.__internal_warning_control_fields->message_type;
    full_record.REC_TIME   =  mtk::dtNowLocal();
    insert_record(full_record);
}

void  fill_cf_xx_mk(record_info& full_record, const mtk::trd::msg::CF_XX_MK & cf)
{
    FILL_FIXED_NUMBER(full_record.CF_POS_QUANTITY,     cf.market_pos.quantity);

    fill_cf_xx(full_record, cf);
}

template<typename T>        //  ie:  mtk::trd::msg::CF_NW_MK
void on_cf_xx_mk(const T&  cf)
{
    record_info  full_record;

    fill_cf_xx_mk(full_record, cf);
    full_record.SENT_TIME  =  cf.__internal_warning_control_fields->sent_date_time;
    full_record.ORDER_TYPE =  cf.__internal_warning_control_fields->message_type;
    full_record.REC_TIME   =  mtk::dtNowLocal();
    insert_record(full_record);
}

template<typename T>        //  ie:  mtk::trd::msg::CF_NW_LS
void on_cf_ex_mk(const T&  ex)
{
    record_info  full_record;

    fill_cf_xx_mk(full_record, ex);
    fill_ex_xx(full_record, ex.executed_pos);
    full_record.SENT_TIME  =  ex.__internal_warning_control_fields->sent_date_time;
    full_record.ORDER_TYPE =  ex.__internal_warning_control_fields->message_type;
    full_record.REC_TIME   =  mtk::dtNowLocal();
    insert_record(full_record);
}

template<typename T>        //  ie:  mtk::trd::msg::RJ_NW_MK
void on_rj_xx_mk(const T&  rj)
{
    record_info  full_record;

    fill_cf_xx_mk(full_record, rj);
    full_record.REJECT_DESCRIPTION = rj.reject_description;
    full_record.SENT_TIME  =  rj.__internal_warning_control_fields->sent_date_time;
    full_record.ORDER_TYPE =  rj.__internal_warning_control_fields->message_type;
    full_record.REC_TIME   =  mtk::dtNowLocal();
    insert_record(full_record);
}



//  ex msg_type   RQ_NW_LS   __RECEIVER__  on_rq_xx_ls
#define  MAKE_TRADING_SUSCRIPTION_RQ(__MSG_TYPE__, __RECEIVER__)    \
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::__MSG_TYPE__>            > hqpid_##__MSG_TYPE__;    \
        MTK_QPID_RECEIVER_CONNECT_F(     \
                                hqpid_##__MSG_TYPE__,     \
                                mtk::admin::get_url("client"),     \
                                "CLITESTING",     \
                                mtk::trd::msg::__MSG_TYPE__::get_in_subject("*", "*", "*", "*"),     \
                                mtk::trd::msg::__MSG_TYPE__,     \
                                __RECEIVER__)

#define  MAKE_TRADING_SUSCRIPTION_CF(__MSG_TYPE__, __RECEIVER__)    \
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::__MSG_TYPE__>            > hqpid_##__MSG_TYPE__;    \
        MTK_QPID_RECEIVER_CONNECT_F(     \
                                hqpid_##__MSG_TYPE__,     \
                                mtk::admin::get_url("client"),     \
                                "CLITESTING",     \
                                mtk::trd::msg::__MSG_TYPE__::get_in_subject("*", "*", "*", "*"),     \
                                mtk::trd::msg::__MSG_TYPE__,     \
                                __RECEIVER__)




int main(int argc, char ** argv)
{
    try
    {
        if(argc==1)
            mtk::admin::init("./config.cfg", APP_NAME, APP_VER, APP_DESCRIPTION, APP_MODIFICATIONS);
        else
            mtk::admin::init(argv[1], APP_NAME, APP_VER, APP_DESCRIPTION, APP_MODIFICATIONS);



        //      LS
        MAKE_TRADING_SUSCRIPTION_RQ   (RQ_NW_LS, on_rq_xx_ls);
        MAKE_TRADING_SUSCRIPTION_RQ   (RQ_MD_LS, on_rq_xx_ls);
        MAKE_TRADING_SUSCRIPTION_RQ   (RQ_CC_LS, on_rq_xx_ls);

        MAKE_TRADING_SUSCRIPTION_CF   (CF_NW_LS, on_cf_xx_ls);
        MAKE_TRADING_SUSCRIPTION_CF   (CF_MD_LS, on_cf_xx_ls);
        MAKE_TRADING_SUSCRIPTION_CF   (CF_CC_LS, on_cf_xx_ls);

        MAKE_TRADING_SUSCRIPTION_CF   (RJ_NW_LS, on_rj_xx_ls);
        MAKE_TRADING_SUSCRIPTION_CF   (RJ_MD_LS, on_rj_xx_ls);
        MAKE_TRADING_SUSCRIPTION_CF   (RJ_CC_LS, on_rj_xx_ls);

        MAKE_TRADING_SUSCRIPTION_CF   (CF_EX_LS, on_cf_ex_ls);




        //      MK
        MAKE_TRADING_SUSCRIPTION_RQ   (RQ_NW_MK, on_rq_xx_mk);
        MAKE_TRADING_SUSCRIPTION_RQ   (RQ_MD_MK, on_rq_xx_mk);
        MAKE_TRADING_SUSCRIPTION_RQ   (RQ_CC_MK, on_rq_xx_mk);

        MAKE_TRADING_SUSCRIPTION_CF   (CF_NW_MK, on_cf_xx_mk);
        MAKE_TRADING_SUSCRIPTION_CF   (CF_MD_MK, on_cf_xx_mk);
        MAKE_TRADING_SUSCRIPTION_CF   (CF_CC_MK, on_cf_xx_mk);

        MAKE_TRADING_SUSCRIPTION_CF   (RJ_NW_MK, on_rj_xx_mk);
        MAKE_TRADING_SUSCRIPTION_CF   (RJ_MD_MK, on_rj_xx_mk);
        MAKE_TRADING_SUSCRIPTION_CF   (RJ_CC_MK, on_rj_xx_mk);

        MAKE_TRADING_SUSCRIPTION_CF   (CF_EX_MK, on_cf_ex_mk);




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
