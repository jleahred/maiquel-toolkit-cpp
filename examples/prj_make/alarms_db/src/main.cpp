#include <iostream>

#include "components/admin/admin.h"
#include "components/admin/msg_admin.h"
#include "support/call_later.h"
#include "components/request_response.hpp"
#include "components/fb/fbinsert.h"



namespace
{

    const char*   APP_NAME          = "ADM_ALARMS_DB";
    const char*   APP_VER           = "2011-12-23";
    const char*   APP_DESCRIPTION   = "This process save alarms on database\n"
                                      "";

    const char*   APP_MODIFICATIONS = "           2011-04-07     first version\n"
                                      "           2011-12-23     problem closing process on production\n";

}





mtk::CountPtr<mtk::fbInsert> fbi_cli;
void  on_alarm_received_cli(const mtk::admin::msg::pub_alarm&  ar)
{
        mtk::fbInsertParams params;
            params.Add(ar.dateTime_generated);
            params.Add(ar.__internal_warning_control_fields->sent_date_time);
            params.Add(mtk::dtNowLocal());
            params.Add(ar.alarm_id);
            params.Add(ar.process_info.location.broker_code);
            params.Add(ar.subject);
            params.Add(ar.message);
            params.Add(ar.priority);
            params.Add(ar.type);
            params.Add(ar.process_info.location.machine);
            params.Add(ar.process_info.version);
            params.Add(ar.process_info.process_name);
            params.Add(ar.process_info.process_uuid);
            params.Add(ar.code_source);

            //  Request asynchronous write
            fbi_cli->Insert(params);

}

mtk::CountPtr<mtk::fbInsert> fbi_srv;
void  on_alarm_received_srv(const mtk::admin::msg::pub_alarm&  ar)
{
        mtk::fbInsertParams params;
            params.Add(ar.dateTime_generated);
            params.Add(ar.__internal_warning_control_fields->sent_date_time);
            params.Add(mtk::dtNowLocal());
            params.Add(ar.alarm_id);
            params.Add(ar.process_info.location.broker_code);
            params.Add(ar.subject);
            params.Add(ar.message);
            params.Add(ar.priority);
            params.Add(ar.type);
            params.Add(ar.process_info.location.machine);
            params.Add(ar.process_info.version);
            params.Add(ar.process_info.process_name);
            params.Add(ar.process_info.process_uuid);
            params.Add(ar.code_source);

            //  Request asynchronous write
            fbi_srv->Insert(params);

}



int main(int argc, char ** argv)
{
    try
    {
        if(argc==1)
            mtk::admin::init("./config.cfg", APP_NAME, APP_VER, APP_DESCRIPTION, APP_MODIFICATIONS);
        else
            mtk::admin::init(argv[1], APP_NAME, APP_VER, APP_DESCRIPTION, APP_MODIFICATIONS);


        fbi_cli = mtk::make_cptr(new mtk::fbInsert("DB_ALARMS", "INSERT INTO CLI_ALARMS (GEN_TIME, SENT_TIME, REC_TIME, AL_ID, BROKER_CODE, SUBJECT, DESCRIPTION, PRIORITY, AL_TYPE, MACHINE, PROCESS_VERSION, PROCESS_NAME, PROCESS_UUID, SOURCE)"
                    "VALUES ( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? )"));

        fbi_srv = mtk::make_cptr(new mtk::fbInsert("DB_ALARMS", "INSERT INTO SRV_ALARMS (GEN_TIME, SENT_TIME, REC_TIME, AL_ID, BROKER_CODE, SUBJECT, DESCRIPTION, PRIORITY, AL_TYPE, MACHINE, PROCESS_VERSION, PROCESS_NAME, PROCESS_UUID, SOURCE)"
                    "VALUES ( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? )"));


        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::admin::msg::pub_alarm>            > hqpid_alarms_cli;
        MTK_QPID_RECEIVER_CONNECT_F(
                                hqpid_alarms_cli,
                                mtk::admin::get_url("client_admin"),
                                mtk::admin::msg::pub_alarm::get_in_subject("CLI"),
                                mtk::admin::msg::pub_alarm,
                                on_alarm_received_cli)

        mtk::CountPtr< mtk::handle_qpid_exchange_receiverMT<mtk::admin::msg::pub_alarm>            > hqpid_alarms_srv;
        MTK_QPID_RECEIVER_CONNECT_F(
                                hqpid_alarms_srv,
                                mtk::admin::get_url("admin"),
                                mtk::admin::msg::pub_alarm::get_in_subject("SRV"),
                                mtk::admin::msg::pub_alarm,
                                on_alarm_received_srv)


        mtk::start_timer_wait_till_end();


        std::cout << "FIN..... " << std::endl;
        fbi_cli = mtk::CountPtr<mtk::fbInsert>();
        fbi_srv = mtk::CountPtr<mtk::fbInsert>();
        #include "support/release_on_exit.hpp"
        return 0;
    }
    MTK_CATCH_CALLFUNCION (std::cout<< , "main", "nothing more")

    std::cout << "MAL..... " << std::endl;
    #include "support/release_on_exit.hpp"
    return -1;

}
