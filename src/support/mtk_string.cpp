#include <ctype.h>      //  tolower para bcb  gcc no lo necesita??
#include "mtk_string.h"
#include "support/count_ptr.hpp"
#include "support/re/RegExp.h"



#include <math.h>




#include "mtk_double.h"
#include "date_time.h"
#include "fixed_number.h"

//std::ostringstream __oss_mtk_ss__;

typedef
        std::list<
                    mtk::tuple<
                        mtk::CountPtr<std::ostringstream> ,
                        mtk::dtDateTime
                    >
        >    t_list_MTK_SS;
mtk::CountPtr<t_list_MTK_SS> l_os_stack;

//  previus to gcc4
//std::ostringstream& __internal_GetOsStringStream2(void)
//{
//    if (l_os_stack.isValid() == false)
//        l_os_stack = mtk::make_cptr(new t_list_MTK_SS() );
//
//    //  verificación de tamaño y limpieza (si corresponde)
//    if (l_os_stack->size() != 0   &&   l_os_stack->size() % 50 == 0)
//    {
//        mtk::AlarmMsg(mtk::Alarm("IDT::SS getos", "stack too big", mtk::alPriorError, mtk::alTypeNoPermisions));
//        {
//            t_list_MTK_SS::iterator it = l_os_stack.get2()->begin();
//            while (it != l_os_stack.get2()->end())
//            {
//                int removed_count =0;
//                if (it->_1 < mtk::dtNowLocal()-mtk::dtSeconds(30) )
//                {
//                    ++removed_count;
//                    it = l_os_stack.get2()->erase(it);
//                }
//                else
//                    ++it;
//                if (removed_count > 0)
//                    mtk::AlarmMsg(mtk::Alarm("IDT::SS getos", "removed from stack old items", mtk::alPriorError, mtk::alTypeNoPermisions));
//            }
//        }
//    }
//
//
//    l_os_stack->push_back(mtk::make_tuple(mtk::make_cptr( new std::ostringstream()), mtk::dtNowLocal()));
//    return *(l_os_stack->back()._0);
//}

std::string  __internal_GetAndRelease2(std::basic_ostream <char, std::char_traits<char> >& os)
{
    if (os != *(l_os_stack->back()._0.get2()))
        throw mtk::Alarm(MTK_HERE, "string",  "top on stack wrong (multithread?)", mtk::alPriorError, mtk::alTypeNoPermisions);
    mtk::CountPtr<std::ostringstream> temp = l_os_stack->back()._0;
    l_os_stack->pop_back();
    return temp->str();
}

namespace mtk {



    std::string     s_trim    (const std::string&    s , char char2remove)
    {
        std::string::size_type pos1 = s.find_first_not_of(char2remove);
        if (pos1==std::string::npos)    //  todo son char2remove
            return "";
        std::string::size_type pos2 = s.find_last_not_of (char2remove);
        return (
                    s.substr(
                            pos1,
                            pos2==std::string::npos ? s.length()-1 : pos2-pos1+1
                    )
        );
    }

    std::string s_trim (const std::string& s, const std::string& chars2remove)
    {
        std::string::size_type pos1 = s.find_first_not_of(chars2remove);
        std::string::size_type pos2 = s.find_last_not_of(chars2remove);

        if (pos1==std::string::npos)    //  todo son char2remove
            return "";
        return (
                    s.substr(
                            pos1,
                            pos2==std::string::npos ? s.length()-1 : pos2-pos1+1
                    )
        );
    }

    std::string     s_toLower(const std::string& s)
    {
        std::string result;
        for(unsigned i=0; i<s.size(); ++i)
        {
            result.push_back( char(tolower(s[i])) );
        }
        return result;
    }

    std::string     s_toUpper(const std::string& s)
    {
        std::string result;
        for(unsigned i=0; i<s.size(); ++i)
        {
            result.push_back( char(toupper(s[i])) );
        }
        return result;
    }





