#include "handler.h"
#include <regex.h>
#include <stdio.h>
#include <string.h>

Http_method parse_http_method(const char *request) {

  // Extracting the first line of request
  char req_copy[256];
  strncpy(req_copy, request, sizeof(req_copy));
  req_copy[sizeof(req_copy) - 1] = '\0';
  char *buffer = strtok(req_copy, "\n");

  // Defining regex
  regex_t regex;
  regmatch_t matches[2];
  const char *pattern = "^(GET|POST)";

  // Compiling regex expression
  int ret = regcomp(&regex, pattern, REG_EXTENDED) != 0;
  if(ret != 0) {
    char error_message[100];
    regerror(ret, &regex, error_message, sizeof(error_message));
    printf("Erro compiling regex: %s\n", error_message);
    return 1;  
  }
  
  // Executing the regex
  if(regexec(&regex, buffer, 2, matches, 0) == 0) {
      // if "GET" was discovered
      if (strncmp(buffer + matches[1].rm_so, "GET", 3) == 0) {
          regfree(&regex);
          return GET;
      }
      // if "POST" was discovered
      if (strncmp(buffer + matches[1].rm_so, "POST", 4) == 0) {
          regfree(&regex);
          return POST;
      }
  } 

  regfree(&regex);
  return UNKNOWN_METHOD;
}
