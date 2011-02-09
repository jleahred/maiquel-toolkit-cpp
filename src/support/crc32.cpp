#include "crc32.h"
#include <sstream>
#include "mtk_string.h"


namespace mtk {


unsigned int crc32(std::string cadena)
{
    unsigned int  crc;

    const int CRC32_POLY = 0xedb88320;
    static unsigned int crc32_table[256];

    if (!crc32_table[1]) {    /* if not already done, */
                       /* build table */
        int i, j;
        unsigned int c;

        for (i = 0; i < 256; ++i) {
                for (c = i, j = 8; j > 0; --j)
                        c = c & 1 ? (c >> 1) ^ CRC32_POLY : (c >> 1);
                crc32_table[i] = c;
        }
    }

    crc = 0xffffffff;       /* preload shift register, per CRC-32 spec */
    for (unsigned pos=0; pos<cadena.size() ; pos++)
        crc = (crc >> 8) ^ crc32_table[(crc ^ cadena[pos]) % 256];
    crc = ~crc;            /* transmit complement, per CRC-32 spec */


    return crc;
}


std::string crc32_as_string (const std::string& str)
{
    std::ostringstream o;
    unsigned int crc = crc32(str);

    o.fill('0');
    o.width(8);
    o << std::hex << crc;
    return s_toUpper(o.str());
}


};      //namespace mtk {
