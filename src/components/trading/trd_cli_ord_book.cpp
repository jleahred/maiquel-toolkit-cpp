#include "trd_cli_ord_book.h"

#include "components/admin/admin.h"
#include "components/trading/accounts/msg_account_manager.h"
#include "components/trading/accounts/account_manager_cli.h"



namespace {
    const char*   VERSION = "2011-03-16";

    const char*   MODIFICATIONS =
                        "           2011-03-16     first version\n"
                        "           2011-05-13     added market orders\n";


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
void command_stats  (const std::string& /*command*/, const std::string& /*param*/,  mtk::list<std::string>&  response_lines);



void register_global_commands (void)
{
    mtk::admin::register_command("__GLOBAL__",    "ver",   "")->connect(command_version);
    mtk::admin::register_command("__GLOBAL__",    "modifs","")->connect(command_modifications);
    mtk::admin::register_command("__GLOBAL__",    "stats", "")->connect(command_stats);
    mtk::admin::register_command("cli_ord_book",  "stats", "")->connect(command_stats);
}

    MTK_ADMIN_REGISTER_GLOBAL_COMMANDS(register_global_commands)

}       //  anonymous namespace  to register "static" commnads





namespace mtk{namespace trd{



namespace  trd_cli_ord_book {


    void orders_susbcription_for_account(const mtk::trd::account::msg::sub_grant&);
    void   init (void)
    {
        //  listen for new accounts
            //mtk::CountPtr<mtk::Signal<const mtk::trd::account::msg::sub_grant&> >           get_signal_new_grant_received(void);
        mtk::accmgrcli::get_signal_new_grant_received()->connect(orders_susbcription_for_account);
    }




struct handles_qpid
{
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::CF_NW_LS> > cf_nw_ls;
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::CF_MD_LS> > cf_md_ls;
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::CF_CC_LS> > cf_cc_ls;
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::RJ_NW_LS> > rj_nw_ls;
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::RJ_MD_LS> > rj_md_ls;
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::RJ_CC_LS> > rj_cc_ls;
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::CF_EX_LS> > cf_ex_ls;
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::CF_ST_LS> > cf_st_ls;

    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::CF_NW_MK> > cf_nw_mk;
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::CF_MD_MK> > cf_md_mk;
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::CF_CC_MK> > cf_cc_mk;
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::RJ_NW_MK> > rj_nw_mk;
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::RJ_MD_MK> > rj_md_mk;
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::RJ_CC_MK> > rj_cc_mk;
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::CF_EX_MK> > cf_ex_mk;
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::CF_ST_MK> > cf_st_mk;
};


struct s_status
{
    mtk::Signal< const mtk::msg::sub_product_code&, const mtk::trd::msg::sub_exec_conf&>  sig_execution;


    //  ls
    mtk::map<msg::sub_order_id, mtk::CountPtr<trd_cli_ls_dangerous_signals_not_warped> >     ls_orders;

    mtk::Signal< const mtk::trd::msg::sub_order_id&, mtk::CountPtr<trd_cli_ls_dangerous_signals_not_warped>&  >     sig_order_ls_new;
    mtk::Signal< mtk::trd::msg::RQ_XX_LS&, bool& /*canceled*/, bool  /*aggre*/   >                                  sig_request_hook_ls;


    //  mk
    mtk::map<msg::sub_order_id, mtk::CountPtr<trd_cli_mk_dangerous_signals_not_warped> >     mk_orders;

