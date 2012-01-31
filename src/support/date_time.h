//---------------------------------------------------------------------------
//  Creado: 3/4/2008        JLE
#ifndef mtkDateTimeH
#define mtkDateTimeH


#include "platform.hpp"
#include "basic_types.hpp"



#if (MTK_PLATFORM == MTK_WIN_PLATFORM)
    #include <basetyps.h>       //  __int64		//	quitar en bcb
#endif

//#if (MTK_PLATFORM == MTK_LINUX_PLATFORM)
//    typedef __int64_t   __int64;
//#endif



#include <iostream>     //  no es debug


namespace YAML  {  class Emitter;  class Node;   };

/*******************************************************************************

            I D E A     B A S E



    Intervalo de tiempo     (TimeQuantity)
    ==========================================

        * Se pueden sumar y restar intervalos.
          El resultado es otro intervalo de tiempo
        * Se puede representar como días y milisegundos en el día
        * Se puede representar también como días y fraciones de días
          en un double
        * Mig: ¿Intervalo de tiempo? ¿Cuando empiezan y terminan los intervalos?
        * Mig: TimeQuantity -> buen nombre (Cantidad de tiempo, duración)



    Momento concreto        (DateTime)
    ==========================================

        * Se descompone en año, mes, día, hora, minuto, segundo, milisegundos
        * No es una cantidad de tiempo, es un momento específico
        * No se pueden sumar momentos de tiempo
        * Sí se pueden restar momentos de tiempo y el resultado es un intervalo
          de tiempo
          Mig: dos momentos de tiempo forman un intervalo y su tamaño es una cantidad de tiempo
        * La suma de Momento concreto  e  intervalo de tiempo no es conmutativa
            * Se puede sumar a un momento concreto un intervalo de tiempo
            * No se puede sumar a un intervalo un momento concreto
            * Mig: DateTime + TimeQuantity = DateTime
            * Mig: TimeQuantity + DateTime : no permitido por decreto

        Ver ejemplos de uso al final del fichero



*******************************************************************************/






