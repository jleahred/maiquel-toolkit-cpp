//---------------------------------------------------------------------------
//#include <iostream>


#include "date_time.h"
#include "alarm.h"






#ifndef MTK_PLATFORM
    #error  "mtk::   NO ESTÁ CARGADO EL FICHERO DE CONFIGURACIÓN  soposupport/form.h"
#endif

#if (MTK_PLATFORM == MTK_WIN_PLATFORM)


    #include <windows.h>

#elif MTK_PLATFORM == MTK_LINUX_PLATFORM

    #include <sys/timeb.h>

#endif


#include <math.h>       //  fbabs


//---------------------------------------------------------------------------

namespace mtk{


const  int  VCL_DAYS_DIFERENCE =    693899;
const  int  MILLISECS_ON_DAY    = 86400000;






//--------------------------------------------------------------------------

//              T i m e Q u a n t i t y

//--------------------------------------------------------------------------



//  CONSTRUCTORES   ____________________________________________________

dtTimeQuantity::dtTimeQuantity (dtTimeQuantitySerialNumber    _timeQuantitySerNumber)
    :
       timeQuantitySerialNumber (_timeQuantitySerNumber                 ),
       decodedTime              (false                                  ),
       sign                     (0                                      ),
       days                     (0                                      ),
       millisecsDay             (0                                      ),
       hours                    (0                                      ),
       mins                     (0                                      ),
       secs                     (0                                      ),
       millisecs                (0                                      )
{
}

dtTimeQuantity::dtTimeQuantity (dtMillisecsDay        _millisecsDay     )
    :
       timeQuantitySerialNumber (double(_millisecsDay.WarningDontDoThisGetInternal())/MILLISECS_ON_DAY ),
       decodedTime              (false                                  ),
       sign                     (0                                      ),
       days                     (0                                      ),
       millisecsDay             (0                                      ),
       hours                    (0                                      ),
       mins                     (0                                      ),
       secs                     (0                                      ),
       millisecs                (0                                      )
{
    if (_millisecsDay.WarningDontDoThisGetInternal()  >  MILLISECS_ON_DAY)
        throw   Alarm (
                        MTK_HERE,
                        "Inicialización   _millisecsDay  > un día",
                        alPriorError, alTypeNoPermisions
                );
    if (_millisecsDay.WarningDontDoThisGetInternal()  <  0)
        throw   Alarm (
                        MTK_HERE,
                        "Inicialización   _millisecsDay  < 0",
                        alPriorError, alTypeNoPermisions
                );
}


dtTimeQuantity::dtTimeQuantity (dtDays                   _days          ,
                                dtMillisecsDay           _millisecsDay  )
    :
  timeQuantitySerialNumber (double(_days.WarningDontDoThisGetInternal())+double(_millisecsDay.WarningDontDoThisGetInternal())/MILLISECS_ON_DAY),
       decodedTime              (false                                  ),
       sign                     (0                                      ),
       days                     (0                                      ),
       millisecsDay             (0                                      ),
       hours                    (0                                      ),
       mins                     (0                                      ),
       secs                     (0                                      ),
       millisecs                (0                                      )
{
    if (_millisecsDay.WarningDontDoThisGetInternal() <0)
        throw   Alarm (
                        MTK_HERE,
                        "Inicialización   millisecsDay  < 0",
                        alPriorError, alTypeNoPermisions
                );

    if (_millisecsDay.WarningDontDoThisGetInternal()  >  MILLISECS_ON_DAY)
        throw   Alarm (
                        MTK_HERE,
                        "Inicialización   millisecsDay  > un día",
                        alPriorError, alTypeNoPermisions
                );

    if (_days.WarningDontDoThisGetInternal() <0)
        throw   Alarm (
                        MTK_HERE,
                        "Inicialización   days  < 0",
                        alPriorError, alTypeNoPermisions
                );
}

dtTimeQuantity::dtTimeQuantity (dtDays                   _days          ,
                                dtHours                  _hours         ,
                                dtMinutes                _minutes       ,
                                dtSeconds                _secs          ,
                                dtMilliseconds           _millisecs     )
    :
       timeQuantitySerialNumber (0                                      ),
       decodedTime              (true                                   ),
       sign                     (1                                      ),
       days                     (_days                                  ),
       millisecsDay             (0                                      ),
       hours                    (_hours                                 ),
       mins                     (_minutes                               ),
       secs                     (_secs                                  ),
       millisecs                (_millisecs                             )
{
    if (_hours.WarningDontDoThisGetInternal()>=24  ||  _minutes.WarningDontDoThisGetInternal()>=60  ||  _secs.WarningDontDoThisGetInternal()>=60   ||  _millisecs.WarningDontDoThisGetInternal()>=1000)
        throw   Alarm (
                        MTK_HERE,
                        "Error  dtTimeQuantity   values out of rage init",
                        alPriorError, alTypeNoPermisions
                );

    if (_days.WarningDontDoThisGetInternal() <0  || _hours.WarningDontDoThisGetInternal()<0    ||  _minutes.WarningDontDoThisGetInternal()<0    ||  _secs.WarningDontDoThisGetInternal()<0     ||  _millisecs.WarningDontDoThisGetInternal()<0    )
        throw   Alarm (
                        MTK_HERE,
                        "Error  dtTimeQuantity   values out of rage init <0",
                        alPriorError, alTypeNoPermisions
                );

    millisecsDay     =  dtMillisecsDay (
                            hours.WarningDontDoThisGetInternal()  *60*60*1000 +
                            mins.WarningDontDoThisGetInternal()      *60*1000 +
                            secs.WarningDontDoThisGetInternal()         *1000 +
                            millisecs.WarningDontDoThisGetInternal()
                        );

    timeQuantitySerialNumber =
                dtTimeQuantitySerialNumber(
                                days.WarningDontDoThisGetInternal() + double(millisecsDay.WarningDontDoThisGetInternal())/MILLISECS_ON_DAY
                 );
}

dtTimeQuantity::dtTimeQuantity (dtHours                 _hours          ,
                                dtMinutes               _minutes        ,
                                dtSeconds               _secs           ,
                                dtMilliseconds          _millisecs      )
    :
       timeQuantitySerialNumber (0                                      ),
       decodedTime              (true                                   ),
       sign                     (1                                      ),
       days                     (0                                      ),
       millisecsDay             (0                                      ),
       hours                    (_hours                                 ),
       mins                     (_minutes                               ),
       secs                     (_secs                                  ),
       millisecs                (_millisecs                             )
{
    if (_hours.WarningDontDoThisGetInternal()>=24  ||  _minutes.WarningDontDoThisGetInternal()>=60  ||  _secs.WarningDontDoThisGetInternal()>=60   ||  _millisecs.WarningDontDoThisGetInternal()>=1000)
        throw   Alarm (
                        MTK_HERE,
                        "Error  dtTimeQuantity   values out of rage init",
                        alPriorError, alTypeNoPermisions
                );

    if (_hours.WarningDontDoThisGetInternal()<0    ||  _minutes.WarningDontDoThisGetInternal()<0    ||  _secs.WarningDontDoThisGetInternal()<0     ||  _millisecs.WarningDontDoThisGetInternal()<0    )
        throw   Alarm (
                        MTK_HERE,
                        "Error  dtTimeQuantity   values out of rage init <0",
                        alPriorError, alTypeNoPermisions
                );

    millisecsDay     =  dtMillisecsDay (
                            hours.WarningDontDoThisGetInternal()  *60*60*1000 +
                            mins.WarningDontDoThisGetInternal()      *60*1000 +
                            secs.WarningDontDoThisGetInternal()         *1000 +
                            millisecs.WarningDontDoThisGetInternal()
                        );

    timeQuantitySerialNumber =
                dtTimeQuantitySerialNumber(
                                days.WarningDontDoThisGetInternal() + double(millisecsDay.WarningDontDoThisGetInternal())/MILLISECS_ON_DAY
                 );
}





//  Conversiones implícitas ___________________________________________


dtTimeQuantity::dtTimeQuantity  (dtQMinutes         _minutes                )
    :
       timeQuantitySerialNumber ((_minutes.WarningDontDoThisGetInternal()*60*1000)/MILLISECS_ON_DAY        ),
       decodedTime              (false                                      ),
       sign                     (0                                          ),
       days                     (0                                          ),
       millisecsDay             (0                                          ),
       hours                    (0                                          ),
       mins                     (0                                          ),
       secs                     (0                                          ),
       millisecs                (0                                          )
{
}

dtTimeQuantity::dtTimeQuantity  (dtQSeconds        _seconds                 )
    :
       timeQuantitySerialNumber ((_seconds.WarningDontDoThisGetInternal()*1000)/MILLISECS_ON_DAY           ),
       decodedTime              (false                                      ),
       sign                     (0                                          ),
       days                     (0                                          ),
       millisecsDay             (0                                          ),
       hours                    (0                                          ),
       mins                     (0                                          ),
       secs                     (0                                          ),
       millisecs                (0                                          )
{
}


dtTimeQuantity::dtTimeQuantity  (dtDays           _days                 )
    :
       timeQuantitySerialNumber (double(_days.WarningDontDoThisGetInternal())                      ),
       decodedTime              (false                                  ),
       sign                     (0                                      ),
       days                     (0                                      ),
       millisecsDay             (0                                      ),
       hours                    (0                                      ),
       mins                     (0                                      ),
       secs                     (0                                      ),
       millisecs                (0                                      )
{
}

dtTimeQuantity::dtTimeQuantity  (dtHours          _hours                    )
    :
       timeQuantitySerialNumber (double(_hours.WarningDontDoThisGetInternal()*60*60*1000)/MILLISECS_ON_DAY ),
       decodedTime              (false                                      ),
       sign                     (0                                      ),
       days                     (0                                          ),
       millisecsDay             (0                                          ),
       hours                    (0                                          ),
       mins                     (0                                          ),
       secs                     (0                                          ),
       millisecs                (0                                          )
{
}

dtTimeQuantity::dtTimeQuantity  (dtMinutes        _minuts                   )
    :
       timeQuantitySerialNumber (double(_minuts.WarningDontDoThisGetInternal()*60*1000)/MILLISECS_ON_DAY   ),
       decodedTime              (false                                      ),
       sign                     (0                                          ),
       days                     (0                                          ),
       millisecsDay             (0                                          ),
       hours                    (0                                          ),
       mins                     (0                                          ),
       secs                     (0                                          ),
       millisecs                (0                                          )
{
}

dtTimeQuantity::dtTimeQuantity  (dtSeconds        _seconds                  )
    :
       timeQuantitySerialNumber (double(_seconds.WarningDontDoThisGetInternal()*1000)/MILLISECS_ON_DAY     ),
       decodedTime              (false                                      ),
       sign                     (0                                          ),
       days                     (0                                          ),
       millisecsDay             (0                                          ),
       hours                    (0                                          ),
       mins                     (0                                          ),
       secs                     (0                                          ),
       millisecs                (0                                          )
{
}

dtTimeQuantity::dtTimeQuantity  (dtMilliseconds   _milliseconds             )
    :
       timeQuantitySerialNumber (double(_milliseconds.WarningDontDoThisGetInternal())/MILLISECS_ON_DAY ),
       decodedTime              (false                                      ),
       sign                     (0                                          ),
       days                     (0                                          ),
       millisecsDay             (0                                          ),
       hours                    (0                                          ),
       mins                     (0                                          ),
       secs                     (0                                          ),
       millisecs                (0                                          )
{
}


dtTimeQuantity::dtTimeQuantity  (dtTotalMillisecs   _milliseconds           )
    :
       timeQuantitySerialNumber (double(_milliseconds.WarningDontDoThisGetInternal())/MILLISECS_ON_DAY ),
       decodedTime              (false                                      ),
       sign                     (0                                          ),
       days                     (0                                          ),
       millisecsDay             (0                                          ),
       hours                    (0                                          ),
       mins                     (0                                          ),
       secs                     (0                                          ),
       millisecs                (0                                          )
{
}






//  OPERADORES      ____________________________________________________

