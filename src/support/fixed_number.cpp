#include "fixed_number.h"


#include <math.h>
#include <iomanip>

#include "mtk_string.h"
#include "yaml/yaml.h"




namespace mtk {





//---------------------------------------------------------------------------

//              f n E x t

//---------------------------------------------------------------------------


fnExt::fnExt(   const fnDec&            dec,
                const fnInc&            inc,
                fnEnFormat              formato
            )
    :
        decimals        (dec	),
        increment       (inc	),
        format          (formato)
{
    if (dec<0)
        throw   fnErrorFixedNumber (
                    Alarm (
                        MTK_HERE, "fixednumber",
                        "num decimales no válido (<0)",
                        alPriorError, alTypeNoPermisions
                    )
                );
    else if (inc<=0)
        throw   fnErrorFixedNumber (
                    Alarm (
                        MTK_HERE, "fixednumber",
                        "incremento no válido (<=0)",
                        alPriorError, alTypeNoPermisions
                    )
                );
}



bool    fnExt::operator==(const fnExt& other) const
{
    if (    this->increment == other.increment
            &&
            this->decimals  == other.decimals
        )
        return true;
    else
        return false;
}

bool    fnExt::operator!=(const fnExt& other) const
{
    return ! operator==(other);
}







//---------------------------------------------------------------------------

//              F i x e d N u m b e r

//---------------------------------------------------------------------------



FixedNumber::FixedNumber(
                    fnDouble    _double,
                    fnDec       _dec,
                    fnInc       _inc
        ) :
            intValue    (0),
            ext         (_dec, _inc   ),
            pow10       (::pow(10, _dec))


{
    //MMA: Ya está en contstructor de fnExt. Nunca se cumple
    //if (_inc<=0)
    //    throw   fnErrorFixedNumber (Alarm (
    //                "FixedNumber",
    //                "inc no válido (<=0)",
    //                alPriorError, alTypeNoPermisions));

    SetDouble (_double.Get(), _double.GetRound());
}




FixedNumber::FixedNumber(
                    fnIntCode   _intCode,
                    fnDec       _dec,
                    fnInc       _inc
        ) :
            intValue    (0            ),
            ext         (_dec, _inc   ),
            pow10       (::pow(10, _dec))
{
    //MMA: redundante. Idem
    //if (_inc<=0)
    //    throw   fnErrorFixedNumber (Alarm (
    //                "FixedNumber",
    //                "inc no válido (<=0)",
    //                alPriorError, alTypeNoPermisions));
    SetIntCode(_intCode.Get(), _intCode.GetRound());
}


FixedNumber::FixedNumber(
                    fnDouble    _double,
                    fnExt       _extInfo
        ) :
            intValue    (0                    ),
            ext         (_extInfo             ),
            pow10       (::pow(10, ext.GetDec()))


{
    //MMA: No pue ser
    //if (ext.GetInc()<=0)
    //    throw   fnErrorFixedNumber (Alarm (
    //                "FixedNumber",
    //                "inc no válido (<=0)",
    //                alPriorError, alTypeNoPermisions));

    SetDouble (_double.Get(), _double.GetRound());
}




FixedNumber::FixedNumber(
                    fnIntCode   _intCode,
                    fnExt       _extInfo
        ) :
            intValue    (0                    ),
            ext         (_extInfo             ),
            pow10       (::pow(10, ext.GetDec()))


{
    //if (ext.GetInc()<=0)
    //    throw   fnErrorFixedNumber (Alarm (
    //                "FixedNumber",
    //                "inc no válido (<=0)",
    //                alPriorError, alTypeNoPermisions));
    SetIntCode(_intCode.Get(), _intCode.GetRound());
}


mtk::Double FixedNumber::GetDouble (void) const
{
    return   mtk::Double(double(int(intValue)) / pow10);
}

FixedNumber& FixedNumber::SetIntCode(int value, const fnEnRound round)
{


    int inc = ext.GetInc();
    int signo = value >= 0  ?  1  :  -1;
    switch (round) {
        case fnRoundArithmetic:
//                intValue = (value*2+  inc)/(2*inc) * inc;
//                break;

//  TODO:   No tengo claro que sea la mejor opción
//          es cierto que es más justa que la aritmética, pero es menos
//          sencillo saber la dirección de redondeo y puede ser un jaleo
//          para los usuarios

                //  si está en medio (es equidistante)
                //  ajustar de forma equitativa, 50% alza y 50% baja
                //  de forma determinista
        {
                int positivValue = value * signo;
                int ajusteEquidistante = 0;
                if((positivValue%inc)*2 == inc) {	//	es equidistante
                    if (positivValue%(2*inc) < inc)
                        ajusteEquidistante = -1 * signo;
                }
                intValue = (value*2 +ajusteEquidistante +  inc*signo)/(2*inc) * inc;            //  FIX IT
                break;
        }



        case fnRoundCeil:
                if (signo==1)
                    intValue = (value+  (inc-1)  )/(inc) * inc;
                else
                    intValue = (value+0)/(inc) * inc;
                break;


        case fnRoundFloor:
                if (signo==1)
                    intValue = (value+0)/(inc) * inc;
                else
                    intValue = (value-  (inc-1)  )/(inc) * inc;
                break;


        case fnRoundNotAllowed:
                intValue = value/inc*inc;
                if (intValue!=value)
                    throw   fnErrorFixedNumber (Alarm (
                                MTK_HERE, "fixednumber",
                                "round not allowed",
                                alPriorError, alTypeNoPermisions));
                break;
        default:
	        throw   fnErrorFixedNumber (Alarm (
						    MTK_HERE, "fixednumber",
						    "round not allowed. default??",
						    alPriorError, alTypeNoPermisions));
    };


    return *this;
}

FixedNumber& FixedNumber::SetDouble (mtk::Double value, const fnEnRound round  )
{
    if (value.IsValid()==false)
	        throw   fnErrorFixedNumber (Alarm (
						    MTK_HERE, "fixednumber",
						    "Invalid value to set",
						    alPriorError, alTypeNoPermisions));
    SetDouble(value.get()._0, round);
    return *this;
}

FixedNumber& FixedNumber::SetDouble (double value, const fnEnRound round  )
{

    //  verificación desbordamiento de dígitos significativos
    //if (value!=0.) {         //  esta optimización parece que no aporta mucho
        double positivValue = value;
        int sign = 1;
        if (positivValue<0.)
        {
            positivValue *= -1;
            sign = -1;
        }

        if (log10(positivValue) >=0   &&  int(log10(positivValue) +0.5) + ext.GetDec() >=9)
                throw fnErrorFixedNumber (Alarm (
                        MTK_HERE, "fixednumber",
                        MTK_SS("desbordamiento" << value << " d" << ext.GetDec()),
                        alPriorError, alTypeNoPermisions
                    ));
    //}
    //  no hay desbordamiento...

    double valuePow10 = value * pow10;


    //  valorar si pueden intentar pasarnos un número exacto (en un número inexacto el double)
    {
        int redondeado = int((valuePow10*10+ (4.999999999999)*sign )/10.);
        if(mtk::Double(double(redondeado)/pow10)  ==  mtk::Double(valuePow10/pow10))
        {
            SetIntCode(redondeado, round);      //  FIX IT
            return *this;
        }
    }

    //  NO parece un número exacto...
    int inc = ext.GetInc();
    int signo = value >= 0  ?  1  :  -1;
    switch (round) {
        case fnRoundArithmetic:
                intValue =  int(
                                  (
                                    (valuePow10+signo*1/1000.)*2.0
                                    +  (inc*signo)
                                  )
                                  /(2.0*inc)
                             )
                             * inc;
                break;


        case fnRoundCeil:
                if (signo==1)
                    intValue = int(
                                    (valuePow10+  (inc-1)  )/(inc)
                                )
                                * inc;
                else
                    intValue = int(
                                    (valuePow10+  0  )/(inc)
                                )
                                * inc;
                break;


        case fnRoundFloor:
                if (signo==1)
                    intValue = int(
                                    (valuePow10+  0  )/(inc)
                                )
                                * inc;
                else
                    intValue = int(
                                    (valuePow10+  (inc-1)  )/(inc)
                                )
                                * inc;
                break;


        case fnRoundNotAllowed:
                throw   fnErrorFixedNumber (Alarm (
                            MTK_HERE, "fixednumber",
                            "round not allowed",
                            alPriorError, alTypeNoPermisions));
                break;
        default:
	        throw   fnErrorFixedNumber (Alarm (
						    MTK_HERE, "fixednumber",
						    "round not allowed. default??",
						    alPriorError, alTypeNoPermisions));
    };

    return *this;
}



