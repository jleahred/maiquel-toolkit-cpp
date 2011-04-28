#include <iostream>
#include "components/msg_common.h"
#include "yaml/yaml.h"



int main(void)
{
    
    mtk::msg::sub_single_product_code spc("market", "product");
    mtk::msg::sub_product_code p (mtk::msg::sub_sys_product_code(mtk::msg::sub_single_product_code(spc), "ljkkl"), mtk::nullable<mtk::msg::sub_adic_product_code>());
    
   YAML::Emitter out;
   out << p;
   
   std::cout << out.c_str() << std::endl;
   
   return 0;
}
 
