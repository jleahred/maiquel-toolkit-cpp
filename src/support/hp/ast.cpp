#include "ast.h"

#include "support/re/RegExp.h"
#include "support/mtk_string.h"
#include "support/foreach.hpp"
#include <map>
#include <sstream>

//#include <iostream>  // debug



namespace mtk {



/**
    Añade en el mismo nivel un nodo hermano
*/
mtk::CountPtr<AST_Node_Item> AST_Node_Item::AddNext(const std::string& _name, const std::string& _value, const std::string& _rule4Replace)
{
    next = mtk::CountPtr<AST_Node_Item>(new AST_Node_Item(_name, _value, _rule4Replace));
    return next;
}

/**
    Añade en un nivel inferior
*/
mtk::CountPtr<AST_Node_Item> AST_Node_Item::AddChild(const std::string& _name, const std::string& _value, const std::string& _rule4Replace)
{
    down = mtk::CountPtr<AST_Node_Item>(new AST_Node_Item(_name, _value, _rule4Replace));
    return down;
}



std::string AST_GetStringNodesOnLevel(const AST_Node_Item* const node)
{
    std::ostringstream result;

//    if (node==0)
//        return "nil";

    const AST_Node_Item* current_node = node;

    while (true)
    {
        result << "NODE NAME:    " << current_node->name;
        result << "             code:         " << long(current_node) << std::endl;
        if (current_node->next.isValid() == false)
            break;
        current_node = current_node->next.get2();
    }

    return result.str();
}


std::string AST_GetStringNodes(const AST_Node_Item* const node)
{
    std::ostringstream result;

//    if (node==0)
//        return "nil";

    //  primero recorremos hacia abajo y luego hacia la derecha (el mismo nivel)

    result << "--------------------------------------------------------------" << std::endl;
    result << "NODE NAME:    " << node->name            << std::endl;
    result << "code:         " << long(node)            << std::endl;
    result << "value:        " << node->value           << std::endl;
    result << "rule4Replace: " << node->rule4Replace    << std::endl;
    result << "childs:       " << std::endl;

        if (node->down.isValid())
            result << AST_GetStringNodesOnLevel(node->down.get2());

    result << "--------------------------------------------------------------" << std::endl;


    if (node->down.isValid())
        result << AST_GetStringNodes(node->down.get2());

    if (node->next.isValid())
        result << AST_GetStringNodes(node->next.get2());


    return result.str();

}



/*
    Replace methods
*/


void AST_Node_Item::ExecReplace(void)
{

    //  primero recorremos hacia abajo y luego hacia la derecha (el mismo nivel)
    if (this->down.isValid())
    {
        this->down->ExecReplace();
        //this->value = this->down->value;
    }

    if (this->next.isValid())
    {
        this->next->ExecReplace();
        //this->value += this->next->value;
    }

    ExecReplaceCurrent();


}




std::string Replace(const std::map<std::string, std::string>& mapItemsFounded, const std::string& rule4Replace);
std::string Replace(const std::string& founded, const std::string& rule4Replace);

void AST_Node_Item::ExecReplaceCurrent(void)
{
    if (this->down.isValid() == false)
    {
        if (rule4Replace!="")
            value = Replace(value, rule4Replace);
        return;
    }

    CountPtr<AST_Node_Item> currentNode = this->down;
    std::map<std::string, std::string>  mapFounded;
    std::ostringstream os;

    while (currentNode.isValid())
    {
        if (mtk::s_trim(rule4Replace, ' ') !="")
        {
            int contador = 0;
            std::string symbol = currentNode->name;
            while (mapFounded.find(symbol) != mapFounded.end())
            {
                ++contador;
                symbol = MTK_SS(currentNode->name << "#" << contador);
            }
            mapFounded[symbol] = currentNode->value;

        }
        else
            os << currentNode->value;
        currentNode = currentNode->next;
    }


    if (rule4Replace !="")
        this->value = Replace(mapFounded, rule4Replace);
    else
        this->value = os.str();
}

std::string Replace(const std::string& founded, const std::string& rule4Replace)
{
    if (mtk::s_trim(rule4Replace, ' ') !="")
    {
        std::map<std::string, std::string> mapFounded;
        mapFounded["t"] = founded;
        return Replace(mapFounded, rule4Replace);
    }
    else
        return founded;
}


std::string Replace(const std::map<std::string, std::string>& mapItemsFounded, const std::string& rule4Replace)
{
    static int replaceCounter = 0;
    ++replaceCounter;

    //  predefined vars on trasform
    static std::map<std::string, std::string> mapPredefinedVars;
    if (mapPredefinedVars.size() == 0)
    {
        mapPredefinedVars["__nothing__"] = "";
        mapPredefinedVars["__endl__"] = "\n";   //MTK_SS(std::endl);
        mapPredefinedVars["__space__"] = " ";
        mapPredefinedVars["__dollar_open_par__"] = "$(";
        mapPredefinedVars["__close_par__"] = ")";
    }
    mapPredefinedVars["__counter__"] = MTK_SS(replaceCounter);


    //  buscar las variables a cambiar
        //  el texto hasta el inicio de la siguiente variable se añade como está
        //  luego se añade el reemplazo de la variable


    std::string result;
    //  buscamos inicio de variable
    std::string::size_type previus = 0;
    for (std::string::size_type i=0; i<rule4Replace.size()-1; ++i)
    {
        if (rule4Replace[i] == '$'  &&  rule4Replace[i+1] == '(')
        {
            //  eureka
            result += rule4Replace.substr(previus, i-previus);
            i+=2;
            std::string::size_type initVar = i;
            while (i<rule4Replace.size()  &&  rule4Replace[i] != ')')
                ++i;
            std::string varName = rule4Replace.substr(initVar, i-initVar);
            std::map<std::string, std::string>::const_iterator it = mapItemsFounded.find(varName);
            std::map<std::string, std::string>::const_iterator itPredefined = mapPredefinedVars.find(varName);
            if (it != mapItemsFounded.end())
                result += it->second;
            else if (itPredefined != mapPredefinedVars.end())
                result += itPredefined->second;
            else
                result += MTK_SS("$(" << varName << ")");
            previus = i+1;
        }
    }
    result += rule4Replace.substr(previus);

    return result;

}


bool  in_list   (const mtk::list<std::string>& lNodes2mantein, const std::string& value)
{
    MTK_FOREACH_CONST_ITERATOR(it, lNodes2mantein)
    {
        if (*it  ==  value)
            return true;
    }
    return false;
}


void  AST_Node_Item::RemoveNodesManteining   (const mtk::list<std::string>& lNodes2mantein)
{
    //  si down es un elemento para eliminar...
        //  down =   down->next

    //  si next es un elemento para eliminar...
        //  next = next->next

    //  recursivo con down
    //  recursivo con next



    if (this->down.isValid())
    {
        //  si down es un elemento para eliminar...
        if (in_list(lNodes2mantein, this->down->name) == false)
        {
            //  down =   down->next
            if (this->down->next.isValid())
            {
                this->down = this->down->next;
                //  recursivo con down
                this->RemoveNodesManteining(lNodes2mantein);

            }
            else
                this->down = mtk::CountPtr<AST_Node_Item>();
        }
        else
        //  recursivo con down
            this->down->RemoveNodesManteining(lNodes2mantein);
    }


        //  si next es un elemento para eliminar...
        if (this->next.isValid())
        {
            if (in_list(lNodes2mantein, this->next->name) == false)
            {
                //  next =   next->next
                if (this->next->next.isValid())
                {
                    this->next = this->next->next;
                    this->RemoveNodesManteining(lNodes2mantein);
                }
                else
                    //  recursivo con next
                    this->next = mtk::CountPtr<AST_Node_Item>();
            }
            else
                //  recursivo con next
                this->next->RemoveNodesManteining(lNodes2mantein);

        }



}





};  //  namespace mtk {
