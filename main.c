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
void get_lab_ip(char* out, int machine_number) {
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
  get_lab_ip(LAB_IP, machine_number);

  char sshprompt[256];
  sprintf(sshprompt, "%s@%s", user, LAB_IP);

  char current_dir[256];
  getcwd(current_dir, 256);

  char command[512];
  sprintf(command, "cd %s; ./compute %s", current_dir, LOCAL_IP);

  char* args[16];

  args[0] = "ssh";
  args[1] = sshprompt;
  
  // dont ask to confirm host authenticity
  args[2] = "-o";
  args[3] = "StrictHostKeyChecking=no";

  args[4] = command;
  args[5] = NULL;

  if (fork() == 0) {
    printf("Attempting to run ssh command on %s\n", LAB_IP);

    // dont print stdout
    int null = open("/dev/null", O_WRONLY);
    dup2(null, STDOUT_FILENO);

    execvp(args[0], args);
  }
}

double i_center = 0.022143087552935;
double r_center = -1.627637309835029;

double radius = 2;
int zoom_level = 0;

void send_render_command(int fd, struct image_info* info) {
  info->r_min = r_center - radius;
  info->i_min = i_center - radius;
  info->r_max = r_center + radius;
  info->i_max = i_center + radius;

  sprintf(info->out_name, "%05d.png", zoom_level);

  write(fd, info, sizeof(*info));

  zoom_level += 1;
  radius /= 1.25;
}

// ffmpeg -framerate 30 -i %05d.png -vf "scale=8000:-1,zoompan=z='zoom+(.25/30)':x=iw/2-(iw/zoom/2):y=ih/2-(ih/zoom/2):d=1*30:s=1024x1024:fps=30" -t 200 -c:v libx264 -pix_fmt yuv420p output.mp4

int main() {
  struct image_info info;

  info.size_r = 1024;
  info.size_i = 1024;

  info.iterations = 2000;

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

  printf("Starting server\n");
  int listen_socket = server_setup();

  // run all ssh commands
  for (int i = 1; i < 2; i++) {
    lab_run_client(i, "sshkolnik40");
  }

  int connected_clients[100];
  int num_connected_clients = 0;

  fd_set read_fds;

  while (zoom_level < 200) {
    FD_ZERO(&read_fds);

    // add listen_socket and all connected clients to read_fds
    int max_fd = listen_socket;

    FD_SET(listen_socket, &read_fds);
    for (int i = 0; i < num_connected_clients; i++) {
      if (connected_clients[i] == -1) {
        continue;
      }

      FD_SET(connected_clients[i], &read_fds);

      if (connected_clients[i] > max_fd) {
        max_fd = connected_clients[i];
      }
    }

    int num_ready = select(max_fd + 1, &read_fds, NULL, NULL, NULL);

    if (FD_ISSET(listen_socket, &read_fds)) {
      printf("Accepted client %d, sending it zoom=%d\n", num_connected_clients, zoom_level);

      int new_client = server_tcp_handshake(listen_socket);
      send_render_command(new_client, &info);

      connected_clients[num_connected_clients] = new_client;
      num_connected_clients += 1;
    }

    for (int i = 0; i < num_connected_clients; i++) {
      if (connected_clients[i] == -1) {
        continue;
      }

      if (!FD_ISSET(connected_clients[i], &read_fds)) {
        continue;
      }

      int res;
      int bytes = read(connected_clients[i], &res, sizeof(res));

      if (bytes == 0) {
        printf("Client %d disconnected\n", i);
        connected_clients[i] = -1;

        continue;
      }

      printf("Client %d finished, sending it zoom=%d\n", i, zoom_level);
      send_render_command(connected_clients[i], &info);
    }
  }
}