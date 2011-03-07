/*
 * This component will work with clients and servers
 *
 *      * sending the enter, exit and keepalive messages
 *      * giving the connections to other pieces
 *      * sending the alarms to the network
 * 
 *      * dealing with admin commands
 *      * receiving and monitoring the central keepalive
 *      * local fluct control
 *      * generating logs files
 *      * sending alarm stats frecuently with stats
 *      * basic preconfigured commands
 * 
 * */







#ifndef  __mtk_admin__
#define  __mtk_admin__



#include "components/msg_common.h"


namespace mtk {
      namespace admin {
          
        void                                init(const std::string& config_file);  
        
        mtk::CountPtr< mtk::qpid_session >  get_qpid_session(const std::string&  url_for, const std::string& address);
        
        std::string                         get_location        (void);
        std::string                         get_machine         (void);
        std::string                         get_session         (void);     //  with server role, this is the process name
        std::string                         get_url             (const std::string& url_for);

        std::string                         get_request_code    (void);     

        mtk::msg::sub_request_info          client_get_request_info (void);
        
        
        mtk::CountPtr<mtk::Signal<const mtk::Alarm&> >       get_signal_alarm_error_critic(void);
        mtk::CountPtr<mtk::Signal<const mtk::Alarm&> >       get_signal_alarm_nonerror    (void);
        
        
        
        
        
        
        
        mtk::CountPtr<mtk::Signal<const std::string& /*cmd*/, const std::string& /*params*/, const std::string& /*rqcode*/> >
                                            register_command(const std::string& group, const std::string& name, const std::string& description);
      
      };     //namespace admin {
      
      
      
    void AlarmMsg (const Alarm& error);
    

void  __internal_admin_nevercall_me____release_on_exit(void);
#define     RELEASE__internal_admin_nevercall_me____release_on_exit   mtk::__internal_admin_nevercall_me____release_on_exit();

      
};  //namespace mtk {


#endif 
