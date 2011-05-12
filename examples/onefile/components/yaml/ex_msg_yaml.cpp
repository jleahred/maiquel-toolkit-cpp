#include <iostream>
#include "components/msg_common.h"
#include "yaml/yaml.h"




int main(void)
{
    //  create message
    mtk::msg::sub_product_code pc("market2", "product2");
    
    
    //  generate yaml
    YAML::Emitter out;
    out << pc;
   
   std::cout << out.c_str() << std::endl;



    //  from yaml generate message
    std::istringstream i(out.c_str());
    YAML::Parser parser(i);
    YAML::Node node;
    parser.GetNextDocument(node);
    mtk::msg::sub_product_code pc2(__internal_get_default((mtk::msg::sub_product_code*) 0));
    node >> pc2;
    std::cout << pc2 << std::endl;
    

   return 0;
}
 
