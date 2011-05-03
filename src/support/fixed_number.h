/*


            C O N C E P T O      G E N E R A L




    Clase de soporte para números de precisión fija

    El objetivo no es realizar operaciones aritméticas con ellos

    fnExt es una clase soporte para gestionar el número de decimales,
    tipo del número e incremento

    fnExt puede trabajar con cada parámetro por separado o con un
    entero donde está encapsulada la información

    A un FixedNumber se le puede sumar y restar fnTicks



        Ver ejemplos de uso al final del fichero.



*/

//---------------------------------------------------------------------------

#ifndef mtk_fixedNumberH
#define mtk_fixedNumberH

#include "alarm.h"
#include "support/mtk_double.h"



namespace YAML  {  class Emitter;  class Node;   };





#define MTK_FIXEDNUMBER_WARP(class_name, class_type)                    \
    class class_name {                                                  \
        class_type  internal;                                           \
    public:                                                             \
        explicit class_name (class_type value) : internal(value) {};    \
        operator class_type (void) const   {  return internal; };       \
    };








namespace mtk {
//---------------------------------------------------------------------------



            //--------------------------------------------------------
//            template<typename T, int Key>
//            class fnWarperSupport {
//                T  internal;
//            public:
//                explicit fnWarperSupport (T value) : internal(value) {};
//                operator T (void) const   {  return internal; };
//            };
            //--------------------------------------------------------







//const char decimalSeparator32s = '~';
const char fnSeparator32s = '*';


enum fnEnRound              {
                                    fnRoundArithmetic   ,   // close to roundHalfEven
                                    fnRoundFloor        ,
                                    fnRoundCeil         ,
                                    fnRoundNotAllowed
                            };


enum fnEnFormat    			{       fnFNormal           ,
                           			fnF32ths
                   			};





//---------------------------------------------------------------------------

//              E R R O R

//---------------------------------------------------------------------------

class fnErrorFixedNumber : public Alarm {
public:
    fnErrorFixedNumber (const Alarm& alerta) : Alarm(alerta) {
    };
};





//---------------------------------------------------------------------------

//              f n E x t

//---------------------------------------------------------------------------

MTK_FIXEDNUMBER_WARP (_fnInc                    ,     int   );
MTK_FIXEDNUMBER_WARP (_fnDec                    ,     int   );
//  ayuda al IDE
typedef _fnInc fnInc;
typedef _fnDec fnDec;


//typedef fnWarperSupport<int, __LINE__>        fnInc;
//typedef fnWarperSupport<int, __LINE__>        fnDec;




class fnExt {
public:
    fnExt   (       const fnDec&            dec,
                    const fnInc&            inc,
                    fnEnFormat              format=fnFNormal
            );


    //  no hay contructor vacío
    //  sirven constructor de copia y operador de asignación



    //  métodos de acceso  -----------------------------
    fnDec           GetDec              (void) const  { return decimals;      };
    fnInc           GetInc              (void) const  { return increment;     };
    fnEnFormat      GetFormat  			(void) const  { return format;     	  };
        //  no se permite modificar  (set)



    //  operadores relacionales  -----------------------
    bool    operator==(const fnExt& other) const;
    bool    operator!=(const fnExt& other) const;
        //  mayor y menor no tienen sentido


private:
    fnDec          decimals;
    fnInc          increment;
    fnEnFormat     format;

};






//---------------------------------------------------------------------------

//              F i x e d N u m b e r

//---------------------------------------------------------------------------

MTK_FIXEDNUMBER_WARP (_fnTicks                  ,     int   );
//  ayuda al IDE
typedef _fnTicks       fnTicks;



template<typename T, int roundType>
class fnWarperRound {
public:
    explicit fnWarperRound(  T           _value,
                             fnEnRound   _round= fnEnRound(roundType))
        :   value(_value),
            round(_round) {}

    T           Get     (void) const { return value;  };
    fnEnRound   GetRound(void) const { return round;  };

private:
    T           value;
    fnEnRound   round;
};

typedef fnWarperRound< mtk::Double  , fnRoundArithmetic	>    fnDouble;
typedef fnWarperRound< int          , fnRoundNotAllowed	>    fnIntCode;

typedef fnWarperRound< mtk::Double  , fnRoundCeil	   	    >    fnDoubleCeil;
typedef fnWarperRound< mtk::Double  , fnRoundFloor		    >    fnDoubleFloor;




class FixedNumber {
public:


    //  CONSTRUCTORES   ____________________________________________________

    FixedNumber(        fnDouble    _double,
                        fnDec       _dec,
                        fnInc       _inc
                );

    FixedNumber(        fnIntCode   _integer,
                        fnDec       _dec,
                        fnInc       _inc
                );

    FixedNumber(        fnDouble    _double,
                        fnExt       _ext
                );

    FixedNumber(        fnIntCode   _integer,
                        fnExt       _ext
                );

    //  sirve constructor de copia y operador de asignación




    //  Conversiones implícitas ___________________________________________






    //  Métodos de acceso  ________________________________________________

    int             GetIntCode(void) const       { return intValue;                 };
    fnExt           GetExt    (void) const       { return ext;                      };
    mtk::Double     GetDouble (void) const;
    mtk::Double     d         (void) const       { return GetDouble();              };

    FixedNumber&    SetIntCode(int         value, const fnEnRound round=fnRoundArithmetic);
    FixedNumber&    SetDouble (double      value, const fnEnRound round=fnRoundArithmetic);
    FixedNumber&    SetDouble (mtk::Double value, const fnEnRound round=fnRoundArithmetic);




    //  OPERADORES      ____________________________________________________

        //  relacionales
    bool    operator ==  (const FixedNumber&  other)  const;
    bool    operator !=  (const FixedNumber&  other)  const;
    bool    operator <   (const FixedNumber&  other)  const;
    bool    operator <=  (const FixedNumber&  other)  const;
    bool    operator >   (const FixedNumber&  other)  const;
    bool    operator >=  (const FixedNumber&  other)  const;





        //  aritméticos
    FixedNumber&        operator++ (void);
    const FixedNumber   operator++ (int );
    FixedNumber&        operator-- (void);
    const FixedNumber   operator-- (int );

    FixedNumber     operator+  (const fnTicks&  ticks) const;
    FixedNumber     operator-  (const fnTicks&  ticks) const;
    FixedNumber&    operator+= (const fnTicks&  ticks);
    FixedNumber&    operator-= (const fnTicks&  ticks);





private:
    int                 intValue;
    fnExt               ext;

    double              pow10;


};



typedef FixedNumber   fn;






std::ostream&  operator<< (std::ostream&  os, const FixedNumber& fn);
std::ostream&  operator<< (std::ostream&  os, const fnExt& fnExt);

YAML::Emitter& operator<< (YAML::Emitter   & os, const FixedNumber& fn);
YAML::Emitter& operator<< (YAML::Emitter   & os, const fnExt& fnExt);
void           operator>> (const YAML::Node& i ,       FixedNumber& fn);
void           operator>> (const YAML::Node& i ,       fnExt& d);






};  //  end namespace mtk
//---------------------------------------------------------------------------
#endif


