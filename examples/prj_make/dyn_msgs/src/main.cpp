#include <iostream>

#include "components/admin/admin.h"
#include "mtk_qpid/mtk_qpid.h"
#include "support/call_later.h"

#include "msg_dynamic.h"





namespace
{

    const char*   APP_NAME          = "TEST_DYNAMIC_MSG";
    const char*   APP_VER           = "2012-06-28";
    const char*   APP_DESCRIPTION   = "Testing\n"
                                      "";

    const char*   APP_MODIFICATIONS = "           2012-06-28     first version\n";



    void command_hello(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
    {
        response_lines.push_back("hi");
    }


    void register_global_commands (void)
    {
        mtk::admin::register_command("testing",  "hello",     "testing command")->connect(command_hello);
    }


    MTK_ADMIN_REGISTER_GLOBAL_COMMANDS(register_global_commands)
}



void  init_app(const int&);




int main(int argc, char ** argv)
{
    try
    {
        if(argc==1)
            mtk::admin::init("./config.cfg", APP_NAME, APP_VER, APP_DESCRIPTION, APP_MODIFICATIONS);
        else
            mtk::admin::init(argv[1], APP_NAME, APP_VER, APP_DESCRIPTION, APP_MODIFICATIONS);


        MTK_CALL_LATER1S_F(mtk::dtSeconds(1), 0, init_app)


        mtk::start_timer_wait_till_end();


        std::cout << "FIN..... " << std::endl;
        #include "support/release_on_exit.hpp"
        return 0;
    }
    MTK_CATCH_CALLFUNCION (std::cout<< , "main", "nothing more")

    std::cout << "MAL..... " << std::endl;
    #include "support/release_on_exit.hpp"
    return -1;

}



void  send_message(void);
void  subscribe(void);






void  init_app(const int&)
{
    subscribe();
    send_message();
}




void  send_message(void)
{
    //  creating with defined and non optional properties
    testing::dynamic::pub_dynamic__qpid_map  pub_dynamic("product_name", false);

    //  modifying a defined optional property
    pub_dynamic.m_static.num_legs = 3;

    //  adding a non defined property
    pub_dynamic.m_qpid_map["testing_new_dynamic_field"] = 3.1415926535;

    mtk_send_message("testing", pub_dynamic);
}








void  stop(const int&)
{
    mtk::stop_timer();
}





void  on_message_dynamic(const  testing::dynamic::pub_dynamic__qpid_map&  msg)
{
    std::cout << "RECEIVED MESSAGE.................................." << std::endl;
    std::cout << msg << std::endl << std::endl;


    if(msg.m_static.processed == false)
    {
        testing::dynamic::pub_dynamic__qpid_map  new_message(msg);

        //  modifying an static property
        new_message.m_static.processed = true;

        //  modifying a defined field from qpid field, has no effect
        new_message.m_qpid_map["num_legs"] = int16_t(666);       //  you have to write...    new_message.m_static.num_legs = 666;


        //  It's not a good idea, but it's possible to add a field defined on msg using qpid_map
        new_message.m_qpid_map["testing"] = "this field has been added using qpid map";


        //  modifying an dynamic property
        new_message.m_qpid_map["testing_new_dynamic_field"] = 1.4142135623730951;

        //  You cannot modify the field type
        //new_message.m_qpid_map["testing_new_dynamic_field"] = "Hello";

        //  adding a field not defined on message
        new_message.m_qpid_map["testing_new_dynamic_field_NEW"] = "En un lugar de la mancha, de cuyo nombre no quiero acordarme, vivía un hidalgo caballero...";



        mtk_send_message("testing", new_message);
        MTK_CALL_LATER1S_F(mtk::dtSeconds(2), 0, stop)
    }
}


void  on_message_static(const  testing::dynamic::pub_dynamic&  msg)
{
    std::cout << "RECEIVED MESSAGE  STATIC interfaz.................................." << std::endl;
    std::cout << msg << std::endl << std::endl;
}


void  subscribe(void)
{

    //  dynamic subscription
    static  mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<testing::dynamic::pub_dynamic__qpid_map> >               handle;
    MTK_QPID_RECEIVER_CONNECT_F(
                            handle,
                            mtk::admin::get_url("testing"),
                            testing::dynamic::pub_dynamic::get_in_subject(),
                            testing::dynamic::pub_dynamic__qpid_map,
                            on_message_dynamic)

    //  we can also subscribe to static message
    //  static subscription
    static  mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<testing::dynamic::pub_dynamic> >               handle_static;
    MTK_QPID_RECEIVER_CONNECT_F(
                            handle_static,
                            mtk::admin::get_url("testing"),
                            testing::dynamic::pub_dynamic::get_in_subject(),
                            testing::dynamic::pub_dynamic,
                            on_message_static)
}