namespace mtk {
//---------------------------------------------------------------------------

#define MTK_DATETIME_WARP(class_name, class_type)                       \
    class class_name {                                                  \
        class_type  internal;                                           \
    public:                                                             \
        explicit class_name (class_type value) : internal(value) {};    \
        class_type  WarningDontDoThisGetInternal(void) const  {  return internal;  };    \
        bool operator==(const class_name& c) const                      \
        {       return internal == c.internal;    }                     \
        bool operator!=(const class_name& c) const                      \
        {       return internal != c.internal;    }                     \
        bool operator< (const class_name& c) const                      \
        {       return internal < c.internal;    }                      \
        bool operator> (const class_name& c) const                      \
        {       return internal > c.internal;    }                      \
        bool operator<=(const class_name& c) const                      \
        {       return internal <= c.internal;    }                     \
        bool operator>=(const class_name& c) const                      \
        {       return internal >= c.internal;    }                     \
    };


#define MTK_DATETIME_WARP_NOEQ(class_name, class_type)                       \
    class class_name {                                                  \
        class_type  internal;                                           \
    public:                                                             \
        explicit class_name (class_type value) : internal(value) {};    \
        class_type  WarningDontDoThisGetInternal(void) const  {  return internal;  };    \
        class_type  i(void) const            {  return internal;  };    \
        bool operator< (const class_name& c) const                      \
        {       return internal < c.internal;    }                      \
        bool operator> (const class_name& c) const                      \
        {       return internal > c.internal;    }                      \
        bool operator<=(const class_name& c) const                      \
        {       return internal <= c.internal;    }                     \
        bool operator>=(const class_name& c) const                      \
        {       return internal >= c.internal;    }                     \
    };
//        operator class_type (void) const   {  return internal; };

//	typedef long long  __int64;		poner esta línea en gcc para linux

MTK_DATETIME_WARP       (_Days                         ,     int      );

MTK_DATETIME_WARP       (_Hours                        ,     int      );
MTK_DATETIME_WARP       (_Minutes                      ,     int      );
MTK_DATETIME_WARP       (_Seconds                      ,     int      );
MTK_DATETIME_WARP       (_Milliseconds                 ,     int      );

MTK_DATETIME_WARP       (_MillisecsDay                 ,     int      );
MTK_DATETIME_WARP       (_TotalMillisecs               ,     __int64  );
MTK_DATETIME_WARP_NOEQ  (_TimeQuantitySerialNumber     ,     double   );      //  days.portionDay
MTK_DATETIME_WARP_NOEQ  (_VCLDateTimeSerialNumber      ,     double   );

MTK_DATETIME_WARP       (_Year                         ,     int      );
MTK_DATETIME_WARP       (_Month                        ,     int      );
MTK_DATETIME_WARP       (_Day                          ,     int      );

MTK_DATETIME_WARP_NOEQ  (_QMinutes                     ,     double   );
MTK_DATETIME_WARP_NOEQ  (_QSeconds                     ,     double   );




//  ayuda al IDE...
typedef _Days                       dtDays                    ;
typedef _Hours                      dtHours                   ;
typedef _Minutes                    dtMinutes                 ;

typedef _Seconds                    dtSeconds                 ;
typedef _Milliseconds               dtMilliseconds            ;
typedef _MillisecsDay               dtMillisecsDay            ;
typedef _TotalMillisecs             dtTotalMillisecs          ;


typedef _TimeQuantitySerialNumber   dtTimeQuantitySerialNumber;
//typedef _VCLDateTimeSerialNumber    dtVCLDateTimeSerialNumber ;

typedef _Year                       dtYear                    ;
typedef _Month                      dtMonth                   ;
typedef _Day                        dtDay                     ;



typedef _QMinutes                   dtQMinutes                ;
typedef _QSeconds                   dtQSeconds                ;





//--------------------------------------------------------------------------

//              T i m e Q u a n t i t y

//--------------------------------------------------------------------------

        //  esta estructura debería utilizarse muy excepcionalmente
struct dtDecodedTimeQuantity {
    const int             sign;       //  -1   or  1
    const dtDays          days;
    const dtHours         hours;
    const dtMinutes       minutes;
    const dtSeconds       seconds;
    const dtMilliseconds  milliseconds;

private:
    friend class dtTimeQuantity;
    dtDecodedTimeQuantity(  int             _sign,
                            dtDays          _days,
                            dtHours         _hours,
                            dtMinutes       _minutes,
                            dtSeconds       _seconds,
                            dtMilliseconds  _milliseconds)
        :   sign        (_sign),
            days        (_days),
            hours       (_hours),
            minutes     (_minutes),
            seconds     (_seconds),
            milliseconds(_milliseconds) {}
};






class dtTimeQuantity
{
public:

    //  CONSTRUCTORES   ____________________________________________________

    explicit dtTimeQuantity (dtTimeQuantitySerialNumber _timeQuantitySerNumber);
    explicit dtTimeQuantity (dtMillisecsDay             _millisecsDay         );

    dtTimeQuantity (         dtDays                     _days                 ,
                             dtMillisecsDay             _millisecsDay         );

    dtTimeQuantity (         dtDays                     _days                 ,
                             dtHours                    _hours                ,
                             dtMinutes                  _minutes              ,
                             dtSeconds                  _secs                 ,
                             dtMilliseconds             _millisecs            );

    dtTimeQuantity (         dtHours                    _hours                ,
                             dtMinutes                  _minutes              ,
                             dtSeconds                  _secs                 ,
                             dtMilliseconds             _millisecs            );

    //  Sirven constructor de copia y operador asignación



    //  Conversiones implícitas ___________________________________________

