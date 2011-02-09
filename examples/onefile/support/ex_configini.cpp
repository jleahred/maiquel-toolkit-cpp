#include <iostream>



#include "support/alarm.h"
#include "support/configini.h"
#include "support/mtk_string.h"




void mtk::AlarmMsg (const mtk::Alarm& error)
{
    std::cout << error.message;
}




int main()
{

    try
    {

        mtk::ConfigINI ci("./testing.ini");
        ci.SetValue   ("section2", "paaaaaa", "ini");
        ci.SetValue   ("section2", "counter", "8");


        {
            //  recogemos un valor
            mtk::Nullable<std::string> value = ci.GetValue("section2", "paaaaaa");
            if (value.HasValue())
                std::cout << std::endl << std::endl << "[section2]" << "paraaaa-> " << value.Get();
            else
                std::cout << std::endl << "no tiene valor";
        }

        //  leemos valor section2->counter
        {
            int counter = 0;
            mtk::Nullable<std::string> value = ci.GetValue("section2", "counter");
            if (value.HasValue())   counter = mtk::s_TRY_stoi(value.Get(), 0)._0;
            //  modificamos un valor
            ci.SetValue("section2", "counter", MTK_SS(++counter));
        }
        {
            //  recogemos la lista de secciones
            std::list<std::string>  sn = ci.GetSectionsNames();
            //  recorremos todas las secciones
            for(auto its = sn.begin(); its != sn.end(); ++its)
            {
                std::cout << std::endl << "_[" << *its << "]_";

                //  recorremos todas las propiedades de la sección *its
                std::list<std::string> properties = ci.GetPropertiesInSection(*its);
                for(auto itp = properties.begin(); itp != properties.end(); ++itp)
                {
                    std::cout << std::endl << *itp << "_=_" << ci.GetValue(*its, *itp).Get();
                }


            }
        }

        {
            //  eliminamos un valor
            mtk::Nullable<std::string> value = ci.GetValue("PRDELETE", "del1");
            if (value.HasValue())
            {
                ci.DeleteValue("PRDELETE", "del1");
                ci.SetValue   ("PRDELETE", "del2", "pr");
            }
            else
            {
                ci.DeleteValue("PRDELETE", "del2");
                ci.SetValue   ("PRDELETE", "del1", "pr");
            }
        }

        #include "support/release_on_exit.hpp"
        return 0;

    }
    catch (const mtk::Alarm& error)
    {
        std::cout << error << std::endl;
        #include "support/release_on_exit.hpp"
        return -1;
    }

}