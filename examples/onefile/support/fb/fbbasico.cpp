#include <iostream>

#include "fb/ibpp.h"


    //  más información en   www.ibpp.com



using namespace std;

int main()
{


    //  ------------------------------------------------------------

    //          L E C T U R A

    //  ------------------------------------------------------------

    try
    {
        IBPP::Database db = IBPP::DatabaseFactory("128.2.8.44", "MABE", "SYSDBA", "pruebas");
        db->Connect();
        IBPP::Transaction tr = IBPP::TransactionFactory(db);
        tr->Start();

            int  id=0;
            std::string idServidor;
            idt::nullable<idt::DateTime> dt;

            IBPP::Statement st = IBPP::StatementFactory(db, tr);
            st->Execute("SELECT FIRST 10 * FROM EVENTO");
            while (st->Fetch())
            {
                st->Get(1, id);                         //  acceso por índice
                cout << "id          : " << id << std::endl;

                st->Get("ID_SERVIDOR", idServidor);     //  acceso por nombre
                cout << "idservidor  : " << idServidor << endl;


                st->Get(st->ColumnNum("FECHA"), dt);   //   acceso por (índice -> nombre)
                cout << "FECHA  : " << dt.Get() << endl;


                cout << endl;
            }


        tr->Commit();
        db->Disconnect();
    }
    catch (IBPP::Exception& e)
    {
        cout << e.what();
    }
        //  también se pueden hacer lecturas con parámetros






    //  ------------------------------------------------------------

    //          E S C R I T U R A

    //  ------------------------------------------------------------


    try
    {
        IBPP::Database db = IBPP::DatabaseFactory("128.2.8.44", "MABE", "SYSDBA", "pruebas");
        db->Connect();
        IBPP::Transaction tr = IBPP::TransactionFactory(db);
        tr->Start();

            IBPP::Statement st = IBPP::StatementFactory(db, tr);
            st->Prepare(
                "INSERT INTO EVENTO (FECHA, ID_MERCADO, ID_SERVIDOR, ID_TIPO_EVENTO, ORIGEN_COD, DESCRIPCION)"
                "VALUES ( ?, ?, ?, ?, ?, ? )"
           );
           st->Set(1, idt::dtNowLocal());
           st->Set(2, "PP");
           st->Set(3, "NO_SERVER");
           st->Set(4, "1");
           st->Set(5, "NO_PLACE");
           st->Set(6, "Nothing especial");
           st->Execute();

        tr->Commit();
        db->Disconnect();
    }
    catch (IBPP::Exception& e)
    {
        cout << e.what();
    }
    /*
      El control de excepciones debería ser así, pero lo dejamos al mínimo para este ejemplo

    } catch(const idt::Alarma& error) {
        std::cout << error;
        return -1;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return -1;
    } catch(...) {
        std::cout << "Error desconocido";
        return -1;
    }
    */



    #include "soporte/release_on_exit.hpp"
    return 0;
}


//---------------------------------------------------------------------------

//  RECEPTOR ALARMAS SALIDA GENERAL

//---------------------------------------------------------------------------

void idt::AlarmaMsg (const Alarma& alarma)
{
        std::cout << "\n\r";
        std::cout << std::endl << "ALARMA SALIDA..." << std::endl ;
        std::cout << alarma << std::endl ;
}
