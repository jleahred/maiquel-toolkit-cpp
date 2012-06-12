#include <iostream>
#include <fstream>
#include "mtk_qpid/mtk_qpid.h"
#include "support/timer.h"
#include "support/call_later.h"
#include "support/alarm.h"
#include "components/admin/admin.h"
#include "msg_data.h"
#include "components/gen/msg_email.h"
#include "support/configfile.h"




namespace
{

    const char*   APP_NAME          = "TEST_ROUTES";
    const char*   APP_VER           = "2012-06-08";
    const char*   APP_DESCRIPTION   = "Test qpid routes and links";

    const char*   APP_MODIFICATIONS = "           2012-05-04     first version\n"
                                      "           2012-06-08     sending email if fails, monitoring all finish, autocheck on time\n"
										;



    void command_init_test_routes(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_show_test_routes(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);


    void register_global_commands (void)
    {
        mtk::admin::register_command("tr",  "init_test_routes",     "init test qpid routes and links", true)->connect(command_init_test_routes);
        mtk::admin::register_command("tr",  "show_test_routes",     "show last test routes"                )->connect(command_show_test_routes);
    }


    MTK_ADMIN_REGISTER_GLOBAL_COMMANDS(register_global_commands)
}








mtk::list<tr::sub_route>&   get_list_routes_to_test(void)
{
    static  mtk::list<tr::sub_route>   result;
    return result;
}

mtk::map<tr::sub_ip_names::key_type, tr::sub_ip_names>&   get_map_name_ip(void)
{
    static  mtk::map<tr::sub_ip_names::key_type, tr::sub_ip_names>   result;
    return result;
}


void   load_ip_names(void)
{
    get_map_name_ip().clear();

    try
    {
        std::ifstream file("./data/ip_names.yaml");

        YAML::Parser parser(file);

        YAML::Node doc;
        parser.GetNextDocument(doc);

        doc["ip_names"] >> get_map_name_ip();

        file.close();
    }
    MTK_CATCH_RETHROW("load_ip_names", "error loading ip names from file")
}


void   load_routes_to_test(void)
{
    get_list_routes_to_test().clear();

    try
    {
        std::ifstream file("./data/routes.yaml");

        YAML::Parser parser(file);

        YAML::Node doc;
        parser.GetNextDocument(doc);

        doc["routes"] >> get_list_routes_to_test();

        file.close();
    }
    MTK_CATCH_RETHROW("load_routes_to_test", "error loading routes from file")
}


//void test_generate_ip_names_file(void)
//{
//    get_map_name_ip().insert(std::make_pair("cc", tr::sub_ip_names("dd", "dd")));
//    std::ofstream file("../data/ip_names.yaml", std::ios::out | std::ios::trunc);
//
//        YAML::Emitter out;
//        out  <<  YAML::BeginMap;
//
//        out  << YAML::Key << "version"   <<  YAML::Value << 1;
//
//        out  << YAML::Key << "ip_names"   <<  YAML::Value  <<  get_map_name_ip();
//
//        out <<  YAML::EndMap;
//
//        file << out.c_str();
//        file.close();
//}


namespace  testing_route
{
    mtk::DateTime&  get_start_time(void)
    {
        static  mtk::DateTime data  {mtk::dtNowLocal()};
        return data;
    }

    mtk::tuple<mtk::DateTime, std::string>&  get_result_checked(void)
    {
        static mtk::tuple<mtk::DateTime, std::string>  result = mtk::make_tuple(mtk::dtNowLocal(), std::string("--"));
        return result;
    }