    mtk::tuple<dtTimeQuantity, bool>
    s_TRY_stotq   (const std::string&    _s, const dtTimeQuantity& defVal )
    {
        //  formatos posibles...
        //      1d
        //      1d4h
        //      4h5m
        //      5m
        //      3s 895ms
        //      5s
        //      123ms
        //      3500ms

        std::string s = mtk::s_trim(_s, ' ');
        if (s.size() == 0)
            return make_tuple(defVal, false);
        try
        {
            std::istringstream i;
            int dias=0;
            int horas=0;
            int minutos=0;
            int segundos=0;
            int milisegundos=0;

            i.str(s);

            int num;
            char tempDelim;
            bool procesadoParcial = false;

            i >> num >> std::skipws >> tempDelim;

            if (tempDelim == 'd')
            {
                dias = num;
                i >> num >> std::skipws >> tempDelim;
                procesadoParcial = true;
            }

            if (tempDelim == 'h')
            {
                horas = num;
                i >> num >> std::skipws >> tempDelim;
                procesadoParcial = true;
            }

            if (tempDelim == 'm'  &&  i.peek()!='s')        //  no ms
            {
                minutos = num;
                i >> num >> std::skipws >> tempDelim;
                procesadoParcial = true;
            }

            if (tempDelim == 's')
            {
                segundos = num;
                i >> num >> std::skipws >> tempDelim;
                procesadoParcial = true;
            }

            if (tempDelim == 'm')
            {
                i >> tempDelim;
                if (tempDelim=='s')
                {
                    milisegundos = num;
                    procesadoParcial = true;
                }
            }

            //  ¿Hemos terminado?
            std::string temp;
            i >> temp;

            if (i.eof() &&  temp==""  &&  procesadoParcial)
            {
                return make_tuple(
                                dtTimeQuantity(
                                            dtDays(dias),
                                            dtHours(horas),
                                            dtMinutes(minutos),
                                            dtSeconds(segundos),
                                            dtMilliseconds(milisegundos)
                                        )
                                , true);
            }
            else
                return make_tuple(defVal, false);
        }
        catch(...)
        {
            return make_tuple(defVal, false);
        }
    }


