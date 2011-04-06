#include "asocmem0.h"


#include "support/foreach.hpp"
#include "support/mtk_string.h"


#include <iostream>




namespace hell {




asoc_mem0::asoc_mem0()
{
    //ctor
}

//asoc_mem0::~asoc_mem0()
//{
//    //dtor
//}



void asoc_mem0::begin_scope (void)
{
    //  mezclamos inherited y current scope y lo volcamos en current_scope.inherited
    //  meter el scope anterior en la pila

    scope new_scope;
    new_scope.add2inherited(current_scope);
    scope_stack.push_front(current_scope);
    current_scope = new_scope;
}


void asoc_mem0::scope::add2inherited(const scope& scope2add)
{
    /*  Copia al nuevo inherited el anterior
        Añade o sobreescribe las variables de local al inherited scope
    */

    inherited_map_name2ref = scope2add.inherited_map_name2ref;

    std::map<std::string, mtk::CountPtr<std::string> >::const_iterator it = scope2add.local_map_name2ref.begin();
    for ( ; it!= scope2add.local_map_name2ref.end(); ++it) {
        inherited_map_name2ref[it->first] = it->second;
    }
}


void asoc_mem0::end_scope   (void)
{
    current_scope = scope_stack.front();
    scope_stack.pop_front();
}


void  asoc_mem0::write_var  (const std::string& var_name, const std::string& var_value)
{
    //  buscar la referencia en el ámbito actual
    //  si no existe, buscarla en el ámbito heredado
    //  escribir en memoria
    mtk::CountPtr<std::string> found = find_ref_from_var_name(var_name);

    if (found.isValid()==false)
    {
        signal_error(mtk::Alarm(MTK_HERE, "ascocmem0", MTK_SS("non existing var " << var_name), mtk::alPriorError));
    }
    else
    {
        //  *found = var_value;

        std::string new_value = *found;
        int processed = signal_assign_to.emit(var_value, new_value);
        if (processed==0)
        {
            *found = "";
            signal_error(mtk::Alarm(MTK_HERE, "ascocmem0", MTK_SS("not connected assing signal " << var_name), mtk::alPriorError));
        }
        else
        {
            *found = new_value;
        }
    }

}



std::string asoc_mem0::read_var  (const std::string& var_name)
{
    mtk::CountPtr<std::string> found = find_ref_from_var_name(var_name);

    if (found.isValid())
        return *found;
    else
    {
        signal_error(mtk::Alarm(MTK_HERE, "ascocmem0", MTK_SS("non existing var " << var_name), mtk::alPriorError));
        return "";
    }
}



mtk::CountPtr<std::string>  asoc_mem0::find_ref_from_var_name (const std::string& var_name)
{
    std::map<std::string, mtk::CountPtr<std::string> >::iterator it_found_ref_local = current_scope.local_map_name2ref.find(var_name);
    if ( it_found_ref_local != current_scope.local_map_name2ref.end())
    {
        return it_found_ref_local->second;
    }
    else
    {
        std::map<std::string, mtk::CountPtr<std::string> >::iterator it_found_ref_inherited = current_scope.inherited_map_name2ref.find(var_name);
        if ( it_found_ref_inherited != current_scope.inherited_map_name2ref.end())
        {
            return it_found_ref_inherited->second;
        }
    }
    return mtk::CountPtr<std::string>();
}

void  asoc_mem0::declare_var(const std::string& var_name, const std::string& var_value)
{
    mtk::CountPtr<std::string> found = find_ref_from_var_name(var_name);

    if (found.isValid()==false)
    {
        current_scope.local_map_name2ref[var_name] = mtk::make_cptr(new std::string(var_value));
    }
    else
    {
        signal_error(mtk::Alarm(MTK_HERE, "ascocmem0", MTK_SS("already existing var " << var_name), mtk::alPriorError));
    }
}



std::ostream& operator<< (std::ostream& os, const asoc_mem0& mem)
{
    os << "asoc_mem0::get_status" << std::endl;
    os << "--------------------------------------------------------------" << std::endl;

    os << mem.current_scope << std::endl;

    return os;
}


std::ostream& operator<< (std::ostream& os, const asoc_mem0::scope& sco)
{
    os << "LOCAL" << std::endl;
    os << "========" << std::endl;

    {
        std::map<std::string, mtk::CountPtr<std::string> >::const_iterator it = sco.local_map_name2ref.begin();
        while (it != sco.local_map_name2ref.end())
        {
            os << it->first << "==" << *(it->second) << std::endl;
            ++it;
        }
    }

    {
        std::map<std::string, mtk::CountPtr<std::string> >::const_iterator it = sco.inherited_map_name2ref.begin();
        while (it != sco.inherited_map_name2ref.end())
        {
            os << it->first << "==" << *(it->second) << std::endl;
            ++it;
        }
    }


    return os;

}





};  //namespace hell {
