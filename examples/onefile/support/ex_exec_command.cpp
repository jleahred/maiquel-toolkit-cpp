#include "support/exec_command.h"

#include "support/call_later.h"





void  force_stop_command(mtk::exec_command* const&  ec)
{
    ec->stop("from main program");
}


void  terminated_command(bool ok, const std::string& desc, const std::string& termination_info, const mtk::dtTimeQuantity& exec_time)
{
    std::cout << "__NR__:  terminated_command: "
            <<  "  "  << std::boolalpha  << ok
            <<  "  "  << desc
            <<  "  "  << termination_info
            <<  "  "  << exec_time
            << std::endl;

    mtk::stop_timer();
}



void on_new_messages(const mtk::list<std::string>& lines)
{
    for(auto it=lines.begin(); it!=lines.end(); ++it)
        std::cout << "__NR__:   ~" << *it << std::endl;
}






int main(int /*argc*/, char ** /*argv*/)
{
    try
    {
        //////////////////////////////////////////////////////
        mtk::exec_command  ec("this is a test", mtk::dtSeconds(5));
        //////////////////////////////////////////////////////

        ec.set_command("./script.sh");
        //ec.set_command("ls  -l -h -s");

        ec.signal_terminated.connect(terminated_command);
        ec.signal_new_lines.connect(on_new_messages);

        ec.run();


        mtk::start_timer_wait_till_end();


        #include "support/release_on_exit.hpp"
        return 0;
    }
    MTK_CATCH_CALLFUNCION(std::cout << , "main", "nothing more to add")

    #include "support/release_on_exit.hpp"
    return -1;
}




//---------------------------------------------------------------------------

//  RECEPTOR ALARMAS SALIDA GENERAL

//---------------------------------------------------------------------------

void mtk::AlarmMsg (const Alarm& alarma)
{
        std::cout << "\n\r";
        std::cout << std::endl << "ALARMA SALIDA..." << alarma <<  std::endl ;
        std::cout << alarma << std::endl ;
}