    mtk::tuple<DateTime, bool>
    s_TRY_stodt   (const std::string&    s, const DateTime& defVal )
    {
        //  formatos posibles...
        //  2011-03-29 09:16:33.123
        //  2011-03-29

        mtk::RegExp re("^ *([12][0-9]{3})-(1[0-2]|0[1-9])-([012][0-9]|[3][01]) ([01][0-9]|[2][0-3]):([0-5][0-9]):([0-5][0-9])\\.([0-9]{3}) *$");
        if(re.Match(s))
        {
            try
            {
                return make_tuple(
                    DateTime{   dtYear(s_TRY_stoi           (re[0], -1)._0),
                                dtMonth(s_TRY_stoi          (re[1], -1)._0),
                                dtDay(s_TRY_stoi            (re[2], -1)._0),
                                dtHours(s_TRY_stoi          (re[3], -1)._0),
                                dtMinutes(s_TRY_stoi        (re[4], -1)._0),
                                dtSeconds(s_TRY_stoi        (re[5], -1)._0),
                                dtMilliseconds(s_TRY_stoi   (re[6], -1)._0)}
                    , true);
            }
            catch(...)
            {
                return make_tuple(defVal, false);
            }
        }
        else
        {
            mtk::RegExp re2("^ *([12][0-9]{3})-(1[0-2]|0[1-9])-([012][0-9]|[3][01]) *$");
            if(re2.Match(s))
            {
                try
                {
                    return make_tuple(
                        DateTime{   dtYear(s_TRY_stoi           (re2[0], -1)._0),
                                    dtMonth(s_TRY_stoi          (re2[1], -1)._0),
                                    dtDay(s_TRY_stoi            (re2[2], -1)._0) }
                        , true);
                }
                catch(...)
                {
                    return make_tuple(defVal, false);
                }
            }
        }
        return make_tuple(defVal, false);
    }








mtk::vector<std::string> s_split (
                                const std::string&  s,
                                const std::string&  separator
                            )
{
    mtk::vector<std::string> result;
    size_t current_pos = 0;
    size_t prev_pos    = 0;

//  esto no funciona en 64bits (debería)
//    while ( (current_pos = s.find(separator, prev_pos+1)) != std::string::npos) {
    while ( (current_pos = s.find(separator, prev_pos)) < s.size()) {
        result.push_back(s.substr(prev_pos, current_pos - prev_pos));
        prev_pos = current_pos+separator.length();
    };
    result.push_back(s.substr(prev_pos, s.length()-prev_pos));

    return result;
}



mtk::tuple<double, bool> s_TRY_stod(const std::string&    _s, double defVal )
{
    std::string s = mtk::s_trim(_s, ' ');
    if (s.size() == 0)
        return make_tuple(defVal, false);

    std::istringstream i;

    i.str(s);
    double d = defVal;
    i >> d;

    if (i.eof())
        return make_tuple(d, true);
    else
        return make_tuple(defVal, false);
}

mtk::tuple<int, bool> s_TRY_stoi(const std::string&    _s, int    defVal )
{
    std::string s = mtk::s_trim(_s, ' ');
    if (s.size() == 0)
        return make_tuple(defVal, false);

    std::istringstream is;

    is.str(s);
    int i = defVal;
    is >> i;

    if (is.eof())
        return make_tuple(i, true);
    else
        return make_tuple(defVal, false);
}







std::string     s_AlignLeft (const std::string& s, int size, char cFill)
{
    std::ostringstream o;
    o.width(size);
    o.fill(cFill);
    o << std::left << s;
    return o.str();
}

std::string     s_AlignRight(const std::string& s, int size, char cFill)
{
    std::ostringstream o;
    o.width(size);
    o.fill(cFill);
    o << std::right << s;
    return o.str();
}


std::string s_normalizeUTF8(const std::string& sourceString)
{
    std::string destinationString;
    unsigned char auxChar;

    for (unsigned int contador=0; contador < sourceString.size(); contador++)
    {
        auxChar=sourceString[contador];

        //Si es un caracter "especial" á, é, í, ó, ú, ñ, ü (y mayusculas)
        // se convierte a UTF8 y el resto se sustituye por "_"
        if (auxChar>127)
        {
            switch (auxChar)
            {
                case 0xE1: //'á'
                    destinationString+=char(0xC3);
                    destinationString+=char(0xA1);
                    break;
                case 0xC1: //'Á'
                    destinationString+=char(0xC3);
                    destinationString+=char(0x81);
                    break;
                case 0xE9: //'é'
                    destinationString+=char(0xC3);
                    destinationString+=char(0xA9);
                    break;
                case 0xC9: //'É'
                    destinationString+=char(0xC3);
                    destinationString+=char(0x89);
                    break;
                case 0xEA: //'í'
                    destinationString+=char(0xC3);
                    destinationString+=char(0xAD);
                    break;
                case 0xCD: //'Í'
                    destinationString+=char(0xC3);
                    destinationString+=char(0x8D);
                    break;
                case 0xF3: //'ó'
                    destinationString+=char(0xC3);
                    destinationString+=char(0xB3);
                    break;
                case 0xD3: //'Ó'
                    destinationString+=char(0xC3);
                    destinationString+=char(0x93);
                    break;
                case 0xFA: //'ú'
                    destinationString+=char(0xC3);
                    destinationString+=char(0xBA);
                    break;
                case 0xDA: //'Ú'
                    destinationString+=char(0xC3);
                    destinationString+=char(0x9A);
                    break;
                case 0xF1: //'ñ'
                    destinationString+=char(0xC3);
                    destinationString+=char(0xB1);
                    break;
                case 0xD1: //'Ñ'
                    destinationString+=char(0xC3);
                    destinationString+=char(0x91);
                    break;
                case 0xFC: //'ü'
                    destinationString+=char(0xC3);
                    destinationString+=char(0xBC);
                    break;
                case 0xDC: //'Ü'
                    destinationString+=char(0xC3);
                    destinationString+=char(0x9C);
                    break;
                default:
                    destinationString+="_";
            }
        }
        else
            destinationString+=sourceString[contador];
    }
    return destinationString;
}


};  //  namespace mtk {


