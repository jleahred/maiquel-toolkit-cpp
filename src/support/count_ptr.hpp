//  Creado                  JLE
//  Modificado: 10/05/02    JLE
//---------------------------------------------------------------------------
#ifndef countPtrH
#define countPtrH
//---------------------------------------------------------------------------

#include <stdexcept>    //  run_time_error exception

//#include <iostream>     //  debug



namespace mtk {




template <class T>
class CountPtr {

private:
    T*      ptr                 ;
    int*    count               ;
    int*    deleteOn            ;
    bool    thisInstanceDelete  ;

public:
    explicit CountPtr (T* p=0)
            :     ptr                   (p)
                , count                 (new int(1))
                , deleteOn              (new int(0))
                , thisInstanceDelete    (true)
            {};

    CountPtr (const CountPtr<T>& p)
            :
                  ptr                   (p.ptr                  )
                , count                 (p.count                )
                , deleteOn              (p.deleteOn             )
                , thisInstanceDelete    (true                   )
            {
                if(isDeleted()) {
                    ++deleteOn;
                    ptr = 0;
                }
                ++*count;
            };

    CountPtr<T>& operator= (const CountPtr<T>& _cntPtr) {
        //  Al estilo boost
        //  seguro para referencias anidadas y autoreferencia
        //  muy ingenioso pero un poco rebuscado...
        
            //  ojo, supongamos que tenemos un countptr cuyo ptr es otro countptr
            //  en la llamada a liberar, podría borrarse también el countpr contenido
            //  si este es utilizado en la asignación... problemas
            //  pero es más... la expansión inline puede hacer inaccesible el _cntPtr después de liberar
        
        CountPtr<T> temp (_cntPtr);
        //  swap  temp <->  this
        swap (ptr               , temp.ptr               );
        swap (count             , temp.count             );
        swap (deleteOn          , temp.deleteOn          );
        swap (thisInstanceDelete, temp.thisInstanceDelete);
        
        return *this;
        

        /*      Mantengo el código original para que se vea la diferencia y lo rebuscado que era
        //  ojo, supongamos que tenemos un countptr cuyo ptr es otro countptr
        //  en la llamada a liberar, podría borrarse también el countpr contenido
        //  si este es utilizado en la asignación... problemas
        //  pero es más... la expansión inline puede hacer inaccesible el _cntPtr después de liberar
        CountPtr<T> cntPtr (_cntPtr);

        CountPtr<T> temp_para_transtornados_que_hagan_autoreferencia (*this);
        
        if (this == &cntPtr)
            return *this;
        liberar();

        ptr                 =   cntPtr.ptr                  ;
        count               =   cntPtr.count                ;
        deleteOn            =   cntPtr.deleteOn             ;
        thisInstanceDelete  =   true                        ;
        if(isDeleted()) {
            ++deleteOn;
            ptr = 0;
        }
        ++*count;

        return *this;
        */
    }

    virtual ~CountPtr ()  {     liberar ();     };


    T&                  operator*       (void) const    { CptrCheck();   return *ptr;       };
    T*                  operator->      (void) const    { CptrCheck();   return  ptr;       };
    T*                  get2            (void) const    { CptrCheck();   return  ptr;       };
    int                 getCount        (void) const    { return isDeleted() ? 0 : *count;};
    const int* /*const*/getCounter      (void) const    { return isDeleted() ? 0 :  count;};


    bool                isValid         (void) const    { return !isDeleted() &&  (ptr!=0);       };
    int                 getDeleteOn     (void) const    { return *deleteOn;           };
    const int* /*const*/getPtrDeleteOn  (void) const    { return  deleteOn;           };

    bool                DANGEROUS_ThisInstance_NOT_Delete (void)  {
        if (thisInstanceDelete == false)
            return false;
        else {
            thisInstanceDelete = false;
            ++*deleteOn;
            return true;
        }
    };



    bool operator== (const CountPtr<T>& cntPtr) const {
        if (ptr == cntPtr.ptr  &&  count ==  cntPtr.count)
            return true;
        else
            return false;
    }
    bool operator!= (const CountPtr<T>& cntPtr) const {
        return !(cntPtr==*this);
    }



