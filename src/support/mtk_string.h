#ifndef idSoporteStringH
#define idSoporteStringH



#include "tuples.hpp"

#include "vector.hpp"
#include <sstream>


//  en situaciones muy excepcionales, esto no funciona bien
//extern std::ostringstream __oss_mtk_ss__;
//#define MTK_SS(__REDIRECT__)  (std::cout << std::endl << "==MTK_SS==  <(" << #__REDIRECT__  << ")>" << std::endl , (__oss_mtk_ss__.str(""), __oss_mtk_ss__) << __REDIRECT__, __oss_mtk_ss__.str())

//std::ostringstream& __internal_GetOsStringStream2(void);
//std::string  __internal_GetAndRelease2(std::basic_ostream <char,std::char_traits<char> >&);
//#define MTK_SS(__REDIRECT__)  (__internal_GetAndRelease2(__internal_GetOsStringStream2() << __REDIRECT__ ))


//  PENDING GCC4
//  esta solución es la mejor pero no está soportada por compiladores gcc3.x
#define MTK_SS(__REDIRECT__, ...)          \
    ({      \
        std::ostringstream __oss_mtk_ss__##__VA_ARGS__;      \
        __oss_mtk_ss__ << __REDIRECT__;         \
        __oss_mtk_ss__.str();                   \
    })



namespace mtk {


    //  CONVERSIONES de tipos base


    mtk::tuple<double, bool>
    s_TRY_stod                (const std::string&    s, double defVal );

    mtk::tuple<int, bool>
    s_TRY_stoi                (const std::string&    s, int    defVal );





    //  CONVERSIONES de tipos librería mtk
    //  de tipo  -->  string  (see MTK_SS)
    class dtTimeQuantity;
    class DateTime;
    class FixedNumber;
    class Double;



    //  de string  -->  tipo
    mtk::tuple<dtTimeQuantity, bool>
    s_TRY_stotq   (const std::string&    s, const dtTimeQuantity& defVal );

    mtk::tuple<DateTime, bool>
    s_TRY_stodt   (const std::string&    s, const DateTime& defVal );






    //  UTILIDADES

    std::string     s_trim    (const std::string&    s , char char2remove);
    std::string     s_trim    (const std::string&    s , const std::string& chars2remove);


    mtk::vector<std::string> s_split (
                                    const std::string&  s,
                                    const std::string&  separator
                                );


    std::string     s_toLower(const std::string& s);
    std::string     s_toUpper(const std::string& s);


    std::string     s_AlignLeft (const std::string& s, int size, char cFill=' ');
    std::string     s_AlignRight(const std::string& s, int size, char cFill=' ');

    std::string     s_normalizeUTF8(const std::string& sourceString);

};  //  namespace mtk {


#endif






