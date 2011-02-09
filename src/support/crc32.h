#ifndef mtk_crc32H
#define mtk_crc32H


#include <string>



namespace mtk {

unsigned int crc32(std::string str);
std::string crc32_as_string (const std::string& str);




};






#endif
