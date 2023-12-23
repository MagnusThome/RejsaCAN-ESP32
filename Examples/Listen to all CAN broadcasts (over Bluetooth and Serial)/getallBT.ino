#include "esp32_can.h"            // https://github.com/collin80/esp32_can AND https://github.com/collin80/can_common
#include "BluetoothSerial.h"

#define BLUE_LED          13  // GPIO13  (GPIO4 on v2.0)
#define YELLOW_LED        12  // GPIO12
#define FORCE_KEEP_ON     25  // GPIO25 


BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  delay(200);
  Serial.println("\nBooting CAN getall");

  pinMode(27, OUTPUT); // THE CAN LIBRARY HAS THIS PIN FOR INTERRUPT FOR CAN1 (UNSUSED HERE) INPUT WITHOUT PULLUP, FORCE TO OUTPUT INSTEAD TO PREVENT ERRONEOUS INTERRUPTS.
  pinMode(FORCE_KEEP_ON, OUTPUT);
  digitalWrite(FORCE_KEEP_ON, HIGH);

  pinMode(BLUE_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  
  SerialBT.begin("RejsaCAN");
  CAN0.setListenOnlyMode(true); 
  if( ! CAN0.begin()) { 
    Serial.println("CAN0 Init Failed");  
    SerialBT.println("CAN0 Init Failed");  
  }
  CAN0.watchFor();
  CAN0.setCallback(0, callback);
}

void loop() {
  unsigned long now = millis();
  delay(150);
  digitalWrite(YELLOW_LED, LOW);
}


void callback(CAN_FRAME *message) {
  digitalWrite(YELLOW_LED, HIGH);
  printFrame(*message);
  printFrameBT(*message);
}


void printFrame(CAN_FRAME &message) {

  Serial.print(millis());
  Serial.print("\t0x");
  Serial.print(message.id,HEX);
  /*
  Serial.print("      \tfid:");
  Serial.print(message.fid);
  Serial.print("  \ttime:");
  Serial.print(message.timestamp);
  Serial.print("  \trtr:");
  Serial.print(message.rtr);
  Serial.print("  \tpri:");
  Serial.print(message.priority);
  Serial.print("  \text:");
  Serial.print(message.extended);
  Serial.print("  \tlen:");
  Serial.print(message.length,DEC);
  Serial.print("  \tdata:  ");
  */
  for(int i = 0;i < message.length; i++) {
    Serial.print("\t0x");
    if (message.data.uint8[i] <= 0xF ) {
      Serial.print("0");
    }
    Serial.print(message.data.uint8[i],HEX);
  }
  Serial.println();
}

void printFrameBT(CAN_FRAME &message) {
  SerialBT.print(millis());
  SerialBT.print("\t0x");
  SerialBT.print(message.id,HEX);
  /*
  SerialBT.print("      \tfid:");
  SerialBT.print(message.fid);
  SerialBT.print("  \ttime:");
  SerialBT.print(message.timestamp);
  SerialBT.print("  \trtr:");
  SerialBT.print(message.rtr);
  SerialBT.print("  \tpri:");
  SerialBT.print(message.priority);
  SerialBT.print("  \text:");
  SerialBT.print(message.extended);
  SerialBT.print("  \tlen:");
  SerialBT.print(message.length,DEC);
  SerialBT.print("  \tdata:  ");
  */
  for(int i = 0;i < message.length; i++) {
    SerialBT.print("\t0x");
    if (message.data.uint8[i] <= 0xF ) {
      SerialBT.print("0");
    }
    SerialBT.print(message.data.uint8[i],HEX);
  }
  SerialBT.println();
}

