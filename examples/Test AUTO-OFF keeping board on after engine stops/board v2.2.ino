#include <Arduino.h>


#define BLUE_LED        13
#define YELLOW_LED      12
#define SWITCHED_3V3    27    // OUTPUT   CAN DRIVE 300-400 mA LOADS. DOES NOT PULL LOW, IS ONLY A HIGH DRIVER

#define FORCE_KEEP_ON   25    // OUTPUT   SET TO HIGH TO KEEP BOARD RUNNING WHEN POWER VOLTAGE DROPS BELOW 13,3V (WHEN CAR ENGINE ISN'T CHARGING THE CAR BATTERY)
#define SENSE_V_DIG     14    // INPUT    USE "INPUT_PULLUP". HIGH = CAR ENGINE IS RUNNING AND IS CHARGING CAR BATTERY
#define SENSE_V_ANA     32    // INPUT    UNCALIBRATED ANALOG REPRESENTATION OF CAR BATTERY VOLTAGE

#define WAKE_BY_CAN     4     // GOES HIGH WHEN THERE IS CAN TRAFFIC ON THE CAN BUS. CAN BE USED TO WAKE FROM SLEEP

#define SDA             21    // GENERAL GPIO OR SDA
#define SCL             22    // GENERAL GPIO OR ...
#define SPI_MOSI        23    // GENERAL GPIO OR ...
#define SPI_MISO        19    // GENERAL GPIO OR ...
#define SPI_CLK         18    // GENERAL GPIO OR ...
#define SPI_SS          5     // GENERAL GPIO OR ...

#define GPIO26          26    // GENERAL GPIO
#define GPIO33          33    // GENERAL GPIO


void setup() {
  Serial.begin(115200);
  delay(200);

  pinMode(BLUE_LED, OUTPUT);
  digitalWrite(BLUE_LED, LOW);
  pinMode(YELLOW_LED, OUTPUT);
  digitalWrite(YELLOW_LED, LOW);

  pinMode(SWITCHED_3V3, OUTPUT);
  digitalWrite(SWITCHED_3V3, HIGH);

  pinMode(SENSE_V_DIG, INPUT_PULLUP);
  pinMode(FORCE_KEEP_ON, OUTPUT);
  digitalWrite(FORCE_KEEP_ON, HIGH);
}


void loop() {
  Serial.println(analogRead(SENSE_V_ANA));  
  shutdowncounter();
  delay(500);
}



void shutdowncounter(void) {

  const uint8_t secondsToStayOn = 5;
  static bool countdown = false;
  static unsigned long timerstart;

  if( !digitalRead(SENSE_V_DIG) ) {
    if ( countdown == false ) {
      timerstart = millis();                                 // START COUNTDOWN
      countdown = true;
    }
    if ( millis() - timerstart >= secondsToStayOn * 1000 ) {
      digitalWrite(FORCE_KEEP_ON, LOW);                      // SHUT DOWN
    }
  }
  else {
    countdown = false;
  }
}
