#ifndef __factory__h
#define __factory__h






#include <map>
#include "support/count_ptr.hpp"
#include "support/date_time.h"
#include "support/exec_max_frec.h"
#include "support/tuples.hpp"
#include "support/mtk_string.h"


namespace mtk{



template<typename TRETURN, typename TKEY>
CountPtr< TRETURN > create_instance_for_factory (const TKEY& key, CountPtr< TRETURN > result=CountPtr< TRETURN >());




template<typename TRETURN, typename TKEY>
inline
CountPtr< TRETURN >
get_from_factory(const TKEY& key, CountPtr< TRETURN > result = CountPtr< TRETURN >())
{
    static std::map< TKEY, CountPtr< TRETURN > > factory_map;

    //CountPtr< TRETURN > result;

    // limpieza no determinista
    MTK_EXEC_MAX_FREC_NO_FIRST_S(dtMinutes(10))
    {
        if (factory_map.size()>2000)
        {
            AlarmMsg  (Alarm(
                        MTK_HERE, "factory",
                        MTK_SS (" too many suscriptions " << factory_map.size()),
                        alPriorError, alTypeNoPermisions));
        }



        typename std::map< TKEY, CountPtr< TRETURN > >::iterator it = factory_map.begin();
        while(it!=factory_map.end())
        {
            if (it->second.isValid()==false)
            {
                typename std::map< TKEY, CountPtr< TRETURN > >::iterator current = it;
                ++it;
                factory_map.erase(current);
                continue;
            }
            ++it;
        }

    }
    MTK_END_EXEC_MAX_FREC


    typename std::map< TKEY, CountPtr< TRETURN > >::iterator it = factory_map.find(key);
    if (it == factory_map.end())//  ||  it->second.isValid()==false)
    {
        result = create_instance_for_factory<TRETURN> (key);

        if(factory_map.find(key) != factory_map.end())
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "factory", MTK_SS("nested factory on " << key), mtk::alPriorError));

        typename std::map< TKEY,  CountPtr< TRETURN > >::iterator itNew =
                factory_map.insert(
                        std::make_pair(key, result))
                                .first;
        itNew->second.DANGEROUS_ThisInstance_NOT_Delete();
    }
    else if (it->second.isValid()==false)
    {
        result = create_instance_for_factory<TRETURN> (key);

        if(factory_map.find(key)->second.isValid() != false)
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "factory", MTK_SS("nested factory on " << key), mtk::alPriorError));

        it->second = result;
        it->second.DANGEROUS_ThisInstance_NOT_Delete();
    }
    else
    {
        result = it->second;
    }
    return result;
}






};  //  namespace mtk{


#endif
