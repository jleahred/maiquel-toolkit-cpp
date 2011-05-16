
#ifndef  __msg_trd_common_support__
#define  __msg_trd_common_support__


#include "yaml/yaml.h"



namespace mtk {

   namespace trd {

       namespace msg {

       

        enum enBuySell { buy, sell };


        class sub_order_id;


        bool is_valid (const sub_order_id& ord_id);

        bool operator<(const sub_order_id& p1, const sub_order_id& p2);




        std::ostream& operator<< (std::ostream& os, const enBuySell& d);

        YAML::Emitter& operator<< (YAML::Emitter& o, const enBuySell& s);


        void   operator>> (const YAML::Node& n, enBuySell& bs);

        enBuySell  __internal_get_default (enBuySell*);
        void  copy(enBuySell& result, const qpid::types::Variant& v);
        void __internal_add2map (qpid::types::Variant::Map& map, enBuySell a, const std::string& key);




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
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "trd_cli_ls.cpp", MTK_SS(serrors << "  " << rq << " / " << last_request), mtk::alPriorCritic, mtk::alTypeNoPermisions));
                ++nerrors;
            }
            return mtk::make_tuple(nerrors, serrors);
        }
        template<typename RQ_TYPE, typename CONF_TYPE>      //  ex:   mtk::trd::msg::RQ_XX_LS
        mtk::tuple<int, std::string> check_request_last_confirm(const RQ_TYPE& rq, const mtk::nullable<CONF_TYPE>& last_conf)
        {
            if (last_conf.HasValue() == false)     return mtk::make_tuple(0, std::string());
            
            
            
            std::string serrors;
            int nerrors=0;
            
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
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "trd_cli_ls.cpp", MTK_SS(serrors << "  " << rq << " / " << last_conf.Get()), mtk::alPriorCritic, mtk::alTypeNoPermisions));
                ++nerrors;
            }
            

            //  non critic
            if (last_conf.HasValue()  &&  mtk::Double(last_conf.Get().total_execs.quantity.GetDouble()) >= (mtk::Double(rq.request_pos.quantity.GetDouble())))
            {
                serrors += "  requested quantity lower or equal than executed quantity!!!  ";
                ++nerrors;
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "trd_cli_ls.cpp", MTK_SS(serrors << "  " << rq << " / " << last_conf), mtk::alPriorWarning, mtk::alTypeNoPermisions));
            }
            
            return mtk::make_tuple(nerrors, serrors);
        }
        template<typename RQ_TYPE, typename CONF_TYPE>      //  ex:   mtk::trd::msg::RQ_XX_LS
        mtk::tuple<int, std::string> check_request_not_modifying(const RQ_TYPE& rq, const mtk::nullable<RQ_TYPE>& last_request, const mtk::nullable<CONF_TYPE>& last_conf)
        {
            if (last_conf.HasValue() == false)     return mtk::make_tuple(0, std::string());
            
            std::string serrors;
            int nerrors=0;

            if (last_request.HasValue()== false  ||  last_request.Get().req_info ==  last_conf.Get().req_info)         //  there are no pending request
                if (rq.request_pos == last_conf.Get().market_pos  &&  rq.cli_ref == last_conf.Get().cli_ref)
                    mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "trd_cli_ls.cpp", MTK_SS("modification not modifing  " << "  " << rq << " / " << last_conf), mtk::alPriorWarning, mtk::alTypeNoPermisions));


            if (nerrors >0)
            {
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "trd_cli_ls.cpp", MTK_SS(serrors << "  " << rq << " / " << last_conf), mtk::alPriorCritic, mtk::alTypeNoPermisions));
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
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "trd_cli_ls.cpp", MTK_SS(serrors << "  " << cf << " / " << last_request), mtk::alPriorCritic, mtk::alTypeNoPermisions));
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

            if (mtk::Double(cf.total_execs.quantity.GetDouble()) > (mtk::Double(last_conf.Get().market_pos.quantity.GetDouble())))
            {
                ++nerrors;
                serrors += "  over execution!!!  ";
            }
            if (nerrors >0)
            {
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "trd_cli_ls.cpp", MTK_SS(serrors << "  " << cf << " / " << last_conf), mtk::alPriorCritic, mtk::alTypeNoPermisions));
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
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "trd_cli_ls.cpp", MTK_SS(serrors << "  " << rj << " / " << last_request), mtk::alPriorCritic, mtk::alTypeNoPermisions));
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
            if(last_conf.Get() != rj)
            {
                serrors += MTK_SS("last_conf.Get() != rj  "  <<  last_conf.Get() << "  !=  "  << rj);
                ++nerrors;
            }

            if (nerrors >0)
            {
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "trd_cli_ls.cpp", MTK_SS(serrors << "  " << rj << " / " << last_conf), mtk::alPriorCritic, mtk::alTypeNoPermisions));
                ++nerrors;
            }
            return mtk::make_tuple(nerrors, serrors);
        }
        template<typename EXEC_TYPE, typename CONF_TYPE>      //  ex:   mtk::trd::msg::CF_XX_LS
        mtk::tuple<int, std::string>  check_exec__last_confirm(const EXEC_TYPE& ex, const mtk::nullable<CONF_TYPE>& last_conf)
        {
//            if (last_conf.HasValue() == false)    
//            {
//                std::string serrors = MTK_SS("execution received on non confirmated order  " << ex << " / " << last_conf);
//                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "trd_cli_ls.cpp", serrors, mtk::alPriorCritic, mtk::alTypeNoPermisions));
//                return mtk::make_tuple(1, serrors);
//            }
            
            std::string serrors;
            int nerrors=0;
            
            if(last_conf.Get().invariant  !=  ex.invariant)
            {
                serrors += MTK_SS("last_conf.Get().invariant  !=  ex.invariant " <<  last_conf.Get().invariant  << "  !=  "  <<  ex.invariant);
                ++nerrors;
            }
            if (mtk::Double(ex.total_execs.quantity.GetDouble()) !=  
                        mtk::Double(ex.executed_pos.quantity.GetDouble()) + mtk::Double(last_conf.Get().total_execs.quantity.GetDouble()))
            {
                ++nerrors;
                serrors += "  total execution received doesn't match with  execution received and last confirmated execution  ";
                
            }
            if (mtk::Double(ex.executed_pos.quantity.GetDouble())  >  (mtk::Double(last_conf.Get().market_pos.quantity.GetDouble()) - mtk::Double(last_conf.Get().total_execs.quantity.GetDouble())))
            {
                ++nerrors;
                serrors += "  over execution!!!  ";
            }

            if (nerrors >0)
            {
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "trd_cli_ls.cpp", MTK_SS(serrors << "  " << ex << " / " << last_conf), mtk::alPriorCritic, mtk::alTypeNoPermisions));
                ++nerrors;
            }
            return mtk::make_tuple(nerrors, serrors);
        }


        };   //namespace msg {

   };  //namespace trd {

};  //namespace mtk {



#endif