    //  OPERADORES      ____________________________________________________

    //  relacionales
bool    FixedNumber::operator ==  (const FixedNumber&  other)  const
{
    if (ext == other.ext   &&   intValue == other.intValue)
        return true;
    else
        return false;
}

bool    FixedNumber::operator !=  (const FixedNumber&  other)  const
{
    return ! operator==(other);
}

bool    FixedNumber::operator <   (const FixedNumber&  other)  const
{
    if (ext == other.ext) {
        return  intValue < other.intValue;
    } else {
        throw   fnErrorFixedNumber (Alarm (
                    MTK_HERE, "fixednumber",
                    "non comparable types",
                    alPriorError, alTypeNoPermisions));

    }
}

bool    FixedNumber::operator <=  (const FixedNumber&  other)  const
{
//    return operator<(other)  ||   operator==(other);
    if (ext == other.ext) {
        return  intValue <= other.intValue;
    } else {
        throw   fnErrorFixedNumber (Alarm (
                    MTK_HERE, "fixednumber",
                    "non comparable types",
                    alPriorError, alTypeNoPermisions));

    }
}


bool    FixedNumber::operator >   (const FixedNumber&  other)  const
{
//    return !operator<=(other);
    if (ext == other.ext) {
        return  intValue > other.intValue;
    } else {
        throw   fnErrorFixedNumber (Alarm (
                    MTK_HERE, "fixednumber",
                    "non comparable types",
                    alPriorError, alTypeNoPermisions));

    }
}

bool    FixedNumber::operator >=  (const FixedNumber&  other)  const
{
//    return !operator<(other);
    if (ext == other.ext) {
        return  intValue >= other.intValue;
    } else {
        throw   fnErrorFixedNumber (Alarm (
                    MTK_HERE, "fixednumber",
                    "non comparable types",
                    alPriorError, alTypeNoPermisions));

    }
}



