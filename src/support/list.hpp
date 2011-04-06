#ifndef __mtk_list__
#define __mtk_list__


//  maintainer: 


#include <list>

#include "container_support.h"
#include "alarm.h"





namespace mtk {





template<typename T>
class list {
public:

        class iterator   {
        public:
            friend class mtk::list<T>;
            friend class mtk::list<T>::const_iterator;
            iterator() : registered_owner(0), last_updated_container(0)  {};
            iterator&   operator++();
            iterator    operator++(int);
            bool        operator==(const iterator& it) const;
            bool        operator!=(const iterator& it) const;

            T* operator->(void);
            T& operator* (void);

        private:
            typename std::list<T>::iterator iiterator;
            typename std::list<T>::iterator i_end_iterator;
            int                             registered_owner;
            int                             last_updated_container;

            bool IsValid (void) const;
        };


        class const_iterator  {
        public:
            friend class mtk::list<T>;
            const_iterator() : registered_owner(0), last_updated_container(0)  {};
            const_iterator(const iterator& it) :
                            iiterator (it.iiterator),
                            i_end_iterator (it.i_end_iterator),
                            registered_owner(it.registered_owner),
                            last_updated_container(it.last_updated_container)
                            {
                            };
            const_iterator&     operator=(const iterator& it)
            {
                iiterator = it.iiterator;
                i_end_iterator = it.i_end_iterator;
                registered_owner = it.registered_owner;
                last_updated_container = it.last_updated_container;
                return *this;
            }


            const_iterator&     operator++();
            const_iterator      operator++(int);
            bool                operator==(const const_iterator& it) const;
            bool                operator!=(const const_iterator& it) const;

            const T* operator->(void);
            const T& operator* (void);

        private:
            typename std::list<T>::const_iterator   iiterator;
            typename std::list<T>::const_iterator   i_end_iterator;
            int                                     registered_owner;
            int                                     last_updated_container;

            bool IsValid (void) const;
        };





	list()  : registered_as(internal_for_containers::register_container(true)) {};
	~list() {  internal_for_containers::unregister_container(registered_as); };

    list(const list<T>& l);
    list<T>& operator=(const list<T>& l);




    //  iterators
    iterator            begin       ();
    const_iterator      begin       () const;
    iterator            end         ();
    const_iterator      end         () const;


    //  capacity
    bool                empty   ()  const;
    unsigned            size    ()  const;
    unsigned            max_size() const;
    void                resize  (unsigned sz, T c = T());

    //  access
    T&                  front ( );
    const T&            front ( ) const;
    T&                  back ( );
    const T&            back ( ) const;


    //  modifiers
    void                assign      ( unsigned n, const T& u );
    void                push_front  ( const T& x );
    void                pop_front   ( );
    void                push_back   ( const T& x );
    void                pop_back    ( );
    iterator            insert      ( const iterator& position, const T& x );
    void                insert      ( const iterator& position, unsigned n, const T& x );
    iterator            erase       ( const iterator& position );
    iterator            erase       ( const iterator& first, const iterator& last );
    void                clear       ( );





