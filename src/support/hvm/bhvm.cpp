#include "bhvm.h"


//#include <iostream>     //  debug  cout
#include "support/mtk_string.h"



namespace mtk {



bhvm::bhvm(void) :
    program         (),
    stack           (),
    labels          (),
    program_counter (0) {}



void bhvm::insert_push   (const std::string& data)
{
    program.push_back("push " + data);
}

void bhvm::define_label  (const std::string& label)
{
    std::map   <std::string, int >::iterator it = labels.find(label);
    if (it != labels.end())
        signal_warning (Alarm(MTK_HERE, "bhvm", MTK_SS("repitied label " << label), alPriorCritic));

    labels[label] = int(program.size()-1);
}

void bhvm::insert_pop    (void)
{
    program.push_back("pop");
}

void bhvm::insert_nop    (void)
{
    program.push_back("nop");
}

void bhvm::insert_calle  (void)
{
    program.push_back("calle");
}

void bhvm::insert_jump   (void)
{
    program.push_back("jump");
}

void bhvm::insert_instruction (const std::string& instruction)
{
    program.push_back(instruction);
}






//  E J E C U C I Ó N   D E   I N S T R U C C IO N E S
void bhvm::exec_push   (const std::string& data)
{
    stack.push_back(data);
}

void bhvm::exec_pop    (void)
{
    if (stack.size() > 0)
        stack.pop_back();
    else
    {
        signal_error(mtk::Alarm(MTK_HERE, "bhvm",  MTK_SS("empty stack, endind program " << get_status()), mtk::alPriorCritic));
        program_counter = int(program.size());
    }
}

void bhvm::exec_nop    (void)
{
    ;
}


void bhvm::exec_calle  (void)
{
    std::string command = get_top();
    exec_pop();
    std::map<std::string, CountPtr< Signal<bhvm*> > >::iterator it = map_signal_external_commands.find(command);

    if (it == map_signal_external_commands.end()  ||  it->second.isValid()==false)
        throw Alarm(MTK_HERE, "bhvm",  MTK_SS("command not registered " << command), alPriorCritic);

    it->second->emit(this);

}

void bhvm::exec_jump   (void)
{
    std::string label2jump;

    if (stack.size() != 0)
    {
        label2jump = get_top();
        exec_pop();
        if (labels.find(label2jump) == labels.end())
        {
            signal_error (Alarm(MTK_HERE, "bhvm",  MTK_SS("inexistent label " << label2jump), alPriorCritic));
            throw Alarm(MTK_HERE, "bhvm",  MTK_SS("inexistent label " << label2jump), alPriorCritic);
        }
        else
            program_counter = labels[label2jump];
    }
    else
        throw Alarm(MTK_HERE, "bhvm",  MTK_SS("no label to jump (empty stack)"), alPriorCritic);
}

void bhvm::exec_instruction (const std::string& instruction)
{
    if (instruction == "pop")
    {
        exec_pop();
    }
    else if (instruction == "nop")
    {
        exec_nop();
    }
    else if (instruction == "calle")
    {
        exec_calle();
    }
    else if (instruction == "jump")
    {
        exec_jump();
    }
    else if (instruction.substr(0, 5) == "push ")
    {
        exec_push(instruction.substr(5));
    }
    else
        throw Alarm(MTK_HERE, "bhvm",  MTK_SS("unknown command " << instruction), alPriorCritic);
}


void bhvm::execute_program (void)
{
    try{


        while (program_counter < int(program.size()))
        {
	    //std::cout << program[program_counter] << std::endl;    // debug... traza todo
            exec_instruction(program[program_counter]);
            ++program_counter;
        }
        signal_debug(Alarm(MTK_HERE, "bhvm",  MTK_SS("end of program." << std::endl << get_status()), alPriorDebug));


    } catch(const mtk::Alarm& error) {
        Alarm al(MTK_HERE, "bhvm",  get_status(), alPriorCritic);
        al.Add(error);
        signal_error(al);
    } catch (std::exception& e) {
        signal_error(Alarm(MTK_HERE, "bhvm",  MTK_SS("c++ exception " << e.what()  << get_status()), alPriorCritic));
    } catch(...) {
        signal_error(Alarm(MTK_HERE, "bhvm",  MTK_SS("unknown error  " << get_status()), alPriorCritic));
    }
}





//  I N T E R A C C I Ó N   E X T E R I O R
std::string  bhvm::get_top        (void) const
{
    if (stack.size()==0)
        throw Alarm(MTK_HERE, "bhvm",  MTK_SS("empty stack"), alPriorCritic);

    return stack.back();
}

std::string  bhvm::get_status     (void) const
{
    std::ostringstream  result;
    result << "status" << std::endl;
    result << "==========" << std::endl;
    result << "program_counter:" << program_counter << std::endl;
    result << "stack:" << std::endl;
    for(unsigned i=0; i<stack.size(); ++i)
        result << "  " << stack[i] << std::endl;
    result << std::endl;
    return result.str();
}

int          bhvm::get_stack_size (void) const
{
    return int(stack.size());
}


CountPtr< Signal<bhvm*> >
bhvm::register_external_command (const std::string& command)
{
    CountPtr< Signal<bhvm*> > new_signal = make_cptr(new Signal<bhvm*>());

    std::map    <std::string, CountPtr < Signal<bhvm*> > >::iterator it = map_signal_external_commands.find(command);
    if (it == map_signal_external_commands.end())
    {
        map_signal_external_commands.insert(std::make_pair(command, new_signal));
        map_signal_external_commands[command].DANGEROUS_ThisInstance_NOT_Delete();
    }
    else
        throw Alarm(MTK_HERE, "bhvm",  MTK_SS("command already registered "), alPriorCritic);

    return new_signal;
}




};  //  namespace mtk {
