#include "platform.hpp"
#if MTK_PLATFORM == MTK_LINUX_PLATFORM



#include "exec_command.h"


#include <fcntl.h>
#include <sys/wait.h>



#include "support/mtk_string.h"
#include "support/call_later.h"



namespace  mtk {




exec_command::exec_command(const mtk::dtTimeQuantity&  _time_out)
        :   child_pid(0), time_out(_time_out), exit_info({false, ""})
{
}



void  add_lines(mtk::list<std::string>& dest, const mtk::list<std::string>&  source)
{
    for(auto it=source.begin(); it!= source.end(); ++it)
        dest.push_back(*it);

    while(dest.size() > 500)
        dest.pop_front();
}

void exec_command::__send_new_output_lines(void)
{
    signal_new_lines.emit(new_output_lines);
    add_lines(last_lines, new_output_lines);
    add_lines(out_last_lines, new_output_lines);
    new_output_lines.clear();
}

void exec_command::__send_new_output_error(void)
{
    signal_new_outerror.emit(new_output_error);
    add_lines(last_lines, new_output_error);
    add_lines(error_last_lines, new_output_lines);
    new_output_error.clear();
}


//char**  prepare_params(const std::string& params)       //  VERY DANGEROUS, raw pointers pointers
//{
//    static char**   result;
//    if(result)      delete[]  result;
//    static mtk::vector<std::string>  vparams = mtk::s_split(params, " ");
//    result = new (char*[vparams.size()+1]);
//    for(unsigned  i=0; i<vparams.size(); ++i)
//        result[i] = const_cast<char*>(vparams[i].c_str());
//    result[vparams.size()] = 0;
//
//    return result;
//}

void exec_command::run(void)
{
    if(command == "")
        throw mtk::Alarm(MTK_HERE, "run", MTK_SS("Empty configured command, it can no be runned"), mtk::alPriorError);

    if(is_running())
        throw mtk::Alarm(MTK_HERE, "run", MTK_SS("Error command is running  with  " << command), mtk::alPriorError);

    start_running = mtk::dtNowLocal();
    MTK_CALL_LATER1S_THIS(time_out, 0, __on_time_out);

    exit_info = mtk::make_tuple(false, std::string{});

    new_output_lines.clear();
    new_output_error.clear();
    last_lines.clear();
    out_last_lines.clear();
    error_last_lines.clear();



    if (pipe(p_child2parent) != 0 || pipe(p_parent2child) != 0  || pipe(p_stderror) != 0)
        throw mtk::Alarm(MTK_HERE, "exec_command", MTK_SS("Error creating pipes command  " << command), mtk::alPriorError);

    child_pid = fork();

    if (child_pid < 0)
        throw mtk::Alarm(MTK_HERE, "exec_command", MTK_SS("Error executing fork  " << command), mtk::alPriorError);
    else if (child_pid == 0)        //  child
    {
        ::setsid();
        ::close(p_child2parent[STDIN_FILENO]);
        dup2(p_child2parent[STDOUT_FILENO], STDOUT_FILENO);

        ::close(p_parent2child[STDOUT_FILENO]);
        dup2(p_parent2child[STDIN_FILENO], STDIN_FILENO);

        ::close(p_stderror[STDIN_FILENO]);
        dup2(p_stderror[STDOUT_FILENO], STDERR_FILENO);

        //system(command.c_str());
        //system(command.c_str());      //  this is not valid because it create a new child
        //execlp("/bin/sh", "sh", "-c", "-e", "ls -l  && pwd && echo ok", NULL);
        execlp("/bin/sh", "sh", "-c", command.c_str(), NULL);
        //execvp(command.c_str(), prepare_params(params));
        std::cout << "ERROR execxxx " << command << std::endl;
        ::close(p_child2parent[STDOUT_FILENO]);
        ::close(p_parent2child[STDIN_FILENO]);
        ::close(p_stderror[STDOUT_FILENO]);
        exit(-1);       //  error  executing command
    }
    else
    {
        ::close(p_child2parent[STDOUT_FILENO]);
        ::close(p_parent2child[STDIN_FILENO]);
        ::close(p_stderror[STDOUT_FILENO]);
    }

    {
        int flags = fcntl(p_child2parent[0], F_GETFL); /* get current file status flags */
        flags |= O_NONBLOCK;		/* turn off blocking flag */
        fcntl(p_child2parent[0], F_SETFL, flags);		/* set up non-blocking read */
    }
    {
        int flags = fcntl(p_stderror[0], F_GETFL); /* get current file status flags */
        flags |= O_NONBLOCK;		/* turn off blocking flag */
        fcntl(p_stderror[0], F_SETFL, flags);		/* set up non-blocking read */
    }

    MTK_TIMER_1D(__check_output);
}

void exec_command::set_command(const std::string&  _command/*, const std::string& _params*/)
{
    if(is_running())
        throw mtk::Alarm(MTK_HERE, "set_command", MTK_SS("Error command is running  with  " << command << " recevied " << _command), mtk::alPriorError);

    command = _command;
    //params  = _params;
}

void   exec_command::write(const  std::string&  text)
{
    ::write(p_parent2child[1], text.c_str(), text.size());
}


bool __read__returns_false_if_fail(     mtk::list<std::string>&                                 output_lines,
                                        mtk::list<std::string>&                                 last_lines,
                                        mtk::list<std::string>&                                 error_or_out_last_lines,
                                        mtk::Signal<const mtk::list<std::string>&>&             signal_new_lines_xxx,
                                        int                                                     pipe[2],
                                        std::string&                                            partial_line,
                                        mtk::tuple<bool, std::string>&                          exit_info,
                                        const std::string                                       command
                                        )
{
    bool result=true;
    {
        static char databuf[1024];
        unsigned lines_before = output_lines.size();
        size_t size;
        while(true)
        {
            databuf[0] = 0;
            size= read(pipe[0], databuf, 1023);
            //std::cout << " size  " << size << std::endl;
            if(size >0  &&  size < 1024)
            {
                databuf[size] = 0;
                mtk::vector<std::string>  lines = mtk::s_split(databuf, "\n");
                for(unsigned i=0; i<lines.size()-1; ++i)
                {
                    if(output_lines.size() > 500)
                    {
                        lines.clear();
                        break;
                    }
                    else if(output_lines.size() == 500)
                        output_lines.push_back("too many lines, truncating lines...");
                    else
                    {
                        output_lines.push_back(partial_line + lines[i]);
                        partial_line = "";
                    }
                }

                if(lines.size() > 0)
                {
                    std::string  ll = lines[unsigned(lines.size()-1)];
                    if(ll != ""   &&  ll[ll.size()-1]=='\n')
                    {
                        output_lines.push_back(ll);
                        partial_line = "";
                    }
                    else
                        partial_line = ll;
                }
            }
            else
            {
                if ((errno != EAGAIN  &&  errno != EWOULDBLOCK  &&  errno != ESRCH)  &&  errno!=0)
                {
                    exit_info = {false, MTK_SS("ERROR getting stdout from  " << command << " errno " << errno) };
                    result = false;
                    //throw mtk::Alarm(MTK_HERE, "exec_command", MTK_SS("Error getting stdout from  " << command << " errno " << error_no), mtk::alPriorError);
                }
                break;
            }
        }
        if(lines_before != output_lines.size())
        {
            signal_new_lines_xxx.emit(output_lines);
            add_lines(last_lines, output_lines);
            add_lines(error_or_out_last_lines, output_lines);
            output_lines.clear();
        }
    }
    return result;
}

void  exec_command::__check_output(void)
{
    int status = 0;
    int wp = waitpid(child_pid, &status, WNOHANG);
    if(status != 0)
    {
        int exit_status = WEXITSTATUS(status);
        if(exit_info._1 == "")
        {
            if(exit_status == 0)
                exit_info = {true, "OK"};
            else
                exit_info = {false, MTK_SS("ERROR  exit code:" << exit_status)};
        }
    }
    if(wp == -1)
    //if(child_pid  &&  kill(child_pid,0))
    {
        if(status == 0  &&  exit_info._1 == "")
            exit_info = {true, "OK"};

        if(child_pid!=0)
        {
            ::close(p_child2parent[STDOUT_FILENO]);
            ::close(p_parent2child[STDIN_FILENO]);
            ::close(p_stderror    [STDOUT_FILENO]);

            kill(-child_pid, SIGKILL);


            child_pid = 0;
            MTK_TIMER_1D_STOP(__check_output);
            if(new_output_lines.size() != 0)
            {
                __send_new_output_error();
                __send_new_output_lines();
            }
            signal_terminated.emit(exit_info._0, exit_info._1, start_running.Get(), mtk::dtNowLocal() - start_running.Get());
            start_running = {};
        }
        return;
    }
    bool result_call_read = true;
    result_call_read = result_call_read && __read__returns_false_if_fail(new_output_error, last_lines, error_last_lines, signal_new_outerror, p_stderror, partial_line_error, exit_info, command);
    result_call_read = __read__returns_false_if_fail(new_output_lines, last_lines, out_last_lines,signal_new_lines, p_child2parent, partial_line, exit_info, command);
    if(result_call_read == false)
        __internal_stop();
}


void        exec_command::__internal_stop(void)
{
    if(child_pid!=0)
    {
        kill(-child_pid, SIGKILL);
        if(partial_line_error != "")
        {
            new_output_error.push_back(partial_line_error);
            __send_new_output_error();
        }
        if(partial_line != "")
        {
            new_output_lines.push_back(partial_line);
            __send_new_output_lines();
        }
    }
}

void        exec_command::stop(const std::string& reason)
{
    if(is_running()==false)
        throw mtk::Alarm(MTK_HERE, "stop", MTK_SS("Error command is NOT running"), mtk::alPriorError);

    exit_info = {false, MTK_SS("EXIT FORCED " << reason)};
    __internal_stop();
}






void exec_command::__on_time_out(const int&)
{
    if(start_running.HasValue())
        stop("time out");
}




std::string        exec_command::get_all_last_lines_as_string (void)  const
{
    std::string  result;

    for(auto it = get_all_last_lines().begin(); it!= get_all_last_lines().end(); ++it)
        result += MTK_SS(*it  <<  std::endl);
    return result;
}

std::string        exec_command::get_out_last_lines_as_string    (void)  const
{
    std::string  result;

    for(auto it = get_out_last_lines().begin(); it!= get_out_last_lines().end(); ++it)
        result += MTK_SS(*it  <<  std::endl);
    return result;
}

std::string        exec_command::get_error_last_lines_as_string  (void)  const
{
    std::string  result;

    for(auto it = get_error_last_lines().begin(); it!= get_error_last_lines().end(); ++it)
        result += MTK_SS(*it  <<  std::endl);
    return result;
}






};      //  namespace  mtk {


#endif      //  mtk__exec__command__h
