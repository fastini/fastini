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

VALUE to_s(VALUE value) {
  return rb_convert_type(value, T_STRING, "String", "to_s");
}

void generate_assignment(VALUE key, VALUE value, VALUE str) {
  rb_str_concat(str, key);
  rb_str_cat2(str, "=");
  rb_str_concat(str, value);
  rb_str_cat2(str, "\n");
}

void generate_section(VALUE key, VALUE str) {
  rb_str_cat2(str, "\n");
  rb_str_cat2(str, "[");
  rb_str_concat(str, key);
  rb_str_cat2(str, "]");
  rb_str_cat2(str, "\n");
}

int hash_to_ini(VALUE key, VALUE value, VALUE str) {
  key = to_s(key);

  if (RB_TYPE_P(value, T_HASH)) {
    generate_section(key, str);
    rb_hash_foreach(value, hash_to_ini, str);
  } else {
    generate_assignment(key, to_s(value), str);
  }

  return ST_CONTINUE;
}
