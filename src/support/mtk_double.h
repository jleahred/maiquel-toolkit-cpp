#ifndef DOUBLE_HPP_INCLUDED
#define DOUBLE_HPP_INCLUDED

#include <iostream>     //  no es debug
#include <math.h>
#include "tuples.hpp"



namespace YAML  {  class Emitter;   class Node;  };




namespace mtk {
//---------------------------------------------------------------------------


class Double {
    //  esto es por rendimiento
    friend Double operator+ (const Double& d1, const Double& d2);
    friend Double operator- (const Double& d1, const Double& d2);
    friend Double operator* (const Double& d1, const Double& d2);
    friend Double operator/ (const Double& d1, const Double& d2);
    friend bool   operator==(const Double& d1, const Double& d2);
    //friend Double operator!=(const Double& d1, const Double& d2);
    friend bool   operator< (const Double& d1, const Double& d2);
    friend bool   operator<=(const Double& d1, const Double& d2);
    friend bool   operator> (const Double& d1, const Double& d2);
    friend bool   operator>=(const Double& d1, const Double& d2);

    friend std::ostream & operator<< (std::ostream & os, const Double& d);
    friend YAML::Emitter& operator<< (YAML::Emitter& os, const Double& d);
    friend void           operator>> (const YAML::Node& n, Double& d);






private:
    static const double     INVALID_VALUE;
    double                  value;

    Double() : value(INVALID_VALUE) {};

public:

    static Double InvalidValue(void)  {  return Double();  };

    //  sirven constructor de copia y operador de asignación por defecto




    //  conversión implícita
    Double(double _value) : value (_value) {};




    //  Métodos de acceso

    bool IsValid(void) const
    {
        return value < INVALID_VALUE/10.;
    };


    tuple<double, bool>     get (void) const;
    double                  get2(void) const;



    //  Operadores aritméticos sin conversión

    Double operator+= (const Double& d);
    Double operator-= (const Double& d);
    Double operator*= (const Double& d);
    Double operator/= (const Double& d);

};


//  Operadores relacionales conversión todos los parámetros

bool     operator    ==  (const Double&  d1, const Double&  d2);

bool     operator    !=  (const Double&  d1, const Double&  d2);

bool     operator    <   (const Double&  d1, const Double&  d2);

bool     operator    <=  (const Double&  d1, const Double&  d2);

bool     operator    >   (const Double&  d1, const Double&  d2);

bool     operator    >=  (const Double&  d1, const Double&  d2);







//  Operadores aritméticos  conversión en todos los parámetros

Double operator+ (const Double& d1, const Double& d2);
Double operator- (const Double& d1, const Double& d2);
Double operator* (const Double& d1, const Double& d2);
Double operator/ (const Double& d1, const Double& d2);


//	salida
std::ostream& operator<< (std::ostream& os, const Double& d);

//  Funciones típicas

Double pow (const Double& base,    const Double& exp );

Double log (const Double& d                         );

Double exp (const Double& d                         );




//---------------------------------------------------------------------------
};      //namespace mtk {








#endif // DOUBLE_HPP_INCLUDED
