#ifndef __mtk_qpid_msg_support__
#define __mtk_qpid_msg_support__

#include <sys/types.h>


#include <qpid/messaging/Message.h>



#define MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(__MSG_TYPE__) \
    namespace mtk {   \
    template<>   \
    inline mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<__MSG_TYPE__> >    \
    create_instance_for_factory (   const mtk::tuple<std::string, std::string, std::string>& key,    \
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



#endif 
 
