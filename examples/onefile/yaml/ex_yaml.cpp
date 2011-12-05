#include "yaml/yaml.h"
#include <iostream>
#include <fstream>


int main()
{
    YAML::Emitter out;
    out << YAML::BeginMap
        << YAML::Key << "ADMIN"                    << YAML::Value
            << YAML::BeginMap
                << YAML::Key << "IdReloj"          << YAML::Value      << "4443"
                << YAML::Key << "ProcessName"      << YAML::Value      << "HOLA_PRUEBA"

                << YAML::Key << "Production"       << YAML::Value      << false
                << YAML::Comment("A partir de aquí, pueden leerse de global (comunes) o quizá deben")
                << YAML::Key << "Market"           << YAML::Value      << YAML::Null
                << YAML::Key << "Daemon"      << YAML::Value      << "128.2.254.100:7500"
                << YAML::Key << "Network"     << YAML::Value      << YAML::Null

                << YAML::Key << "Services"    << YAML::Value
                    << YAML::BeginMap
                        << YAML::Key << "Client"       << YAML::Value      << "03"
                        << YAML::Key << "Server"       << YAML::Value      << "02"
                        << YAML::Key << "Service"      << YAML::Value      << "01"
                        << YAML::Key << "Other"        << YAML::Value      << "07"
                        << YAML::Key << "Pepe"         << YAML::Value      << "09"
                    << YAML::EndMap
            << YAML::EndMap
        << YAML::EndMap;



   std::cout << out.c_str();

   //   escribir en fichero
    std::ofstream ofile;
    ofile.open ("config.yaml");
    ofile << out.c_str();
    ofile.close();



    std::cout << std::endl   << std::endl  << "Probamos a leer algunas propiedades..." << std::endl;

    //  leer el fichero de configuración
    std::ifstream fin("config.yaml");
    YAML::Parser parser(fin);

    YAML::Node doc;
    parser.GetNextDocument(doc);

    std::string idReloj, processName, servicePepe;
    doc["ADMIN"]["IdReloj"] >> idReloj;
    doc["ADMIN"]["ProcessName"] >> processName;
    doc["ADMIN"]["Services"]["Pepe"] >> servicePepe;

    std::cout << idReloj << std::endl;
    std::cout << processName << std::endl;
    std::cout << servicePepe << std::endl;

    #include "support/release_on_exit.hpp"


   return 0;
}
