#ifndef HTTP_COMMON_H
#define HTTP_COMMON_H

//Suported HTTP methods
typedef enum {
  GET,
  POST,
  UNKNOWN_METHOD
} Http_method;

typedef struct HttpRequest {
    Http_method method;
    char *path;
    char *version;
} HttpRequest;

#endif // !HTTP_COMMON_H
