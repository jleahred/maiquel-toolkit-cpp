#include <iostream>


#include "support/hvm/bhvm.h"
#include "support/mtk_string.h"
#include "support/nullable.hpp"
#include "support/foreach.hpp"





using namespace std;



void mtk::AlarmMsg(const mtk::Alarm& al)
{
    std::cout << "ouch...: "  << al << std::endl;

}




//  tipos de datos de la máquina
const char* code_type_bool      = "bool:";
const char* code_type_double    = "double:";
const char* code_type_var       = "var:";
const char* code_type_void      = "void:";


//  valores predefinidos para algunos tipos de datos
const char* code_val_void = "(__void__)";
const char* code_val_true       = "bool:true";
const char* code_val_false      = "bool:false";






//  comandos que añadimos a la máquina...

void  process_add                   (mtk::bhvm* bm);
void  process_subs                  (mtk::bhvm* bm);

void  process_and                   (mtk::bhvm* bm);
void  process_or                    (mtk::bhvm* bm);
void  process_not                   (mtk::bhvm* bm);
void  process_if                    (mtk::bhvm* bm);
void  process_equal                 (mtk::bhvm* bm);
void  process_not_equal             (mtk::bhvm* bm);


void  process_define_variable       (mtk::bhvm* bm);
void  process_write_value2var       (mtk::bhvm* bm);
void  process_read_value4var        (mtk::bhvm* bm);








std::string get_vars_status(void);

void ShowLog(const mtk::Alarm& info)
{
    std::cout << info << std::endl;
}