    mtk::Signal< const mtk::trd::msg::sub_order_id&, mtk::CountPtr<trd_cli_mk_dangerous_signals_not_warped>&  >          sig_order_mk_new;
    mtk::Signal< mtk::trd::msg::RQ_XX_MK&, bool& /*canceled*/, bool  /*aggre*/   >          sig_request_hook_mk;
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
void cf_st_ls(const mtk::trd::msg::CF_ST_LS& ex);


void cf_nw_mk(const mtk::trd::msg::CF_NW_MK& cf);
void cf_md_mk(const mtk::trd::msg::CF_MD_MK& cf);
void cf_cc_mk(const mtk::trd::msg::CF_CC_MK& cf);
void rj_nw_mk(const mtk::trd::msg::RJ_NW_MK& rj);
void rj_md_mk(const mtk::trd::msg::RJ_MD_MK& rj);
void rj_cc_mk(const mtk::trd::msg::RJ_CC_MK& rj);
void cf_ex_mk(const mtk::trd::msg::CF_EX_MK& ex);
void cf_st_mk(const mtk::trd::msg::CF_ST_MK& ex);



void orders_susbcription_for_account(const mtk::trd::account::msg::sub_grant& grant)
{
            static  mtk::CountPtr< mtk::map<mtk::trd::account::msg::sub_grant::IC_key, handles_qpid> >   map_handles;
            if(map_handles.isValid() == false)
                map_handles = mtk::make_cptr( new mtk::map<mtk::trd::account::msg::sub_grant::IC_key, handles_qpid> );


            auto located = map_handles->find(grant.key);

            //  grant deletion
            if((grant.type == "V"  ||  grant.type == "C"  ||  grant.type == "F") == false)
            {
                if(located != map_handles->end())
                    map_handles->erase(located);
                return;
            }

            //  already registered grant
            if(located != map_handles->end())
                return;

            // new grant received, making new suscription
            map_handles->insert( std::make_pair(grant.key, handles_qpid()) );
            handles_qpid&   handles = (*map_handles)[grant.key];        //  dangerous reference, I know



            std::string process_client_code = mtk::admin::get_process_info().location.client_code;
            //if(client_code == "CIMD")           client_code = "*";
            if(process_client_code != "CIMD"  &&  process_client_code !=  grant.key.account.client_code)
                throw mtk::Alarm(MTK_HERE, "ord_book", MTK_SS("client code is not cimd and client account is diferent to client code "
                                        << process_client_code << "  !=  "  << grant.key.account.client_code), mtk::alPriorCritic, mtk::alTypeLogicError);

            std::string client_code = grant.key.account.client_code;
            std::string market = grant.key.market;
            std::string account_name = grant.key.account.name;
            std::string session_id = mtk::admin::get_session_id();

            MTK_QPID_RECEIVER_CONNECT_F(
                                    handles.cf_nw_ls,
                                    mtk::admin::get_url("client"),
                                    mtk::trd::msg::CF_NW_LS::get_in_subject(client_code, market, account_name, "*"),
                                    mtk::trd::msg::CF_NW_LS,
                                    cf_nw_ls)

            MTK_QPID_RECEIVER_CONNECT_F(
                                    handles.cf_md_ls,
                                    mtk::admin::get_url("client"),
                                    mtk::trd::msg::CF_MD_LS::get_in_subject(client_code, market, account_name, "*"),
                                    mtk::trd::msg::CF_MD_LS,
                                    cf_md_ls)

            MTK_QPID_RECEIVER_CONNECT_F(
                                    handles.cf_cc_ls,
                                    mtk::admin::get_url("client"),
                                    mtk::trd::msg::CF_CC_LS::get_in_subject(client_code, market, account_name, "*"),
                                    mtk::trd::msg::CF_CC_LS,
                                    cf_cc_ls)

            MTK_QPID_RECEIVER_CONNECT_F(
                                    handles.rj_nw_ls,
                                    mtk::admin::get_url("client"),
                                    mtk::trd::msg::RJ_NW_LS::get_in_subject(client_code, market, account_name, session_id),
                                    mtk::trd::msg::RJ_NW_LS,
                                    rj_nw_ls)

            MTK_QPID_RECEIVER_CONNECT_F(
                                    handles.rj_md_ls,
                                    mtk::admin::get_url("client"),
                                    mtk::trd::msg::RJ_MD_LS::get_in_subject(client_code, market, account_name, session_id),
                                    mtk::trd::msg::RJ_MD_LS,
                                    rj_md_ls)

            MTK_QPID_RECEIVER_CONNECT_F(
                                    handles.rj_cc_ls,
                                    mtk::admin::get_url("client"),
                                    mtk::trd::msg::RJ_CC_LS::get_in_subject(client_code, market, account_name, session_id),
                                    mtk::trd::msg::RJ_CC_LS,
                                    rj_cc_ls)
            MTK_QPID_RECEIVER_CONNECT_F(
                                    handles.cf_ex_ls,
                                    mtk::admin::get_url("client"),
                                    mtk::trd::msg::CF_EX_LS::get_in_subject(client_code, market, account_name, "*"),
                                    mtk::trd::msg::CF_EX_LS,
                                    cf_ex_ls)



            MTK_QPID_RECEIVER_CONNECT_F(
                                    handles.cf_nw_mk,
                                    mtk::admin::get_url("client"),
                                    mtk::trd::msg::CF_NW_MK::get_in_subject(client_code, market, account_name, "*"),
                                    mtk::trd::msg::CF_NW_MK,
                                    cf_nw_mk)

            MTK_QPID_RECEIVER_CONNECT_F(
                                    handles.cf_md_mk,
                                    mtk::admin::get_url("client"),
                                    mtk::trd::msg::CF_MD_MK::get_in_subject(client_code, market, account_name, "*"),
                                    mtk::trd::msg::CF_MD_MK,
                                    cf_md_mk)

            MTK_QPID_RECEIVER_CONNECT_F(
                                    handles.cf_cc_mk,
                                    mtk::admin::get_url("client"),
                                    mtk::trd::msg::CF_CC_MK::get_in_subject(client_code, market, account_name, "*"),
                                    mtk::trd::msg::CF_CC_MK,
                                    cf_cc_mk)

            MTK_QPID_RECEIVER_CONNECT_F(
                                    handles.rj_nw_mk,
                                    mtk::admin::get_url("client"),
                                    mtk::trd::msg::RJ_NW_MK::get_in_subject(client_code, market, account_name, session_id),
                                    mtk::trd::msg::RJ_NW_MK,
                                    rj_nw_mk)

            MTK_QPID_RECEIVER_CONNECT_F(
                                    handles.rj_md_mk,
                                    mtk::admin::get_url("client"),
                                    mtk::trd::msg::RJ_MD_MK::get_in_subject(client_code, market, account_name, session_id),
                                    mtk::trd::msg::RJ_MD_MK,
                                    rj_md_mk)

            MTK_QPID_RECEIVER_CONNECT_F(
                                    handles.rj_cc_mk,
                                    mtk::admin::get_url("client"),
                                    mtk::trd::msg::RJ_CC_MK::get_in_subject(client_code, market, account_name, session_id),
                                    mtk::trd::msg::RJ_CC_MK,
                                    rj_cc_mk)
            MTK_QPID_RECEIVER_CONNECT_F(
                                    handles.cf_ex_mk,
                                    mtk::admin::get_url("client"),
                                    mtk::trd::msg::CF_EX_MK::get_in_subject(client_code, market, account_name, "*"),
                                    mtk::trd::msg::CF_EX_MK,
                                    cf_ex_mk)


            //  request load current orders and subscribe to response
            mtk::msg::sub_request_info  ri = mtk::admin::get_request_info();
            MTK_QPID_RECEIVER_CONNECT_F(
                                    handles.cf_st_ls,
                                    mtk::admin::get_url("client"),
                                    mtk::trd::msg::CF_ST_LS::get_in_subject(grant.key.account.client_code, ri.req_id.session_id),
                                    mtk::trd::msg::CF_ST_LS,
                                    cf_st_ls)
            MTK_QPID_RECEIVER_CONNECT_F(
                                    handles.cf_st_mk,
                                    mtk::admin::get_url("client"),
                                    mtk::trd::msg::CF_ST_MK::get_in_subject(grant.key.account.client_code, ri.req_id.session_id),
                                    mtk::trd::msg::CF_ST_MK,
                                    cf_st_mk)
            mtk::trd::msg::RQ_ORDERS_STATUS  msg_rq_order_status(ri, grant.key.market, grant.key.account);
            mtk::send_message(mtk::admin::get_qpid_sender("client", mtk::t_qpid_address("CLITESTING")), msg_rq_order_status);
}


s_status& get_status_ref(void)
{
    if (deleted)    throw mtk::Alarm(MTK_HERE, "trd_cli_ord_book", "on deleted module", mtk::alPriorWarning, mtk::alTypeNoPermisions);
    if (__internal_ptr_status==0)
    {

        __internal_ptr_status = new s_status();

    }
    return *__internal_ptr_status;
}




template<typename T>
void send_request_message(const T& rq)
{
    static mtk::CountPtr< mtk::mtkqpid_sender > qpid_sender = mtk::get_from_factory< mtk::mtkqpid_sender >(mtk::make_tuple(mtk::admin::get_url("client"), mtk::t_qpid_address("CLITESTING")));
    mtk::send_message(qpid_sender, rq);
}



mtk::Signal< const mtk::trd::msg::sub_order_id&, mtk::CountPtr<trd_cli_ls_dangerous_signals_not_warped>&  >& get_sig_order_ls_new    (void)
{
    return get_status_ref().sig_order_ls_new;
}

mtk::Signal< const mtk::trd::msg::sub_order_id&, mtk::CountPtr<trd_cli_mk_dangerous_signals_not_warped>&  >& get_sig_order_mk_new    (void)
{
    return get_status_ref().sig_order_mk_new;
}


mtk::Signal< const mtk::msg::sub_product_code&, const mtk::trd::msg::sub_exec_conf& >& get_sig_execution       (void)
{
    return get_status_ref().sig_execution;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////
//      generic support   get_order
/**  ex
 *      ORDER_TYPE  trd_cli_ls_dangerous_not_warped
 */
template<typename ORDER_TYPE>
mtk::CountPtr<ORDER_TYPE>  get_order_withmapandsignal(      const mtk::trd::msg::sub_order_id& ord_id,
                                                            mtk::map<msg::sub_order_id,
                                                            mtk::CountPtr<ORDER_TYPE> >&  order_map,
                                                            mtk::Signal< const mtk::trd::msg::sub_order_id&, mtk::CountPtr<ORDER_TYPE>&  >& signal_new)
{
    mtk::CountPtr<ORDER_TYPE> order;
    typename mtk::map<msg::sub_order_id, mtk::CountPtr<ORDER_TYPE> >::iterator it= order_map.find(ord_id);
    if (it == order_map.end())
    {
        //  creating new order
        order = mtk::make_cptr(new ORDER_TYPE);
        order->sig_rq_nw.connect(send_request_message);
        order->sig_rq_md.connect(send_request_message);
        order->sig_rq_cc.connect(send_request_message);

        order_map[ord_id] = order;
        signal_new.emit(ord_id, order);
    }
    else
        order = it->second;
    return order;
}

template<typename ORDER_TYPE>
mtk::CountPtr<ORDER_TYPE>  get_order(const mtk::trd::msg::sub_order_id& ord_id);

template<>
mtk::CountPtr<trd_cli_ls_dangerous_signals_not_warped>  get_order<trd_cli_ls_dangerous_signals_not_warped>(const mtk::trd::msg::sub_order_id& ord_id)
{
    return get_order_withmapandsignal<trd_cli_ls_dangerous_signals_not_warped>(ord_id, get_status_ref().ls_orders, get_status_ref().sig_order_ls_new);
}

template<>
mtk::CountPtr<trd_cli_mk_dangerous_signals_not_warped>  get_order<trd_cli_mk_dangerous_signals_not_warped>(const mtk::trd::msg::sub_order_id& ord_id)
{
    return get_order_withmapandsignal<trd_cli_mk_dangerous_signals_not_warped>(ord_id, get_status_ref().mk_orders, get_status_ref().sig_order_mk_new);
}


//      generic support   get_order
//////////////////////////////////////////////////////////////////////////////////////////////////////////



mtk::CountPtr<trd_cli_ls>          get_order_ls        (const msg::sub_order_id& ord_id)
{
    return  mtk::make_cptr(new trd_cli_ls(get_order<trd_cli_ls_dangerous_signals_not_warped>(ord_id)));
}

mtk::CountPtr<trd_cli_mk>          get_order_mk        (const msg::sub_order_id& ord_id)
{
    return  mtk::make_cptr(new trd_cli_mk(get_order<trd_cli_mk_dangerous_signals_not_warped>(ord_id)));
}





mtk::list<mtk::trd::msg::sub_order_id>      get_all_order_ids       (void)
{
    mtk::list<mtk::trd::msg::sub_order_id>  result;
    if(__internal_ptr_status == 0)        return result;


    //mtk::map<msg::sub_order_id, mtk::CountPtr<trd_cli_ls_dangerous_signals_not_warped> >     ls_orders;
    for(mtk::map<msg::sub_order_id, mtk::CountPtr<trd_cli_ls_dangerous_signals_not_warped> >::const_iterator it = __internal_ptr_status->ls_orders.begin(); it!=__internal_ptr_status->ls_orders.end(); ++it)
        result.push_back(it->first);

    //mtk::map<msg::sub_order_id, mtk::CountPtr<trd_cli_mk_dangerous_signals_not_warped> >     mk_orders;
    for(mtk::map<msg::sub_order_id, mtk::CountPtr<trd_cli_mk_dangerous_signals_not_warped> >::const_iterator it = __internal_ptr_status->mk_orders.begin(); it!=__internal_ptr_status->mk_orders.end(); ++it)
        result.push_back(it->first);


    return result;
}



mtk::Signal< mtk::trd::msg::RQ_XX_LS&, bool&, bool    >&  get_signal_request_hook_ls         (void)
{
    return get_status_ref().sig_request_hook_ls;
}

mtk::Signal< mtk::trd::msg::RQ_XX_MK&, bool&, bool    >&  get_signal_request_hook_mk         (void)
{
    return get_status_ref().sig_request_hook_mk;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////
//      generic support

/**
 *      ex:
 *              ORDER_TYPE                  trd_cli_ls_dangerous_signals_not_warped
 *              POS_TYPE                    msg::sub_position_ls
 *              REQUEST_TYPE                mtk::trd::msg::RQ_XX_LS
 */
template<typename ORDER_TYPE, typename  POS_TYPE,  typename REQUEST_TYPE, typename REQUEST_TYPE_ORDER_TYPE>
mtk::CountPtr<ORDER_TYPE>   rq_nw_xx    (               const mtk::msg::sub_product_code&   pc,
                                                        const mtk::trd::msg::enBuySell      buy_sell,
                                                        const POS_TYPE& rq_pos,
                                                        const mtk::trd::msg::sub_account_info& account,
                                                        const std::string& cli_ref)
{
    mtk::msg::sub_request_info  rq_info = mtk::admin::get_request_info();

    mtk::trd::msg::sub_order_id ord_id (rq_info.req_id);

    mtk::CountPtr<ORDER_TYPE> order = get_order<ORDER_TYPE>(ord_id);


    mtk::trd::msg::sub_invariant_order_info  invariant  (ord_id, pc, buy_sell, account);
    mtk::trd::msg::RQ_XX                     rqxx       (invariant, rq_info, cli_ref, mtk::admin::get_control_fluct_info());
    REQUEST_TYPE                             rqxxxx     (rqxx, rq_pos);

    REQUEST_TYPE_ORDER_TYPE                  rq         (rqxxxx);

    order->rq_nw(rq);
    return order;
}



template<typename ORDER_TYPE, typename  POS_TYPE,  typename REQUEST_TYPE, typename REQUEST_TYPE_ORDER_TYPE>
mtk::CountPtr<ORDER_TYPE>   rq_nw_xx_manual    (        const mtk::msg::sub_product_code&   pc,
                                                        const mtk::trd::msg::enBuySell      buy_sell,
                                                        const POS_TYPE& rq_pos,
                                                        const std::string& cli_ref,
                                                        bool agressive,
                                                        mtk::Signal< REQUEST_TYPE&, bool& /*canceled*/, bool  /*aggre*/   >& signal_hook
                                                        )
{
    mtk::msg::sub_request_info  rq_info = mtk::admin::get_request_info();
    mtk::trd::msg::sub_order_id ord_id (rq_info.req_id);

    mtk::trd::msg::sub_account_info          account    ("", "");
    mtk::trd::msg::sub_invariant_order_info  invariant  (ord_id, pc, buy_sell, account);
    mtk::trd::msg::RQ_XX                     rqxx       (invariant, rq_info, cli_ref, mtk::admin::get_control_fluct_info());
    REQUEST_TYPE                             rqxxls     (rqxx, rq_pos);

    REQUEST_TYPE_ORDER_TYPE                  rq         (rqxxls);


    bool canceled=false;
    signal_hook.emit(rq, canceled, agressive);
    if (!canceled)
    {
        mtk::CountPtr<ORDER_TYPE> order = get_order<ORDER_TYPE>(ord_id);
        order->rq_nw(rq);

        return order;
    }
    else
        return mtk::CountPtr<ORDER_TYPE>();
}






/**
    it will return the last request
    or  an artificial request with confirmation info in case we don't have a previus request

    ex:
        ORDER_TYPE:  trd_cli_ls_dangerous_signals_not_warped
 */
template<typename  ORDER_TYPE,  typename REQUEST_TYPE,  typename CONF_TYPE>
REQUEST_TYPE     get_new_request_from_last_request_or_build_from_confirmation (mtk::CountPtr<ORDER_TYPE> order)
{
    if (order.isValid()==false)
        throw mtk::Alarm(MTK_HERE, "trd_cli_ord_book", "missing order", mtk::alPriorCritic, mtk::alTypeNoPermisions);

    if(order->has_pending_rq())
    {
        REQUEST_TYPE                rqxxls     (order->last_request().Get());
        rqxxls.request_info         =  mtk::admin::get_request_info();
        rqxxls.orig_control_fluct   =  mtk::admin::get_control_fluct_info();
        return rqxxls;
    }
    else if (order->last_confirmation().HasValue())
    {
        CONF_TYPE                   lc (order->last_confirmation().Get());

        mtk::trd::msg::RQ_XX        rqxx       (lc.invariant, mtk::admin::get_request_info(), lc.cli_ref, mtk::admin::get_control_fluct_info());
        REQUEST_TYPE                rqxxls     (rqxx, lc.market_pos);

        return rqxxls;
    }
   else
        throw mtk::Alarm(MTK_HERE, "trd_cli_ord_book", "not pending request, not confirmated order???", mtk::alPriorCritic, mtk::alTypeNoPermisions);
}


template<typename ORDER_TYPE, typename  POS_TYPE,  typename REQUEST_TYPE, typename REQUEST_TYPE_ORDER_TYPE, typename  CONF_TYPE>
mtk::CountPtr<ORDER_TYPE>   rq_md_xx    ( const msg::sub_order_id& ord_id, const POS_TYPE& rq_pos, const std::string& cli_ref)
{
    mtk::CountPtr<ORDER_TYPE> order = get_order<ORDER_TYPE>(ord_id);
    REQUEST_TYPE rq = get_new_request_from_last_request_or_build_from_confirmation<ORDER_TYPE, REQUEST_TYPE, CONF_TYPE>(order);
    rq.request_pos = rq_pos;
    rq.cli_ref = cli_ref;
    order->rq_md(REQUEST_TYPE_ORDER_TYPE (rq));

    return order;
}


template<typename ORDER_TYPE, typename  POS_TYPE,  typename REQUEST_TYPE, typename REQUEST_TYPE_ORDER_TYPE, typename  CONF_TYPE>
mtk::CountPtr<ORDER_TYPE>   rq_md_xx_manual    (const msg::sub_order_id& ord_id, mtk::Signal< REQUEST_TYPE&, bool& /*canceled*/, bool  /*aggre*/   >& signal_hook)
{
    mtk::CountPtr<ORDER_TYPE> order = get_order<ORDER_TYPE>(ord_id);
    REQUEST_TYPE_ORDER_TYPE   rq(get_new_request_from_last_request_or_build_from_confirmation<ORDER_TYPE, REQUEST_TYPE, CONF_TYPE>(order));

    bool canceled=false;
    signal_hook.emit(rq, canceled, false);
    if (!canceled)
    {
        order->rq_md(rq);
        return order;
    }
    else
        return mtk::CountPtr<ORDER_TYPE>();
}


template<typename ORDER_TYPE, typename REQUEST_TYPE, typename REQUEST_TYPE_ORDER_TYPE, typename  CONF_TYPE>
mtk::CountPtr<ORDER_TYPE>   rq_cc_xx    (const msg::sub_order_id& ord_id)
{
    mtk::CountPtr<ORDER_TYPE> order = get_order<ORDER_TYPE>(ord_id);

    order->rq_cc(REQUEST_TYPE_ORDER_TYPE (get_new_request_from_last_request_or_build_from_confirmation<ORDER_TYPE, REQUEST_TYPE, CONF_TYPE>(order)));

    return order;
}


template<typename ORDER_TYPE, typename  CONF_TYPE>
void cf_nw_xx(const CONF_TYPE& cf)
{
    mtk::admin::check_control_fluct(cf.orig_control_fluct);

    mtk::CountPtr<ORDER_TYPE>  order = get_order<ORDER_TYPE>(cf.invariant.order_id);
    order->cf_nw(cf);
    //get_status_ref().sig_order_ls_status_modif.emit(order);
}


template<typename ORDER_TYPE, typename  CONF_TYPE>
void cf_md_xx(const CONF_TYPE& cf)
{
    mtk::admin::check_control_fluct(cf.orig_control_fluct);

    mtk::CountPtr<ORDER_TYPE>  order = get_order<ORDER_TYPE>(cf.invariant.order_id);
    order->cf_md(cf);
}

template<typename ORDER_TYPE, typename  CONF_TYPE>
void cf_cc_xx(const CONF_TYPE& cf)
{
    mtk::admin::check_control_fluct(cf.orig_control_fluct);

    mtk::CountPtr<ORDER_TYPE>  order = get_order<ORDER_TYPE>(cf.invariant.order_id);
    order->cf_cc(cf);
}

template<typename ORDER_TYPE, typename  REJECT_TYPE>
void rj_nw_xx(const REJECT_TYPE& rj)
{
    mtk::admin::check_control_fluct( rj.orig_control_fluct);

    mtk::CountPtr<ORDER_TYPE>  order = get_order<ORDER_TYPE>(rj.invariant.order_id);
    order->rj_nw(rj);
}

template<typename ORDER_TYPE, typename  REJECT_TYPE>
void rj_md_xx(const REJECT_TYPE& rj)
{
    mtk::admin::check_control_fluct( rj.orig_control_fluct);

    mtk::CountPtr<ORDER_TYPE>  order = get_order<ORDER_TYPE>(rj.invariant.order_id);
    order->rj_md(rj);
}

template<typename ORDER_TYPE, typename  REJECT_TYPE>
void rj_cc_xx(const REJECT_TYPE& rj)
{
    mtk::admin::check_control_fluct( rj.orig_control_fluct);

    mtk::CountPtr<ORDER_TYPE>  order = get_order<ORDER_TYPE>(rj.invariant.order_id);
    order->rj_cc(rj);
}

template<typename ORDER_TYPE, typename  EXEC_TYPE>
void cf_ex_xx(const EXEC_TYPE& ex)
{
    mtk::admin::check_control_fluct(ex.orig_control_fluct);

    mtk::CountPtr<ORDER_TYPE>  order = get_order<ORDER_TYPE>(ex.invariant.order_id);
    order->cf_ex(ex);

    get_status_ref().sig_execution.emit(ex.invariant.product_code, ex.executed_pos);
}

template<typename ORDER_TYPE, typename  CONF_TYPE>
void cf_st_xx(const CONF_TYPE& cf)
{
    mtk::CountPtr<ORDER_TYPE>  order = get_order<ORDER_TYPE>(cf.invariant.order_id);
    order->cf_st(cf);
}



//      generic support
//////////////////////////////////////////////////////////////////////////////////////////////////////////


mtk::CountPtr<trd_cli_ls_dangerous_signals_not_warped>   rq_nw_ls        (const mtk::msg::sub_product_code&   pc, mtk::trd::msg::enBuySell  buy_sell, const msg::sub_position_ls& rq_pos, const mtk::trd::msg::sub_account_info& account, const std::string& cli_ref)
{
    return rq_nw_xx<trd_cli_ls_dangerous_signals_not_warped, msg::sub_position_ls, mtk::trd::msg::RQ_XX_LS, mtk::trd::msg::RQ_NW_LS>(pc, buy_sell, rq_pos, account, cli_ref);
}

mtk::CountPtr<trd_cli_mk_dangerous_signals_not_warped>   rq_nw_mk        (const mtk::msg::sub_product_code&   pc, mtk::trd::msg::enBuySell  buy_sell, const msg::sub_position_mk& rq_pos, const mtk::trd::msg::sub_account_info& account, const std::string& cli_ref)
{
    return rq_nw_xx<trd_cli_mk_dangerous_signals_not_warped, msg::sub_position_mk, mtk::trd::msg::RQ_XX_MK, mtk::trd::msg::RQ_NW_MK>(pc, buy_sell, rq_pos, account, cli_ref);
}

mtk::CountPtr<trd_cli_ls_dangerous_signals_not_warped>   rq_nw_ls_manual    (const mtk::msg::sub_product_code&   pc, mtk::trd::msg::enBuySell  buy_sell, const msg::sub_position_ls& rq_pos, const std::string& cli_ref, bool agressive)
{
    return rq_nw_xx_manual<trd_cli_ls_dangerous_signals_not_warped, msg::sub_position_ls, mtk::trd::msg::RQ_XX_LS, mtk::trd::msg::RQ_NW_LS>(pc, buy_sell, rq_pos, cli_ref, agressive, get_status_ref().sig_request_hook_ls);
}

mtk::CountPtr<trd_cli_mk_dangerous_signals_not_warped>   rq_nw_mk_manual    (const mtk::msg::sub_product_code&   pc, mtk::trd::msg::enBuySell  buy_sell, const msg::sub_position_mk& rq_pos, const std::string& cli_ref, bool agressive)
{
    return rq_nw_xx_manual<trd_cli_mk_dangerous_signals_not_warped, msg::sub_position_mk, mtk::trd::msg::RQ_XX_MK, mtk::trd::msg::RQ_NW_MK>(pc, buy_sell, rq_pos, cli_ref, agressive, get_status_ref().sig_request_hook_mk);
}



mtk::CountPtr<trd_cli_ls_dangerous_signals_not_warped>   rq_md_ls    ( const msg::sub_order_id& ord_id, const msg::sub_position_ls& rq_pos, const std::string& cli_ref)
{
    return rq_md_xx<trd_cli_ls_dangerous_signals_not_warped, msg::sub_position_ls, mtk::trd::msg::RQ_XX_LS, mtk::trd::msg::RQ_MD_LS, mtk::trd::msg::CF_XX_LS>(ord_id, rq_pos, cli_ref);
}

mtk::CountPtr<trd_cli_mk_dangerous_signals_not_warped>   rq_md_mk    ( const msg::sub_order_id& ord_id, const msg::sub_position_mk& rq_pos, const std::string& cli_ref)
{
    return rq_md_xx<trd_cli_mk_dangerous_signals_not_warped, msg::sub_position_mk, mtk::trd::msg::RQ_XX_MK, mtk::trd::msg::RQ_MD_MK, mtk::trd::msg::CF_XX_MK>(ord_id, rq_pos, cli_ref);
}


mtk::CountPtr<trd_cli_ls_dangerous_signals_not_warped>   rq_md_ls_manual    (const msg::sub_order_id& ord_id)
{
    return rq_md_xx_manual<trd_cli_ls_dangerous_signals_not_warped, msg::sub_position_ls, mtk::trd::msg::RQ_XX_LS, mtk::trd::msg::RQ_MD_LS, mtk::trd::msg::CF_XX_LS>(ord_id, get_status_ref().sig_request_hook_ls);
}

mtk::CountPtr<trd_cli_mk_dangerous_signals_not_warped>   rq_md_mk_manual    (const msg::sub_order_id& ord_id)
{
    return rq_md_xx_manual<trd_cli_mk_dangerous_signals_not_warped, msg::sub_position_mk, mtk::trd::msg::RQ_XX_MK, mtk::trd::msg::RQ_MD_MK, mtk::trd::msg::CF_XX_MK>(ord_id, get_status_ref().sig_request_hook_mk);
}


mtk::CountPtr<trd_cli_ls_dangerous_signals_not_warped>   rq_cc_ls    ( const msg::sub_order_id& ord_id )
{
    return rq_cc_xx<trd_cli_ls_dangerous_signals_not_warped, mtk::trd::msg::RQ_XX_LS, mtk::trd::msg::RQ_CC_LS, mtk::trd::msg::CF_XX_LS>(ord_id);
}

mtk::CountPtr<trd_cli_mk_dangerous_signals_not_warped>   rq_cc_mk    ( const msg::sub_order_id& ord_id )
{
    return rq_cc_xx<trd_cli_mk_dangerous_signals_not_warped, mtk::trd::msg::RQ_XX_MK, mtk::trd::msg::RQ_CC_MK, mtk::trd::msg::CF_XX_MK>(ord_id);
}





void cf_nw_ls(const mtk::trd::msg::CF_NW_LS& cf)
{
    cf_nw_xx<trd_cli_ls_dangerous_signals_not_warped, mtk::trd::msg::CF_NW_LS>(cf);
}
void cf_nw_mk(const mtk::trd::msg::CF_NW_MK& cf)
{
    cf_nw_xx<trd_cli_mk_dangerous_signals_not_warped, mtk::trd::msg::CF_NW_MK>(cf);
}


void cf_md_ls(const mtk::trd::msg::CF_MD_LS& cf)
{
    cf_md_xx<trd_cli_ls_dangerous_signals_not_warped, mtk::trd::msg::CF_MD_LS>(cf);
}

void cf_md_mk(const mtk::trd::msg::CF_MD_MK& cf)
{
    cf_md_xx<trd_cli_mk_dangerous_signals_not_warped, mtk::trd::msg::CF_MD_MK>(cf);
}



void cf_cc_ls(const mtk::trd::msg::CF_CC_LS& cf)
{
    cf_cc_xx<trd_cli_ls_dangerous_signals_not_warped, mtk::trd::msg::CF_CC_LS>(cf);
}

void cf_cc_mk(const mtk::trd::msg::CF_CC_MK& cf)
{
    cf_cc_xx<trd_cli_mk_dangerous_signals_not_warped, mtk::trd::msg::CF_CC_MK>(cf);
}




void rj_nw_ls(const mtk::trd::msg::RJ_NW_LS& rj)
{
    rj_nw_xx<trd_cli_ls_dangerous_signals_not_warped, mtk::trd::msg::RJ_NW_LS>(rj);
}

void rj_nw_mk(const mtk::trd::msg::RJ_NW_MK& rj)
{
    rj_nw_xx<trd_cli_mk_dangerous_signals_not_warped, mtk::trd::msg::RJ_NW_MK>(rj);
}


void rj_md_ls(const mtk::trd::msg::RJ_MD_LS& rj)
{
    rj_md_xx<trd_cli_ls_dangerous_signals_not_warped, mtk::trd::msg::RJ_MD_LS>(rj);
}

void rj_md_mk(const mtk::trd::msg::RJ_MD_MK& rj)
{
    rj_md_xx<trd_cli_mk_dangerous_signals_not_warped, mtk::trd::msg::RJ_MD_MK>(rj);
}

void rj_cc_ls(const mtk::trd::msg::RJ_CC_LS& rj)
{
    rj_cc_xx<trd_cli_ls_dangerous_signals_not_warped, mtk::trd::msg::RJ_CC_LS>(rj);
}

void rj_cc_mk(const mtk::trd::msg::RJ_CC_MK& rj)
{
    rj_cc_xx<trd_cli_mk_dangerous_signals_not_warped, mtk::trd::msg::RJ_CC_MK>(rj);
}

void cf_ex_ls(const mtk::trd::msg::CF_EX_LS& ex)
{
    cf_ex_xx<trd_cli_ls_dangerous_signals_not_warped, mtk::trd::msg::CF_EX_LS>(ex);
}

void cf_ex_mk(const mtk::trd::msg::CF_EX_MK& ex)
{
    cf_ex_xx<trd_cli_mk_dangerous_signals_not_warped, mtk::trd::msg::CF_EX_MK>(ex);
}


void cf_st_ls(const mtk::trd::msg::CF_ST_LS& st)
{
    cf_st_xx<trd_cli_ls_dangerous_signals_not_warped, mtk::trd::msg::CF_ST_LS>(st);
}

void cf_st_mk(const mtk::trd::msg::CF_ST_MK& st)
{
    cf_st_xx<trd_cli_mk_dangerous_signals_not_warped, mtk::trd::msg::CF_ST_MK>(st);
}








en_order_type  get_order_type(const msg::sub_order_id& ord_id)
{
    if(get_status_ref().ls_orders.find(ord_id) !=  get_status_ref().ls_orders.end())
        return ot_limit;
    else if(get_status_ref().mk_orders.find(ord_id) !=  get_status_ref().mk_orders.end())
        return ot_market;
    else
        throw mtk::Alarm(MTK_HERE, "cli_order_book", MTK_SS("missing " << ord_id << " looking order type"), mtk::alPriorCritic, mtk::alTypeNoPermisions);
}










};//    namespace  trd_cli_ord_book {

};   //  namespace mtk
};   //  namespace trd


namespace   //anonymous
{
    void command_stats(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
    {
        response_lines.push_back("cli_order_book_____________________");
        response_lines.push_back(MTK_SS("limit :" <<  mtk::trd::trd_cli_ord_book::get_status_ref().ls_orders.size()));
        response_lines.push_back(MTK_SS("market:" <<  mtk::trd::trd_cli_ord_book::get_status_ref().mk_orders.size()));
    }

}
