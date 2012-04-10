#include "trd_cli_ord_book.h"

#include "components/admin/admin.h"
#include "components/trading/accounts/msg_account_manager.h"
#include "components/trading/accounts/account_manager_cli.h"



namespace {
    const char*   VERSION = "2012-03-12";

    const char*   MODIFICATIONS =
                        "           2011-03-16     first version\n"
                        "           2011-05-13     added market orders\n"
                        "           2012-01-18     added linked executions\n"
                        "           2012-03-12     added stop market orders\n";


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




struct handles_qpid
{
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::CF_EXLK>  > cf_exlk;
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::CF_ST_EX> > cf_st_ex;

    #define  REGISTER_ORDER_TYPE(__OT__, __ot__)  \
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::CF_NW_##__OT__> > cf_nw_##__ot__;    \
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::CF_MD_##__OT__> > cf_md_##__ot__;    \
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::CF_CC_##__OT__> > cf_cc_##__ot__;    \
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::RJ_NW_##__OT__> > rj_nw_##__ot__;    \
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::RJ_MD_##__OT__> > rj_md_##__ot__;    \
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::RJ_CC_##__OT__> > rj_cc_##__ot__;    \
        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::CF_ST_##__OT__> > cf_st_##__ot__;


    REGISTER_ORDER_TYPE(LS, ls);
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::CF_EX_LS> > cf_ex_ls;

    REGISTER_ORDER_TYPE(MK, mk);
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::CF_EX_MK> > cf_ex_mk;

    REGISTER_ORDER_TYPE(SM, sm);
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::CF_TR_SM> > cf_tr_sm;

    REGISTER_ORDER_TYPE(SL, sl);
    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::msg::CF_TR_SL> > cf_tr_sl;


    #undef  REGISTER_ORDER_TYPE
};


struct s_status
{
    mtk::Signal< const mtk::trd::msg::CF_XX&                                     >          sig_triggered;


    //  execs
    mtk::map<t_exec_key, msg::CF_EXLK>                                                      map_execs;
    mtk::list<t_exec_key>                                                                   list_execs_time_order;
    mtk::map<t_exec_key, msg::CF_EXLK>                                                      map_orphan_execs;
    mtk::Signal< const mtk::trd::msg::CF_XX&, const mtk::trd::msg::sub_exec_conf&>          sig_execution_RT;
    mtk::Signal< const mtk::trd::msg::CF_XX&, const mtk::trd::msg::sub_exec_conf&>          sig_execution_NON_RT;

    //  ls
    mtk::map<msg::sub_order_id, mtk::CountPtr<trd_cli_ls_dangerous_signals_not_warped> >     ls_orders;

    mtk::Signal< const mtk::trd::msg::sub_order_id&, mtk::CountPtr<trd_cli_ls_dangerous_signals_not_warped>&  >     sig_order_ls_new;
    mtk::Signal< mtk::trd::msg::RQ_XX_LS&, bool& /*canceled*/, bool  /*aggre*/   >                                  sig_request_hook_ls;


    //  mk
    mtk::map<msg::sub_order_id, mtk::CountPtr<trd_cli_mk_dangerous_signals_not_warped> >     mk_orders;

    mtk::Signal< const mtk::trd::msg::sub_order_id&, mtk::CountPtr<trd_cli_mk_dangerous_signals_not_warped>&  >     sig_order_mk_new;
    mtk::Signal< mtk::trd::msg::RQ_XX_MK&, bool& /*canceled*/, bool  /*aggre*/   >          sig_request_hook_mk;


    //  sm
    mtk::map<msg::sub_order_id, mtk::CountPtr<trd_cli_sm_dangerous_signals_not_warped> >     sm_orders;

    mtk::Signal< const mtk::trd::msg::sub_order_id&, mtk::CountPtr<trd_cli_sm_dangerous_signals_not_warped>&  >     sig_order_sm_new;
    mtk::Signal< mtk::trd::msg::RQ_XX_SM&, bool& /*canceled*/, bool  /*aggre*/   >          sig_request_hook_sm;


    //  sl
    mtk::map<msg::sub_order_id, mtk::CountPtr<trd_cli_sl_dangerous_signals_not_warped> >     sl_orders;

    mtk::Signal< const mtk::trd::msg::sub_order_id&, mtk::CountPtr<trd_cli_sl_dangerous_signals_not_warped>&  >     sig_order_sl_new;
    mtk::Signal< mtk::trd::msg::RQ_XX_SL&, bool& /*canceled*/, bool  /*aggre*/   >          sig_request_hook_sl;
};




s_status* __internal_ptr_status=0;
bool      deleted=false;



void cf_exlk (const mtk::trd::msg::CF_EXLK&  exlk);
void cf_st_ex(const mtk::trd::msg::CF_ST_EX& st_ex);



#define  REGISTER_ORDER_TYPE(__OT__, __ot__)  \
    void cf_nw_##__ot__(const mtk::trd::msg::CF_NW_##__OT__& cf);  \
    void cf_md_##__ot__(const mtk::trd::msg::CF_MD_##__OT__& cf);  \
    void cf_cc_##__ot__(const mtk::trd::msg::CF_CC_##__OT__& cf);  \
    void rj_nw_##__ot__(const mtk::trd::msg::RJ_NW_##__OT__& rj);  \
    void rj_md_##__ot__(const mtk::trd::msg::RJ_MD_##__OT__& rj);  \
    void rj_cc_##__ot__(const mtk::trd::msg::RJ_CC_##__OT__& rj);  \
    void cf_st_##__ot__(const mtk::trd::msg::CF_ST_##__OT__& st);


REGISTER_ORDER_TYPE(LS, ls);
void cf_ex_ls(const mtk::trd::msg::CF_EX_LS& ex);

REGISTER_ORDER_TYPE(MK, mk);
void cf_ex_mk(const mtk::trd::msg::CF_EX_MK& ex);


REGISTER_ORDER_TYPE(SM, sm);
void cf_tr_sm(const mtk::trd::msg::CF_TR_SM& tr);

REGISTER_ORDER_TYPE(SL, sl);
void cf_tr_sl(const mtk::trd::msg::CF_TR_SL& tr);





#undef REGISTER_ORDER_TYPE


