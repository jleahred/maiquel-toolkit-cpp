#ifndef mtk_asynch_signal__h
#define mtk_asynch_signal__h


//   as  SignalSlot is not variadic (at the moment), it isn't either


#include "support/signalslot.hpp"
#include "support/exec_max_frec.h"
#include "support/timer.h"
#include "support/list.hpp"




namespace  mtk
{



template    <       typename TP0=null_type,
                    typename TP1=null_type,
                    typename TP2=null_type,
                    typename TP3=null_type,
                    typename TP4=null_type
            >
class async_signal_last;





template    <       typename TP0=null_type,
                    typename TP1=null_type,
                    typename TP2=null_type,
                    typename TP3=null_type,
                    typename TP4=null_type
            >
class async_signal_all;



template    <       typename TP0=null_type,
                    typename TP1=null_type,
                    typename TP2=null_type,
                    typename TP3=null_type,
                    typename TP4=null_type
            >
class async_signal_inmediate;










////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//      async_signal_last
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <>
class async_signal_last
        <null_type, null_type, null_type, null_type, null_type>
        :   public SignalReceptor//,public non_copyable (implicit)
{
public:

    mtk::Signal<>       signal;

    async_signal_last(const mtk::dtTimeQuantity&   _max_frec)
    :  pending_send(false), max_frec(_max_frec)
    {
        if(max_frec < mtk::dtMilliseconds(15))
        {   MTK_TIMER_1C(on_timer);     }
        else if(max_frec < mtk::dtMilliseconds(150))
        {   MTK_TIMER_1D(on_timer);     }
        else
        {   MTK_TIMER_1S(on_timer);     }
    }

    void    emit (void)
    {
        pending_send = true;
        on_timer();
    }


private:
    bool                        pending_send;
    const mtk::dtTimeQuantity   max_frec;

    void    on_timer(void)
    {
        MTK_EXEC_MAX_FREC_NO_FIRST(max_frec)
            if(pending_send)
            {
                pending_send = false;
                signal.emit();
            }
        MTK_END_EXEC_MAX_FREC
    }
};






template <typename TP0>
class async_signal_last
        <TP0, null_type, null_type, null_type, null_type>
        :   public SignalReceptor//,public non_copyable (implicit)
{
public:

    mtk::Signal<TP0>       signal;

    async_signal_last(const mtk::dtTimeQuantity&   _max_frec)
    :  pending_send(false), params2send(0), max_frec(_max_frec)
    {
        if(max_frec < mtk::dtMilliseconds(15))
        {   MTK_TIMER_1C(on_timer);     }
        else if(max_frec < mtk::dtMilliseconds(150))
        {   MTK_TIMER_1D(on_timer);     }
        else
        {   MTK_TIMER_1S(on_timer);     }
    }
    ~async_signal_last(void)
    {
        if(params2send != 0)
            delete params2send;
        params2send = 0;
    }

    void    emit(TP0 value0)
    {
        if(params2send == 0)
            params2send = new t_tuple2send(value0);
        else
            *params2send = mtk::make_tuple(value0);

        pending_send = true;
        on_timer();
    }


private:
    typedef  mtk::tuple<    typename mtk::remove_const_and_reference<TP0>::type>     t_tuple2send;

    bool                            pending_send;
    t_tuple2send                    *params2send;
    const mtk::dtTimeQuantity       max_frec;

    void    on_timer(void)
    {
        MTK_EXEC_MAX_FREC_NO_FIRST(max_frec)
            if(pending_send)
            {
                pending_send = false;
                signal.emit(params2send->_0);
            }
        MTK_END_EXEC_MAX_FREC
    }
};





template <typename TP0, typename TP1>
class async_signal_last
        <TP0, TP1, null_type, null_type, null_type>
        :   public SignalReceptor//,public non_copyable (implicit)
{
public:

    mtk::Signal<TP0, TP1>       signal;

    async_signal_last(const mtk::dtTimeQuantity&   _max_frec)
    :  pending_send(false), params2send(0), max_frec(_max_frec)
    {
        if(max_frec < mtk::dtMilliseconds(15))
        {   MTK_TIMER_1C(on_timer);     }
        else if(max_frec < mtk::dtMilliseconds(150))
        {   MTK_TIMER_1D(on_timer);     }
        else
        {   MTK_TIMER_1S(on_timer);     }
    }

    void    emit(TP0 value0, TP1 value1)
    {
        if(params2send == 0)
            params2send = new t_tuple2send(value0, value1);
        else
            *params2send = t_tuple2send(value0, value1);

        pending_send = true;
        on_timer();
    }


private:
    typedef  mtk::tuple<    typename mtk::remove_const_and_reference<TP0>::type,
                            typename mtk::remove_const_and_reference<TP1>::type>   t_tuple2send;

    bool                                            pending_send;
    t_tuple2send                                    *params2send;
    const mtk::dtTimeQuantity                       max_frec;

    void    on_timer(void)
    {
        MTK_EXEC_MAX_FREC_NO_FIRST(max_frec)
            if(pending_send)
            {
                pending_send = false;
                signal.emit(params2send->_0, params2send->_1);
            }
        MTK_END_EXEC_MAX_FREC
    }
};






template <typename TP0, typename TP1, typename TP2>
class async_signal_last
        <TP0, TP1, TP2, null_type, null_type>
        :   public SignalReceptor//,public non_copyable (implicit)
{
public:

    mtk::Signal<TP0, TP1, TP2>       signal;

    async_signal_last(mtk::Signal<TP0, TP1, TP2>&  _input_signal, const mtk::dtTimeQuantity&   _max_frec)
    :  pending_send(false), params2send(0), max_frec(_max_frec)
    {
        if(max_frec < mtk::dtMilliseconds(15))
        {   MTK_TIMER_1C(on_timer);     }
        else if(max_frec < mtk::dtMilliseconds(150))
        {   MTK_TIMER_1D(on_timer);     }
        else
        {   MTK_TIMER_1S(on_timer);     }
    }

    void    emit(TP0 value0, TP1 value1, TP2 value2)
    {
        if(params2send == 0)
            params2send = new t_tuple2send(value0, value1, value2);
        else
            *params2send = mtk::make_tuple(value0, value1, value2);

        pending_send = true;
        on_timer();
    }


private:
    typedef  mtk::tuple<    typename mtk::remove_const_and_reference<TP0>::type,
                            typename mtk::remove_const_and_reference<TP1>::type,
                            typename mtk::remove_const_and_reference<TP2>::type>   t_tuple2send;

    bool                                            pending_send;
    t_tuple2send                                    *params2send;
    const mtk::dtTimeQuantity                       max_frec;

    void    on_timer(void)
    {
        MTK_EXEC_MAX_FREC_NO_FIRST(max_frec)
            if(pending_send)
            {
                pending_send = false;
                signal.emit(params2send->_0, params2send->_1, params2send->_2);
            }
        MTK_END_EXEC_MAX_FREC
    }
};


template <typename TP0, typename TP1, typename TP2, typename TP3>
class async_signal_last
        <TP0, TP1, TP2, TP3, null_type>
        :   public SignalReceptor//,public non_copyable (implicit)
{
public:

    mtk::Signal<TP0, TP1, TP2, TP3>       signal;

    async_signal_last(const mtk::dtTimeQuantity&   _max_frec)
    :  pending_send(false), params2send(0), max_frec(_max_frec)
    {
        if(max_frec < mtk::dtMilliseconds(15))
        {   MTK_TIMER_1C(on_timer);     }
        else if(max_frec < mtk::dtMilliseconds(150))
        {   MTK_TIMER_1D(on_timer);     }
        else
        {   MTK_TIMER_1S(on_timer);     }
    }

    void    emit(TP0 value0, TP1 value1, TP2 value2, TP3 value3)
    {
        if(params2send == 0)
            params2send = new t_tuple2send(value0, value1, value2, value3);
        else
            *params2send = mtk::make_tuple(value0, value1, value2, value3);

        pending_send = true;
        on_timer();
    }


private:
    typedef  mtk::tuple<    typename mtk::remove_const_and_reference<TP0>::type,
                            typename mtk::remove_const_and_reference<TP1>::type,
                            typename mtk::remove_const_and_reference<TP2>::type,
                            typename mtk::remove_const_and_reference<TP3>::type>   t_tuple2send;

    bool                                            pending_send;
    t_tuple2send                                    *params2send;
    const mtk::dtTimeQuantity                       max_frec;

    void    on_timer(void)
    {
        MTK_EXEC_MAX_FREC_NO_FIRST(max_frec)
            if(pending_send)
            {
                pending_send = false;
                signal.emit(params2send->_0, params2send->_1, params2send->_2, params2send->_3);
            }
        MTK_END_EXEC_MAX_FREC
    }
};














////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//      async_signal_all
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


template <typename TP0>
class async_signal_all
        <TP0, null_type, null_type, null_type, null_type>
        :   public SignalReceptor//,public non_copyable (implicit)
{
public:

    mtk::Signal<TP0>       signal;

    async_signal_all(const mtk::dtTimeQuantity&   _max_frec, int _max_queued=200)
    :  max_frec(_max_frec), max_queued(_max_queued)
    {
        if(max_frec < mtk::dtMilliseconds(15))
        {   MTK_TIMER_1C(on_timer);     }
        else if(max_frec < mtk::dtMilliseconds(150))
        {   MTK_TIMER_1D(on_timer);     }
        else
        {   MTK_TIMER_1S(on_timer);     }
    }

    void    emit(TP0 value0)
    {
        if(params2send.size() > max_queued)
        {
            MTK_EXEC_MAX_FREC(mtk::dtSeconds(60))
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "on_signal async all", "too many messages queued, ignoring messages", mtk::alPriorError));
            MTK_END_EXEC_MAX_FREC
            return;
        }
        params2send.push_back(t_tuple2send(value0));
        on_timer();
    }


