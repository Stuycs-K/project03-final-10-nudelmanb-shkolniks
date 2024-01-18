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
  int shmid = shmget(229875612, info->size_r * info->size_i * sizeof(int), IPC_CREAT | 0640);
  int* data = shmat(shmid, 0, 0);

  int NUM_CHILDREN = 8;
  for (int child = 0; child < NUM_CHILDREN; child++) {
    if (fork() == 0) {
      for (int n = child; n < info->size_r * info->size_i; n += NUM_CHILDREN) {
        int rc = n % info->size_r;
        int ic = n / info->size_r;

        double i = info->i_max + ((info->i_min - info->i_max) * ic) / info->size_i;
        double r = info->r_min + ((info->r_max - info->r_min) * rc) / info->size_r;

        struct complex z;
        z.r = 0;
        z.i = 0;

        struct complex c;
        c.r = r;
        c.i = i;

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