    void   init (void)
    {
        //  listen for new accounts
            //mtk::CountPtr<mtk::Signal<const mtk::trd::account::msg::sub_grant&> >           get_signal_new_grant_received(void);
        mtk::accmgrcli::get_signal_new_grant_received()->connect(orders_susbcription_for_account);


        static  mtk::CountPtr< handles_qpid >   handles;
        if(handles.isValid() == false)
            handles = mtk::make_cptr( new handles_qpid );

        #define  REGISTER_ORDER_TYPE(__OT__, __ot__)  \
                        MTK_QPID_RECEIVER_CONNECT_F(  \
                                                handles->cf_st_##__ot__,  \
                                                mtk::admin::get_url("client"),  \
                                                mtk::trd::msg::CF_ST_##__OT__::get_in_subject(client_code, session_id),  \
                                                mtk::trd::msg::CF_ST_##__OT__,  \
                                                cf_st_##__ot__)


                std::string  client_code = mtk::admin::get_process_info().location.broker_code;
                if(client_code == "CIMD")
                    client_code = "*";
                std::string  session_id  = mtk::admin::get_session_id();
                REGISTER_ORDER_TYPE(LS, ls);
                REGISTER_ORDER_TYPE(MK, mk);
                REGISTER_ORDER_TYPE(SM, sm);
                REGISTER_ORDER_TYPE(SL, sl);

        #undef  REGISTER_ORDER_TYPE


        MTK_QPID_RECEIVER_CONNECT_F(
                                handles->cf_st_ex,
                                mtk::admin::get_url("client"),
                                mtk::trd::msg::CF_ST_EX::get_in_subject(client_code, session_id),
                                mtk::trd::msg::CF_ST_EX,
                                cf_st_ex)
    }




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



            std::string process_client_code = mtk::admin::get_process_info().location.broker_code;
            //if(broker_code == "CIMD")           broker_code = "*";
            if(process_client_code != "CIMD"  &&  process_client_code !=  grant.key.account.client_code)
                throw mtk::Alarm(MTK_HERE, "ord_book", MTK_SS("client code is not cimd and client account is diferent to client code "
                                        << process_client_code << "  !=  "  << grant.key.account.client_code), mtk::alPriorCritic, mtk::alTypeLogicError);

            std::string broker_code = grant.key.account.client_code;
            std::string market = grant.key.market;
            std::string account_name = grant.key.account.name;
            std::string session_id = mtk::admin::get_session_id();


            MTK_QPID_RECEIVER_CONNECT_F(
                                    handles.cf_exlk,
                                    mtk::admin::get_url("client"),
                                    mtk::trd::msg::CF_EXLK::get_in_subject(broker_code, market, account_name),
                                    mtk::trd::msg::CF_EXLK,
                                    cf_exlk)


            #define  REGISTER_ORDER_TYPE(__OT__, __ot__)  \
                MTK_QPID_RECEIVER_CONNECT_F(  \
                                        handles.cf_nw_##__ot__,  \
                                        mtk::admin::get_url("client"),  \
                                        mtk::trd::msg::CF_NW_##__OT__::get_in_subject(broker_code, market, account_name),  \
                                        mtk::trd::msg::CF_NW_##__OT__,  \
                                        cf_nw_##__ot__)  \
                MTK_QPID_RECEIVER_CONNECT_F(  \
                                        handles.cf_md_##__ot__,  \
                                        mtk::admin::get_url("client"),  \
                                        mtk::trd::msg::CF_MD_##__OT__::get_in_subject(broker_code, market, account_name),  \
                                        mtk::trd::msg::CF_MD_##__OT__,  \
                                        cf_md_##__ot__)  \
                MTK_QPID_RECEIVER_CONNECT_F(  \
                                        handles.cf_cc_##__ot__,  \
                                        mtk::admin::get_url("client"),  \
                                        mtk::trd::msg::CF_CC_##__OT__::get_in_subject(broker_code, market, account_name),  \
                                        mtk::trd::msg::CF_CC_##__OT__,  \
                                        cf_cc_##__ot__)  \
                MTK_QPID_RECEIVER_CONNECT_F(  \
                                        handles.rj_nw_##__ot__,  \
                                        mtk::admin::get_url("client"),  \
                                        mtk::trd::msg::RJ_NW_##__OT__::get_in_subject(broker_code, market, account_name),  \
                                        mtk::trd::msg::RJ_NW_##__OT__,  \
                                        rj_nw_##__ot__)  \
                MTK_QPID_RECEIVER_CONNECT_F(  \
                                        handles.rj_md_##__ot__,  \
                                        mtk::admin::get_url("client"),  \
                                        mtk::trd::msg::RJ_MD_##__OT__::get_in_subject(broker_code, market, account_name),  \
                                        mtk::trd::msg::RJ_MD_##__OT__,  \
                                        rj_md_##__ot__)  \
                MTK_QPID_RECEIVER_CONNECT_F(  \
                                        handles.rj_cc_##__ot__,  \
                                        mtk::admin::get_url("client"),  \
                                        mtk::trd::msg::RJ_CC_##__OT__::get_in_subject(broker_code, market, account_name),  \
                                        mtk::trd::msg::RJ_CC_##__OT__,  \
                                        rj_cc_##__ot__)  \


            REGISTER_ORDER_TYPE(LS, ls);
            REGISTER_ORDER_TYPE(MK, mk);
            REGISTER_ORDER_TYPE(SM, sm);
            REGISTER_ORDER_TYPE(SL, sl);

            #undef  REGISTER_ORDER_TYPE

            MTK_QPID_RECEIVER_CONNECT_F(
                                    handles.cf_ex_ls,
                                    mtk::admin::get_url("client"),
                                    mtk::trd::msg::CF_EX_LS::get_in_subject(broker_code, market, account_name),
                                    mtk::trd::msg::CF_EX_LS,
                                    cf_ex_ls)

            MTK_QPID_RECEIVER_CONNECT_F(
                                    handles.cf_ex_mk,
                                    mtk::admin::get_url("client"),
                                    mtk::trd::msg::CF_EX_MK::get_in_subject(broker_code, market, account_name),
                                    mtk::trd::msg::CF_EX_MK,
                                    cf_ex_mk)

            MTK_QPID_RECEIVER_CONNECT_F(
                                    handles.cf_tr_sm,
                                    mtk::admin::get_url("client"),
                                    mtk::trd::msg::CF_TR_SM::get_in_subject(broker_code, market, account_name),
                                    mtk::trd::msg::CF_TR_SM,
                                    cf_tr_sm)

            MTK_QPID_RECEIVER_CONNECT_F(
                                    handles.cf_tr_sl,
                                    mtk::admin::get_url("client"),
                                    mtk::trd::msg::CF_TR_SL::get_in_subject(broker_code, market, account_name),
                                    mtk::trd::msg::CF_TR_SL,
                                    cf_tr_sl)



            mtk::msg::sub_request_info  ri = mtk::admin::get_request_info();
            mtk::trd::msg::RQ_ORDERS_STATUS  msg_rq_order_status(ri, grant.key.market, grant.key.account);
            mtk::send_message_with_sender(mtk::admin::get_qpid_sender("client", msg_rq_order_status.get_qpid_address()), msg_rq_order_status);
}



void check_orphans(void);

s_status& get_status_ref(void)
{
    if (deleted)    throw mtk::Alarm(MTK_HERE, "trd_cli_ord_book", "on deleted module", mtk::alPriorWarning, mtk::alTypeNoPermisions);
    if (__internal_ptr_status==0)
    {
        
        __internal_ptr_status = new s_status();
        MTK_TIMER_1SF(check_orphans);

    }
    return *__internal_ptr_status;
}




template<typename T>
void send_request_message(const T& rq)
{
    mtk_send_message("client", rq);
}



mtk::Signal< const mtk::trd::msg::sub_order_id&, mtk::CountPtr<trd_cli_ls_dangerous_signals_not_warped>&  >& get_sig_order_ls_new    (void)
{
    return get_status_ref().sig_order_ls_new;
}

mtk::Signal< const mtk::trd::msg::sub_order_id&, mtk::CountPtr<trd_cli_mk_dangerous_signals_not_warped>&  >& get_sig_order_mk_new    (void)
{
    return get_status_ref().sig_order_mk_new;
}

mtk::Signal< const mtk::trd::msg::sub_order_id&, mtk::CountPtr<trd_cli_sm_dangerous_signals_not_warped>&  >& get_sig_order_sm_new    (void)
{
    return get_status_ref().sig_order_sm_new;
}

mtk::Signal< const mtk::trd::msg::sub_order_id&, mtk::CountPtr<trd_cli_sl_dangerous_signals_not_warped>&  >& get_sig_order_sl_new    (void)
{
    return get_status_ref().sig_order_sl_new;
}


mtk::Signal< const mtk::trd::msg::CF_XX&, const mtk::trd::msg::sub_exec_conf& >& get_sig_execution_RT       (void)
{
    return get_status_ref().sig_execution_RT;
}

mtk::Signal< const mtk::trd::msg::CF_XX&, const mtk::trd::msg::sub_exec_conf& >& get_sig_execution_NON_RT   (void)
{
    return get_status_ref().sig_execution_NON_RT;
}


mtk::Signal< const mtk::trd::msg::CF_XX& >& get_sig_triggered       (void)
{
    return get_status_ref().sig_triggered;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//      register executions

bool  register_execution__and_check_if_duplicated(const msg::CF_EXLK&   exlk)
{
    //    mtk::map<t_exec_key, msg::CF_ST_EX>                                                     map_execs;
    //    mtk::Signal< const mtk::trd::msg::CF_XX&, const mtk::trd::msg::sub_exec_conf&>          sig_execution_RT;
    //    mtk::Signal< const mtk::trd::msg::CF_XX&, const mtk::trd::msg::sub_exec_conf&>          sig_execution_NON_RT;

    t_exec_key  exec_key = get_exec_key(exlk);
    auto it = get_status_ref().map_execs.find(exec_key);
    if(it != get_status_ref().map_execs.end())
    {
        if(exlk.executed_pos != it->second.executed_pos)
        {
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "trd_cli_ord_book::register_execution",
                        MTK_SS("received duplicated execution with diferent info" << std::endl
                        << "This execution is ignored" << std::endl << exlk << "  \n  " <<  it->second.executed_pos),
                        mtk::alPriorCritic));
        }
        else
        {
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "trd_cli_ord_book::register_execution",
                        MTK_SS("received duplicated execution with same value " << std::endl
                        << "duplicated ignored" << std::endl
                        << "This could not be an error, but it's look weird. Check it." << std::endl
                        << exlk << std::endl <<  it->second.executed_pos),
                        mtk::alPriorError));
        }
        return true;
    }
    else
    {
        get_status_ref().map_execs.insert(std::make_pair(exec_key, exlk)).first;
        //  insert in order
        if(get_status_ref().list_execs_time_order.size() == 0)
        {
            get_status_ref().list_execs_time_order.push_front(exec_key);
        }
        else
        {
            auto it_ex_ord = get_status_ref().list_execs_time_order.begin();
            while(it_ex_ord != get_status_ref().list_execs_time_order.end())
            {
                auto it_exec = get_status_ref().map_execs.find(*it_ex_ord);
                if(it_exec == get_status_ref().map_execs.end())
                {
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "trd_cli_ord_book::register_execution",
                                MTK_SS("execution not registered in  map_execs" << std::endl
                                << *it_ex_ord),
                                mtk::alPriorCritic));
                }
                else
                {
                    if( it_exec->second.orig_control_fluct.datetime > exlk.orig_control_fluct.datetime)
                    {
                        get_status_ref().list_execs_time_order.insert(it_ex_ord, exec_key);
                        break;  //      <<-------------
                    }
                }
                ++it_ex_ord;           //      <<-------------
            }
            if(it_ex_ord == get_status_ref().list_execs_time_order.end())
            {
                get_status_ref().list_execs_time_order.push_back(exec_key);
            }
        }
        return false;
    }
}


bool  register_exec_in_order(const msg::CF_EXLK& cf_exlk);

template<typename MAP_ORDERS>       //  i.e.   mtk::map<msg::sub_order_id, mtk::CountPtr<trd_cli_ls_dangerous_signals_not_warped> >
int   get_sum_execs_orders(const MAP_ORDERS& map_orders)
{
    int sum_execs_orders_quantity=0;
    {
        for(auto it=map_orders.begin(); it!=map_orders.end(); ++it)
        {
            mtk::CountPtr<mtk::trd::hist::order_EXECS_historic_dangerous_not_signal_warped>  execs = it->second->executions();
            mtk::CountPtr<mtk::list<mtk::trd::hist::order_exec_item> > list_execs = execs->get_items_list();
            for(auto it2=list_execs->begin(); it2!=list_execs->end(); ++it2)
            {
                sum_execs_orders_quantity += it2->exec_info.quantity.GetIntCode();
            }
        }
    }
    return sum_execs_orders_quantity;
}
void check_orphans(void)
{
    MTK_EXEC_MAX_FREC_NO_FIRST_S(mtk::dtSeconds(30))
        auto it=get_status_ref().map_orphan_execs.begin();
        while(it!=get_status_ref().map_orphan_execs.end())
        {
            if(register_exec_in_order(it->second))
                it = get_status_ref().map_orphan_execs.erase(it);
            else
                ++it;
        }
    MTK_END_EXEC_MAX_FREC
    
    MTK_EXEC_MAX_FREC_NO_FIRST_S(mtk::dtMinutes(3))
        if (get_status_ref().map_orphan_execs.size() >0)
        {
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "checking",
                        "There are orphans execs. It could be an error",
                        mtk::alPriorError));
            return;
        }

