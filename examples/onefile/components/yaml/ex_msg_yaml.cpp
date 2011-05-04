#include <iostream>
#include "components/msg_common.h"
#include "yaml/yaml.h"




int main(void)
{
    //  create message
    mtk::msg::sub_single_product_code spc("market2", "product2");
    
    
    //  generate yaml
    YAML::Emitter out;
    out << spc;
   
   std::cout << out.c_str() << std::endl;



    //  from yaml generate message
    std::istringstream i(out.c_str());
    YAML::Parser parser(i);
    YAML::Node node;
    parser.GetNextDocument(node);
    mtk::msg::sub_single_product_code spc2(__internal_get_default((mtk::msg::sub_single_product_code*) 0));
    node >> spc2;
    std::cout << spc2 << std::endl;
    

   return 0;
}
 
