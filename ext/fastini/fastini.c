#include "fastini.h"

VALUE mFastini;

void Init_fastini(void) {
  mFastini = rb_define_module("Fastini");
  rb_define_singleton_method(mFastini, "load", fastini_load, 1);
}

VALUE fastini_load(VALUE mod, VALUE str) {
  VALUE result = rb_hash_new();

  char *str_p = StringValueCStr(str);
  char *section = NULL;
  char *line = strtok(str_p, "\n");

  while(line != NULL) {
    char *sanitized_line = lstrip(rstrip(line));

    // Ignoring comments
    if(!*sanitized_line || *sanitized_line == ';' || *sanitized_line == '#') {
      line = strtok(NULL, "\n");
      continue;
    }

    // Start of a section
    if(*sanitized_line == '[') {
      fprintf(stderr, "Start of a section!\n");
    }

    line = strtok(NULL, "\n");
  }

  return result;
}
