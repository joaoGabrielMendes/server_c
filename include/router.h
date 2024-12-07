#ifndef ROUTER_H
#define ROUTER_H

#include "http_common.h"

#define HASH_TABLE_SIZE 1024

typedef struct Route {
  Http_method method;
  char path[128];
  void (*handler)(void);
} Route;

typedef struct Router {
  Route *table[HASH_TABLE_SIZE];
} Router;

unsigned long hash_route(Http_method method, const char* path);
Router *create_router();
void add_router(Router *router, Http_method method, const char *path, void (*handler)(void));
Route *find_route(Router *router, Http_method method, const char *path); 

#endif // !ROUTER_H

