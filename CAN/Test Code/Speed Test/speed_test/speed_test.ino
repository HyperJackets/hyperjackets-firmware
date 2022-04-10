// demo: CAN-BUS Shield, send data
// loovee@seeed.cc


#include <SPI.h>

#define CAN_2515
// #define CAN_2518FD

// Set SPI CS Pin according to your hardware

#if defined(SEEED_WIO_TERMINAL) && defined(CAN_2518FD)
// For Wio Terminal w/ MCP2518FD RPi Hat：
// Channel 0 SPI_CS Pin: BCM 8
// Channel 1 SPI_CS Pin: BCM 7
// Interupt Pin: BCM25
const int SPI_CS_PIN  = BCM8;
const int CAN_INT_PIN = BCM25;
#else

// For Arduino MCP2515 Hat:
// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10
const int SPI_CS_PIN = 9;
const int CAN_INT_PIN = 2;
#endif


#ifdef CAN_2518FD
#include "mcp2518fd_can.h"
mcp2518fd CAN(SPI_CS_PIN); // Set CS pin
#endif

#ifdef CAN_2515
#include "mcp2515_can.h"
mcp2515_can CAN(SPI_CS_PIN); // Set CS pin
#endif

void setup() {
    SERIAL_PORT_MONITOR.begin(115200);
    while(!Serial){};

    while (CAN_OK != CAN.begin(CAN_1000KBPS)) {             // init can bus : baudrate = 125k bc thats the configuration on BBB
        SERIAL_PORT_MONITOR.println(" CAN init fail, retry...");
        delay(100);
    }
    SERIAL_PORT_MONITOR.println("CAN init ok!");
}

unsigned char stmp[2] = {0, 0};
long cur = 0;
unsigned long prev_time = millis();
unsigned long end_time = 0;
unsigned long start_time = 0;
void loop() {
    // send data:  id = 0x00, standrad frame, data len = 8, stmp: data buf
    if (cur == 0) {
      start_time = millis();
    }
    cur++;
    stmp[0] = cur; // First byte is count of message
    prev_time = millis();
    CAN.sendMsgBuf(0x00, 0, 2, stmp); 
    Serial.println("Message sent!");
    // delay(100);                       // send data per 100ms
    stmp[1] = millis() - prev_time; // Second byte is time taken to send previous message
    if (cur == 255) {
      end_time = millis();
      unsigned long total_time = (end_time - start_time) / 256;
      SERIAL_PORT_MONITOR.println("Ten thousand Messages sent. Time taken: " + total_time);
      cur = 0;      
    }

}

// END FILE
