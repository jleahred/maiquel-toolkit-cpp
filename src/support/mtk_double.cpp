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


bool operator==(const Double&  d1, const Double&  d2) {
    if (d1.IsValid()  &&  d2.IsValid()) {
        if (
                d1.value - d2.value <  1e-10
                &&
                d1.value - d2.value > -1e-10
            )
        {
            return true;
        }
    }
    return false;               //  criterio
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
