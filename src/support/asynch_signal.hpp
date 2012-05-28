#ifndef mtk_asynch_signal__h
#define mtk_asynch_signal__h


//   as  SignalSlot is not variadic (at the moment, 25/05/2012), it isn't either


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
    typedef  async_signal_last  CLASS_NAME;
public:

    mtk::Signal<>       signal;

    async_signal_last(mtk::Signal<>&  _input_signal, const mtk::dtTimeQuantity&   _max_frec)
    :  pending_send(false), max_frec(_max_frec)
    {
        MTK_CONNECT_THIS(_input_signal, on_signal);
        if(max_frec < mtk::dtMilliseconds(15))
        {   MTK_TIMER_1C(on_timer);     }
        else if(max_frec < mtk::dtMilliseconds(150))
        {   MTK_TIMER_1D(on_timer);     }
        else
        {   MTK_TIMER_1S(on_timer);     }
    }


private:
    bool                        pending_send;
    const mtk::dtTimeQuantity   max_frec;

    void    on_signal(void)
    {
        pending_send = true;
        on_timer();
    }
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
    typedef  async_signal_last  CLASS_NAME;

public:

    mtk::Signal<TP0>       signal;

    async_signal_last(mtk::Signal<TP0>&  _input_signal, const mtk::dtTimeQuantity&   _max_frec)
    :  pending_send(false), params2send(0), max_frec(_max_frec)
    {
        MTK_CONNECT_THIS(_input_signal, on_signal);
        if(max_frec < mtk::dtMilliseconds(15))
        {   MTK_TIMER_1C(on_timer);     }
        else if(max_frec < mtk::dtMilliseconds(150))
        {   MTK_TIMER_1D(on_timer);     }
        else
        {   MTK_TIMER_1S(on_timer);     }
    }


private:
    typedef  mtk::tuple<typename std::remove_reference<TP0>::type>    t_tuple2send;

    bool                            pending_send;
    t_tuple2send                    *params2send;
    const mtk::dtTimeQuantity       max_frec;

    void    on_signal(TP0 value0)
    {
        if(params2send == 0)
            params2send = new t_tuple2send(value0);
        else
            *params2send = mtk::make_tuple(value0);

        pending_send = true;
        on_timer();
    }
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
    typedef  async_signal_last  CLASS_NAME;

public:

    mtk::Signal<TP0, TP1>       signal;

    async_signal_last(mtk::Signal<TP0, TP1>&  _input_signal, const mtk::dtTimeQuantity&   _max_frec)
    :  pending_send(false), params2send(0), max_frec(_max_frec)
    {
        MTK_CONNECT_THIS(_input_signal, on_signal);
        if(max_frec < mtk::dtMilliseconds(15))
        {   MTK_TIMER_1C(on_timer);     }
        else if(max_frec < mtk::dtMilliseconds(150))
        {   MTK_TIMER_1D(on_timer);     }
        else
        {   MTK_TIMER_1S(on_timer);     }
    }


private:
    typedef  mtk::tuple<    typename std::remove_reference<TP0>::type,
                            typename std::remove_reference<TP1>::type>    t_tuple2send;

    bool                                            pending_send;
    t_tuple2send                                    *params2send;
    const mtk::dtTimeQuantity                       max_frec;

    void    on_signal(TP0 value0, TP1 value1)
    {
        if(params2send == 0)
            params2send = new t_tuple2send(value0, value1);
        else
            *params2send = mtk::make_tuple(value0, value1);

        pending_send = true;
        on_timer();
    }
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
    typedef  async_signal_last  CLASS_NAME;

public:

    mtk::Signal<TP0, TP1, TP2>       signal;

    async_signal_last(mtk::Signal<TP0, TP1, TP2>&  _input_signal, const mtk::dtTimeQuantity&   _max_frec)
    :  pending_send(false), params2send(0), max_frec(_max_frec)
    {
        MTK_CONNECT_THIS(_input_signal, on_signal);
        if(max_frec < mtk::dtMilliseconds(15))
        {   MTK_TIMER_1C(on_timer);     }
        else if(max_frec < mtk::dtMilliseconds(150))
        {   MTK_TIMER_1D(on_timer);     }
        else
        {   MTK_TIMER_1S(on_timer);     }
    }


