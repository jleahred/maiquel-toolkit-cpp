
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


        };   //namespace msg {

   };  //namespace trd {

};  //namespace mtk {



#endif