        int sum_execs_quantity = 0;
        {
            for (auto it = get_status_ref().map_execs.begin(); it != get_status_ref().map_execs.end(); ++it)
            {
                sum_execs_quantity += it->second.executed_pos.quantity.GetIntCode();
            }
        }
        
        int sum_execs_orders_quantity=0;
        sum_execs_orders_quantity += get_sum_execs_orders(get_status_ref().ls_orders);
        sum_execs_orders_quantity += get_sum_execs_orders(get_status_ref().mk_orders);

        if (sum_execs_orders_quantity != sum_execs_quantity)
        {
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "checking",
                        MTK_SS("sum_execs_orders_quantity != sum_execs_quantity   " << sum_execs_orders_quantity << " != " << sum_execs_quantity),
                        mtk::alPriorCritic));
            return;
        }

    MTK_END_EXEC_MAX_FREC
}

void save_orphan_exec(const msg::CF_EXLK&   exlk)
{
    t_exec_key  exec_key = get_exec_key(exlk);
    auto it = get_status_ref().map_orphan_execs.find(exec_key);
    if(it != get_status_ref().map_orphan_execs.end())
    {
        if(exlk.executed_pos != it->second.executed_pos)
        {
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "trd_cli_ord_book::register_execution",
                        MTK_SS("(orphan) received duplicated execution with diferent info" << std::endl
                        << "This execution is ignored" << std::endl << exlk << "  \n  " <<  it->second.executed_pos),
                        mtk::alPriorCritic));
        }
        else
        {
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "trd_cli_ord_book::register_execution",
                        MTK_SS("(orphan)received duplicated execution with same value " << std::endl
                        << "duplicated ignored" << std::endl
                        << "This could not be an error, but it's look weird. Check it." << std::endl
                        << exlk << std::endl <<  it->second.executed_pos),
                        mtk::alPriorError));
        }
    }
    else
    {
        get_status_ref().map_orphan_execs.insert(std::make_pair(exec_key, exlk));
    }
}

