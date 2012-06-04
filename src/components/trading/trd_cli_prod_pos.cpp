#include "trd_cli_prod_pos.h"




namespace {
    const char*   VERSION = "2012-05-30";

    const char*   MODIFICATIONS =
                        "           2012-05-30     first version\n"
                        ;


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



    void register_global_commands (void)
    {
        mtk::admin::register_command("__GLOBAL__",    "ver",   "")->connect(command_version);
        mtk::admin::register_command("__GLOBAL__",    "modifs","")->connect(command_modifications);
    }

    MTK_ADMIN_REGISTER_GLOBAL_COMMANDS(register_global_commands)

}       //  anonymous namespace  to register "static" commnads



namespace {

    mtk::map<mtk::msg::sub_product_code, mtk::list<mtk::CountPtr<mtk::trd::trd_cli_ls> > >&   get_map_product_orders(void)
    {
        static  mtk::map<mtk::msg::sub_product_code, mtk::list<mtk::CountPtr<mtk::trd::trd_cli_ls> > >        result;
        return result;
    }

    mtk::map<mtk::msg::sub_product_code, mtk::list<mtk::trd::cli_pos_prod::level> >&    get_map_product_levels(void)
    {
        static  mtk::map<mtk::msg::sub_product_code, mtk::list<mtk::trd::cli_pos_prod::level> >       result;
        return result;
    }

    mtk::map<mtk::trd::msg::sub_order_id, mtk::CountPtr<mtk::trd::trd_cli_ls> >&  get_orphan_orders_map  (void)
    {
        static  mtk::map<mtk::trd::msg::sub_order_id, mtk::CountPtr<mtk::trd::trd_cli_ls> >   result;
        return result;
    }


    void  add_level(mtk::list<mtk::trd::cli_pos_prod::level>&  levels, const mtk::trd::cli_pos_prod::level&  level)
    {
        for(auto it=levels.begin(); it!=levels.end(); ++it)
        {
            mtk::trd::cli_pos_prod::level&  item = *it;     //  I know it's dangerous
            if(item.price == level.price)
            {
                item.quantity.SetDouble(item.quantity.GetDouble() + level.quantity.GetDouble());
                return;
            }
        }
        levels.push_back(level);
    }