int main()
{


    try
    {
        mtk::bhvm  machine;

        machine.signal_debug.connect    (&ShowLog);
        machine.signal_error.connect    (&ShowLog);
        machine.signal_warning.connect  (&ShowLog);

        //  registro de comandos  ------------------------------------------------------------------------
        MTK_HVM_REGISTER_COMMAND(machine, cmd_add       , "cmd:+"        , process_add            );
        MTK_HVM_REGISTER_COMMAND(machine, cmd_sub       , "cmd:-"        , process_subs           );

        MTK_HVM_REGISTER_COMMAND(machine, cmd_and       , "cmd:and"      , process_and            );
        MTK_HVM_REGISTER_COMMAND(machine, cmd_or        , "cmd:or"       , process_or             );
        MTK_HVM_REGISTER_COMMAND(machine, cmd_not       , "cmd:not"      , process_not            );
        MTK_HVM_REGISTER_COMMAND(machine, cmd_if        , "cmd:if"       , process_if             );

        MTK_HVM_REGISTER_COMMAND(machine, cmd_equal     , "cmd:=="       , process_equal          );
        MTK_HVM_REGISTER_COMMAND(machine, cmd_not_equal , "cmd:!="       , process_not_equal      );

        MTK_HVM_REGISTER_COMMAND(machine, cmd_defvar    , "cmd:defvar"   , process_define_variable);
        MTK_HVM_REGISTER_COMMAND(machine, cmd_w2v       , "cmd:write2var", process_write_value2var);
        MTK_HVM_REGISTER_COMMAND(machine, cmd_r4v       , "cmd:read4var" , process_read_value4var );



        //  1-(5+2)
//        machine.insert_instruction("push double:1");
//        machine.insert_instruction("push double:2");
//        machine.insert_instruction("push double:5");
//        machine.insert_instruction("push cmd:+");
//        machine.insert_instruction("calle");
//        machine.insert_instruction("push cmd:-");
//        machine.insert_instruction("calle");



//        //  variables
//        //  declaramos x de tipo double:
//        machine.insert_instruction("push double:");
//        machine.insert_instruction("push var:x");
//        machine.insert_instruction("push cmd:defvar");
//        machine.insert_instruction("calle");
//        //  asignamos a x el valor 2
//        machine.insert_instruction("push double:2");
//        machine.insert_instruction("push var:x");
//        machine.insert_instruction("push cmd:write2var");
//        machine.insert_instruction("calle");
//        //  declaramos y de tipo double:
//        machine.insert_instruction("push double:");
//        machine.insert_instruction("push var:y");
//        machine.insert_instruction("push cmd:defvar");
//        machine.insert_instruction("calle");
//        //  asignamos a y el valor 2
//        machine.insert_instruction("push double:33");
//        machine.insert_instruction("push var:y");
//        machine.insert_instruction("push cmd:write2var");
//        machine.insert_instruction("calle");
//        //  asignamos a x el valor 55
//        machine.insert_instruction("push double:55");
//        machine.insert_instruction("push var:x");
//        machine.insert_instruction("push cmd:write2var");
//        machine.insert_instruction("calle");
//
//        //  leemos valor de x
//        machine.insert_instruction("push var:x");
//        machine.insert_instruction("push cmd:read4var");
//        machine.insert_instruction("calle");
//        //  leemos valor de y
//        machine.insert_instruction("push var:y");
//        machine.insert_instruction("push cmd:read4var");
//        machine.insert_instruction("calle");




//        //  x=55; x+10
//        //  declaramos x de tipo double:
//        machine.insert_instruction("push double:");
//        machine.insert_instruction("push var:x");
//        machine.insert_instruction("push cmd:defvar");
//        machine.insert_instruction("calle");
//        //  asignamos a x el valor 7
//        machine.insert_instruction("push double:55");
//        machine.insert_instruction("push var:x");
//        machine.insert_instruction("push cmd:write2var");
//        machine.insert_instruction("calle");
//        //  metemos 10
//        machine.insert_instruction("push double:10");
//        //  leemos valor de x
//        machine.insert_instruction("push var:x");
//        machine.insert_instruction("push cmd:read4var");
//        machine.insert_instruction("calle");
//        //  sumamos
//        machine.insert_instruction("push cmd:+");
//        machine.insert_instruction("calle");




//        //  x=void; x+10
//        //  declaramos x de tipo double:
//        machine.insert_instruction("push double:");
//        machine.insert_instruction("push var:x");
//        machine.insert_instruction("push cmd:defvar");
//        machine.insert_instruction("calle");
//        //  metemos 10
//        machine.insert_instruction("push double:10");
//        //  leemos valor de x
//        machine.insert_instruction("push var:x");
//        machine.insert_instruction("push cmd:read4var");
//        machine.insert_instruction("calle");
//        //  sumamos
//        machine.insert_instruction("push cmd:+");
//        machine.insert_instruction("calle");





//        //  variables
//        //  declaramos a de tipo bool:
//        machine.insert_instruction("push bool:");
//        machine.insert_instruction("push var:a");
//        machine.insert_instruction("push cmd:defvar");
//        machine.insert_instruction("calle");
//        //  asignamos a a el valor true
//        machine.insert_instruction("push bool:true");
//        machine.insert_instruction("push var:a");
//        machine.insert_instruction("push cmd:write2var");
//        machine.insert_instruction("calle");
//        //  leemos valor de a
//        machine.insert_instruction("push var:a");
//        machine.insert_instruction("push cmd:read4var");
//        machine.insert_instruction("calle");
//        //  or false
//        machine.insert_instruction("push bool:false");
//        machine.insert_instruction("push cmd:or");
//        machine.insert_instruction("calle");



//        //  prueba if
//        machine.insert_instruction("push double:1");
//        machine.insert_instruction("push double:2");
//        machine.insert_instruction("push bool:true");
//        machine.insert_instruction("push cmd:if");
//        machine.insert_instruction("calle");



//        //  prueba igualdad
//        machine.insert_instruction("push double:4");
//        machine.insert_instruction("push double:6");
//        machine.insert_instruction("push cmd:==");
//        machine.insert_instruction("calle");




//        //  prueba salto condicional
//        machine.insert_instruction("push label:falso");
//        machine.insert_instruction("push label:verdadero");
//        machine.insert_instruction("push bool:false");      //------------
//        machine.insert_instruction("push cmd:if");
//        machine.insert_instruction("calle");
//        machine.insert_instruction("jump");
//        //  ejecutar si falso
//        machine.define_label("label:falso");
//        machine.insert_instruction("push double:33");
//        machine.insert_instruction("push label:continuar");
//        machine.insert_instruction("jump");
//        //  ejecutar si verdadero
//        machine.define_label("label:verdadero");
//        machine.insert_instruction("push double:55");
//        //  continuar
//        machine.define_label("label:continuar");
//        machine.insert_instruction("nop");


        //  el input es la entrada estándar
        std::string string2execute;
        while (std::cin.eof() == false)
        {
            char next_char = char(std::cin.get());
            //if (next_char == '\n'  ||  next_char == '\r')
            //      break;

            string2execute += next_char;
        }
        string2execute = string2execute.substr(0, string2execute.size()-2);
        mtk::vector<std::string>  vlines2parse = mtk::s_split(string2execute, "\n");
        for (unsigned i = 0; i < vlines2parse.size(); ++i)
        {
            std::string line2insert = mtk::s_trim(vlines2parse[i], ' ');

            if (line2insert.substr(0, 13) == "define_label:")
            {
                machine.define_label(line2insert.substr(13));
                continue;
            }

            if (line2insert != "")
                machine.insert_instruction(vlines2parse[i]);
        }





        machine.execute_program();
        std::cout << machine.get_status()  << std::endl;
        std::cout << get_vars_status() << std::endl;


    } catch(const mtk::Alarm& error) {
        std::cout << error;
    } catch (std::exception& e) {
        std::cout << mtk::Alarm("execute_program", MTK_SS("c++ exception " << e.what()), mtk::alPriorCritic);
    } catch(...) {
        std::cout << mtk::Alarm("execute_program", "unknown error", mtk::alPriorCritic);
    }

    #include "support/release_on_exit.hpp"
    return 0;
}




