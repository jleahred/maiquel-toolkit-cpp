#ifndef __trd_cli_support_h__
#define __trd_cli_support_h__




#include "trd_cli_ls.h"





namespace mtk{namespace trd{



    template<typename ORDER_TYPE>       //  mtk::trd::trd_cli_ls
    mtk::msg::sub_product_code   get_product_code(const ORDER_TYPE& order)
    {
        if(order.last_request().HasValue())
            return order.last_request().Get().invariant.product_code;
        else if (order.last_confirmation().HasValue())
            return order.last_confirmation().Get().invariant.product_code;
        else
            throw mtk::Alarm(MTK_HERE, "trd_cli_support", MTK_SS("no request no confirmation on order"), mtk::alPriorCritic, mtk::alTypeNoPermisions);
    }


    template<typename ORDER_TYPE>       //  mtk::trd::trd_cli_ls
    mtk::trd::msg::sub_account_info   get_account(const ORDER_TYPE& order)
    {
        if(order.last_request().HasValue())
            return order.last_request().Get().invariant.account;
        else if (order.last_confirmation().HasValue())
            return order.last_confirmation().Get().invariant.account;
        else
            throw mtk::Alarm(MTK_HERE, "trd_cli_support", MTK_SS("no request no confirmation on order"), mtk::alPriorCritic, mtk::alTypeNoPermisions);
    }

    template<typename ORDER_TYPE>       //  mtk::trd::trd_cli_ls
    std::string   get_cli_ref(const ORDER_TYPE& order)
    {
        if(order.last_request().HasValue())
            return order.last_request().Get().request_pos.cli_ref;
        else if (order.last_confirmation().HasValue())
            return order.last_confirmation().Get().market_pos.cli_ref;
        else
            throw mtk::Alarm(MTK_HERE, "trd_cli_support", MTK_SS("no request no confirmation on order"), mtk::alPriorCritic, mtk::alTypeNoPermisions);
    }


    /**
     *      It will return the description of last transaction
     */
    template<typename ORDER_TYPE>       //  mtk::trd::trd_cli_ls
    std::string    get_lasttr_descr  (const ORDER_TYPE& order)
    {
        return order.history()->get_lasttr_descr();
    }



    /**
     *      If last transition is a reject, it will return true
     */
    template<typename ORDER_TYPE>       //  mtk::trd::trd_cli_ls
    bool     is_last_tr_rj  (const ORDER_TYPE& order)
    {
        return order.history()->is_last_tr_rj();
    }



