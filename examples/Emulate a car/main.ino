/*

This code replies as if it is a car with OBD2 

Any OBD2 standard PID requested gets a reply with a fake value
 
*/

#include "esp32_can.h"            // https://github.com/collin80/esp32_can AND https://github.com/collin80/can_common
#include "obd2.h"

#define YELLOW_LED        12  // CAN INIT FAILED
#define BLUE_LED          4   // CAN PACKET RECEIVED
                              // gpio  4 for board v2.0
                              // gpio 13 for board v2.1
void setup() {
  Serial.begin(115200);
  Serial.println("Booting fake car...");
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  if(CAN0.begin()) { 
    Serial.println("CAN0 init OK"); 
  } 
  else { 
    digitalWrite(YELLOW_LED, HIGH);
    Serial.println("CAN0 failed"); 
  }
  CAN0.watchFor();
}


void loop() {
  static uint8_t lobyte = 0;
  static uint8_t hibyte = 0;
  CAN_FRAME incoming;       
  CAN_FRAME outgoing;
  
  if (CAN0.read(incoming)) {

    digitalWrite(BLUE_LED, HIGH);
    
    Serial.print("REQST ");
    Serial.print(incoming.id, HEX);
    for(uint8_t i=0;i<8;i++) {
      printhex(incoming.data.uint8[i]);
    }
    Serial.println();

    // DEFAULT ONE BYTE REPLY    
    outgoing.id = 0x7E8;
    outgoing.length = 8;
    outgoing.extended = 0;
    outgoing.rtr = 0;
    outgoing.data.uint8[0] = 0x03;  // number of bytes
    outgoing.data.uint8[1] = 0x41;
    outgoing.data.uint8[2] = incoming.data.uint8[2];
    outgoing.data.uint8[3] = lobyte;
    outgoing.data.uint8[4] = 0x00;
    outgoing.data.uint8[5] = 0x00;
    outgoing.data.uint8[6] = 0x00;
    outgoing.data.uint8[7] = 0x00;

    // SUPPORTED PIDS REPLY
    if( incoming.data.uint8[2] == PIDS_SUPPORT_01_20  ||   
        incoming.data.uint8[2] == PIDS_SUPPORT_21_40  ||   
        incoming.data.uint8[2] == PIDS_SUPPORT_41_60 ) { 
      outgoing.data.uint8[0] = 0x06;  // number of bytes
      outgoing.data.uint8[3] = 0xFF;
      outgoing.data.uint8[4] = 0xFF;
      outgoing.data.uint8[5] = 0xFF;
      outgoing.data.uint8[6] = 0xFF;
     }

    // TWO BYTE REPLIES, ADD HERE
    if( incoming.data.uint8[2] == ENGINE_RPM ) { 
      outgoing.data.uint8[0] = 0x04;  // number of bytes
      outgoing.data.uint8[3] = hibyte;
      outgoing.data.uint8[4] = lobyte;
      outgoing.data.uint8[5] = 0xFF;
      outgoing.data.uint8[6] = 0xFF;
     }

    Serial.print("REPLY ");
    Serial.print(outgoing.id, HEX);
    for(uint8_t i=0;i<8;i++) {
      printhex(outgoing.data.uint8[i]);
    }
    Serial.println();

    CAN0.sendFrame(outgoing);
    lobyte++;
    if(lobyte==0) {
      hibyte++;
    }
  }
  delay(5);
  digitalWrite(BLUE_LED, LOW);
}


void printhex(uint8_t val) {
  Serial.print("\t");
  if (val<0x10) {
      Serial.print("0");
  }
  Serial.print(val, HEX);
}
