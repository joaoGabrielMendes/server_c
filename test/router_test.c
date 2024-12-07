#include <stdio.h>
#include <stdlib.h>
#include "http_common.h"
#include "router.h"

void home_handler(void) {
    printf("Handler da rota /home (GET)\n \n");
}

void login_handler(void) {
    printf("Handler da rota /login (POST)\n \n");
}

int main(int argc, char *argv[]) {
   
  Router *router = create_router();
  add_router(router, GET, "/", home_handler);
  add_router(router, POST, "/login", login_handler);

  Route *route = find_route(router, GET, "/");
  if (route != NULL) {
      printf("Rota encontrada: %s\n", route->path);
      route->handler();  // Chama o handler da rota
  } else {
      printf("Rota não encontrada.\n");
  }

  route = find_route(router, POST, "/login");
  if (route != NULL) {
      printf("Rota encontrada: %s\n", route->path);
      route->handler();  // Chama o handler da rota
  } else {
      printf("Rota não encontrada.\n");
  }

  // Testa rota inexistente
  route = find_route(router, GET, "/about");
  if (route != NULL) {
      printf("Rota encontrada: %s\n", route->path);
      route->handler();  // Chama o handler da rota
  } else {
      printf("Rota não encontrada.\n");
  }

  // Libera a memória alocada
  free(router);
  return 0;
}
