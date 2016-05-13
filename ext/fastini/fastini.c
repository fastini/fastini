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

    // Ignoring comments and empty lines.
    if(is_comment(line)) {
      line = strtok(NULL, "\n");
      continue;
    }

    // Start of a section
    if(*sanitized_line == '[') {
      char *section_end = strchr(sanitized_line, ']');

      if (section_end != NULL) {
        *section_end = '\0';
        VALUE section_key = rb_str_new2(sanitized_line + 1);
        rb_hash_aset(result, section_key, rb_hash_new());
      } else {
        rb_raise(rb_eSyntaxError, "section must have an end");
      }
    }

    line = strtok(NULL, "\n");
  }

  return result;
}