    //  relacionales
bool      dtTimeQuantity::operator  ==  (const dtTimeQuantity& ti) const
{
    DecodeTime();
    ti.DecodeTime();

    if ( sign == ti.sign  &&  days == ti.days)
        if (millisecsDay == ti.millisecsDay  ||
                (    millisecsDay.WarningDontDoThisGetInternal() - ti.millisecsDay.WarningDontDoThisGetInternal() <   2
                &&   millisecsDay.WarningDontDoThisGetInternal() - ti.millisecsDay.WarningDontDoThisGetInternal() >  -2
                )
            )
            return true;

    return false;
}

bool      dtTimeQuantity::operator  !=  (const dtTimeQuantity& ti) const
{
    return !operator==(ti);
}

bool      dtTimeQuantity::operator  <   (const dtTimeQuantity& ti) const
{
    bool result;
    DecodeTime();
    ti.DecodeTime();

    //  primero hacemos una comparación abs
    //  luego ajustamos según el signo


    if (sign < ti.sign)
        return true;
    else if (sign > ti.sign)
        return false;
    //  a partir de ahora sabemos que el signo es igual
    else if ( days < ti.days )
        result = true;
    else if ( days > ti.days )
        result = false;
    else if ( millisecsDay < ti.millisecsDay)
        result = true;
    else
        result = false;

    //  sabemos que tienen el mismo signo, y en result tenemos el resultado
    //  de la comparación abs
    if (sign > 0)       //  sólo puede ser 1 o -1
        return result;
    else
        return !result;

}

bool      dtTimeQuantity::operator  <=  (const dtTimeQuantity& ti) const
{
    if (operator==(ti))
        return true;
    else if (operator<(ti))
        return true;
    else
        return false;
}

bool      dtTimeQuantity::operator  >   (const dtTimeQuantity& ti) const
{
    return !operator<=(ti);
}

bool      dtTimeQuantity::operator  >=  (const dtTimeQuantity& ti) const
{
    return !operator<(ti);
}



