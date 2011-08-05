#include "account_manager_cli.h"

#include "components/admin/admin.h"
#include "support/tuples.hpp"



namespace {
    const char*   VERSION = "2011-05-25";
    
    const char*   MODIFICATIONS =
                        "           2011-05-25     first version\n";
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
    
    
    void  request__and__susbcribe_add_accounts_and_initserver(void);
    
    mtk::CountPtr<mtk::map <mtk::trd::account::msg::sub_grant::IC_key,   mtk::trd::account::msg::sub_grant > >   get_grants_map(void)
    {
        static mtk::CountPtr<mtk::map <mtk::trd::account::msg::sub_grant::IC_key,   mtk::trd::account::msg::sub_grant > >  result;
        if(result.isValid()==false)
        {
            result = mtk::make_cptr(new mtk::map <mtk::trd::account::msg::sub_grant::IC_key,   mtk::trd::account::msg::sub_grant >);
        }
        return result;
    }
    
    void command_list_accounts(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_version(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_stats  (const std::string& /*command*/, const std::string& /*param*/,  mtk::list<std::string>&  response_lines);
    
    void register_global_commands (void)
    {
        mtk::admin::register_command("__GLOBAL__",    "ver",   "")->connect(command_version);
        mtk::admin::register_command("__GLOBAL__",    "stats", "")->connect(command_stats);
        mtk::admin::register_command("accmgr"    ,  "stats",   "")->connect(command_stats);
        mtk::admin::register_command("accmgr"    ,  "list",         "")->connect(command_list_accounts);
    }

};


namespace mtk { 
    namespace accmgrcli {
        


        void init()
        {
            request__and__susbcribe_add_accounts_and_initserver();
            register_global_commands();
        }

        mtk::CountPtr<mtk::Signal<const mtk::trd::account::msg::sub_grant&> >           get_signal_new_grant_received(void)
        {
            static mtk::CountPtr<mtk::Signal<const mtk::trd::account::msg::sub_grant&> >  result;
            if(result.isValid() == false)
            {
                result =  mtk::make_cptr( new mtk::Signal<const mtk::trd::account::msg::sub_grant&>  );
            }
            return result;
        }

        mtk::list<mtk::trd::account::msg::sub_grant>                                    get_grant_list(void)
        {
            mtk::list<mtk::trd::account::msg::sub_grant>  result;
            mtk::CountPtr<mtk::map <mtk::trd::account::msg::sub_grant::IC_key,   mtk::trd::account::msg::sub_grant > >  grant_map = get_grants_map();
            for(mtk::map <mtk::trd::account::msg::sub_grant::IC_key,   mtk::trd::account::msg::sub_grant >::iterator it = grant_map->begin();
                                it != grant_map->end(); ++it)
            {
                result.push_back(it->second);
            }
            
            return result;
        }

        std::string  get_grant_less_restrictive (const std::string& market)
        {
            std::string  result;
            mtk::CountPtr<mtk::map <mtk::trd::account::msg::sub_grant::IC_key,   mtk::trd::account::msg::sub_grant > >  grant_map = get_grants_map();
            for(mtk::map <mtk::trd::account::msg::sub_grant::IC_key,   mtk::trd::account::msg::sub_grant >::iterator it = grant_map->begin();
                                it != grant_map->end(); ++it)
            {
                if(it->first.market == market)
                {
                    if(it->second.type == "F")
                        return "F";
                    else if(it->second.type == "C")
                        result = "C";
                    else if(it->second.type == "V"  &&  result != "C")
                        result = "V";
                }
                    
            }
            
            return result;
        }


        std::string   get_grant (const std::string& market, const mtk::trd::msg::sub_account_info& ai)
        {
            mtk::CountPtr<mtk::map <mtk::trd::account::msg::sub_grant::IC_key,   mtk::trd::account::msg::sub_grant > >  grant_map = get_grants_map();
            mtk::trd::account::msg::sub_grant::IC_key k(market, ai);
            auto located = grant_map->find(k);
            if(located == grant_map->end())
                return "";
            else
                return located->second.type;
        }



    };  //      namespace accmgrcli {
};      //  namespace mtk { 
 




namespace {
    
    
    void on_add_accounts(const mtk::trd::account::msg::conf_add_accounts&  add_accounts)
    {

            //add_accounts [<  V:0, SUBJ:CONF.${location.client_code}.ACCOUNTS.${session_id}   >]
            //{
            //    location        (lc)    :   mtk::msg::sub_location
            //    session_id      (sid)   :   string
            //
            //    [grant_list]    (grl)   :   sub_grant       //  grant type is empty to revoque permision
            //}
        mtk::CountPtr<mtk::Signal<const mtk::trd::account::msg::sub_grant&> >      signal_new_grant_received  = mtk::accmgrcli::get_signal_new_grant_received();
        const mtk::list<mtk::trd::account::msg::sub_grant>&  rec_grants = add_accounts.grant_list;
        mtk::CountPtr<mtk::map <mtk::trd::account::msg::sub_grant::IC_key,   mtk::trd::account::msg::sub_grant > > grants = get_grants_map();
        
        for(mtk::list<mtk::trd::account::msg::sub_grant>::const_iterator it = rec_grants.begin(); it!= rec_grants.end(); ++it)
        {
            mtk::map <mtk::trd::account::msg::sub_grant::IC_key,   mtk::trd::account::msg::sub_grant >::iterator find_grant = get_grants_map()->find(it->key);
            if(find_grant != get_grants_map()->end())
                find_grant->second = *it;
            else
                get_grants_map()->insert(std::make_pair(it->key, *it));
            signal_new_grant_received->emit(*it);
        }
    }

    void  on_pub_accmgr_init(const mtk::trd::account::msg::pub_accmgr_init&   pub_accmgr_init)
    {
        mtk::trd::account::msg::rq_accounts_oninit    rq_accounts_oninit (mtk::admin::get_request_info(), pub_accmgr_init.request_sufix_subjetc);
        mtk::send_message(mtk::admin::get_qpid_session("client", "CLITESTING"), rq_accounts_oninit);
    }
    
    
    void  request__and__susbcribe_add_accounts_and_initserver(void)
    {
        mtk::msg::sub_request_info  ri (mtk::admin::get_request_info());
        
        static mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::account::msg::conf_add_accounts> >    hqpid_add_accounts;
        std::string  client_code = ri.process_info.location.client_code;
        std::string  session_id = ri.req_id.session_id;
        
        MTK_QPID_RECEIVER_CONNECT_F(
                                hqpid_add_accounts,
                                mtk::admin::get_url("client"),
                                "CLITESTING",
                                mtk::trd::account::msg::conf_add_accounts::get_in_subject(client_code, session_id),
                                mtk::trd::account::msg::conf_add_accounts,
                                on_add_accounts)
                                
                                
        mtk::trd::account::msg::rq_accounts msg_rq_accounts(ri);
        mtk::send_message(mtk::admin::get_qpid_session("client", "CLITESTING"), msg_rq_accounts);


        //  suscription to init server
        static mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::trd::account::msg::pub_accmgr_init> >    hqpid_pub_accmgr_init;
        MTK_QPID_RECEIVER_CONNECT_F(
                                hqpid_pub_accmgr_init,
                                mtk::admin::get_url("client"),
                                "CLITESTING",
                                mtk::trd::account::msg::pub_accmgr_init::get_in_subject(),
                                mtk::trd::account::msg::pub_accmgr_init,
                                on_pub_accmgr_init)
    }
    
    
    void command_list_accounts(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
    {
        command_stats("", "", response_lines);
        mtk::CountPtr<mtk::map <mtk::trd::account::msg::sub_grant::IC_key,   mtk::trd::account::msg::sub_grant > > grants = get_grants_map();
        for(mtk::map <mtk::trd::account::msg::sub_grant::IC_key,   mtk::trd::account::msg::sub_grant >::const_iterator it= grants->begin();
                                                    it != grants->end(); ++it)
        {
            response_lines.push_back(MTK_SS(it->second));
        }
    }

    void command_stats  (const std::string& /*command*/, const std::string& /*param*/,  mtk::list<std::string>&  response_lines)
    {
        response_lines.push_back(MTK_SS("#accounts: " << get_grants_map()->size()));
    }
    
    
    
};
