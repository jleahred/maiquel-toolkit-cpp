/*
 * This component will work with clients and servers
 *
 *      * sending the enter, exit and keepalive messages
 *      * giving the connections to other pieces
 *      * sending the alarms to the network
 *      * dealing with admin commands
 *      * basic preconfigured commands
 *      * sending alarm stats frecuently with stats
 *      * receiving and monitoring the central keepalive
 * 
 *      * local fluct control
 *      * generating logs files
 * 
 * */







#ifndef  __mtk_admin__
#define  __mtk_admin__



#include "components/msg_common.h"
#include "components/admin/msg_admin.h"
#include "components/acs/msg_acs.h"



namespace mtk {
      namespace admin {
          
        void                                                init            (const std::string& config_file_name,
                                                                             const std::string& app_name,
                                                                             const std::string& app_version,
                                                                             const std::string& app_description,
                                                                             const std::string& app_modifications);  
        
        bool                                                is_production(void);
        
        mtk::CountPtr< mtk::qpid_session >                  get_qpid_session(const std::string&  url_for, const std::string& address);
        
        mtk::msg::sub_process_info                          get_process_info            (void);
         
        //std::string                                         get_session                     (void);     //  with server role, this is the process name
        
        
        std::string                                         get_url                         (const std::string& url_for);

        mtk::msg::sub_request_info                          get_request_info                (void);
        
        
        mtk::CountPtr<mtk::Signal<const mtk::Alarm&> >      get_signal_alarm_error_critic   (void);
        mtk::CountPtr<mtk::Signal<const mtk::Alarm&> >      get_signal_alarm_nonerror       (void);
        
        mtk::CountPtr<mtk::Signal<const mtk::dtTimeQuantity&> > get_signal_no_receiving_messages(void);
        mtk::CountPtr<mtk::Signal<> >                           get_signal_receiving_messages_back(void);
        
        
        mtk::Nullable<std::string>                          get_config_property(const std::string& path);
        void                                                set_config_property(const std::string& path, const std::string&  property_value);
        
        
        
        //  to be call from acs_client
        void client_login_ok_confirmation   (const mtk::acs::msg::res_login::IC_login_response_info& client_login_confirmation);
        void client_logout_confirmation     (const std::string& description);
        
        
        
        
        
        
        
        mtk::CountPtr<mtk::Signal<const std::string& /*cmd*/, const std::string& /*params*/, mtk::list<std::string>& /*response lines*/> >
                                            register_command(   const std::string& group, 
                                                                const std::string& name, 
                                                                const std::string& description, 
                                                                bool confirmation_requiered=false);
                                                                
                                                                
        mtk::Signal<>*           get_signal_admin_ready(void);
      
      };     //namespace admin {
      
      
      
    void AlarmMsg (const Alarm& error);
    

void  __internal_admin_nevercall_me____release_on_exit(void);
#define     RELEASE__internal_admin_nevercall_me____release_on_exit   mtk::__internal_admin_nevercall_me____release_on_exit();


#define  MTK_ADMIN_REGISTER_GLOBAL_COMMANDS(__METHOD_NAME__) \
    struct __register_global_commands__    \
    {    \
        __register_global_commands__()     \
        {    \
            mtk::admin::get_signal_admin_ready()->connect(__METHOD_NAME__);    \
        }    \
    };    \
    __register_global_commands__ rc;


      
};  //namespace mtk {


#endif 
