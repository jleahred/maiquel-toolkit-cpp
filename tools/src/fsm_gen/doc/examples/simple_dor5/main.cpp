#include "support/mtk_string.h"
#include "support/misc.h"
#include "support/crc32.h"




#include "generated/simple_dor.h"
#include "generated/simple_dor.impl"








void on_logic_error(const mtk::Alarm& al)
{
	std::cout << al << std::endl;
	std::cout << "================================================================================" << std::endl;
}


void on_login_ok(const std::string& session_id)
{
    std::cout << "login ok  session_id  " << session_id << std::endl;
}

void on_log_out(const std::string& description)
{
    std::cout << "log out   " << description << std::endl;
}
void on_reject_login(void)
{
    std::cout << "reject login  " << std::endl;
}

std::string key;
void on_generated_key(const std::string& _key)
{
    key = _key;
    std::cout << "received key " << key << std::endl;
}


int  main(int /*argc*/, const char* /*argv*/[])
{
    try
    {
        std::cout << "login -> logout -> login" << std::endl << std::endl;
        {
            testing::simple_dor dor;

            //  connect signals
            dor.sig_login_ok.connect(on_login_ok);
            dor.sig_logout.connect(on_log_out);
            dor.sig_reject_login.connect(on_reject_login);
            dor.sig_generated_key.connect(on_generated_key);
            dor.sig_alarm.connect(on_logic_error);

            // request valid login
            dor.rq_key();

            std::string user = "fulanito";
            std::string calculated_pass_coded = mtk::crc32_as_string(MTK_SS(user << "1111" << key));
            dor.rq_login(user, calculated_pass_coded);

            dor.rq_logout();

            // request valid login
            dor.rq_key();
            user = "fulanito";
            calculated_pass_coded = mtk::crc32_as_string(MTK_SS(user << "1111" << key));
            dor.rq_login(user, calculated_pass_coded);

            dor.rq_logout();
        }

        std::cout << std::endl << std::endl << "************************************************" << std::endl << std::endl;

        std::cout << "login and request key on login_ok..." << std::endl << std::endl;
        {
            testing::simple_dor dor;

            //  connect signals
            dor.sig_login_ok.connect(on_login_ok);
            dor.sig_logout.connect(on_log_out);
            dor.sig_reject_login.connect(on_reject_login);
            dor.sig_generated_key.connect(on_generated_key);
            dor.sig_alarm.connect(on_logic_error);

            // request valid login
            dor.rq_key();

            std::string user = "fulanito";
            std::string calculated_pass_coded = mtk::crc32_as_string(MTK_SS(user << "1111" << key));
            dor.rq_login(user, calculated_pass_coded);


            // request key on valid login
            dor.rq_key();
        }

        std::cout << std::endl << std::endl << "************************************************" << std::endl << std::endl;


        std::cout << "requesting login invalid pass..." << std::endl << std::endl;
        {
            testing::simple_dor dor;

            //  connect signals
            dor.sig_login_ok.connect(on_login_ok);
            dor.sig_logout.connect(on_log_out);
            dor.sig_reject_login.connect(on_reject_login);
            dor.sig_generated_key.connect(on_generated_key);
            dor.sig_alarm.connect(on_logic_error);

            // request login invalid pass
            dor.rq_key();

            std::string user = "fulanito";
            std::string calculated_pass_coded = mtk::crc32_as_string(MTK_SS(user << "aaaa" << key));
            dor.rq_login(user, calculated_pass_coded);
        }



        std::cout << std::endl << std::endl << "************************************************" << std::endl << std::endl;

        std::cout << "login -> get_session_id -> logout -> get_session_id  look the problem" << std::endl << std::endl;
        {
            testing::simple_dor dor;

            //  connect signals
            dor.sig_login_ok.connect(on_login_ok);
            dor.sig_logout.connect(on_log_out);
            dor.sig_reject_login.connect(on_reject_login);
            dor.sig_generated_key.connect(on_generated_key);
            dor.sig_alarm.connect(on_logic_error);

            // request valid login
            dor.rq_key();

            std::string user = "fulanito";
            std::string calculated_pass_coded = mtk::crc32_as_string(MTK_SS(user << "1111" << key));
            dor.rq_login(user, calculated_pass_coded);

            std::cout << "session_id  "  <<  dor.session_id()  << "             OK"  << std::endl;

            dor.rq_logout();

            std::cout << "session_id  "  <<  dor.session_id()  << "             BAD  (on this status, session id doesn't exists)"  << std::endl;
        }

    }
    MTK_CATCH_CALLFUNCION (std::cout << , "main", "nothing more")

    return 0;
}



void mtk::AlarmMsg(const mtk::Alarm& error)
{
    std::cout << error << std::endl;
}
