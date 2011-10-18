#ifndef __mtk_qpid_msg_support__
#define __mtk_qpid_msg_support__

#include <sys/types.h>


#include <qpid/messaging/Message.h>



#define MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(__MSG_TYPE__) \
    namespace mtk {   \
    template<>   \
    inline mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<__MSG_TYPE__> >    \
    create_instance_for_factory (   const mtk::tuple<t_qpid_url, t_qpid_address, t_qpid_filter>& key,    \
                                    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<__MSG_TYPE__> > result)   \
    {   \
        result = mtk::make_cptr(new mtk::handle_qpid_exchange_receiverMT<__MSG_TYPE__>(key._0, key._1, key._2));   \
        return result;   \
    }   \
    };



#define QPID_DESCOMPOSE_FIXED_NUMBER(__fn__)  \
    ({  \
    qpid::types::Variant::Map m_fn;  \
    m_fn["n"] = int32_t(__fn__.GetIntCode());  \
    m_fn["d"] = int8_t(__fn__.GetExt().GetDec());  \
    m_fn["i"] = int8_t(__fn__.GetExt().GetInc());  \
    m_fn;  \
    });

#define QPID_DESCOMPOSE_FN_EXT(__fnex__)  \
    ({  \
    qpid::types::Variant::Map m_fn;  \
    m_fn["d"] = int8_t(__fnex__.GetDec());  \
    m_fn["i"] = int8_t(__fnex__.GetInc());  \
    m_fn;  \
    });



#define __MTK_QPID_WARP__(class_name, class_type)                       \
    class class_name {                                                  \
        class_type  internal;                                           \
    public:                                                             \
        explicit class_name (class_type value) : internal(value) {};    \
        class_type  WarningDontDoThisGetInternal(void) const  {  return internal;  };    \
        bool operator==(const class_name& c) const                      \
        {       return internal == c.internal;    }                     \
        bool operator!=(const class_name& c) const                      \
        {       return internal != c.internal;    }                     \
        bool operator< (const class_name& c) const                      \
        {       return internal < c.internal;    }                      \
        bool operator> (const class_name& c) const                      \
        {       return internal > c.internal;    }                      \
        bool operator<=(const class_name& c) const                      \
        {       return internal <= c.internal;    }                     \
        bool operator>=(const class_name& c) const                      \
        {       return internal >= c.internal;    }                     \
    };                                                                  \
    inline std::ostream&  operator<< (std::ostream& os, const class_name& o)   \
    {   return  os << o.WarningDontDoThisGetInternal();    }


namespace  mtk
{

    __MTK_QPID_WARP__       (_t_qpid_url                       ,     std::string);
    __MTK_QPID_WARP__       (_t_qpid_address                   ,     std::string);
    __MTK_QPID_WARP__       (_t_qpid_exch_recept_conf          ,     std::string);
    __MTK_QPID_WARP__       (_t_qpid_exch_sender_conf          ,     std::string);
    __MTK_QPID_WARP__       (_t_qpid_filter                    ,     std::string);

    //  ide help
    typedef _t_qpid_url                           t_qpid_url;
    typedef _t_qpid_address                       t_qpid_address;
    typedef _t_qpid_exch_recept_conf              t_qpid_exch_recept_conf;
    typedef _t_qpid_exch_sender_conf              t_qpid_exch_sender_conf;
    typedef _t_qpid_filter                        t_qpid_filter;



    //      on qpid012 it's necessary to configure as this in order to delete the linked queue when receiver or session
    //      get out of scope
    //      This bug is fixed on qpid013  (pending to test)
    static const t_qpid_exch_recept_conf  QUEUE__DEFAULT_RECEPTOR_CONFIG {
                    "{ "
                    "  assert: allways, "
                    //"  create: never, "
                    "  node : "
                    "  { "
                    "    type: topic "
                    "  }, "
                    "  link: "
                    "  { "
                    //"    name: 'testing1" << i << "', "
                    "    durable: false, "
                    "    x-declare: "
                    "    { "
                    "      auto-delete: true, "
                    "      exclusive: True, "
                    "      arguments: "
                    "      { "
                    //"         qpid.last_value_queue_key: 'qpid.subject', "
                    "        'qpid.max_count': 2000, "
                    "        'qpid.max_size': 2000000, "        //  in bytes
                    "        'qpid.policy_type': ring "
                    "      } "
                    "    } "
                    "  } "
                    "} " };

    static const t_qpid_exch_sender_conf   QUEUE__DEFAULT_SENDER_CONFIG   {  "{assert:always, node:{type:topic} }"  };


};


#endif

