#ifndef __INTEGER_COMPACTOR_H__
#define __INTEGER_COMPACTOR_H__

#include <sys/types.h>
#include <string>




namespace mtk {
//---------------------------------------------------------------------------


const  int   integer_compactor_buffer_size = 1024*100;


class  integer_compactor
{
public:

    integer_compactor(void);

    integer_compactor&  push(int8_t   val)    {  return push(int32_t    (val));  }
    integer_compactor&  push(int16_t  val)    {  return push(int32_t    (val));  }
    integer_compactor&  push(int32_t  val);


    std::string  get_buffer (void);
    void         clear      (void);


private:
    int8_t                  buffer[integer_compactor_buffer_size];
    int                     lenght;

    int                     counter_temp;
    int32_t                 temp[4];

    int8_t                  get_sizes(void);
    void                    write_temps(void);
};



class  integer_DEcompactor
{
public:

    integer_DEcompactor(void);

    int8_t   pop_int8_t (void);
    int16_t  pop_int16_t(void);
    int32_t  pop_int32_t(void);


    void         set_buffer (const std::string&  _buffer);


private:
    int8_t                  buffer[integer_compactor_buffer_size];
    int                     lenght;
    int                     position;

    int                     counter_temp;
    int32_t                 temp[4];

    void                    write_temps(void);
};




//---------------------------------------------------------------------------
};      //namespace mtk {








#endif // __INTEGER_COMPACTOR_H__
