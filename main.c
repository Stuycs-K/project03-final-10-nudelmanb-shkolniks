#include <stdio.h>
#include <string.h>
#include "networking.h"
#include "compute.h"

/*
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
*/

int main() {
  char* IP = "127.0.0.1";
  /*if (argc>1) {
    IP = argv[1];
  }*/

  int server_socket = client_tcp_handshake(IP);
  printf("Connection to compute server made.\n");

  struct image_info info;

  info.r_min = -2;
  info.i_min = -2;
  info.r_max = 2;
  info.i_max = 2;

  info.size_r = 512;
  info.size_i = 512;

  info.iterations = 500;
  strcpy(info.out_name, "test.png");

  info.palette[0] = RGB(0, 0, 0);
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

    info.palette[i + 1] = RGB(r, g, b);
  }

  write(server_socket, &info, sizeof(info));
}