#include <iostream>

#include "support/mtk_string.h"
#include "support/configfile.h"
#include "support/nullable.hpp"
#include "support/foreach.hpp"
#include "support/alarm.h"
#include "support/list.hpp"


//*********************************************************************************************************************
//*********************************************************************************************************************
//*********************************************************************************************************************


bool CheckPropertiesForNode(const mtk::ConfigFile& config, const mtk::ConfigFile& config2,  const std::string& keys)
{

    const mtk::list<mtk::tuple<std::string, mtk::ConfigFile::enPropertyType> > lproperties = config.GetProperties(keys);
    const mtk::list<mtk::tuple<std::string, mtk::ConfigFile::enPropertyType> > lproperties2 = config2.GetProperties(keys);

    if (lproperties.size() != lproperties2.size())
    {
        std::cout << "Los ficheros no son consistentes. En el nodo [" << keys << "] no hay las mismas propiedades " << lproperties.size() << " != " << lproperties2.size() << std::endl;
        return false;
    }

    mtk::list< mtk::tuple<std::string, mtk::ConfigFile::enPropertyType> >::const_iterator it1 = lproperties.begin();
    mtk::list< mtk::tuple<std::string, mtk::ConfigFile::enPropertyType> >::const_iterator it2 = lproperties2.begin();

    while(it1 != lproperties.end())
    {
        if (it1->_0 != it2->_0)
        {
            std::cout << "Los ficheros no son consistentes. En el nodo [" << keys  << "] propiedad " << it1->_0  << " != " << it2->_0 << std::endl;
            return false;
        }
        else
        {
			try
			{
                if (it1->_1 != it2->_1)
                {
                    std::cout << "Los ficheros no son consistentes. En el nodo [" << keys << "] " <<
			"Tipos de propiedad distintas: " << int(it1->_1)  << " != " << int(it2->_1) << std::endl;
                    return false;
                }
                if (it1->_1 == mtk::ConfigFile::ptValue) //Es una propiedad valor
                {
                    mtk::Nullable<std::string> valor1 = config .GetValue(MTK_SS(keys << "." << it1->_0));
                    mtk::Nullable<std::string> valor2 = config2.GetValue(MTK_SS(keys << "." << it2->_0));
                    if (valor1.HasValue() && valor2.HasValue())
                    {
                        if (valor1.Get() != valor2.Get())
                        {
                            std::cout << "Los ficheros no son consistentes. En el nodo [" << keys << "] " << valor1.Get()  << " != " << valor2.Get() << std::endl;
                            return false;
                        }
                        else
                            if (valor1.Get() == "")
                                std::cout << "PROPERTY [" << keys << "." << it1->_0 << "] = ~" << std::endl;
                            else
                                std::cout << "PROPERTY [" << keys << "." << it1->_0 << "] = " << valor1.Get() << std::endl;
                    }
                    else
                    {
                        if (valor1.HasValue() != valor2.HasValue())
                        {
                            std::cout << "PROPERTY [" << keys << "." << it1->_0 << "] = " << valor1.Get() << std::endl;
                            std::cout << "Los ficheros no son consistentes. En el nodo [" << keys << "] " << valor1.HasValue() << " diferente HasValue() " << valor2.HasValue() << std::endl;
                            return false;
                        }
                        else
                            std::cout << "PROPERTY [" << keys << "." << it1->_0 << "] no tiene valor" << std::endl;
                    }
                }
                else //Es una propiedad lista
                {
                    if (config.GetList(MTK_SS(keys << "." << it1->_0)).HasValue() != config2.GetList(MTK_SS(keys << "." << it2->_0)).HasValue() )
                    {
                            std::cout << "PROPERTY [" << keys << "." << it1->_0 << "] " << std::endl;
                            std::cout << "Los ficheros no son consistentes. En el nodo [" << keys << "] " <<
                                            config.GetList(MTK_SS(keys << "." << it1->_0)).HasValue() << " diferente HasValue() " <<
                                            config2.GetList(MTK_SS(keys << "." << it2->_0)).HasValue() << std::endl;
                            return false;
                    }
                    else
                    {
                        if (config.GetList(MTK_SS(keys << "." << it1->_0)).HasValue())
                        {
                            mtk::list<std::string>   listitems = config.GetList(MTK_SS(keys << "." << it1->_0)).Get();
                            mtk::list<std::string>   listitems2 = config2.GetList(MTK_SS(keys << "." << it2->_0)).Get();
                            if (listitems.size() != listitems2.size())
                            {
                                std::cout << "Los ficheros no son consistentes. En la lista [" << keys << "." << it1->_0 <<
                                                "] no hay los mismos elementos " << listitems.size() << " != " << listitems2.size() << std::endl;
                                return false;
                            }

                            std::cout << "LISTA " << it1->_0 << ": " << std::endl <<
                                            "[" << std::endl;

                            mtk::list<std::string>::const_iterator itList1 = listitems.begin();
                            mtk::list<std::string>::const_iterator itList2 = listitems2.begin();

                            while(itList1 != listitems.end())
                            {
                                std::cout << *itList1 << std::endl;
                                if (*itList1 != *itList2)
                                {
                                    std::cout << "Los ficheros no son consistentes. En la lista [" << keys << "." << it1->_0 <<
                                                "] el elemento " << *itList1 << " != " << *itList2 << std::endl;
                                    return false;
                                }
                                ++itList1;
                                ++itList2;
                            }
                            std::cout << "]" << std::endl;
                        }
                        else
                            std::cout << "PROPERTY LIST [" << keys << "." << it1->_0 << "] no tiene valor" << std::endl;
                    }
                }
			}
			catch(const mtk::Alarm& alarma)
			{
                //Si no es la alarma de demasiada recursividad lanzamos una excepción
                std::list<mtk::BaseAlarm>::const_iterator it = alarma.stackAlarms.begin();
                if (it != alarma.stackAlarms.end())
                {
                    if ((*it).message != "too depth recursion (11)  $(SECT1.PROP1)  on file config2.cfg")
                        throw;
                }
			}
        }
        ++it1;
        ++it2;
    }
    return true;
}