private:
    typedef  mtk::tuple<typename std::remove_reference<TP0>::type>    t_tuple2send;

    mtk::list<t_tuple2send>         params2send;
    const mtk::dtTimeQuantity       max_frec;
    const size_t                    max_queued;

    void    on_timer(void)
    {
        MTK_EXEC_MAX_FREC_NO_FIRST(max_frec)
            if(params2send.size() > 0)
            {
                t_tuple2send  p2send = params2send.front();
                params2send.pop_front();
                signal.emit(p2send._0);
            }
        MTK_END_EXEC_MAX_FREC
    }
};





template <typename TP0, typename TP1>
class async_signal_all
        <TP0, TP1, null_type, null_type, null_type>
        :   public SignalReceptor//,public non_copyable (implicit)
{
public:

    mtk::Signal<TP0, TP1>       signal;

    async_signal_all(const mtk::dtTimeQuantity&   _max_frec, int _max_queued=200)
    :  params2send(0), max_frec(_max_frec), max_queued(_max_queued)
    {
        if(max_frec < mtk::dtMilliseconds(15))
        {   MTK_TIMER_1C(on_timer);     }
        else if(max_frec < mtk::dtMilliseconds(150))
        {   MTK_TIMER_1D(on_timer);     }
        else
        {   MTK_TIMER_1S(on_timer);     }
    }

    void    emit(TP0 value0, TP1 value1)
    {
        if(params2send.size() > max_queued)
        {
            MTK_EXEC_MAX_FREC(mtk::dtSeconds(60))
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "on_signal async all", "too many messages queued, ignoring messages", mtk::alPriorError));
            MTK_END_EXEC_MAX_FREC
            return;
        }
        params2send.push_back(t_tuple2send(value0, value1));
        on_timer();
    }


