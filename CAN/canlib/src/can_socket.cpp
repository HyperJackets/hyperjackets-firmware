#include "include/can_socket.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

static int s;
static struct sockaddr_can addr;
static struct ifreq ifr;

void CANSocket::connectCANBus() {

  // Sock raw prevents TCP/IP encapsulation packet processing
  if ((s = socket(AF_INET, SOCK_RAW, 0)) < 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }
  // Change to can1 later for actual use
  strcpy(ifr.ifr_name, "vcan0"); 
  // Retrieving index of chosen CAN interface
  ioctl(s, SIOCGIFINDEX, &ifr);

  // Binding the socket to CAN interface
  memset(&addr, 0, sizeof(addr));
  addr.can_family = AF_CAN;
  addr.can_ifindex = ifr.ifr_ifindex;

  if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    perror("Bind failed");
    exit(EXIT_FAILURE);
  }
}
