

/**
    Tuplas sencillas
    No tienen las posibilidades de las de boost o tr1



    tuple<int, std::string> t1(8, "hlkjh");
    tuple<int, std::string, int> t2 = make_tuple(8, std::string("ocho"), 88);

    std::cout << std::endl << std::endl << t2._0 << "   "  << t2._1 << "   "  << t2._2;


*/



#ifndef mtkTuplesH
#define mtkTuplesH



#include <ostream>
#include "basic_types.hpp"


namespace mtk {




//  TUPLES



template <
  typename T0 = null_type, typename T1 = null_type, typename T2 = null_type,
  typename T3 = null_type, typename T4 = null_type, typename T5 = null_type,
  typename T6 = null_type, typename T7 = null_type, typename T8 = null_type,
  typename T9 = null_type>
class tuple;





template <typename T0>
class tuple <T0,
        null_type, null_type, null_type, null_type, null_type, null_type,
        null_type, null_type, null_type > {
public:
    T0  _0;

    tuple() {};
    tuple(const T0& v0) : _0(v0) {};

    void assign (T0& r0) {
        r0 = _0;
    };

};

template<typename T0>
tuple<T0> make_tuple(const T0& v0)
{
    return tuple<T0>(v0);
};

template<typename T0>
bool operator<(const tuple <T0>& t0, const tuple <T0>& t1)
{
    if (t0._0 < t1._0)
        return true;
    else
        return false;
};

template<typename T0>
std::ostream& operator<< (std::ostream& o, const tuple <T0>& t)
{
    o << "(" << t._0  <<  ")";
    return o;
};




template <typename T0, typename T1>
class tuple <T0, T1,
        null_type, null_type, null_type, null_type, null_type,
        null_type, null_type, null_type > {
public:
    T0  _0;
    T1  _1;

    tuple() {};
    tuple(const T0& v0, const T1& v1) : _0(v0), _1(v1) {};

    void assign (T0& r0, T1& r1) {
        r0 = _0;
        r1 = _1;
    };

};

template<typename T0, typename T1>
tuple<T0, T1> make_tuple(const T0& v0, const T1& v1)
{
    return tuple<T0, T1>(v0, v1);
};

template<typename T0, typename T1>
bool operator<(const tuple <T0, T1>& t0, const tuple <T0, T1>& t1)
{
    if (t0._0 < t1._0)
        return true;
    else if (t0._0 == t1._0  &&  t0._1 < t1._1)
        return true;
    else
        return false;
};

template<typename T0, typename T1>
std::ostream& operator<< (std::ostream& o, const tuple <T0, T1>& t)
{
    o << "(" << t._0 << ", " << t._1 << ")";
    return o;
};






template <typename T0, typename T1, typename T2>
class tuple <T0, T1, T2,
        null_type, null_type, null_type, null_type, null_type,
        null_type, null_type > {
public:
    T0  _0;
    T1  _1;
    T2  _2;

    tuple() {};
    tuple(const T0& v0, const T1& v1, const T2& v2)
        : _0(v0), _1(v1), _2(v2) {};

    void assign (T0& r0, T1& r1, T2& r2) {
        r0 = _0;
        r1 = _1;
        r2 = _2;
    };
};

template<typename T0, typename T1, typename T2 >
tuple<T0, T1, T2> make_tuple(const T0& v0, const T1& v1, const T2& v2)
{
    return tuple<T0, T1, T2>(v0, v1, v2);
};

template<typename T0, typename T1, typename T2>
bool operator<(const tuple <T0, T1, T2>& t0, const tuple <T0, T1, T2>& t1)
{
    if (t0._0 < t1._0)
        return true;
    else if (t0._0 == t1._0  &&  t0._1 < t1._1)
        return true;
    else if (t0._0 == t1._0  &&  t0._1 == t1._1  &&  t0._2 < t1._2)
        return true;
    else
        return false;
};

template<typename T0, typename T1, typename T2>
std::ostream& operator<< (std::ostream& o, const tuple <T0, T1, T2>& t)
{
    o << std::string("(") << t._0 << ", " << t._1 << ", " << t._2 << ")";
    return o;
};





template <typename T0, typename T1, typename T2, typename T3>
class tuple <T0, T1, T2, T3,
        null_type, null_type, null_type, null_type, null_type,
        null_type > {
public:
    T0  _0;
    T1  _1;
    T2  _2;
    T3  _3;

    tuple() {};
    tuple(const T0& v0, const T1& v1, const T2& v2, const T3& v3)
        : _0(v0), _1(v1), _2(v2), _3(v3) {};

    void assign (T0& r0, T1& r1, T2& r2, T3& r3) {
        r0 = _0;
        r1 = _1;
        r2 = _2;
        r3 = _3;
    };
};

template<typename T0, typename T1, typename T2, typename T3 >
tuple<T0, T1, T2, T3> make_tuple(const T0& v0, const T1& v1, const T2& v2, const T3& v3)
{
    return tuple<T0, T1, T2, T3>(v0, v1, v2, v3);
};

template <typename T0, typename T1, typename T2, typename T3>
bool operator<(const tuple <T0, T1, T2, T3>& t0, const tuple <T0, T1, T2, T3>& t1)
{
    if (t0._0 < t1._0)
        return true;
    else if (t0._0 == t1._0  &&  t0._1 < t1._1)
        return true;
    else if (t0._0 == t1._0  &&  t0._1 == t1._1  &&  t0._2 < t1._2)
        return true;
    else if (t0._0 == t1._0  &&  t0._1 == t1._1  &&  t0._2 == t1._2  &&  t0._3 < t1._3)
        return true;
    else
        return false;
};

template <typename T0, typename T1, typename T2, typename T3>
std::ostream& operator<< (std::ostream& o, const tuple <T0, T1, T2, T3>& t)
{
    o << std::string("(") << t._0 << ", " << t._1 << ", " << t._2 << ", " << t._3 << ")";
    return o;
};




template <typename T0, typename T1, typename T2, typename T3, typename T4>
class tuple <T0, T1, T2, T3, T4,
        null_type, null_type, null_type, null_type, null_type> {
public:
    T0  _0;
    T1  _1;
    T2  _2;
    T3  _3;
    T4  _4;

    tuple() {};
    tuple(const T0& v0, const T1& v1, const T2& v2, const T3& v3, const T4& v4)
        : _0(v0), _1(v1), _2(v2), _3(v3), _4(v4) {};

    void assign (T0& r0, T1& r1, T2& r2, T3& r3, T4& r4) {
        r0 = _0;
        r1 = _1;
        r2 = _2;
        r3 = _3;
        r4 = _4;
    };
};

template<typename T0, typename T1, typename T2, typename T3, typename T4 >
tuple<T0, T1, T2, T3, T4> make_tuple(const T0& v0, const T1& v1, const T2& v2, const T3& v3, const T4& v4)
{
    return tuple<T0, T1, T2, T3, T4>(v0, v1, v2, v3, v4);
};

template <typename T0, typename T1, typename T2, typename T3, typename T4>
bool operator<(const tuple <T0, T1, T2, T3, T4>& t0, const tuple <T0, T1, T2, T3, T4>& t1)
{
    if (t0._0 < t1._0)
        return true;
    else if (t0._0 == t1._0  &&  t0._1 < t1._1)
        return true;
    else if (t0._0 == t1._0  &&  t0._1 == t1._1  &&  t0._2 < t1._2)
        return true;
    else if (t0._0 == t1._0  &&  t0._1 == t1._1  &&  t0._2 == t1._2  &&  t0._3 < t1._3)
        return true;
    else if (t0._0 == t1._0  &&  t0._1 == t1._1  &&  t0._2 == t1._2  &&  t0._3 == t1._3  &&  t0._4 < t1._4)
        return true;
    else
        return false;
};

template <typename T0, typename T1, typename T2, typename T3, typename T4>
std::ostream& operator<< (std::ostream& o, const tuple <T0, T1, T2, T3, T4>& t)
{
    o << std::string("(") << t._0 << ", " << t._1 << ", " << t._2 << ", " << t._3 << ", " << t._4 << ")";
    return o;
};



};  //  namespace mtk {


#endif