private:
    typedef  mtk::tuple<    typename std::remove_reference<TP0>::type,
                            typename std::remove_reference<TP1>::type>    t_tuple2send;

    t_tuple2send                                    *params2send;
    const mtk::dtTimeQuantity                       max_frec;
    const size_t                                    max_queued;

    void    on_signal(TP0 value0, TP1 value1)
    {
        if(params2send.size() > max_queued)
        {
            MTK_EXEC_MAX_FREC(mtk::dtSeconds(60))
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "on_signal async all", "too many messages queued, ignoring messages", mtk::alPriorError));
            MTK_END_EXEC_MAX_FREC
            return;
        }
        params2send.push_back(t_tuple2send(value0, value1));
        on_timer();
    }
    void    on_timer(void)
    {
        MTK_EXEC_MAX_FREC_NO_FIRST(max_frec)
            if(params2send.size() > 0)
            {
                t_tuple2send  p2send = params2send.front();
                params2send.pop_front();
                signal.emit(p2send._0, p2send._1);
            }
        MTK_END_EXEC_MAX_FREC
    }
};


template <typename TP0, typename TP1, typename TP2>
class async_signal_all
        <TP0, TP1, TP2, null_type, null_type>
        :   public SignalReceptor//,public non_copyable (implicit)
{
public:

    mtk::Signal<TP0, TP1, TP2>       signal;

    async_signal_all(const mtk::dtTimeQuantity&   _max_frec, int _max_queued=200)
    :  params2send(0), max_frec(_max_frec), max_queued(_max_queued)
    {
        if(max_frec < mtk::dtMilliseconds(15))
        {   MTK_TIMER_1C(on_timer);     }
        else if(max_frec < mtk::dtMilliseconds(150))
        {   MTK_TIMER_1D(on_timer);     }
        else
        {   MTK_TIMER_1S(on_timer);     }
    }

    void    emit(TP0 value0, TP1 value1, TP2 value2)
    {
        if(params2send.size() > max_queued)
        {
            MTK_EXEC_MAX_FREC(mtk::dtSeconds(60))
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "on_signal async all", "too many messages queued, ignoring messages", mtk::alPriorError));
            MTK_END_EXEC_MAX_FREC
            return;
        }
        params2send.push_back(t_tuple2send(value0, value1, value2));
        on_timer();
    }