//      register executions
//////////////////////////////////////////////////////////////////////////////////////////////////////////


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

template<>
mtk::CountPtr<trd_cli_sm_dangerous_signals_not_warped>  get_order<trd_cli_sm_dangerous_signals_not_warped>(const mtk::trd::msg::sub_order_id& ord_id)
{
    return get_order_withmapandsignal<trd_cli_sm_dangerous_signals_not_warped>(ord_id, get_status_ref().sm_orders, get_status_ref().sig_order_sm_new);
}

template<>
mtk::CountPtr<trd_cli_sl_dangerous_signals_not_warped>  get_order<trd_cli_sl_dangerous_signals_not_warped>(const mtk::trd::msg::sub_order_id& ord_id)
{
    return get_order_withmapandsignal<trd_cli_sl_dangerous_signals_not_warped>(ord_id, get_status_ref().sl_orders, get_status_ref().sig_order_sl_new);
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

mtk::CountPtr<trd_cli_sm>          get_order_sm        (const msg::sub_order_id& ord_id)
{
    return  mtk::make_cptr(new trd_cli_sm(get_order<trd_cli_sm_dangerous_signals_not_warped>(ord_id)));
}

mtk::CountPtr<trd_cli_sl>          get_order_sl        (const msg::sub_order_id& ord_id)
{
    return  mtk::make_cptr(new trd_cli_sl(get_order<trd_cli_sl_dangerous_signals_not_warped>(ord_id)));
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


    //mtk::map<msg::sub_order_id, mtk::CountPtr<trd_cli_sm_dangerous_signals_not_warped> >     sm_orders;
    for(mtk::map<msg::sub_order_id, mtk::CountPtr<trd_cli_sm_dangerous_signals_not_warped> >::const_iterator it = __internal_ptr_status->sm_orders.begin(); it!=__internal_ptr_status->sm_orders.end(); ++it)
        result.push_back(it->first);

    //mtk::map<msg::sub_order_id, mtk::CountPtr<trd_cli_sl_dangerous_signals_not_warped> >     sl_orders;
    for(mtk::map<msg::sub_order_id, mtk::CountPtr<trd_cli_sl_dangerous_signals_not_warped> >::const_iterator it = __internal_ptr_status->sl_orders.begin(); it!=__internal_ptr_status->sl_orders.end(); ++it)
        result.push_back(it->first);


    return result;
}

mtk::list<mtk::trd::msg::CF_EXLK>           get_all_execs           (void)
{
    mtk::list<mtk::trd::msg::CF_EXLK>  result;
    if(__internal_ptr_status == 0)        return result;
    
    for(auto it=__internal_ptr_status->list_execs_time_order.begin(); it!=__internal_ptr_status->list_execs_time_order.end(); ++it)
    {
        auto it_map_exec = __internal_ptr_status->map_execs.find(*it);
        if(it_map_exec!=__internal_ptr_status->map_execs.end())
            result.push_back(it_map_exec->second);
        else
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "trd_cli_ord_book", MTK_SS("exec in list_execs_time_order not in map_execs  " << *it), mtk::alPriorCritic));
    }
    
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

