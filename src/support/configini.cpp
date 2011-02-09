#include "configini.h"
#include <fstream>

#include "string_codec.h"
#include "mtk_string.h"
#include "alarm.h"


namespace mtk {


ConfigINI::ConfigINI(std::string _fileName)
    :   modified(false),
        fileName(_fileName)
{
    std::ifstream           file(fileName.c_str());

    if (file.is_open() == false)
    {
            throw
                        Alarm (
                            MTK_HERE, "configini",
                            std::string("No se pudo abrir el fichero  ") + fileName,
                            alPriorCritic,
                            alTypeNoPermisions
                        )

            ;

    }

    std::string             line                            ;
    std::string             inSection("___none___")         ;
    InfoSection             currentInfoSection(inSection)   ;

    while(std::getline(file, line)) {

        if (line[0] == '[') {

            mapSecciones[inSection] = currentInfoSection;
            listSeccionesOriginalOrder.push_back(inSection);

            inSection = s_trim(line.substr(1, line.find(']')-1), ' ');
            //  todo: si existe protestar y cancelar
            currentInfoSection = InfoSection(inSection);
            continue;
        }

        currentInfoSection.lLineInfo.push_back(LineInfo(line));

    }

    mapSecciones[inSection] = currentInfoSection;
    listSeccionesOriginalOrder.push_back(inSection);
}

ConfigINI::~ConfigINI()
{
    try{
        Write();
    } catch(...){
        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "exception on destructor", "catched exception on destructor", mtk::alPriorError));
    }
}


ConfigINI::LineInfo::LineInfo(std::string _line)
{
    _line = s_trim(_line, ' ');
    if (_line.size() ==0)       return;

    if (_line[0] == ';'  ||  _line[0] == '#') {
        comment = _line;
        return;
    }


    CodecStringList csl("", '\\', '=');

    mtk::CountPtr<std::list<std::string> > listPropValue = csl.Decode (_line);
    propertyName  =   listPropValue->front();

    listPropValue->pop_front();

    if (listPropValue->size() != 0)
        propertyValue   =   listPropValue->front();
    else
        propertyValue   = "";


}



std::list<std::string>  ConfigINI::GetSectionsNames        (void) const
{
    std::list<std::string> result;

    for(auto itSection=listSeccionesOriginalOrder.begin(); itSection!=listSeccionesOriginalOrder.end(); ++itSection) {
        result.push_back(*itSection);
    }

//    MTK_FOREACH(itSection, mapSecciones) {
//        result.push_back(itSection->first);
//    }
    return result;
}


std::list<std::string>  ConfigINI::GetPropertiesInSection  (const std::string& _section) const
{
    std::list<std::string> result;

//    std::list<LineInfo> llif = mapSecciones[_section].lLineInfo;
    if (mapSecciones.find(_section) == mapSecciones.end())
        return result;
    const std::list<LineInfo>& llif = mapSecciones.find(_section)->second.lLineInfo;

    for(auto itLineInfo=llif.begin(); itLineInfo!=llif.end(); ++itLineInfo)
    {
        if (itLineInfo->propertyName != "")
            result.push_back(itLineInfo->propertyName);
    }

    return result;

}

mtk::Nullable<std::string> ConfigINI::GetValue (
                                            const std::string&  _section,
                                            const std::string&  _propName
                                )  const
{
        //  si no es un método constante, esto vale...
//    std::list<LineInfo> llif = mapSecciones[_section].lLineInfo;
        //  al ponerlo como método constante, es necesario algo como...
    if (mapSecciones.find(_section) == mapSecciones.end())
        return mtk::Nullable<std::string>();

    const std::list<LineInfo>& llif = mapSecciones.find(_section)->second.lLineInfo;

    for(auto itLineInfo = llif.cbegin();  itLineInfo != llif.cend(); ++itLineInfo)
    {
        if (itLineInfo->propertyName == _propName)
            return mtk::Nullable<std::string>(itLineInfo->propertyValue);
    }


    return mtk::Nullable<std::string>();
}

