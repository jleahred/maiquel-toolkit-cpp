//============================================================================
// Name        : prNullable.cpp
// Author      : jle
// Version     :
// Copyleft    : mtk
// Description :
//============================================================================


//---------------------------------------------------------------------------

#ifndef mtkNullableH
#define mtkNullableH



#include "alarm.h"
#include "yaml/emitter.h"




namespace mtk {
//---------------------------------------------------------------------------





//---------------------------------------------------------------------------

//      n u l l a b l e

//---------------------------------------------------------------------------


template<typename T>
class nullable
{
private:
    T* ptrValue;  // T necesita contructor de copia
                  // T necesita operador de asignación de copia (Podría no necesitarlo)

public:
    explicit nullable(const T& _value)
            :  ptrValue(new T(_value))
    {}
    nullable(void)
            :  ptrValue(0)
    {}

    nullable(const nullable& n)
            :  ptrValue( n.HasValue() ?  new T(*(n.ptrValue)) : 0 )
    {
    }

    ~nullable()
    {
        //if(ptrValue)  {    valeeee... esto no es necesario
            delete ptrValue;
            ptrValue = 0;
	//}
    }

    bool HasValue(void) const
    {
        return  ptrValue != 0 ? true : false;
    };

    const T Get (void) const
    {
        if (HasValue())
            return *ptrValue;
        else
            throw Alarm (
                    MTK_HERE,
                    "nullable", 
                    "Have NO Value",
                    alPriorError, alTypeNoPermisions
            );
    }


    nullable<T>& operator = (const nullable<T>& nulValue)
    {
        if (&nulValue == this)  return *this;
        if (HasValue()  &&  nulValue.HasValue())
        {
            if( ptrValue != nulValue.ptrValue ) 	// verificación de autoasignación.
                 *ptrValue = *(nulValue.ptrValue); 	// T necesita operador de asignación de copia
                                                   	// se podría evitar
        }
        else if (HasValue()  &&  !nulValue.HasValue())
        {
            delete ptrValue;
            ptrValue = 0;
        }
        else if (!HasValue()  &&  nulValue.HasValue())
        {
            ptrValue = new T( *(nulValue.ptrValue) );
        }
        //else if ( !ptrValue &&  !nulValue.ptrValue)
        //{
        //    ;
        // }
        return *this;
    }

    nullable<T>& operator = (const T& value)
    {
        if (HasValue()) {
            delete ptrValue;
            ptrValue = 0;
        }
        *this = nullable(value);
        //*this = nullable<T>(value);	//	esto para bcb
        return *this;
    }

    /*
    bool operator == (const nullable<T>& nulValue) const
    {
        //MMA : OJO está mal. Usa operador==
        //if (ptrValue  ==  nulValue.ptrValue)
        //{
        //    return Get()  ==  nulValue.Get();
        //}

        if (ptrValue  ==  nulValue.ptrValue) return true; //MMA

        if (ptrValue  &&  nulValue.ptrValue) //MMA: Ojo estaba == en vez de &&
        {
            return Get()  ==  nulValue.Get(); //T necesita operador ==
        }
        else if (!ptrValue  &&  !nulValue.ptrValue)
        {
            return true;
        }
        else
            return false;
    }

    bool operator != (const nullable<T>& nulValue) const
    {
        return ( ! this->operator==(nulValue) );
    }
    */

};

template<typename T>
mtk::nullable<T> make_nullable(const T& valor) {
    return nullable<T>(valor);
};


template<typename T>
bool operator == (const nullable<T>& p1, const nullable<T>& p2)
{
    if (p1.HasValue() == p2.HasValue())
    {
        if (p1.HasValue() == false)
            return true;
        else
        {   //  los dos tienen valores
            if (p1.Get() == p2.Get())
                return true;
            else
                return false;
        }
    }
    else
        return false;
}

template<typename T>
bool operator != (const nullable<T>& p1, const nullable<T>& p2)
{
    return !operator==(p1, p2);
}



template<typename T>
std::ostream& operator<< (std::ostream& o, const nullable<T>& n)
{
    if (n.HasValue())
        o << n.Get();
    else
        o << "<null>";
    return o;
};

template<typename T>
YAML::Emitter& operator<< (YAML::Emitter& o, const nullable<T>& n)
{
    if (n.HasValue())
        o << n.Get();
    else
        o << YAML::Null;
    return o;
};





//---------------------------------------------------------------------------

//      N u l l a b l e

//---------------------------------------------------------------------------


template<typename T>
class Nullable
{
	//NO Proporciona operador de igualdad. Nullable1.Get()==Nullable2.Get() (si se necesita)
private:
    T       value;     //T necesita: Constructor vacio, Constructor copia y
                       //  operador de asignación de copia.
    bool    hasValue;

public:
    explicit Nullable(const T& _value)
            :  value(_value), hasValue(true)
    {}
    Nullable(void)
            :  hasValue(false)
    {}


    //  Sirven contructor de copia y operador de asignación

    bool HasValue(void) const
    {
        return  hasValue;
    };

    const T Get (void) const
    {
        if (HasValue())
            return value;
        else
            //MMA
            throw Alarm (
                    MTK_HERE,
                    "Nullable", 
                    "Have NO Value",
                    alPriorError, alTypeNoPermisions
            );

    }



    Nullable<T>& operator = (const T& _value)
    {
        value    = _value;
        hasValue =  true;
        return *this;
    }
};






//---------------------------------------------------------------------------
};      //  namespace mtk {



//---------------------------------------------------------------------------
#endif








/*          E J E M P L O    D E     U S O


#include <iostream>
#include <assert.h>

#include <map>


#include <Nullalbe.h>



class NoTengoConstructorVacio {
public:
    int hola;

    NoTengoConstructorVacio(int pajaritoSinCola)
        : hola(pajaritoSinCola) {}
};



int main()
{

    assert (mtk::nullable<int>(3).HasValue()  == true );
    assert (mtk::nullable<int>( ).HasValue()  == false);

    assert (mtk::nullable<int>(3).Get() == 3          );

    // error en tiempo de ejecución
    //assert (mtk::nullable<int>( ).Get() == 4        );



    assert (
        (mtk::nullable<int>() = 9).Get()
        == 9
    );






    assert (mtk::Nullable<int>(3).HasValue()  == true );
    assert (mtk::Nullable<int>( ).HasValue()  == false);

    assert (mtk::Nullable<int>(3).Get() == 3          );

    // error en tiempo de ejecución
    //assert (mtk::nullable<int>( ).Get() == 4        );



    assert (
        (mtk::Nullable<int>() = 9).Get()
        == 9
    );



    std::map<int, NoTengoConstructorVacio> esteMapaEsDelicado;
    esteMapaEsDelicado[5] = NoTengoConstructorVacio(8); //  esto no compila, ohhhhh....

    std::map<int, mtk::nullable<NoTengoConstructorVacio> > esteMapaPareceNormal;
    esteMapaPareceNormal[5] = mtk::nullable<NoTengoConstructorVacio>(8); //    esto funciona, yuhhuuuu
    esteMapaPareceNormal[99] = 8; //    esto funciona, SIN CONVERSIÓN IMPLÍCITA

    std::map<int, mtk::Nullable<NoTengoConstructorVacio> > esteTambienEsRaro;
    esteTambienEsRaro[5] = mtk::Nullable<NoTengoConstructorVacio>(8); //    esto tampoco compila


    return 0;
}


*/
