

//  Este include se debe poner sólo antes de terminar el programa
//  de hacerlo antes, atente a las consecuencias
//  Tampoco es imprescindible hacer esta llamada

//  Este fichero existe sólo para realizar una limpieza total y dejar el informe de valgrind limpio
//  en memory leaks


//  se podría poner una llamada automática en cada fichero que necesita un relelease
//  pero eso no sirve porque el orden de llamada podría ser relevante


#ifdef RELEASE___internal_call_later_nevercall_me_release_on_exit
    RELEASE___internal_call_later_nevercall_me_release_on_exit  
#endif


#ifdef RELEASE_Timer__internal_nevercall_me_release_on_exit
    RELEASE_Timer__internal_nevercall_me_release_on_exit
#endif


#ifdef RELEASE__internal_containersupport_nevercall_me____release_on_exit
    RELEASE__internal_containersupport_nevercall_me____release_on_exit
#endif




//#ifdef RELEASE_____internal_admin_nevercall_me_release_on_exit
//    RELEASE_____internal_admin_nevercall_me_release_on_exit
//#endif


//#ifdef RELEASE_____internal_sabcli_nevercall_me_release_on_exit 
//    RELEASE_____internal_sabcli_nevercall_me_release_on_exit 
//#endif


//#ifdef RELEASE_______internal_nevercall_me_release_on_exit_request_response
//    RELEASE_______internal_nevercall_me_release_on_exit_request_response
//#endif


//#ifdef RELEASE_______internal_nevercall_me_release_on_exit_request_response 
//    RELEASE_______internal_nevercall_me_release_on_exit_request_response
//#endif