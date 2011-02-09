#include <stdlib.h>   //  exit
#include <iostream>

#include "support/hp/humbleparser.h"
#include "support/alarm.h"


//  Prueba de gramática LL con operador + asociativo por la izquierda con ast
//  y reglas de transformación para pasar a una notación postfija

void TestParsing(const mtk::HumbleParser& hParser, std::string text2Parse);


int main(int /*argc*/, char* /*argv*/[])
{
    mtk::HumbleParser  hParser;

    hParser.AddRule("   EXPR    ::=    _ VAR _ = _ EXPR                                     ##transf2-> $(EXPR)$(__endl__)copy2:$(VAR)" );
    hParser.AddRule("   EXPR    ::=    _ VAL _ EXPR'                                     ##transf2-> $(VAL)$(__endl__)$(EXPR')" );
    hParser.AddRule("   EXPR    ::=    _ unaryoperator VAL _ EXPR'                                    ##transf2-> $(VAL)$(__endl__)$(unaryoperator)$(__endl__)$(EXPR')" );
    hParser.AddRule("   EXPR    ::=    _ ( _ EXPR _ ) _ EXPR'                                    ##transf2-> $(EXPR)$(__endl__)$(EXPR')" );
    hParser.AddRule("   EXPR    ::=    _ unaryoperator ( _ EXPR _ ) _ EXPR'                                    ##transf2-> $(EXPR)$(__endl__)$(unaryoperator)$(__endl__)$(EXPR')" );
    hParser.AddRule("   EXPR'   ::=    POWER" );
    hParser.AddRule("   EXPR'   ::=    FACTOR" );
    hParser.AddRule("   EXPR'   ::=    SUM" );

    hParser.AddRule("   POWER   ::=    _ powerop _ VAL _ POWER                     ##transf2-> $(VAL)$(__endl__)$(POWER)$(__endl__)$(powerop)" );
    hParser.AddRule("   POWER   ::=    _ powerop _ VAL _ FACTOR                     ##transf2-> $(VAL)$(__endl__)$(powerop)$(__endl__)$(FACTOR)" );
    hParser.AddRule("   POWER   ::=    _ powerop _ VAL _ SUM                     ##transf2-> $(VAL)$(__endl__)$(powerop)$(__endl__)$(SUM)" );
    hParser.AddRule("   POWER   ::=    _ powerop _ ( _ EXPR _ ) _ EXPR'                     ##transf2-> $(EXPR)$(__endl__)$(mult_operator)$(__endl__)$(EXPR')" );

    hParser.AddRule("   FACTOR  ::=    _ mult_operator _ VAL _ POWER                     ##transf2-> $(VAL)$(__endl__)$(POWER)$(__endl__)$(mult_operator)" );
    hParser.AddRule("   FACTOR  ::=    _ mult_operator _ VAL _ FACTOR                     ##transf2-> $(VAL)$(__endl__)$(mult_operator)$(__endl__)$(FACTOR)" );
    hParser.AddRule("   FACTOR  ::=    _ mult_operator _ VAL _ SUM                     ##transf2-> $(VAL)$(__endl__)$(mult_operator)$(__endl__)$(SUM)" );
    hParser.AddRule("   FACTOR  ::=    _ mult_operator _ ( _ EXPR _ ) _ EXPR'                     ##transf2-> $(EXPR)$(__endl__)$(mult_operator)$(__endl__)$(EXPR')" );

    hParser.AddRule("   SUM     ::=    _ add_operator _ VAL _ POWER                     ##transf2-> $(VAL)$(__endl__)$(POWER)$(__endl__)$(add_operator)" );
    hParser.AddRule("   SUM     ::=    _ add_operator _ VAL _ FACTOR                     ##transf2-> $(VAL)$(__endl__)$(FACTOR)$(__endl__)$(add_operator)" );
    hParser.AddRule("   SUM     ::=    _ add_operator _ VAL _ SUM                     ##transf2-> $(VAL)$(__endl__)$(add_operator)$(__endl__)$(SUM)" );
    hParser.AddRule("   SUM     ::=    _ add_operator _ ( _ EXPR _ ) _ EXPR'                     ##transf2-> $(EXPR)$(__endl__)$(add_operator)$(__endl__)$(EXPR')" );

    hParser.AddRule("   SUM     ::=    _                 ");


    hParser.AddRule("   VAL     ::=    FUNC _ ( _ EXPR _ ) _                            ##transf2-> $(EXPR)fun/1:$(FUNC)");
    hParser.AddRule("   VAL     ::=    FUNC _ ( _ EXPR _ , _ EXPR _ ) _                 ##transf2-> $(EXPR)$(__endl__)$(EXPR#1)fun/2:$(FUNC)");

    hParser.AddRule("   VAL     ::=    num                            ");
    hParser.AddRule("   VAL     ::=    VAR                              ");

    hParser.AddRule("   VAR     ::=    id                                               ##transf2-> var:$(id)");
    hParser.AddRule("   FUNC    ::=    id                             ");


    hParser.AddRule("   num           ::=    ([0-9]*\\.[0-9]+)                                   ##transf2-> num:$(t)");
    hParser.AddRule("   num           ::=    ([0-9]+\\.[0-9]*)                                   ##transf2-> num:$(t)");
    hParser.AddRule("   num           ::=    ([0-9]+)                                   ##transf2-> num:$(t)");
    hParser.AddRule("   id            ::=    ([a-z|A-Z][0-9|a-z|A-Z|_]*)  ");
    hParser.AddRule("   id            ::=    (_+[0-9|a-z|A-Z]+[0-9|a-z|A-Z|_]*)" );
    hParser.AddRule("   powerop       ::=    (\\^)                                        ##transf2-> fun/2:$(t)");
    hParser.AddRule("   mult_operator ::=    ([\\*|\\\\])                               ##transf2-> fun/2:$(t)");
    hParser.AddRule("   add_operator  ::=    ([\\+|\\-])                                ##transf2-> fun/2:$(t)");
    hParser.AddRule("   unaryoperator ::=    ([\\+|\\-])                                ##transf2-> fun/1:$(t)");
    hParser.AddRule("   _             ::=    ([ |\t]*)                                  ##transf2-> $(__nothing__)");
    hParser.AddRule("   (             ::=    (\\()                        ");
    hParser.AddRule("   )             ::=    (\\))                        ");
    hParser.AddRule("   ,             ::=    (,)                          ");
    hParser.AddRule("   =             ::=    (=)                          ");






    TestParsing(hParser, "1+ 2+3");
    TestParsing(hParser, "-1 +  2+ 3");
    TestParsing(hParser, "1+2+(4+5)");
    TestParsing(hParser, "1+2+(+3+(4+5))+1");
    TestParsing(hParser, "+1 +  2+ 3- x + sin ( -y) + (8+ (9+2+3))+1");
    TestParsing(hParser, "1+2+pow(2,5)");
    TestParsing(hParser, "1+2+3");
    TestParsing(hParser, "1+2*3");
    TestParsing(hParser, "1*2+3");
    TestParsing(hParser, "1*2*3");
    TestParsing(hParser, "y=x=1+2*3");
    TestParsing(hParser, "x=1+(y=2*3)");
    TestParsing(hParser, "-(2*(-(1+2)))");
    TestParsing(hParser, "1+2^3");
    TestParsing(hParser, "1+2^3^4");
    TestParsing(hParser, "1.009+.2+1.+2");
    TestParsing(hParser, "x=1+(y=2*3)");



    //  errores
//    TestParsing(hParser, "+1+2-");
//    TestParsing(hParser, "+1+2-(8+9");



    #include "support/release_on_exit.hpp"
    return 0;
}


void TestParsing(const mtk::HumbleParser& hParser, std::string text2Parse)
{
    bool result;
    std::string resultTest;
    mtk::AST_Node_Item astRoot("");
    std::cout << "text2Parse " <<  text2Parse;
    hParser.Parse(      text2Parse,
                        "EXPR"
                 ).assign(result, resultTest, astRoot);

    std::cout << std::endl << result <<  "  "  <<   resultTest;

    std::cout << std::endl << std::endl ;

    std::cout << std::endl << astRoot.value;

    //std::cout << std::endl << AST_GetStringNodes(&astRoot);
    std::cout << std::endl << std::endl;

    if (result==false)
      exit(-1);
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
