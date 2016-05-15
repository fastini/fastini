#include "fastini.h"

VALUE mFastini;

void Init_fastini(void) {
  mFastini = rb_define_module("Fastini");
  rb_define_singleton_method(mFastini, "load", fastini_load, 1);
  rb_define_singleton_method(mFastini, "load_file", fastini_load_file, 1);
  rb_define_singleton_method(mFastini, "dump", fastini_dump, 1);
  rb_define_singleton_method(mFastini, "dump_file", fastini_dump_file, 2);
}

VALUE fastini_load(VALUE mod, VALUE str) {
  VALUE result = rb_hash_new();
  VALUE current_section = Qnil;

  char *str_p = StringValueCStr(str);
  char *strtok_context = NULL;
  char *line = strtok_r(str_p, "\n", &strtok_context);

  while(line != NULL) {
    char *sanitized_line = lstrip(rstrip(line));

    if(is_comment(sanitized_line)) {
      line = strtok_r(NULL, "\n", &strtok_context);
      continue;
    }

    if(is_section(sanitized_line)) {
      current_section = parse_section(sanitized_line, result);
    } else {
      parse_assignment(sanitized_line, current_section, result);
    }

    line = strtok_r(NULL, "\n", &strtok_context);
  }

  return result;
}

VALUE fastini_load_file(VALUE mod, VALUE filename) {
  VALUE result = rb_hash_new();
  VALUE current_section = Qnil;

  char *path = StringValueCStr(filename);
  FILE* file = fopen(path, "r");
  char line[LINE_LENGTH];

  if (!file) {
    rb_raise(rb_eStandardError, "file not found");
  }

  while (fgets(line, sizeof(line), file)) {
    char *sanitized_line = lstrip(rstrip(line));

    if(is_comment(sanitized_line)) {
      continue;
    }

    if(is_section(sanitized_line)) {
      current_section = parse_section(sanitized_line, result);
    } else {
      parse_assignment(sanitized_line, current_section, result);
    }
  }

  fclose(file);

  return result;
}

VALUE fastini_dump(VALUE mod, VALUE hash) {
  if (!RB_TYPE_P(hash, T_HASH)) {
    rb_raise(rb_eTypeError, "argument must be a Hash");
  }

  VALUE result = rb_utf8_str_new_cstr("");
  rb_hash_foreach(hash, hash_to_ini, result);

  return result;
}

VALUE fastini_dump_file(VALUE mod, VALUE hash, VALUE filename) {
  if (!RB_TYPE_P(hash, T_HASH)) {
    rb_raise(rb_eTypeError, "argument must be a Hash");
  }

  VALUE result = rb_utf8_str_new_cstr("");
  char *result_str = NULL;
  char *path = StringValueCStr(filename);
  FILE* file = fopen(path, "w");

  if (!file) {
    rb_raise(rb_eStandardError, "invalid file path");
  }

  rb_hash_foreach(hash, hash_to_ini, result);
  result_str = StringValueCStr(result);

  fputs(result_str, file);
  fclose(file);

  return Qtrue;
}

VALUE parse_section(char *line, VALUE result) {
  VALUE section_name = Qnil;
  char *section_end = strchr(line, ']');

  if (section_end != NULL) {
    *section_end = '\0';
    section_name = rb_str_new2(line + 1);
    rb_hash_aset(result, section_name, rb_hash_new());
  } else {
    rb_raise(rb_eSyntaxError, "section must have an end");
  }

  return section_name;
}

void parse_assignment(char *line, VALUE current_section, VALUE result) {
  char *assign = strchr(line, '=');

  if (assign != NULL) {
    *assign = '\0';
    VALUE key = rb_str_new2(line);

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
