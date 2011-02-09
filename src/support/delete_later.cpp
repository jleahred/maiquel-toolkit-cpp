#include "delete_later.h"




namespace  mtk {


bool& __internal__get_delete_later_clossing(void)
{
    static  bool*  result = new bool(false);

    return *result;
}

void  __internal_delete_later_nevercall_me____release_on_exit(void)
{
    __internal__get_delete_later_clossing() = true;
}




};      //  end namespace mtk


