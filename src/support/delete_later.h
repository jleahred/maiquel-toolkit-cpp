#ifndef __DELETE_LATER__H
#define __DELETE_LATER__H




#include "support/mtk_string.h"
#include "support/exec_max_frec.h"
#include "support/timer.h"
#include "support/list.hpp"
#include "support/count_ptr.hpp"




namespace  mtk {

bool& __internal__get_delete_later_clossing(void);


template<typename T>
mtk::list<mtk::tuple<mtk::dtDateTime, CountPtr<T> > >&  get_list_to_delete(void)
{
    static  auto  result = new mtk::list<mtk::tuple<mtk::dtDateTime, CountPtr<T> > >{};
    return  *result;
}

template<typename T>
void  check_to_delete (void)
{
    auto& list_to_delete = get_list_to_delete<T>();

    if(list_to_delete.size()  ==  0)
    {
        MTK_EXEC_MAX_FREC_S(mtk::dtSeconds(30))
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "check_to_delete", MTK_SS("Called with empty list"), mtk::alPriorError));
        MTK_END_EXEC_MAX_FREC
        return;
    }


    auto it= list_to_delete.begin();
    while(it != list_to_delete.end())
    {
        mtk::tuple<mtk::dtDateTime, CountPtr<T> >&  item = *it;
        if(item._0 + mtk::dtMilliseconds(500)  < mtk::dtNowLocal())
            it = list_to_delete.erase(it);
        else
            ++it;
    }
    if(list_to_delete.size() == 0)
        MTK_TIMER_1SF_STOP(check_to_delete<T>);
}


template<typename T>
void  delete_later(const CountPtr<T>& obj)
{
    if(__internal__get_delete_later_clossing()) return;

    if(obj.getCount()  ==  0)
    {
        MTK_EXEC_MAX_FREC_S(mtk::dtSeconds(30))
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "delete_later", MTK_SS("Invalid count: " << obj.getCount()), mtk::alPriorError));
        MTK_END_EXEC_MAX_FREC
    }

    auto& list_to_delete = get_list_to_delete<T>();
    list_to_delete.push_back(mtk::make_tuple(mtk::dtNowLocal(),obj));

    if(list_to_delete.size() == 1)
        MTK_TIMER_1SF(check_to_delete<T>);
}







template  <typename  __IMPL__>
class  delete_later_wrapper
{
    public:
        explicit delete_later_wrapper(const mtk::CountPtr<__IMPL__>&  impl)
            :   __impl(impl)
        {
        }
        ~delete_later_wrapper(void)   { mtk::delete_later(__impl); }


        CountPtr<__IMPL__>             __impl;
};


void  __internal_delete_later_nevercall_me____release_on_exit(void);

#define     RELEASE____internal_delete_later_nevercall_me____release_on_exit   mtk::__internal_delete_later_nevercall_me____release_on_exit();


};      //  end namespace mtk

#endif      //__DELETE_LATER__H
