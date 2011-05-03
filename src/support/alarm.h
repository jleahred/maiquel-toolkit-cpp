//  Creado                  JLE
//  Modificado: 19/03/08    JLE
//---------------------------------------------------------------------------
#ifndef  mtkAlarmH
#define  mtkAlarmH


#include <string>
#include <sstream>

#include <list>

#include "date_time.h"



namespace mtk {


    
#define __INTERNAL_LOCAL_MTK_SS(__REDIRECT__, ...)          \
    ({      \
        std::ostringstream __oss_mtk_ss__##__VA_ARGS__;      \
        __oss_mtk_ss__ << __REDIRECT__;         \
        __oss_mtk_ss__.str();                   \
    })
    
#define MTK_HERE  __INTERNAL_LOCAL_MTK_SS(__PRETTY_FUNCTION__ << "(" << __FILE__ << ":" << __LINE__ << ")")
    

//---------------------------------------------------------------------------


enum alEnPriority   {
                        alPriorCritic       ,
                        alPriorError        ,
                        alPriorWarning      ,
                        alPriorDebug        ,
                        alPriorStats
                    };


enum alEnType       {
                        alTypeUnknown       ,
                        alTypeNoPermisions  ,
                        alTypeOverflow      ,
                        alTypeRealTime
                    };

YAML::Emitter&  operator<< (YAML::Emitter& o, const alEnPriority& a);
YAML::Emitter&  operator<< (YAML::Emitter& o, const alEnType& a);

void            operator>> (const YAML::Node& o, alEnPriority& a);
void            operator>> (const YAML::Node& o, alEnType& a);





struct BaseAlarm {
    std::string             codeSource      ;
    std::string             subject         ;
    std::string             message         ;
    alEnPriority            priority        ;
    mtk::alEnType           type            ;
    mtk::DateTime           dateTime        ;

    BaseAlarm (
                        const std::string&      _codeSource   ,
                        const std::string&      _subject      ,
                        const std::string&      _message      ,
                        alEnPriority            _priority     ,//=critic
                        alEnType                _type
        )
        :   codeSource(_codeSource),         subject(_subject),
            message(_message),
            priority(_priority),             type(_type),
            dateTime (dtNowLocal())
            {};


    virtual ~BaseAlarm(){};

friend std::ostream& operator<< (std::ostream& os, const BaseAlarm& a);

};



struct Alarm : public BaseAlarm {

    Alarm (
                        const std::string&      _codeSource,
                        const std::string&      _subject,
                        const std::string&      _message,
                        alEnPriority            _priority, //=critic
                        alEnType                _type = alTypeUnknown
        )
        :     BaseAlarm(_codeSource, _subject, _message, _priority, _type)
            , alarmID(++classAlarmId%=2000000000)
            , stackAlarms() {}

        const int   alarmID;

        void Add (const BaseAlarm& prevAlarm) {
            stackAlarms.push_back(prevAlarm);
        };

        void Add (const Alarm& prevAlarm) {
            stackAlarms.push_back(prevAlarm);

            std::list<BaseAlarm>::const_iterator it= prevAlarm.stackAlarms.begin();
            while (it != prevAlarm.stackAlarms.end())
            {
                stackAlarms.push_back(*it);
                ++it;
            }
        };

    std::list<BaseAlarm>  stackAlarms;

friend std::ostream& operator<< (std::ostream& os, const Alarm& a);

private:
    static int  classAlarmId;
};


//---------------------------------------------------------------------------


extern void AlarmMsg (const Alarm& error);


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------



//  rethrow no apila si los mensajes son iguales
#define MTK_CATCH_RETHROW(__SUBJECT__, __DESCRIPTION__)    \
                  catch (mtk::Alarm& __alarm__) {                   \
                    if (__alarm__.subject == __SUBJECT__   &&  __alarm__.message ==(__DESCRIPTION__ +std::string(" alarm")))  \
                        throw __alarm__;  \
                    mtk::Alarm  mtkError(                              \
                                MTK_HERE,                            \
                                __SUBJECT__,                      \
                                __DESCRIPTION__  +std::string(" alarm"), \
                                __alarm__.priority,                      \
                                __alarm__.type                            \
                        );                                              \
                    mtkError.Add(__alarm__);                         \
                    throw (mtkError);                                   \
                } catch (std::exception& e) {                           \
                    throw mtk::Alarm(                                 \
                                MTK_HERE,                            \
                                __SUBJECT__,                      \
                                __DESCRIPTION__  +std::string(" exception ") + e.what(),\
                                mtk::alPriorCritic);                    \
                } catch (...) {                                         \
                    throw mtk::Alarm(                                 \
                                MTK_HERE,                            \
                                __SUBJECT__,                      \
                                __DESCRIPTION__   +std::string(" ..."), \
                                mtk::alPriorCritic);                    \
                }

#define MTK_CATCH_CALLFUNCION(__FUNCTION2CALL__, __SUBJECT__, __DESCRIPTION__)    \
                  catch (const mtk::Alarm& __alarm__) {                   \
                    mtk::Alarm  mtkError(                              \
                                MTK_HERE,                            \
                                __SUBJECT__,                      \
                                __DESCRIPTION__  + std::string(" alarm"),\
                                __alarm__.priority,                      \
                                __alarm__.type                            \
                        );                                              \
                    mtkError.Add(__alarm__);				\
                    __FUNCTION2CALL__ (mtkError);                                   \
                } catch (std::exception& e) {                           \
                    __FUNCTION2CALL__ (mtk::Alarm(                                 \
                                MTK_HERE,                            \
                                __SUBJECT__,                      \
                                __DESCRIPTION__  + std::string(" exception ") + e.what(), \
                                mtk::alPriorCritic));                    \
                } catch (...) {                                         \
                    __FUNCTION2CALL__ (mtk::Alarm(                                 \
                                MTK_HERE,                            \
                                __SUBJECT__,                      \
                                __DESCRIPTION__  + std::string(" exception"),\
                                mtk::alPriorCritic));                    \
                }



};   // end namespace mtk {



#endif
