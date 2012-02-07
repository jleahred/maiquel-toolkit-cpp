BEGIN_INIT

NAMESPACES = ['mtk', 'msg']

END_INIT




//---------------------------------------------------------------------
//        CONTROL FIELDS
//---------------------------------------------------------------------
sub_control_fields [< >]
{
    message_type        (mt)        :   string

    control_fluct_key   (cfk)       :   string          //  if empty, it will be ignored. Clients will have to start with '_'
    sent_date_time      (sdt)       :   date_time

    depreciated_on      (do)        :   mtk::DateTime   [optional]
}


