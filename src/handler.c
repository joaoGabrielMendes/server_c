#include "handler.h"
#include "http_common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


HttpRequest* init_http_request() {
HttpRequest *request = (HttpRequest*) malloc(sizeof(HttpRequest));
if (!request) {
perror("Allocation memory error");
      exit(EXIT_FAILURE);
  }
  request->path = NULL;
  request->method = UNKNOWN_METHOD;
  request->version = NULL;
  return request;
}

void free_http_request(HttpRequest *request) {
  if(request) {
    free(request->path);
    free(request->version);
    free(request);
  }
}

Http_method string_to_http_method(const char *method) {
  if (strcmp(method, "GET") == 0) {
        return GET;
    } else if (strcmp(method, "POST") == 0) {
        return POST;
    }
    return UNKNOWN_METHOD;
}

int parse_http_line(const char *line, HttpRequest *http_request) {
  
  // Verify parms
  if(!line || !http_request) {
    perror("Error: invalid parmams at parse_http_line function");
  }

  char *method_str = NULL;
  char *path = NULL;
  char *version = NULL;

  // Copy line to avoid modify original line
  char *line_copy = strdup(line)  ;
  if(!line_copy) {
    perror("Memory Allocation error");
  }

  method_str = strtok(line_copy, " ");
  path = strtok(NULL, " ");
  version = strtok(NULL, "\r\n");

  if (!method_str || !path || !version) {
        fprintf(stderr, "Error: Invalid format on line\n");
        free(line_copy);
        return -1;
  }
  
  http_request->method = string_to_http_method(method_str);
  http_request->path = strdup(path);
  http_request->version = strdup(version);

  free(line_copy);
  return 0;
}


int parse_http(const char *request, HttpRequest *http_request) {
  if (!request || !http_request) {
      fprintf(stderr, "Error: Invalid parmams.\n");
      return -1;
  }

  // Locate first line
  const char *line_end = strchr(request, '\n');
  if (!line_end) {
      fprintf(stderr, "Erro: First line was not encounter.\n");
      return -1;
  }

  // Copy first line
  size_t line_length = line_end - request;
  char *first_line = malloc(line_length + 1);
  if (!first_line) {
      fprintf(stderr, "Erro: Memory allocation fail.\n");
      return -1;
  }
  strncpy(first_line, request, line_length);
  first_line[line_length] = '\0';

  // Parsre first line
  int result = parse_http_line(first_line, http_request);
  free(first_line);

  return result;
}
