#ifndef  mtk__exec__command__h
#define  mtk__exec__command__h



#include "platform.hpp"
#if MTK_PLATFORM == MTK_LINUX_PLATFORM




#include "support/signalslot.hpp"
#include "support/date_time.h"
#include "support/asynch_signal.hpp"




namespace mtk {




class  exec_command  :    public  mtk::SignalReceptor
{
public:
    //  INIT
    exec_command(const std::string&  description,  const mtk::dtTimeQuantity&  time_out);
    exec_command(const exec_command&)               = delete;
    exec_command& operator= (const exec_command&)   = delete;
    ~exec_command(void);


    //  OUTPUT
    mtk::Signal<const mtk::list<std::string>& >                                             signal_new_lines;
    mtk::Signal<const mtk::list<std::string>& >                                             signal_new_outerror;

    mtk::Signal<    bool                        ,/*ok*/
                    const std::string&          ,/*description*/
                    const std::string&          ,/*termination info*/
                    const mtk::dtTimeQuantity&   /*exec time*/>                             signal_terminated;


    //  INPUT
    void   write(const  std::string&  text);


    //  ACCESS
    bool                                is_running                      (void)  const  {  return  start_running.HasValue();   }
    const mtk::list<std::string>&       get_all_last_lines              (void)  const  {  return  last_lines;                 }
    std::string                         get_all_last_lines_as_string    (void)  const;

    const mtk::list<std::string>&       get_out_last_lines              (void)  const  {  return  out_last_lines;             }
    std::string                         get_out_last_lines_as_string    (void)  const;

    const mtk::list<std::string>&       get_error_last_lines            (void)  const  {  return  error_last_lines;           }
    std::string                         get_error_last_lines_as_string  (void)  const;

    std::string                         get_description                 (void)  const  {  return  description;                }

    //  MANIPULATE
    void                                set_command(const std::string& _command);
    void                                run (void);
    void                                stop(const std::string& reason);


private:
    std::string                         description;

    pid_t                               child_pid;
    mtk::nullable<mtk::DateTime>        start_running;
    mtk::dtTimeQuantity                 time_out;
    mtk::tuple<bool, std::string>       exit_info;
    std::string                         command;

    std::string                         partial_line;
    std::string                         partial_line_error;
    mtk::list<std::string>              new_output_lines;
    mtk::list<std::string>              new_output_error;
    mtk::list<std::string>              last_lines;
    mtk::list<std::string>              out_last_lines;
    mtk::list<std::string>              error_last_lines;


    int                                 p_child2parent[2];
    int                                 p_parent2child[2];
    int                                 p_stderror    [2];

    void                                __check_output(void);
    void                                __internal_stop(void);
    void                                __on_time_out(const int&);
    void                                __send_new_output_lines(void);
    void                                __send_new_output_error(void);
};



};      //      namespace mtk


#endif  //  MTK_LINUX_PLATFORM


#endif      //  mtk__exec__command__h
