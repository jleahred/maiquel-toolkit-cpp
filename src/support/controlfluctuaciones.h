#ifndef CONTROLFLUCTUACIONES_H
#define CONTROLFLUCTUACIONES_H



#include "support/exec_max_frec.h"
#include "support/date_time.h"
#include "support/tuples.hpp"
#include "support/alarm.h"
//#include "support/foreach.hpp"
#include "support/mtk_string.h"

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
        if (tq <= dtMilliseconds(40))   return;
        if (tq > maxTime)      maxTime = tq;
        ++totalCounter;
        if      (tq < dtMilliseconds(200))      ++_0_02s_counter;
        else if (tq < dtSeconds(1))             ++_02_1s_counter;
        else if (tq < dtSeconds(5))             ++_1_5s_counter;
        else if (tq < dtSeconds(15))            ++_5_15s_counter;
        else                                    ++_more_15s_counter;
    }
    std::string GetReport(void) const {
        return  MTK_SS(
               "\nmaxTime            :" <<  maxTime
            << "\ntotalCounter       :" <<  totalCounter
            << "\n_0_02s_counter     :" <<  _0_02s_counter
            << "\n_02_1s_counter     :" <<  _02_1s_counter
            << "\n_1_5s_counter      :" <<  _1_5s_counter
            << "\n_5_15s_counter     :" <<  _5_15s_counter
            << "\n_more_15s_counter  :" <<  _more_15s_counter
        );
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


    TimeStats  statFluctsPrev;
    TimeStats  statFlucts5min;


    std::string GetReport(void) const {
        return  "prev..." + statFluctsPrev.GetReport() + "\n" +  "5min..." + statFlucts5min.GetReport();
    }
};


template<typename T>
class ControlFluctuacionesMulti {
    std::map<T , ControlFluctuacionesSingle> mapControlFluctuaciones;

public:
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

    std::string GetReport(void) const {
        std::ostringstream result;

        result << "size:   " << mapControlFluctuaciones.size();

        typename std::map<T , ControlFluctuacionesSingle>::const_iterator it = mapControlFluctuaciones.begin();
        while (it!= mapControlFluctuaciones.end())
        {

            result << std::endl << "[" << it->first << std::string("]\n");
            result << it->second.GetReport();
            ++it;
        }
        return result.str();
    }

};




tuple<bool, Alarm>
CheckAlarmFluctuation(
            tuple<dtTimeQuantity, dtTimeQuantity>   prev_5min_flucts,
            dtTimeQuantity                          errorInterval,
            dtTimeQuantity                          waringInterval,
            std::string                             codOrigen
    );





};   //  end namespace mtk

#endif // CONTROLFLUCTUACIONES_H