private:
    typedef  mtk::tuple<    typename std::remove_reference<TP0>::type,
                            typename std::remove_reference<TP1>::type>,
                            typename std::remove_reference<TP2>::type>
                    t_tuple2send;

    bool                                            pending_send;
    t_tuple2send                                    *params2send;
    const mtk::dtTimeQuantity                       max_frec;

    void    on_signal(TP0 value0, TP1 value1, TP2 value2)
    {
        if(params2send == 0)
            params2send = new t_tuple2send(value0, value1, value2);
        else
            *params2send = mtk::make_tuple(value0, value1, value2);

        pending_send = true;
        on_timer();
    }
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
    typedef  async_signal_last  CLASS_NAME;

public:

    mtk::Signal<TP0, TP1, TP2, TP3>       signal;

    async_signal_last(mtk::Signal<TP0, TP1, TP2, TP3>&  _input_signal, const mtk::dtTimeQuantity&   _max_frec)
    :  pending_send(false), params2send(0), max_frec(_max_frec)
    {
        MTK_CONNECT_THIS(_input_signal, on_signal);
        if(max_frec < mtk::dtMilliseconds(15))
        {   MTK_TIMER_1C(on_timer);     }
        else if(max_frec < mtk::dtMilliseconds(150))
        {   MTK_TIMER_1D(on_timer);     }
        else
        {   MTK_TIMER_1S(on_timer);     }
    }


private:
    typedef  mtk::tuple<    typename std::remove_reference<TP0>::type,
                            typename std::remove_reference<TP1>::type>,
                            typename std::remove_reference<TP2>::type>,
                            typename std::remove_reference<TP3>::type>
                    t_tuple2send;

    bool                                            pending_send;
    t_tuple2send                                    *params2send;
    const mtk::dtTimeQuantity                       max_frec;

    void    on_signal(TP0 value0, TP1 value1, TP2 value2, TP3 value3)
    {
        if(params2send == 0)
            params2send = new t_tuple2send(value0, value1, value2, value3);
        else
            *params2send = mtk::make_tuple(value0, value1, value2, value3);

        pending_send = true;
        on_timer();
    }
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



