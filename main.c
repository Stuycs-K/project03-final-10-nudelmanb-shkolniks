#include <stdio.h>
#include <string.h>
#include "networking.h"
#include "compute.h"

// gets the ip address for a computer in the lab
void find_ip(char* out, int machine_number) {
  sprintf(out, "149.89.161.1%02d", machine_number);
}

// returns a file descriptor of a socket to a remote compute server
int lab_run_client(int machine_number, char* user){
  char IP[32];
  find_ip(IP, machine_number);

  char* args[16];
  args[0] = "ssh";

  char sshprompt[124];
  sprintf(sshprompt, "%s@%s", user, IP);

  args[1] = sshprompt;
  args[2] = "-o";
  args[3] = "StrictHostKeyChecking=no";
  args[4] = "cd Desktop/project03-final-10-nudelmanb-shkolniks; make compute";
  args[5] = NULL;

  if (fork() == 0) {
    printf("Running ssh command on %s\n", IP);
    execvp(args[0], args);
  } else {
    sleep(10);

    int server_socket = client_tcp_handshake(IP);
    printf("Connection to compute server %s made\n", IP);

    return server_socket;
  }
}

int main() {
  int server_socket = lab_run_client(10, "sshkolnik40");

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