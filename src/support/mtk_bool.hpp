#ifndef BOOL_HPP_INCLUDED
#define BOOL_HPP_INCLUDED





namespace mtk {
//---------------------------------------------------------------------------



/*  Bool with default value true or false
 *  usage:   Bool<true>  var;   //  this var will be initialized with true
 */ 

template <bool>
class Bool;


template<>
class Bool<true> {
    bool  value;
    friend class Bool<false>;
    
public:
    Bool() : value(true) {};
    Bool(const Bool<false>& b);

    Bool(bool _value) : value(_value) {};
    operator bool () const      { return value; }
    Bool operator = (bool p)    { value = p; return *this; }
};

template <>
class Bool<false> {
    bool  value;
    friend class Bool<true>;
    
public:
    Bool() : value(false) {};
    Bool(const Bool<true>& b);

    Bool(bool _value) : value(_value) {};
    operator bool () const      { return value; }
    Bool operator = (bool p)    { value = p; return *this; }
};


inline Bool<true>::Bool(const Bool<false>& b) : value(b.value) {};
inline Bool<false>::Bool(const Bool<true>& b) : value(b.value) {};



inline Bool<false> make_bool(bool b)
{
    return Bool<false>(b);
}




//---------------------------------------------------------------------------
};      //namespace mtk {








#endif // BOOL_HPP_INCLUDED