mtk::Signal< mtk::trd::msg::RQ_XX_SM&, bool&, bool    >&  get_signal_request_hook_sm         (void)
{
    return get_status_ref().sig_request_hook_sm;
}

mtk::Signal< mtk::trd::msg::RQ_XX_SL&, bool&, bool    >&  get_signal_request_hook_sl         (void)
{
    return get_status_ref().sig_request_hook_sl;
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
                                                        const mtk::trd::msg::sub_account_info& account)
{
    mtk::msg::sub_request_info  rq_info = mtk::admin::get_request_info();

    mtk::trd::msg::sub_order_id ord_id (rq_info.req_id);

    mtk::CountPtr<ORDER_TYPE> order = get_order<ORDER_TYPE>(ord_id);


    mtk::trd::msg::sub_invariant_order_info  invariant  (ord_id, pc, buy_sell, account, "DAY", false);
    mtk::trd::msg::RQ_XX                     rqxx       (invariant, rq_info, mtk::admin::get_control_fluct_info());
    REQUEST_TYPE                             rqxxxx     (rqxx, rq_pos);

    REQUEST_TYPE_ORDER_TYPE                  rq         (rqxxxx);

    order->rq_nw(rq);
    return order;
}



template<typename ORDER_TYPE, typename  POS_TYPE,  typename REQUEST_TYPE, typename REQUEST_TYPE_ORDER_TYPE>
mtk::CountPtr<ORDER_TYPE>   rq_nw_xx_manual    (        const mtk::msg::sub_product_code&   pc,
                                                        const mtk::trd::msg::enBuySell      buy_sell,
                                                        const POS_TYPE& rq_pos,
                                                        bool agressive,
                                                        mtk::Signal< REQUEST_TYPE&, bool& /*canceled*/, bool  /*aggre*/   >& signal_hook
                                                        )
{
    mtk::msg::sub_request_info  rq_info = mtk::admin::get_request_info();
    mtk::trd::msg::sub_order_id ord_id (rq_info.req_id);

    mtk::trd::msg::sub_account_info          account    ("", "");
    mtk::trd::msg::sub_invariant_order_info  invariant  (ord_id, pc, buy_sell, account, "DAY", false);
    mtk::trd::msg::RQ_XX                     rqxx       (invariant, rq_info, mtk::admin::get_control_fluct_info());
    REQUEST_TYPE                             rqxxtp     (rqxx, rq_pos);

    REQUEST_TYPE_ORDER_TYPE                  rq         (rqxxtp);


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

        mtk::trd::msg::RQ_XX        rqxx       (lc.invariant, mtk::admin::get_request_info(), mtk::admin::get_control_fluct_info());
        REQUEST_TYPE                rqxxls     (rqxx, lc.market_pos);

        return rqxxls;
    }
   else
        throw mtk::Alarm(MTK_HERE, "trd_cli_ord_book", "not pending request, not confirmated order???", mtk::alPriorCritic, mtk::alTypeNoPermisions);
}


