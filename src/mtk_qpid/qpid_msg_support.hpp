#ifndef __mtk_qpid_msg_support__
#define __mtk_qpid_msg_support__

#include <sys/types.h>


#include <qpid/messaging/Message.h>



#define MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(__MSG_TYPE__) \
    namespace mtk {   \
    template<>   \
    inline mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<__MSG_TYPE__> >    \
    create_instance_for_factory (   const mtk::tuple<t_qpid_url, t_qpid_address, t_qpid_filter, mtk::t_qpid_exch_recept_conf>& key,    \
                                    mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<__MSG_TYPE__> > result)   \
    {   \
        result = mtk::make_cptr(new mtk::handle_qpid_exchange_receiverMT<__MSG_TYPE__>(key._0, key._1, key._2, key._3));   \
        return result;   \
    }   \
    };



inline qpid::types::Variant::Map   QPID_DESCOMPOSE_FIXED_NUMBER(const mtk::FixedNumber&  fn)
{
    qpid::types::Variant::Map m_fn;
    m_fn["n"] = int32_t(fn.GetIntCode());
    m_fn["d"] = int8_t (fn.GetExt().GetDec());
    m_fn["i"] = int8_t (fn.GetExt().GetInc());
    return  m_fn;
}

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


    /////////////////////////////////
    namespace  msg
    {
        class  raw_string
        {
        public:
            explicit raw_string(){};
            explicit raw_string(const std::string& s)  : string(s){}

            std::string  string;

        };
        //  operators
        inline std::ostream&  operator<< (std::ostream& os, const raw_string&)
        {   return  os << "<raw_string>";    }
        inline YAML::Emitter& operator<< (YAML::Emitter   & os, const raw_string& rs) {  os << rs.string;  return os; }
        inline void           operator>> (const YAML::Node& i ,       raw_string& rs) {  i  >> rs.string;  }
        inline bool operator==(const raw_string& rs1, const raw_string& rs2)  {  return rs1.string == rs2.string;  }



        class  string_utf8  : public  qpid::types::Variant
        {
            //  requested Mario
            //  This is used on dynamic messages to avoid configure utf8 everytime
            //  This is not a type supported on IDL.
            //  All strings on IDL are marked as utf8
        public:
            explicit string_utf8(const std::string& s) : qpid::types::Variant(s)
            {   setEncoding("utf8");  };
        };
    };  //  namespace  msg
    /////////////////////////////////



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



    inline  void merge__keep_destination(qpid::types::Variant::Map&  destination,  const qpid::types::Variant::Map&  source)
    {
        for(auto it_field_source = source.begin(); it_field_source != source.end(); ++it_field_source)
        {
            qpid::types::Variant  ref_field_source = it_field_source->second;
            auto it_field_destination = destination.find(it_field_source->first);
            if(it_field_destination == destination.end())
                destination.insert(std::make_pair(it_field_source->first, it_field_source->second));
            else
            {
                qpid::types::Variant  ref_field_destination = it_field_destination->second;
                if(ref_field_destination.getType()  !=  ref_field_source.getType())
                    throw mtk::Alarm(MTK_HERE, "merge__keep_destination", MTK_SS("type mismach on destination and source fields " << ref_field_destination << "  " << ref_field_source), mtk::alPriorError);

                if(ref_field_destination.getType() == qpid::types::VAR_MAP)
                    merge__keep_destination(ref_field_destination.asMap(), ref_field_source.asMap());
            }

        }
    }

};


#endif

