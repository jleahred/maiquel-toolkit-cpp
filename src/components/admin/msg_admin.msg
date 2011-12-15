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




pub_enter  [< QE:ALL_GS, SUBJ:GS.MON.${cli_srv}.ENTER >]
{
    cli_srv             (c_s)   :   string      //  "CLI"  or "SVR"

    process_info        (pi)    :   mtk::msg::sub_process_info
    ka_interval_send    (kas)   :   time_quantity
    ka_interval_check   (kac)   :   time_quantity
}


pub_keep_alive_srv  [< QE:ALL_GS, SUBJ:GS.MON.SRV.KA >]
{
    process_info        (pi)    :   mtk::msg::sub_process_info
    ka_interval_send    (kas)   :   time_quantity
    ka_interval_check   (kac)   :   time_quantity
}

pub_keep_alive_cli  [< QE:ALL_GS, I:pub_keep_alive_srv,  SUBJ:GS.MON.CLI.KA >]
{
    //  aditional info for ACS  (hot registration)
    login_confirmation  (lgc)    :   mtk::acs::msg::res_login::IC_session_info
}


pub_exit  [< QE:ALL_GS, SUBJ:GS.MON.${cli_srv}.EXIT >]
{
    cli_srv             (c_s)   :   string      //  "CLI"  or "SVR"

    process_info        (pi)    :   mtk::msg::sub_process_info
    reason              (r)     :   string
}







//-------------------------------------------------------------------
//  ALARMS
//-------------------------------------------------------------------


pub_alarm  [< QE:ALL_GS,  SUBJ:GS.MON.${cli_srv}.ALARM >]
{
    cli_srv             (c_s)   :   string      //  "CLI"  or "SVR"

    process_info        (pi)    :   mtk::msg::sub_process_info
    code_source         (cs)    :   string
    subject             (sbj)   :   string
    message             (msg)   :   string
    priority            (p)     :   mtk::alEnPriority
    type                (ty)    :   mtk::alEnType
    dateTime_generated  (dtg)   :   date_time
    alarm_id            (ai)    :   int16
}







//-------------------------------------------------------------------
//  COMMANDS
//-------------------------------------------------------------------


req_command2  [<  >]
{
    request_info            (rqi)   :   mtk::msg::sub_request_info
    sender_broker_code      (sbc)   :   string

    proc_info__destination  (pd)    :   mtk::msg::sub_process_info
    command_line            (cl)    :   string                  //  command and params
}

req_command_srv  [< I:req_command2, QE:ALL_GS, SUBJ:SYS.${sender_broker_code}.MON.${proc_info__destination.location.broker_code}.${proc_info__destination.location.machine}.${proc_info__destination.process_name}.${proc_info__destination.process_uuid}.COMMAND >]
{
}

req_command_cli  [< I:req_command2, QE:ALL_GS, SUBJ:CLI.${proc_info__destination.location.broker_code}.${proc_info__destination.location.machine}.${proc_info__destination.process_name}.${proc_info__destination.process_uuid}.COMMAND >]
{
}


sub_command_rd [< >]
{
    text                (txt)       :   string
}

res_command  [< QE:ALL_GS, SUBJ:GS.MON.${response_info.request_info.process_info.process_uuid}.${response_info.request_info.req_id.req_code}.RSCOMM >]
{
    response_info       (rsi)   :   mtk::msg::sub_r_response
    response_data       (rsd)   :   sub_command_rd
}


//-------------------------------------------------------------------
//  central keep alive
//
//  messages from system to clients
//  or system to server processes
//
//  it will be sent by houselight
//-------------------------------------------------------------------

pub_central_keep_alive  [< QE:ALL_GS, SUBJ:ALL.${process_info.location.broker_code}.MON.LHKA >]
{
    process_info        (pi)    :   mtk::msg::sub_process_info
    ka_interval_send    (kas)   :   time_quantity
    ka_interval_check   (kac)   :   time_quantity
    is_production       (prd)   :   bool
}