    void  finished_test(bool ok)
    {
        mtk::tuple<mtk::DateTime, std::string>  result =   get_result_checked();
        if(ok)
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "ureport", MTK_SS("OK      time:" << mtk::dtNowLocal() - get_start_time() << "  " <<  result._1), mtk::alPriorDebug));
        else
        {
            std::string  error_desc = MTK_SS("ERROR   time:" << mtk::dtNowLocal() - get_start_time() << "  " <<  result._1);
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "ureport", error_desc, mtk::alPriorError));
            mtk::gen::msg::pub_email  pub_email(mtk::admin::get_config_mandatory_property("TEST_ROUTES.email_to"), "ERROR testing routes", error_desc);
            mtk_send_message("server", pub_email);
        }
    }


    mtk::list<std::string>&   get_detail_tested(void)
    {
        static  mtk::list<std::string>   result;
        return  result;
    }

    tr::sub_route&  get_current_route(void)
    {
        static  tr::sub_route   result("-", "-", "-", "-");
        return  result;
    }

    mtk::CountPtr< mtk::handle_qpid_exchange_receiver>&   get_handle_receptor(void)
    {
        static  mtk::CountPtr< mtk::handle_qpid_exchange_receiver>   result;
        return  result;
    }

    void  test_next_route(void);

    void on_message(const qpid::messaging::Message& message)
    {
        if (message.getContent() != MTK_SS(get_current_route()))
            return;

        get_detail_tested().push_back(MTK_SS(mtk::dtNowLocal() << " ok...          "  << get_current_route() << "  "  <<  message.getSubject() << "  " << message.getContent()));
        test_next_route();
    }

    mtk::t_qpid_url  get_url(const std::string&  url_name)
    {
        auto it = get_map_name_ip().find(url_name);
        if(it == get_map_name_ip().end())
            throw mtk::Alarm(MTK_HERE, "get_url", MTK_SS(url_name << "  NOT FOUND"), mtk::alPriorCritic);
        else
            return mtk::t_qpid_url(MTK_SS("amqp:tcp:" << it->second.ip));
    }

    void  send_message(const int&)
    {
        qpid::messaging::Message message(MTK_SS(get_current_route()));
        message.setSubject(get_current_route().subject);

        auto sender = mtk::get_from_factory< mtk::mtkqpid_sender2 > (mtk::make_tuple(
                                                                get_url(get_current_route().origin),
                                                                mtk::t_qpid_address(get_current_route().qe_name)));
        get_detail_tested().push_back(MTK_SS(mtk::dtNowLocal() <<  " sending...     "  << get_current_route() << "   subject: "  <<  message.getSubject() << "    content: " << message.getContent() << "  ... "  << get_url(get_current_route().origin)));
        sender->qpid_sender().send(message);
    }


    mtk::DateTime&  get_last_sent_message(void)
    {
        static  mtk::DateTime  result = mtk::dtNowLocal();
        return result;
    }

    void  timer_time_out(void)
    {
        if(get_last_sent_message() + mtk::dtSeconds(4) < mtk::dtNowLocal())
        {
            get_result_checked() = mtk::make_tuple(mtk::dtNowLocal(), MTK_SS("FAILED  " << get_current_route()));
            get_handle_receptor() = mtk::CountPtr< mtk::handle_qpid_exchange_receiver>{};
            MTK_TIMER_1SF_STOP(timer_time_out);
            finished_test(false);
        }
    }

    void  test_next_route(void)
    {
        try
        {
            MTK_TIMER_1SF_STOP(timer_time_out);

            if(get_list_routes_to_test().size()  == 0)
            {
                get_result_checked() = mtk::make_tuple(mtk::dtNowLocal(), std::string("OK"));
                finished_test(true);
                return;
            }

            get_current_route() =  get_list_routes_to_test().front();
            get_list_routes_to_test().pop_front();


            get_detail_tested().push_back(MTK_SS(mtk::dtNowLocal() << " testing...     "  << get_current_route()
                                                        << "     ... orig " << get_url(get_current_route().origin)
                                                        << "     ... dest " << get_url(get_current_route().dest)
                                                        ));

            get_detail_tested().push_back(MTK_SS(mtk::dtNowLocal() << " connecting...  "  << get_current_route() << "     ... " << get_url(get_current_route().dest)));

            get_handle_receptor() =  mtk::get_from_factory<mtk::handle_qpid_exchange_receiver>(
                                                                    mtk::make_tuple(
                                                                            get_url(get_current_route().dest),
                                                                            mtk::t_qpid_address(get_current_route().qe_name),
                                                                            mtk::t_qpid_filter(get_current_route().subject)));
            get_handle_receptor()->signalMessage->connect(on_message);
            get_last_sent_message() = mtk::dtNowLocal();

            MTK_TIMER_1SF(timer_time_out);
            MTK_CALL_LATER1S_F(mtk::dtSeconds(1), 0, send_message);
        }
        catch (const mtk::Alarm& __alarm__) {
            get_result_checked() = mtk::make_tuple(mtk::dtNowLocal(), MTK_SS("FAILED  " << get_current_route()));
            get_handle_receptor() = mtk::CountPtr< mtk::handle_qpid_exchange_receiver>{};
            mtk::AlarmMsg(__alarm__);
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "checking routes", __alarm__.message, mtk::alPriorCritic));
            finished_test(false);
        } catch (std::exception& e) {
            get_result_checked() = mtk::make_tuple(mtk::dtNowLocal(), MTK_SS("FAILED  " << get_current_route()));
            get_handle_receptor() = mtk::CountPtr< mtk::handle_qpid_exchange_receiver>{};
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "checking routes", e.what(), mtk::alPriorCritic));
            finished_test(false);
        } catch (...) {
            get_result_checked() = mtk::make_tuple(mtk::dtNowLocal(), MTK_SS("FAILED  " << get_current_route()));
            get_handle_receptor() = mtk::CountPtr< mtk::handle_qpid_exchange_receiver>{};
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "checking routes", "...", mtk::alPriorCritic));
            finished_test(false);
        }
    }
};





