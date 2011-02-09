//---------------------------------------------------------------------------

#ifndef mtkPropertyH
#define mtkPropertyH

#include "support/fixed_number.h"
#include "support/date_time.h"
#include "support/nullable.hpp"


//---------------------------------------------------------------------------

namespace mtk {




enum propEnType { propTypeNone, propTypeNumber, propTypeText, propTypeDate };




/*
---------------------------------------------------------------------------

    @author MMA and JLE
    Property  (con nombre)

---------------------------------------------------------------------------
*/

class Property {
public:


    //  CONSTRUCTORES   ____________________________________________________

    Property (void)
            : type(propTypeNone) {};



    Property (const std::string& _name, const std::string& _value)
            :   name(_name),
                type(propTypeText),
                text(_value)  {};


    Property (const std::string& _name, const FixedNumber& _value)
            :   name(_name),
                type(propTypeNumber),
                number(_value) {};


    Property (const std::string& _name, const DateTime& _date)
            :   name(_name),
                type(propTypeDate),
                date(_date) {};


    //  Sirve el constructor de copia

    Property& operator=(const Property& value);





    //  Conversiones implícitas ___________________________________________
//    operator std::string() const;
//
//    operator FixedNumber() const {
//        if (type==tpNumber)     return number;
//        else
//            throw "variant_operator DateTime() on not DateTime value";
//    }
//
//    operator DateTime()   const {
//        if (type==tpDate) return date.Get();
//        else
//            throw "variant_operator DateTime() on not DateTime value";
//    }







    //  Métodos de acceso  ________________________________________________

    bool IsNumber(void)const { return (type==propTypeNumber) ? true : false;   };

    bool IsText  (void)const { return (type==propTypeText)   ? true : false;   };

    bool IsDate  (void)const { return (type==propTypeDate)   ? true : false;   };


    std::string         GetName      () const  {  return name; }


    std::string         AsString     () const;

    mtk::DateTime       AsDateTime   () const;

    mtk::FixedNumber    AsFixedNumber() const;





    //  OPERADORES      ____________________________________________________
        //  relacionales

    bool operator==(const Property& value)const;

    bool operator!=(const Property& value)const {
        return !operator==(value);
    }



private:
    std::string                     name    ;

    propEnType                      type    ;
    nullable<FixedNumber>           number  ;
    std::string                     text    ;
    nullable<DateTime>              date    ;

};



std::ostream& operator<< (std::ostream& os, const Property& prop);



//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
};   //     namespace mtk {
#endif
