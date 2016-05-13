#include "utils.h"

char * rstrip(char *str) {
  char *p = str + strlen(str);

  while(p > str && isspace(*--p)) {
    *p = '\0';
  }

  return str;
}

char * lstrip(char *str) {
  while(*str && isspace(*str)) {
    str++;
  }

  return str;
}

int is_comment(char *str) {
  return (!*str || *str == ';' || *str == '#');
}
