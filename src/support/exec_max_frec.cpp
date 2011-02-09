#include "exec_max_frec.h"



namespace mtk {
//---------------------------------------------------------------------------



emfCheckMaxFrec::emfCheckMaxFrec (dtTimeQuantity _intervalCheck)
    :
        intervalCheck   (_intervalCheck),
        previusValidated(dtNowLocal()-dtDays(1))
{
}


bool  emfCheckMaxFrec::Check(void)
{
    dtDateTime now = dtNowLocal();

    //  verificación cambio de hora hacia atrás...
    if (previusValidated > now)
        previusValidated = now - dtDays(1);

    if (previusValidated + intervalCheck < now) {
        previusValidated = now;
        return true;
    }
    else
        return false;
}













//---------------------------------------------------------------------------
};      //namespace mtk {
