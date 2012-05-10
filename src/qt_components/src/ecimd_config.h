#ifndef ECIMD_CONFIG_H
#define ECIMD_CONFIG_H


#include <string>


namespace  ecimd_config
{

    void  set_user_name(const std::string&  user_name);

    bool blinking           (void);
    bool market_orders      (void);
    bool historic_execs     (void);
    bool loss_win           (void);
}




#endif // ECIMD_CONFIG_H