    //  Polimorfismo ejecución basado en herencia
    template <class U>
    explicit CountPtr (const CountPtr<U>& p)
                    :   ptr                 (p.get2()                                ),
                        count               (const_cast <int*>(p.getCounter())      ),
                        deleteOn            (const_cast <int*>(p.getPtrDeleteOn())  ),
                        thisInstanceDelete  (true                                   )
            {
                if(isDeleted()) {
                    ++deleteOn;
                    ptr = 0;
                }
                ++*count;
            };
    template <class U>
    CountPtr<T>& operator= (const CountPtr<U>& _cntPtr) {
        //  Al estilo boost
        //  seguro para referencias anidadas y autoreferencia
        //  muy ingenioso pero un poco rebuscado...
        
            //  ojo, supongamos que tenemos un countptr cuyo ptr es otro countptr
            //  en la llamada a liberar, podría borrarse también el countpr contenido
            //  si este es utilizado en la asignación... problemas
            //  pero es más... la expansión inline puede hacer inaccesible el _cntPtr después de liberar
        
        CountPtr<T> temp (_cntPtr);
        //  swap  temp <->  this
        swap (ptr               , temp.ptr               );
        swap (count             , temp.count             );
        swap (deleteOn          , temp.deleteOn          );
        swap (thisInstanceDelete, temp.thisInstanceDelete);
        
        return *this;
        
        
        /*
        //  ojo, supongamos que tenemos un countptr cuyo ptr es otro countptr
        //  en la llamada a liberar, podría borrarse también el countpr contenido
        //  si este es utilizado en la asignación... problemas
        //  pero es más... la expansión inline puede hacer inaccesible el _cntPtr después de liberar
        CountPtr<U> cntPtr (_cntPtr);

        CountPtr<T> temp_para_transtornados_que_hagan_autoreferencia (*this);

        if (this == &cntPtr)
            return *this;
        liberar();

        ptr                 =   cntPtr.ptr                  ;
        count               =   cntPtr.count                ;
        deleteOn            =   cntPtr.deleteOn             ;
        thisInstanceDelete  =   true                        ;
        if(isDeleted()) {
            ++deleteOn;
            ptr = 0;
        }
        ++*count;

        return *this;
        */
    }

private:
    bool                isDeleted       (void) const    {  return *count <= *deleteOn;  };

    void CptrCheck(void) const
    {
        if (isValid() == false)                                 
            throw std::runtime_error("CountPtr pointer not valid");
    }

    void liberar(void) {
        //assert (*count>0);

        if (count) {
            bool previusDeleted = isDeleted();
            --*count;
            if (thisInstanceDelete == false)
                --*deleteOn;

            if (ptr  &&  count  &&  *count == *deleteOn  && !previusDeleted) {
                delete ptr;
                ptr = 0;
            }

            if (*count==0) {
//                if (ptr  &&  *deleteOn==0)
//                    delete ptr;
                delete count;
                count = 0;
                delete deleteOn;
                deleteOn = 0;
            }
        }
    }
    
    template<typename TS>
    void swap(TS& s1, TS& s2)
    {
        TS temp = s1;
        s1 = s2;
        s2 = temp;
    }

};
//---------------------------------------------------------------------------



/*      23/07/2008

template <class T>
class CountPtr {
private:
    T* ptr;
    int* count;
    int deleteOn;
public:
    explicit CountPtr (T* p=0)  : ptr(p), count(new int(1)), deleteOn(0)  {};
    explicit CountPtr (T* p, int WARNING_USE_WIHT_CAUTION_deleteOn)
            : ptr(p), count(new int(1))
                , deleteOn(WARNING_USE_WIHT_CAUTION_deleteOn)
            {};
    CountPtr (const CountPtr<T>& p)
                                : ptr(p.ptr), count(p.count), deleteOn(p.deleteOn) { ++*count; };
    CountPtr<T>& operator= (const CountPtr<T>& cntPtr) {
        if (ptr == cntPtr.ptr)      return *this;
        //if ((ptr != cntPtr.ptr  ||  count!=cntPtr.count) ||  ptr==0)
        //if (ptr != cntPtr.ptr)
        liberar();

        ptr = cntPtr.ptr;
        count = cntPtr.count;
        deleteOn = cntPtr.deleteOn;
        ++*count;

        return *this;
    }
    virtual ~CountPtr ()     { liberar (); };

    T&  operator* (void) const   { return *ptr;  };
    T*  operator->(void) const   { return  ptr;  };
    T*  get       (void) const   { return  ptr;  };
    int getCount  (void) const   { return *count;};
    const int* const getCounter(void) const { return count; }
    bool isDeleted(void) {  return *count <= deleteOn;  }
    int  getDeleteOn(void)  { return deleteOn; };

    bool operator== (const CountPtr<T>& cntPtr) const {
        if (ptr == cntPtr.ptr  &&  count ==  cntPtr.count)
            return true;
        else
            return false;
    }
    bool operator!= (const CountPtr<T>& cntPtr) const {
        return !(cntPtr==*this);
    }
    //  Polimorfismo ejecución basado en herencia
    template <class U>
    CountPtr (const CountPtr<U>& p)
                                :   ptr(p.get()),
                                    count(const_cast <int*>(p.getCounter())),
                                    deleteOn(p.getDeleteOn())
            { ++*count; };
    template <class U>
    CountPtr<T>& operator= (const CountPtr<U>& cntPtr) {
        if (ptr != cntPtr.ptr)
            liberar();

        ptr = cntPtr.ptr;
        count = cntPtr.count;
        deleteOn = cntPtr.deleteOn;
        ++*count;

        return *this;
    }

private:
    void liberar(void) {
        //assert (*count>0);
        if (count) {
            --*count;
            if (*count==0) {
                if (ptr  &&  deleteOn==0)
                    delete ptr;
                delete count;
                count = 0;
            }
            if (ptr  &&  count  &&  *count==deleteOn) {
                delete ptr;
            }
        }
    }
};
//---------------------------------------------------------------------------
*/


template<typename T>
CountPtr<T> make_cptr(T* ptr)
{
    if (ptr!=0)
        return CountPtr<T>(ptr);
    else
        return CountPtr<T>();
};





};   // end namespace mtk {

#endif
