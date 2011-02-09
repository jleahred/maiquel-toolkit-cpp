#include "controlfluctuaciones.h"
#include "support/exec_max_frec.h"


#include "support/mtk_string.h"


//#include <iostream>			//	debug



namespace mtk {






tuple<dtTimeQuantity, dtTimeQuantity>
ControlFluctuacionesSingle::CheckFluctuacion(dtTimeQuantity  milisecRefSender)
{
    /*
      we will check 20 flucts maximum per second
    */
    auto  now = mtk::dtNowLocal();
    if(started_current_fluct_check+mtk::dtSeconds(1) > now)
    {
        if(counter_current_fluct_check>20)
            return mtk::make_tuple(mtk::dtTimeQuantity(mtk::dtSeconds(0)), mtk::dtTimeQuantity(mtk::dtSeconds(0)));
        else
            ++counter_current_fluct_check;
    }
    else
    {
        started_current_fluct_check = now;
        counter_current_fluct_check = 0;
    }

    dtTimeQuantity resultFluctPrev(dtSeconds(0));
    dtTimeQuantity resultFluct5min(dtSeconds(0));


    /*
          Si el anterior es de hace más de 1h, no es válido para contrastar

          Sólo se controlan n id diferentes

          Contrastar con el anterior

          Contrastar con otra diferencia muestra mantenida durante 5 minutos

          Si las diferencias con los anteriores es de más de 3 minutos, no sirve
                  probable cambio de día, o diferencia no relevante

          Actualizar anterior y hasta cinco minutos antes

            se comprara con dos muestras anteriores,
            la inmediata anterior, y otra referencia que se cambia cada 5 minutos
            o con cualquier ajuste de "mejora"
        */


        //  ----------------------------------------------------------
        //  inicialización datos
        //  ----------------------------------------------------------
        const mtk::DateTime       currentTime           =   now;
        const mtk::dtTimeQuantity currentDif            =
                                     dtMachineGetTotalMillisecs() //currentRefMillisecs
                                          -
                                     milisecRefSender;

        //  ----------------------------------------------------------
        //  Calculos fluctuaciones
        //  ----------------------------------------------------------
        resultFluctPrev  = currentDif - previousDiference;
        resultFluct5min  = currentDif - previous5MinDif;

        //  Si las fluctuaciones son de más de 5 minutos, no nos valen
        if( abs(resultFluctPrev) > dtMinutes(5) )
        {
            resultFluctPrev = dtSeconds(0);
        }
        if( abs(resultFluct5min) > dtMinutes(5) )
        {
            resultFluct5min  = dtSeconds(0);
        }


        //  si hace más de una hora entre verificaciones, el resultado no es relevante
        if( currentTime - previousTime >= mtk::dtHours(1) ) {
            resultFluctPrev = dtSeconds(0);
            resultFluct5min = dtSeconds(0);
        }

        statFluctsPrev.AddTime(resultFluctPrev);
        statFlucts5min.AddTime(resultFluctPrev);

        //  ----------------------------------------------------------
        //  reajustamos los nuevos valores anteriores
        //  ----------------------------------------------------------
        //  Nueva referencia 5 minutos anterior, sólo cuando la muestra
        //  5 min anterior sea más vieja de 5min o cuando la diferencia
        //  de tiempo entre receptor y emisor es inferior
        if(
            (previous5MinTime + mtk::dtMinutes(5) < currentTime)
            ||
            (currentDif < previous5MinDif)
           )
        {
           previous5MinTime = currentTime;
           previous5MinDif  = currentDif;
        }
        //  el anterior siempre
        previousTime      = currentTime;
        previousDiference = currentDif;




    return make_tuple(resultFluctPrev, resultFluct5min);
};









mtk::CountPtr<mtk::Alarm>
CheckAlarmFluctuation(
            tuple<dtTimeQuantity, dtTimeQuantity>   prev_5min_flucts,
            dtTimeQuantity                          criticInterval,
            dtTimeQuantity                          errorInterval,
            dtTimeQuantity                          waringInterval,
            std::string                             codOrigen
        )
{
    //  fluctuaciones
    std::string tipoFluctuacion;
    dtTimeQuantity maxFluct = dtSeconds(0);

    if (abs(prev_5min_flucts._0) > abs(prev_5min_flucts._1)) {
        maxFluct = prev_5min_flucts._0;     //  fluct previa
        tipoFluctuacion = " (prev)";
    } else {
        maxFluct = prev_5min_flucts._1;     //  fluct 5 minutos
        tipoFluctuacion = " (5min) ";
    }


    dtTimeQuantity absFluct =  maxFluct;
    if (maxFluct < dtMilliseconds(0))   //  negativo
        absFluct = -absFluct;

    if (absFluct > criticInterval)
    {

                return make_cptr (
                        new Alarm (
                            MTK_HERE, codOrigen,
                            MTK_SS("fluctuation  " << maxFluct
                                            <<  " " << tipoFluctuacion),
                            alPriorCritic, alTypeRealTime
                        )
                );

    }
    else if (absFluct > errorInterval)
    {

                return make_cptr (
                        new Alarm (
                            MTK_HERE, codOrigen,
                            MTK_SS("fluctuation  " << maxFluct
                                            <<  " " << tipoFluctuacion),
                            alPriorError, alTypeRealTime
                        )
                );

    }
    else if (absFluct > waringInterval)
    {
                return make_cptr (
                        new Alarm (
                            MTK_HERE, codOrigen,
                            MTK_SS("fluctuation  " << maxFluct
                                                << " " << tipoFluctuacion),
                            alPriorWarning, alTypeRealTime
                        )
                );
    }
    else
                return mtk::CountPtr<mtk::Alarm>();
}








};      //  end namespace mtk
