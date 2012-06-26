//  <1>
BEGIN_INIT

NAMESPACES = ['testing']

END_INIT



LimitPosition   [< >]      // <2>
{
   buy_sell (bs)   :  string       [optional]        // <3>
   price    (pr)   :  fix_num      [recomended]
   quantity (qt)   :  fix_num      [mandatory]
}




RQ_NW_LS  [< DEPRECIATED:2012-02-05,  RT:2, SUBJ:hola.pajaarito, QE:testing >]   // <4>
{
   //  single fields
   order_id (oid)  :  string       [mandatory]
   cli_ref  (cr)   :  string       [mandatory]

   // External nested submessage          <5>
   position (pos)  : LimitPosition [mandatory]

   // External not nested submessage     <6>
   positionnn      : LimitPosition




   //  group of fields not nested on "wired" message   <7>
   control_fields_  [< >]
   {
      clock_id (ci)       :  date_time    [mandatory]
      secuence (sec)      :  int32        [mandatory]
   }

   //  group of fields nested on "wired" message    <8>
   product_code (pc)   [< >]
   {
      market        (mk)       :  string       [mandatory]
      product_code  (pr)       :  string       [mandatory]
      aditional_code(ac)       :  string       //[mandatory]  by default is mandatory  <9>
   }

    [names]       (ns)          :  string            // <10>
    [postitions]  (poss)        :  LimitPosition     // <11>
}



LimitPositionChild   [< I:LimitPosition, RT:2,  >]      // <12>
{
   new_field   (nf)  : string

  #send  [{  std::cout  << "#send " << this->new_field << std::endl; }]    //    <13>
}
