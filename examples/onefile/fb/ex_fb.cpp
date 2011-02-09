#include <iostream>

#include "fb/ibpp.h"
#include "support/mtk_string.h"


    //  más información en   www.ibpp.com



using namespace std;

int main()
{

    try
    {

        //  ------------------------------------------------------------

        //          L E C T U R A

        //  ------------------------------------------------------------

        try
        {
            IBPP::Database db = IBPP::DatabaseFactory("127.0.0.1", "/home/maiquel/develop/testing/mtk_db/examples.fdb", "SYSDBA", "mtkmtk");
            db->Connect();
            IBPP::Transaction tr = IBPP::TransactionFactory(db);
            tr->Start();

                int  id=0;
                std::string idServidor;
                mtk::nullable<mtk::DateTime> dt;

                IBPP::Statement st = IBPP::StatementFactory(db, tr);
                st->Execute("SELECT FIRST 10 * FROM ALARMS");
                while (st->Fetch())
                {
                    st->Get(1, id);                         //  acceso por índice
                    cout << "id          : " << id << std::endl;

                    st->Get("SOURCE_CODE", idServidor);     //  acceso por nombre
                    cout << "SOURCE_CODE  : " << idServidor << endl;


                    st->Get(st->ColumnNum("DATE_TIME"), dt);   //   acceso por (índice -> nombre)
                    cout << "DATE_TIME  : " << dt.Get() << endl;


                    cout << endl;
                }


            tr->Commit();
            db->Disconnect();
        }
        MTK_CATCH_RETHROW("main", "reading error")
            //  también se pueden hacer lecturas con parámetros






        //  ------------------------------------------------------------

        //          E S C R I T U R A

        //  ------------------------------------------------------------


        try
        {
            IBPP::Database db = IBPP::DatabaseFactory("127.0.0.1", "/home/maiquel/develop/testing/mtk_db/examples.fdb", "SYSDBA", "mtkmtk");
            db->Connect();
            IBPP::Transaction tr = IBPP::TransactionFactory(db);
            tr->Start();

                IBPP::Statement st = IBPP::StatementFactory(db, tr);
                st->Prepare(
                            "INSERT INTO ALARMS (DATE_TIME, SOURCE_CODE, DESCRIPTION)"
                            "VALUES (?, ?, ?)"
               );
               st->Set(1, mtk::dtNowLocal());
               st->Set(2, MTK_SS("sc"<< mtk::dtNowLocal()));
               st->Set(3, MTK_SS("description" << mtk::dtNowLocal()));
               st->Execute();

            tr->Commit();
            db->Disconnect();
        }
        MTK_CATCH_RETHROW("main", "reading error")

        #include "support/release_on_exit.hpp"
        return 0;

    }
    MTK_CATCH_CALLFUNCION(std::cout <<, "main", "error")
    #include "support/release_on_exit.hpp"
    return -1;
}


//---------------------------------------------------------------------------

//  RECEPTOR ALARMAS SALIDA GENERAL

//---------------------------------------------------------------------------

void mtk::AlarmMsg (const Alarm& alarma)
{
        std::cout << "\n\r";
        std::cout << std::endl << "ALARMA SALIDA..." << std::endl ;
        std::cout << alarma << std::endl ;
}