//  ----------------------------------------------------------------------------------------
//  declaraciones de soporte

mtk::nullable<double>   s_read_double           (mtk::bhvm* bm);
void                    s_write_double          (mtk::bhvm* bm, mtk::nullable<double> value);

mtk::nullable<bool>     s_read_bool             (mtk::bhvm* bm);
void                    s_write_bool            (mtk::bhvm* bm, mtk::nullable<bool> value);


std::string             s_read_var_name         (mtk::bhvm* bm);
void                    s_write_varname         (mtk::bhvm* bm, const std::string& var_name);

std::string             s_get_value_from_var    (const std::string& var_name);
void                    s_save_value_in_var     (const std::string& var_name, const std::string& value);
void                    s_def_variable          (const std::string& var_name, const std::string& var_type);

mtk::tuple<std::string, std::string> s_get_val_type_and_value  (const std::string& value);




//  ----------------------------------------------------------------------------------------
//  implementación  c o m a n d o s
//  ----------------------------------------------------------------------------------------


void  process_add (mtk::bhvm* bm)
{
    //  sacar los parámetros
    //  sumar
    //  meter en la pila el resultado

    mtk::nullable<double> num2 = s_read_double(bm);
    mtk::nullable<double> num1 = s_read_double(bm);

    if (num1.HasValue() == false  ||  num2.HasValue()==false)
        s_write_double(bm, mtk::nullable<double>());
    else
        s_write_double(bm, mtk::make_nullable(num1.Get()+num2.Get()));
}

void  process_subs  (mtk::bhvm* bm)
{
    mtk::nullable<double> num2 = s_read_double(bm);
    mtk::nullable<double> num1 = s_read_double(bm);

    if (num1.HasValue() == false  ||  num2.HasValue()==false)
        s_write_double(bm, mtk::nullable<double>());
    else
        s_write_double(bm, mtk::make_nullable(num1.Get()-num2.Get()));
}

void  process_and  (mtk::bhvm* bm)
{
    mtk::nullable<bool> val2 = s_read_bool(bm);
    mtk::nullable<bool> val1 = s_read_bool(bm);

    if (val1.HasValue() == false  ||  val2.HasValue()==false)
        s_write_bool(bm, mtk::nullable<bool>());
    else
        s_write_bool(bm, mtk::make_nullable(val1.Get() && val2.Get()));
}