    dtTimeQuantity    (dtDays           );
    dtTimeQuantity    (dtHours          );
    dtTimeQuantity    (dtMinutes        );
    dtTimeQuantity    (dtSeconds        );
    dtTimeQuantity    (dtMilliseconds   );
    dtTimeQuantity    (dtTotalMillisecs );

    //dtTimeQuantity    (dtTotalDays           );
    //dtTimeQuantity    (dtTotalHours          );
    dtTimeQuantity    (dtQMinutes       );
    dtTimeQuantity    (dtQSeconds       );



    //  OPERADORES      ____________________________________________________

        //  relacionales
    bool                operator  ==  (const dtTimeQuantity& ti) const;
    bool                operator  !=  (const dtTimeQuantity& ti) const;
    bool                operator  <   (const dtTimeQuantity& ti) const;
    bool                operator  <=  (const dtTimeQuantity& ti) const;
    bool                operator  >   (const dtTimeQuantity& ti) const;
    bool                operator  >=  (const dtTimeQuantity& ti) const;

        //  aritméticos
    dtTimeQuantity        operator-     (void) const;

    dtTimeQuantity        operator  +   (const dtTimeQuantity& ti) const;
    dtTimeQuantity&       operator  +=  (const dtTimeQuantity& ti);
    dtTimeQuantity        operator  -   (const dtTimeQuantity& ti) const;
    dtTimeQuantity&       operator  -=  (const dtTimeQuantity& ti);

//    dtTimeQuantity&       operator  ++  (void);
//    const dtTimeQuantity  operator  ++  (int );
//    dtTimeQuantity&       operator  --  (void);
//    const dtTimeQuantity  operator  --  (int );




    //  ACCESO  (en ocasiones perezoso)  __________________________________

    dtDecodedTimeQuantity         GetDecodedTimeQuantity    (void) const;
    dtTimeQuantitySerialNumber    GetQuantitySerialNumber   (void) const;


    bool                          IsNegative                (void) const;
    bool                          IsPositive                (void) const;



    friend std::ostream&  operator<< (std::ostream     & os, const dtTimeQuantity& d);
    friend YAML::Emitter& operator<< (YAML::Emitter    & os, const dtTimeQuantity& d);
    friend void           operator>> (const YAML::Node & i ,       dtTimeQuantity& d);





private:

    //  no perezosos
    dtTimeQuantitySerialNumber    timeQuantitySerialNumber;


    mutable bool                  decodedTime;
    //  perezosos
    mutable int                   sign;
    mutable dtDays                days;
    mutable dtMillisecsDay        millisecsDay;

    mutable dtHours               hours;
    mutable dtMinutes             mins;
    mutable dtSeconds             secs;
    mutable dtMilliseconds        millisecs;

    void DecodeTime (void)  const;


friend int ARE_YOU_SURE_YOU_WANT_GetMillisecsDay(const mtk::dtTimeQuantity& tq);

};











//--------------------------------------------------------------------------

//              D a t e T i m e

//--------------------------------------------------------------------------



class DateTime {
public:

    //  CONSTRUCTORES   ____________________________________________________

    DateTime           (dtYear                        _year                 ,
                        dtMonth                       _month                ,
                        dtDay                         _day                  );

    DateTime           (dtYear                        _year                 ,
                        dtMonth                       _month                ,
                        dtDay                         _day                  ,
                        dtTimeQuantity                _timeQuantity         );

    DateTime           (dtYear                        _year                 ,
                        dtMonth                       _month                ,
                        dtDay                         _day                  ,
                        dtHours                       _hour                 ,
                        dtMinutes                     _minutes              ,
                        dtSeconds                     _seconds              ,
                        dtMilliseconds                _milliseconds         );

    //  Sirven constructor de copia y operador asignación



    //  Conversiones implícitas ___________________________________________




    //  OPERADORES      ____________________________________________________

