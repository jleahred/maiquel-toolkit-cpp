#ifndef BHVM_H
#define BHVM_H


#include <string>
#include <stack>
#include <map>

#include "support/vector.hpp"
#include "support/alarm.h"
#include "support/basic_types.hpp"
#include "support/signalslot.hpp"




#define MTK_HVM_REGISTER_COMMAND(__MACHINE__, __COMMAND_CODE__, __COMMAND_LITERAL__, __FUNCTION2PROCESS__)                        \
    mtk::CountPtr< mtk::Signal<mtk::bhvm*> >  __COMMAND_CODE__ = __MACHINE__.register_external_command    (__COMMAND_LITERAL__);  \
    __COMMAND_CODE__->connect(__FUNCTION2PROCESS__);


namespace mtk {



class bhvm : mtk::non_copyable
{
public:
    bhvm();
    //virtual ~bhvm();



    void execute_program (void);


    void define_label  (const std::string& label);


    //     I N S E R C I Ó N    D E    I N S T R U C C I O N E S   (en el programa)

    void insert_push   (const std::string& data);

    void insert_pop    (void);
    void insert_nop    (void);
    void insert_calle  (void);
    void insert_jump   (void);


    void insert_instruction (const std::string& instruction);




    //  S A L I D A
    mtk::Signal<const mtk::Alarm&>        signal_error;
    mtk::Signal<const mtk::Alarm&>        signal_warning;
    mtk::Signal<const mtk::Alarm&>        signal_debug;


    //  I N T E R A C C I Ó N   E X T E R I O R
    std::string  get_top        (void) const;

    std::string  get_status     (void) const;
    int          get_stack_size (void) const;

    CountPtr< Signal<bhvm*> >
    register_external_command (const std::string& command);




    //  E J E C U C I Ó N   D E   I N S T R U C C I O N E S
    void exec_push   (const std::string& data);

    void exec_pop    (void);
    void exec_nop    (void);
    void exec_calle  (void);
    void exec_jump   (void);

    void exec_instruction (const std::string& instruction);




private:
    mtk::vector <std::string>                   program;
    mtk::vector <std::string>                   stack;
    std::map    <std::string, int >             labels;
    int                                         program_counter;
    std::map    <std::string, CountPtr< Signal<bhvm*> > >   map_signal_external_commands;

};




};  //  namespace mtk {


#endif // BHVM_H
