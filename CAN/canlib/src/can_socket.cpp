#include "include/can_socket.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

void CANSocket::connectCANBus() {
  int s;

  struct sockaddr_can addr;
  struct ifreq ifr;

  // Sock raw prevents TCP/IP encapsulation packet processing
  if ((s = socket(AF_INET, SOCK_RAW, 0)) < 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }
}