//*********************************************************************************************************************
//*********************************************************************************************************************
//*********************************************************************************************************************


bool CheckNodes(const mtk::ConfigFile& config, const mtk::ConfigFile& config2,  const std::string& keys)
{
    const mtk::list<std::string> lnodes = config.GetNodes(keys);
    const mtk::list<std::string> lnodes2 = config2.GetNodes(keys);

    if (lnodes.size() != lnodes2.size())
    {
        std::cout << "Los ficheros no son consistentes. En el nodo [" << keys << "] no hay los mismos nodos " << lnodes.size() << " != " << lnodes2.size() << std::endl;
        return false;
    }

    mtk::list<std::string>::const_iterator it1 = lnodes.begin();
    mtk::list<std::string>::const_iterator it2 = lnodes2.begin();

    while(it1 != lnodes.end())
    {
        if (*it1 != *it2)
        {
            std::cout << "Los ficheros no son consistentes. En el nodo [" << keys << "] nodo " << *it1  << " != " << *it2 << std::endl;
            return false;
        }
        else
            std::cout << "NODE [" << keys << "] = " << *it1 << std::endl;

        std::string newkeys;
        if (keys != "")
            newkeys = MTK_SS(keys <<  "." << *it1);
        else
            newkeys = *it1;

        //Chequeamos las propiedades del nodo
        if (CheckPropertiesForNode(config, config2, newkeys) == false)
            return false;

        if (CheckNodes(config, config2, newkeys) == false)
            return false;

        ++it1;
        ++it2;
    }
    return true;
}


//*********************************************************************************************************************
//*********************************************************************************************************************
//*********************************************************************************************************************

