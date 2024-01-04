#include <stdio.h>
#include <gmp.h>
#include "compute.h"

int iterate(int iterations, struct complex* z) {
  mpf_t r_copy;
  mpf_t i_copy;

  mpf_init2(r_copy, FLOAT_PREC);
  mpf_init2(i_copy, FLOAT_PREC);

  for (int i = 0; i < iterations; i++) {
    mpf_set(r_copy, z->r); //r_copy = z.r
    mpf_set(i_copy, z->i); //i_copy = z.i

    mpf_pow_ui(r_copy, 2); //r_copy **= 2
    mpf_pow_ui(i_copy, 2); //i_copy **= 2

    mpf_sub(r_copy, r_copy, i_copy); //r_copy -= i_copy

    mpf_set_ui(i_copy, 2); //i_copy = 2
    mpf_mul(i_copy, i_copy, z->r); //i_copy *= z.r
    mpf_mul(i_copy, i_copy, z->i); //i_copy *= z.i
  }

  mpf_clear(r_copy);
  mpf_clear(i_copy);

  return i;
}

int main() {
  printf("hi\n");
}