    namespace  msg
    {
        template<typename RQ_TYPE>      //  ex:   mtk::trd::msg::RQ_XX_LS
            mtk::tuple<int, std::string> check_request(const RQ_TYPE& rq)
            {
                std::string serrors;
                int nerrors=0;

                if (is_valid(rq.invariant.order_id)==false)
                {
                    ++nerrors;
                    serrors + "  invalid order_id on request!!!  ";
                }
                if (is_valid(rq.invariant.product_code)==false)
                {
                    ++nerrors;
                    serrors + "  invalid product_code on request!!!  ";
                }

                if (rq.request_pos.quantity.GetIntCode() == 0)
                {
                    ++nerrors;
                    serrors + "  invalid quantity!!!  ";
                }

                if (nerrors >0)     //  all errors on this level are critic
                {
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "check_request", MTK_SS(serrors << "  " << rq ), mtk::alPriorCritic, mtk::alTypeNoPermisions));
                    ++nerrors;
                }
                return mtk::make_tuple(nerrors, serrors);
            }
            template<typename RQ_TYPE>      //  ex:   mtk::trd::msg::RQ_XX_LS
            mtk::tuple<int, std::string> check_request_request(const RQ_TYPE& rq, const mtk::nullable<RQ_TYPE>& last_request)
            {
                std::string serrors;
                int nerrors=0;

                {
                    std::string l_serrors;
                    int l_nerrors=0;
                    check_request(rq).assign(l_nerrors, l_serrors);
                    nerrors += l_nerrors;
                    serrors += l_serrors;
                }


                if (last_request.HasValue() == true)
                {
                    if(last_request.Get().invariant != rq.invariant)
                    {
                        serrors += MTK_SS("last_request.Get().invariant != rq.invariant  "  <<  last_request.Get().invariant << "  !=  "  << rq.invariant);
                        ++nerrors; \
                    }
                }

                if (nerrors >0)     //  all errors on this level are critic
                {
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "check_request_request", MTK_SS(serrors << "  " << rq << " / " << last_request), mtk::alPriorCritic, mtk::alTypeNoPermisions));
                    ++nerrors;
                }
                return mtk::make_tuple(nerrors, serrors);
            }
            template<typename RQ_TYPE, typename CONF_TYPE>      //  ex:   mtk::trd::msg::RQ_XX_LS
            mtk::tuple<int, std::string, bool> check_request_last_confirm(const RQ_TYPE& rq, const mtk::nullable<CONF_TYPE>& last_conf)
            {       //  mtk::tuple<int, std::string, bool>   num errors, errors description,  quantity lower than executed
                if (last_conf.HasValue() == false)     return mtk::make_tuple(0, std::string(), false);



                std::string serrors;
                int nerrors=0;
                bool quantity_lower_than_executed = false;

                {
                    std::string l_serrors;
                    int l_nerrors=0;
                    check_request(rq).assign(l_nerrors, l_serrors);
                    nerrors += l_nerrors;
                    serrors += l_serrors;
                }


                if(rq.invariant  !=  last_conf.Get().invariant)
                {
                    serrors += MTK_SS("rq.invariant  !=  last_conf.invariant  "  <<  rq.invariant << "  !=  "  << last_conf.Get().invariant);
                    ++nerrors; \
                }

                if (nerrors >0)     //  all errors on this level are critic
                {
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "check_request_last_confirm", MTK_SS(serrors << "  " << rq << " / " << last_conf.Get()), mtk::alPriorCritic, mtk::alTypeNoPermisions));
                    ++nerrors;
                }


                //  non critic
                if (last_conf.HasValue()  &&  mtk::Double(last_conf.Get().total_execs.acc_quantity.GetDouble()) >= (mtk::Double(rq.request_pos.quantity.GetDouble())))
                {
                    quantity_lower_than_executed = true;
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "check_request_last_confirm", MTK_SS("requested qty lower than exec qty  "  << "  " << rq << " / " << last_conf), mtk::alPriorWarning, mtk::alTypeNoPermisions));
                }

                return mtk::make_tuple(nerrors, serrors, quantity_lower_than_executed);
            }
            template<typename RQ_TYPE, typename CONF_TYPE>      //  ex:   mtk::trd::msg::RQ_XX_LS
            mtk::tuple<int, std::string> check_request_not_modifying(const RQ_TYPE& rq, const mtk::nullable<RQ_TYPE>& last_request, const mtk::nullable<CONF_TYPE>& last_conf)
            {
                if (last_conf.HasValue() == false)     return mtk::make_tuple(0, std::string());

                std::string serrors;
                int nerrors=0;

                if (last_request.HasValue()== false  ||  last_request.Get().request_info.req_id ==  last_conf.Get().req_id)         //  there are no pending request
                    if (rq.request_pos == last_conf.Get().market_pos)
                        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "check_request_not_modifying", MTK_SS("modification not modifing  " << "  " << rq << " / " << last_conf), mtk::alPriorWarning, mtk::alTypeNoPermisions));


                if (nerrors >0)
                {
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "check_request_not_modifying", MTK_SS(serrors << "  " << rq << " / " << last_conf), mtk::alPriorCritic, mtk::alTypeNoPermisions));
                    ++nerrors;
                }
                return mtk::make_tuple(nerrors, serrors);
            }

            template<typename CONF_TYPE>      //  ex:   mtk::trd::msg::CF_XX_LS
            mtk::tuple<int, std::string> check_confirm(const CONF_TYPE& cf)
            {
                std::string serrors;
                int nerrors=0;

                if(cf.market_pos.quantity.GetDouble() != (cf.total_execs.acc_quantity.GetDouble() + cf.total_execs.remaining_qty.GetDouble()))
                    serrors += MTK_SS("quantity doesn't match   cf.market_pos.quantity != (cf.total_execs.acc_quantity + cf.total_execs.remaining_qty)" <<
                            cf.market_pos.quantity << " !=  "  << "(" << cf.total_execs.acc_quantity << "+" <<cf.total_execs.remaining_qty<<")");

                if (nerrors >0)
                {
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "check_confirm_request", serrors, mtk::alPriorCritic, mtk::alTypeNoPermisions));
                    ++nerrors;
                }
                return mtk::make_tuple(nerrors, serrors);
            }

            template<typename RQ_TYPE, typename CONF_TYPE>      //  ex:   mtk::trd::msg::RQ_XX_LS
            mtk::tuple<int, std::string> check_confirm_request(const CONF_TYPE& cf, const mtk::nullable<RQ_TYPE>& last_request)
            {
                std::string serrors;
                int nerrors=0;

                if (last_request.HasValue()== true)
                {
                    if(cf.invariant  !=  last_request.Get().invariant)
                    {
                        serrors += MTK_SS("cf.invariant  !=  last_request.invariant  "  <<  cf.invariant << "  !=  "  << last_request.Get().invariant);
                        ++nerrors;
                    }
                }

                if (nerrors >0)
                {
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "check_confirm_request", MTK_SS(serrors << "  " << cf << " / " << last_request), mtk::alPriorCritic, mtk::alTypeNoPermisions));
                    ++nerrors;
                }
                return mtk::make_tuple(nerrors, serrors);
            }

            template<typename CONF_TYPE>      //  ex:   mtk::trd::msg::CF_XX_LS
            mtk::tuple<int, std::string> check_confirm__last_confirm(const CONF_TYPE& cf, const mtk::nullable<CONF_TYPE>& last_conf)
            {
                if (last_conf.HasValue() == false)     return mtk::make_tuple(0, std::string());

                std::string serrors;
                int nerrors=0;

                if(cf.invariant  !=  last_conf.Get().invariant)
                {
                    serrors += MTK_SS("cf.invariant  !=  last_conf.Get().invariant  "  <<  cf.invariant  <<  "  !=  "  <<  last_conf.Get().invariant);
                    ++nerrors;
                }


                if (mtk::Double(cf.total_execs.acc_quantity.GetDouble())  >  (mtk::Double(last_conf.Get().market_pos.quantity.GetDouble())))
                {
                    ++nerrors;
                    serrors += MTK_SS("  received confirmation with total_exed_qty > last_conf.market_pos.quantty  "  <<  cf.total_execs.acc_quantity  <<
                                        "   "  <<  last_conf.Get().market_pos.quantity.GetDouble());
                }

                if (nerrors >0)
                {
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "check_confirm__last_confirm", MTK_SS(serrors << "  " << cf << " / " << last_conf), mtk::alPriorCritic, mtk::alTypeNoPermisions));
                    ++nerrors;
                }
                return mtk::make_tuple(nerrors, serrors);
            }
            template<typename CONF_TYPE, typename RQ_TYPE>      //  ex:   mtk::trd::msg::CF_XX_LS
            mtk::tuple<int, std::string> check_reject_request(const CONF_TYPE& rj, const mtk::nullable<RQ_TYPE>& last_request)
            {
                std::string serrors;
                int nerrors=0;

                if (last_request.HasValue())
                {
                    if(last_request.Get().invariant  !=  rj.invariant)
                    {
                        serrors += MTK_SS("last_request.Get().invariant  !=  rj.invariant  "  <<  last_request.Get().invariant  << "  !=  " <<  rj.invariant);
                        ++nerrors;
                    }
                }

                if (nerrors >0)
                {
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "check_reject_request", MTK_SS(serrors << "  " << rj << " / " << last_request), mtk::alPriorCritic, mtk::alTypeNoPermisions));
                    ++nerrors;
                }
                return mtk::make_tuple(nerrors, serrors);
            }
            template<typename CONF_TYPE>      //  ex:   mtk::trd::msg::CF_XX_LS
            mtk::tuple<int, std::string> check_reject__last_confirm(const CONF_TYPE& rj, const mtk::nullable<CONF_TYPE>& last_conf)
            {
                if (last_conf.HasValue() == false)     return mtk::make_tuple(0, std::string());

                std::string serrors;
                int nerrors=0;

                if(last_conf.Get().invariant  !=  rj.invariant)
                {
                    serrors += MTK_SS("last_conf.Get().invariant  !=  rj.invariant  "  <<  last_conf.Get().invariant  << "  !=  " <<  rj.invariant);
                    ++nerrors;
                }
                if(last_conf.Get().total_execs != rj.total_execs)
                {
                    serrors += MTK_SS("last_conf.total_execs != rj.total_execs  "  <<  last_conf.Get().total_execs << "  !=  "  << rj.total_execs);
                    ++nerrors;
                }
                if(last_conf.Get().market_pos != rj.market_pos)
                {
                    serrors += MTK_SS("last_conf.market_pos != rj.market_pos  "  <<  last_conf.Get().market_pos << "  !=  "  << rj.market_pos);
                    ++nerrors;
                }

                if (mtk::Double(rj.total_execs.acc_quantity.GetDouble())  >  (mtk::Double(last_conf.Get().market_pos.quantity.GetDouble())))
                {
                    ++nerrors;
                    serrors += MTK_SS("  received confirmation with total_exed_qty > last_conf.market_pos.quantty  "  <<  rj.total_execs.acc_quantity  <<
                                        "   "  <<  last_conf.Get().market_pos.quantity.GetDouble());
                }
                if (nerrors >0)
                {
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "check_reject__last_confirm", MTK_SS(serrors << "  " << rj << " / " << last_conf), mtk::alPriorCritic, mtk::alTypeNoPermisions));
                    ++nerrors;
                }
                return mtk::make_tuple(nerrors, serrors);
            }

            template<typename EXEC_TYPE, typename CONF_TYPE>      //  ex:   mtk::trd::msg::CF_XX_LS
            mtk::tuple<int, std::string>  check_exec__last_confirm(const EXEC_TYPE& ex, const mtk::nullable<CONF_TYPE>& last_conf)
            {
                if (last_conf.HasValue() == false)     return mtk::make_tuple(0, std::string());

                std::string serrors;
                int nerrors=0;

                if(last_conf.Get().invariant  !=  ex.invariant)
                {
                    serrors += MTK_SS("last_conf.Get().invariant  !=  ex.invariant " <<  last_conf.Get().invariant  << "  !=  "  <<  ex.invariant);
                    ++nerrors;
                }
                if (mtk::Double(ex.total_execs.acc_quantity.GetDouble()) !=
                            mtk::Double(ex.executed_pos.quantity.GetDouble()) + mtk::Double(last_conf.Get().total_execs.acc_quantity.GetDouble()))
                {
                    ++nerrors;
                    serrors += "  total execution received doesn't match with  execution received and last confirmated execution  ";

                }
                if (mtk::Double(ex.executed_pos.quantity.GetDouble())  >  (mtk::Double(last_conf.Get().market_pos.quantity.GetDouble()) - mtk::Double(last_conf.Get().total_execs.acc_quantity.GetDouble())))
                {
                    ++nerrors;
                    serrors += "  over execution!!!  ";
                }

                if (nerrors >0)
                {
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "check_exec__last_confirm", MTK_SS(serrors << "  " << ex << " / " << last_conf), mtk::alPriorCritic, mtk::alTypeNoPermisions));
                    ++nerrors;
                }
                return mtk::make_tuple(nerrors, serrors);
            }
        }       //      namespace  msg



};   //  namespace trd
};   //  namespace mtk


#endif // __trd_cli_support_h__


