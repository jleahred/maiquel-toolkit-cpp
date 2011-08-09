#ifndef MTKNODE_H_62B23520_7C8E_11DE_8A39_0800200C9A66
#define MTKNODE_H_62B23520_7C8E_11DE_8A39_0800200C9A66

#if !defined(__GNUC__) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || (__GNUC__ >= 4) // GCC supports "pragma once" correctly since 3.4
#pragma once
#endif


#include "support/vector.hpp"
#include "support/map.hpp"
#include "support/list.hpp"
#include "support/nullable.hpp"
#include "support/date_time.h"
#include <string>
#include "support/fixed_number.h"
#include "support/mtk_double.h"



namespace
{
    inline std::string  __internal_get_default(std::string*) {  return std::string();  }
    inline mtk::Double __internal_get_default(mtk::Double*)  {  return mtk::Double(0.0); }
    inline mtk::FixedNumber __internal_get_default(mtk::FixedNumber*) { return mtk::FixedNumber(mtk::fnDouble(0), mtk::fnDec(0), mtk::fnInc(1)); }
    inline mtk::DateTime __internal_get_default(mtk::DateTime*) {  return mtk::DateTime(mtk::dtYear(2000), mtk::dtMonth(1), mtk::dtDay(1)); }
    inline mtk::dtTimeQuantity __internal_get_default(mtk::dtTimeQuantity*) { return mtk::dtTimeQuantity(mtk::dtHours(0), mtk::dtMinutes(0), mtk::dtSeconds(0), mtk::dtMilliseconds(0)); }
    inline bool __internal_get_default(bool*) {  return false; }
    inline int __internal_get_default(int*) { return 0;  }

    template<typename T>
    mtk::list<T>  __internal_get_default(mtk::list<T>*)
    {
        return mtk::list<T>();
    }
};

namespace YAML
{
    
	template <typename T>
	inline void operator >> (const Node& node, mtk::list<T>& l)
	{
		l.clear();
		for(unsigned i=0;i<node.size();++i)
        {
            T v = __internal_get_default((T*)0);
            node[i] >> v;
            l.push_back(v);
        }
	}

	template <typename T>
	inline void operator >> (const Node& node, mtk::vector<T>& v)
	{
		v.clear();
		v.resize(node.size());
		for(unsigned i=0;i<node.size();++i)
			node[i] >> v[i];
	}
	
	
	template <typename K, typename V>
	inline void operator >> (const Node& node, mtk::map<K, V>& m)
	{
		m.clear();
		for(unsigned i=0;i<node.size();++i)
        {
            V v = __internal_get_default((V*)0);
            node[i] >> v;
            m.insert(std::make_pair(v.get_key(), v));
        }
//		for(Iterator it=node.begin();it!=node.end();++it) {
//            K k = __internal_get_default((K*)0);
//            V v = __internal_get_default((V*)0);
//			//K k;
//			//V v;
//			it.first() >> k;
//			it.second() >> v;
//			//m[k] = v;
//            m.insert(std::make_pair(k,v));
//		}
	}
    
    template <typename T>
    inline void  operator >> (const YAML::Node& n, mtk::nullable <T>& nv) 
    {
        if(n.size()!=0)
        {
            T t = __internal_get_default((T*)0);
            n >> t;
            nv = t;
        }
    }


    template<typename T>
    T  parse_from_yaml_string(const std::string&  yaml_string)
    {
        T  result =  __internal_get_default((T*) 0);
        std::istringstream  istr(yaml_string);
        YAML::Parser parser(istr);
        YAML::Node doc;
        parser.GetNextDocument(doc);
        doc >> result;
        
        return result;
    }

}

#endif // MTKNODE_H_62B23520_7C8E_11DE_8A39_0800200C9A66
