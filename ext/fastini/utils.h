#ifndef _UTILS
#define _UTILS

#include <ruby.h>
#include <ctype.h>
#include <string.h>

char * rstrip(char *str);
char * lstrip(char *str);

int is_comment(char *str);

int hash_to_ini(VALUE key, VALUE value, VALUE str);

VALUE to_s(VALUE value);

void generate_assignment(VALUE key, VALUE value, VALUE str);
void generate_section(VALUE key, VALUE str);

#endif