void  ConfigINI::SetValue   (
                                        const std::string&  section,
                                        const std::string&  propName,
                                        const std::string&  value
                            )
{

    //  si la sección no existe darla de alta en listSeccionesOriginalOrder
    if (mapSecciones.find(section) == mapSecciones.end())
        listSeccionesOriginalOrder.push_back(section);

    //  si la sección no existe se crea
    std::list<LineInfo>& llif = mapSecciones[section].lLineInfo;

        bool propiedadEncontrada = false;
        for(auto itLineInfo = llif.begin(); itLineInfo != llif.end(); ++itLineInfo)
        {
            if (itLineInfo->propertyName == propName) {
                propiedadEncontrada = true;
                if (itLineInfo->propertyValue != value)
                {
                    itLineInfo->propertyValue = value;
                    modified = true;
                }
            }
        }

        if (propiedadEncontrada == false)
        {
            LineInfo nuevaPropiedad;
            nuevaPropiedad.propertyName = propName;
            nuevaPropiedad.propertyValue = value;
            llif.push_front(nuevaPropiedad);
            modified = true;
        }

}

bool  ConfigINI::DeleteValue (
                                        const std::string&  _section ,
                                        const std::string&  _propName
                                        )
{
    //  si la sección no existe...
    if (mapSecciones.find(_section) == mapSecciones.end())
        return false;


    std::list<LineInfo>& llif = mapSecciones.find(_section)->second.lLineInfo;
    for(auto itLineInfo=llif.begin(); itLineInfo!=llif.end(); ++itLineInfo)
    {
        if (itLineInfo->propertyName == _propName) {
                llif.erase(itLineInfo);
                modified = true;
                return true;
        }
    }

    return false;
}



void ConfigINI::Write      ( void )
{
    modified = false;   ///\todo pendiente de activar optimización de no escritura si no hay cambios (probar)

    std::ofstream file(fileName.c_str());
//    std::ofstream file((fileName+".pr").c_str());

    if (file.is_open() == false)
    {
            throw
                        Alarm (
                            MTK_HERE, "configini",
                            std::string("No se pudo abrir el fichero  ") + fileName,
                            alPriorCritic,
                            alTypeNoPermisions
                        )

            ;

    }

    std::list<std::string>  lSections = GetSectionsNames();

    CodecStringList csl("", '\\', '=');

    for(auto itSectionName = lSections.begin(); itSectionName != lSections.end(); ++itSectionName) {
        std::list<LineInfo> llif = mapSecciones[*itSectionName].lLineInfo;
        if ( *itSectionName != "___none___")
            file << "[" << *itSectionName << "]" << std::endl;

        for(auto itLineInfo = llif.begin(); itLineInfo != llif.end(); ++itLineInfo) {
            if (itLineInfo->propertyName!="" /*&&  itLineInfo->propertyValue!=""*/) {
                csl.AddString(itLineInfo->propertyName);
                csl.AddString(itLineInfo->propertyValue);
                file << csl.Encode() << std::endl;
            }
            else if (itLineInfo->propertyName=="" &&  itLineInfo->propertyValue=="") {
                file << itLineInfo->comment << std::endl;
            }
        }
    }
    file.flush();
}


std::string ConfigINI::GetStringConfigFileLines () const
{
    const unsigned short MAX_LINES_NUMBER=500;
    unsigned short linesNumber=0;
    std::string result;

    for(auto itSection = listSeccionesOriginalOrder.begin(); itSection != listSeccionesOriginalOrder.end(); ++itSection) {
        result.append("[" + *itSection + "]" + "\n\r");
        linesNumber++;
        const std::list<LineInfo>& llif = mapSecciones.find(*itSection)->second.lLineInfo;

        for(auto itLineInfo = llif.begin(); itLineInfo != llif.end(); ++itLineInfo) {
            if (itLineInfo->propertyName != "")
            {
                result.append(itLineInfo->propertyName + "=" + itLineInfo->propertyValue + "\n\r");
                linesNumber++;
            }
            else if (itLineInfo->comment != "")
            {
                result.append(itLineInfo->comment + "\n\r");
                linesNumber++;
            }

            if (linesNumber>=MAX_LINES_NUMBER)  break;
        }

        if (linesNumber>=MAX_LINES_NUMBER)  break;
    }

    return result;
}







};  //  namespace mtk {
