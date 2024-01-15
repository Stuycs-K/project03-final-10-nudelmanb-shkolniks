#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
//#include <gmp.h>
#include "compute.h"
#include "libattopng.h"
#include "networking.h"

// iterate z^2 + c iterations times
int iterate(int iterations, struct complex* z, struct complex* c) {
  mpf_t r_copy;
  mpf_t i_copy;
  mpf_t mag;

  mpf_init_set(r_copy, z->r); //r_copy = z.r
  mpf_init_set(i_copy, z->i); //i_copy = z.i
  mpf_init(mag);

  for (int i = 0; i < iterations; i++) {
    mpf_pow_ui(r_copy, 2); //r_copy **= 2
    mpf_pow_ui(i_copy, 2); //i_copy **= 2

    mpf_set_ui(mag, 0); //mag = 0
    mpf_add(mag, r_copy); //mag += r_copy
    mpf_add(mag, i_copy); //mag += i_copy

    if (mpf_cmp_ui(mag, 2 * 2) >= 0) {
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
  
  return -1;
}

void render_image(struct image_info* info) {
  int shmid = shmget(229875612, info->size_r * info->size_i * sizeof(int), IPC_CREAT | 0640);
  int* data = shmat(shmid, 0, 0);

  int NUM_CHILDREN = 8;
  for (int child = 0; child < NUM_CHILDREN; child++) {
    if (fork() == 0) {
      mpf_set_default_prec(FLOAT_PREC);

      struct complex z;
      mpf_init(z.r);
      mpf_init(z.i);

      struct complex c;
      mpf_init(c.r);
      mpf_init(c.i);

      struct complex bottom_left;
      mpf_init_set_str(bottom_left.r, info->r_min, 10);
      mpf_init_set_str(bottom_left.i, info->i_min, 10);

      struct complex step;
      mpf_init_set_str(step.r, info->r_max, 10);
      mpf_init_set_str(step.i, info->i_max, 10);

      mpf_sub(step.r, step.r, bottom_left.r);
      mpf_sub(step.i, step.i, bottom_left.i);

      mpf_div_ui(step.r, step.r, info->size_r - 1);
      mpf_div_ui(step.i, step.i, info->size_i - 1);

      for (int n = child; n < info->size_r * info->size_i; n += NUM_CHILDREN) {
        int rc = n % info->size_r;
        int ic = n / info->size_r;

        mpf_set(c.r, step.r);
        mpf_mul_ui(c.r, c.r, rc);
        mpf_add(c.r, c.r, bottom_left.r);

        mpf_set(c.i, step.i);
        mpf_mul_ui(c.i, c.i, ic);
        mpf_add(c.i, c.i, bottom_left.i);

        mpf_set_ui(z.r, 0);
        mpf_set_ui(z.i, 0);

        data[n] = iterate(info->iterations, &z, &c);
      }

      exit(0);
    }
  }
  
  for (int child = 0; child < NUM_CHILDREN; child++) {
    wait(NULL);
  }

  libattopng_t* png = libattopng_new(info->size_r, info->size_i, PNG_PALETTE);
  libattopng_set_palette(png, info->palette, 256);

  for (int i = 0; i < info->size_r * info->size_i; i++) {
    int rc = i % info->size_r;
    int ic = i / info->size_r;

    if (data[i] == -1) {
      libattopng_set_pixel(png, rc, ic, 0);
    } else {
      libattopng_set_pixel(png, rc, ic, 1 + data[i] % 255);
    }
  }

  libattopng_save(png, info->out_name);
  libattopng_destroy(png);

  shmctl(shmid, IPC_RMID, 0);
}

int main(int argc, char *argv[]) {
  char* IP = "127.0.0.1";
  if (argc > 1) {
    IP = argv[1];
  }

  printf("Trying to connect to %s\n", IP);

  int server_socket = client_tcp_handshake(IP);

  printf("Connection made\n");

  while (1) {
    struct image_info info;
    ssize_t bytes = read(server_socket, &info, sizeof(info));

    if (bytes == 0) {
      printf("0 bytes read, connection closed\n");
      return 0;
    }

    printf("Recieved compute command:\n");
    printf("\tcoordinates: %f + %fi to %f + %fi\n", info.r_min, info.i_min, info.r_max, info.i_max);
    printf("\titerations: %d, out name: %s\n", info.iterations, info.out_name);
    printf("\tout width: %d, out height: %d\n", info.size_r, info.size_i);

    render_image(&info);

    int success = 1;
    write(server_socket, &success, sizeof(success));
  }
}