        //  relacionales
    bool                operator  ==  (const DateTime&       dt) const;
    bool                operator  !=  (const DateTime&       dt) const;
    bool                operator  <   (const DateTime&       dt) const;
    bool                operator  <=  (const DateTime&       dt) const;
    bool                operator  >   (const DateTime&       dt) const;
    bool                operator  >=  (const DateTime&       dt) const;

        //  aritméticos
    DateTime&           operator  ++  (void);
    const DateTime      operator  ++  (int );
    DateTime&           operator  --  (void);
    const DateTime      operator  --  (int );

    dtTimeQuantity      operator  -   (const DateTime&       dt) const;

    DateTime            operator  +   (const dtTimeQuantity& ti) const;
    DateTime            operator  -   (const dtTimeQuantity& ti) const;
    DateTime&           operator  +=  (const dtTimeQuantity& ti);
    DateTime&           operator  -=  (const dtTimeQuantity& ti);



    //  ACCESO  (en ocasiones perezoso)  __________________________________

    dtYear                        GetYear                    (void) const;
    dtMonth                       GetMonth                   (void) const;
    dtDay                         GetDay                     (void) const;

    dtHours                       GetHours                   (void) const;
    dtMinutes                     GetMinutes                 (void) const;
    dtSeconds                     GetSeconds                 (void) const;
    dtMilliseconds                GetMilliseconds            (void) const;

    dtMillisecsDay                GetMillisecsDay            (void) const;


    dtTimeQuantitySerialNumber    __WARNING_NOT_CALL_IT_internal_use_GetTimeQuantitySerialNumber(void) const;
//    dtVCLDateTimeSerialNumber     GetVCLDateTimeSerialNumber (void) const;



    friend std::ostream&  operator<< (std::ostream      & os, const DateTime& d);
    friend YAML::Emitter& operator<< (YAML::Emitter     & os, const DateTime& d);
    friend void           operator>> (const YAML::Node  & i ,       DateTime& d);





private:

    //  no perezosos
    dtTimeQuantity              timeQuantity;


    mutable bool                decodedDate;
    //  perezosos
    mutable dtYear              year;
    mutable dtMonth             month;
    mutable dtDay               day;
    mutable dtHours             hours;
    mutable dtMinutes           minutes;
    mutable dtSeconds           seconds;
    mutable dtMilliseconds      milliseconds;


    void              DecodeDate (void)  const;
    dtTimeQuantity    EncodeDate (dtYear _year, dtMonth _month, dtDay _day );


    DateTime   (dtTimeQuantity          _timeQuantity);
    DateTime friend WARNING_do_not_use_it__I_coul_kill_you_for_it__get_DateTime_from_time_quantity(dtTimeQuantity          _timeQuantity);


//public:
    //  esto es sólo para probar con la VCL   TDateTime   --  NO UTILIZAR  --
    //explicit DateTime (dtVCLDateTimeSerialNumber _vclDateTimeSerialNumber);


};







//  Funciones de soporte adicionales __________________________________

DateTime        dtNowUTC                    (void);
DateTime        dtNowLocal                  (void);
dtTimeQuantity  dtMachineGetTotalMillisecs  (void);
DateTime        dtToday_0Time               (void);


DateTime    dtNowLocal__non_monotonic(void);
DateTime    dtNowUTC__non_monotonic  (void);
void        dtResynchr_monotonic       (void);


dtTimeQuantity  abs(const dtTimeQuantity& ti);


int ARE_YOU_SURE_YOU_WANT_GetMillisecsDay(const mtk::dtTimeQuantity& tq);

//??DateTime        dtOnlyDate_0Time            (void);




DateTime WARNING_do_not_use_it__I_coul_kill_you_for_it__get_DateTime_from_time_quantity(dtTimeQuantity          _timeQuantity);




typedef DateTime dtDateTime;
//typedef DateTime dt;





//---------------------------------------------------------------------------
};      //namespace mtk {
#endif



