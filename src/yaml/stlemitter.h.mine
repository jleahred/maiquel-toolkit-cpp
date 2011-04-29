#pragma once

#ifndef STLEMITTER_H_62B23520_7C8E_11DE_8A39_0800200C9A66
#define STLEMITTER_H_62B23520_7C8E_11DE_8A39_0800200C9A66


#include "support/vector.hpp"
#include "support/list.hpp"
#include "support/map.hpp"
#include "support/date_time.h"
#include "support/mtk_string.h"
#include "support/fixed_number.h"
#include "support/mtk_double.h"



namespace YAML
{
	template <typename T>
	inline Emitter& operator << (Emitter& emitter, const mtk::vector <T>& v) {
		typedef typename std::vector <T> vec;
		emitter << YAML::BeginSeq;
		for(unsigned i=0; i<= v.size() ;++i)
			emitter << v[i];
		emitter << YAML::EndSeq;
		return emitter;
        /*
		typedef typename std::vector <T> vec;
		emitter << BeginSeq;
		for(typename vec::const_iterator it=v.begin();it!=v.end();++it)
			emitter << *it;
		emitter << EndSeq;
		return emitter;
        */
	}

	template <typename T>
	inline Emitter& operator << (Emitter& emitter, const mtk::list <T>& v) {
		typedef typename mtk::list <T> list;
		emitter << BeginSeq;
		for(typename list::const_iterator it=v.begin();it!=v.end();++it)
			emitter << *it;
		emitter << EndSeq;
		return emitter;
	}

	template <typename K, typename V>
	inline Emitter& operator << (Emitter& emitter, const mtk::map <K, V>& m) {
		typedef typename mtk::map <K, V> map;
		emitter << BeginMap;
		for(typename map::const_iterator it=m.begin();it!=m.end();++it)
			emitter << Key << it->first << Value << it->second;
		emitter << EndMap;
		return emitter;
	}

}

#endif // STLEMITTER_H_62B23520_7C8E_11DE_8A39_0800200C9A66
