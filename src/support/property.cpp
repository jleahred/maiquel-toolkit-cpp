//---------------------------------------------------------------------------


#include "property.h"


//---------------------------------------------------------------------------




namespace mtk {
//---------------------------------------------------------------------------


Property& Property::operator=(const Property& value) {
    if (type==value.type  ||  type==propTypeNone) {
        name = value.name;
        number=value.number;
        text = value.text;
        type = value.type;
        date = value.date;
        return *this;
    }
    else
        throw Alarm (
                    MTK_HERE,
                    "Tipos no compatibles",
                    alPriorError, alTypeNoPermisions
                );
}

bool Property::operator==(const Property& value)const {
    //MMA: como ya no existe nullable::operator(==) se complica la cosa
    // number y date son nullables

    if ( name==value.name  && type==value.type ) {
         if ( type==propTypeNone ) return true;
         if ( type==propTypeText ) return text==value.text;
         if ( type==propTypeNumber ) {
            //if( number.HasValue() && value.number.HasValue() ) //Siempre verdad
                return number.Get() == value.number.Get();
            //else return false;
         }
         //if ( type==varTypeDate ) {  //Solo puede ser Fecha
            //if( date.HasValue() && value.date.HasValue() ) //Siempre verdad
                return number.Get() == value.number.Get();
            //else return false;
         //}
    }
    else
        return false;
}


//Variant::operator std::string() const {
//    if (type==tpText)           return text;
//    else {
//        throw Alarm (
//                            "Variant_operator_std::string",
//                            "Is not a text",
//                            error, noPermisions
//                );
//    }
//    /*  parece más seguro no hacer esta conversión implícita
//    else if (type==tpDate)      return std::string(date);
//    else if (type==tpNumber)    return std::string(number);
//    else return "???";
//    */
//}
//




std::string         Property::AsString     () const
{
    if(type == propTypeText)
        return text;
    else
        throw Alarm (
                            MTK_HERE,
                            "Is not a text",
                            alPriorError, alTypeNoPermisions
                );
}

mtk::DateTime       Property::AsDateTime   () const
{
    if(type == propTypeDate)
        return date.Get();
    else
        throw Alarm (
                            MTK_HERE,
                            "Is not a date",
                            alPriorError, alTypeNoPermisions
                );
}

mtk::FixedNumber    Property::AsFixedNumber() const
{
    if(type == propTypeNumber)
        return number.Get();
    else
        throw Alarm (
                            MTK_HERE,
                            "Is not a number",
                            alPriorError, alTypeNoPermisions
                );
}




std::ostream& operator<< (std::ostream& os, const mtk::Property& prop)
{
    if (prop.IsDate())
        os << "<dt " << prop.GetName() << ": " << prop.AsDateTime() << ">";
    else if (prop.IsNumber())
        os << "<fn " << prop.GetName() << ": " << prop.AsFixedNumber() << ">";
    else if (prop.IsText())
        os << "<tx " << prop.GetName() << ": " << prop.AsString() << ">";
        
    return os;
}



//---------------------------------------------------------------------------
};      //  namespace mtk {

