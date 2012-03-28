#include "integer_compactor.h"

#include "support/alarm.h"
#include "support/mtk_string.h"







namespace mtk {



integer_DEcompactor::integer_DEcompactor(void)
    : lenght(0), position(0), counter_temp(4), temp{0,0,0,0}
{

}

void     integer_DEcompactor::set_buffer (const std::string&  _buffer)
{
    if(_buffer.size() > unsigned(integer_compactor_buffer_size))
        throw  mtk::Alarm(MTK_HERE, "integer_DEcompactor", MTK_SS("buffer overflow  "  << lenght), mtk::alPriorCritic, mtk::alTypeOverflow);

    for(size_t i=0; i<_buffer.size(); ++i)
        buffer[i] = _buffer[i];
    lenght = int(_buffer.size());
    position = 0;
    counter_temp = 4;
    for(int i=0; i<4; ++i)
        temp[i] = 0;
}


int32_t  integer_DEcompactor::pop_int32_t(void)
{
    if(counter_temp == 4)
        write_temps();      //  it puts counter temp to 0

    return temp[counter_temp++];
}


int8_t  get_size(int32_t   val)
//  returns number of bytes -1 necessary to save the value
{
    if(val<=127  &&  val >= -128)
        return 0;
    else if(val<=32767  &&  val >= -32768)
        return 1;
    else if(val<=8388607  &&  val >= -8388608)
        return 2;
    return 3;
}

int8_t  integer_DEcompactor::pop_int8_t(void)
{
    int32_t  result = pop_int32_t();

    if(get_size(result)+1 != 1)
        throw mtk::Alarm(MTK_HERE, "integer_DEcompactor", MTK_SS("overflow  value is bigger than a bute " << result), mtk::alPriorCritic, mtk::alTypeOverflow);
    return int8_t(result);
}

int16_t  integer_DEcompactor::pop_int16_t(void)
{
    int32_t  result = pop_int32_t();

    if(get_size(result)+1 != 2)
        throw mtk::Alarm(MTK_HERE, "integer_DEcompactor", MTK_SS("overflow  value is bigger than a bute " << result), mtk::alPriorCritic, mtk::alTypeOverflow);
    return int16_t(result);
}


void  integer_DEcompactor::write_temps(void)
{
    counter_temp = 0;
    int8_t  sizes = buffer[position];
    if(++position > lenght)
        throw mtk::Alarm(MTK_HERE, "integer_DEcompactor", MTK_SS("overflow  length " << lenght  <<  "   position " << position), mtk::alPriorCritic, mtk::alTypeOverflow);

    int8_t  sizes_temp[4]  = {  int8_t( ((sizes & 0xC0) >> 6) +1),
                                int8_t( ((sizes & 0x30) >> 4) +1),
                                int8_t( ((sizes & 0x0C) >> 2) +1),
                                int8_t( ((sizes & 0x03)     ) +1)
                        };

    for(int itemp=0; itemp<4; ++itemp)
    {
        temp[itemp] = 0;
        for(int i=0; i<sizes_temp[itemp]; ++i)
        {
            if(position > lenght)
                throw mtk::Alarm(MTK_HERE, "integer_DEcompactor", MTK_SS("overflow  length " << lenght  <<  "   position " << position), mtk::alPriorCritic, mtk::alTypeOverflow);
            if(i!=sizes_temp[itemp]-1)
                temp[itemp] += unsigned(buffer[position] & 0xFF)  << 8*i;
            else
                temp[itemp] += (buffer[position])  << 8*i;
            ++position;
        }
    }
}





integer_compactor::integer_compactor(void)
    : lenght(0), counter_temp(0), temp{0,0,0,0}
{
}



int8_t  integer_compactor::get_sizes(void)
//  returns a byte with 4 next sizes
{
    int result=0;
    int pow2=64;

    for(unsigned i=0; i<4; ++i)
    {
        result += get_size(temp[i])*pow2;
        pow2 /= 4;
    }

    return int8_t(result);
}



void      integer_compactor::write_temps(void)
{
    #define CHECK_ERROR_OVERFLOW     \
            if(lenght > integer_compactor_buffer_size)     \
                throw  mtk::Alarm(MTK_HERE, "integer_compactor", MTK_SS("buffer overflow  "  << lenght), mtk::alPriorCritic, mtk::alTypeOverflow);

    buffer[lenght++] = get_sizes();
    CHECK_ERROR_OVERFLOW

    for(int i=0; i<4; ++i)
    {
        int8_t  size = get_size(temp[i]);
        buffer[lenght++] = int8_t(temp[i] & 0xFF);
        CHECK_ERROR_OVERFLOW
        if(size >= 1)
        {
            buffer[lenght++] = int8_t((temp[i] & 0xFF00)        >>   8);
            CHECK_ERROR_OVERFLOW
        }
        if(size >= 2)
        {
            buffer[lenght++] = int8_t((temp[i] & 0xFF0000)      >>  16);
            CHECK_ERROR_OVERFLOW
        }
        if(size >= 3)
        {
            buffer[lenght++] = int8_t((temp[i] & 0xFF000000)    >>  24);
            CHECK_ERROR_OVERFLOW
        }
        temp[i]=0;
    }
    counter_temp = 0;
}

integer_compactor&     integer_compactor::push(int32_t   val)
{
    temp[counter_temp] = val;
    ++counter_temp;

    if(counter_temp == 4)
        write_temps();

    return *this;
}


std::string  integer_compactor::get_buffer (void)
{
    if(counter_temp != 0)
        write_temps();
    std::string result = std::string((char*)(buffer), lenght);
    clear();
    return result;
}

void         integer_compactor::clear      (void)
{
    lenght = 0;
    for(int i=0; i<4; ++i)
        temp[i]=0;
    counter_temp = 0;
}




//---------------------------------------------------------------------------
};      //namespace mtk {
