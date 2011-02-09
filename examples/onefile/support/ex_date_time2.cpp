

        //      E J E M P L O S      DE       U S O



#include <iostream>

#include "support/date_time.h"
#include "support/alarm.h"



int main(void) {

    bool resultOk = true;

    mtk::dtTimeQuantity  tq1  (mtk::dtDays(100));
    mtk::dtTimeQuantity  tq2 = mtk::dtDays(4);

    if (
            tq1
                !=
            tq2 + mtk::dtDays(96)
        )
    {
      std::cout << std::endl <<   "Error al comprobar  suma de dÃ­as 1";
      resultOk = false;
    }


    //      esto no compila --------------------------
//     if (
//             tq1
//                 !=
//             mtk::dtDays(96) + tq2
//         )
//         std::cout << std::endl <<   "esto no compila";


    if (
            mtk::dtTimeQuantity(
                                mtk::dtDays         (4  ),
                                mtk::dtHours        (3  ),
                                mtk::dtMinutes      (8  ),
                                mtk::dtSeconds      (10 ),
                                mtk::dtMilliseconds (987)
                    )
                !=
            mtk::dtTimeQuantity(mtk::dtHours(3))
                              + mtk::dtDays         (4  )
                              + mtk::dtMinutes      (8  )
                              + mtk::dtSeconds      (10 )
                              + mtk::dtMilliseconds (987)
        )
    {
        std::cout << std::endl <<   "Error al comprobar  suma de dÃ­as 2";
        resultOk = false;
    }



    if (
            mtk::dtTimeQuantity(
                        mtk::dtTimeQuantitySerialNumber(3.5)
                    )       //  3.5 dÃ­as
                !=
            mtk::dtTimeQuantity(    mtk::dtDays         (3  ),
                                    mtk::dtHours        (12 ),
                                    mtk::dtMinutes      (0  ),
                                    mtk::dtSeconds      (0  ),
                                    mtk::dtMilliseconds (0  )
                    )
        )
    {
        std::cout << std::endl <<   "Error al comprobar  suma de dÃ­as 3";
        resultOk = false;
    }



            //  dos milisegundo de diferencia
    if (
            mtk::dtTimeQuantity(
                        mtk::dtTimeQuantitySerialNumber(3.5)
                    )       //  3.5 dÃ­as
                ==
            mtk::dtTimeQuantity(    mtk::dtDays         (3  ),
                                    mtk::dtHours        (12 ),
                                    mtk::dtMinutes      (0  ),
                                    mtk::dtSeconds      (0  ),
                                    mtk::dtMilliseconds (2  )
                    )
        )
    {
        std::cout << std::endl <<   "Error al comprobar  suma de dÃ­as 3.5";
        resultOk = false;
    }


            //  ATENCIÓN un milisegundo de diferencia se considera igual
    if (
            mtk::dtTimeQuantity(
                        mtk::dtTimeQuantitySerialNumber(3.5)
                    )       //  3.5 dÃ­as
                !=
            mtk::dtTimeQuantity(    mtk::dtDays         (3  ),
                                    mtk::dtHours        (12 ),
                                    mtk::dtMinutes      (0  ),
                                    mtk::dtSeconds      (0  ),
                                    mtk::dtMilliseconds (1  )
                    )
        )
    {
        std::cout << std::endl <<   "Error al comprobar  suma de dÃ­as 3.6";
        resultOk = false;
    }



            //  MÃ¡s breve
    if (
            mtk::dtTimeQuantity(
                        mtk::dtTimeQuantitySerialNumber(3.5)
                    )       //  3.5 dÃ­as
                !=
            mtk::dtTimeQuantity(  mtk::dtDays         (3  ))
                                + mtk::dtHours        (12 )
        )
    {
        std::cout << std::endl <<   "Error al comprobar  suma de dÃ­as 4";
        resultOk = false;
    }





                //  2 dÃ­as y medio son... 60 horas
    if (
            mtk::dtTimeQuantity(
                        mtk::dtTimeQuantitySerialNumber(2.5)
                    )       //  3.5 dÃ­as
                !=
            mtk::dtTimeQuantity(  mtk::dtHours        (60  ))
        )
    {
        std::cout << std::endl <<   "Error al comprobar  suma de dÃ­as 5";
        resultOk = false;
    }



    if (
            mtk::dtTimeQuantity(
                        mtk::dtTimeQuantitySerialNumber(2.5)
                    )       //  3.5 dÃ­as
                !=
            mtk::dtHours        (60  )
        )
    {
        std::cout << std::endl <<   "Error al comprobar  suma de dÃ­as 5.5";
        resultOk = false;
    }




                //  un dÃ­a y medio  son...   2160 minutos
    if (
            mtk::dtTimeQuantity(
                        mtk::dtTimeQuantitySerialNumber(1.5)
                    )       //  3.5 dÃ­as
                !=
            mtk::dtTimeQuantity(  mtk::dtMinutes      (2160 ))
        )
    {
        std::cout << std::endl <<   "Error al comprobar  suma de dÃ­as 6";
        resultOk = false;
    }



    if (
            mtk::dtTimeQuantity(
                        mtk::dtTimeQuantitySerialNumber(1.5)
                    )       //  3.5 dÃ­as
                !=
            mtk::dtMinutes      (2160  )
        )
    {
        std::cout << std::endl <<   "Error al comprobar  suma de dÃ­as 6.5";
        resultOk = false;
    }




    //  Trabajando con momentos concretos

        //  Esto no compila, no tiene sentido sumar dos fechas concretas

//     mtk::DateTime dtNC (
//             mtk::DateTime (
//                         mtk::dtYear (2008),
//                         mtk::dtMonth(3   ),
//                         mtk::dtDay  (15  )

//                     )
//                 +
//             mtk::dtDateTime (
//                         mtk::dtYear (2008),
//                         mtk::dtMonth(3   ),
//                         mtk::dtDay  (1   )

//                     )
//     );




        //  Esto no compila, la diferencia entre dos fechas es un TimeQuantity,
        //  no una fecha
//     mtk::DateTime dtNC (
//             mtk::dtDateTime (
//                         mtk::dtYear (2008),
//                         mtk::dtMonth(3   ),
//                         mtk::dtDay  (15  )

//                     )
//                 -
//             mtk::DateTime (
//                         mtk::dtYear (2008),
//                         mtk::dtMonth(3   ),
//                         mtk::dtDay  (1   )

//                     )
//     );



    if (
            mtk::dtDateTime (
                        mtk::dtYear (2008),
                        mtk::dtMonth(3   ),
                        mtk::dtDay  (15  )

                    )
                -
            mtk::dtDateTime (
                        mtk::dtYear (2008),
                        mtk::dtMonth(3   ),
                        mtk::dtDay  (1   )

                    )
                !=
            mtk::dtTimeQuantity(  mtk::dtDays (14)       )
        )
    {
        std::cout << std::endl <<   "Error al comprobar  fechas concretas 7";
        resultOk = false;
    }


    if (
            mtk::dtDateTime (
                        mtk::dtYear (2008),
                        mtk::dtMonth(3   ),
                        mtk::dtDay  (15  )

                    )
                -
            mtk::dtDateTime (
                        mtk::dtYear (2008),
                        mtk::dtMonth(3   ),
                        mtk::dtDay  (1   )

                    )
                !=
            mtk::dtDays (14)
        )
    {
        std::cout << std::endl <<   "Error al comprobar  fechas concretas 8";
        std::cout << std::endl <<
	    (
                        mtk::DateTime (
                                    mtk::dtYear (2008),
                                    mtk::dtMonth(3   ),
                                    mtk::dtDay  (1   )
                        )
                        +
                        mtk::dtTimeQuantity(mtk::dtDays(45))
		     ).GetMonth().WarningDontDoThisGetInternal();
        ;
        resultOk = false;
    }

    if (resultOk == false)
    {
        #include "support/release_on_exit.hpp"
        return -1;

    }
    else
    {
        std::cout << "result ok." << std::endl;
        #include "support/release_on_exit.hpp"
        return 0;
    }

}

//---------------------------------------------------------------------------

//  RECEPTOR ALARMAS SALIDA GENERAL

//---------------------------------------------------------------------------

void mtk::AlarmMsg (const Alarm& alarma)
{
        std::cout << "\n\r";
        std::cout << std::endl << "ALARMA SALIDA..." << std::endl ;
        std::cout << alarma << std::endl ;
}
