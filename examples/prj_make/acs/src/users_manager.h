#ifndef __acs_users_manager_h__
#define __acs_users_manager_h__

#include <string>

#include "support/list.hpp"
#include "support/signalslot.hpp"



namespace users_manager  
{

    void        init                    (void);
    void        save_user_list          (void);

    
    bool        check_user_password     (const std::string& name, const std::string& key, const std::string& password);
    bool        check_user_client_code  (const std::string& name, const std::string& client_code);
    std::string decode_modif_password   (const std::string& name, const std::string& key, const mtk::list<int>& new_password);
    void        save_new_password       (const std::string& name, const std::string& password);
    
    

};

#endif // __acs_users_manager_h__
