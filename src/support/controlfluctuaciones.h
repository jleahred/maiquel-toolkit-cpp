#ifndef CONTROLFLUCTUACIONES_H
#define CONTROLFLUCTUACIONES_H



#include "support/exec_max_frec.h"
#include "support/date_time.h"
#include "support/tuples.hpp"
#include "support/alarm.h"
//#include "support/foreach.hpp"
#include "support/mtk_string.h"
#include "support/count_ptr.hpp"
#include "support/list.hpp"

#include <map>
#include <string>
#include <sstream>




namespace mtk {






struct TimeStats {
    dtTimeQuantity  maxTime;
    int             totalCounter;
    int             _0_02s_counter;
    int             _02_1s_counter;
    int             _1_5s_counter;
    int             _5_15s_counter;
    int             _more_15s_counter;

    TimeStats() :
        maxTime (dtSeconds(0)) ,       totalCounter(0)         ,
        _0_02s_counter(0)       ,       _02_1s_counter(0)       ,
        _1_5s_counter(0)        ,       _5_15s_counter(0)       ,
        _more_15s_counter(0)            {};
    void AddTime(const dtTimeQuantity& tq) {
        //if (tq <= dtMilliseconds(40))   return;
        if (tq > maxTime)      maxTime = tq;
        ++totalCounter;
        if      (tq < dtMilliseconds(200))      ++_0_02s_counter;
        else if (tq < dtSeconds(1))             ++_02_1s_counter;
        else if (tq < dtSeconds(5))             ++_1_5s_counter;
        else if (tq < dtSeconds(15))            ++_5_15s_counter;
        else                                    ++_more_15s_counter;
    }
    mtk::list<std::string> GetReport(void) const {
        mtk::list<std::string>  result;
        result.push_back(MTK_SS("        maxTime            :" <<  maxTime));
        result.push_back(MTK_SS("        totalCounter       :" <<  totalCounter));
        result.push_back(MTK_SS("        _0_02s_counter     :" <<  _0_02s_counter));
        result.push_back(MTK_SS("        _02_1s_counter     :" <<  _02_1s_counter));
        result.push_back(MTK_SS("        _1_5s_counter      :" <<  _1_5s_counter));
        result.push_back(MTK_SS("        _5_15s_counter     :" <<  _5_15s_counter));
        result.push_back(MTK_SS("        _more_15s_counter  :" <<  _more_15s_counter));
    
        return result;
    }
};




class ControlFluctuacionesSingle {
        mtk::dtTimeQuantity     previousDiference;
        mtk::dtTimeQuantity     previous5MinDif;
        mtk::DateTime           previousTime;
        mtk::DateTime           previous5MinTime;


public:
    ControlFluctuacionesSingle()
        :
            previousDiference   (mtk::dtMilliseconds(0)),
            previous5MinDif     (mtk::dtMilliseconds(0)),
            previousTime        (mtk::dtNowLocal() - mtk::dtDays(1)),
            previous5MinTime    (mtk::dtNowLocal() - mtk::dtDays(1)) {};

    tuple<dtTimeQuantity, dtTimeQuantity>       //  prevFluct,  5minFluct
    CheckFluctuacion(dtTimeQuantity  tqSender);
    
    tuple<dtTimeQuantity, dtTimeQuantity>       //  prevFluct,  5minFluct
    CheckFluctuacion(DateTime  dtSender)
    {
        static DateTime  init (dtNowLocal());
        return CheckFluctuacion(dtSender - init);
    }


    TimeStats  statFluctsPrev;
    TimeStats  statFlucts5min;


    mtk::list<std::string> GetReport(void) const {
        mtk::list<std::string>  result;
        result.push_back("    prev.....................");
        mtk::list<std::string>  partial_result;
        
        partial_result = statFluctsPrev.GetReport();
        for(mtk::list<std::string>::iterator it=partial_result.begin(); it!=partial_result.end(); ++it)
            result.push_back(*it);
        
        result.push_back("    5min.....................");
        partial_result = statFlucts5min.GetReport();
        for(mtk::list<std::string>::iterator it=partial_result.begin(); it!=partial_result.end(); ++it)
            result.push_back(*it);
    
        return result;
    }
};


template<typename T>
class ControlFluctuacionesMulti {
    std::map<T , ControlFluctuacionesSingle> mapControlFluctuaciones;

public:

    tuple<dtTimeQuantity, dtTimeQuantity>       //  prevFluct,  5minFluct
    CheckFluctuacion(           T               id,
                                DateTime        dtSender)
    {
        static DateTime  init (dtNowLocal());
        return CheckFluctuacion(id, dtSender - init);
    }



    tuple<dtTimeQuantity, dtTimeQuantity>       //  prevFluct,  5minFluct
    CheckFluctuacion(           T               id,
                                dtTimeQuantity  tqSender)
    {
        MTK_EXEC_MAX_FREC(dtMilliseconds(100))
            //  Sólo 20 referencias
            typename std::map< T , ControlFluctuacionesSingle>::iterator itControlFluctuaciones =
                                                mapControlFluctuaciones.find(id);

            if (
                itControlFluctuaciones == mapControlFluctuaciones.end()
                &&
                mapControlFluctuaciones.size() > 20
               )
            {
                    MTK_EXEC_MAX_FREC_A(mtk::dtSeconds(50), A)
                        mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "ControlFluctuacionesMulti", "too many flucts to control", mtk::alPriorError));
                    MTK_END_EXEC_MAX_FREC
                    return make_tuple(dtTimeQuantity(dtSeconds(0)), dtTimeQuantity(dtSeconds(0)));
            }
            else
            {
                    if (itControlFluctuaciones == mapControlFluctuaciones.end())
                    {
                        mapControlFluctuaciones[id] = ControlFluctuacionesSingle();
                        return mapControlFluctuaciones[id].CheckFluctuacion(tqSender);
                    }
                    else
                    {
                        return itControlFluctuaciones->second.CheckFluctuacion(tqSender);
                    }
            }
        MTK_END_EXEC_MAX_FREC
        return make_tuple(dtTimeQuantity(dtSeconds(0)), dtTimeQuantity(dtSeconds(0)));
    }



    ControlFluctuacionesMulti() {};

    size_t size() const  { return  mapControlFluctuaciones.size();  }

    mtk::list<std::string> GetReport(void) const {
        mtk::list<std::string> result;

        result.push_back(MTK_SS("size: " << mapControlFluctuaciones.size()));

        typename std::map<T , ControlFluctuacionesSingle>::const_iterator it = mapControlFluctuaciones.begin();
        while (it!= mapControlFluctuaciones.end())
        {

            result.push_back(MTK_SS("[" << it->first << std::string("]  _______________________")));
            
            mtk::list<std::string>  partial_result = it->second.GetReport();
            for(mtk::list<std::string>::iterator it2=partial_result.begin(); it2!=partial_result.end(); ++it2)
                result.push_back(*it2);
            ++it;
        }
        return result;
    }

};




mtk::CountPtr<mtk::Alarm>
CheckAlarmFluctuation(
            tuple<dtTimeQuantity, dtTimeQuantity>   prev_5min_flucts,
            dtTimeQuantity                          criticInterval,
            dtTimeQuantity                          errorInterval,
            dtTimeQuantity                          waringInterval,
            std::string                             codOrigen
    );





};   //  end namespace mtk

#endif // CONTROLFLUCTUACIONES_H