    //  operations
    void remove ( const T& value );
    void unique ( );
    //void merge ( list<T,std::Allocator>& x );
    void sort ( );
    void reverse ( );





private:
	std::list<T>        ilist;
    int                 registered_as;

};






//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

//		I M P L E M E N T AC I Ó N

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------


template <typename T>
list<T>::list(const list<T>& l)
  : registered_as (internal_for_containers::register_container( ilist.size()==0? true : false))
{
	ilist = l.ilist;

    if (ilist.size() !=0)
        internal_for_containers::register_container_size_change(registered_as);
}

template <typename T>
list<T>& list<T>::operator=(const list<T>& l)
{
	ilist = l.ilist;
    registered_as = internal_for_containers::register_container( ilist.size()==0? true : false);
    if (ilist.size() !=0)
        internal_for_containers::register_container_size_change(registered_as);
    return *this;
}






//  iterators
template <typename T>
bool list<T>::iterator::IsValid (void) const
{
    if (last_updated_container==0 || internal_for_containers::get_registered_container_last_size_change(registered_owner) != last_updated_container)
        return false;
    else
        return true;
}

template <typename T>
typename list<T>::iterator  list<T>::begin       ()
{
    typename list<T>::iterator it;
    it.iiterator = ilist.begin();

    it.registered_owner = registered_as;
    it.i_end_iterator = ilist.end();
    it.last_updated_container = internal_for_containers::get_registered_container_last_size_change(registered_as);  //  anotamos el momento del último cambio de tamaño del contenedor

    return it;
}


template <typename T>
typename list<T>::iterator  list<T>::end       ()
{
    typename list<T>::iterator it;
    it.iiterator = ilist.end();
    it.registered_owner = registered_as;
    it.i_end_iterator = ilist.end();
    return it;
}





template <typename T>
typename list<T>::iterator&  list<T>::iterator::operator++()
{
    if (IsValid() == false)
        throw mtk::Alarm(MTK_HERE, "list", "iterator not valid", mtk::alPriorError);

    if (i_end_iterator == iiterator)
        throw mtk::Alarm(MTK_HERE, "list", "++ on end iterator", mtk::alPriorError);

    ++iiterator;
    return *this;
}

template <typename T>
typename list<T>::iterator  list<T>::iterator::operator++(int)
{
    typename list<T>::iterator  result = *this;
    if (IsValid() == false)
        throw mtk::Alarm(MTK_HERE, "list", "iterator not valid", mtk::alPriorError);

    if (i_end_iterator == iiterator)
        throw mtk::Alarm(MTK_HERE, "list", "++ on end iterator", mtk::alPriorError);

    ++iiterator;
    return result;
}



template <typename T>
bool  list<T>::iterator::operator==(const list<T>::iterator& it) const
{
    if (registered_owner!=0  &&  it.registered_owner != 0   &&  registered_owner !=  it.registered_owner)
        throw mtk::Alarm(MTK_HERE, "list", "on different owners", mtk::alPriorError);

    return it.iiterator == iiterator;
}

template <typename T>
bool  list<T>::iterator::operator!=(const list<T>::iterator& it) const
{
    return !operator==(it);
}


template <typename T>
T* list<T>::iterator::operator->(void)
{
    if (IsValid() == false)
        throw mtk::Alarm(MTK_HERE, "list", "iterator not valid", mtk::alPriorError);

    if (i_end_iterator == iiterator)
        throw mtk::Alarm(MTK_HERE, "list", "-> on end iterator", mtk::alPriorError);

    return iiterator.operator->();
}

template <typename T>
T& list<T>::iterator::operator*(void)
{
    if (IsValid() == false)
        throw mtk::Alarm(MTK_HERE, "list", "iterator not valid", mtk::alPriorError);

    if (i_end_iterator == iiterator)
        throw mtk::Alarm(MTK_HERE, "list", "* on end iterator", mtk::alPriorError);

    return *iiterator;
}






//  const_iterators       ---------------------------------------------------
template <typename T>
bool list<T>::const_iterator::IsValid (void) const
{
    if (last_updated_container==0  ||  internal_for_containers::get_registered_container_last_size_change(registered_owner) != last_updated_container)
        return false;
    else
        return true;
}

template <typename T>
typename list<T>::const_iterator  list<T>::begin       () const
{
    typename list<T>::const_iterator it;
    it.iiterator = ilist.begin();

    it.registered_owner = registered_as;
    it.i_end_iterator = ilist.end();

    it.last_updated_container = internal_for_containers::get_registered_container_last_size_change(registered_as);  //  anotamos el momento del último cambio de tamaño del contenedor

    return it;
}


template <typename T>
typename list<T>::const_iterator  list<T>::end       ()  const
{
    typename list<T>::const_iterator it;
    it.registered_owner = registered_as;
    it.i_end_iterator = ilist.end();
    it.iiterator = ilist.end();
    return it;
}



template <typename T>
typename list<T>::const_iterator&  list<T>::const_iterator::operator++()
{
    if (IsValid() == false)
        throw mtk::Alarm(MTK_HERE, "list", "iterator not valid", mtk::alPriorError);

    if (i_end_iterator == iiterator)
        throw mtk::Alarm(MTK_HERE, "list", "++ on end iterator", mtk::alPriorError);

    ++iiterator;
    return *this;
}

template <typename T>
typename list<T>::const_iterator  list<T>::const_iterator::operator++(int)
{
    typename list<T>::const_iterator result = *this;
    if (IsValid() == false)
        throw mtk::Alarm(MTK_HERE, "list", "iterator not valid", mtk::alPriorError);

    if (i_end_iterator == iiterator)
        throw mtk::Alarm(MTK_HERE, "list", "++ on end iterator", mtk::alPriorError);

    ++iiterator;
    return result;
}


template <typename T>
bool  list<T>::const_iterator::operator==(const const_iterator& it) const
{
    if(registered_owner!=0  &&  it.registered_owner != 0   &&  registered_owner !=  it.registered_owner)
        throw mtk::Alarm(MTK_HERE, "list", "on different owners", mtk::alPriorError);

    return it.iiterator == iiterator;
}

template <typename T>
bool  list<T>::const_iterator::operator!=(const const_iterator& it) const
{
    return !operator==(it);
}


template <typename T>
const T* list<T>::const_iterator::operator->(void)
{
    if (IsValid() == false)
        throw mtk::Alarm(MTK_HERE, "list", "iterator not valid", mtk::alPriorError);

    if (i_end_iterator == iiterator)
        throw mtk::Alarm(MTK_HERE, "list", "-> on end iterator", mtk::alPriorError);

    return iiterator.operator->();
}

template <typename T>
const T& list<T>::const_iterator::operator*(void)
{
    if (IsValid() == false)
        throw mtk::Alarm(MTK_HERE, "list", "iterator not valid", mtk::alPriorError);

    if (i_end_iterator == iiterator)
        throw mtk::Alarm(MTK_HERE, "list", "* on end iterator", mtk::alPriorError);

    return *iiterator;
}




//  capacity
template <typename T>
bool   list<T>::empty   ()  const
{
    return ilist.empty();
}

template <typename T>
unsigned   list<T>::size    ()  const
{
    return unsigned(ilist.size());
}


template <typename T>
unsigned   list<T>::max_size() const
{
    return unsigned(ilist.max_size());
}


template <typename T>
void   list<T>::resize  (unsigned sz, T c)
{
    internal_for_containers::register_container_size_change(registered_as);
    ilist.resize(sz, c);
}






//  access
template<typename T>
T&       list<T>::front ( )
{
    if (size()==0)
        throw mtk::Alarm(MTK_HERE, "list", "front on empty list", mtk::alPriorError);

    return ilist.front();
}

template<typename T>
const T& list<T>::front ( ) const
{
    if (size()==0)
        throw mtk::Alarm(MTK_HERE, "list", "front on empty list", mtk::alPriorError);

    return ilist.front();
}

template<typename T>
T&       list<T>::back ( )
{
    if (size()==0)
        throw mtk::Alarm(MTK_HERE, "list", "back on empty list", mtk::alPriorError);

    return ilist.back();
}

template<typename T>
const T& list<T>::back ( ) const
{
    if (size()==0)
        throw mtk::Alarm(MTK_HERE, "list", "back on empty list", mtk::alPriorError);

    return ilist.back();
}



//  modifiers
template<typename T>
void     list<T>::assign      ( unsigned n, const T& u )
{
    internal_for_containers::register_container_size_change(registered_as);
    ilist.assign(n, u);
}

template<typename T>
void     list<T>::push_front  ( const T& x )
{
    internal_for_containers::register_container_size_change(registered_as);
    ilist.push_front(x);
}

template<typename T>
void     list<T>::pop_front   ( )
{
    if (size()==0)
        throw mtk::Alarm(MTK_HERE, "list",  "pop_front on empty list", mtk::alPriorError);
    internal_for_containers::register_container_size_change(registered_as);
    ilist.pop_front();
}

template<typename T>
void     list<T>::push_back   ( const T& x )
{
    if (internal_for_containers::get_registered_container_last_size_change(registered_as) == 0)
        internal_for_containers::register_container_size_change(registered_as);
    ilist.push_back(x);
}

template<typename T>
void     list<T>::pop_back    ( )
{
    if (size()==0)
        throw mtk::Alarm(MTK_HERE, "list", "pop_back on empty list", mtk::alPriorError);
    internal_for_containers::register_container_size_change(registered_as);
    ilist.pop_back();
}

template<typename T>
typename list<T>::iterator list<T>::insert      ( const typename list<T>::iterator& position, const T& x )
{
    if (position.registered_owner  != registered_as)
        throw mtk::Alarm(MTK_HERE, "list", "insert with extrange iterator", mtk::alPriorError);

    if (position.iiterator != position.i_end_iterator)
        if (internal_for_containers::get_registered_container_last_size_change(position.registered_owner) != position.last_updated_container)
            throw mtk::Alarm(MTK_HERE, "list", "insert with invalid iterator", mtk::alPriorError);

    internal_for_containers::register_container_size_change(registered_as);
    typename list<T>::iterator result;
    result.iiterator =  ilist.insert(position.iiterator, x);

    result.registered_owner = registered_as;
    result.last_updated_container = internal_for_containers::get_registered_container_last_size_change(registered_as);
    result.i_end_iterator = ilist.end();

    return result;
}

template<typename T>
//void     list<T>::insert      ( iterator position, unsigned n, const T& x )
void     list<T>::insert      ( const typename list<T>::iterator& position, unsigned n, const T& x )
{
    if (position.registered_owner  != registered_as)
        throw mtk::Alarm(MTK_HERE, "list", "insert with extrange iterator", mtk::alPriorError);

    if (position.iiterator != position.i_end_iterator)
        if (internal_for_containers::get_registered_container_last_size_change(position.registered_owner) != position.last_updated_container)
            throw mtk::Alarm(MTK_HERE, "list", "insert with invalid iterator", mtk::alPriorError);

    // unsigned n
    // . si n = número negativo, al ser unsigned lo transforma en el positivo sin signo y
    //                           genera un bucle largo que se puede quedar con la máquina.
    // . si n = 0, no añade nada.

	internal_for_containers::register_container_size_change(registered_as);
	ilist.insert(position.iiterator, n, x);
}

template<typename T>
typename list<T>::iterator list<T>::erase       ( const typename list<T>::iterator& position )
{
    if (position.registered_owner  != registered_as)
        throw mtk::Alarm(MTK_HERE, "list", "erase with extrange iterator", mtk::alPriorError);
    if (position.iiterator  == ilist.end())
        throw mtk::Alarm(MTK_HERE, "list", "erase over end iterator", mtk::alPriorError);
    if (position.IsValid() == false)
        throw mtk::Alarm(MTK_HERE, "list", "erase over iterator invalid", mtk::alPriorError);

    internal_for_containers::register_container_size_change(registered_as);

    typename list<T>::iterator result;
    result.iiterator = ilist.erase(position.iiterator);

    result.registered_owner = registered_as;
    result.i_end_iterator = ilist.end();
    if (ilist.size()>0)
        result.last_updated_container = internal_for_containers::get_registered_container_last_size_change(registered_as);  //  anotamos el momento del último cambio de tamaño del contenedor
    else
        result.last_updated_container = 0;        //  no tiene valor accesible

    return result;
}


template<typename T>
typename list<T>::iterator list<T>::erase       ( const typename list<T>::iterator& first, const typename list<T>::iterator& last )
{
    if (first.registered_owner  != registered_as  ||  last.registered_owner  != registered_as)
        throw mtk::Alarm(MTK_HERE, "list", "erase with extrange iterator (first or second)", mtk::alPriorError);
    if (first.iiterator  == ilist.end())
        throw mtk::Alarm(MTK_HERE, "list", "erase over end iterator (first)", mtk::alPriorError);
    if (first.IsValid() == false)
        throw mtk::Alarm(MTK_HERE, "list", "erase over iterator invalid (first)", mtk::alPriorError);

    typename list<T>::iterator result;

    if (first == last)
    {
        result = erase (first);
    }
    else
    {
        internal_for_containers::register_container_size_change(registered_as);

        typename list<T>::iterator next;
        bool bFindLastIterator = false;

        next = first;

        do
        {
            //if (next == last)
            if (next.iiterator == last.iiterator)
                bFindLastIterator = true;

            result.iiterator = ilist.erase(next.iiterator);
            result.registered_owner = registered_as;
            result.i_end_iterator = ilist.end();
            if (ilist.size()>0)
                result.last_updated_container = internal_for_containers::get_registered_container_last_size_change(registered_as);  //  anotamos el momento del último cambio de tamaño del contenedor
            else
                result.last_updated_container = 0;        //  no tiene valor accesible

            next = result;

        }
        while ((bFindLastIterator == false) && (result.iiterator != ilist.end()));


        if ((last.iiterator != ilist.end()) && (bFindLastIterator == false))
            throw mtk::Alarm(MTK_HERE, "list", "erase from first iterator to end of container (last iterator not found)", mtk::alPriorError);

    }
    return result;
}

template<typename T>
void     list<T>::clear       ( )
{
    internal_for_containers::register_container_size_change(registered_as);
    ilist.clear();
}






//  operations
template<typename T>
void list<T>::remove ( const T& value )
{
    internal_for_containers::register_container_size_change(registered_as);
    ilist.remove(value);
}

template<typename T>
void list<T>::unique ( )
{
    internal_for_containers::register_container_size_change(registered_as);
    ilist.unique();
}

//void merge ( list<T,std::Allocator>& x );
template<typename T>
void list<T>::sort ( )
{
    internal_for_containers::register_container_size_change(registered_as);
    ilist.sort();
}

template<typename T>
void list<T>::reverse ( )
{
    internal_for_containers::register_container_size_change(registered_as);
    ilist.reverse();
}










};   //namespace mtk {

#endif // __mtk_list__
