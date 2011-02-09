#include "call_later.h"


namespace mtk {

mtk::CountPtr<mtk::list<mtk::CountPtr<__internal_abstract_call_later_emiter> > > __internal_later_call_emiters;

void __internal_process_call_later1s(void)
{
        mtk::list<mtk::CountPtr<__internal_abstract_call_later_emiter> >::iterator it = __internal_later_call_emiters->begin();
        while (it!=__internal_later_call_emiters->end())
        {
            bool result = true;
            try
            {
                result = (*it)->check_and_emit();
            } 
            MTK_CATCH_CALLFUNCION(mtk::AlarmMsg , MTK_HERE, "error processing call_later")
            
            if (result == true)
                it = __internal_later_call_emiters->erase(it);
            else
                ++it;
        }
}


void __internal_call_later_nevercall_me_release_on_exit(void)
{
    //delete __internal_later_call_emiters;
    //__internal_later_call_emiters = 0;    
    if (__internal_later_call_emiters.isValid())
        __internal_later_call_emiters = mtk::make_cptr(new mtk::list<mtk::CountPtr<__internal_abstract_call_later_emiter> >());
}



};  // namespace mtk {
