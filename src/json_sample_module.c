#include "wrapper.h"

#include <apache2/httpd.h>
#include <apache2/http_protocol.h>
#include <apache2/http_config.h>

static int sample_handler(request_rec* req)
{
    if(strcmp(req->handler, "mod_json_sample"))
        return DECLINED;

    return serve(req);
}

static void register_hooks(apr_pool_t* pool)
{ 
    ap_hook_handler(sample_handler, NULL, NULL, APR_HOOK_MIDDLE);
}

module AP_MODULE_DECLARE_DATA mod_json_sample = {
    STANDARD20_MODULE_STUFF,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    register_hooks
};