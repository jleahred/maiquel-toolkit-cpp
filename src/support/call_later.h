#ifndef idCallLaterH
#define idCallLaterH




//#include <iostream>     //  no es debug, revisar porqué es necesario esto
//
#include "support/timer.h"
#include "support/signalslot.hpp"
#include "support/list.hpp"
#include "support/count_ptr.hpp"
#include "support/map.hpp"



#define MTK_CALL_LATER1S_THIS(__INTERVAL__, __DATA__, __METHOD__)  \
        mtk::CallLaterFactory1S(__INTERVAL__, __DATA__).connect(this, &CLASS_NAME::__METHOD__);

#define MTK_CALL_LATER1S_F(__INTERVAL__, __DATA__, __FUNCTION__)  \
        mtk::CallLaterFactory1S(__INTERVAL__, __DATA__).connect(__FUNCTION__);




namespace mtk {





class __internal_abstract_call_later_emiter
{
public:
    virtual ~__internal_abstract_call_later_emiter(void) {};
    virtual bool check_and_emit(void) = 0;
};


template<typename T>
class __internal_call_later_emiter : public __internal_abstract_call_later_emiter
{
    mtk::non_copyable nc;

public:
    __internal_call_later_emiter(mtk::DateTime _when, const T& _data) 
            : when (_when), data(_data) {}

    mtk::DateTime           when;
    mtk::Signal<const T&>   signal;
    T                       data;
    virtual bool check_and_emit(void)  
    {  
        if (when <= mtk::dtNowLocal())
        {
            signal.emit(data);  
            return true;
        }
        else return false;
    }
};


extern mtk::CountPtr<mtk::list<mtk::CountPtr<__internal_abstract_call_later_emiter> > > __internal_later_call_emiters;

void __internal_process_call_later1s(void);

template <typename T>
mtk::Signal<const T&>&  CallLaterFactory1S (mtk::dtTimeQuantity interval, const T& data)
{
    mtk::DateTime when = mtk::dtNowLocal() + interval;

    if (__internal_later_call_emiters.isValid() == false)
    {
        __internal_later_call_emiters = mtk::make_cptr(new mtk::list<mtk::CountPtr<__internal_abstract_call_later_emiter> >());
        mtk::Timer::instance()->signal1s.connect(&__internal_process_call_later1s);
    }

    mtk::CountPtr<__internal_call_later_emiter<T> > new_item = mtk::make_cptr(new __internal_call_later_emiter<T>(when, data));

    __internal_later_call_emiters->push_back(mtk::CountPtr<__internal_abstract_call_later_emiter >(new_item));

    return new_item->signal;
}





void __internal_call_later_nevercall_me_release_on_exit(void);
#define RELEASE___internal_call_later_nevercall_me_release_on_exit  mtk::__internal_call_later_nevercall_me_release_on_exit();



};      //  end namespace mtk

#endif
