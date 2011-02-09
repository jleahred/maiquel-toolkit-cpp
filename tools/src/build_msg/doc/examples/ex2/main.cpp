#include "test_msg_key.h"

#include "support/list.hpp"
#include "support/map.hpp"
#include "support/misc.h"

#include <fstream>



int main (void)
{

    //  generating  the file  as list
    {
        mtk::list<test::sub_test_key>       list_sub_test_key;
        list_sub_test_key.push_back(test::sub_test_key("et", "mi casa", "telefono", "not invented"));
        list_sub_test_key.push_back(test::sub_test_key("fulano", "su casa", "unkown", "fulano@gmail.com"));
        list_sub_test_key.push_back(test::sub_test_key("mengano", "mengano's house", "unkown", "mengano@gmail"));

        std::ofstream file;
        file.open ("test_db__list.yaml");
        YAML::Emitter out;
        out << list_sub_test_key;
        file << out.c_str();
        file.close();
    }


    //  loading the file into a map
    {
        //  first, load into a list
        std::ifstream ifile("test_db__list.yaml");
        mtk::map<test::sub_test_key::key_type, test::sub_test_key>       map_loaded;

        YAML::Parser parser(ifile);
        YAML::Node doc;
        parser.GetNextDocument(doc);
        doc >> map_loaded;


        //  print map
        for(auto it = map_loaded.begin(); it!= map_loaded.end(); ++it)
            std::cout <<  it->second  << std::endl;




        //  save map (it will save as list)
        std::ofstream ofile;
        ofile.open ("test_db__map.yaml");
        YAML::Emitter out;
        out << map_loaded;
        ofile << out.c_str();
        ofile.close();

    }



    return 0;
}


void mtk::AlarmMsg(const mtk::Alarm& error)
{
    std::cout << error << std::endl;
}
