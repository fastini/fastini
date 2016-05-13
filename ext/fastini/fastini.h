#ifndef _FASTINI
#define _FASTINI

#include <ruby.h>
#include <string.h>
#include "utils.h"

extern VALUE mFastini;

VALUE fastini_load(VALUE mod, VALUE str);

VALUE fastini_dump(VALUE mod, VALUE hash);

#endif
