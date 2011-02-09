#ifndef mtkExecMaxFrec
#define mtkExecMaxFrec

#include <map>
#include "support/date_time.h"
#include "support/nullable.hpp"


//#include <iostream>     //  debug



#define MTK_EXEC_MAX_FREC(___TIMEINTERVAL___)                                           	\
            {                                                                       	\
            static std::map<long, mtk::nullable<mtk::DateTime> > map_lastInformed_l;       \
            if (map_lastInformed_l.find(long(this)) == map_lastInformed_l.end())             \
                map_lastInformed_l[long(this)] =  mtk::make_nullable(mtk::dtNowUTC()- mtk::dtDays(1));   \
            mtk::DateTime lastInformed_l = map_lastInformed_l[long(this)].Get();                           \
            if (lastInformed_l > mtk::dtNowUTC()) {                                    	\
                lastInformed_l =  mtk::dtNowUTC()- mtk::dtDays(1);                        \
                map_lastInformed_l[long(this)] =  lastInformed_l;                            \
            }                                                                           \
            if (mtk::dtNowUTC() - lastInformed_l  >  (___TIMEINTERVAL___) )  {         	\
                lastInformed_l = mtk::dtNowUTC();                                         \
                map_lastInformed_l[long(this)] =  lastInformed_l;

#define MTK_EXEC_MAX_FREC_A(___TIMEINTERVAL___, __A__)                                           	\
            {                                                                       	\
            static std::map<long, mtk::nullable<mtk::DateTime> > map_lastInformed##__A__;       \
            if (map_lastInformed##__A__.find(long(this)) == map_lastInformed##__A__.end())             \
                map_lastInformed##__A__[long(this)] =  mtk::make_nullable(mtk::dtNowUTC()- mtk::dtDays(1));   \
            mtk::DateTime lastInformed##__A__ = map_lastInformed##__A__[long(this)].Get();                           \
            if (lastInformed##__A__ > mtk::dtNowUTC()) {                                    	\
                lastInformed##__A__ =  mtk::dtNowUTC()- mtk::dtDays(1);                        \
                map_lastInformed##__A__[long(this)] =  lastInformed##__A__;                            \
            }                                                                           \
            if (mtk::dtNowUTC() - lastInformed##__A__  >  (___TIMEINTERVAL___) )  {         	\
                lastInformed##__A__ = mtk::dtNowUTC();                                         \
                map_lastInformed##__A__[long(this)] =  lastInformed##__A__;



#define MTK_EXEC_MAX_FREC_NO_FIRST(___TIMEINTERVAL___)                                           	\
            {                                                                       	\
            static std::map<long, mtk::nullable<mtk::DateTime> > map_lastInformed_l;       \
            if (map_lastInformed_l.find(long(this)) == map_lastInformed_l.end())             \
                map_lastInformed_l[long(this)] =  mtk::make_nullable(mtk::dtNowUTC());   \
            mtk::DateTime lastInformed_l = map_lastInformed_l[long(this)].Get();                           \
            if (lastInformed_l > mtk::dtNowUTC()) {                                    	\
                lastInformed_l =  mtk::dtNowUTC()- mtk::dtDays(1);                        \
                map_lastInformed_l[long(this)] =  lastInformed_l;                            \
            }                                                                           \
            if (mtk::dtNowUTC() - lastInformed_l >  (___TIMEINTERVAL___) )  {         	\
                lastInformed_l = mtk::dtNowUTC();                                         \
                map_lastInformed_l[long(this)] =  lastInformed_l;

#define MTK_EXEC_MAX_FREC_NO_FIRST_A(___TIMEINTERVAL___, __A__)                                 	\
            {                                                                       	\
            static std::map<long, mtk::nullable<mtk::DateTime> > map_lastInformed##__A__;       \
            if (map_lastInformed##__A__.find(long(this)) == map_lastInformed##__A__.end())             \
                map_lastInformed##__A__[long(this)] =  mtk::make_nullable(mtk::dtNowUTC());   \
            mtk::DateTime lastInformed##__A__ = map_lastInformed##__A__[long(this)].Get();                           \
            if (lastInformed##__A__ > mtk::dtNowUTC()) {                                    	\
                lastInformed##__A__ =  mtk::dtNowUTC()- mtk::dtDays(1);                        \
                map_lastInformed##__A__[long(this)] =  lastInformed##__A__;                            \
            }                                                                           \
            if (mtk::dtNowUTC() - lastInformed##__A__ >  (___TIMEINTERVAL___) )  {         	\
                lastInformed##__A__ = mtk::dtNowUTC();                                         \
                lastInformed##__A__[long(this)] =  lastInformed##__A__;


//  EJECUCIÓN CON FRECUENCIA MÁXIMA LOCAL
//  PARA FUNCIONES INDEPENDIENTES O MIEMBROS ESTÁTICOS

//  si detecta que la hora se ha movido hacia atrás desde la última referencia
//  resetea lastInformed

#define MTK_EXEC_MAX_FREC_S(___TIMEINTERVAL___)                                           	\
            {                                                                       	\
            static mtk::DateTime lastInformed_l =  mtk::dtNowUTC()- mtk::dtDays(1);       \
            if (lastInformed_l > mtk::dtNowUTC())                                     	\
                lastInformed_l =  mtk::dtNowUTC()- mtk::dtDays(1);                        \
            if (mtk::dtNowUTC() - lastInformed_l >  (___TIMEINTERVAL___) )  {         	\
                lastInformed_l = mtk::dtNowUTC();

#define MTK_EXEC_MAX_FREC_S_A(___TIMEINTERVAL___, __A__)                                           	\
            {                                                                       	\
            static mtk::DateTime lastInformed##__A__ =  mtk::dtNowUTC()- mtk::dtDays(1);       \
            if (lastInformed##__A__ > mtk::dtNowUTC())                                     	\
                lastInformed##__A__ =  mtk::dtNowUTC()- mtk::dtDays(1);                        \
            if (mtk::dtNowUTC() - lastInformed##__A__ >  (___TIMEINTERVAL___) )  {         	\
                lastInformed##__A__ = mtk::dtNowUTC();


#define MTK_ELSE_MTK_EXEC_MAX_FREC  }    else    {


#define MTK_END_EXEC_MAX_FREC  }  }



#define MTK_EXEC_MAX_FREC_NO_FIRST_S(___TIMEINTERVAL___)                                           	\
            {                                                                       	\
            static mtk::DateTime lastInformed_l =  mtk::dtNowUTC();                       \
            if (lastInformed_l > mtk::dtNowUTC())                                     	\
                lastInformed_l =  mtk::dtNowUTC()- mtk::dtDays(1);                        \
            if (mtk::dtNowUTC() - lastInformed_l >  (___TIMEINTERVAL___) )  {         	\
                lastInformed_l = mtk::dtNowUTC();

#define MTK_EXEC_MAX_FREC_NO_FIRST_S_A(___TIMEINTERVAL___, __A__)                                           	\
            {                                                                       	\
            static mtk::DateTime lastInformed##__A__ =  mtk::dtNowUTC();                       \
            if (lastInformed##__A__ > mtk::dtNowUTC())                                     	\
                lastInformed##__A__ =  mtk::dtNowUTC()- mtk::dtDays(1);                        \
            if (mtk::dtNowUTC() - lastInformed##__A__ >  (___TIMEINTERVAL___) )  {         	\
                lastInformed##__A__ = mtk::dtNowUTC();




// ---------------------------------------------------------------------------

//  EJECUCIÓN CON FRECUENCIA MÁXIMA BASADA EN OBJETO (interés para el caso global)


//  Si queremos compartir una frecuencia de ejecución en diferentes puntos del
//  programa, debemos utilizar esta clase
//  NOTE (maiquel#9#): Pte probar

// ---------------------------------------------------------------------------

namespace  mtk {


class emfCheckMaxFrec {
public:

    emfCheckMaxFrec (dtTimeQuantity _intervalCheck);


    bool  Check(void);


private:
    dtTimeQuantity  intervalCheck;
    dtDateTime      previusValidated;

};



template<int SECONDS>
class emfCheckMaxFrecSECONDS : public emfCheckMaxFrec {

public:
    emfCheckMaxFrecSECONDS() : emfCheckMaxFrec(dtSeconds(SECONDS)) {};


};

template<int MILLISECONDS>
class emfCheckMaxFrecMILLISECONDS : public emfCheckMaxFrec {

public:
    emfCheckMaxFrecMILLISECONDS() : emfCheckMaxFrec(dtMilliseconds(MILLISECONDS)) {};


};



#define MTK_EXEC_MAX_FREC_OBJ(___OBJ_CHECK___)                                           	\
            if ((___OBJ_CHECK___).Check())                                              \
            {                                                                       	\


#define MTK_ELSE_MTK_EXEC_MAX_FREC_OBJ  }    else    {


#define MTK_END_EXEC_MAX_FREC_OBJ  }










//---------------------------------------------------------------------------
};      //namespace mtk {

#endif

