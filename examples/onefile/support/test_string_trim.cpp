#include "support/mtk_string.h"
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------

//          M A I N

//---------------------------------------------------------------------------

#define TEST(__INPUT__, __RESULT__, __TRIM_CRITERIA__) \
    {  \
        std::string input(__INPUT__), result(__RESULT__);  \
        if (result != mtk::s_trim(input, __TRIM_CRITERIA__))  \
        {  \
            std::cout << "Failed    " << "TEST(" << #__INPUT__ << "   , " << #__RESULT__ << "  , " << #__TRIM_CRITERIA__ << "  )    on line "  << __LINE__  << std::endl;  \
            return -1;  \
        } else {  \
            std::cout << " O K      " << "TEST(" << #__INPUT__ << "   , " << #__RESULT__ << "  , " << #__TRIM_CRITERIA__ << "  )"  << std::endl;  \
        }  \
    }



int main(int /*argc*/, char** /*argv[]*/)
{
    std::cout << "Test trim functions" << std::endl;


    TEST("    a    ",       "a",    ' ')
    TEST("    a"    ,       "a",    ' ')
    TEST("a    "    ,       "a",    ' ')
    TEST(" a "      ,       "a",    ' ')
    TEST("a"        ,       "a",    ' ')

    TEST("         ",       "",    ' ')
    TEST("     "    ,       "",    ' ')
    TEST("  "       ,       "",    ' ')
    TEST(" "        ,       "",    ' ')
    TEST(""         ,       "",    ' ')

    TEST("         ",       "",    " ")
    TEST("     "    ,       "",    " ")
    TEST("  "       ,       "",    " ")
    TEST(" "        ,       "",    " ")
    TEST(""         ,       "",    " ")

    TEST("    a    ",       "a",    " ")
    TEST("    a"    ,       "a",    " ")
    TEST("a    "    ,       "a",    " ")
    TEST(" a "      ,       "a",    " ")
    TEST("a"        ,       "a",    " ")

    TEST("    a    ",       "a",    "  ")
    TEST("    a"    ,       "a",    "  ")
    TEST("a    "    ,       "a",    "  ")
    TEST(" a "      ,       "a",    "  ")
    TEST("a"        ,       "a",    "  ")

    TEST("    a    ",       "a",    "b ")
    TEST("    a"    ,       "a",    "b ")
    TEST("a    "    ,       "a",    "b ")
    TEST(" a "      ,       "a",    "b ")
    TEST("a"        ,       "a",    "b ")

    TEST("    a    ",       "a",    " b ")
    TEST("    a"    ,       "a",    " b ")
    TEST("a    "    ,       "a",    " b ")
    TEST(" a "      ,       "a",    " b ")
    TEST("a"        ,       "a",    " b ")

    TEST("    a    ",       "a",    " b")
    TEST("    a"    ,       "a",    " b")
    TEST("a    "    ,       "a",    " b")
    TEST(" a "      ,       "a",    " b")
    TEST("a"        ,       "a",    " b")

    TEST("    a    ",       "",    "a ")
    TEST("    a"    ,       "",    "a ")
    TEST("a    "    ,       "",    "a ")
    TEST(" a "      ,       "",    "a ")
    TEST("a"        ,       "",    "a ")

    TEST("    a    ",       "",    " a ")
    TEST("    a"    ,       "",    " a ")
    TEST("a    "    ,       "",    " a ")
    TEST(" a "      ,       "",    " a ")
    TEST("a"        ,       "",    " a ")

    TEST("    a    ",       "",    " a")
    TEST("    a"    ,       "",    " a")
    TEST("a    "    ,       "",    " a")
    TEST(" a "      ,       "",    " a")
    TEST("a"        ,       "",    " a")

    TEST("    a    ",       "",    "ab ")
    TEST("    a"    ,       "",    "ab ")
    TEST("a    "    ,       "",    "ab ")
    TEST(" a "      ,       "",    "ab ")
    TEST("a"        ,       "",    "ab ")

    TEST("    a    ",       "",    " ab ")
    TEST("    a"    ,       "",    " ab ")
    TEST("a    "    ,       "",    " ab ")
    TEST(" a "      ,       "",    " ab ")
    TEST("a"        ,       "",    " ab ")

    TEST("    a    ",       "",    " ab")
    TEST("    a"    ,       "",    " ab")
    TEST("a    "    ,       "",    " ab")
    TEST(" a "      ,       "",    " ab")
    TEST("a"        ,       "",    " ab")

    TEST("    a    ",       "",    "ba ")
    TEST("    a"    ,       "",    "ba ")
    TEST("a    "    ,       "",    "ba ")
    TEST(" a "      ,       "",    "ba ")
    TEST("a"        ,       "",    "ba ")

    TEST("         ",       "",    ' ')
    TEST("     "    ,       "",    ' ')
    TEST("  "       ,       "",    ' ')
    TEST(" "        ,       "",    ' ')
    TEST(""         ,       "",    ' ')

    TEST("         ",       "",    " ")
    TEST("     "    ,       "",    " ")
    TEST("  "       ,       "",    " ")
    TEST(" "        ,       "",    " ")
    TEST(""         ,       "",    " ")

    TEST("         ",       "",    "  ")
    TEST("     "    ,       "",    "  ")
    TEST("  "       ,       "",    "  ")
    TEST(" "        ,       "",    "  ")
    TEST(""         ,       "",    "  ")

    TEST("         ",       "",    "a ")
    TEST("     "    ,       "",    "a ")
    TEST("  "       ,       "",    "a ")
    TEST(" "        ,       "",    "a ")
    TEST(""         ,       "",    "a ")

    TEST("         ",       "",    " a ")
    TEST("     "    ,       "",    " a ")
    TEST("  "       ,       "",    " a ")
    TEST(" "        ,       "",    " a ")
    TEST(""         ,       "",    " a ")

    TEST("         ",       "",    " a")
    TEST("     "    ,       "",    " a")
    TEST("  "       ,       "",    " a")
    TEST(" "        ,       "",    " a")
    TEST(""         ,       "",    " a")


    TEST("    ab    ",       "a",    "b ")
    TEST("    ab"    ,       "a",    "b ")
    TEST("ab    "    ,       "a",    "b ")
    TEST(" ab "      ,       "a",    "b ")
    TEST("ab"        ,       "a",    "b ")

    TEST("    ab    ",       "a",    " b ")
    TEST("    ab"    ,       "a",    " b ")
    TEST("ab    "    ,       "a",    " b ")
    TEST(" ab "      ,       "a",    " b ")
    TEST("ab"        ,       "a",    " b ")

    TEST("    ab    ",       "a",    " b")
    TEST("    ab"    ,       "a",    " b")
    TEST("ab    "    ,       "a",    " b")
    TEST(" ab "      ,       "a",    " b")
    TEST("ab"        ,       "a",    " b")

    TEST("    ab    ",       "a",    " bb")
    TEST("    ab"    ,       "a",    " bb")
    TEST("ab    "    ,       "a",    " bb")
    TEST(" ab "      ,       "a",    " bb")
    TEST("ab"        ,       "a",    " bb")

    TEST("    ab    ",       "a",    " b b")
    TEST("    ab"    ,       "a",    " b b")
    TEST("ab    "    ,       "a",    " b b")
    TEST(" ab "      ,       "a",    " b b")
    TEST("ab"        ,       "a",    " b b")

    TEST("    a a    ",       "a a",    " ")
    TEST("    a a"    ,       "a a",    " ")
    TEST("a a    "    ,       "a a",    " ")
    TEST(" a a "      ,       "a a",    " ")
    TEST("a a"        ,       "a a",    " ")

    TEST("    a a    ",       "a a",    "  ")
    TEST("    a a"    ,       "a a",    "  ")
    TEST("a a    "    ,       "a a",    "  ")
    TEST(" a a "      ,       "a a",    "  ")
    TEST("a a"        ,       "a a",    "  ")

    TEST("    a a    ",       "a a",    "b ")
    TEST("    a a"    ,       "a a",    "b ")
    TEST("a a    "    ,       "a a",    "b ")
    TEST(" a a "      ,       "a a",    "b ")
    TEST("a a"        ,       "a a",    "b ")

    TEST("    a a    ",       "a a",    " b ")
    TEST("    a a"    ,       "a a",    " b ")
    TEST("a a    "    ,       "a a",    " b ")
    TEST(" a a "      ,       "a a",    " b ")
    TEST("a a"        ,       "a a",    " b ")

    TEST("    a a    ",       "a a",    " b")
    TEST("    a a"    ,       "a a",    " b")
    TEST("a a    "    ,       "a a",    " b")
    TEST(" a a "      ,       "a a",    " b")
    TEST("a a"        ,       "a a",    " b")

    TEST("    a a    ",       "a a",    " b b ")
    TEST("    a a"    ,       "a a",    " b b ")
    TEST("a a    "    ,       "a a",    " b b ")
    TEST(" a a "      ,       "a a",    " b b ")
    TEST("a a"        ,       "a a",    " b b ")

    return 0;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

//  RECEPTOR ALARMAS SALIDA GENERAL

//---------------------------------------------------------------------------

void mtk::AlarmMsg (const Alarm& alarm)
{
        std::cout << "\n\r";
        std::cout << std::endl << "ALARMA SALIDA..." << std::endl ;
        std::cout << alarm << std::endl ;
}