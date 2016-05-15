#ifndef _FASTINI
#define _FASTINI

#include <ruby.h>
#include <string.h>
#include "utils.h"

#define LINE_LENGTH 300

extern VALUE mFastini;

VALUE fastini_load(VALUE mod, VALUE str);
VALUE fastini_load_file(VALUE mod, VALUE path);

VALUE parse_section(char *line, VALUE result);
void parse_assignment(char *line, VALUE current_section, VALUE result);

VALUE fastini_dump(VALUE mod, VALUE hash);
VALUE fastini_dump_file(VALUE mod, VALUE hash, VALUE filename);

#endif