int main(void)
{
    try
    {
        mtk::ConfigFile config("config2.cfg");
        mtk::ConfigFile configAux;

        config.SaveToFile("config_saved2.cfg");
        std::cout  << "Fichero config_saved2.cfg guardado" << std::endl;

        configAux.LoadFromFile("config_saved2.cfg");
        std::cout  << "Fichero config_saved2.cfg cargado" << std::endl;


        std::cout << "************************************************************************************" << std::endl;
        std::cout << "Comprobamos todo el fichero" << std::endl;
        if (!CheckNodes(config, configAux, ""))
            std::cout << "Los ficheros no son consistentes" << std::endl;
        else
            std::cout << "Los ficheros son consistentes" << std::endl;
        std::cout << "************************************************************************************" << std::endl << std::endl;

        //  obtener valores de varios niveles
        std::cout << "************************************************************************************" << std::endl;
        std::cout << "Vamos a leer algunas propiedades" << std::endl;
        mtk::Nullable <std::string> valorConfig = config.GetValue("ADMIN.ProcessPriority");
        if (valorConfig.HasValue() )
            std::cout << "[ADMIN.ProcessPriority] = " << valorConfig.Get()  << std::endl;
        else
        {
            std::cout << "REVISAR!!! El funcionamiento no es el esperado [ADMIN.ProcessPriority] No tiene valor" << std::endl;
            return -1;
        }

        valorConfig = config.GetValue("ADMIN.TibcoServices.Client");
        if (valorConfig.HasValue() )
            std::cout << "[ADMIN.TibcoServices.Client] = " << valorConfig.Get() << std::endl;
        else
        {
            std::cout << "REVISAR!!! El funcionamiento no es el esperado [ADMIN.TibcoServices.Client] No tiene valor" << std::endl;
            return -2;
        }

        valorConfig = config.GetValue("HOLA.prueba");
        if (valorConfig.HasValue() )
            std::cout << "[HOLA.prueba] = " << valorConfig.Get() << std::endl;
        else
        {
            std::cout << "REVISAR!!! El funcionamiento no es el esperado [HOLA.prueba] No tiene valor" << std::endl;
            return -3;
        }

        valorConfig = config.GetValue("HOLA.noExisto");
        if (valorConfig.HasValue() )
        {
            std::cout << "REVISAR!!! El funcionamiento no es el esperado [HOLA.noExisto] = " << valorConfig.Get() << std::endl;
            return -4;
        }
        else
            std::cout << "[HOLA.noExisto] No tiene valor" << std::endl;
        std::cout << "************************************************************************************" << std::endl << std::endl;



        std::cout << "************************************************************************************" << std::endl;
        std::cout << "Obtenemos la lista de propiedades de [ADMIN.TibcoServices]"  << std::endl;
        const mtk::list<mtk::tuple<std::string, mtk::ConfigFile::enPropertyType> > lproperties = config.GetProperties("ADMIN.TibcoServices");
        MTK_FOREACH_CONST_ITERATOR (itProperty, lproperties)
        {
            std::cout <<  itProperty->_0 << std::endl;
        }

        std::cout << "************************************************************************************" << std::endl << std::endl;



        std::cout << "************************************************************************************" << std::endl;
        std::cout << "Obtenemos la lista de nodos de [ADMIN.PR1]"  << std::endl;
        const mtk::list<std::string> lnodes = config.GetNodes("ADMIN.PR1");
        MTK_FOREACH_CONST_ITERATOR (itNode, lnodes)
        {
            std::cout <<  *itNode << std::endl;
        }

        std::cout << "************************************************************************************" << std::endl << std::endl;


        //  escribir valor anidado
        std::cout << "************************************************************************************" << std::endl;
        std::cout << "Escribimos un valor en una propiedad de un nodo anidado" << std::endl;
        config.ModifOrCreate("ADMIN.TibcoServices.Client", "555");
        config.SaveToFile("config_saved.cfg");
        configAux.LoadFromFile("config_saved.cfg");


        valorConfig = config.GetValue("ADMIN.TibcoServices.Client");
        mtk::Nullable <std::string> valorConfig2 = configAux.GetValue("ADMIN.TibcoServices.Client");
        if (valorConfig.HasValue() && valorConfig2.HasValue() )
        {
            if (valorConfig.Get()  == valorConfig.Get() )
                std::cout << "Los ficheros son consistentes [ADMIN.TibcoServices.Client] " << valorConfig.Get() << " == " << valorConfig2.Get() << std::endl;
            else
            {
                std::cout << "REVISAR!!! Los ficheros no son consistentes [ADMIN.TibcoServices.Client] " << valorConfig.Get() << " != " << valorConfig2.Get() << std::endl;
                return -5;
            }
        }
        else
        {
             if (valorConfig.HasValue() != valorConfig2.HasValue())
             {
                std::cout << "REVISAR!!! Los ficheros no son consistentes [ADMIN.TibcoServices.Client] " << valorConfig.HasValue() << " distinto HasValue() " << valorConfig2.HasValue() << std::endl;
                return -6;
             }
             else
             {
                std::cout << "REVISAR!!! El funcionamiento no es el esperado [ADMIN.TibcoServices.Client] no tiene valor" << std::endl;
                return -7;
             }
        }
        std::cout << "************************************************************************************" << std::endl << std::endl;


        //  añadir valores y nodos
        std::cout << "************************************************************************************" << std::endl;
        std::cout << "Añadimos una propiedad a un nodo existente" << std::endl;
        config.ModifOrCreate("ADMIN.TibcoServices.Nuevo", "666");
        config.SaveToFile("config_saved.cfg");
        configAux.LoadFromFile("config_saved.cfg");

        valorConfig = config.GetValue("ADMIN.TibcoServices.Nuevo");
        valorConfig2 = configAux.GetValue("ADMIN.TibcoServices.Nuevo");
        if (valorConfig.HasValue() && valorConfig2.HasValue() )
        {
            if (valorConfig.Get()  == valorConfig.Get() )
                std::cout << "Los ficheros son consistentes [ADMIN.TibcoServices.Nuevo] " << valorConfig.Get() << " == " << valorConfig2.Get() << std::endl;
            else
            {
                std::cout << "REVISAR!!! Los ficheros no son consistentes [ADMIN.TibcoServices.Nuevo] " << valorConfig.Get() << " != " << valorConfig2.Get() << std::endl;
                return -8;
            }
        }
        else
        {
             if (valorConfig.HasValue() != valorConfig2.HasValue() )
             {
                std::cout << "REVISAR!!! Los ficheros no son consistentes [ADMIN.TibcoServices.Nuevo] " << valorConfig.HasValue() << " distinto HasValue() " << valorConfig2.HasValue() << std::endl;
                return -9;
             }
             else
             {
                 std::cout << "REVISAR!!! El funcionamiento no es el esperado [ADMIN.TibcoServices.Nuevo] no tiene valor" << std::endl;
                 return -10;
             }
        }

        std::cout << "Añadimos una propiedad a un nodo existente" << std::endl;
        config.ModifOrCreate("ADMIN.TibcoServices.Nuevo2", "777");
        config.SaveToFile("config_saved.cfg");
        configAux.LoadFromFile("config_saved.cfg");

        valorConfig = config.GetValue("ADMIN.TibcoServices.Nuevo2");
        valorConfig2 = configAux.GetValue("ADMIN.TibcoServices.Nuevo2");
        if (valorConfig.HasValue() && valorConfig2.HasValue() )
        {
            if (valorConfig.Get()  == valorConfig.Get() )
                std::cout << "Los ficheros son consistentes [ADMIN.TibcoServices.Nuevo2] " << valorConfig.Get() << " == " << valorConfig2.Get() << std::endl;
            else
            {
                std::cout << "REVISAR!!! Los ficheros no son consistentes [ADMIN.TibcoServices.Nuevo2] " << valorConfig.Get() << " != " << valorConfig2.Get() << std::endl;
                return -11;
            }
        }
        else
        {
             if (valorConfig.HasValue() != valorConfig2.HasValue() )
             {
                std::cout << "REVISAR!!! Los ficheros no son consistentes [ADMIN.TibcoServices.Nuevo2] " << valorConfig.HasValue() << " distinto HasValue() " << valorConfig2.HasValue() << std::endl;
                return -12;
             }
             else
             {
                 std::cout << "REVISAR!!! El funcionamiento no es el esperado [ADMIN.TibcoServices.Nuevo2] no tiene valor" << std::endl;
                 return -13;
             }
        }

        std::cout << "************************************************************************************"  << std::endl << std::endl;



        std::cout << "************************************************************************************"  << std::endl;
        std::cout << "Añadimos una propiedad a un nodo existente utilizando simbolos" << std::endl;
        config.ModifOrCreate("ADMIN.ConSim-bolo_s", "8888");
        config.SaveToFile("config_saved.cfg");
        configAux.LoadFromFile("config_saved.cfg");


        valorConfig = config.GetValue("ADMIN.ConSim-bolo_s");
        valorConfig2 = configAux.GetValue("ADMIN.ConSim-bolo_s");
        if (valorConfig.HasValue() && valorConfig2.HasValue() )
        {
            if (valorConfig.Get()  == valorConfig.Get() )
                std::cout << "Los ficheros son consistentes [ADMIN.ConSim-bolo_s] " << valorConfig.Get() << " == " << valorConfig2.Get() << std::endl;
            else
            {
                std::cout << "REVISAR!!! Los ficheros no son consistentes [ADMIN.ConSim-bolo_s] " << valorConfig.Get() << " != " << valorConfig2.Get() << std::endl;
                return -14;
            }
        }
        else
        {
             if (valorConfig.HasValue() != valorConfig2.HasValue() )
             {
                std::cout << "REVISAR!!! Los ficheros no son consistentes [ADMIN.ConSim-bolo_s] " << valorConfig.HasValue() << " distinto HasValue() " << valorConfig2.HasValue() << std::endl;
                return -15;
             }
             else
             {
                 std::cout << "REVISAR!!! El funcionamiento no es el esperado [ADMIN.ConSim-bolo_s] no tiene valor" << std::endl;
                 return -16;
             }
        }

        std::cout << "************************************************************************************" << std::endl << std::endl;


        try
        {
            //  añadir valores y nodos
                    //Raquel:
                    //Actualmente no se pueden crear nodos pero opino que sería interesante poder hacerlo
                    //Ahora no se pueden crear y lanza una excepción al intertar hacerlo
            std::cout << "************************************************************************************" << std::endl;
            std::cout << "Añadimos una propiedad a un nodo nuevo" << std::endl;
            config.ModifOrCreate("NODO_NUEVO.hOLa",  "999999");
            config.SaveToFile("config_saved.cfg");
            configAux.LoadFromFile("config_saved.cfg");
            valorConfig = config.GetValue("NODO_NUEVO.hOLa");
            valorConfig2 = configAux.GetValue("NODO_NUEVO.hOLa");
            if (valorConfig.HasValue() && valorConfig2.HasValue() )
            {
                if (valorConfig.Get()  == valorConfig.Get() )
                    std::cout << "Los ficheros son consistentes [NODO_NUEVO.hOLa] " << valorConfig.Get() << " == " << valorConfig2.Get() << std::endl;
                else
                {
                    std::cout << "REVISAR!!! Los ficheros no son consistentes [NODO_NUEVO.hOLa] " << valorConfig.Get() << " != " << valorConfig2.Get() << std::endl;
                    return -17;
                }
            }
            else
            {
                if (valorConfig.HasValue() != valorConfig2.HasValue() )
                {
                    std::cout << "REVISAR!!! Los ficheros no son consistentes [NODO_NUEVO.hOLa] " << valorConfig.HasValue() << " distinto HasValue() " << valorConfig2.HasValue() << std::endl;
                    return -18;
                }
                else
                {
                    std::cout << "REVISAR!!! El funcionamiento no es el esperado [NODO_NUEVO.hOLa] no tiene valor" << std::endl;
                    return -19;
                }
            }
            std::cout << "************************************************************************************" << std::endl << std::endl;
        }
        catch(const mtk::Alarm& alarma)
        {
            std::list<mtk::BaseAlarm>::const_iterator it = alarma.stackAlarms.begin();

            bool encontrado = false;
            while (it != alarma.stackAlarms.end())
            {
                if ((*it).message == "Cannot create property with a node key [NODO_NUEVO.hOLa]   node doesn't exists")
                {
                    encontrado = true;
                    std::cout << "No está permitido crear una propiedad en un nodo nuevo: "<< std::endl;
                    std::cout << "__NR__:  " << MTK_SS(alarma)  << std::endl;
                }
                it ++;
            }
            if (!encontrado)
            {
                 std::cout << "REVISAR!!! Alarma: " << MTK_SS(alarma) << std::endl;
                 return -20;
            }
        }
        catch (std::exception& e)
        {
            std::cout << "REVISAR!!! Excepción: " << e.what() << std::endl;
            return -21;
        }
        catch (...)
        {
            std::cout << "REVISAR!!!"<< std::endl;
            return -22;
        }

        //  borrar un valor
                //Raquel:
                //Actualmente no se pueden borrar nodos, pero creo que puede llegar a ser interesante.
                    //Es más, cuando a un nodo se le borran todas las propiedades sería conveniente que ese nodo desapareciera automáticamente.
                    //Haciendo eso los ficheros de configuración no se quedan con basura.

        std::cout << "************************************************************************************" << std::endl;
        std::cout << "Vamos a borrar una propiedad" << std::endl;
        config.Delete("ADMIN.ESTASEBORRA");
        config.SaveToFile("config_saved.cfg");
        configAux.LoadFromFile("config_saved.cfg");
        valorConfig = config.GetValue("ADMIN.ESTASEBORRA");
        valorConfig2 = configAux.GetValue("ADMIN.ESTASEBORRA");
        if (valorConfig.HasValue() != valorConfig2.HasValue())
            std::cout << "Los ficheros no son consistentes [ADMIN.ESTASEBORRA] " << valorConfig.HasValue() << " distinto HasValue() " << valorConfig2.HasValue() << std::endl;
        else
        {
            if (!valorConfig.HasValue())
                std::cout << "Se ha borrado la propiedad [ADMIN.ESTASEBORRA]" << std::endl;
            else
                std::cout << "El funcionamiento no es el esperado [ADMIN.ESTASEBORRA] no se ha borrado" << std::endl;

        }
        std::cout << "************************************************************************************" << std::endl << std::endl;



        std::cout << "************************************************************************************" << std::endl;
        std::cout << "Comprobamos todo el fichero" << std::endl;
        if (!CheckNodes(config, configAux, ""))
            std::cout << "Los ficheros no son consistentes" << std::endl;
        else
            std::cout << "Los ficheros son consistentes" << std::endl;
        std::cout << "************************************************************************************" << std::endl << std::endl;



        //Borrar nodos
                //Raquel:
                //Actualmente no deja borrar modos pero tampoco avisa cuando los quieres borrar
                //Es mas, creo que se debería poder consultar si un nodo existe de alguna manera...
                //Como dije antes creo que es interesante que deje borrar los nodos, pero si no deja debería lanzar una excepción
        try
        {
            std::cout << "************************************************************************************" << std::endl;
            std::cout << "Vamos a borrar un nodo" << std::endl;
            config.Delete("ADMIN");
            config.SaveToFile("config_saved.cfg");
            //Raquel:
            //Comprobamos si se ha borrado cogiendo una propiedad de ADMIN que estaba, ya que no sé como consultar si existe un nodo
            valorConfig = config.GetValue("ADMIN.ProcessPriority");
            valorConfig2 = configAux.GetValue("ADMIN.ProcessPriority");
            if (valorConfig.HasValue() != valorConfig2.HasValue())
            {
                std::cout << "Los ficheros no son consistentes [ADMIN] " << valorConfig.HasValue() << " distinto HasValue() " << valorConfig2.HasValue() << std::endl;
            }
            else
            {
                if (!valorConfig.HasValue())
                    std::cout << "Se ha borrado el nodo [ADMIN]" << std::endl;
                else
                {
                    std::cout << "REVISAR!!! Actualmente no se permiten borrar nodos [ADMIN] no se ha borrado" << std::endl;
                    return -23;
                }
            }
            std::cout << "************************************************************************************" << std::endl << std::endl;
        }
        catch(const mtk::Alarm& alarma)
        {
            std::list<mtk::BaseAlarm>::const_iterator it = alarma.stackAlarms.begin();
            if (it != alarma.stackAlarms.end())
            {
                if ((*it).message == "Cannot delete on keys.property [ADMIN]")
                {
                    std::cout << "No esta permitido borrar un nodo: " << std::endl;
                    std::cout << "__NR__:  " << MTK_SS(alarma) << std::endl;
                }
                else
                {
                     std::cout << "REVISAR!!! Alarma: " << MTK_SS(alarma) << std::endl;
                     return -24;
                }

            }
        }
        catch (std::exception& e)
        {
            std::cout << "REVISAR!!! Excepción: " << e.what() << std::endl;
            return -25;
        }
        catch (...)
        {
            std::cout << "REVISAR!!!"<< std::endl;
            return -26;
        }


        try
        {
            std::cout << "************************************************************************************" << std::endl;
            //  no se puede escribir un valor en un nodo   (lanzaría una excepción)
            std::cout << "Vamos a intentar escribir un valor en un nodo:" << std::endl;
            config.ModifOrCreate ("ADMIN", "oooooohhhhhhhhhHHHHH!!!!");
            config.SaveToFile("config_saved.cfg");
            valorConfig = config.GetValue("ADMIN.oooooohhhhhhhhhHHHHH!!!!");
            valorConfig2 = configAux.GetValue("ADMIN.oooooohhhhhhhhhHHHHH!!!!");
            if (valorConfig.HasValue() && valorConfig2.HasValue() )
            {
                if (valorConfig.Get()  == valorConfig.Get() )
                    std::cout << "Los ficheros son consistentes [ADMIN.oooooohhhhhhhhhHHHHH!!!!] " << valorConfig.Get() << " == " << valorConfig2.Get() << std::endl;
                else
                {
                    std::cout << "REVISAR!!! Los ficheros no son consistentes [ADMIN.oooooohhhhhhhhhHHHHH!!!!] " << valorConfig.Get() << " != " << valorConfig2.Get() << std::endl;
                    return -27;
                }
            }
            else
            {
                if (valorConfig.HasValue() != valorConfig2.HasValue() )
                {
                    std::cout << "REVISAR!!! Los ficheros no son consistentes [ADMIN.oooooohhhhhhhhhHHHHH!!!!] " << valorConfig.HasValue() << " distinto HasValue() " << valorConfig2.HasValue() << std::endl;
                    return -28;
                }
                else
                {
                    std::cout << "REVISAR!!! El funcionamiento no es el esperado ya que no se ha creado [ADMIN.oooooohhhhhhhhhHHHHH!!!!] pero no lanza excepción"<< std::endl;
                    return -29;
                }
            }
            std::cout << "************************************************************************************" << std::endl << std::endl;
        }
        catch(const mtk::Alarm& alarma)
        {
            std::list<mtk::BaseAlarm>::const_iterator it = alarma.stackAlarms.begin();
            bool encontrado = false;

            while (it != alarma.stackAlarms.end())
            {
                if ((*it).message == "Cannot write a property on a node [ADMIN] ")
                {
                    encontrado = true;
                    std::cout << "No esta permitido escribir un valor en un nodo: " << std::endl;
                    std::cout << "__NR__:  " << MTK_SS(alarma)  << std::endl;
                }
                it ++;
            }
            if (!encontrado)
            {
                std::cout << "REVISAR!!! Alarma: " << MTK_SS(alarma) << std::endl;
                return -30;
            }
        }
        catch (std::exception& e)
        {
            std::cout << "REVISAR!!! Excepción: " << e.what() << std::endl;
            return -31;
        }
        catch (...)
        {
            std::cout << "REVISAR!!!"<< std::endl;
            return -32;
        }


        std::cout << "************************************************************************************" << std::endl;
        std::cout << "Comprobamos todo el fichero" << std::endl;
        if (!CheckNodes(config, configAux, ""))
        {
            std::cout << "REVISAR!!! Los ficheros no son consistentes" << std::endl;
            return -33;
        }
        else
            std::cout << "Los ficheros son consistentes" << std::endl;
        std::cout << "************************************************************************************" << std::endl << std::endl;



        try
        {
            std::cout << "************************************************************************************" << std::endl;
            std::cout << "Vamos a intentar crear un identificador con símbolos no permitidos:" << std::endl;
            //  no se puede escribir un un identificador con símbolos no permitidos  (lanzaría una excepción)
            config.Create ("ADMIN.aaaa íá=()", "NOooooop");
            config.SaveToFile("config_saved.cfg");
            valorConfig = config.GetValue("ADMIN.aaaa íá=()");
            valorConfig2 = configAux.GetValue("ADMIN.aaaa áí=()");
            if (valorConfig.HasValue() && valorConfig2.HasValue() )
            {
                if (valorConfig.Get()  == valorConfig.Get() )
                    std::cout << "Los ficheros son consistentes [ADMIN.aaaa íá=()] " << valorConfig.Get() << " == " << valorConfig2.Get() << std::endl;
                else
                {
                    std::cout << "REVISAR!!! Los ficheros no son consistentes [ADMIN.aaaa íá=()] " << valorConfig.Get() << " != " << valorConfig2.Get() << std::endl;
                    return -34;
                }
            }
            else
            {
                if (valorConfig.HasValue() != valorConfig2.HasValue() )
                {
                    std::cout << "REVISAR!!! Los ficheros no son consistentes [ADMIN.aaaa íá=()] " << valorConfig.HasValue() << " distinto HasValue() " << valorConfig2.HasValue() << std::endl;
                    return -35;
                }
                else
                {
                    std::cout << "REVISAR!!! El funcionamiento no es el esperado ya que no se ha creado [ADMIN.aaaa íá=()] pero no lanza excepción"<< std::endl;
                    return -36;
                }
            }
            std::cout << "************************************************************************************" << std::endl << std::endl;
        }
        catch(const mtk::Alarm& alarma)
        {
            std::list<mtk::BaseAlarm>::const_iterator it = alarma.stackAlarms.begin();
            if (it != alarma.stackAlarms.end())
            {
                if ((*it).message == "invalid id ADMIN.aaaa íá=()")
                {
                    std::cout << "No esta permitido crear un identificador con símbolos no permitidos: " << std::endl;
                    std::cout << "__NR__:  " << MTK_SS(alarma)  << std::endl;
                }
                else
                {
                    std::cout << "REVISAR!!! Alarma: " << MTK_SS(alarma) << std::endl;
                    return -37;
                }

            }
        }
        catch (std::exception& e)
        {
            std::cout << "REVISAR!!! Excepción: " << e.what() << std::endl;
            return -38;
        }
        catch (...)
        {
            std::cout << "REVISAR!!!" << std::endl;
            return -39;
        }


        std::cout << "************************************************************************************" << std::endl;
        std::cout << "Vamos a coger una propiedad con variables:" << std::endl;
        try
        {
            valorConfig = config.GetValue("ADMIN.PR1.varmercado");
            if (valorConfig.HasValue())
            {
                std::cout << "Valor de la variable varmercado:" << valorConfig.Get() << std::endl;
                valorConfig2 = config.GetValue("ADMIN.MarketConVariable");
                if (valorConfig2.HasValue())
                {
                    std::cout << "MarketConVariable: " << valorConfig2.Get() << std::endl;
                }
                else
                {
                    std::cout << "REVISAR ADMIN.MarketConVariable no tiene valor" << std::endl;
                    return -40;
                }
            }
            else
            {
                std::cout << "REVISAR La variable ADMIN.PR1.varmercado no tiene valor" << std::endl;
                return -41;
            }
            std::cout << "************************************************************************************" << std::endl;

        }
        catch(const mtk::Alarm& alarma)
        {
            std::cout << "REVISAR!!! Alarma: " << MTK_SS(alarma) << std::endl;
            return -42;
        }
        catch (std::exception& e)
        {
            std::cout << "REVISAR!!! Excepción: " << e.what() << std::endl;
            return -43;
        }
        catch (...)
        {
            std::cout << "REVISAR!!!" << std::endl;
            return -44;
        }



        std::cout << "************************************************************************************" << std::endl;
        std::cout << "Vamos a coger una propiedad con variable que es la misma propiedad (recursivo)" << std::endl;
        try
        {
            valorConfig = config.GetValue("SECT1.PROP1");
            if (valorConfig.HasValue())
            {
                std::cout << "Valor de la variable SECT1.PROP1:" << valorConfig.Get() << std::endl;
                valorConfig2 = config.GetValue("SECT1.PROP1");
                if (valorConfig2.HasValue())
                {
                    std::cout << "SECT1.PROP1: " << valorConfig2.Get() << std::endl;
                }
                else
                {
                    std::cout << "REVISAR SECT1.PROP1 no tiene valor" << std::endl;
                    return -45;
                }
            }
            else
            {
                std::cout << "REVISAR La variable SECT1.PROP1 no tiene valor" << std::endl;
                return -46;
            }
            std::cout << "************************************************************************************" << std::endl;

        }
        catch(const mtk::Alarm& alarma)
        {
            std::list<mtk::BaseAlarm>::const_iterator it = alarma.stackAlarms.begin();
            if (it != alarma.stackAlarms.end())
            {
                if ((*it).message == "too depth recursion (11)  $(SECT1.PROP1)  on file config2.cfg")
                    std::cout << "No permitida recursividad: " << (*it).message << std::endl;
                else
                {
                    std::cout << "REVISAR!!! Alarma: " << MTK_SS(alarma) << std::endl;
                    return -47;
                }

            }
        }
        catch (std::exception& e)
        {
            std::cout << "REVISAR!!! Excepción: " << e.what() << std::endl;
            return -48;
        }
        catch (...)
        {
            std::cout << "REVISAR!!!" << std::endl;
            return -49;
        }


        std::cout << "************************************************************************************" << std::endl;
        std::cout << "Vamos a modificar una lista" << std::endl;
        try
        {
            mtk::Nullable<mtk::list <std::string> > listNode = config.GetList("HOLA.seq");
            mtk::list<std::string>  list;
            if (listNode.HasValue())
                list = listNode.Get();
            list.push_back("ultimo elemento lista");
            list.push_front("primer elemento lista");
            config.ModifList("HOLA.seq", list);
            config.SaveToFile("config_saved.cfg");

        }
        catch(const mtk::Alarm& alarma)
        {
            std::cout << "REVISAR!!! Alarma: " << MTK_SS(alarma) << std::endl;
            return -50;
        }
        catch (std::exception& e)
        {
            std::cout << "REVISAR!!! Excepción: " << e.what() << std::endl;
            return -51;
        }
        catch (...)
        {
            std::cout << "REVISAR!!!" << std::endl;
            return -52;
        }

        std::cout << "************************************************************************************" << std::endl;
        std::cout << "Vamos a modificar una lista dejandola vacia" << std::endl;
        try
        {
            mtk::list<std::string>  list;
            config.ModifList("HOLA.lista", list);
            config.SaveToFile("config_saved.cfg");

        }
        catch(const mtk::Alarm& alarma)
        {
            std::cout << "REVISAR!!! Alarma: " << MTK_SS(alarma) << std::endl;
            return -53;
        }
        catch (std::exception& e)
        {
            std::cout << "REVISAR!!! Excepción: " << e.what() << std::endl;
            return -54;
        }
        catch (...)
        {
            std::cout << "REVISAR!!!" << std::endl;
            return -55;
        }

        std::cout << "************************************************************************************" << std::endl;
        std::cout << "Vamos a insertar un elemento a una lista vacia" << std::endl;
        try
        {
            mtk::Nullable<mtk::list <std::string> > listNode = config.GetList("HOLA.listavaciaono");
            mtk::list<std::string>  list;
            if (listNode.HasValue())
                list = listNode.Get();
            list.push_back("Ahora no estoy vacia");
            config.ModifList("HOLA.listavaciaono", list);
            config.SaveToFile("config_saved.cfg");

        }
        catch(const mtk::Alarm& alarma)
        {
            std::cout << "REVISAR!!! Alarma: " << MTK_SS(alarma) << std::endl;
            return -56;
        }
        catch (std::exception& e)
        {
            std::cout << "REVISAR!!! Excepción: " << e.what() << std::endl;
            return -57;
        }
        catch (...)
        {
            std::cout << "REVISAR!!!" << std::endl;
            return -58;
        }


        std::cout << "************************************************************************************" << std::endl;
        std::cout << "Creamos una lista que no existe" << std::endl;
        try
        {
            mtk::Nullable<mtk::list <std::string> > listNode = config.GetList("HOLA.seq");
            mtk::list<std::string>  list;
            if (listNode.HasValue())
                list = listNode.Get();
            list.push_back("Soy un elemento nuevo");
            config.CreateList("HOLA.listaCopiaDeSeq", list);
            config.SaveToFile("config_saved.cfg");

        }
        catch(const mtk::Alarm& alarma)
        {
            std::cout << "REVISAR!!! Alarma: " << MTK_SS(alarma) << std::endl;
            return -59;
        }
        catch (std::exception& e)
        {
            std::cout << "REVISAR!!! Excepción: " << e.what() << std::endl;
            return -60;
        }
        catch (...)
        {
            std::cout << "REVISAR!!!" << std::endl;
            return -61;
        }

        std::cout << "************************************************************************************" << std::endl;
        std::cout << "ModifOrCreate una lista que no existe" << std::endl;
        try
        {
            mtk::Nullable<mtk::list <std::string> > listNode = config.GetList("HOLA.seq");
            mtk::list<std::string>  list;
            if (listNode.HasValue())
                list = listNode.Get();
            list.push_back("Soy un elemento nuevo mas");
            config.ModifOrCreateList("HOLA.listaCopiaDeSeq", list); //modifica
            config.ModifOrCreateList("HOLA.listaCopia2DeSeq", list); //Crea
            config.SaveToFile("config_saved.cfg");

        }
        catch(const mtk::Alarm& alarma)
        {
            std::cout << "REVISAR!!! Alarma: " << MTK_SS(alarma) << std::endl;
            return -59;
        }
        catch (std::exception& e)
        {
            std::cout << "REVISAR!!! Excepción: " << e.what() << std::endl;
            return -60;
        }
        catch (...)
        {
            std::cout << "REVISAR!!!" << std::endl;
            return -61;
        }



        std::cout << "************************************************************************************" << std::endl;
        std::cout << "Vamos a borrar una lista" << std::endl;
        try
        {
            config.Delete("HOLA.mevanaborrar");
            config.SaveToFile("config_saved.cfg");

        }
        catch(const mtk::Alarm& alarma)
        {
            std::cout << "REVISAR!!! Alarma: " << MTK_SS(alarma) << std::endl;
            return -62;
        }
        catch (std::exception& e)
        {
            std::cout << "REVISAR!!! Excepción: " << e.what() << std::endl;
            return -63;
        }
        catch (...)
        {
            std::cout << "REVISAR!!!" << std::endl;
            return -64;
        }

        std::cout << "ESCRIBIMOS EL FICHERO... "  << std::endl;
        std::cout << config.GetStringConfigFileLines() << std::endl;

        std::cout << "************************************************************************************" << std::endl << std::endl;
        std::cout << "FIN..... " << std::endl;
        std::cout << "************************************************************************************" << std::endl << std::endl;
        
        #include "support/release_on_exit.hpp"
        return 0;
    }
    MTK_CATCH_CALLFUNCION (std::cout<< , "main", "REVISAR!!!")

    #include "support/release_on_exit.hpp"
    return -65;

}



void mtk::AlarmMsg(const mtk::Alarm& al)
{
    std::cout << "ouch...: "  << MTK_SS(al) << std::endl;

}