private:
    typedef  mtk::tuple<    typename std::remove_reference<TP0>::type,
                            typename std::remove_reference<TP1>::type,
                            typename std::remove_reference<TP2>::type>
                    t_tuple2send;

    t_tuple2send                                    *params2send;
    const mtk::dtTimeQuantity                       max_frec;
    const size_t                                    max_queued;

    void    on_timer(void)
    {
        MTK_EXEC_MAX_FREC_NO_FIRST(max_frec)
            if(params2send.size() > 0)
            {
                t_tuple2send  p2send = params2send.front();
                params2send.pop_front();
                signal.emit(p2send._0, p2send._1, p2send._2);
            }
        MTK_END_EXEC_MAX_FREC
    }
};



template <typename TP0, typename TP1, typename TP2, typename TP3>
class async_signal_all
        <TP0, TP1, TP2, TP3, null_type>
        :   public SignalReceptor//,public non_copyable (implicit)
{
public:

    mtk::Signal<TP0, TP1, TP2, TP3>       signal;

    async_signal_all(const mtk::dtTimeQuantity&   _max_frec, int _max_queued=200)
    :  params2send(0), max_frec(_max_frec), max_queued(_max_queued)
    {
        if(max_frec < mtk::dtMilliseconds(15))
        {   MTK_TIMER_1C(on_timer);     }
        else if(max_frec < mtk::dtMilliseconds(150))
        {   MTK_TIMER_1D(on_timer);     }
        else
        {   MTK_TIMER_1S(on_timer);     }
    }

    void    emit(TP0 value0, TP1 value1, TP2 value2, TP3 value3)
    {
        if(params2send.size() > max_queued)
        {
            MTK_EXEC_MAX_FREC(mtk::dtSeconds(60))
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "on_signal async all", "too many messages queued, ignoring messages", mtk::alPriorError));
            MTK_END_EXEC_MAX_FREC
            return;
        }
        params2send.push_back(t_tuple2send(value0, value1, value2, value3));
        on_timer();
    }


