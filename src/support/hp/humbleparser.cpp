#include "humbleparser.h"

#include "support/re/RegExp.h"
#include "support/mtk_string.h"
#include "support/mtk_string.h"


#include <iostream>  // I/O
#include <fstream>   // file I/O
#include <iomanip>   // format manipulation




//  debug ---------------------------------
//#include <iostream>
//#include "support/debug/checkscopetime.h"
//  debug ---------------------------------




namespace mtk {




HumbleParser::HumbleParser()
    :       string2parse                (),
            nonTerminalRules            (),
            terminalRules               (),
            existErrorsInRules          (false),
            deeperErrorParsingPos       (-1),
            deeperErrorExpectedSymbols  (),
            astRootDebug                (0),
            addingRuleMultiLine         (false)
{
}

HumbleParser::~HumbleParser()
{
}



bool HumbleParser::IsTerminal(const std::string& str) const
{
//mtk::CheckScopeTime cs("IsTerminal");
    if (str[0]>='A' && str[0]<='Z')
        return false;
    else
        return true;

    /*  se cambia por rendimiento, se volverá a poner
    if (str=="_")       return true;

    mtk::RegExp re ("^([A-Z][A-Z|0-9|_|']*)$");      //  esto es lo que se cumplen en los terminales

    if (re.Match(str))
        return false;
    else
        return true;
    */
}


#define PREPARE_NODE                    \
    if (currentAstNode.isValid() == false)				\
    {                                                                   \
        currentAstNode = mtk::make_cptr(new AST_Node_Item(nodeName));       \
        astNode.down = currentAstNode;                                  \
    }                                                                   \
    else                                                                \
    {                                                                   \
        currentAstNode->next = mtk::make_cptr(new AST_Node_Item(nodeName)); \
        currentAstNode = currentAstNode->next;                          \
    }                                                                   \

#define CHECK_ERRORS   \
    if (deeperErrorParsingPos < remainingStr2ParsePos  ||   deeperErrorParsingPos==-1)   \
    {   \
        deeperErrorParsingPos = remainingStr2ParsePos;   \
        deeperErrorExpectedSymbols.clear();   \
        deeperErrorExpectedSymbols.insert(*it1);   \
    }   \
    else if (remainingStr2ParsePos == deeperErrorParsingPos  ||   deeperErrorParsingPos==-1)   \
    {   \
        deeperErrorParsingPos = remainingStr2ParsePos;   \
        deeperErrorExpectedSymbols.insert(*it1);   \
    }



mtk::tuple<bool, int> HumbleParser::ExecuteNonTerminal( int str2parsePos, const std::string& nonTerminalCode, AST_Node_Item& astNode) const
{
//mtk::CheckScopeTime cs("ExecuteNONTerminal");
    ContainerRules::const_iterator itNonTerminal = nonTerminalRules.find(nonTerminalCode);
    if (itNonTerminal == nonTerminalRules.end())
        throw MTK_SS("non terminal symbol [" << nonTerminalCode <<  "] has no expansion rule");

    std::list< mtk::tuple <std::list<std::string>, std::string> >::const_iterator it0 = nonTerminalRules.find(nonTerminalCode)->second.begin();

    bool result=false;
    int strPosRule = str2parsePos;

    //  probamos con todas las reglas con símbolo a la izquierda  nonTerminalCode
    while (it0!=nonTerminalRules.find(nonTerminalCode)->second.end())
    {
        const std::list<std::string>& rightSymbols = it0->_0;

        strPosRule = str2parsePos;
        astNode.rule4Replace = it0->_1;

        //  probamos todos los símbolos de la derecha
        mtk::CountPtr<AST_Node_Item> currentAstNode;
        for(auto it1 = rightSymbols.begin(); it1 != rightSymbols.end(); ++it1)
        {
            int remainingStr2ParsePos = strPosRule;
            result = false;

            std::string nodeName(*it1);
            PREPARE_NODE
            CHECK_ERRORS

            if (IsTerminal(*it1))
            {
                //cs.Stop();
                if (it1->substr(it1->size()-1) == "*")
                    ExecuteTerminalKlein(remainingStr2ParsePos, it1->substr(0, it1->size()-1), *currentAstNode).assign(result, remainingStr2ParsePos/*, currentAstNode*/);
                else
                    ExecuteTerminal(remainingStr2ParsePos, *it1, *currentAstNode).assign(result, remainingStr2ParsePos);
                //cs.Start();
            }
            else
            {
                //cs.Stop();
                //  verificar si es un símbolo con la estrella de klein
                if (it1->substr(it1->size()-1) == "*")
                    ExecuteNonTerminalKlein(remainingStr2ParsePos, it1->substr(0, it1->size()-1), *currentAstNode).assign(result, remainingStr2ParsePos/*, currentAstNode*/);
                else
                    ExecuteNonTerminal(remainingStr2ParsePos, *it1, *currentAstNode).assign(result, remainingStr2ParsePos);
                //cs.Start();
            }
            if (result == false)
                break;
            else
                strPosRule = remainingStr2ParsePos;
            //  si queremos recursión de cola esto tiene que estar vacío
            //  si es el último elemento de la lista, es como si estuviera vacío
        }

        if (result)
            break;
        ++it0;
        //  si queremos recursión de cola esto tiene que estar vacío
        //  si el resultado es verdadero, es como si estuviera vacío
    }
    //  si queremos recursión de cola esto tiene que estar vacío
    if (result==false)
        return mtk::make_tuple(result, str2parsePos);
    else
        return mtk::make_tuple(result, strPosRule);
}


mtk::tuple<bool, int/*, mtk::CountPtr<AST_Node_Item> */> HumbleParser::ExecuteNonTerminalKlein( int str2parsePos, const std::string& nonTerminalCode, AST_Node_Item& astNode) const
{
    int addedItems = -1;
    bool result=true;
    int remainingStr2ParsePos=str2parsePos;
    mtk::CountPtr<AST_Node_Item> astNodeBeforeFail;
    mtk::CountPtr<AST_Node_Item> currentAstNode;
    std::string nodeName(nonTerminalCode);
    //CHECK_ERRORS
    while (result)
    {
        ++addedItems;
        astNodeBeforeFail = currentAstNode;
        PREPARE_NODE
        ExecuteNonTerminal(remainingStr2ParsePos, nonTerminalCode, *currentAstNode).assign(result, remainingStr2ParsePos);
    }
    if (result==false)
    {
        if (addedItems!=0)
            astNodeBeforeFail->next = mtk::CountPtr<AST_Node_Item>();
        else
            astNode.down = mtk::CountPtr<AST_Node_Item>();
    }


    return mtk::make_tuple(true, remainingStr2ParsePos/*, astNodeBeforeFail*/);
}

mtk::tuple<bool, int/*, mtk::CountPtr<AST_Node_Item> */> HumbleParser::ExecuteTerminalKlein( int str2parsePos, const std::string& nonTerminalCode, AST_Node_Item& astNode) const
{
    int addedItems = -1;
    bool result=true;
    int remainingStr2ParsePos=str2parsePos;
    mtk::CountPtr<AST_Node_Item> astNodeBeforeFail;
    mtk::CountPtr<AST_Node_Item> currentAstNode;
    std::string nodeName(nonTerminalCode);

    while (result)
    {
        ++addedItems;
        astNodeBeforeFail = currentAstNode;
        PREPARE_NODE
        ExecuteTerminal(remainingStr2ParsePos, nonTerminalCode, *currentAstNode).assign(result, remainingStr2ParsePos);
    }
    if (result==false)
    {
        if (addedItems!=0)
            astNodeBeforeFail->next = mtk::CountPtr<AST_Node_Item>();
        else
            astNode.down = mtk::CountPtr<AST_Node_Item>();
    }
    return mtk::make_tuple(true, remainingStr2ParsePos/*, astNodeBeforeFail*/);
}



/*
    Esta versión es interesante
    Acumula todos los caracteres en el código no terminal* reduciendo significativamente el tamaño del árbol AST
    Lo malo es que no permitiría hacer transformaciones individuales
    Sería aplicable si no se hacen transformaciones
    Otra opción es poner la estrella de klein en el lado derecho de la definición de una regla terminal
mtk::tuple<bool, int, mtk::CountPtr<AST_Node_Item> > HumbleParser::ExecuteTerminalKlein( int str2parsePos, const std::string& nonTerminalCode, CountPtr<AST_Node_Item> _astNode) const
{
    int addedItems = -1;
    bool result=true;
    int remainingStr2ParsePos=str2parsePos;
    std::string finalValue;

    while (result)
    {
        ++addedItems;
        ExecuteTerminal(remainingStr2ParsePos, nonTerminalCode, *_astNode).assign(result, remainingStr2ParsePos);
        if (result)
            finalValue += _astNode->value;
    }
   _astNode->value = finalValue;
   return mtk::make_tuple(true, remainingStr2ParsePos, _astNode);
}
*/






mtk::tuple<bool, int> HumbleParser::ExecuteTerminal(const int str2parsePos, const std::string& terminalCode, AST_Node_Item& astNode) const
{
//mtk::CheckScopeTime cs("ExecuteTerminal");


    ContainerRules::const_iterator itTerminal = terminalRules.find(terminalCode);
    if (itTerminal == terminalRules.end())
        throw MTK_SS("terminal symbol [" << terminalCode <<  "] has no expansion rule");



    int remainingStr2ParsePos = str2parsePos;
    bool result = false;
    std::list< mtk::tuple <std::list<std::string> , std::string> >::const_iterator it = terminalRules.find(terminalCode)->second.begin();
    while (it!=terminalRules.find(terminalCode)->second.end())
    {
        //  constantes predefinidas     ------------------------------------------------------------
        if ((*(it->_0.begin())).substr(0, 2) == "__")
            ExecutePredefinedVar(str2parsePos,  (*(it->_0.begin())),  astNode, it->_1).assign(result, remainingStr2ParsePos);
        //  expresiones regulares      ------------------------------------------------------------
        else if ((*(it->_0.begin())).substr(0, 2) == "^("  ||  (*(it->_0.begin())).substr(0, 3) == "!^(")
            ExecuteRegularExpresion(str2parsePos,  (*(it->_0.begin())),  astNode, it->_1).assign(result, remainingStr2ParsePos);
        //  literales
        else if ((*(it->_0.begin())).substr(0, 1) == "\'"  ||  (*(it->_0.begin())).substr(0, 2) == "!\'")
            ExecuteLiteral(str2parsePos,  (*(it->_0.begin())),  astNode, it->_1).assign(result, remainingStr2ParsePos);

        else
            throw MTK_SS("terminal symbol [" << terminalCode <<  "] invalid format " <<  (*(it->_0.begin())));



        if (result)
            return mtk::make_tuple(true, remainingStr2ParsePos);

        ++it;
    }
    return mtk::make_tuple(false, str2parsePos);
}




mtk::tuple<bool, std::string>  HumbleParser::AddRule (const std::string& rule_t2)
{
    std::string rule;
    std::string transform2;
    {
        mtk::RegExp re_rt (" *(.*) *##transf2-> *(.*) *");

        if (re_rt.Match(rule_t2))
        {
            rule = mtk::s_trim(re_rt[0], ' ');
            transform2 = mtk::s_trim(re_rt[1], ' ');
        }
        else
        {
            rule = rule_t2;
        }
    }



    //  separar lados regla

    mtk::RegExp re ("^ *([^ \t]*) *::= *(.*)$");
    if (re.Match(rule))
    {
        if (IsTerminal(re[0]) == false)
        {
            //  Hay que separar las reglas e introducirlas en la lista
            mtk::vector<std::string> rightSymbols = mtk::s_split(re[1], " ");
            std::list<std::string>  lRightSymbols;
            //MTK_FOREACH (it, rightSymbols)
            for(unsigned i=0; i<rightSymbols.size(); ++i)
            {
                std::string termRule = mtk::s_trim(rightSymbols[i], ' ');
                if (termRule != "")
                    lRightSymbols.push_back(termRule);
            }
            nonTerminalRules[re[0]].push_back(
                                        mtk::make_tuple(lRightSymbols, transform2));
        }
        else
        {
            std::string toadd = mtk::s_trim(re[1], ' ');
            std::list<std::string> lTerminal;
            if (toadd[0] == '(' ||  toadd.substr(0,2) == "!(")
            {
            //  TERMINAL:  "regular expresion"
                if (toadd[0] != '!')
                    lTerminal.push_back(MTK_SS("^" << toadd/* << ".*"*/));
                else
                    lTerminal.push_back(MTK_SS("!^" << toadd.substr(1)/* << ".*"*/));
                terminalRules[re[0]].push_back ( mtk::make_tuple(lTerminal, transform2));
            }
            else if (toadd.substr(0,2) == "__"  &&   toadd.substr(toadd.size()-2,2) == "__")
            {
                //  TERMINAL:  constantes predefinidas
                lTerminal.push_back(mtk::s_trim(toadd, ' '));
                terminalRules[re[0]].push_back ( mtk::make_tuple(lTerminal, transform2));
            }
            else if ( (toadd[0] == '\''  || toadd.substr(0,2) == "!\'")  &&   toadd[toadd.size()-1] == '\'')
            {
                //  TERMINAL:  literales sin escape
                lTerminal.push_back(mtk::s_trim(toadd, ' '));
                terminalRules[re[0]].push_back ( mtk::make_tuple(lTerminal, transform2));
            }
//            else if (toadd[0] == '['  &&   toadd.substr(toadd.size()-1,1) == "]")
//            {
//                //  //  TERMINAL:  lista de caracteres
//                lTerminal.push_back(mtk::s_trim(toadd));
//                terminalRules[re[0]].push_back ( mtk::make_tuple(lTerminal, transform2));
//            }
            else
            {
                existErrorsInRules = true;
                return mtk::make_tuple(false, MTK_SS("Error adding rule. TerminalFormat {" << rule << "}   "<<  rule_t2));
            }


        }
    }
    else
    {
        existErrorsInRules = true;
        return mtk::make_tuple(false, MTK_SS("Error adding rule. Incorrect rule format {" << rule << "}   "<<  rule_t2));
    }
    return mtk::make_tuple(true, MTK_SS("ok"));
}




mtk::tuple<bool, std::string> HumbleParser::LoadRulesFromStream (std::istream& stream)
{
    Clear();
    mtk::tuple<bool, std::string> result = make_tuple(true, std::string());
    char buffer[4096];

    stream.getline(buffer, 4096);

    //  La primera regla indica el o los puntos de inicio de la gramática
    defaultInitSymbol = mtk::s_trim(buffer, ' ');

    while (stream.getline(buffer, 4096))
    {
        if (buffer[0] == '/'  &&  buffer[1]=='/')
            continue;
        if (mtk::s_trim(buffer, ' ') != "")
        {
            //result = AddRule(buffer);
            result = AddLine(buffer);
            if (result._0 == false)
                return result;
        }
    }

    return result;
}


mtk::tuple<bool, std::string> HumbleParser::LoadRulesFromString (std::string rules)
{
    mtk::tuple<bool, std::string> result = make_tuple(true, std::string());

    std::istringstream iss(rules);
    result = LoadRulesFromStream(iss);

    return result;

}


mtk::tuple<bool, std::string> HumbleParser::LoadRulesFromFile(const std::string& fileRules)
{
    mtk::tuple<bool, std::string> result = make_tuple(true, std::string());
    std::ifstream fRules(fileRules.c_str(), std::ios::in);
    result = LoadRulesFromStream(fRules);
    fRules.close();

    return result;
}



mtk::tuple<bool, std::string>
HumbleParser::AddLine (std::string line)
{
    line = mtk::s_trim(line, ' ');
    if (addingRuleMultiLine)
    {
        if (line != "")
        {
            if (line == "__endrule__")
            {
                addingRuleMultiLine = false;
                return AddRule(buildingRule);
            }
            else
            {
                buildingRule.push_back(' ');      //  es necesario porque nos dan las líneas sin códigos inservibles
                for (unsigned i=0; i<line.size(); ++i)
                {
                    char char2add = line[i];
                    if (char2add == '\r'  ||  char2add == '\n'  ||  char2add=='\t')  // no sirve para nada, no recibimos dichos códigos, lo mantengo por si acaso se cambia en el futuro
                        char2add = ' ';

                    buildingRule.push_back(char2add);
                }
                return make_tuple(true, MTK_SS("ok"));
            }
        }
        else
            return make_tuple(true, MTK_SS("ok"));
    }
    else
    {
	if (line == "__beginrule__")
	{
	    addingRuleMultiLine = true;
	    buildingRule = "";
	    return make_tuple(true, MTK_SS("ok"));
	}
	else
	    return AddRule(line);
    }
}





mtk::tuple<bool, std::string/*remaining*/, AST_Node_Item>
HumbleParser::Parse(const std::string& input, const std::string& init) const
{
//mtk::CheckScopeTime ("Parse");

    AST_Node_Item astRoot(init, "");
    astRootDebug = &astRoot;    //  debug
    try
    {
        deeperErrorParsingPos = -1;
        deeperErrorExpectedSymbols.clear();

        if (ExistErrorsInRules())
            return mtk::make_tuple(false, MTK_SS("CANNOT PARSE  there are errors in rules "), astRoot);

        bool result = false;

        int remainingStr2ParsePos;
        string2parse = input;
        ExecuteNonTerminal(0, init, astRoot).assign(result, remainingStr2ParsePos);

        std::string remainingInput = string2parse.substr(remainingStr2ParsePos);

        if (result==false  ||  remainingInput!= "")
        {
            std::ostringstream expectedSymbols;
            if (deeperErrorExpectedSymbols.size() > 0)
            {
                expectedSymbols  <<  "   expected:  ";
                for(auto it = deeperErrorExpectedSymbols.begin(); it != deeperErrorExpectedSymbols.end(); ++it)
                    expectedSymbols << " " << *it;
            }
            return mtk::make_tuple(false, MTK_SS("ERROR parsing... " << string2parse.substr(deeperErrorParsingPos, 50) << "." << expectedSymbols.str()), astRoot);
        }
        else
            return mtk::make_tuple(true, MTK_SS("ok"), astRoot);
    }
    catch(const std::string& error)
    {
            return mtk::make_tuple(false, error, astRoot);
    }
}


mtk::tuple<bool, std::string/*remaining*/, AST_Node_Item>
HumbleParser::MultiParse(const std::string& input, std::string minit) const
{

    if (minit == "")
        minit = defaultInitSymbol;
    if (minit == "")
        return mtk::make_tuple(false, MTK_SS("CANNOT PARSE  missing init symbol"), AST_Node_Item("<none>"));


    //  separar los elementos

    deeperErrorParsingPos = -1;
    deeperErrorExpectedSymbols.clear();

    if (ExistErrorsInRules())
        return mtk::make_tuple(false, MTK_SS("CANNOT PARSE  there are errors in rules "), AST_Node_Item("<none>"));

    std::string newInput = input;
    AST_Node_Item astResult("<pending>");
    mtk::RegExp re ("([^,]+)");
    while (re.GlobalMatch(minit))
    {
        bool result = false;
        std::string remainingInput;
        Parse(newInput, re[0]).assign(result, remainingInput, astResult);
        if (result==false  ||  remainingInput!= "ok")
            return mtk::make_tuple(result, remainingInput, astResult);
        astResult.ExecReplace();
        newInput =  astResult.value;
    }

    return mtk::make_tuple(true, MTK_SS("ok"), astResult);
}


void HumbleParser::Clear(void)
{
    string2parse = "";
    nonTerminalRules.clear();
    terminalRules.clear();
    existErrorsInRules = false;
    deeperErrorParsingPos = -1;
    deeperErrorExpectedSymbols.clear();
    defaultInitSymbol = "";
}









// ----------------------------------------------------------------------------------------------------------------------------
mtk::tuple<bool, int> HumbleParser::ExecutePredefinedVar(int str2parsePos, const std::string& terminalRule, AST_Node_Item& astNode, const std::string& rule2replace) const
{
    //  constantes predefinidas     ------------------------------------------------------------

//    if (str2parsePos >= int(string2parse.size()))
//        return mtk::make_tuple(false, str2parsePos);

    if (terminalRule  == "__any__")
    {
        if (str2parsePos >= int(string2parse.size()))
            return mtk::make_tuple(false, str2parsePos);
        astNode.value        = string2parse.substr(str2parsePos, 1);
        astNode.rule4Replace = rule2replace;
        return mtk::make_tuple(true, str2parsePos+1);
    }

    else if (terminalRule  == "__isalpha__")
    {
        char char2check = string2parse[str2parsePos];
        if ( isalpha(char2check) )
        {
            astNode.value        = char2check;
            astNode.rule4Replace = rule2replace;
            return mtk::make_tuple(true, str2parsePos+1);
        }
    }
    else if (terminalRule  == "__islower__")
    {
        char char2check = string2parse[str2parsePos];
        if ( islower(char2check) )
        {
            astNode.value        = char2check;
            astNode.rule4Replace = rule2replace;
            return mtk::make_tuple(true, str2parsePos+1);
        }
    }
    else if (terminalRule  == "__isupper__")
    {
        char char2check = string2parse[str2parsePos];
        if ( isupper(char2check) )
        {
            astNode.value        = char2check;
            astNode.rule4Replace = rule2replace;
            return mtk::make_tuple(true, str2parsePos+1);
        }
    }
    else if (terminalRule  == "__isdigit__")
    {
        char char2check = string2parse[str2parsePos];
        if ( isdigit(char2check) )
        {
            astNode.value        = char2check;
            astNode.rule4Replace = rule2replace;
            return mtk::make_tuple(true, str2parsePos+1);
        }
    }
    else if (terminalRule  == "__isalnum__")
    {
        char char2check = string2parse[str2parsePos];
        if ( isalnum(char2check) )
        {
            astNode.value        = char2check;
            astNode.rule4Replace = rule2replace;
            return mtk::make_tuple(true, str2parsePos+1);
        }
    }

    else if (terminalRule  == "__endl__")
    {
        char char2check = string2parse[str2parsePos];
        if ( char2check == '\n'  ||  char2check == '\r')
        {
            astNode.value        = char2check;
            astNode.rule4Replace = rule2replace;
            return mtk::make_tuple(true, str2parsePos+1);
        }
    }
    else if (terminalRule  == "__isspace__")
    {
        char char2check = string2parse[str2parsePos];
        if (isspace(char2check))
        {
            astNode.value        = char2check;
            astNode.rule4Replace = rule2replace;
            return mtk::make_tuple(true, str2parsePos+1);
        }
    }
    else if (terminalRule  == "__isspace*__")
    {
        int contador=0;
        char char2check = string2parse[str2parsePos+contador];
        while (isspace(char2check))     //  no es necesario verificar el final de cadena (\0 no es igual)
        {
            if (contador == 0)
                astNode.rule4Replace  = rule2replace;
            astNode.value        += char2check;
            contador++;
            char2check = string2parse[str2parsePos+contador];
        }
        return mtk::make_tuple(true, str2parsePos+contador);
    }
    else if (terminalRule  == "__isspace+__")
    {
        int contador=0;
        char char2check = string2parse[str2parsePos+contador];
        while (isspace(char2check))     //  no es necesario verificar el final de cadena (\0 no es igual)
        {
            if (contador == 0)
                astNode.rule4Replace  = rule2replace;
            astNode.value        += char2check;
            contador++;
            char2check = string2parse[str2parsePos+contador];
        }
        if (contador == 0)
            return mtk::make_tuple(false, str2parsePos+contador);
        else
            return mtk::make_tuple(true, str2parsePos+contador);
    }
    else if (terminalRule  == "__space_tab__")
    {
        char char2check = string2parse[str2parsePos];
        if (char2check== '\t'  ||  char2check== ' ')
        {
            astNode.value        = char2check;
            astNode.rule4Replace = rule2replace;
            return mtk::make_tuple(true, str2parsePos+1);
        }
    }
    else
        throw  MTK_SS("unknown constant [" << terminalRule  << "]"  <<  std::endl);


    return mtk::make_tuple(false, str2parsePos);
}


mtk::tuple<bool, int> HumbleParser::ExecuteRegularExpresion(int str2parsePos, const std::string& terminalRule, AST_Node_Item& astNode, const std::string& rule2replace) const
{
    int  remainingStr2ParsePos = str2parsePos;
    std::string re2eval;
    bool positivEval = true;
    if ( terminalRule[0] != '!')
    {
        re2eval = terminalRule;
        positivEval = true;
    }
    else
    {
        re2eval = terminalRule.substr(1);
        positivEval = false;
    }

    mtk::RegExp reTerminal (re2eval);
    if (remainingStr2ParsePos > int(string2parse.size()))
        std::cerr << "ERROR... " << std::endl;


    if (positivEval)
    {
        if (reTerminal.Match( string2parse.substr(remainingStr2ParsePos) ))
        {
            astNode.value        = reTerminal[0];
            remainingStr2ParsePos += int(astNode.value.size());
            astNode.rule4Replace = rule2replace;
            return mtk::make_tuple(true, remainingStr2ParsePos);
        }
    }
    else
    {
        if (remainingStr2ParsePos >= int(string2parse.size()))
            return mtk::make_tuple(false, remainingStr2ParsePos);
        if (reTerminal.Match( string2parse.substr(remainingStr2ParsePos) )== false)
        {
            astNode.value        = string2parse.substr(remainingStr2ParsePos, 1);
            remainingStr2ParsePos += 1;
            astNode.rule4Replace = rule2replace;
            return mtk::make_tuple(true, remainingStr2ParsePos);
        }
    }
    return mtk::make_tuple(false, str2parsePos);
}



mtk::tuple<bool, int> HumbleParser::ExecuteLiteral(int str2parsePos, const std::string& _terminalRule, AST_Node_Item& astNode, const std::string& rule2replace) const
{
    if (str2parsePos > int(string2parse.size()))
        std::cerr << "ERROR... " << std::endl;
    int  remainingStr2ParsePos = str2parsePos;
    std::string terminalRule;
    bool positivEval = true;
    if ( _terminalRule[0] != '!')
    {
        terminalRule = _terminalRule.substr(1, _terminalRule.size()-2);
        positivEval = true;
    }
    else
    {
        terminalRule = _terminalRule.substr(2, _terminalRule.size()-3);
        positivEval = false;
    }
    if (str2parsePos+int(terminalRule.size()) > int(string2parse.size()))
        return mtk::make_tuple(false, str2parsePos);



    std::string substring2parse =  string2parse.substr(remainingStr2ParsePos, terminalRule.size());
    if (positivEval)
    {
        if (terminalRule ==  substring2parse)
        {
            astNode.value        = substring2parse;
            remainingStr2ParsePos += int(astNode.value.size());
            astNode.rule4Replace = rule2replace;
            return mtk::make_tuple(true, remainingStr2ParsePos);
        }
    }
    else
    {
        if (remainingStr2ParsePos >= int(string2parse.size()))
            return mtk::make_tuple(false, remainingStr2ParsePos);
        if (terminalRule !=  substring2parse)
        {
            astNode.value        = string2parse.substr(remainingStr2ParsePos, 1);
            remainingStr2ParsePos += 1;
            astNode.rule4Replace = rule2replace;
            return mtk::make_tuple(true, remainingStr2ParsePos);
        }
    }
    return mtk::make_tuple(false, str2parsePos);
}


std::list<std::string>   HumbleParser::GetTerminalRules(void)const
{
    std::list<std::string> result;
    for(auto it = terminalRules.begin(); it != terminalRules.end(); ++it)
    {
        result.push_back(it->first);
    }
    return result;
}

std::list<std::string>   HumbleParser::GetNonTerminalRules(void)const
{
    std::list<std::string> result;
    for(auto it = nonTerminalRules.begin(); it != nonTerminalRules.end(); ++it)
    {
        result.push_back(it->first);
    }
    return result;
}



};  //  namespace mtk {
