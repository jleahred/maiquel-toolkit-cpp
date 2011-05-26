BEGIN_INIT

NAMESPACES = ['mtk', 'admin', 'msg']
INCLUDES   = ['#include "../msg_common.h"', '#include "../msg_common_support.h"', '#include "msg_admin_support.h"', '#include "../acs/msg_acs.h"']

END_INIT



/////////////////////////////////////////////////////////////////////////////////
//
//      
//      Out messages->    ADM.<cli_code>.<machine_code>....
//      In  messages->    ADM.CIMD....
//
/////////////////////////////////////////////////////////////////////////////////





//-------------------------------------------------------------------
//  ENTER, KeepAlive, EXIT
//
//  messages from client to cimd system (monitoring)
//  or processes to monitoring
//-------------------------------------------------------------------



pub_enter  [< V:0, SUBJ:ADM.CIMD.ENTER >]
{
    process_info        (pi)    :   mtk::msg::sub_process_info
    ka_interval_send    (ks)    :   time_quantity
    ka_interval_check   (kc)    :   time_quantity
}


pub_keep_alive_srv  [< V:0, SUBJ:ADM.CIMD.KA >]
{
    process_info        (pi)    :   mtk::msg::sub_process_info
    ka_interval_send    (ks)    :   time_quantity
    ka_interval_check   (kc)    :   time_quantity
}

pub_keep_alive_clients  [< V:0, I:pub_keep_alive_srv,  SUBJ:ADM.CIMD.KA >]
{
    //  aditional info for ACS  (hot registration)
    login_confirmation  (lc)    :   mtk::acs::msg::res_login::IC_session_info
}


pub_exit  [< V:0, SUBJ:ADM.CIMD.EXIT >]
{
    process_info        (pi)    :   mtk::msg::sub_process_info
    reason              (r)     :   string
}



//-------------------------------------------------------------------
//  ALARMS
//-------------------------------------------------------------------


pub_alarm  [< V:0,  SUBJ:ADM.CIMD.ALARMS >]
{
    process_info        (pi)    :   mtk::msg::sub_process_info
    code_source         (cs)    :   string
    subject             (sb)    :   string
    message             (ms)    :   string
    priority            (p)     :   mtk::alEnPriority
    type                (t)     :   mtk::alEnType
    dateTime_generated  (dt)    :   date_time
    alarm_id            (ai)    :   int16
}






//-------------------------------------------------------------------
//  COMMANDS
//-------------------------------------------------------------------

req_command  [< V:0, SUBJ:ADM.${proc_info__destination.location.client_code}.${proc_info__destination.location.machine}.${proc_info__destination.process_name}.${proc_info__destination.process_uuid}.COMMAND >]
{
    request_info            (ri)    :   mtk::msg::sub_request_info

    proc_info__destination  (pd)    :   mtk::msg::sub_process_info
    command_line            (c)     :   string                  //  command and params
}


sub_command_rd [< V:0 >]
{
    text                (t)     :   string
}

res_command  [< V:0,  SUBJ:ADM.CIMD.COMMRES.${response_info.request_info.process_info.process_uuid}.${response_info.request_info.req_id.req_code} >]
{
    response_info       (ri)    :   mtk::msg::sub_r_response
    response_data       (rd)    :   sub_command_rd
}


//-------------------------------------------------------------------
//  central keep alive 
//
//  messages from system to clients
//  or system to server processes
//
//  it will be sent by houselight
//-------------------------------------------------------------------

pub_central_keep_alive  [< V:0, SUBJ:ADM.ALL.KA >]
{
    process_info        (pi)    :   mtk::msg::sub_process_info
    ka_interval_send    (ks)    :   time_quantity
    ka_interval_check   (kc)    :   time_quantity
}