template <typename TP0, typename TP1, typename TP2, typename TP3, typename TP4>
class async_signal_last
        <TP0, TP1, TP2, TP3, TP4>
        :   public SignalReceptor//,public non_copyable (implicit)
{
    typedef  async_signal_last  CLASS_NAME;

public:

    mtk::Signal<TP0, TP1, TP2, TP3, TP4>       signal;

    async_signal_last(mtk::Signal<TP0, TP1, TP2, TP3, TP4>&  _input_signal, const mtk::dtTimeQuantity&   _max_frec)
    :  pending_send(false), params2send(0), max_frec(_max_frec)
    {
        MTK_CONNECT_THIS(_input_signal, on_signal);
        if(max_frec < mtk::dtMilliseconds(15))
        {   MTK_TIMER_1C(on_timer);     }
        else if(max_frec < mtk::dtMilliseconds(150))
        {   MTK_TIMER_1D(on_timer);     }
        else
        {   MTK_TIMER_1S(on_timer);     }
    }


private:
    typedef  mtk::tuple<    typename std::remove_reference<TP0>::type,
                            typename std::remove_reference<TP1>::type>,
                            typename std::remove_reference<TP2>::type>,
                            typename std::remove_reference<TP3>::type>,
                            typename std::remove_reference<TP4>::type>
                    t_tuple2send;

    bool                                            pending_send;
    t_tuple2send                                    *params2send;
    const mtk::dtTimeQuantity                       max_frec;

    void    on_signal(TP0 value0, TP1 value1, TP2 value2, TP3 value3, TP4 value4)
    {
        if(params2send == 0)
            params2send = new t_tuple2send(value0, value1, value2, value3, value4);
        else
            *params2send = mtk::make_tuple(value0, value1, value2, value3, value4);

        pending_send = true;
        on_timer();
    }
    void    on_timer(void)
    {
        MTK_EXEC_MAX_FREC_NO_FIRST(max_frec)
            if(pending_send)
            {
                pending_send = false;
                signal.emit(params2send->_0, params2send->_1, params2send->_2, params2send->_3, params2send->_4);
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
    typedef  async_signal_all  CLASS_NAME;

public:

    mtk::Signal<TP0>       signal;

    async_signal_all(mtk::Signal<TP0>&  _input_signal, const mtk::dtTimeQuantity&   _max_frec, int _max_queued=200)
    :  max_frec(_max_frec), max_queued(_max_queued)
    {
        MTK_CONNECT_THIS(_input_signal, on_signal);
        if(max_frec < mtk::dtMilliseconds(15))
        {   MTK_TIMER_1C(on_timer);     }
        else if(max_frec < mtk::dtMilliseconds(150))
        {   MTK_TIMER_1D(on_timer);     }
        else
        {   MTK_TIMER_1S(on_timer);     }
    }


private:
    typedef  mtk::tuple<typename std::remove_reference<TP0>::type>    t_tuple2send;

    mtk::list<t_tuple2send>         params2send;
    const mtk::dtTimeQuantity       max_frec;
    const size_t                    max_queued;

    void    on_signal(TP0 value0)
    {
        if(params2send.size() > max_queued)
        {
            MTK_EXEC_MAX_FREC(mtk::dtSeconds(60))
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "on_signal async all", "too many messages queued, next will be ignored", mtk::alPriorError));
            MTK_END_EXEC_MAX_FREC
            return;
        }
        params2send.push_back(t_tuple2send(value0));
        on_timer();
    }
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
    typedef  async_signal_all  CLASS_NAME;

public:

    mtk::Signal<TP0, TP1>       signal;

    async_signal_all(mtk::Signal<TP0, TP1>&  _input_signal, const mtk::dtTimeQuantity&   _max_frec, int _max_queued=200)
    :  params2send(0), max_frec(_max_frec), max_queued(_max_queued)
    {
        MTK_CONNECT_THIS(_input_signal, on_signal);
        if(max_frec < mtk::dtMilliseconds(15))
        {   MTK_TIMER_1C(on_timer);     }
        else if(max_frec < mtk::dtMilliseconds(150))
        {   MTK_TIMER_1D(on_timer);     }
        else
        {   MTK_TIMER_1S(on_timer);     }
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
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "on_signal async all", "too many messages queued, next will be ignored", mtk::alPriorError));
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
    typedef  async_signal_all  CLASS_NAME;

public:

    mtk::Signal<TP0, TP1, TP2>       signal;

    async_signal_all(mtk::Signal<TP0, TP1, TP2>&  _input_signal, const mtk::dtTimeQuantity&   _max_frec, int _max_queued=200)
    :  params2send(0), max_frec(_max_frec), max_queued(_max_queued)
    {
        MTK_CONNECT_THIS(_input_signal, on_signal);
        if(max_frec < mtk::dtMilliseconds(15))
        {   MTK_TIMER_1C(on_timer);     }
        else if(max_frec < mtk::dtMilliseconds(150))
        {   MTK_TIMER_1D(on_timer);     }
        else
        {   MTK_TIMER_1S(on_timer);     }
    }


private:
    typedef  mtk::tuple<    typename std::remove_reference<TP0>::type,
                            typename std::remove_reference<TP1>::type>,
                            typename std::remove_reference<TP2>::type>
                    t_tuple2send;

    t_tuple2send                                    *params2send;
    const mtk::dtTimeQuantity                       max_frec;
    const size_t                                    max_queued;

    void    on_signal(TP0 value0, TP1 value1, TP2 value2)
    {
        if(params2send.size() > max_queued)
        {
            MTK_EXEC_MAX_FREC(mtk::dtSeconds(60))
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "on_signal async all", "too many messages queued, next will be ignored", mtk::alPriorError));
            MTK_END_EXEC_MAX_FREC
            return;
        }
        params2send.push_back(t_tuple2send(value0, value1, value2));
        on_timer();
    }
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
    typedef  async_signal_all  CLASS_NAME;

