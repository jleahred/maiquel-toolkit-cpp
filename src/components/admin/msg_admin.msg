BEGIN_INIT

NAMESPACES = ['mtk', 'admin', 'msg']
INCLUDES   = ['#include "../msg_common.h"', '#include "../msg_common_support.h"', '#include "msg_admin_support.h"']

END_INIT



/////////////////////////////////////////////////////////////////////////////////
//
//      These messages will work on  ADMCLI or ADMSRV  addresses
//      Out messages->    ADM.<cli_code>.<machine_code>....
//      In  messages->    ADM.CIMD....
//
/////////////////////////////////////////////////////////////////////////////////



sub_process_location  [<V:0>]
{
    location        (lc)  : string
    machine         (mc)  : string
    process_name    (pn)  : string
    process_uuid    (pi)  : string
}



//-------------------------------------------------------------------
//  ENTER, KeepAlive, EXIT
//
//  messages from client to cimd system (monitoring)
//  or processes to monitoring
//-------------------------------------------------------------------



enter  [< V:0, SUBJ:ADM.CIMD.ENTER >]
{
    process_location    (pl)    :   sub_process_location
    ka_interval_send    (ks)    :   time_quantity
    ka_interval_check   (kc)    :   time_quantity
}


keep_alive  [< V:0, SUBJ:ADM.CIMD.KA >]
{
    process_location    (pl)    :   sub_process_location
    ka_interval_send    (ks)    :   time_quantity
    ka_interval_check   (kc)    :   time_quantity
}

exit  [< V:0, SUBJ:ADM.CIMD.EXIT >]
{
    process_location    (pl)    :   sub_process_location
    reason              (r)     :   string
}



//-------------------------------------------------------------------
//  ALARMS
//-------------------------------------------------------------------


alarm  [< V:0,  SUBJ:ADM.CIMD.ALARMS >]
{
    process_location    (pl)    :   sub_process_location
    code_source         (cs)    :   string
    message             (ms)    :   string
    priority            (p)     :   mtk::alEnPriority
    type                (t)     :   mtk::alEnType
    dateTime_generated  (dt)    :   date_time
    alarm_id            (ai)    :   int16
}






//-------------------------------------------------------------------
//  COMMANDS
//-------------------------------------------------------------------

command  [< V:0, SUBJ:ADM.${proc_loc__destination.location}.${proc_loc__destination.machine}.${proc_loc__destination.process_name}.${proc_loc__destination.process_uuid}.COMMAND >]
{
    request_code            (ri)    :   mtk::msg::sub_request_r

    proc_loc__destination   (pd)    :   sub_process_location
    command_line            (c)     :   string                  //  command and params
}


sub_command_rd [< V:0 >]
{
    text                (t)     :   string
}

command_response  [< V:0,  SUBJ:ADM.CIMD.COMMRES.${response_info.request_code} >]
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

central_keep_alive  [< V:0, SUBJ:ADM.ALL.KA >]
{
    process_location    (pl)    :   sub_process_location
    ka_interval_send    (ks)    :   time_quantity
    ka_interval_check   (kc)    :   time_quantity
}