private:
    typedef  mtk::tuple<    typename std::remove_reference<TP0>::type,
                            typename std::remove_reference<TP1>::type,
                            typename std::remove_reference<TP2>::type,
                            typename std::remove_reference<TP3>::type>
                    t_tuple2send;

    t_tuple2send                                    *params2send;
    const mtk::dtTimeQuantity                       max_frec;
    const size_t                                    max_queued;

    void    on_timer(void)
    {
        MTK_EXEC_MAX_FREC_NO_FIRST(max_frec)
            if(params2send.size() > 0)
            {
                t_tuple2send  p2send = params2send.front();
                params2send.pop_front();
                signal.emit(p2send._0, p2send._1, p2send._2, p2send._3);
            }
        MTK_END_EXEC_MAX_FREC
    }
};











////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//      async_signal_all_list
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


template <typename INFO, typename TP>
class async_signal_all_list
        :   public SignalReceptor//,public non_copyable (implicit)
{
public:
    mtk::Signal<const INFO&, const mtk::list<TP>& >       signal;

    async_signal_all_list(INFO _info, const mtk::dtTimeQuantity&   _max_frec, int _max_queued=200)
    :  info(_info), max_frec(_max_frec), max_queued(_max_queued)
    {
        if(max_frec < mtk::dtMilliseconds(15))
        {   MTK_TIMER_1C(on_timer);     }
        else if(max_frec < mtk::dtMilliseconds(150))
        {   MTK_TIMER_1D(on_timer);     }
        else
        {   MTK_TIMER_1S(on_timer);     }
    }


    void    emit(const TP& value)
    {
        if(params2send.size() > max_queued)
        {
            MTK_EXEC_MAX_FREC(mtk::dtSeconds(60))
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "on_signal async_signal_all_list", "too many messages queued, ignoring messages", mtk::alPriorError));
            MTK_END_EXEC_MAX_FREC
            return;
        }
        params2send.push_back(value);
        on_timer();
    }


private:
    INFO                                                    info;
    mtk::list<typename std::remove_reference<TP>::type>     params2send;
    const mtk::dtTimeQuantity                               max_frec;
    const size_t                                            max_queued;

    void    on_timer(void)
    {
        MTK_EXEC_MAX_FREC_NO_FIRST(max_frec)
            if(params2send.size() > 0)
            {
                signal.emit(info, params2send);
                params2send.clear();
            }
        MTK_END_EXEC_MAX_FREC
    }
};












////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//      async_signal_inmediate
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


template <>
class async_signal_inmediate
        <null_type, null_type, null_type, null_type, null_type>
        :   public SignalReceptor//,public non_copyable (implicit)
{
public:

    mtk::Signal<>       signal;

    async_signal_inmediate(int _max_queued=200)
    :  max_queued(_max_queued), pending2emit(false)
    {
    }

    void    emit(void)
    {
        if(pending2emit==false)
            Timer::instance()->signal_async_inmediate.connect(this, &async_signal_inmediate<>::on_turn_to_emit);
        if(params2send.size() > max_queued)
        {
            MTK_EXEC_MAX_FREC(mtk::dtSeconds(60))
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "on_signal async all", "too many messages queued, ignoring messages", mtk::alPriorError));
            MTK_END_EXEC_MAX_FREC
            return;
        }
        params2send.push_back(false);
    }

    void    operator()(void)
    {
        emit();
    }


