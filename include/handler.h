#ifndef HANDLER_H

typedef enum {
  GET,
  POST,
  UNKNOWN_METHOD
} Http_method;

Http_method parse_http_method(const char *buffer);

#endif // !HANDLER_H