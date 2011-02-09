#ifndef MTK_CHECKSCOPETIME_H
#define MTK_CHECKSCOPETIME_H


#include <map>
#include "support/tuples.hpp"








namespace mtk{



class CheckScopeTime
{
public:
    CheckScopeTime(const char* _name);
    ~CheckScopeTime();

    void Stop (void);
    void Start(void);

    static void PrintTimes      (void);

private:
    const char*     name;
    __int64         start;
    bool            running;
    static std::map<std::string, mtk::tuple<__int64, int/*contador*/, bool/*running*/> >  mNameTime;


    static void AddTime         (const char* name, __int64 tq);
    static bool RegisterStart   (const char* name);
    static void RegisterStop    (const char* name);
    static void IncrementCounter(const char* name);
};


};  // end namespace mtk
#endif // CHECKSCOPETIME_H
