#include "string_codec.h"
#include "foreach.hpp"
#include "alarm.h"





namespace mtk {
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------

//      CodecStringList

//---------------------------------------------------------------------------

CodecStringList::CodecStringList(void)
    :
          scape                     ('\\' )
        , fieldSeparator            (','  )
        , startCoded                ("\\L")     //  sólo especial al inicio de la cadena
    {
        specialCodes.push_back(scape            );
        specialCodes.push_back(fieldSeparator   );
    }


CodecStringList::CodecStringList(
                        const std::string&  _startCoded,
                        char                _scape,
                        char                _fieldSeparator
        )
    :
          scape                     (_scape )
        , fieldSeparator            (_fieldSeparator  )
        , startCoded                (_startCoded)
{
    specialCodes.push_back(scape            );
    specialCodes.push_back(fieldSeparator   );
}


//  Encode interfaz
//      opción 1

void CodecStringList::InitEncode  (void)
{
    if (internalList2Encode.size() !=0) {
        AlarmMsg(
            Alarm (
                MTK_HERE,
                "Init in non empty list",
                mtk::alPriorError,
                mtk::alTypeNoPermisions
            )
        );
        internalList2Encode.clear();
    }
}


void CodecStringList::AddString(const std::string& s)
{
    internalList2Encode.push_back(s);
}




std::string  CodecStringList::Encode      (void)
{
    std::string result(startCoded);



    MTK_FOREACH (itItemEncoding, internalList2Encode) {


        if (itItemEncoding != internalList2Encode.begin())
            result.push_back(fieldSeparator);



        std::string value = *itItemEncoding;
        MTK_FOREACH(itChar, value) {
            if (specialCodes.find(*itChar) != std::string::npos)
            {
                result.push_back('\\');
                result.push_back(*itChar);
            }
            else
                result.push_back(*itChar);
        }


    }


    internalList2Encode.clear();

    return result;
}



std::string CodecStringList::Encode (const std::list<std::string>& ls)
{
    InitEncode();
    for (std::list<std::string>::const_iterator it = ls.begin();
                                                     it != ls.end();
                                                     ++it)
        AddString(*it);

    return Encode();
}





//---------------------------------------------------------------------
//  Decode interfaz

mtk::CountPtr<std::list<std::string> >
CodecStringList::Decode      (const std::string& s)
{
    mtk::CountPtr<std::list<std::string> > result (new std::list<std::string>);

    //  verificar marca de listacodificada
    std::string rStartCode = s.substr(0, startCoded.size());

    if (rStartCode != startCoded) {
        AlarmMsg(
            Alarm (
                MTK_HERE,
                "It's not a coded list, return empty list",
                mtk::alPriorError,
                mtk::alTypeNoPermisions
            )
        );
        return result;
    }




    std::string currentItem;
    for (
            std::string::const_iterator it = s.begin()+startCoded.size();
            it != s.end();
            ++it
        )
    {


        if (*it == scape) {
            if (specialCodes.find(*(it+1)) != std::string::npos) {
                ++it;
                currentItem.push_back(*it);
                continue;
            }
            else
            {
                AlarmMsg(
                    Alarm (
                        MTK_HERE,
                        "Incorrect scape code",
                        mtk::alPriorError,
                        mtk::alTypeNoPermisions
                    )
                );
                return result;
            }
        }

        else if (*it == fieldSeparator) {
            result->push_back(currentItem);
            currentItem = "";
            continue;
        }


        currentItem.push_back(*it);

    }


    result->push_back(currentItem);

    return result;
}















//---------------------------------------------------------------------------

//      CodecStringProperties

//---------------------------------------------------------------------------

CodecStringProperties::CodecStringProperties(void)
    :
          scape                     ('\\' )
        , fieldSeparator            (','  )
        , propertySeparator         ('='  )
        , startCoded                ("\\P")     //  sólo especial al inicio de la cadena
    {
        specialCodes.push_back(scape            );
        specialCodes.push_back(fieldSeparator   );
        specialCodes.push_back(propertySeparator);
    }


CodecStringProperties::CodecStringProperties(const std::string&  _startCoded, char _scape, char _fieldSeparator)
    :
          scape                     (_scape             )
        , fieldSeparator            (_fieldSeparator    )
        , propertySeparator         ('='                )
        , startCoded                (_startCoded        )     //  sólo especial al inicio de la cadena
    {
        specialCodes.push_back(scape            );
        specialCodes.push_back(fieldSeparator   );
        specialCodes.push_back(propertySeparator);
    }




//  Encode interfaz
//      opción 1

void CodecStringProperties::InitEncode  (void)
{
    if (internalMap2Encode.size() !=0) {
        AlarmMsg(
            Alarm (
                MTK_HERE,
                "Init in non empty list",
                mtk::alPriorError,
                mtk::alTypeNoPermisions
            )
        );
        internalMap2Encode.clear();
    }
}


void CodecStringProperties::AddProperty (const std::string& p, const std::string& v)
{
    internalMap2Encode[p] = v;
}




std::string  CodecStringProperties::Encode      (void)
{
    CodecStringList cslItem(startCoded, scape, fieldSeparator);
    CodecStringList cslEncodeProp ("", '\\' , '=');



    cslItem.InitEncode();
    MTK_FOREACH (itItemEncoding, internalMap2Encode) {

        cslEncodeProp.InitEncode();
        cslEncodeProp.AddString(itItemEncoding->first);
        cslEncodeProp.AddString(itItemEncoding->second);
        cslItem.AddString(cslEncodeProp.Encode());

    }


    internalMap2Encode.clear();

    return cslItem.Encode();
}



std::string CodecStringProperties::Encode (const std::map<std::string, std::string>& mp)
{
    InitEncode();
//    for (
//            std::map<std::string, std::string>::const_iterator it = mp.begin();
//            it != mp.end();
//            ++it
//    )
    MTK_FOREACH_CONST_ITERATOR(it, mp)
        AddProperty(it->first, it->second);

    return Encode();
}





//---------------------------------------------------------------------
//  Decode interfaz

mtk::CountPtr<std::map<std::string, std::string> >
CodecStringProperties::Decode      (const std::string& s)
{
    mtk::CountPtr<
            std::map<std::string, std::string>
        > result (new std::map<std::string, std::string>);

    //  verificar marca de listacodificada
    std::string rStartCode = s.substr(0, startCoded.size());

    if (rStartCode != startCoded) {
        AlarmMsg(
            Alarm (
                MTK_HERE,
                "It's not a coded map, return empty map",
                mtk::alPriorError,
                mtk::alTypeNoPermisions
            )
        );
        return result;
    }




    CodecStringList cslItem(startCoded, scape, fieldSeparator);
    mtk::CountPtr<std::list<std::string> > items = cslItem.Decode(s);

    CodecStringList cslParseProperty ("", '\\' , '=');


    MTK_FOREACH_CONTAINER_POINTER(it, items)
//    for (
//                std::list<std::string>::iterator it = items->begin();
//                it != items->end();
//                ++it
//        )
    {
        mtk::CountPtr<std::list<std::string> > propValue = cslParseProperty.Decode (*it);
        std::string nombre  =   propValue->front();
        std::string value;
        propValue->pop_front();
        if (propValue->size() != 0)
            value   =   propValue->front();
        else
            value   = "";

        (*result) [nombre]  =   value;
    }


    internalMap2Encode.clear();


    return result;
}







//---------------------------------------------------------------------------
};      //  namespace mtk {
