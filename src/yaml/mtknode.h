#ifndef MTKNODE_H_62B23520_7C8E_11DE_8A39_0800200C9A66
#define MTKNODE_H_62B23520_7C8E_11DE_8A39_0800200C9A66

#if !defined(__GNUC__) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || (__GNUC__ >= 4) // GCC supports "pragma once" correctly since 3.4
#pragma once
#endif


#include "support/vector.hpp"
#include "support/map.hpp"

namespace YAML
{
	template <typename T>
	void operator >> (const Node& node, mtk::vector<T>& v)
	{
		v.clear();
		v.resize(node.size());
		for(unsigned i=0;i<node.size();++i)
			node[i] >> v[i];
	}
	
	
	template <typename K, typename V>
	void operator >> (const Node& node, mtk::map<K, V>& m)
	{
		m.clear();
		for(Iterator it=node.begin();it!=node.end();++it) {
			K k;
			V v;
			it.first() >> k;
			it.second() >> v;
			m[k] = v;
		}
	}
}

#endif // MTKNODE_H_62B23520_7C8E_11DE_8A39_0800200C9A66
