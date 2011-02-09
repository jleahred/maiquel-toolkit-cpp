#include "qmtk_misc.h"






QString fn_as_QString(const mtk::FixedNumber& fn)
{
    return QString::number(fn.GetDouble().get()._0, 'f', fn.GetExt().GetDec());
}
