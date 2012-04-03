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
    description     (desc)      :       string
    re_rule         (rer)       :       string
    n_received      (nr)        :       int
    last_notified   (lnot)      :       date_time
    frequency       (fr)        :       time_quantity
    start_time      (st)       :        time_quantity
    end_time        (et)       :        time_quantity
}


