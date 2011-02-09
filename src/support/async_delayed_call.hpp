#ifndef ASYNCDELAYEDCALL_HPP_INCLUDED
#define ASYNCDELAYEDCALL_HPP_INCLUDED




#include "support/timer.h"
#include <queue>

#include "support/exec_max_frec.h"
#include "support/mtk_string.h"


#define MTK_ASYNC_DELAYED_CALL_DI(METHOD_NAME, PARAM_TYPE, QTY, TIME_INTERVAL, MAX_QUEUE_SIZE) \
        mutable std::queue<PARAM_TYPE>   qAsyncDelayed_##METHOD_NAME;       \
        void METHOD_NAME (PARAM_TYPE p)                             \
        {                                                           \
            if(qAsyncDelayed_##METHOD_NAME.size()==0)               \
                MTK_TIMER_1D(__Delayed_##METHOD_NAME);                   \
            if(qAsyncDelayed_##METHOD_NAME.size()<MAX_QUEUE_SIZE)   \
                qAsyncDelayed_##METHOD_NAME.push(p);                \
            else                                                    \
            {                                                       \
                std::string error;                                  \
                error += "queue overflow   method:";                \
                error += #METHOD_NAME;                              \
                error += "   paramType:";                           \
                error += #PARAM_TYPE;                               \
                error += "    qty:";                                \
                error += #QTY;                                      \
                error += "   timeInterval:";                        \
                error += #TIME_INTERVAL;                            \
                error += "    maxQueueSize";                        \
                error += #MAX_QUEUE_SIZE;                           \
                error += " ";                                       \
                AsyncDelayedCall_Overflow(error);                   \
            }                                                       \
        }                                                           \
        void __Delayed_##METHOD_NAME(void)                          \
        {                                                           \
            MTK_EXEC_MAX_FREC(mtk::dtTimeQuantity(TIME_INTERVAL)-mtk::dtMilliseconds(5))\
                std::string  ___methodName(#METHOD_NAME);                   \
                for (int i__ASDC=0; i__ASDC<QTY; ++i__ASDC)                                   \
                {                                                           \
                    try                                                         \
                    {                                                           \
                        if (qAsyncDelayed_##METHOD_NAME.size()==0)              \
                        {                                                       \
                            MTK_TIMER_1D_STOP(__Delayed_##METHOD_NAME);              \
                        }                                                       \
                        else if(qAsyncDelayed_##METHOD_NAME.size()>0)           \
                        {                                                       \
                            PARAM_TYPE p = qAsyncDelayed_##METHOD_NAME.front(); \
                            qAsyncDelayed_##METHOD_NAME.pop();                  \

#define MTK_ASYNC_DELAYED_CALL_END_I                                                \
                        }                                                       \
                    } catch(const mtk::Alarm& alarm) {                         \
                        mtk::AlarmMsg(alarm);                                  \
                    } catch(std::exception& e) {                                              \
                        AlarmMsg(                                              \
                            mtk::Alarm (   ___methodName,                      \
                                MTK_SS("Unkown error ...   ASYNC_DELAYED_CALL_END_I" << e.what()),\
                                mtk::alPriorError                               \
                            )                                                   \
                        );                                                      \
                    } catch(...) {                                              \
                        AlarmMsg(                                              \
                            mtk::Alarm (   ___methodName,                      \
                                std::string("Unkown error ...   ASYNC_DELAYED_CALL_END_I"),\
                                mtk::alPriorError                               \
                            )                                                   \
                        );                                                      \
                    }                                                       \
                }                                                           \
            MTK_END_EXEC_MAX_FREC                                               \
        }









#define MTK_ASYNC_DELAYED_CALL_D(METHOD_NAME, PARAM_TYPE, QTY, TIME_INTERVAL, MAX_QUEUE_SIZE) \
        mutable std::queue<PARAM_TYPE>   qAsyncDelayed_##METHOD_NAME;       \
        void METHOD_NAME (PARAM_TYPE p)                             \
        {                                                           \
            if(qAsyncDelayed_##METHOD_NAME.size()==0)               \
                MTK_TIMER_1D(__Delayed_##METHOD_NAME##QTY##MAX_QUEUE_SIZE);                   \
            if(qAsyncDelayed_##METHOD_NAME.size()<MAX_QUEUE_SIZE)   \
                qAsyncDelayed_##METHOD_NAME.push(p);                \
            else                                                    \
            {                                                       \
                std::string error;                                  \
                error += "queue overflow   method:";                \
                error += #METHOD_NAME;                              \
                error += "   paramType:";                           \
                error += #PARAM_TYPE;                               \
                error += "    qty:";                                \
                error += #QTY;                                      \
                error += "   timeInterval:";                        \
                error += #TIME_INTERVAL;                            \
                error += "    maxQueueSize";                        \
                error += #MAX_QUEUE_SIZE;                           \
                error += " ";                                       \
                AsyncDelayedCall_Overflow(error);                   \
            }                                                       \
        }                                                           \
        void __Delayed_##METHOD_NAME##QTY##MAX_QUEUE_SIZE(void);





#define ASYNC_DELAYED_CALL_I(METHOD_NAME, PARAM_TYPE, QTY, TIME_INTERVAL, MAX_QUEUE_SIZE) \
        __Delayed_##METHOD_NAME##QTY##MAX_QUEUE_SIZE(void)                          \
        {                                                           \
            MTK_EXEC_MAX_FREC(mtk::dtTimeQuantity(TIME_INTERVAL)-mtk::dtMilliseconds(5))\
                std::string  ___methodName(#METHOD_NAME);                   \
                for (int i__ASDC=0; i__ASDC<QTY; ++i__ASDC)                                   \
                {                                                           \
                    try                                                         \
                    {                                                           \
                        if (qAsyncDelayed_##METHOD_NAME.size()==0)              \
                        {                                                       \
                            MTK_TIMER_1D_STOP(__Delayed_##METHOD_NAME##QTY##MAX_QUEUE_SIZE);              \
                        }                                                       \
                        else if(qAsyncDelayed_##METHOD_NAME.size()>0)           \
                        {                                                       \
                            PARAM_TYPE p = qAsyncDelayed_##METHOD_NAME.front(); \
                            qAsyncDelayed_##METHOD_NAME.pop();                  \




#define MTK_ASYNC_DELAYED_CALL_END_I                                        \
                        }                                                       \
                    } catch(const mtk::Alarm& alarm) {                         \
                        mtk::AlarmMsg(alarm);                                  \
                    } catch(std::exception& e) {                                              \
                        AlarmMsg(                                              \
                            mtk::Alarm (   ___methodName,                      \
                                MTK_SS("Unkown error ...   ASYNC_DELAYED_CALL_END_I" << e.what()),\
                                mtk::alPriorError                               \
                            )                                                   \
                        );                                                      \
                    } catch(...) {                                              \
                        AlarmMsg(                                              \
                            mtk::Alarm (   ___methodName,                      \
                                std::string("Unkown error ...   ASYNC_DELAYED_CALL_END_I"),\
                                mtk::alPriorError                               \
                            )                                                   \
                        );                                                      \
                    }                                                       \
                }                                                           \
            MTK_END_EXEC_MAX_FREC                                               \
        }






#endif // ASYNCDELAYEDCALL_HPP_INCLUDED
