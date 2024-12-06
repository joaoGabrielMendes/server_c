#include "handler.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  const char *request1 = "POST /users HTTP/1.1";
  const char *request2 = "GET /users HTTP/1.1";
  const char *request3 = "SEX /users HTTP/1.1";


  Http_method method1 = parse_http_method(request1);
  if (method1 == POST) {
    printf("OK \n");
  } else {
    printf("FAIL \n");
  }

  Http_method method2 = parse_http_method(request2);
  if (method2 == GET) {
    printf("OK \n");
  } else {
    printf("FAIL \n");
  }

  Http_method method3 = parse_http_method(request3);
  if (method3 == UNKNOWN_METHOD) {
    printf("OK \n");
  } else {
    printf("FAIL \n");
  }

  return 0;
}
