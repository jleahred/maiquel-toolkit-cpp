BEGIN_INIT

INCLUDES = ['#include "support/mtk_string.h"' ]
NAMESPACES = ['mtk', 'gen', 'msg']

END_INIT



//---------------------------------------------------------------------
//
//
//---------------------------------------------------------------------



pub_email  [< QE:ALL_GS, RT:2, SUBJ:GS.EMAIL   >]
{
    eto             (eto)        :       string
    esubject        (esubj)      :       string
    emessage        (emsg)       :       string
}