    //  aritméticos
dtTimeQuantity        dtTimeQuantity::operator-     (void) const
{
    return dtTimeQuantity(
                    dtTimeQuantitySerialNumber(
                        -double(
                            timeQuantitySerialNumber.WarningDontDoThisGetInternal()
                        )
                    )
            );
}


dtTimeQuantity        dtTimeQuantity::operator  +   (const dtTimeQuantity& ti) const
{
    return dtTimeQuantity(
                dtTimeQuantitySerialNumber(
                        timeQuantitySerialNumber.WarningDontDoThisGetInternal()
                        +
                        ti.timeQuantitySerialNumber.WarningDontDoThisGetInternal()
                )
        );
}

dtTimeQuantity&       dtTimeQuantity::operator  +=  (const dtTimeQuantity& ti)
{
    //  poco eficiente, más seguro, más cómodo
    *this = *this + ti;
    return *this;
}

dtTimeQuantity        dtTimeQuantity::operator  -   (const dtTimeQuantity& ti) const
{
    return operator+(-ti);

//    return dtTimeQuantity(
//                dtTimeQuantitySerialNumber(
//                        timeQuantitySerialNumber
//                        -
//                        ti.timeQuantitySerialNumber
//                )
//        );
}

dtTimeQuantity&       dtTimeQuantity::operator  -=  (const dtTimeQuantity& ti)
{
    *this = *this - ti;
    return *this;
}








//  ACCESO  (en ocasiones perezoso)  __________________________________




dtDecodedTimeQuantity   dtTimeQuantity::GetDecodedTimeQuantity    (void) const
{
    DecodeTime();
    return dtDecodedTimeQuantity(
                sign,
                days,
                hours,
                mins,
                secs,
                millisecs
            );
}

dtTimeQuantitySerialNumber  dtTimeQuantity::GetQuantitySerialNumber (void) const
{
    DecodeTime();
    return timeQuantitySerialNumber;
}





bool dtTimeQuantity::IsNegative                (void) const
{
    if (sign<0)
        return true;
    else
        return false;
}

bool dtTimeQuantity::IsPositive                (void) const
{
    return !IsNegative();
}




void dtTimeQuantity::DecodeTime (void)  const
{
    if (decodedTime == true)
        return;

    dtTimeQuantitySerialNumber absTimeQuantitySerialNumber =
                dtTimeQuantitySerialNumber(fabs(timeQuantitySerialNumber.WarningDontDoThisGetInternal()));
    if (timeQuantitySerialNumber.WarningDontDoThisGetInternal() < 0.)
        sign = -1;
    else
        sign =  1;

    days = dtDays ( int(absTimeQuantitySerialNumber.WarningDontDoThisGetInternal()) );

    millisecsDay =
            dtMillisecsDay(
                int(
                    (absTimeQuantitySerialNumber.WarningDontDoThisGetInternal() - days.WarningDontDoThisGetInternal())
                    * MILLISECS_ON_DAY
                    +0.5
                )
            );

    hours     = dtHours        ( millisecsDay.WarningDontDoThisGetInternal()/(60*60*1000) );

    mins      = dtMinutes      ( millisecsDay.WarningDontDoThisGetInternal()/(   60*1000) 
				 - hours.WarningDontDoThisGetInternal()              *60);

    secs      = dtSeconds      ( millisecsDay.WarningDontDoThisGetInternal()/(      1000) 
				 - hours.WarningDontDoThisGetInternal()           *60*60      
				 - mins.WarningDontDoThisGetInternal()               *60);

    millisecs = dtMilliseconds ( millisecsDay.WarningDontDoThisGetInternal()              
				 - hours.WarningDontDoThisGetInternal()      *60*60*1000 
				 - mins.WarningDontDoThisGetInternal()          *60*1000 
				 - secs.WarningDontDoThisGetInternal()             *1000);


    decodedTime = true;
}






std::ostream& operator<< (std::ostream& o, const dtTimeQuantity& tq)
{
    dtDecodedTimeQuantity dti= tq.GetDecodedTimeQuantity();


    if (dti.sign<0)
        o << "-";


    if (dti.days.WarningDontDoThisGetInternal()>=1)
    {
        o << dti.days.WarningDontDoThisGetInternal() << "d ";
    }

    if (dti.hours.WarningDontDoThisGetInternal()>=1)
    {
        o << dti.hours.WarningDontDoThisGetInternal() << "h ";
    }

    if (dti.minutes.WarningDontDoThisGetInternal()>=1)
    {
        o << dti.minutes.WarningDontDoThisGetInternal() << "m ";
    }

    if (dti.seconds.WarningDontDoThisGetInternal()>=1)
    {
        o << dti.seconds.WarningDontDoThisGetInternal() << "s ";
    }

    if (dti.milliseconds.WarningDontDoThisGetInternal()>=1)
    {
        o << dti.milliseconds.WarningDontDoThisGetInternal() << "ms";
    }
    return o;
};










//--------------------------------------------------------------------------

//              D a t e T i m e

//--------------------------------------------------------------------------