template<typename ORDER_TYPE, typename  POS_TYPE,  typename REQUEST_TYPE, typename REQUEST_TYPE_ORDER_TYPE, typename  CONF_TYPE>
mtk::CountPtr<ORDER_TYPE>   rq_md_xx    ( const msg::sub_order_id& ord_id, const POS_TYPE& rq_pos)
{
    mtk::CountPtr<ORDER_TYPE> order = get_order<ORDER_TYPE>(ord_id);
    REQUEST_TYPE rq = get_new_request_from_last_request_or_build_from_confirmation<ORDER_TYPE, REQUEST_TYPE, CONF_TYPE>(order);
    rq.request_pos = rq_pos;
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

    static auto   session_id  =  mtk::admin::get_session_id();
    if(rj.req_id.session_id  ==  session_id)
    {
        mtk::CountPtr<ORDER_TYPE>  order = get_order<ORDER_TYPE>(rj.invariant.order_id);
        order->rj_nw(rj);
    }
}

template<typename ORDER_TYPE, typename  REJECT_TYPE>
void rj_md_xx(const REJECT_TYPE& rj)
{
    mtk::admin::check_control_fluct( rj.orig_control_fluct);

    static auto   session_id  =  mtk::admin::get_session_id();
    if(rj.req_id.session_id  ==  session_id)
    {
        mtk::CountPtr<ORDER_TYPE>  order = get_order<ORDER_TYPE>(rj.invariant.order_id);
        order->rj_md(rj);
    }
}

template<typename ORDER_TYPE, typename  REJECT_TYPE>
void rj_cc_xx(const REJECT_TYPE& rj)
{
    mtk::admin::check_control_fluct( rj.orig_control_fluct);

    static auto   session_id  =  mtk::admin::get_session_id();
    if(rj.req_id.session_id  ==  session_id)
    {
        mtk::CountPtr<ORDER_TYPE>  order = get_order<ORDER_TYPE>(rj.invariant.order_id);
        order->rj_cc(rj);
    }
}


template<typename ORDER_TYPE, typename  CONF_TYPE>
void cf_st_xx(const CONF_TYPE& cf)
{
    mtk::CountPtr<ORDER_TYPE>  order = get_order<ORDER_TYPE>(cf.invariant.order_id);
    order->cf_st(cf);
}




template<typename ORDER_TYPE, typename  EXEC_TYPE>
void cf_ex_xx(const EXEC_TYPE& ex)
{
    mtk::admin::check_control_fluct(ex.orig_control_fluct);

    mtk::trd::msg::CF_EXLK  cf_exlk {ex, ex.executed_pos};
    if(register_execution__and_check_if_duplicated(cf_exlk) == false)      //  == false means not duplicated
    {
        mtk::CountPtr<ORDER_TYPE>  order = get_order<ORDER_TYPE>(ex.invariant.order_id);
        order->cf_ex(ex);

        get_status_ref().sig_execution_RT.emit(ex, ex.executed_pos);
    }
}


template<typename ORDER_TYPE, typename  TR_TYPE>
void cf_tr_xx(const TR_TYPE& tr)
{
    mtk::admin::check_control_fluct(tr.orig_control_fluct);

    mtk::CountPtr<ORDER_TYPE>  order = get_order<ORDER_TYPE>(tr.invariant.order_id);
    order->cf_tr(tr);

    get_status_ref().sig_triggered.emit(tr);
}





//      generic support
//////////////////////////////////////////////////////////////////////////////////////////////////////////



