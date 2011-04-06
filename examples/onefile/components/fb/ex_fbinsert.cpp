#include <iostream>


#include "components/fb/fbinsert.h"



#include "components/admin/admin.h"
#include "components/admin/msg_admin.h"
#include "support/call_later.h"
#include "components/request_response.hpp"




namespace
{

    const char*   APP_NAME          = "ex_fbinsert";
    const char*   APP_VER           = "2011-04-05";
    const char*   APP_DESCRIPTION   = "small example of fbinsert component";
    const char*   APP_MODIFICATIONS = "example, no modifications info";
    
    
}





void stop(const int&)
{
    mtk::stop_timer();
}





int main(int /*argc*/, char ** /*argv*/)
{
    try
    {
        mtk::admin::init("./config.cfg", APP_NAME, APP_VER, APP_DESCRIPTION, APP_MODIFICATIONS);
        

            /*
                INSERT INTO CLI_ALARMS (REC_TIME, SENT_TIME, AL_ID, CLI_CODE, SUBJECT, DESCRIPTION, PRIORITY, AL_TYPE, MACHINE, PROCESS_VERSION, PROCESS_NAME, PROCESS_UUID, SOURCE)
                 VALUES (
                *REC_TIME, 
                *SENT_TIME, 
                *AL_ID, 
                *CLI_CODE, 
                *SUBJECT, 
                *DESCRIPTION, 
                *PRIORITY, 
                *AL_TYPE, 
                *MACHINE, 
                *PROCESS_VERSION, 
                *PROCESS_NAME, 
                *PROCESS_UUID, 
                *SOURCE
                )            */
            mtk::fbInsert fbi("DBPR", "INSERT INTO CLI_ALARMS (REC_TIME, SENT_TIME, AL_ID, CLI_CODE, SUBJECT, DESCRIPTION, PRIORITY, AL_TYPE, MACHINE, PROCESS_VERSION, PROCESS_NAME, PROCESS_UUID, SOURCE)"
                    "VALUES ( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? )");
                    
                    
            mtk::fbInsertParams params;
            params.Add(mtk::dtNowLocal());
            params.Add(mtk::dtNowLocal());
            params.Add(0);
            params.Add("CLI_CODE");
            params.Add("SUBJECT");
            params.Add("DESCRIPTION");
            params.Add(0);
            params.Add(0);
            params.Add("MACHINE");
            params.Add("PROCESS_VERSION");
            params.Add("PROCESS_NAME");
            params.Add("PROCESS_UUID");
            params.Add("SOURCE");
            
            mtk::fbInsertParams params2;
            params2.Add(mtk::dtNowLocal());
            params2.Add(mtk::dtNowLocal());
            params2.Add(0);
            params2.Add("CLI_CODE");
            params2.Add("SUBJECT");
            params2.Add("DESCRIPTION");
            params2.Add(0);
            params2.Add(0);
            params2.Add("MACHINE");
            params2.Add("PROCESS_VERSION");
            params2.Add("PROCESS_NAME");
            params2.Add("PROCESS_UUID");
            params2.Add("SOURCE");


            //  Pedimos escritura asíncrona contenida
            fbi.Insert(params);
            fbi.Insert(params2);


        MTK_CALL_LATER1S_F(mtk::dtSeconds(10), 0, stop);
        
        

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
