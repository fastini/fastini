#include "fastini.h"

VALUE mFastini;

void Init_fastini(void) {
  mFastini = rb_define_module("Fastini");
  rb_define_singleton_method(mFastini, "load", fastini_load, 1);
  rb_define_singleton_method(mFastini, "dump", fastini_dump, 1);
}

VALUE fastini_load(VALUE mod, VALUE str) {
  VALUE result = rb_hash_new();


  char *str_p = StringValueCStr(str);
  VALUE current_section = Qnil;
  char *line = strtok(str_p, "\n");

  while(line != NULL) {
    char *sanitized_line = lstrip(rstrip(line));

    if(is_comment(sanitized_line)) {
      line = strtok(NULL, "\n");
      continue;
    }

    if(*sanitized_line == '[') {
      char *section_end = strchr(sanitized_line, ']');

      if (section_end != NULL) {
        *section_end = '\0';
        current_section = rb_str_new2(sanitized_line + 1);
        rb_hash_aset(result, current_section, rb_hash_new());
      } else {
        rb_raise(rb_eSyntaxError, "section must have an end");
      }
    } else {
      char *assign = strchr(sanitized_line, '=');

      if (assign != NULL) {
        *assign = '\0';
        VALUE key = rb_str_new2(sanitized_line);

        // TODO: Check type and convert. For now only strings are created.
        VALUE value = rb_str_new2(assign + 1);

        if (NIL_P(current_section)) {
          rb_hash_aset(result, key, value);
        } else {
          VALUE section_hash = rb_hash_aref(result, current_section);
          rb_hash_aset(section_hash, key, value);
        }
      } else {
        rb_raise(rb_eSyntaxError, "values must be assigned with the '=' symbol");
      }
    }

    line = strtok(NULL, "\n");
  }

  return result;
}


VALUE fastini_dump(VALUE mod, VALUE hash) {
  VALUE result = rb_utf8_str_new_cstr("");

  if (!RB_TYPE_P(hash, T_HASH)) {
    rb_raise(rb_eTypeError, "argument must be a Hash");
  }

  rb_hash_foreach(hash, hash_to_ini, result);

  return result;
}
