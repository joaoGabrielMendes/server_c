#include "router.h"
#include "http_common.h"
#include "hash_djb2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

unsigned long hash_route(Http_method method, const char* path) {
  char key[256];
  snprintf(key, sizeof(key), "%d %s", method, path);
  return hash_djb2(key);
}

// Create Router
Router *create_router() {
  Router *router = (Router *) malloc(sizeof(Router));
   if (!router) {
        perror("Error creating router");
        exit(EXIT_FAILURE);
    }

  // Initialize all hash table buckets to NULL
  memset(router->table, 0, sizeof(router->table));
  return router;
}

// Adding a new route to the Router
void add_router(Router *router, Http_method method, const char *path, void (*handler)(void)) {
  unsigned long hash = hash_route(method, path);
  unsigned int index = hash % HASH_TABLE_SIZE;

    // Create a new route and insert it into the hash table
    Route *new_route = (Route *)malloc(sizeof(Route));
    if (!new_route) {
        perror("Error creating route");
        exit(EXIT_FAILURE);
    }
    new_route->method = method;
    strcpy(new_route->path, path);
    new_route->handler = handler;

  // Register in hash table
  router->table[index] = new_route;
}

Route *find_route(Router *router, Http_method method, const char *path) {
  unsigned long hash = hash_route(method, path);
  unsigned int index = hash % HASH_TABLE_SIZE;

  Route *route = router->table[index];
  if (route != NULL && route->method == method && strcmp(route->path, path) == 0) {
    return route;  // Route found
  }
    return NULL;  // Route not found
}
