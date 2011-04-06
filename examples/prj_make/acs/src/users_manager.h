#ifndef __acs_users_manager_h__
#define __acs_users_manager_h__

#include <string>

#include "support/list.hpp"
#include "support/signalslot.hpp"



class users_manager  :  public  mtk::SignalReceptor  {
    typedef  users_manager  CLASS_NAME;

	static users_manager* ms_instance;

public:
	static users_manager* Instance();
	static void Release();
    
    
    bool        check_user_password     (const std::string& name, const std::string& key, const std::string& password);
    bool        check_user_client_code  (const std::string& name, const std::string& client_code);
    std::string decode_modif_password   (const std::string& name, const std::string& key, const mtk::list<int>& new_password);
    void        save_new_password       (const std::string& name, const std::string& password);
    

private:
	users_manager();
	~users_manager();

    bool         exists_user        (const std::string& user_name);
    std::string  get_passwordcrc32  (const std::string& user_name);

    void command_user_list  (const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_add_user   (const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_remove_user(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_user_find  (const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_resetpwd   (const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_modif_user (const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_stats      (const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);

    int num_check_passwords;
};

#endif // __acs_users_manager_h__