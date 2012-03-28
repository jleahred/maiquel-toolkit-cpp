#include <iostream>

#include "support/integer_compactor.h"

#include "support/misc.h"
#include "support/alarm.h"
#include "support/mtk_string.h"



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



int main (void)
{
    //  very small example
    {
        mtk::integer_compactor   ic;
        mtk::integer_DEcompactor idec;


        std::cout << "ic.push(-1234567890).push(0).push(100);" << std::endl;
        ic.push(-1234567890).push(0).push(100);
        std::string  buffer = ic.get_buffer();
        for(unsigned i=0;i<buffer.size();++i)
            std::cout << "  " << int(buffer[i]);
        std::cout << std::endl;
        idec.set_buffer(buffer);
        std::cout << "  "  <<  idec.pop_int32_t();
        std::cout << "  "  <<  idec.pop_int32_t();
        std::cout << "  "  <<  idec.pop_int32_t();
        std::cout << std::endl;
    }


    std::cout << "TESTING SIZES..."  << std::endl;
    {
        mtk::integer_compactor  ic;
        for(int repeat=0; repeat<500; ++repeat)
        {
            int max_numb = 127;
            for(int  n_bytes_max = 1;  n_bytes_max<=4; ++n_bytes_max)
            {
                max_numb *= 127;
                for(int i=1; i<100;++i)
                {
                    int val_bytes = 0;
                    for(int j=0; j<i; ++j)
                    {
                        int val = mtk::rand()%max_numb;
                        val_bytes += get_size(val)+1;
                        ic.push(val);
                    }
                    size_t total_size = val_bytes + 1 + (i-1)/4  +  (i%4 ? 4 - i%4 : 0);

                    size_t size = ic.get_buffer().size();
                    if(total_size == size)
                            std::cout << "." << std::flush;
                    else
                    {
                        std::cout << "added " << i << "  error expected size " << total_size  << "  received size  " <<  size  << std::endl;
                        return -1;
                    }
                }
            }
        }
    }

    std::cout << "TESTING I/O..."  << std::endl;
    {
        mtk::integer_compactor       ic;
        mtk::integer_DEcompactor     iDEc;

        for(int repeat=0; repeat<500; ++repeat)
        {
            {
                std::srand(repeat);
                int max_numb = 127;
                for(int  n_bytes_max = 1;  n_bytes_max<=4; ++n_bytes_max)
                {
                    max_numb *= 127;
                    for(int i=1; i<100;++i)
                    {
                        for(int j=0; j<i; ++j)
                        {
                            int number_to_insert = std::rand()%max_numb;
                            ic.push(number_to_insert);
                        }
                    }
                }
            }

            {
                iDEc.set_buffer(ic.get_buffer());
                std::srand(repeat);
                int max_numb = 127;
                for(int  n_bytes_max = 1;  n_bytes_max<=4; ++n_bytes_max)
                {
                    max_numb *= 127;
                    for(int i=1; i<100;++i)
                    {
                        for(int j=0; j<i; ++j)
                        {
                            const int number_to_insert = std::rand()%max_numb;
                            const int readed = iDEc.pop_int32_t();
                            if(readed != number_to_insert)
                            {
                                std::cout << "error   repeat " << repeat  << "  i " << i << "  j " << j <<  "  readed " <<  readed << "  expected " <<  number_to_insert << std::endl;
                                return  -1;
                            }
                            else
                                std::cout << "." << std::flush;
                        }
                    }
                }
            }




        }
    }


    std::cout << std::endl;
    return 0;
}


void  mtk::AlarmMsg(const mtk::Alarm& )
{

}

 
