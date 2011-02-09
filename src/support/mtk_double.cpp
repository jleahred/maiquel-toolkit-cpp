#include <limits>


#include "mtk_double.h"
#include "yaml/yaml.h"



namespace mtk {


const double Double::INVALID_VALUE=1e307;



//  Métodos de acceso




tuple<double, bool>  Double::get(void) const  {
    if (IsValid())
        return make_tuple(value, true);
    else
        return make_tuple(std::numeric_limits<double>::quiet_NaN(), false);
}



double   Double::get2(void) const
{
    if (IsValid())
        return value;
    else
        throw mtk::Alarm(MTK_HERE, "get2", "get2 on invalid double number", mtk::alPriorError, mtk::alTypeNoPermisions);
}







//  Operadores aritméticos sin conversión

Double Double::operator+= (const Double& d) {
    //  esto es poco eficiente pero más seguro y más cómodo
    //*this = *this + sum;
    //return *this;

    if (IsValid()  &&  d.IsValid())
        value += d.value;   //  llamada implicita a Double(...
    else
        value = INVALID_VALUE;
    return *this;
};


Double Double::operator-= (const Double& d) {

    if (IsValid()  &&  d.IsValid())
        value -= d.value;   //  llamada implicita a Double(...
    else
        value = INVALID_VALUE;
    return *this;
};


Double Double::operator*= (const Double& d) {

    if (IsValid()  &&  d.IsValid())
        value *= d.value;   //  llamada implicita a Double(...
    else
        value = INVALID_VALUE;
    return *this;
};


Double Double::operator/= (const Double& d) {

    if (IsValid()  &&  d.IsValid())
        value /= d.value;   //  llamada implicita a Double(...
    else
        value = INVALID_VALUE;
    return *this;
};







// Salida estándar









//  Operadores relacionales conversión todos los parámetros


bool operator==(const Double&  D1, const Double&  D2)
{
    // testing performance with  100_000_000 iterations



    if(D1.IsValid() == false  ||  D2.IsValid() == false)
        return false;       //  criteria
    double d1 = D1.get2();
    double d2 = D2.get2();


    //  best performance  5s 300ms

    //  managing zero in a symetric way
    if(d2<1e-300  &&  d2>-1e-300)        //  it is interpreted as exact zero
    {       //  here we don't consider the exponent
        if( d1 > -1e-12  &&  d1 < 1e-12)
            return true;
        else
            return false;

    }
    if(d1<1e-300  &&  d1>-1e-300)        //  it is interpreted as exact zero
    {       //  here we don't consider the exponent
        if( d2 > -1e-12  &&  d2 < 1e-12)
            return true;
        else
            return false;
    }

    //  checking for not zeros
    double div = d1 / d2;
    if( div > 1-1e-10  &&  div < 1+1e-10)
        return true;
    else
        return false;



    //  very good performance       6s 90ms
    //  correct with all numbers (big, small and medim)
    //  pending exponent normalization
    /*
    int     exponent1 = 0.;
    double  significant1= frexp(d1, &exponent1);

    int     exponent2 = 0.;
    double  significant2= frexp(d2, &exponent2);

    //  normalize exponents
    //  pending
    if(exponent1 != exponent2)
        return false;
    else
    {
        double sig_diff = significant1 - significant2;
        if(sig_diff > 1e-10  ||  sig_diff < -1e-10)
            return false;
    }
    return true;
    */

    //  dynamic epsilon.  this is ok but not good in performance    15s
    /*
    int max = int(d1.get2()>d2.get2() ? d1.get2() : d2.get2());
    int __log10 =  0;
    if(max >= 1)        __log10 = int(::log10(max));
    else if (max<=-1)   __log10 = int(::log10(-1*max));
    else                __log10 = 0;

    if (d1.IsValid()  &&  d2.IsValid()) {
        if (
                d1.value - d2.value <  -1*(::pow(10, -12+__log10))//1e-10
                &&
                d1.value - d2.value >     (::pow(10, -12+__log10))//1e-10
            )
        {
            return true;
        }
    }
    return false;               //  criterio
    */

    //  fixed epsilon.  good performance but  wrong with big numbers
    /*

    if (d1.IsValid()  &&  d2.IsValid()) {
        if (
                d1.value - d2.value <   -1e-10
                &&
                d1.value - d2.value >  1e-10
            )
        {
            return true;
        }
    }
    return false;               //  criterio
     */
};


bool operator!=(const Double&  d1, const Double&  d2) {
    return !operator==(d1, d2);
};




bool operator<(const Double&  d1, const Double&  d2) {
    if (d1 == d2)
        return false;

    if (d1.IsValid()  &&  d2.IsValid())
        return d1.value < d2.value;
    else
        return false;
};


bool operator>(const Double&  d1, const Double&  d2) {
    if (d1 == d2)
        return false;

    if (d1.IsValid()  &&  d2.IsValid())
        return d1.value > d2.value;
    else
        return false;
};


bool operator<=(const Double&  d1, const Double&  d2) {
    if (d1 == d2)
        return true;

    //  es más conciso pero menos claro esto...
    //  return d1 < d2;

    if (d1.IsValid()  &&  d2.IsValid())
        return d1.value < d2.value;
    else
        return false;
};


bool operator>=(const Double&  d1, const Double&  d2) {
    if (d1 == d2)
        return true;

    if (d1.IsValid()  &&  d2.IsValid())
        return d1.value > d2.value;
    else
        return false;
};




//  Operadores aritméticos  conversión en todos los parámetros

Double operator+ (const Double& d1, const Double& d2) {
//    if (d1.IsValid()  &&  d2.IsValid())
//        return d1.get()._0 + d2.get()._0;   //  llamada implicita a Double(...
//    else
//        return Double();


    if (d1.IsValid()  &&  d2.IsValid())
        return d1.value + d2.value;   //  llamada implicita a Double(...
    else
        return Double();
};


Double operator- (const Double& d1, const Double& d2) {

    if (d1.IsValid()  &&  d2.IsValid())
        return d1.value - d2.value;   //  llamada implicita a Double(...
    else
        return Double();
};


Double operator* (const Double& d1, const Double& d2) {
//    if (d1.IsValid()  &&  d2.IsValid())
//        return d1.get()._0 * d2.get()._0;   //  llamada implicita a Double(...
//    else
//        return Double();
    if (d1.IsValid()  &&  d2.IsValid())
        return d1.value * d2.value;   //  llamada implicita a Double(...
    else
        return Double();
};


Double operator/ (const Double& d1, const Double& d2) {
//    if (d1.IsValid()  &&  d2.IsValid())
//        return d1.get()._0 / d2.get()._0;   //  llamada implicita a Double(...
//    else
//        return Double();
    if (d1.IsValid()  &&  d2.IsValid())
        return d1.value / d2.value;   //  llamada implicita a Double(...
    else
        return Double();
};


//  Funciones típicas

Double pow (const Double& base, const Double& exp ) {
    if (base.IsValid()  &&  exp.IsValid())
        return ::pow(base.get()._0,exp.get()._0);
    else
        return Double::InvalidValue();
};


Double log (const Double& d) {
    if (d.IsValid())
        return ::log(d.get()._0);
    else
        return Double::InvalidValue();
};


Double exp (const Double& d) {
    if (d.IsValid())
        return ::exp(d.get()._0);
    else
        return Double::InvalidValue();
};




std::ostream& operator<< (std::ostream& os, const Double& d)
{
    if (d.IsValid() == false)
        os << "#invalid#";
    else
        os << d.value;

    return os;
};

YAML::Emitter& operator<< (YAML::Emitter& os, const Double& d)
{
    if (d.IsValid() == false)
        os << YAML::Null;
    else
        os << d.value;

    return os;

}

void           operator>> (const YAML::Node& n, Double& d)
{
    if(n.size()>0)
    {
        double ld=0;
        n >> ld;
        d = Double(ld);
    }
}




//---------------------------------------------------------------------------
};      //namespace mtk {