    //  CONSTRUCTORES   ____________________________________________________

DateTime::DateTime( dtYear                        _year                 ,
                    dtMonth                       _month                ,
                    dtDay                         _day                  )
    :
        timeQuantity    (dtTimeQuantitySerialNumber(0)),
        decodedDate     (true  ),
        year            (_year ),
        month           (_month),
        day             (_day  ),
        hours           (0     ),
        minutes         (0     ),
        seconds         (0     ),
        milliseconds    (0     )
{
    timeQuantity = EncodeDate(_year, _month, _day);
    DecodeDate();
    if (year != _year  ||  month != _month  ||  day != _day)
        throw   Alarm (
                        MTK_HERE,
                        "Invalid argument DateTime(dtYear _year, dtMonth _month, dtDay _day",
                        alPriorError, alTypeNoPermisions
                );

}


DateTime::DateTime( dtYear                        _year                 ,
                    dtMonth                       _month                ,
                    dtDay                         _day                  ,
                    dtTimeQuantity                _timeQuantity         )
    :
        timeQuantity    (dtTimeQuantitySerialNumber(0)),
        decodedDate     (true  ),
        year            (_year ),
        month           (_month),
        day             (_day  ),
        hours           (0     ),
        minutes         (0     ),
        seconds         (0     ),
        milliseconds    (0     )
{
    timeQuantity  =  EncodeDate(_year, _month, _day);
    DecodeDate();       //  esto reajustará las horas, minutos, etc...
    if (year != _year  ||  month != _month  ||  day != _day)
        throw   Alarm (
                        MTK_HERE,
                        "Invalid argument DateTime(dtYear _year, dtMonth _month, dtDay _day",
                        alPriorError, alTypeNoPermisions
                );
    timeQuantity += _timeQuantity;
}



DateTime::DateTime     (dtYear                        _year                 ,
                        dtMonth                       _month                ,
                        dtDay                         _day                  ,
                        dtHours                       _hour                 ,
                        dtMinutes                     _minutes              ,
                        dtSeconds                     _seconds              ,
                        dtMilliseconds                _milliseconds         )
    :
        timeQuantity    (dtTimeQuantitySerialNumber(0)),
        decodedDate     (true           ),
        year            (_year          ),
        month           (_month         ),
        day             (_day           ),
        hours           (_hour          ),
        minutes         (_minutes       ),
        seconds         (_seconds       ),
        milliseconds    (_milliseconds  )
{
    timeQuantity = EncodeDate(_year, _month, _day);
    timeQuantity += dtTimeQuantity (_hour, _minutes, _seconds, _milliseconds);
    DecodeDate();
    if (year != _year  ||  month != _month  ||  day != _day)
        throw   Alarm (
                        MTK_HERE,
                        "Invalid argument DateTime(dtYear _year, dtMonth _month, dtDay _day",
                        alPriorError, alTypeNoPermisions
                );
    if (hours != _hour  ||  minutes != _minutes  ||  seconds != _seconds)
        throw   Alarm (
                        MTK_HERE,
                        "Invalid argument DateTime(h,m,s,ms",
                        alPriorError, alTypeNoPermisions
                );
    if (milliseconds != _milliseconds  &&
            (milliseconds.WarningDontDoThisGetInternal()-_milliseconds.WarningDontDoThisGetInternal() >1
            || milliseconds.WarningDontDoThisGetInternal()-_milliseconds.WarningDontDoThisGetInternal() < -1)
        )
        throw   Alarm (
                        MTK_HERE,
                        "Invalid argument DateTime(h,m,s,ms",
                        alPriorError, alTypeNoPermisions
                );

}




//  OPERADORES      ____________________________________________________

