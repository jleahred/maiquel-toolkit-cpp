#include <iostream>

#include "support/alarm.h"
#include "support/factory.hpp"



class database_connection      // <1>
{
public:

    std::string server;
    std::string database;
    std::string user;
    std::string password;

    database_connection(const std::string& _server, const std::string& _database, const std::string& _user, const std::string& _password)
        : server(_server), database(_database), user(_user), password(_password)
    {
        //  connect to the database
        std::cout << "creating a instance... " << server << " " << database << " " << user << " " << password << std::endl;
    }
    ~database_connection()
    { // disconnect database
        std::cout << "deleting instance... " << server << " " << database << " " << user << " " << password << std::endl;
    };

    //db_session  get_session...
};

namespace mtk {     //  <2>
    template<>
    mtk::CountPtr< database_connection > create_instance_for_factory(const mtk::tuple<std::string, std::string, std::string, std::string>& key, mtk::CountPtr<database_connection> result)
    {
        result = mtk::make_cptr(new database_connection(key._0, key._1, key._2, key._3));
        return result;
    }
};



class file_handle // <3>
{
public:
    const std::string file_name;

    file_handle(const std::string& _file_name)
        : file_name (_file_name) { std::cout << "creating " << _file_name << std::endl;}
    ~file_handle() { std::cout << "destroying " << file_name << std::endl; }

};

namespace mtk {     //  <4>
    template<>
    mtk::CountPtr< file_handle > create_instance_for_factory(const std::string& key, mtk::CountPtr<file_handle> result)
    {
        result = mtk::make_cptr(new file_handle(key));
        return result;
    }
};



int main(void)
{
    mtk::CountPtr< database_connection > dbc =  mtk::get_from_factory<database_connection>(mtk::make_tuple(std::string("dbserver"), std::string("db_db"), std::string("me"), std::string("my_password")));

    //  <5>
    mtk::CountPtr< database_connection > dbc2 =  mtk::get_from_factory<database_connection>(mtk::make_tuple(std::string("dbserver"), std::string("db_db"), std::string("me"), std::string("my_password")));
    mtk::CountPtr< database_connection > dbc3 =  mtk::get_from_factory<database_connection>(mtk::make_tuple(std::string("dbserver"), std::string("db_db"), std::string("me"), std::string("my_password")));


    //  <6>
    mtk::CountPtr< file_handle > fh =  mtk::get_from_factory<file_handle>(std::string("file_handler"));

    return 0;
}





void mtk::AlarmMsg(const mtk::Alarm& error)
{
    std::cout << error << std::endl;
}