#define  MACRO_CONCAT(__BLAH__, __TO_CONTAT__)   __BLAH__##__TO_CONTAT__
#define  REGISTER_ORDER_TYPE(__OT__, __ot__)  \
        mtk::CountPtr<MACRO_CONCAT(trd_cli_##__ot__,_dangerous_signals_not_warped)>   rq_nw_##__ot__        (const mtk::msg::sub_product_code&   pc, mtk::trd::msg::enBuySell  buy_sell, const msg::sub_position_##__ot__& rq_pos, const mtk::trd::msg::sub_account_info& account)  \
        {  \
            return rq_nw_xx<MACRO_CONCAT(trd_cli_##__ot__,_dangerous_signals_not_warped), msg::sub_position_##__ot__, mtk::trd::msg::RQ_XX_##__OT__, mtk::trd::msg::RQ_NW_##__OT__>(pc, buy_sell, rq_pos, account);  \
        }  \
        mtk::CountPtr<MACRO_CONCAT(trd_cli_##__ot__,_dangerous_signals_not_warped)>   MACRO_CONCAT(rq_nw_##__ot__,_manual)    (const mtk::msg::sub_product_code&   pc, mtk::trd::msg::enBuySell  buy_sell, const msg::sub_position_##__ot__& rq_pos, bool agressive)  \
        {  \
            return rq_nw_xx_manual<MACRO_CONCAT(trd_cli_##__ot__,_dangerous_signals_not_warped), msg::sub_position_##__ot__, mtk::trd::msg::RQ_XX_##__OT__, mtk::trd::msg::RQ_NW_##__OT__>(pc, buy_sell, rq_pos, agressive, get_status_ref().sig_request_hook_##__ot__);  \
        }  \
        mtk::CountPtr<MACRO_CONCAT(trd_cli_##__ot__,_dangerous_signals_not_warped)>   rq_md_##__ot__    ( const msg::sub_order_id& ord_id, const msg::sub_position_##__ot__& rq_pos)  \
        {  \
            return rq_md_xx<MACRO_CONCAT(trd_cli_##__ot__,_dangerous_signals_not_warped), msg::sub_position_##__ot__, mtk::trd::msg::RQ_XX_##__OT__, mtk::trd::msg::RQ_MD_##__OT__, mtk::trd::msg::CF_XX_##__OT__>(ord_id, rq_pos);  \
        }  \
        mtk::CountPtr<MACRO_CONCAT(trd_cli_##__ot__,_dangerous_signals_not_warped)>   MACRO_CONCAT(rq_md_##__ot__,_manual)    (const msg::sub_order_id& ord_id)  \
        {  \
            return rq_md_xx_manual<MACRO_CONCAT(trd_cli_##__ot__,_dangerous_signals_not_warped), msg::sub_position_##__ot__, mtk::trd::msg::RQ_XX_##__OT__, mtk::trd::msg::RQ_MD_##__OT__, mtk::trd::msg::CF_XX_##__OT__>(ord_id, get_status_ref().sig_request_hook_##__ot__);  \
        }  \
        mtk::CountPtr<MACRO_CONCAT(trd_cli_##__ot__,_dangerous_signals_not_warped)>   rq_cc_##__ot__    ( const msg::sub_order_id& ord_id )  \
        {  \
            return rq_cc_xx<MACRO_CONCAT(trd_cli_##__ot__,_dangerous_signals_not_warped), mtk::trd::msg::RQ_XX_##__OT__, mtk::trd::msg::RQ_CC_##__OT__, mtk::trd::msg::CF_XX_##__OT__>(ord_id);  \
        }  \
        void cf_nw_##__ot__(const mtk::trd::msg::CF_NW_##__OT__& cf)   \
        {   \
            cf_nw_xx<MACRO_CONCAT(trd_cli_##__ot__,_dangerous_signals_not_warped), mtk::trd::msg::CF_NW_##__OT__>(cf);   \
        }   \
        void cf_md_##__ot__(const mtk::trd::msg::CF_MD_##__OT__& cf)   \
        {   \
            cf_md_xx<MACRO_CONCAT(trd_cli_##__ot__,_dangerous_signals_not_warped), mtk::trd::msg::CF_MD_##__OT__>(cf);   \
        }   \
        void cf_cc_##__ot__(const mtk::trd::msg::CF_CC_##__OT__& cf)   \
        {   \
            cf_cc_xx<MACRO_CONCAT(trd_cli_##__ot__,_dangerous_signals_not_warped), mtk::trd::msg::CF_CC_##__OT__>(cf);   \
        }   \
        void rj_nw_##__ot__(const mtk::trd::msg::RJ_NW_##__OT__& rj)   \
        {   \
            rj_nw_xx<MACRO_CONCAT(trd_cli_##__ot__,_dangerous_signals_not_warped), mtk::trd::msg::RJ_NW_##__OT__>(rj);   \
        }   \
        void rj_md_##__ot__(const mtk::trd::msg::RJ_MD_##__OT__& rj)   \
        {   \
            rj_md_xx<MACRO_CONCAT(trd_cli_##__ot__,_dangerous_signals_not_warped), mtk::trd::msg::RJ_MD_##__OT__>(rj);   \
        }   \
        void rj_cc_##__ot__(const mtk::trd::msg::RJ_CC_##__OT__& rj)   \
        {   \
            rj_cc_xx<MACRO_CONCAT(trd_cli_##__ot__,_dangerous_signals_not_warped), mtk::trd::msg::RJ_CC_##__OT__>(rj);   \
        }   \
        void cf_st_##__ot__(const mtk::trd::msg::CF_ST_##__OT__& st)   \
        {   \
            cf_st_xx<MACRO_CONCAT(trd_cli_##__ot__,_dangerous_signals_not_warped), mtk::trd::msg::CF_ST_##__OT__>(st);   \
        }   \





REGISTER_ORDER_TYPE(LS, ls);
REGISTER_ORDER_TYPE(MK, mk);
REGISTER_ORDER_TYPE(SM, sm);
REGISTER_ORDER_TYPE(SL, sl);


#undef   REGISTER_ORDER_TYPE
#undef   MACRO_CONCAT








void cf_exlk(const mtk::trd::msg::CF_EXLK& exlk)
{
    //  mtk::admin::check_control_fluct(exlk.orig_control_fluct);  lk and loading execs are not real time messages

    if(register_execution__and_check_if_duplicated(exlk) == false)      //  == false means not duplicated
    {
        if(!register_exec_in_order(exlk))
            save_orphan_exec(exlk);
    }
}

void cf_st_ex(const mtk::trd::msg::CF_ST_EX&  cf_st_ex)
{
    cf_exlk(cf_st_ex);
}




void cf_ex_ls(const mtk::trd::msg::CF_EX_LS& ex)
{
    cf_ex_xx<trd_cli_ls_dangerous_signals_not_warped, mtk::trd::msg::CF_EX_LS>(ex);
}

void cf_ex_mk(const mtk::trd::msg::CF_EX_MK& ex)
{
    cf_ex_xx<trd_cli_mk_dangerous_signals_not_warped, mtk::trd::msg::CF_EX_MK>(ex);
}



void cf_tr_sm(const mtk::trd::msg::CF_TR_SM& tr)
{
    cf_tr_xx<trd_cli_sm_dangerous_signals_not_warped, mtk::trd::msg::CF_TR_SM>(tr);


    mtk::CountPtr<mtk::trd::trd_cli_mk>  order = get_order_mk(tr.invariant.order_id);
    mtk::msg::sub_gen_response_location  fake_resonse_location(admin::get_session_id(), admin::get_process_info().location.broker_code);
    mtk::trd::msg::sub_position_mk       position_mk(tr.market_pos.quantity, tr.market_pos.cli_ref);
    mtk::trd::msg::CF_XX_MK              cf_xx_mk(mtk::trd::msg::CF_XX(tr), position_mk);
    mtk::trd::msg::CF_ST_MK              cf_st_mk(cf_xx_mk, fake_resonse_location);

    order->cf_hist(get_order_sm(tr.invariant.order_id)->history());
    order->cf_st(cf_st_mk);
}


void cf_tr_sl(const mtk::trd::msg::CF_TR_SL& tr)
{
    cf_tr_xx<trd_cli_sl_dangerous_signals_not_warped, mtk::trd::msg::CF_TR_SL>(tr);


    mtk::CountPtr<mtk::trd::trd_cli_ls>  order = get_order_ls(tr.invariant.order_id);
    mtk::msg::sub_gen_response_location  fake_resonse_location(admin::get_session_id(), admin::get_process_info().location.broker_code);
    mtk::trd::msg::sub_position_ls       position_ls(tr.market_pos.price, tr.market_pos.quantity, tr.market_pos.cli_ref);
    mtk::trd::msg::CF_XX_LS              cf_xx_ls(mtk::trd::msg::CF_XX(tr), position_ls);
    mtk::trd::msg::CF_ST_LS              cf_st_ls(cf_xx_ls, fake_resonse_location);

    order->cf_hist(get_order_sl(tr.invariant.order_id)->history());
    order->cf_st(cf_st_ls);
}






bool  register_exec_in_order(const msg::CF_EXLK& cf_exlk)
{
    
    if(get_status_ref().ls_orders.find(cf_exlk.invariant.order_id) !=  get_status_ref().ls_orders.end())
    {
        auto  order = get_order_ls(cf_exlk.invariant.order_id);
        order->cf_exLK(cf_exlk);
    }
    else if(get_status_ref().mk_orders.find(cf_exlk.invariant.order_id) !=  get_status_ref().mk_orders.end())
    {
        auto  order = get_order_mk(cf_exlk.invariant.order_id);
        order->cf_exLK(cf_exlk);
    }
    else
        return false;
        
    return true;
}


en_order_type  get_order_type(const msg::sub_order_id& ord_id)
{
    if(get_status_ref().ls_orders.find(ord_id) !=  get_status_ref().ls_orders.end())
        return ot_limit;
    else if(get_status_ref().mk_orders.find(ord_id) !=  get_status_ref().mk_orders.end())
        return ot_market;
    else if(get_status_ref().sm_orders.find(ord_id) !=  get_status_ref().sm_orders.end())
        return ot_stop_market;
    else if(get_status_ref().sl_orders.find(ord_id) !=  get_status_ref().sl_orders.end())
        return ot_stop_limit;
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
        response_lines.push_back(MTK_SS("limit :     " <<  mtk::trd::trd_cli_ord_book::get_status_ref().ls_orders.size()));
        response_lines.push_back(MTK_SS("market:     " <<  mtk::trd::trd_cli_ord_book::get_status_ref().mk_orders.size()));
        response_lines.push_back(MTK_SS("stop market:" <<  mtk::trd::trd_cli_ord_book::get_status_ref().sm_orders.size()));
        response_lines.push_back(MTK_SS("stop limit: " <<  mtk::trd::trd_cli_ord_book::get_status_ref().sl_orders.size()));
        response_lines.push_back(MTK_SS("execs:      " <<  mtk::trd::trd_cli_ord_book::get_status_ref().map_execs.size()));
        response_lines.push_back(MTK_SS("orphan exs: " <<  mtk::trd::trd_cli_ord_book::get_status_ref().map_orphan_execs.size()));
    }

}
