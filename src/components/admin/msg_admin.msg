BEGIN_INIT

NAMESPACES = ['mtk', 'admin', 'msg']
INCLUDES   = ['#include "../msg_common.h"', '#include "../msg_common_support.h"', '#include "msg_admin_support.h"']

END_INIT



/////////////////////////////////////////////////////////////////////////////////
//
//      These messages will work on  ADMCLI   address
//      Out messages->    ADM.<cli_code>.<machine_code>....
//      In  messages->    ADM.CIMD....
//
/////////////////////////////////////////////////////////////////////////////////



sub_admin_header  [<V:0>]
{
    location    (lc)  : string
    machine     (mc)  : string
    sent        (snt) : date_time
}



//-------------------------------------------------------------------
//  ENTER, KeepAlive, EXIT
//
//  messages from client to cimd system
//-------------------------------------------------------------------



enter  [< V:0, SUBJ:ADM.CIMD.ENTER >]
{
    header              (h)     :   sub_admin_header
    ka_interval_send    (ks)    :   time_quantity
    ka_interval_check   (kc)    :   time_quantity
}


keep_alive  [< V:0, SUBJ:ADM.CIMD.KA >]
{
    header              (h)     :   sub_admin_header
    ka_interval_send    (ks)    :   time_quantity
    ka_interval_check   (kc)    :   time_quantity
}

exit  [< V:0, SUBJ:ADM.CIMD.EXIT >]
{
    header              (h)     :   sub_admin_header
    reason              (r)     :   string
}



//-------------------------------------------------------------------
//  ALARMS
//-------------------------------------------------------------------


alarm  [< V:0,  SUBJ:ADM.CIMD.ALARMS >]
{
    header              (h)     :   sub_admin_header
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

command  [< V:0, SUBJ:ADM.${header_destination.location}.${header_destination.machine}.COMMAND >]
{
    request_code        (ri)    :   mtk::msg::sub_request_r

    header_destination  (h)     :   sub_admin_header
    command_line        (c)     :   string                  //  command and params
}


sub_command_rd [< V:0 >]
{
    header              (h)     :   sub_admin_header
    text                (t)     :   string
}

command_response  [< V:0,  SUBJ:ADM.CIMD.${response_info.request_code}.COMMRES >]
{
    response_info       (ri)    :   mtk::msg::sub_r_response
    response_data       (rd)    :   sub_command_rd
}


