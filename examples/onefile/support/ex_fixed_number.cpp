 
#include <assert.h>



#include "support/fixed_number.h"


int main()
{











//        E X T E N D I D O . . .



assert (        mtk::fnExt(mtk::fnDec(5), mtk::fnInc(5)   )
                !=
                mtk::fnExt(mtk::fnDec(2), mtk::fnInc(5)    )
    );

assert (        mtk::fnExt(mtk::fnDec(2), mtk::fnInc(10)   )
                !=
                mtk::fnExt(mtk::fnDec(1), mtk::fnInc(1)    )
    );




//---------------------------------------------------------------------------

//              f n D o u b l e

//---------------------------------------------------------------------------

//  the same..
mtk::fnDouble d1 (3.4);
mtk::fnDouble d2 (3.4, mtk::fnRoundArithmetic   );

mtk::fnDouble d3 (3.4, mtk::fnRoundFloor        );
mtk::fnDouble d4 (3.4, mtk::fnRoundCeil         );
mtk::fnDouble d5 (3.4, mtk::fnRoundNotAllowed   );








//---------------------------------------------------------------------------

//              F i x e d N u m b e r

//---------------------------------------------------------------------------


    //  CONSTRUCTORES   ____________________________________________________


//  double
assert  (
            mtk::FixedNumber(
                mtk::fnDouble   (3.1415926535          ),
                mtk::fnDec      (4                     ),
                mtk::fnInc      (1                     )
            )
            ==
            mtk::FixedNumber(
                mtk::fnDouble   (3.1415926535            ,
                                 mtk::fnRoundArithmetic ),
                mtk::fnDec      (4                      ),
                mtk::fnInc      (1                      )
            )
    );

assert  (
            mtk::FixedNumber(
                mtk::fnDouble   (3.1415926535        ,
                                 mtk::fnRoundCeil   ),
                mtk::fnDec      (4                  ),
                mtk::fnInc      (1                  )
            )
            ==
            mtk::fn(        //  nombre abreviado
                mtk::fnDouble   (3.1415926535        ,
                                 mtk::fnRoundCeil   ),
                mtk::fnDec      (4                  ),
                mtk::fnInc      (1                  )
            )

        );

//  integer
assert  (
            mtk::FixedNumber(
                mtk::fnIntCode  (31416                 ),
                mtk::fnDec      (4                     ),
                mtk::fnInc      (1                     )
            )
            ==
            mtk::FixedNumber(
                mtk::fnDouble   (3.1415926535            ,
                                 mtk::fnRoundArithmetic ),
                mtk::fnDec      (4                      ),
                mtk::fnInc      (1                      )
            )

        );



        //  error en tiempo de ejecución
        //  redondeo por defecto para enteros...   notallowed
        /*
            mtk::FixedNumber(
                mtk::fnIntCode  (31416              ),
                mtk::fnDec      (4                  ),
                mtk::fnInc      (5                  )
            );
      */

assert  (
            mtk::FixedNumber(
                mtk::fnIntCode  (31415                 ),
                mtk::fnDec      (4                     ),
                mtk::fnInc      (5                     )
            )
            ==
            mtk::FixedNumber(
                mtk::fnIntCode   (31416                  ,
                                 mtk::fnRoundArithmetic ),
                mtk::fnDec      (4                      ),
                mtk::fnInc      (5                      )
            )

        );






//  fnExt
assert  (
            mtk::FixedNumber(
                mtk::fnIntCode  (31416                 ),
                mtk::fnExt (
                            mtk::fnDec      (4         ),
                            mtk::fnInc      (1         )
                           )
            )
            ==
            mtk::FixedNumber(
                mtk::fnDouble   (3.1415926535            ,
                                 mtk::fnRoundArithmetic ),
                mtk::fnExt (
                            mtk::fnDec      (4          ),
                            mtk::fnInc      (1          )
                           )
            )

        );






    //  Métodos de acceso  ________________________________________________

    //  lectura
    assert  (
                mtk::fn(mtk::fnDouble(3.14), mtk::fnDec(2), mtk::fnInc(5))
                .GetDouble()
                > 3.14
                //  == 3.15
            );


    {
    mtk::fn fn1 (mtk::fnDouble(3.14), mtk::fnDec(2), mtk::fnInc(5));

    assert (    fn1.GetExt().GetDec()       ==  2              );
    assert (    fn1.GetDouble()             >   3.14           );
    assert (    fn1.d()                     >   3.14           );
    assert (    fn1.GetExt().GetFormat()    ==  mtk::fnFNormal );



        //  escritura
    fn1.SetDouble(3.11);
    assert (    fn1.GetIntCode()            ==  310 );
    assert (    fn1.GetDouble ()            <   3.11);

    fn1.SetIntCode(39);
    assert (    fn1.GetIntCode()            ==  40 );
    assert (    fn1.GetDouble ()            >   0.39);


    mtk::fn fn2 =  fn1;
    assert (    fn1.SetDouble(3.10)         ==  fn2.SetIntCode(310)  );


    assert  (
                mtk::FixedNumber(
                    mtk::fnIntCode  (0                      ),
                    mtk::fnDec      (4                      ),
                    mtk::fnInc      (5                      )
                ).SetIntCode (31415)
                ==
                mtk::FixedNumber(
                    mtk::fnIntCode  (0                      ),
                    mtk::fnDec      (4                      ),
                    mtk::fnInc      (5                      )
                ).SetIntCode (31416, mtk::fnRoundArithmetic )

            );


            //  error en tiempo de ejecución,
            //  default round for integers, not allowed
        /*
                mtk::FixedNumber fnp = mtk::FixedNumber(
                            mtk::fnIntCode  (0                  ),
                            mtk::fnDec      (4                  ),
                            mtk::fnInc      (5                  )
                    ).SetIntCode (31416);

                mtk::FixedNumber fnp2(
                            mtk::fnIntCode  (0                  ),
                            mtk::fnDec      (4                  ),
                            mtk::fnInc      (5                  )
                    );
                fnp2.SetIntCode (31416);
          */
    }









    //  OPERADORES      ____________________________________________________

        //  relacionales
assert  (
            mtk::fn(mtk::fnDouble(3.14), mtk::fnDec(2), mtk::fnInc(5))
            >=
            mtk::fn(mtk::fnDouble(3.14), mtk::fnDec(2), mtk::fnInc(5))
            &&
            mtk::fn(mtk::fnDouble(3.14), mtk::fnDec(2), mtk::fnInc(5))
            >
            mtk::fn(mtk::fnDouble(3.0) , mtk::fnDec(2), mtk::fnInc(5))
            &&
            mtk::fn(mtk::fnDouble(3.0) , mtk::fnDec(2), mtk::fnInc(5))
            !=
            mtk::fn(mtk::fnDouble(3.14) , mtk::fnDec(2), mtk::fnInc(5))
            &&
            mtk::fn(mtk::fnDouble(3.14) , mtk::fnDec(2), mtk::fnInc(5))
            <
            mtk::fn(mtk::fnDouble(20.0) , mtk::fnDec(2), mtk::fnInc(5))
        );


            //  error en tiempo de ejecución, no son comparables
/*
assert  (
            mtk::fn(mtk::fnDouble(3.14), mtk::fnDec(2), mtk::fnInc(1))
            >=
            mtk::fn(mtk::fnDouble(3.14), mtk::fnDec(2), mtk::fnInc(5))
        );
assert  (
            mtk::fn(mtk::fnDouble(3.14), mtk::fnDec(1), mtk::fnInc(5))
            >=
            mtk::fn(mtk::fnDouble(3.14), mtk::fnDec(2), mtk::fnInc(5))
        );
*/





        //  aritméticos

mtk::fn fna (mtk::fnDouble(3.20), mtk::fnDec(2), mtk::fnInc(1));
assert  (
            ++mtk::fn(mtk::fnDouble(3.14), mtk::fnDec(2), mtk::fnInc(1))
            ==
            mtk::fn  (mtk::fnDouble(3.15), mtk::fnDec(2), mtk::fnInc(1))

            &&

            mtk::fn  (mtk::fnDouble(3.15), mtk::fnDec(2), mtk::fnInc(1))
            ==
            --mtk::fn(mtk::fnDouble(3.16), mtk::fnDec(2), mtk::fnInc(1))

            &&

            --mtk::fn(mtk::fnDouble(3.16), mtk::fnDec(2), mtk::fnInc(1))
            ==
            mtk::fn  (mtk::fnDouble(3.10), mtk::fnDec(2), mtk::fnInc(1))
            +mtk::fnTicks(5)

            &&

            mtk::fn  (mtk::fnDouble(3.10), mtk::fnDec(2), mtk::fnInc(1))
            +mtk::fnTicks(5)
            ==
            (fna-=mtk::fnTicks(5))
        );






{
    mtk::fn         fn1(mtk::fnIntCode(0),   mtk::fnDec(3), mtk::fnInc(5) );
    fn1.SetDouble(3.14);
    mtk::fn         fn2(mtk::fnDouble(3.14), mtk::fnDec(3), mtk::fnInc(5) );
    mtk::fn         fn3(mtk::fnIntCode(0),   mtk::fnDec(3), mtk::fnInc(5) );
    fn3.SetIntCode(3140);

    assert          (fn1 == fn2    &&    fn2 == fn3);
    assert          (   fn3
                        ==
                        mtk::fn(
                                mtk::fnIntCode(0),
                                mtk::fnDec(3),
                                mtk::fnInc(5)
                               ).SetIntCode(3140)
                    );
}





    #include "support/release_on_exit.hpp"
    return 0;
}




void mtk::AlarmMsg(const mtk::Alarm& al)
{
    std::cout << "ouch...: "  << al << std::endl;

}