private:
    //typedef  mtk::tuple<typename std::remove_reference<TP0>::type>    t_tuple2send;

    mtk::list<bool>                 params2send;
    const size_t                    max_queued;
    bool                            pending2emit;

    void    on_turn_to_emit(void)
    {
        if(params2send.size() > 0)
        {
            while(params2send.size()>0)
            {
                //t_tuple2send  p2send = params2send.front();
                params2send.pop_front();
                signal.emit();
            }
        }
        //  it is disconnected by caller
        pending2emit = false;
    }
};


template <typename TP0>
class async_signal_inmediate
        <TP0, null_type, null_type, null_type, null_type>
        :   public SignalReceptor//,public non_copyable (implicit)
{
public:

    mtk::Signal<TP0>       signal;

    async_signal_inmediate(int _max_queued=200)
    :  max_queued(_max_queued), pending2emit(false)
    {
    }

    void    emit(TP0 value0)
    {
        if(pending2emit==false)
            Timer::instance()->signal_async_inmediate.connect(this, &async_signal_inmediate<TP0>::on_turn_to_emit);
        if(params2send.size() > max_queued)
        {
            MTK_EXEC_MAX_FREC(mtk::dtSeconds(60))
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "on_signal async all", "too many messages queued, ignoring messages", mtk::alPriorError));
            MTK_END_EXEC_MAX_FREC
            return;
        }
        params2send.push_back(t_tuple2send(value0));
    }

    void    operator()(TP0 value0)
    {
        emit(value0);
    }


private:
    typedef  mtk::tuple<typename std::remove_reference<TP0>::type>    t_tuple2send;

    mtk::list<t_tuple2send>         params2send;
    const size_t                    max_queued;
    bool                            pending2emit;

    void    on_turn_to_emit(void)
    {
        if(params2send.size() > 0)
        {
            while(params2send.size()>0)
            {
                t_tuple2send  p2send = params2send.front();
                params2send.pop_front();
                signal.emit(p2send._0);
            }
        }
        //  it is disconnected by caller
        pending2emit = false;
    }
};


template <typename TP0, typename TP1>
class async_signal_inmediate
        <TP0, TP1, null_type, null_type, null_type>
        :   public SignalReceptor//,public non_copyable (implicit)
{
public:

    mtk::Signal<TP0, TP1>       signal;

    async_signal_inmediate(int _max_queued=200)
    :  max_queued(_max_queued), pending2emit(false)
    {
    }

    void    emit(TP0 value0, TP1 value1)
    {
        if(pending2emit==false)
            Timer::instance()->signal_async_inmediate.connect(this, &async_signal_inmediate<TP0, TP1>::on_turn_to_emit);
        if(params2send.size() > max_queued)
        {
            MTK_EXEC_MAX_FREC(mtk::dtSeconds(60))
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "on_signal async all", "too many messages queued, ignoring messages", mtk::alPriorError));
            MTK_END_EXEC_MAX_FREC
            return;
        }
        params2send.push_back(t_tuple2send(value0, value1));
    }

    void    operator()(TP0 value0, TP1 value1)
    {
        emit(value0, value1);
    }


private:
    typedef  mtk::tuple<    typename std::remove_reference<TP0>::type,
                            typename std::remove_reference<TP1>::type>    t_tuple2send;

    mtk::list<t_tuple2send>         params2send;
    const size_t                    max_queued;
    bool                            pending2emit;

    void    on_turn_to_emit(void)
    {
        if(params2send.size() > 0)
        {
            while(params2send.size()>0)
            {
                t_tuple2send  p2send = params2send.front();
                params2send.pop_front();
                signal.emit(p2send._0, p2send._1);
            }
        }
        //  it is disconnected by caller
        pending2emit = false;
    }
};




};  //  end namespace mtk {


#endif


