
#include "alarm.h"
#include "mtk_string.h"



namespace mtk {
//---------------------------------------------------------------------------

int Alarm::classAlarmId=0;



void write_time (std::ostream& os, const DateTime& dt)
{
    os.width(2); os.fill('0');
    os << dt.GetHours().WarningDontDoThisGetInternal() << ":";
    os.width(2); os.fill('0');
    os << dt.GetMinutes().WarningDontDoThisGetInternal() << ":";
    os.width(2); os.fill('0');
    os << dt.GetSeconds().WarningDontDoThisGetInternal() << ".";
    os.width(3); os.fill('0');
    os << dt.GetMilliseconds().WarningDontDoThisGetInternal();
}


void write_body (std::ostream& os, const BaseAlarm& a)
{
    if      (a.priority == alPriorCritic      )
        os << " CRIT.";
    else if (a.priority == alPriorError  )
        os << " ERROR";
    else if (a.priority == alPriorWarning)
        os << " Warn ";
    else if (a.priority == alPriorDebug  )
        os << " debug";
    else if (a.priority == alPriorStats  )
        os << " stats";
    else
        os << " [" << int(a.priority) << "]";

    if      (a.type == alTypeNoPermisions )
        os << " NoPerm";
    else if (a.type == alTypeOverflow     )
        os << " Overfl";
    else if (a.type == alTypeRealTime     )
        os << " RealTm";
    else if (a.type == alTypeUnknown      )
        os << " Unkown";
    else
        os << " <" << int(a.type) << ">";


    os  << " # " << a.message
        << " @" << a.codeSource;
}


std::ostream& operator<< (std::ostream& os, const BaseAlarm& a)
{
    write_time(os, a.dateTime);
    write_body(os, a);

    return os;
};

std::ostream& operator<< (std::ostream& os, const Alarm& a)
{
    os << static_cast<const BaseAlarm&>(a);
    
    if (a.stackAlarms.size()>0)
        os << " [" << a.alarmID << "]";

    std::list<BaseAlarm>::const_iterator it = a.stackAlarms.begin();
    while (it != a.stackAlarms.end())
    {
        os << std::endl;
        os <<  s_AlignRight(MTK_SS(it->dateTime - a.dateTime), 12);
        write_body(os, *it);
        ++it;
    }

    return os;
};

//---------------------------------------------------------------------------
};      //  namespace mtk {