public:

    mtk::Signal<TP0, TP1, TP2, TP3>       signal;

    async_signal_all(mtk::Signal<TP0, TP1, TP2, TP3>&  _input_signal, const mtk::dtTimeQuantity&   _max_frec, int _max_queued=200)
    :  params2send(0), max_frec(_max_frec), max_queued(_max_queued)
    {
        MTK_CONNECT_THIS(_input_signal, on_signal);
        if(max_frec < mtk::dtMilliseconds(15))
        {   MTK_TIMER_1C(on_timer);     }
        else if(max_frec < mtk::dtMilliseconds(150))
        {   MTK_TIMER_1D(on_timer);     }
        else
        {   MTK_TIMER_1S(on_timer);     }
    }


private:
    typedef  mtk::tuple<    typename std::remove_reference<TP0>::type,
                            typename std::remove_reference<TP1>::type>,
                            typename std::remove_reference<TP2>::type>,
                            typename std::remove_reference<TP3>::type>
                    t_tuple2send;

    t_tuple2send                                    *params2send;
    const mtk::dtTimeQuantity                       max_frec;
    const size_t                                    max_queued;

    void    on_signal(TP0 value0, TP1 value1, TP2 value2, TP3 value3)
    {
        if(params2send.size() > max_queued)
        {
            MTK_EXEC_MAX_FREC(mtk::dtSeconds(60))
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "on_signal async all", "too many messages queued, next will be ignored", mtk::alPriorError));
            MTK_END_EXEC_MAX_FREC
            return;
        }
        params2send.push_back(t_tuple2send(value0, value1, value2, value3));
        on_timer();
    }
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


template <typename TP0, typename TP1, typename TP2, typename TP3, typename TP4>
class async_signal_all
        <TP0, TP1, TP2, TP3, TP4>
        :   public SignalReceptor//,public non_copyable (implicit)
{
    typedef  async_signal_all  CLASS_NAME;

public:

    mtk::Signal<TP0, TP1, TP2, TP3, TP4>       signal;

    async_signal_all(mtk::Signal<TP0, TP1, TP2, TP3, TP4>&  _input_signal, const mtk::dtTimeQuantity&   _max_frec, int _max_queued=200)
    :  params2send(0), max_frec(_max_frec), max_queued(_max_queued)
    {
        MTK_CONNECT_THIS(_input_signal, on_signal);
        if(max_frec < mtk::dtMilliseconds(15))
        {   MTK_TIMER_1C(on_timer);     }
        else if(max_frec < mtk::dtMilliseconds(150))
        {   MTK_TIMER_1D(on_timer);     }
        else
        {   MTK_TIMER_1S(on_timer);     }
    }


private:
    typedef  mtk::tuple<    typename std::remove_reference<TP0>::type,
                            typename std::remove_reference<TP1>::type>,
                            typename std::remove_reference<TP2>::type>,
                            typename std::remove_reference<TP3>::type>,
                            typename std::remove_reference<TP4>::type>
                    t_tuple2send;

    t_tuple2send                                    *params2send;
    const mtk::dtTimeQuantity                       max_frec;
    const size_t                                    max_queued;

    void    on_signal(TP0 value0, TP1 value1, TP2 value2, TP3 value3, TP4 value4)
    {
        if(params2send.size() > max_queued)
        {
            MTK_EXEC_MAX_FREC(mtk::dtSeconds(60))
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "on_signal async all", "too many messages queued, next will be ignored", mtk::alPriorError));
            MTK_END_EXEC_MAX_FREC
            return;
        }
        params2send.push_back(t_tuple2send(value0, value1, value2, value3, value4));
        on_timer();
    }
    void    on_timer(void)
    {
        MTK_EXEC_MAX_FREC_NO_FIRST(max_frec)
            if(params2send.size() > 0)
            {
                t_tuple2send  p2send = params2send.front();
                params2send.pop_front();
                signal.emit(p2send._0, p2send._1, p2send._2, p2send._3, p2send._4);
            }
        MTK_END_EXEC_MAX_FREC
    }
};


};  //  end namespace mtk {


#endif

