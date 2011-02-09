#ifndef  __mtk_admin__
#define  __mtk_admin__



#include "components/msg_common.h"


namespace mtk {
      namespace admin {

        inline mtk::msg::sub_request_info   get_request_info (void)
        {
            static int contador;
            return mtk::msg::sub_request_info(    mtk::msg::sub_request_id("sess_id", MTK_SS(contador)),
                                        "CLIENT");
        }
      
      };     //namespace admin {
};  //namespace mtk {


#endif 
