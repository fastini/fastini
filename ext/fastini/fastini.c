#include "fastini.h"

VALUE mFastini;

void Init_fastini(void) {
  mFastini = rb_define_module("Fastini");
}
