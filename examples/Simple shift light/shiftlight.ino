#include "esp32_can.h"            // https://github.com/collin80/esp32_can AND https://github.com/collin80/can_common

#define BLUE_LED          13  // GPIO13  (GPIO4 on v2.0)
#define YELLOW_LED        12  // GPIO12

#define CANPID_RPM          0x0C
#define CAN_REQST_ID        0x7DF 
#define CAN_REPLY_ID        0x7E8

uint16_t rpm;


void setup() {
  Serial.begin(115200);
  pinMode(27, OUTPUT); // THE CAN LIBRARY HAS THIS PIN FOR INTERRUPT FOR CAN1 (UNSUSED HERE) INPUT WITHOUT PULLUP, FORCE TO OUTPUT INSTEAD TO PREVENT ERRONEOUS INTERRUPTS.
  
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(BLUE_LED, LOW);

  CAN0.begin();
  CAN0.watchFor(CAN_REPLY_ID);
  CAN0.setCallback(0, callback);
}

void loop() {
  requestCar();
  Serial.println(rpm);

  if( rpm > 6000 ) { digitalWrite(BLUE_LED, HIGH); }
  else             { digitalWrite(BLUE_LED, LOW);  }

  if( rpm > 6500 ) { digitalWrite(YELLOW_LED, HIGH); }
  else             { digitalWrite(YELLOW_LED, LOW);  }

  delay(100);
}



void requestCar(void) {  
  CAN_FRAME outgoing;
  outgoing.id = CAN_REQST_ID;
  outgoing.length = 8;
  outgoing.extended = 0;
  outgoing.rtr = 0;
  outgoing.data.uint8[0] = 0x02;  
  outgoing.data.uint8[1] = 0x01;  
  outgoing.data.uint8[2] = CANPID_RPM; 
  outgoing.data.uint8[3] = 0x00;
  outgoing.data.uint8[4] = 0x00;  
  outgoing.data.uint8[5] = 0x00;  
  outgoing.data.uint8[6] = 0x00;  
  outgoing.data.uint8[7] = 0x00;  
  CAN0.sendFrame(outgoing);
}


void callback(CAN_FRAME *from_car) {
  if (from_car->data.uint8[2]==CANPID_RPM) {
    uint8_t rpmOBDH = from_car->data.uint8[3];
    uint8_t rpmOBDL = from_car->data.uint8[4];
    rpm = (uint16_t) ((256*rpmOBDH) + rpmOBDL)/(float)4;
  }
}
