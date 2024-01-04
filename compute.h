#ifndef COMPUTE_H
#define COMPUTE_H

#include <gmp.h>
#define FLOAT_PREC 64

struct complex {
  mpf_t r;
  mpf_t i;
};

#endif