#include <iostream>

#include "support/hp/humbleparser.h"

//  Prueba de gramática LL con operador + asociativo por la izquierda

int main(int /*argc*/, char* /*argv*/[])
{
    mtk::HumbleParser  hParser;

    hParser.AddRule("   EXPR    ::=    VAL EXPR_                        ");
    hParser.AddRule("   EXPR_   ::=    add_operator VAL EXPR_           ");
    hParser.AddRule("   EXPR_   ::=    _                 ");



    hParser.AddRule("   VAL     ::=    FUNC _ ( EXPR _ )                ");
    hParser.AddRule("   VAL     ::=    _ num                            ");
    hParser.AddRule("   VAL     ::=    VAR                              ");
    hParser.AddRule("   VAR     ::=    _ id                             ");
    hParser.AddRule("   FUNC    ::=    _ id                             ");


    hParser.AddRule("   num           ::=    ([0-9]+)                     ");
    hParser.AddRule("   id            ::=    ([a-z|A-Z][0-9|a-z|A-Z|_]*)");
    hParser.AddRule("   id            ::=    (_+[0-9|a-z|A-Z]+[0-9|a-z|A-Z|_]*)");
    hParser.AddRule("   mult_operator ::=    ([\\*|\\/])                 ");
    hParser.AddRule("   add_operator  ::=    ([\\+|\\-])                  ");
    hParser.AddRule("   unaryoperator ::=    ([\\+|\\-])                  ");
    hParser.AddRule("   _             ::=    ([ |\\t]*)                    ");
    hParser.AddRule("   (             ::=    (\\()                        ");
    hParser.AddRule("   )             ::=    (\\))                        ");


    bool result;
    std::string resultTest;
    mtk::AST_Node_Item astRoot("");

    hParser.Parse(      "1+2+3+4+5",
                        "EXPR"
			).assign(result, resultTest, astRoot);

    std::cout << std::endl << result <<  "  "  <<   resultTest;

    #include "support/release_on_exit.hpp"
    return result == true ? 0 : -1;
} 


//---------------------------------------------------------------------------

//  RECEPTOR ALARMAS SALIDA GENERAL

//---------------------------------------------------------------------------

void mtk::AlarmMsg (const Alarm& alarma)
{
    std::cout << "\n\r";
    std::cout << std::endl << "ALARMA SALIDA..." << std::endl ;
    std::cout << alarma << std::endl ;
}
