#include <apache2/httpd.h>
#include <apache2/http_protocol.h>
#include <apache2/http_config.h>

static int sample_handler(request_rec* req)
{
    if(!req->handler || strcmp(req->handler, "dimkush"))
        return DECLINED;

        ap_set_content_type(req, "text/html;charset=ascii");
    
    ap_rputs("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\">\n", req);
    ap_rputs("<html><head><title>Sample apache module responce!</head></title>",req);
    ap_rputs("<body><h1>Welcome to the club, body.</h1></body></html>", req);

    return OK;
}

static void register_hooks(apr_pool_t* pool)
{ 
    ap_hook_handler(sample_handler, NULL, NULL, APR_HOOK_MIDDLE);
}

module AP_MODULE_DECLARE_DATA sample_module = {
    STANDARD20_MODULE_STUFF,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    register_hooks
};