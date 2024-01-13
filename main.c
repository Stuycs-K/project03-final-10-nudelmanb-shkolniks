#define _GNU_SOURCE     /* To get defns of NI_MAXSERV and NI_MAXHOST */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include "networking.h"
#include "compute.h"

// gets the ip address for a computer in the lab
void find_lab_ip(char* out, int machine_number) {
  sprintf(out, "149.89.161.1%02d", machine_number);
}

// returns local ip address
void get_local_ip(char* out) {
  struct ifaddrs *ifaddr;
  getifaddrs(&ifaddr);
  
  for (struct ifaddrs *ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
    struct sockaddr* addr = ifa->ifa_addr;
    unsigned int flags = ifa->ifa_flags;

    // is addr ipv4 and not loopback
    if (addr != NULL && addr->sa_family == AF_INET && !(flags & IFF_LOOPBACK)) {
      getnameinfo(addr, sizeof(struct sockaddr_in), out, 32, NULL, 0, NI_NUMERICHOST);
      return;
    }
  }

  freeifaddrs(ifaddr);
}

// tries running client program on remote computer, if successful server will recieve another connection
int lab_run_client(int machine_number, char* user){
  char LOCAL_IP[32];
  get_local_ip(LOCAL_IP);

  char LAB_IP[32];
  find_lab_ip(LAB_IP, machine_number);

  char* args[16];
  args[0] = "ssh";

  char sshprompt[256];
  sprintf(sshprompt, "%s@%s", user, LAB_IP);

  char command[256];
  sprintf(command, "cd Desktop/project03-final-10-nudelmanb-shkolniks; make compute ARGS=\"%s\"", LOCAL_IP);

  args[1] = sshprompt;
  args[2] = "-o";
  args[3] = "StrictHostKeyChecking=no";
  args[4] = command;
  args[5] = NULL;

  if (fork() == 0) {
    printf("Running ssh command on %s\n", LOCAL_IP);
    execvp(args[0], args);
  }
}

int main() {
  printf("Starting server\n");
  
  int listen_socket = server_setup(); 

  lab_run_client(10, "sshkolnik40");

  int client_socket = server_tcp_handshake(listen_socket);

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

  write(client_socket, &info, sizeof(info));
}