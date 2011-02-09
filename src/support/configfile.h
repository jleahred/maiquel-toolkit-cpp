#ifndef MTK_CONFIGFILE_H
#define MTK_CONFIGFILE_H

//  maintainer: 


/*
 *  P E N D I N G . . .
 * ==========================================================================
 * Faltan la escritura de los comentarios en los set los comentarios
 *
 *
 *
 * Poder crear nodos (actualmente lanza una excepción)
 * Borrar nodos (ahora tampoco lanza una excepción cuando se intenta)
 *       Además cuando un nodo se queda vacío (no tiene nodos ni propiedades) se debería borrar automáticamente
 * Poder consultar si un nodo existe o no
 *
 */


#include <string>
#include "support/list.hpp"
#include "support/hp/humbleparser.h"
#include "support/nullable.hpp"



namespace mtk {

class ConfigFile
{
public:
    enum enPropertyType   {  ptValue, ptList };


    ConfigFile(const std::string& filename="");

    void LoadFromFile(const std::string& filename);
    void SaveToFile  (const std::string&  filename="")const;

    //  acceso a las propiedades
    mtk::Nullable<std::string>             GetValue(const std::string& key) const;
    
    mtk::Nullable<mtk::list<std::string> > GetList (const std::string& key) const;

    void        Modif                (const std::string& key, const std::string& value, const std::string& comment="");
    void        Create               (const std::string& key, const std::string& value, const std::string& comment="");
    void        ModifOrCreate        (const std::string& key, const std::string& value, const std::string& comment="");
    void        Delete               (const std::string& key);

    void        ModifList            (const std::string& key, const mtk::list<std::string>& list);
    void        CreateList           (const std::string& key, const mtk::list<std::string>& list);
    void        ModifOrCreateList    (const std::string& key, const mtk::list<std::string>& list);


    mtk::list<std::string>  GetNodes      (const std::string& key) const;
    mtk::list<mtk::tuple<std::string, enPropertyType> >
                            GetProperties (const std::string& key) const;

    std::string GetStringConfigFileLines(void) const;
	std::string GetFileName_current(void)const { return filename; };
    
    bool IsLoaded(void) const  {  return is_loaded;  };
//     void debug_print(void);


private:
    std::string                     filename;
    mtk::HumbleParser               hParser;
    mtk::CountPtr<AST_Node_Item>    astConfigFile;
    bool                            is_loaded;
};


};  //  end namespace mtk

#endif // MTK_CONFIG_H
