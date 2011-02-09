#ifndef mtkBasicTypesH
#define mtkBasicTypesH



#include "platform.hpp"



namespace mtk {

class non_copyable {
    non_copyable(const non_copyable&);
    non_copyable& operator=(const non_copyable&);

public:
    non_copyable() {}
    ~non_copyable() {}
};


struct null_type{};




//--------------------------------------------------------------------
//  Template IF for types   //  esto se debería pasar al fichero de tipos básicos
//--------------------------------------------------------------------
template <bool condition, class Then, class Else>
struct t_IF_TYPE
{
    typedef Then RET;
};

template <class Then, class Else>
struct t_IF_TYPE<false, Then, Else>
{
    typedef Else RET;
};




};  //  namespace mtk {

#if (MTK_PLATFORM == MTK_LINUX_PLATFORM)

    typedef long long  __int64;

#endif


#endif