void  process_or  (mtk::bhvm* bm)
{
    mtk::nullable<bool> val2 = s_read_bool(bm);
    mtk::nullable<bool> val1 = s_read_bool(bm);

    if (val1.HasValue() == false  ||  val2.HasValue()==false)
        s_write_double(bm, mtk::nullable<double>());
    else
        s_write_bool(bm, mtk::make_nullable(val1.Get() || val2.Get()));
}

void  process_not  (mtk::bhvm* bm)
{
    mtk::nullable<bool> val = s_read_bool(bm);

    if (val.HasValue() == false)
        s_write_bool(bm, mtk::nullable<bool>());
    else
        s_write_bool(bm, mtk::make_nullable(!val.Get()));
}

void  process_if  (mtk::bhvm* bm)
{
    mtk::nullable<bool> val = s_read_bool(bm);

    bool condition;
    if (val.HasValue() == false)
        condition = false;
    else if (val.Get() == false)
        condition = false;
    else
        condition = true;

    //  si es verdadero, sacamos dos elementos de la pila y dejamos el primero
    //  si es falso, sacamos dos elementos de la pila y dejamos el segundo

    if (condition)
    {
        std::string result = bm->get_top();
        bm->exec_pop();
        bm->exec_pop();
        bm->exec_push(result);
    }
    else
    {
        bm->exec_pop();
        std::string result = bm->get_top();
        bm->exec_pop();
        bm->exec_push(result);
    }
}

void  process_equal  (mtk::bhvm* bm)
{
    std::string first = bm->get_top();
    bm->exec_pop();
    std::string second = bm->get_top();
    bm->exec_pop();

    if (first != second)
        bm->exec_push(code_val_false);
    else
        bm->exec_push(code_val_true);
}


void  process_not_equal  (mtk::bhvm* bm)
{
    std::string first = bm->get_top();
    bm->exec_pop();
    std::string second = bm->get_top();
    bm->exec_pop();

    if (first != second)
        bm->exec_push(code_val_true);
    else
        bm->exec_push(code_val_false);
}




void  process_define_variable       (mtk::bhvm* bm)
{
    std::string var_name = s_read_var_name(bm);

    std::string var_type = bm->get_top();
    bm->exec_pop();

    s_def_variable(var_name, var_type);
}


void  process_write_value2var     (mtk::bhvm* bm)
{
    //  sacar el nombre de variable
    std::string var_name = s_read_var_name(bm);

    //  sacar el valor a asignar
    std::string value = bm->get_top();
    //bm->exec_pop();

    //  guardar valor
    s_save_value_in_var(var_name, value);
}

void  process_read_value4var      (mtk::bhvm* bm)
{
    bm->exec_push( s_get_value_from_var( s_read_var_name(bm) ) );
}







//  ----------------------------------------------------------------------------------------
//  implementación soporte

mtk::nullable<double> s_read_double (mtk::bhvm* basic_machine)
{

    std::string top = basic_machine->get_top();
    basic_machine->exec_pop();


    std::string type;
    std::string value;
    s_get_val_type_and_value(top).assign(type, value);

    if (type != code_type_double)
        throw mtk::Alarm("read_double", MTK_SS(top << " is not a number"), mtk::alPriorCritic);


    if (value == code_val_void)
        return mtk::nullable<double>();


    bool   conversionResult;

    double result;
    mtk::s_TRY_stod                (value, 0.).assign(result, conversionResult);
    if (conversionResult == false)
        throw mtk::Alarm("s_read_double", MTK_SS("invalid conversion from " << value << " to double"), mtk::alPriorCritic);

    return mtk::make_nullable(result);
}

void s_write_double (mtk::bhvm* basic_machine, mtk::nullable<double> number)
{
    if (number.HasValue())
        basic_machine->exec_push(MTK_SS(code_type_double << number.Get()));
    else
        basic_machine->exec_push(MTK_SS(code_type_double << code_val_void));
}



