#include <stdio.h>
//#include <gmp.h>
#include "compute.h"

// iterate z^2 + c iterations times
int iterate(int iterations, struct complex* z, struct complex* c) {
  /*mpf_t r_copy;
  mpf_t i_copy;
  mpf_t mag;

  mpf_init2(r_copy, FLOAT_PREC);
  mpf_init2(i_copy, FLOAT_PREC);
  mpf_init2(mag, FLOAT_PREC);

  mpf_set(r_copy, z->r); //r_copy = z.r
  mpf_set(i_copy, z->i); //i_copy = z.i

  for (int i = 0; i < iterations; i++) {
    mpf_pow_ui(r_copy, 2); //r_copy **= 2
    mpf_pow_ui(i_copy, 2); //i_copy **= 2

    mpf_set_ui(mag, 0); //mag = 0
    mpf_add(mag, r_copy); //mag += r_copy
    mpf_add(mag, i_copy); //mag += i_copy

    if (mpf_cmp_ui(mag, 2) >= 0) {
      return i;
    }

    mpf_sub(r_copy, r_copy, i_copy); //r_copy -= i_copy

    mpf_set_ui(i_copy, 2); //i_copy = 2
    mpf_mul(i_copy, i_copy, z->r); //i_copy *= z.r
    mpf_mul(i_copy, i_copy, z->i); //i_copy *= z.i

    mpf_add(r_copy, r_copy, c->r); //r_copy += c.r
    mpf_add(i_copy, i_copy, c->i); //i_copy += c.i

    mpf_set(z->r, r_copy); //z.r = z_copy
    mpf_set(z->i, i_copy); //z.i = i_copy
  }

  mpf_clear(r_copy);
  mpf_clear(i_copy);
  mpf_clear(mag);
  
  return i;*/

  for (int i = 0; i < iterations; i++) {
    double r_copy = z->r * z->r - z->i * z->i;
    double i_copy = 2 * z->r * z->i;

    z->r = r_copy + c->r;
    z->i = i_copy + c->i;

    if (z->r * z->r + z->i * z->i >= 2) {
      return i + 1;
    }
  }

  return -1;
}

int main() {
  for (double i = 1; i > -1; i -= .05) {
    for (double r = -1.5; r < .5; r += .05) {
      struct complex z;
      z.r = 0;
      z.i = 0;

      struct complex c;
      c.r = r;
      c.i = i;

      if (iterate(1000, &z, &c) == -1) {
        printf("*");
      } else {
        printf(" ");
      }
    }

    printf("\n");
  }
}