    //  relacionales
bool     DateTime::operator  ==  (const DateTime&     dt) const
{
    return timeQuantity == dt.timeQuantity;
}

bool     DateTime::operator  !=  (const DateTime&     dt) const
{
    return timeQuantity != dt.timeQuantity;
}

bool     DateTime::operator  <   (const DateTime&     dt) const
{
    return timeQuantity < dt.timeQuantity;
}

bool     DateTime::operator  <=  (const DateTime&     dt) const
{
    return timeQuantity <= dt.timeQuantity;
}

bool     DateTime::operator  >   (const DateTime&     dt) const
{
    return timeQuantity >  dt.timeQuantity;
}

bool     DateTime::operator  >=  (const DateTime&     dt) const
{
    return timeQuantity >= dt.timeQuantity;
}



    //  aritméticos
DateTime&           DateTime::operator  ++  (void)
{
    *this = DateTime(timeQuantity+dtDays(1));
    return *this;
}

const DateTime      DateTime::operator  ++  (int )
{
    DateTime prev (*this);
    *this = DateTime(timeQuantity+dtDays(1));
    return prev;
}

DateTime&           DateTime::operator  --  (void)
{
    *this = DateTime(timeQuantity-dtDays(1));
    return *this;
}

const DateTime      DateTime::operator  --  (int )
{
    DateTime prev (*this);
    *this = DateTime(timeQuantity-dtDays(1));
    return prev;
}

dtTimeQuantity        DateTime::operator  -   (const DateTime&         dt) const
{
    return timeQuantity -  dt.timeQuantity;
}


DateTime       DateTime::operator  +   (const dtTimeQuantity& ti) const
{
    return  DateTime(
                    dtTimeQuantity(
                        dtTimeQuantitySerialNumber(
                              double(timeQuantity.GetQuantitySerialNumber().WarningDontDoThisGetInternal())
                              +
                              double(ti.GetQuantitySerialNumber().WarningDontDoThisGetInternal())
                        )
                    )
            );
}

DateTime       DateTime::operator  -   (const dtTimeQuantity& ti) const
{
    return *this + (-ti);

//    return  DateTime(
//                    dtTimeQuantity(
//                        dtTimeQuantitySerialNumber(
//                              double(timeQuantity.GetQuantitySerialNumber())
//                              -
//                              double(ti.GetQuantitySerialNumber())
//                        )
//                    )
//            );
}

DateTime&      DateTime::operator  +=  (const dtTimeQuantity& ti)
{
    *this = *this + ti;
    return  *this;
}

DateTime&      DateTime::operator  -=  (const dtTimeQuantity& ti)
{
    *this = *this - ti;
    return  *this;
}








//  ACCESO  (en ocasiones perezoso)  __________________________________

dtYear                        DateTime::GetYear                    (void) const
{
    DecodeDate();
    return year;
}

dtMonth                       DateTime::GetMonth                   (void) const
{
    DecodeDate();
    return month;
}

dtDay                         DateTime::GetDay                     (void) const
{
    DecodeDate();
    return day;
}


dtHours                       DateTime::GetHours                   (void) const
{
    DecodeDate();
    return hours;
}

dtMinutes                      DateTime::GetMinutes                (void) const
{
    DecodeDate();
    return minutes;
}

dtSeconds                     DateTime::GetSeconds                  (void) const
{
    DecodeDate();
    return seconds;
}

dtMilliseconds               DateTime::GetMilliseconds             (void) const
{
    DecodeDate();
    return milliseconds;
}


dtMillisecsDay          DateTime::GetMillisecsDay           (void) const
{
    return  dtMillisecsDay(
                int(
                        hours.WarningDontDoThisGetInternal()   * 60. * 60. *1000.
                      + minutes.WarningDontDoThisGetInternal()       * 60. *1000.
                      + seconds.WarningDontDoThisGetInternal()             *1000.
                      + milliseconds.WarningDontDoThisGetInternal()
                )
            );
}


dtTimeQuantitySerialNumber    DateTime::__WARNING_NOT_CALL_IT_internal_use_GetTimeQuantitySerialNumber(void) const
{
    return timeQuantity.GetQuantitySerialNumber();
}

DateTime WARNING_do_not_use_it__I_coul_kill_you_for_it__get_DateTime_from_time_quantity(dtTimeQuantity          _timeQuantity)
{
    return DateTime(_timeQuantity);
}


//dtVCLDateTimeSerialNumber     DateTime::GetVCLDateTimeSerialNumber (void) const
//{
//    return dtVCLDateTimeSerialNumber(
//                timeQuantity.GetQuantitySerialNumber().WarningDontDoThisGetInternal()-double(VCL_DAYS_DIFERENCE)
//            );
//}




//DateTime::DateTime (dtVCLDateTimeSerialNumber _vclDateTimeSerialNumber)
//    :
//        timeQuantity    (
//                dtTimeQuantitySerialNumber(
//                        _vclDateTimeSerialNumber.WarningDontDoThisGetInternal()+VCL_DAYS_DIFERENCE
//                    )
//            ),
//        decodedDate     (false  ),
//        year            (0      ),
//        month           (0      ),
//        day             (0      ),
//        hours           (0      ),
//        minutes         (0      ),
//        seconds         (0      ),
//        milliseconds    (0      )
//{
//}


DateTime::DateTime (dtTimeQuantity                _timeQuantity)
    :
        timeQuantity    (_timeQuantity),
        decodedDate     (false  ),
        year            (0      ),
        month           (0      ),
        day             (0      ),
        hours           (0      ),
        minutes         (0      ),
        seconds         (0      ),
        milliseconds    (0      )

{
}







void            DateTime::DecodeDate (void)  const
{
    __int64  sn = int (timeQuantity.GetQuantitySerialNumber().WarningDontDoThisGetInternal());     //  días desde...

    __int64  y = (10000*sn  + 14780)  / 3652425;

    int ddd = int ( sn - ( 365*y + y/4 - y/100 + y/400 ) );
    if (ddd < 0) {
        y--;
        ddd = int(  sn - ( 365*y + y/4 - y/100 + y/400 )  );
    }
    int mi = (100*ddd +52)/3060;
    int mm = (mi+2)%12 +1;
    y = y + (mi+2) /12;
    int dd = ddd - (mi*306 + 5)/10  +1;

    year  = dtYear (int(y));
    month = dtMonth(mm);
    day  =  dtDay  (dd);



    dtDecodedTimeQuantity dti = timeQuantity.GetDecodedTimeQuantity();
    hours        =  dti.hours;
    minutes      =  dti.minutes;
    seconds      =  dti.seconds;
    milliseconds =  dti.milliseconds;

    decodedDate = true;
}

dtTimeQuantity    DateTime::EncodeDate (dtYear _year, dtMonth _month, dtDay _day )
{
    double decimals  =   double(timeQuantity.GetQuantitySerialNumber().WarningDontDoThisGetInternal())
                                -
                        int(double(timeQuantity.GetQuantitySerialNumber().WarningDontDoThisGetInternal()));

    int m = (int(_month.WarningDontDoThisGetInternal()) +9) %12;
    int y = _year.WarningDontDoThisGetInternal() - m /10;


    return dtTimeQuantity (
            dtTimeQuantitySerialNumber (
                double(365*y + y/4 - y/100 +y/400 + (m*306 + 5)/10 + _day.WarningDontDoThisGetInternal() - 1)
                    +
                decimals
            )
        );
}





//  Funciones de soporte adicionales __________________________________

#ifndef MTK_PLATFORM
    #error  "mtk::   NO ESTÁ CARGADO EL FICHERO DE CONFIGURACIÓN  soposupport/form.h"
#endif

#if (MTK_PLATFORM == MTK_WIN_PLATFORM)


DateTime    dtNowUTC(void)
{
    SYSTEMTIME systemtime;
    GetSystemTime(&systemtime);

    return DateTime(
            dtYear        (systemtime.wYear        ),
            dtMonth       (systemtime.wMonth       ),
            dtDay         (systemtime.wDay         ),
            dtHours       (systemtime.wHour        ),
            dtMinutes     (systemtime.wMinute      ),
            dtSeconds     (systemtime.wSecond      ),
            dtMilliseconds(systemtime.wMilliseconds)
        );
}


DateTime    dtNowLocal(void)
{
    SYSTEMTIME systemtime;
    GetLocalTime(&systemtime);

    return DateTime (
            dtYear        (systemtime.wYear        ),
            dtMonth       (systemtime.wMonth       ),
            dtDay         (systemtime.wDay         ),
            dtHours       (systemtime.wHour        ),
            dtMinutes     (systemtime.wMinute      ),
            dtSeconds     (systemtime.wSecond      ),
            dtMilliseconds(systemtime.wMilliseconds)
        );
}


dtTimeQuantity  dtMachineGetTotalMillisecs (void)
{
//    return  dtTotalMillisecs(GetTickCount());

    static __int64          vueltas64           = 0;
    static const __int64    _2pow32             = 4294967296LL;	//	en bcb hay que dejar una sola L
    static unsigned         previusTickCount32  = 0;
    unsigned                currentTickCount32  = GetTickCount();

    if (currentTickCount32 < previusTickCount32)    //  casi seguro que hemos dado la vuelta al int32
    {
        vueltas64 += _2pow32;
    }

    previusTickCount32 = currentTickCount32;
    return  dtTotalMillisecs((__int64)(currentTickCount32) + (__int64)(vueltas64));
}


#elif MTK_PLATFORM == MTK_LINUX_PLATFORM

