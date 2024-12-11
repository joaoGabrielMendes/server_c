#include "handler.h"
#include "http_common.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  const char *request1 = "POST /users HTTP/1.1";
  const char *request2 = "GET /users HTTP/1.1";
  const char *request3 = "SEX /users HTTP/1.1";

  HttpRequest *request = init_http_request();
  int success = parse_http_line(request1, request);
  
  if (success == 0) {
    // Imprimir os valores de path e version corretamente
    printf("PATH: %s\n", request->path);
    printf("VERSION: %s\n", request->version);
  } else {
    printf("Erro ao processar a requisição.\n");
  }

  // Liberar a memória alocada para a estrutura HttpRequest
  free_http_request(request);

  return 0;
}

