#ifndef mtkConfigINIH
#define mtkConfigINIH


#include <string>
#include <list>
#include <map>

#include "count_ptr.hpp"
#include "nullable.hpp"




namespace mtk {




class ConfigINI {

public:
    ConfigINI(std::string fileName);
    ~ConfigINI() { Write();  }


    std::list<std::string>  GetSectionsNames        (void)  const;


    std::list<std::string>  GetPropertiesInSection  (const std::string& section) const;


    mtk::Nullable<std::string>  GetValue    (
                                            const std::string&  section ,
                                            const std::string&  propName
                                            )   const;

    void                        SetValue    (
                                            const std::string&  section ,
                                            const std::string&  propName,
                                            const std::string&  value
                                            );

    bool                        DeleteValue (
                                            const std::string&  section ,
                                            const std::string&  propName
                                            );

    void                        Write       ( void );


    std::string  GetStringConfigFileLines () const;



private:

    struct LineInfo {

        LineInfo() {};
        LineInfo(std::string linea);

        std::string       propertyName    ;
        std::string       propertyValue   ;
        std::string       comment         ;
    };

    struct InfoSection {

        InfoSection(std::string _nombre="") : nombre(_nombre) {};

        std::string             nombre          ;
        std::list<LineInfo>     lLineInfo       ;
    };


    bool                            modified                    ;
    std::string                     fileName                    ;
    std::list<std::string>          listSeccionesOriginalOrder  ;
    std::map<std::string, InfoSection>  mapSecciones                ;
};




};  //  namespace mtk {


#endif


