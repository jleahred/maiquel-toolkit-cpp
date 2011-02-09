#include <iostream>
#include "support/fixed_number.h"
#include "support/misc.h"



void  check_set_double_round_not_allowed(mtk::FixedNumber fn, double value)
{
    try
    {
        fn.SetDouble(value, mtk::fnRoundNotAllowed);

        if(mtk::Double(value) !=  fn.GetDouble())
        {
            std::cout << std::endl << "ERROR..." << std::endl;
            std::cout << fn << "  " << value << std::endl;
            exit(-1);
        }
    }catch(...)
    {
        std::cout << std::endl << "ERROR..." << std::endl;
        std::cout << fn << "  " << value << std::endl;
        exit(-1);
    }
}


int main(void)
{
    //  regresion test
    {
        std::cout << std::endl << std::endl << "regresion test"  <<  std::endl;
        std::cout << "i, dec, inc    (getdouble)" << std::endl;
        for(int dec=0; dec<=3; ++dec)
        {
            for(int inc=1; inc<=10; ++inc)
            {
                mtk::FixedNumber  fn  (mtk::fnDouble(0.), mtk::fnDec(dec), mtk::fnInc(inc));
                for(int i=-1000; i<1000; ++i)
                {
                    fn.SetDouble(i/1000.);
                    std::cout <<  i << ", " << dec << ", " << inc  <<   "    (" << fn.GetDouble() << ")"  << std::endl;
                }
            }
        }
    }

    //  testing negative positive simetry
    {
        std::cout << std::endl << std::endl << "testing negative positive simetry"  <<  std::endl;
        std::cout << "i, dec, inc    (+double, -double)" << std::endl;
        for(int dec=0; dec<=3; ++dec)
        {
            for(int inc=1; inc<=10; ++inc)
            {
                mtk::FixedNumber  fn  (mtk::fnDouble(0.), mtk::fnDec(dec), mtk::fnInc(inc));
                mtk::FixedNumber  fn2 (mtk::fnDouble(0.), mtk::fnDec(dec), mtk::fnInc(inc));
                for(int i=-1000000; i<=0; ++i)
                {
                    fn.SetDouble(i/1000.);
                    fn2.SetDouble(-1.*i/1000.);
                    if(fn.GetDouble()*(-1.) != fn2.GetDouble())
                    {
                        std::cout << "ERROR  "  <<  i << ", " << dec << ", " << inc  <<   "    (" << fn2.GetDouble() << ", " << fn.GetDouble() << ")"  << std::endl;
                        return -1;
                    }
                    static int counter=0; ++counter;  if(counter%1000000 == 0)  std::cout << "." << std::flush;
                }
            }
        }
        std::cout << "OK" << std::endl;
    }


    //  simetric test
    {
        std::cout << std::endl << std::endl << "simetric test"  <<  std::endl;
        std::cout << "i, dec, inc    (fn.GetIntCode(), generated_number)" << std::endl;
        int pow10=1;
        for(int dec=0; dec<=4; ++dec)
        {
            if(dec!=0)
                pow10 *= 10;
            else
                pow10 =1;
            for(int inc=1; inc<=10; ++inc)
            {
                mtk::FixedNumber  fn  (mtk::fnDouble(0.), mtk::fnDec(dec), mtk::fnInc(inc));
                for(int i=-1000000; i<=1000000; ++i)
                {
                    double generated_number = double(i*inc) / double(pow10);
                    fn.SetDouble(generated_number);
                    if(double(fn.GetIntCode()) - (generated_number*pow10)  > 0.0000001)
                    {
                        std::cout << "ERROR  "  <<  i << ", " << dec << ", " << inc  <<   "    (" << int(generated_number*pow10) << ", " << fn.GetIntCode() << ")"  << std::endl;
                        return -1;
                    }
                    static int counter=0; ++counter;  if(counter%3000000 == 0)  std::cout << "." << std::flush;
                }
            }
        }
        std::cout << "OK" << std::endl;
    }


    {
        //  correct values, assigned value and original value has to be the same
        std::cout << std::endl << std::endl << "testing check_set_double_round_not_allowed"  <<  std::endl;
        std::list<int> inc_list = {1, 2, 5, 10 };
        std::cout << "regresion with   mtk::fnRoundNotAllowed  correct values" << std::endl;
        for(auto it_inc=inc_list.begin(); it_inc!=inc_list.end(); ++it_inc)
        {
            int inc = *it_inc;
            double pow10=1;
            for(int dec=0; dec<=4; ++dec)
            {
                for(int i=0; i<100000; ++i)
                {
                    mtk::FixedNumber  fn(mtk::fnDouble(0.), mtk::fnDec(dec), mtk::fnInc(inc));

                    //  same value
                    check_set_double_round_not_allowed(fn, (i*inc)/pow10);
                    check_set_double_round_not_allowed(fn, (-1*i*inc)/pow10);
                    //  very close value
                    check_set_double_round_not_allowed(fn, (i*inc)/pow10+0.000000000000001);
                    check_set_double_round_not_allowed(fn, (i*inc)/pow10-0.000000000000001);
                    check_set_double_round_not_allowed(fn, (-1*i*inc)/pow10+0.000000000000001);
                    check_set_double_round_not_allowed(fn, (-1*i*inc)/pow10-0.000000000000001);

                    static int counter=0; ++counter;  if(counter%100000 == 0)  std::cout << "." << std::flush;
                }
                pow10 *= 10.;
            }
        }
        std::cout << "OK" << std::endl;
    }

    return 0;
}



//---------------------------------------------------------------------------

//  RECEPTOR ALARMAS SALIDA GENERAL

//---------------------------------------------------------------------------

void mtk::AlarmMsg (const Alarm& alarma)
{
        std::cout << "\n\r";
        std::cout << std::endl << "ALARMA SALIDA..." << alarma <<  std::endl ;
        std::cout << alarma << std::endl ;
}