    void update_product(const  mtk::msg::sub_product_code&  product_code)
    {
        auto  it_find_product = get_map_product_orders().find(product_code);
        if(it_find_product  == get_map_product_orders().end())
        {
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "update_product", MTK_SS("missgin product" << product_code << " " << product_code), mtk::alPriorError));
            return;
        }


        mtk::list<mtk::trd::cli_pos_prod::level>  levels;
        mtk::list<mtk::CountPtr<mtk::trd::trd_cli_ls> >&  list_orders = it_find_product->second;  //  I know it's dangerous
        for(auto it= list_orders.begin(); it != list_orders.end(); ++it)
        {
            mtk::CountPtr<mtk::trd::trd_cli_ls>  item = *it;    // I know it's dangerous
            if(item->is_alive()  &&  item->last_confirmation().HasValue())
            {
                const mtk::trd::msg::CF_XX_LS&   last_confirmation = item->last_confirmation().Get();   //  I know it's dangerous
                mtk::trd::cli_pos_prod::level   level{last_confirmation.market_pos.price, last_confirmation.total_execs.remaining_qty};
                add_level(levels, level);
            }
            get_map_product_levels()[product_code] = levels;
        }
        mtk::trd::cli_pos_prod::get_sig_product_updated().emit(product_code, levels);       //  I know it will take a copy from product and levels
    }


    template<typename  T>   //      const mtk::trd::msg::CF_NW_LS&
    void  updated_order(const T&   cf)
    {
        try
        {
            update_product(cf.invariant.product_code);
        }
        MTK_CATCH_CALLFUNCION(mtk::AlarmMsg, "prod_pos", "updated_order");
    }


    void  insert_order(const mtk::trd::msg::sub_order_id& order_id, mtk::CountPtr<mtk::trd::trd_cli_ls>   order);


    void  check_orphans(void)
    {
        MTK_EXEC_MAX_FREC_S(mtk::dtSeconds(10))
        {
            {
                //  orphans with info
                auto it=get_orphan_orders_map().begin();
                while(it!=get_orphan_orders_map().end())
                {
                    mtk::CountPtr<mtk::trd::trd_cli_ls>&    order = it->second;  // I know it's dangerous
                    if(order->last_confirmation().HasValue()  ||  order->last_request().HasValue())
                        it = get_orphan_orders_map().erase(it);
                    else
                        ++it;
                }
            }

            //  orders not in market
            {
                auto it = get_map_product_orders().begin();
                while(it != get_map_product_orders().end())
                {
                    mtk::list<mtk::CountPtr<mtk::trd::trd_cli_ls> >&  item = it->second;      //  I know, it's dangerous
                    auto it2 = item.begin();
                    while(it2!= item.end())
                    {
                        mtk::CountPtr<mtk::trd::trd_cli_ls>&  item2 = *it2;      //  I know, it's dangerous
                        if(item2->is_alive() == false)
                            it2 = item.erase(it2);
                        else
                            ++it2;
                    }
                    if(item.size() == 0)
                        it = get_map_product_orders().erase(it);
                    else
                        ++it;
                }
            }
        }
        MTK_END_EXEC_MAX_FREC
    }

    template<typename  T>   //      const mtk::trd::msg::CF_NW_LS&
    void  orphan_order_changed(const T&   cf)
    {
        //  remove from orphans
            //  insert_order
        try
        {
            auto it=get_orphan_orders_map().find(cf.invariant.order_id);
            if(it != get_orphan_orders_map().end())
            {
                mtk::CountPtr<mtk::trd::trd_cli_ls>    order = it->second;
                if(order->last_confirmation().HasValue()  ||  order->last_request().HasValue())
                {
                    order->sig_cf_nw.disconnect(orphan_order_changed);
                    order->sig_cf_md.disconnect(orphan_order_changed);
                    order->sig_cf_cc.disconnect(orphan_order_changed);
                    order->sig_cf_ex.disconnect(orphan_order_changed);
                    order->sig_cf_st.disconnect(orphan_order_changed);
                    insert_order(mtk::trd::get_order_id(*order), order);
                }
            }
        }
        MTK_CATCH_CALLFUNCION(mtk::AlarmMsg, "prod_pos", "orphan_order_changed");
    }

    void  insert_order(const mtk::trd::msg::sub_order_id& order_id, mtk::CountPtr<mtk::trd::trd_cli_ls>   order)
    {
        static  mtk::msg::sub_product_code   pc_missing_info("<none>", "<none>");
        if(order->last_confirmation().HasValue() == false  &&   order->last_request().HasValue() == false)
        {
            get_orphan_orders_map().insert(std::make_pair(order_id, order));
            order->sig_cf_nw.connect(orphan_order_changed);
            order->sig_cf_md.connect(orphan_order_changed);
            order->sig_cf_cc.connect(orphan_order_changed);
            order->sig_cf_ex.connect(orphan_order_changed);
            order->sig_cf_st.connect(orphan_order_changed);
            return;
        }

        mtk::msg::sub_product_code  product_code =  mtk::trd::get_product_code(*order);

        auto  it_find_product = get_map_product_orders().find(product_code);
        if(it_find_product  == get_map_product_orders().end())
        {
            get_map_product_orders()[product_code].push_back(order);
            order->sig_cf_nw.connect(updated_order);
            order->sig_cf_md.connect(updated_order);
            order->sig_cf_cc.connect(updated_order);
            order->sig_cf_ex.connect(updated_order);
            order->sig_cf_st.connect(updated_order);
            return;
        }
        else
        {
            bool located = false;
            for(auto it= it_find_product->second.begin(); it != it_find_product->second.end(); ++it)
            {
                mtk::CountPtr<mtk::trd::trd_cli_ls>  item = *it;    // I know it's dangerous
                if(order_id == mtk::trd::get_order_id(*item))
                {
                    located = true;
                    break;
                }
            }
            if(located == false)
            {
                get_map_product_orders()[product_code].push_back(order);
                order->sig_cf_nw.connect(updated_order);
                order->sig_cf_md.connect(updated_order);
                order->sig_cf_cc.connect(updated_order);
                order->sig_cf_ex.connect(updated_order);
                order->sig_cf_st.connect(updated_order);
            }
            else
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "insert_order", MTK_SS("order alredy registered" << product_code << " " << order_id), mtk::alPriorError));
            update_product(product_code);
        }
    }

    void  on_new_order(const mtk::trd::msg::sub_order_id& order_id, mtk::CountPtr<mtk::trd::trd_cli_ls_dangerous_signals_not_warped>& order)
    {
        try
        {
            insert_order(order_id, mtk::make_cptr(new mtk::trd::trd_cli_ls{order}));
        }
        MTK_CATCH_CALLFUNCION(mtk::AlarmMsg, "prod_pos", "on_new_order");
    }

};       //  anonymous namespace  support




namespace mtk{namespace trd{



namespace  cli_pos_prod {

    void  init(void)
    {
        static bool initialized = false;
        if(initialized == true)
            return;
        initialized = true;

        mtk::list<mtk::trd::msg::sub_order_id>   orders_id  =  mtk::trd::trd_cli_ord_book::get_all_order_ids();
        for(auto it= orders_id.begin(); it!= orders_id.end(); ++it)
        {
            if(mtk::trd::trd_cli_ord_book::get_order_type(*it)  ==  mtk::trd::trd_cli_ord_book::ot_limit)
                insert_order(*it, mtk::trd::trd_cli_ord_book::get_order_ls(*it));
        }

        mtk::trd::trd_cli_ord_book::get_sig_order_ls_new().connect(on_new_order);
        MTK_TIMER_1SF(check_orphans);
    }




    mtk::Signal<const mtk::msg::sub_product_code&, const mtk::list<mtk::trd::cli_pos_prod::level>& >&         get_sig_product_updated     (void)
    {
        init();
        static  mtk::Signal<const mtk::msg::sub_product_code&, const mtk::list<mtk::trd::cli_pos_prod::level>& >    result;
        return result;
    }


    mtk::list<mtk::trd::cli_pos_prod::level>         get_product_levels            (const mtk::msg::sub_product_code&   product_code)
    {
        init();
        return  get_map_product_levels()[product_code];
    }





};//    namespace  cli_pos_prod {

};   //  namespace mtk
};   //  namespace trd

