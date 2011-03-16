#include "trd_cli_ord_book.h"

#include "components/admin/admin.h"



namespace {
    const char*   VERSION = "2011-03-16";
    
    const char*   MODIFICATIONS =
                        "           2011-03-16     first version\n";


void command_version(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
{
    response_lines.push_back(MTK_SS(__FILE__ << ":  " << VERSION));
}

void command_modifications  (const std::string& /*command*/, const std::string& /*param*/,  mtk::list<std::string>&  response_lines)
{
    response_lines.push_back(__FILE__);
    response_lines.push_back(".......................................");
    response_lines.push_back(MODIFICATIONS);
}

    struct register_global_commands
    {
        register_global_commands (void)
        {
            mtk::admin::register_command("__GLOBAL__",  "ver",   "")->connect(command_version);
            mtk::admin::register_command("__GLOBAL__",  "modifs",   "")->connect(command_modifications);
        }
    };
    register_global_commands rc;

}       //  anonymous namespace  to register "static" commnads





namespace mtk{namespace trd{

    
    
namespace  trd_cli_ord_book {




struct handles_qpid
{
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::CF_NW_LS> > cf_nw_ls;
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::CF_MD_LS> > cf_md_ls;
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::CF_CC_LS> > cf_cc_ls;
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::RJ_NW_LS> > rj_nw_ls;
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::RJ_MD_LS> > rj_md_ls;
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::RJ_CC_LS> > rj_cc_ls;
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::CF_EX_LS> > cf_ex_ls;
};


struct s_status
{
    handles_qpid                                                handles;
    
    //  ls
    mtk::map<msg::sub_order_id, mtk::CountPtr<trd_cli_ls> >     ls_orders;

