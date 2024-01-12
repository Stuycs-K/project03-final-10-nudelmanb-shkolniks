#ifndef COMPUTE_H
#define COMPUTE_H

//for images
#define RGBA(r, g, b, a) ((r) | ((g) << 8) | ((b) << 16) | ((a) << 24))
#define RGB(r, g, b) RGBA(r, g, b, 0xff)

//#include <gmp.h>
#define FLOAT_PREC 64

//DONT FORGET AOBUT THIS
#define mpf_t double

struct complex {
  mpf_t r;
  mpf_t i;
};

struct image_info {
  mpf_t r_min;
  mpf_t i_min;

  mpf_t r_max;
  mpf_t i_max;

  int iterations;
  int palette[256];
  char out_name[32];

  int size_r;
  int size_i;
};

#endif