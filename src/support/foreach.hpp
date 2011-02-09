#ifndef mtkFOREACHH
#define mtkFOREACHH



/**
    Solución para GCC
    No funciona con Borland
    No es tan completo como la solución de Boost o c++0x



    Ejemplo...

    std::vector<int>                vint;
    std::list  <int>                lint;
    std::map   <int, std::string>   mint;


    for (int i=0; i<10; i++) {
        vint.push_back(3);
        lint.push_back(4);
    }
    mint[1] = "uno";
    mint[2] = "dos";
    mint[3] = "tres";
    mint[4] = "cuatro";
    mint[5] = "cinco";




    MTK_FOREACH(a, vint) {
        std::cout << "  .." << *a;
    };

    MTK_FOREACH(b, lint) {
        std::cout << "  .." << *b;
    };


    MTK_FOREACH(c, mint) {
        std::cout << "  .." << c->first << "  "  << c->second;
    };




*/


//  MTK_FOREACH




#ifdef __GNUC__
    #define MTK_FOREACH( i, c )\
      typedef __typeof__( c ) c##_CONTAINERTYPE;\
      for( c##_CONTAINERTYPE::iterator i = c.begin(); i != c.end(); ++i )

    #define MTK_FOREACH_CONTAINER_POINTER( i, c )\
      typedef __typeof__( *c ) c##_CONTAINERTYPE;\
      for( c##_CONTAINERTYPE::iterator i = c->begin(); i != c->end(); ++i )



    #define MTK_FOREACH_CONST_ITERATOR( i, c )\
      typedef __typeof__( c ) c##_CONTAINERTYPE;\
      for( c##_CONTAINERTYPE::const_iterator i = c.begin(); i != c.end(); ++i )


#else
    #error "Macro FOREACH sOlo compila con GCC"
#endif

namespace mtk {


};  //  namespace mtk {


#endif


