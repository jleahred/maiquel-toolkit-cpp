#ifndef JLEAST_H
#define JLEAST_H


#include <string>
#include "support/count_ptr.hpp"
#include "support/list.hpp"




namespace mtk {


class AST_Node_Item
{
public:
    std::string                     name        ;
    std::string                     value       ;
    std::string                     rule4Replace;
    mtk::CountPtr<AST_Node_Item>    down        ;
    mtk::CountPtr<AST_Node_Item>    next        ;

    AST_Node_Item(const std::string& _name, const std::string& _value="", const std::string& _rule4Replace="")
        :   name(_name),  value(_value), rule4Replace(_rule4Replace) {};

    mtk::CountPtr<AST_Node_Item> AddNext (const std::string& _name, const std::string& _value, const std::string& _rule4Replace);
    mtk::CountPtr<AST_Node_Item> AddChild(const std::string& _name, const std::string& _value, const std::string& _rule4Replace);

    void ExecReplace            (void);
    void RemoveNodesManteining  (const mtk::list<std::string>& lNodes2mantein);

private:
    void ExecReplaceCurrent(void);
};


std::string AST_GetStringNodes(const AST_Node_Item* const node);



};  //  namespace mtk {



#endif // JLEAST_H
