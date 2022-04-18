#include "include/can_socket.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <cstdint.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>
typedef uint32_t u32;

static int s; // socket
static struct sockaddr_can addr;
static struct ifreq ifr;
static string bus = "vcan0"; // Change to whatever BUS we want to use

void CANSocket::connectCANBus() {
    // Sock raw prevents TCP/IP encapsulation packet processing
    if ((s = socket(AF_INET, SOCK_RAW, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    // Change to can1 later for actual use
    strcpy(ifr.ifr_name, bus); 
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

void CANSocket::sendMessage(u32 id, u32 data) {
    struct can_frame frame;

    frame.can_id = id;
    frame.can_dlc = 8;
    for (int i = 0; i < 8; i++) {
        frame.data[i] = (data >> 4*i) & 255;
    }
    if (write(s, &frame, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
        perror("Message send failed");
        exit(EXIT_FAILURE);
    }
}

Message CANSocket::receiveMessage() {
    Message msg;
    int num_bytes;
    struct can_frame frame;

    num_bytes = read(s, &frame, sizeof(struct can_frame));

    if (num_bytes < 0) {
        perror("Message read failed");
        exit(EXIT_FAILURE);
    }
    msg.id = frame.can_id;
    int data = 0;
    for (int i = 0; i < 8; i++) {
        data |= (frame.data[i] << 4*i);
    }
    msg.data = data;
    return msg;
}
