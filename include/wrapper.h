#ifndef _WRAPPER_H_
#define _WRAPPER_H_

#include <apache2/httpd.h>
#include <apache2/http_protocol.h>

#ifdef __cplusplus
extern "C"
#endif
int serve(request_rec *req);

#endif //_WRAPPER_H_