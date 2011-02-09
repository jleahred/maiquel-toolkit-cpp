#ifndef mtkStingCodecH
#define mtkStingCodecH


#include <string>
#include <list>
#include <map>

#include "count_ptr.hpp"




/**

    Codificación y decodificación de string a y desde...

        Listas de strings
        Listas de propiedades
        Recursividad (el código generado puede ser críptico)

    Es importante tratar que la codificación no sea muy críptica para una
    lectura o manipulación manual

    También es importante que la codificación sea compacta


*/



namespace mtk {
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------

//      CodecStringList

//---------------------------------------------------------------------------

class CodecStringList {


public:

    CodecStringList(void);
    CodecStringList(const std::string&  _startCoded, char _scape, char _fieldSeparator);



    //---------------------------------------------------------------------
    //  Encode interfaz
    //      opción 1
    void            InitEncode  (void                               );
    void            AddString   (const std::string& s               );
    std::string     Encode      (void                               );

    //      opción 2
    std::string     Encode      (const std::list<std::string>& ls   );

    //---------------------------------------------------------------------





    //---------------------------------------------------------------------
    //  Decode interfaz

    mtk::CountPtr<std::list<std::string> >
    Decode      (const std::string& s);

    //---------------------------------------------------------------------




private:
    const char              scape                   ;
    const char              fieldSeparator          ;
    const std::string       startCoded              ;

    std::string             specialCodes            ;



    std::list<std::string>  internalList2Encode     ;

};















//---------------------------------------------------------------------------

//      CodecStringProperties

//---------------------------------------------------------------------------

class CodecStringProperties {


public:

    CodecStringProperties(void);
    CodecStringProperties(const std::string&  _startCoded, char _scape, char _fieldSeparator);



    //---------------------------------------------------------------------
    //  Encode interfaz
    //      opción 1
    void            InitEncode  (void                                        );
    void            AddProperty (const std::string& p, const std::string& v  );
    std::string     Encode      (void                                        );

    //      opción 2
    std::string     Encode      (const std::map<std::string, std::string>& mp);

    //---------------------------------------------------------------------





    //---------------------------------------------------------------------
    //  Decode interfaz

    mtk::CountPtr<std::map<std::string, std::string> >
    Decode      (const std::string& s);

    //---------------------------------------------------------------------




private:
    const char              scape                   ;
    const char              fieldSeparator          ;
    const char              propertySeparator       ;
    const std::string       startCoded              ;

    std::string             specialCodes            ;



    std::map<std::string, std::string>  internalMap2Encode;

};




//---------------------------------------------------------------------------
};      //  namespace mtk {



//---------------------------------------------------------------------------
#endif
