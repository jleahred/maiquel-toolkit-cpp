BEGIN_INIT

INCLUDES = [ ]
NAMESPACES = ['mon', 'msg']

END_INIT



//---------------------------------------------------------------------
//        
//
//---------------------------------------------------------------------


sub_rule [< KEY:re_rule >]
{
    re_rule         (rer)       :       string
    frequency       (fr)        :       time_quantity
    n_received      (nr)        :       int
    description     (desc)      :       string
    start_time      (st)       :        time_quantity
    end_time        (et)       :        time_quantity
    last_notified   (lnot)      :       date_time
}