    mtk::Signal< const mtk::trd::msg::sub_order_id&, mtk::CountPtr<trd_cli_ls>&  >       sig_order_ls_new;
    mtk::Signal< mtk::trd::msg::RQ_XX_LS&, bool&    >                                           sig_request_hook;
};




s_status* __internal_ptr_status=0;
bool      deleted=false;



void cf_nw_ls(const mtk::trd::msg::CF_NW_LS& cf);
void cf_md_ls(const mtk::trd::msg::CF_MD_LS& cf);
void cf_cc_ls(const mtk::trd::msg::CF_CC_LS& cf);
void rj_nw_ls(const mtk::trd::msg::RJ_NW_LS& rj);
void rj_md_ls(const mtk::trd::msg::RJ_MD_LS& rj);
void rj_cc_ls(const mtk::trd::msg::RJ_CC_LS& rj);
void cf_ex_ls(const mtk::trd::msg::CF_EX_LS& ex);


s_status& get_status_ref(void)
{
    if (deleted)    throw mtk::Alarm(MTK_HERE, "on deleted module", mtk::alPriorWarning, mtk::alTypeNoPermisions);
    if (__internal_ptr_status==0)
    {
        __internal_ptr_status = new s_status();
            MTK_QPID_RECEIVER_CONNECT_F(
                                    __internal_ptr_status->handles.cf_nw_ls,
                                    mtk::admin::get_url("client"),
                                    "CLITESTING",
                                    mtk::trd::msg::CF_NW_LS::get_in_subject("CIMD", "*", "*"),
                                    mtk::trd::msg::CF_NW_LS,
                                    cf_nw_ls)

            MTK_QPID_RECEIVER_CONNECT_F(
                                    __internal_ptr_status->handles.cf_md_ls,
                                    mtk::admin::get_url("client"),
                                    "CLITESTING",
                                    mtk::trd::msg::CF_MD_LS::get_in_subject("CIMD", "*", "*"),
                                    mtk::trd::msg::CF_MD_LS,
                                    cf_md_ls)

            MTK_QPID_RECEIVER_CONNECT_F(
                                    __internal_ptr_status->handles.cf_cc_ls,
                                    mtk::admin::get_url("client"),
                                    "CLITESTING",
                                    mtk::trd::msg::CF_CC_LS::get_in_subject("CIMD", "*", "*"),
                                    mtk::trd::msg::CF_CC_LS,
                                    cf_cc_ls)

            MTK_QPID_RECEIVER_CONNECT_F(
                                    __internal_ptr_status->handles.rj_nw_ls,
                                    mtk::admin::get_url("client"),
                                    "CLITESTING",
                                    mtk::trd::msg::RJ_NW_LS::get_in_subject("CIMD", "*", "*"),
                                    mtk::trd::msg::RJ_NW_LS,
                                    rj_nw_ls)

            MTK_QPID_RECEIVER_CONNECT_F(
                                    __internal_ptr_status->handles.rj_md_ls,
                                    mtk::admin::get_url("client"),
                                    "CLITESTING",
                                    mtk::trd::msg::RJ_MD_LS::get_in_subject("CIMD", "*", "*"),
                                    mtk::trd::msg::RJ_MD_LS,
                                    rj_md_ls)

            MTK_QPID_RECEIVER_CONNECT_F(
                                    __internal_ptr_status->handles.rj_cc_ls,
                                    mtk::admin::get_url("client"),
                                    "CLITESTING",
                                    mtk::trd::msg::RJ_CC_LS::get_in_subject("CIMD", "*", "*"),
                                    mtk::trd::msg::RJ_CC_LS,
                                    rj_cc_ls)
            MTK_QPID_RECEIVER_CONNECT_F(
                                    __internal_ptr_status->handles.cf_ex_ls,
                                    mtk::admin::get_url("client"),
                                    "CLITESTING",
                                    mtk::trd::msg::CF_EX_LS::get_in_subject("CIMD", "*", "*"),
                                    mtk::trd::msg::CF_EX_LS,
                                    cf_ex_ls)
    }
    return *__internal_ptr_status;
}




template<typename T>
void send_request_message(const T& rq)
{
    static mtk::CountPtr< mtk::qpid_session > qpid_session = mtk::get_from_factory< mtk::qpid_session >(mtk::make_tuple(mtk::admin::get_url("client"), std::string("CLITESTING")));
    mtk::send_message(qpid_session, rq);
}



mtk::Signal< const mtk::trd::msg::sub_order_id&, mtk::CountPtr<trd_cli_ls>&  >& get_sig_order_ls_new    (void)
{
    return get_status_ref().sig_order_ls_new;
}



mtk::CountPtr<trd_cli_ls>  get_order_ls(const mtk::trd::msg::sub_order_id& ord_id)
{
    mtk::CountPtr<trd_cli_ls> order;    
    mtk::map<msg::sub_order_id, mtk::CountPtr<trd_cli_ls> >::iterator it= get_status_ref().ls_orders.find(ord_id);    
    if (it == get_status_ref().ls_orders.end())
    {
        //  creating new order
        order = mtk::make_cptr(new trd_cli_ls);
        order->sig_rq_nw.connect(send_request_message);
        order->sig_rq_md.connect(send_request_message);
        order->sig_rq_cc.connect(send_request_message);

        get_status_ref().ls_orders[ord_id] = order;
        get_status_ref().sig_order_ls_new.emit(ord_id, order);
    }
    else    
        order = it->second;
    return order;
}



mtk::Signal< mtk::trd::msg::RQ_XX_LS&, bool&    >&  get_signal_request_hook         (void)
{
    return get_status_ref().sig_request_hook;
}



mtk::CountPtr<trd_cli_ls>   rq_nw_ls    (                             const mtk::msg::sub_product_code&   pc, const msg::sub_position_ls& rq_pos, const std::string& cli_ref)
{
    mtk::msg::sub_request_info  rq_info = mtk::admin::get_request_info();
    mtk::trd::msg::sub_order_id ord_id (rq_info.req_id);
    
    mtk::CountPtr<trd_cli_ls> order = get_order_ls(ord_id);

    mtk::trd::msg::RQ_NW_LS rq(mtk::trd::msg::RQ_XX_LS(
                                        rq_info,
                                        ord_id,
                                        pc,
                                        rq_pos,
                                        cli_ref));
    order->rq_nw(rq);
    return order;
}

mtk::CountPtr<trd_cli_ls>   rq_nw_ls_manual    (                             const mtk::msg::sub_product_code&   pc, const msg::sub_position_ls& rq_pos, const std::string& cli_ref)
{
    mtk::msg::sub_request_info  rq_info = mtk::admin::get_request_info();
    mtk::trd::msg::sub_order_id ord_id (rq_info.req_id);

    mtk::trd::msg::RQ_NW_LS rq(mtk::trd::msg::RQ_XX_LS(
                                        rq_info,
                                        ord_id,
                                        pc,
                                        rq_pos,
                                        cli_ref));
    bool canceled=false;
    get_status_ref().sig_request_hook.emit(rq, canceled);
    if (!canceled)
    {
        mtk::CountPtr<trd_cli_ls> order = get_order_ls(ord_id);
        order->rq_nw(rq);

        return order;
    }
    else
        return mtk::CountPtr<trd_cli_ls>();
}


/*
    it will return the last request or last confirmation if we don't have a previus request
 */
mtk::trd::msg::RQ_XX_LS get_last_request_or_confirmation (mtk::CountPtr<trd_cli_ls> order)
{
    if (order.isValid()==false)
        throw mtk::Alarm(MTK_HERE, "missing order", mtk::alPriorCritic, mtk::alTypeNoPermisions);

    if (order->last_request().HasValue())
        return order->last_request().Get();
    else if (order->last_confirmation().HasValue())
    {
        mtk::trd::msg::CF_XX_LS lc (order->last_confirmation().Get());
        return mtk::trd::msg::RQ_XX_LS( lc.req_info, lc.confirmated_info.order_id, lc.confirmated_info.product_code, lc.confirmated_info.market_pos, lc.confirmated_info.cli_ref);
    }
   else
        throw mtk::Alarm(MTK_HERE, "missing product code in order", mtk::alPriorCritic, mtk::alTypeNoPermisions);
}



mtk::CountPtr<trd_cli_ls>   rq_md_ls    ( const msg::sub_order_id& ord_id, const msg::sub_position_ls& rq_pos, const std::string& cli_ref)
{
    mtk::msg::sub_request_info  rq_info = mtk::admin::get_request_info();
    
    mtk::CountPtr<trd_cli_ls> order = get_order_ls(ord_id);
    mtk::trd::msg::RQ_XX_LS rq = get_last_request_or_confirmation(order);
    rq.request_pos = rq_pos;
    rq.cli_ref = cli_ref;
    order->rq_md(mtk::trd::msg::RQ_MD_LS (rq));
    
    return order;
}

mtk::CountPtr<trd_cli_ls>   rq_md_ls_manual    (const msg::sub_order_id& ord_id)
{
    mtk::msg::sub_request_info  rq_info = mtk::admin::get_request_info();


    mtk::CountPtr<trd_cli_ls> order = get_order_ls(ord_id);
    mtk::trd::msg::RQ_MD_LS rq(get_last_request_or_confirmation(order));

    bool canceled=false;
    get_status_ref().sig_request_hook.emit(rq, canceled);
    if (!canceled)
    {
        order->rq_md(rq);
        return order;
    }
    else
        return mtk::CountPtr<trd_cli_ls>();
}

mtk::CountPtr<trd_cli_ls>   rq_cc_ls    ( const msg::sub_order_id& ord_id )
{
    mtk::msg::sub_request_info  rq_info = mtk::admin::get_request_info();
    
    mtk::CountPtr<trd_cli_ls> order = get_order_ls(ord_id);

    order->rq_cc(mtk::trd::msg::RQ_CC_LS (get_last_request_or_confirmation(order)));
    
    return order;
}



void cf_nw_ls(const mtk::trd::msg::CF_NW_LS& cf)
{
    mtk::CountPtr<trd_cli_ls>  order = get_order_ls(cf.confirmated_info.order_id);
    order->cf_nw(cf);
    //get_status_ref().sig_order_ls_status_modif.emit(order);
}
void cf_md_ls(const mtk::trd::msg::CF_MD_LS& cf)
{
    mtk::CountPtr<trd_cli_ls>  order = get_order_ls(cf.confirmated_info.order_id);
    order->cf_md(cf);
}

void cf_cc_ls(const mtk::trd::msg::CF_CC_LS& cf)
{
    mtk::CountPtr<trd_cli_ls>  order = get_order_ls(cf.confirmated_info.order_id);
    order->cf_cc(cf);
}

void rj_nw_ls(const mtk::trd::msg::RJ_NW_LS& rj)
{
    mtk::CountPtr<trd_cli_ls>  order = get_order_ls(rj.confirmated_info.order_id);
    order->rj_nw(rj);
}

void rj_md_ls(const mtk::trd::msg::RJ_MD_LS& rj)
{
    mtk::CountPtr<trd_cli_ls>  order = get_order_ls(rj.confirmated_info.order_id);
    order->rj_md(rj);
}

void rj_cc_ls(const mtk::trd::msg::RJ_CC_LS& rj)
{
    mtk::CountPtr<trd_cli_ls>  order = get_order_ls(rj.confirmated_info.order_id);
    order->rj_cc(rj);
}

void cf_ex_ls(const mtk::trd::msg::CF_EX_LS& ex)
{
    mtk::CountPtr<trd_cli_ls>  order = get_order_ls(ex.confirmated_info.order_id);
    order->cf_ex(ex);
}









};//    namespace  trd_cli_ord_book {

};   //  namespace mtk
};   //  namespace trd