    DateTime    dtNowUTC(void)
    {
        static struct timeb tp;
        ftime(&tp);
        tm* now = gmtime(&tp.time);

        return DateTime(
                dtYear        (now->tm_year+1900        ),
                dtMonth       (now->tm_mon+1            ),
                dtDay         (now->tm_mday             ),
                dtHours       (now->tm_hour             ),
                dtMinutes     (now->tm_min              ),
                dtSeconds     (now->tm_sec              ),
                dtMilliseconds(tp.millitm               )
            );
    }


    DateTime    dtNowLocal(void)
    {
        static struct timeb tp;
        ftime(&tp);
        tm* now = localtime(&tp.time);

        return DateTime(
                dtYear        (now->tm_year+1900        ),
                dtMonth       (now->tm_mon+1            ),
                dtDay         (now->tm_mday             ),
                dtHours       (now->tm_hour             ),
                dtMinutes     (now->tm_min              ),
                dtSeconds     (now->tm_sec              ),
                dtMilliseconds(tp.millitm               )
            );
    }


    dtTimeQuantity  dtMachineGetTotalMillisecs (void)
    {
        //  En linux no hay una forma fácil (razonable)
        //  para obtener esta información
        static DateTime firstCallDateTime = dtNowLocal();

        return dtNowLocal() - firstCallDateTime;
    }

#else

