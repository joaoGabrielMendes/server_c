#ifndef HANDLER_H
#define HANDLER_H

#include "http_common.h"

Http_method parse_http_method(const char *request);
HttpRequest* init_http_request();
void free_http_request(HttpRequest *request);
Http_method string_to_http_method(const char *method);
int parse_http_line(const char *line, HttpRequest *http_request);
int parse_http(const char *request, HttpRequest *http_request);

#endif // !HANDLER_H
