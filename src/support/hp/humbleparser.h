#ifndef HUMBLEPARSER_H
#define HUMBLEPARSER_H


#include <string>
#include <map>
#include <list>
#include <set>

#include "support/tuples.hpp"
#include "ast.h"


/*  todo
    Detectar blucles infinitos (en tiempo de ejecución)
    señales para avisar en caso de detectar errores
    detectar símbolos huérfanos CheckRules(void)
*/



namespace mtk {




class HumbleParser
{
public:
    HumbleParser();
    virtual ~HumbleParser();

    //  parse ------------------------------------------------------------
    mtk::tuple<bool, std::string/*remaining*/, AST_Node_Item>
    Parse(const std::string& input, const std::string& init) const;

    mtk::tuple<bool, std::string/*remaining*/, AST_Node_Item>
    MultiParse(const std::string& input, std::string minit="") const;


    //  load rules  ------------------------------------------------------
    mtk::tuple<bool, std::string>
    AddRule (const std::string& rule_t2);       //  regla y transformación

    mtk::tuple<bool, std::string>
    AddLine (std::string line);                 //  Añade una línea que puede contener parte de una regla
                                                //  Los retornos de carro y los tabuladores los cambia por espacios
                                                //  Luego llama a AddRule

    mtk::tuple<bool, std::string>
    LoadRulesFromStream (std::istream& stream);


    mtk::tuple<bool, std::string>
    LoadRulesFromFile(const std::string& fileRules);

    mtk::tuple<bool, std::string>
    LoadRulesFromString (std::string rules);



    //  status  ----------------------------------------------------------
    bool ExistErrorsInRules(void)  const    {  return existErrorsInRules;  }
    void Clear(void);
    std::list<std::string>   GetTerminalRules(void)const;
    std::list<std::string>   GetNonTerminalRules(void)const;


protected:

private:
    mutable std::string   string2parse;

    typedef std::map<   std::string,                                        //  rule left
                        std::list<  mtk::tuple<
                                                std::list<std::string>,     //  right symbols
                                                std::string> > >            //  transformation2
            ContainerRules  ;
    ContainerRules      nonTerminalRules ;
    ContainerRules      terminalRules    ;


    mtk::tuple<bool, int>
	ExecuteNonTerminal    (int srt2parsePos, const std::string& nonTerminalCode, AST_Node_Item& astNode) const;

    mtk::tuple<bool, int>
	ExecuteTerminal       (int str2parsePos, const std::string& terminalCode   , AST_Node_Item& astNode) const;

    mtk::tuple<bool, int/*, mtk::CountPtr<AST_Node_Item> */>
	ExecuteNonTerminalKlein   (int srt2parsePos, const std::string& nonTerminalCode, AST_Node_Item& astNode) const;

    mtk::tuple<bool, int/*, mtk::CountPtr<AST_Node_Item> */>
	ExecuteTerminalKlein      (int srt2parsePos, const std::string& nonTerminalCode, AST_Node_Item& astNode) const;


    bool existErrorsInRules;

    mutable int                                             deeperErrorParsingPos;
    mutable std::set<std::string>                           deeperErrorExpectedSymbols;

    bool IsTerminal(const std::string& str) const;

    std::string  defaultInitSymbol;





    mtk::tuple<bool, int> ExecutePredefinedVar   (int srt2parsePos, const std::string& terminalRule, AST_Node_Item& astNode, const std::string& rule2replace) const;
    mtk::tuple<bool, int> ExecuteRegularExpresion(int srt2parsePos, const std::string& terminalRule, AST_Node_Item& astNode, const std::string& rule2replace) const;
    mtk::tuple<bool, int> ExecuteLiteral         (int srt2parsePos, const std::string& terminalRule, AST_Node_Item& astNode, const std::string& rule2replace) const;


    //  debug
    mutable AST_Node_Item* astRootDebug;


    bool addingRuleMultiLine;
    std::string buildingRule;
};


}  //  namespace mtk {

#endif // HUMBLEPARSER_H
