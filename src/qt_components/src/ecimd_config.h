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

    bool new_order_and      (void); //  new order andorra type

    //  components
    bool execs_ticker       (void);
    bool switch_money       (void);
}




#endif // ECIMD_CONFIG_H
