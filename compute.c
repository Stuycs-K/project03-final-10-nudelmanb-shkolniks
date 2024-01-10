#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
//#include <gmp.h>
#include "compute.h"
#include "libattopng.h"
#include "networking.h"

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

    if (mpf_cmp_ui(mag, 2 * 2) >= 0) {
      return i + 1;
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

    if (z->r * z->r + z->i * z->i >= 2 * 2) {
      return i + 1;
    }
  }

  return -1;
}

void render_image(struct image_info* info) {
  libattopng_t* png = libattopng_new(info->size_r, info->size_i, PNG_PALETTE);
  libattopng_set_palette(png, info->palette, 256);

  for (int ic = 0; ic < info->size_i; ic++) {
    for (int rc = 0; rc < info->size_r; rc++) {
      double i = info->i_max + ((info->i_min - info->i_max) * ic) / info->size_i;
      double r = info->r_min + ((info->r_max - info->r_min) * rc) / info->size_r;

      struct complex z;
      z.r = 0;
      z.i = 0;

      struct complex c;
      c.r = r;
      c.i = i;

      int count = iterate(info->iterations, &z, &c);

      if (count == -1) {
        libattopng_set_pixel(png, rc, ic, 0);
      } else {
        libattopng_set_pixel(png, rc, ic, 1 + count % 255);
      }
    }
  }

  libattopng_save(png, info->out_name);
  libattopng_destroy(png);
}

int main() {
  struct image_info info;
  /*double i_center = 0.022143087552935;
  double r_center = -1.627637309835029;

  int iterations = 2000;
  double radius = 2;

  int palette[256];
  palette[0] = RGB(0, 0, 0);
  for (int i = 0; i < 255; i++) {
    int r, g, b;

    if (i < 32) {
        r = i * 8;
        g = i * 8;
        b = 127 - i * 4;
    } else if (i < 128) {
        r = 255;
        g = 255 - (i - 32) * 8 / 3;
        b = (i - 32) * 4 / 3;
    } else if (i < 192) {
        r = 255 - (i - 128) * 4;
        g = 0 + (i - 128) * 3;
        b = 127 - (i - 128);
    } else {
        r = 0;
        g = 192 - (i - 192) * 3;
        b = 64 + (i - 192);
    }

    palette[i + 1] = RGB(r, g, b);
  }

  int NUM_CHILDREN = 8;
  int NUM_IMAGES = 10; //170;

  for (int childID = 0; childID < NUM_CHILDREN; childID++) {
    if (fork() == 0) {
      for (int i = childID; i < NUM_IMAGES; i += NUM_CHILDREN) {
        char png_name_buf[32];
        sprintf(png_name_buf, "%05d.png", i);

        struct image_info info;

        info.r_min = r_center - radius;
        info.i_min = i_center - radius;
        info.r_max = r_center + radius;
        info.i_max = i_center + radius;

        info.iterations = iterations;
        info.palette = palette;
        info.out_name = png_name_buf;

        info.size_r = 512;
        info.size_i = 512;

        render_image(&info);
        printf("Child %d: wrote %s\n", childID, png_name_buf);

        for (int j = 0; j < NUM_CHILDREN; j++) {
          radius /= 1.25;
        }
      }

      exit(0);
    }

    radius /= 1.25;
  }

  for (int i = 0; i < NUM_CHILDREN; i++) {
    wait(NULL);
    printf("wait(NULL) returned\n");
  }*/
}