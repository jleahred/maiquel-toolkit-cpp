#ifndef MTK_CONTAINERS_VECTOR_GUARD
#define MTK_CONTAINERS_VECTOR_GUARD

//  maintainer: 



#include <vector>

#include "alarm.h"
#include <sstream>



namespace mtk {
//---------------------------------------------------------------------------

template<typename T>
class vector
{
public:

	vector() {};
	//	sirven constructor de copia y operador de asignación


    T& 					operator[] 		( unsigned n );
	const T&			operator[] 		( unsigned n ) const;
	void 				clear 			(void);
	unsigned long 		size			() const;
	bool 				empty 			() const;
	const T& 			at 				( unsigned n ) const;
    T& 					at 				( unsigned n );
    T& 					front 			(void);
	const T& 			front 			(void) const;
	T& 					back 			(void);
	const T& 			back 			(void) const;
	void 				pop_back 		(void);
	void 				push_back 		(const T& x);

    void                reserve         (size_t n);


//	iterator insert ( iterator position, const T& x )
//    void insert ( iterator position, unsigned n, const T& x )
//	template <class InputIterator>
//    void insert ( iterator position, InputIterator first, InputIterator last )
//iterator erase ( iterator position )
//iterator erase ( iterator first, iterator last )

private:
	std::vector<T>  ivector;
	void check_limits(unsigned n, const char* text) const;		//	ponemos esto aquí sólo para ocultarlo

};





//		IMPLEMENTACIÓN	----------------------------------------------------------


template <typename T>
void   vector<T>::check_limits 		( unsigned n, const char* text ) const
{
	if (n>=ivector.size())
    {
        std::ostringstream oss;
        oss << "out of limits " << "ivector.size() " << ivector.size() << " < " << n << " on... " << text;
		throw mtk::Alarm(MTK_HERE, std::string("out of limits ") +
                    oss.str() , mtk::alPriorError);
    }
}



template <typename T>
T&   vector<T>::operator[] 		( unsigned n )
{
	check_limits(n, "operator[]");
	return  ivector[n];
}


template <typename T>
const T&  vector<T>::operator[] 		( unsigned n ) const
{
	check_limits(n, "const operator[]");
	return  ivector[n];
}


template <typename T>
void vector<T>::clear 			(void)
{
	ivector.clear();
}



template <typename T>
unsigned long 	vector<T>::size			() const
{
    return ivector.size();
}

template <typename T>
bool    vector<T>::empty 			() const
{
    return ivector.empty();
}

template <typename T>
const T&  vector<T>::at 				( unsigned n ) const
{
    check_limits(n , "at");
    return ivector.at(n);
}

template <typename T>
T& vector<T>::at 				( unsigned n )
{
    check_limits(n , "at");
    return ivector.at(n);
}

template <typename T>
T& 	vector<T>::front 			(void)
{
    check_limits(0 , "front");
    return ivector.front();
}

template <typename T>
const T&  vector<T>::front 			(void) const
{
    check_limits(0 , "front");
    return ivector.front();
}

template <typename T>
T& 	vector<T>::back 			(void)
{
    check_limits(0 , "back");
    return ivector.back();
}

template <typename T>
const T&  vector<T>::back 			(void) const
{
    check_limits(0 , "back");
    return ivector.back();
}


template <typename T>
void 	vector<T>::pop_back 		(void)
{
    check_limits(0 , "pop_back");
    ivector.pop_back();
}

template <typename T>
void 	vector<T>::push_back 		(const T& x)
{
    ivector.push_back(x);
}



template <typename T>
void 	vector<T>::reserve         (size_t n)
{
    ivector.reserver(n);
}





//---------------------------------------------------------------------------
}      //  namespace mtk {


#endif