    #error  Unknown platfrom

#endif  //#if (MTK_PLATFORM == MTK_WIN_PLATFORM)



dtTimeQuantity abs(const dtTimeQuantity& ti)
{
    if (ti.IsNegative())
        return -ti;
    else
        return ti;

}






int ARE_YOU_SURE_YOU_WANT_GetMillisecsDay(const dtTimeQuantity& tq)
{
    tq.DecodeTime();
    return tq.millisecsDay.WarningDontDoThisGetInternal();
}


/*
DateTime  dtOnlyDate_0Time (void)
{

}
*/


std::ostream& operator<< (std::ostream& os, const DateTime& dt)
{
    os << dt.GetYear().WarningDontDoThisGetInternal() << "-";
    os.width(2); os.fill('0');
    os << dt.GetMonth().WarningDontDoThisGetInternal() << "-";
    os.width(2); os.fill('0');
    os << dt.GetDay().WarningDontDoThisGetInternal();

    if (dt.GetMillisecsDay().WarningDontDoThisGetInternal() != 0)
    {
        os << " ";
        os << dt.GetHours().WarningDontDoThisGetInternal() << ":";
        os.width(2); os.fill('0');
        os << dt.GetMinutes().WarningDontDoThisGetInternal() << ":";
        os.width(2); os.fill('0');
        os << dt.GetSeconds().WarningDontDoThisGetInternal() << ".";
        os.width(3); os.fill('0');
        os << dt.GetMilliseconds().WarningDontDoThisGetInternal();
    }

    return os;

}



//---------------------------------------------------------------------------
};      //  namespace mtk {
