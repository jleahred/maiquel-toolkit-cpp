#include "fsm_cli_acs.h"

#include "components/admin/admin.h"
#include "support/call_later.h"



#define SUBJECT_RESPONSE_IN(__REQUEST_INFO__)  __REQUEST_INFO__.process_location.location.client_code, __REQUEST_INFO__.process_location.location.machine, __REQUEST_INFO__.process_location.process_uuid, __REQUEST_INFO__.req_id.sess_id, __REQUEST_INFO__.req_id.req_code


#include "fsm_cli_acs.impl"