BEGIN_INIT

INCLUDES = ['' ]
NAMESPACES = ['testing', 'dynamic']

END_INIT



//---------------------------------------------------------------------
//
//
//---------------------------------------------------------------------



sub_levels  [<  >]
{
    price0       (price0)       :      int32           [optional]
    quantity0    (quantity0)    :      int32           [optional]

    price1       (price0)       :      int32           [optional]
    quantity1    (quantity0)    :      int32           [optional]

    price2       (price0)       :      int32           [optional]
    quantity2    (quantity0)    :      int32           [optional]

    price3       (price0)       :      int32           [optional]
    quantity3    (quantity0)    :      int32           [optional]

    price4       (price0)       :      int32           [optional]
    quantity4    (quantity0)    :      int32           [optional]

    price5       (price0)       :      int32           [optional]
    quantity5    (quantity0)    :      int32           [optional]

}





pub_dynamic  [< QE:testing, RT:2, SUBJ:testing.DYNAMIC   >]
{
    product_name     (procut_name)   :  string
    processed        (pm)            :  bool


    value_date       (value_date)    :  date_time                   [optional]
    num_legs         (num_legs)      :  int16                       [optional]
    testing          (testing)       :  string                      [optional]

    bids             (bids)          :  sub_levels                  [optional]
    asks             (asks)          :  sub_levels__qpid_map        [optional]

}