mtk::nullable<bool> s_read_bool (mtk::bhvm* basic_machine)
{

    std::string top = basic_machine->get_top();
    basic_machine->exec_pop();


    std::string type;
    std::string value;

    s_get_val_type_and_value(top).assign(type, value);

    if (type != code_type_bool)
        throw mtk::Alarm("s_read_bool", MTK_SS(top << " is not a boolean"), mtk::alPriorCritic);


    if (value == code_val_void)
        return mtk::nullable<bool>();

    if      (value=="true")
        return mtk::make_nullable(true);
    else if (value=="false")
        return mtk::make_nullable(false);
    else
        throw mtk::Alarm("s_read_bool", MTK_SS("invalid bool value in " << value), mtk::alPriorCritic);

}

void s_write_bool (mtk::bhvm* basic_machine, mtk::nullable<bool> value)
{
    if (value.HasValue())
    {
        if (value.Get())
            basic_machine->exec_push(code_val_true);
        else
            basic_machine->exec_push(code_val_false);
    }
    else
        basic_machine->exec_push(MTK_SS(code_type_bool << code_val_void));
}







std::string s_read_var_name (mtk::bhvm* basic_machine)
{
    std::string top = basic_machine->get_top();
    basic_machine->exec_pop();

    std::string varname;
    if (top.substr(0, 4) == code_type_var)
    {
        varname = top.substr(4);
    }
    else
        throw mtk::Alarm("read_varname", MTK_SS(top << " is not a var"), mtk::alPriorCritic);


    return varname;
}


void s_write_varname (mtk::bhvm* basic_machine, const std::string& var_name)
{
    basic_machine->exec_push(MTK_SS(code_type_var << var_name));
}





//  memoria asociativa para variables       ------------------------------------------------------------------

std::map< std::string, std::string > map_var_value;

void s_save_value_in_var(const std::string& var_name, const std::string& value)
{

    //  verificar existencia previa de la variable
    std::map< std::string, std::string >::iterator it = map_var_value.find(var_name);
    if (it == map_var_value.end())
        throw mtk::Alarm("s_save_value_in_var", MTK_SS(var_name << " doesn't exists"), mtk::alPriorCritic);

    std::string current_value = it->second;

    //  verificar tipos de variables
    if (s_get_val_type_and_value(value)._0 != s_get_val_type_and_value(current_value)._0)
        throw mtk::Alarm("s_save_value_in_var", MTK_SS(value << ", " << current_value << " type doesn't match, cannot assing"), mtk::alPriorCritic);

    it->second = value;
}


std::string s_get_value_from_var    (const std::string& var_name)
{
    //  verificar existencia previa de la variable
    std::map< std::string, std::string >::iterator it = map_var_value.find(var_name);
    if (it == map_var_value.end())
        throw mtk::Alarm("s_get_value_from_var", MTK_SS(var_name << " doesn't exists"), mtk::alPriorCritic);

    return it->second;
}

mtk::tuple<std::string, std::string> s_get_val_type_and_value  (const std::string& value)
{
    unsigned till_type = unsigned(value.find_first_of(':')+1);
    return mtk::make_tuple(value.substr(0, till_type), value.substr(till_type));
}


void s_def_variable(const std::string& var_name, const std::string& var_type)
{
    //  verificar existencia previa de la variable
    std::map< std::string, std::string >::iterator it = map_var_value.find(var_name);
    if (it != map_var_value.end())
        throw mtk::Alarm("s_def_variable", MTK_SS(var_name << " already exists"), mtk::alPriorCritic);

    map_var_value[var_name] = MTK_SS(var_type << code_val_void);
}


std::string get_vars_status(void)
{
    std::ostringstream  result;
    result << "vars" << std::endl;
    result << "==========" << std::endl;

    MTK_FOREACH(it, map_var_value) {
        result << it->first << " ==  " << it->second << std::endl;
    }
    return result.str();
}

