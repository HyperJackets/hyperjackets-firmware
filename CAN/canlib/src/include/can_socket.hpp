#ifndef can_socket_h
#define can_socket_h
#include <cstdint.h>
typedef uint32_t u32;

//The structure of a raw CAN frame
//struct can_frame {
//    canid_t can_id;  /* 32 bit CAN_ID + EFF/RTR/ERR flags */
//    __u8    can_dlc; /* frame payload length in byte (0 .. 8) */
//    __u8    __pad;   /* padding */
//    __u8    __res0;  /* reserved / padding */
//    __u8    __res1;  /* reserved / padding */
//    __u8    data[8] __attribute__((aligned(8)));
//};

// Message used as a wrapper for can messages. An unsigned int is used for the data because it makes the bitwise shifts easier when trying to parse the raw CAN payload, which is an 8 byte character array.
struct Message {
    bool received; // this is for when reading the bus returns nothing
    unsigned int id; // this is also unsigned for consistency
    unsigned int data; // for right now, we aren't going to worry about floats
}

class CANSocket {
public:
    int k_PORT = 8000;

    void connectCANBus();
    void sendMessage();
    Message receiveMessage();
};

#endif