    //  aritméticos
FixedNumber&    FixedNumber::operator++ (void)
{
    return operator+=(fnTicks(1));
}

const FixedNumber    FixedNumber::operator++ (int )
{
    FixedNumber temp (*this);
    operator++();
    return temp;
}

FixedNumber&    FixedNumber::operator-- (void)
{
    return operator-=(fnTicks(1));
}

const FixedNumber    FixedNumber::operator-- (int )
{
    FixedNumber temp (*this);
    operator--();
    return temp;
}


FixedNumber     FixedNumber::operator+  (const fnTicks&  ticks) const
{
    FixedNumber result(*this);
    return result += ticks;
}

FixedNumber     FixedNumber::operator-  (const fnTicks&  ticks) const
{
    FixedNumber result(*this);
    return result -= ticks;
}

FixedNumber&    FixedNumber::operator+= (const fnTicks&  ticks)
{
    intValue += ticks*ext.GetInc();
    return *this;
}

FixedNumber&    FixedNumber::operator-= (const fnTicks&  ticks)
{
    intValue -= ticks*ext.GetInc();
    return *this;
}




std::ostream& operator<< (std::ostream& o, const FixedNumber& fn)
{
    int intCode = fn.GetIntCode();
    int absIntCode;

    if (intCode < 0) {
        o << "-";
        absIntCode = -intCode;
    }
    else
        absIntCode =  intCode;


    int pow10 = int(::pow(10, fn.GetExt().GetDec())+0.00001);
    int entera  = int(absIntCode / pow10);
    int decimal = absIntCode - entera*pow10;

    o << entera;
    o << ".";
    o.width(fn.GetExt().GetDec());
    o.fill('0');
    if (fn.GetExt().GetDec() > 0)
        o << decimal;
     o << "#" << fn.GetExt().GetInc();

    return o;
};


std::ostream& operator<< (std::ostream& os, const fnExt& fnExt)
{
    std::streamsize old_precision = os.precision();
    os.precision(fnExt.GetDec());
    os << "#" << std::setiosflags(std::ios::fixed) << 1. /::pow(10, fnExt.GetDec())  * fnExt.GetInc();
    os.precision(old_precision);
    return os;
}



YAML::Emitter& operator<< (YAML::Emitter& os, const FixedNumber& fn)
{
    return os << YAML::Flow << YAML::BeginSeq
        << fn.GetDouble() << fn.GetExt()
        << YAML::EndSeq;
}

YAML::Emitter& operator<< (YAML::Emitter& os, const fnExt& fnExt)
{
    return os << YAML::Flow << YAML::BeginSeq
        << fnExt.GetDec() << fnExt.GetInc()
        << YAML::EndSeq;
}



void           operator>> (const YAML::Node   & i ,       FixedNumber& fn)
{
    int int_code=0;

    i[0] >> int_code;

    fnExt ext(fnDec(0), fnInc(1));     //  temporary value
    i[1] >> ext;
    fn = FixedNumber(fnIntCode(int_code), ext);
}
void           operator>> (const YAML::Node   & i ,       fnExt& d)
{
    int decimals=0;
    int increment=0;

    i[0] >> decimals;
    i[1] >> increment;

    d = fnExt(fnDec(decimals), fnInc(increment));
}




};      //  namespace mtk {