void  init_test_routes(const int&)
{
    testing_route::get_start_time() = mtk::dtNowLocal();
    load_ip_names();
    load_routes_to_test();
    testing_route::get_detail_tested().clear();
    testing_route::get_result_checked() = mtk::make_tuple(mtk::dtNowLocal(), std::string("--"));

    testing_route::test_next_route();
}



void check_auto_test_routes(void)
{
    static mtk::dtTimeQuantity  frec2check { mtk::dtMinutes{10} };
    static mtk::dtTimeQuantity  frecmargin { mtk::dtMinutes{1}  };

    MTK_EXEC_MAX_FREC_S(mtk::dtMinutes(10))
        mtk::ConfigFile  config_file("./data/schedule.cfg");
        mtk::Nullable<mtk::list<std::string> >    time_list  = config_file.GetList("TEST_ROUTES.time_execs");
        if(time_list.HasValue() == false)
        {
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "test routes", MTK_SS("check_auto_test_routes  missing   TEST_ROUTES.TIMES_EXEC  in config"), mtk::alPriorError));
            return;
        }

        for(auto it= time_list.Get().begin(); it!= time_list.Get().end(); ++it)
        {
            mtk::tuple<mtk::dtTimeQuantity, bool>  convert  =   mtk::s_TRY_stotq(*it, mtk::dtSeconds(0));
            if(convert._1 == false)
                mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "test routes", MTK_SS("check_auto_test_routes incorrect  time in TEST_ROUTES.TIMES_EXEC  in config  "  << *it), mtk::alPriorError));
            else
            {
                mtk::DateTime  test_on = mtk::dtToday_0Time() + convert._0;
                if(test_on < mtk::dtNowLocal()  &&    mtk::dtNowLocal() - test_on < (frec2check + frecmargin))
                {
                    //  execute test
                    init_test_routes(0);
                    break;
                }
            }
        }

    MTK_END_EXEC_MAX_FREC
}





int main(int argc, char** argv)
{
    try
    {

        if(argc==1)
            mtk::admin::init("./config.cfg", APP_NAME, APP_VER, APP_DESCRIPTION, APP_MODIFICATIONS);
        else
            mtk::admin::init(argv[1], APP_NAME, APP_VER, APP_DESCRIPTION, APP_MODIFICATIONS);



        //MTK_CALL_LATER1S_F(mtk::dtSeconds(1), 0, init_test_routes);
        MTK_TIMER_1SF(check_auto_test_routes)


        mtk::start_timer_wait_till_end();



        #include "support/release_on_exit.hpp"
        return 0;
    }
    MTK_CATCH_CALLFUNCION(std::cout << , "main", "no more")

    #include "support/release_on_exit.hpp"
    return -1;
}



namespace {

void command_init_test_routes(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
{
    init_test_routes(0);
	response_lines.push_back("started test routes.");
	response_lines.push_back("It will require some time.");
	response_lines.push_back("You can check the status with command show_test_routes.");
}

void command_show_test_routes(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
{
	response_lines.push_back(MTK_SS ("testing_route  " << testing_route::get_current_route()));
	response_lines.push_back(MTK_SS ("detail "));

    if(testing_route::get_detail_tested().size()>10)
        response_lines.push_back("...");

    int counter = 0;
    for(auto it = testing_route::get_detail_tested().begin(); it!= testing_route::get_detail_tested().end(); ++it, ++counter)
    {
        if(testing_route::get_detail_tested().size() - counter < 10)
            response_lines.push_back(MTK_SS (*it));
    }
	response_lines.push_back(MTK_SS ("RESULT " << testing_route::get_result_checked()));
}


};
