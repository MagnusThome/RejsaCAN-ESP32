// Board v2.0

#define BLUE_LED               4  // GPIO4
#define YELLOW_LED            12  // GPIO12
#define FORCE_KEEP_ON         25  // GPIO25 
#define POWER_VOLTAGE_ANALOG  26  // GPIO26
#define ENGINE_RUNNING_VOLT_THRESHOLD  2600  // ROUGH APPROXIMATE VALUE. NOT THE EXACT SAME VALUE AS THE THRESHOLD FOR THE DC-DC CONVERTER
#define SECONDS_TO_STAY_ON             5

void setup() {
  Serial.begin(115200);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(FORCE_KEEP_ON, OUTPUT);
  digitalWrite(FORCE_KEEP_ON, HIGH);
}



// -----------------------------------------------------------------------------------

void loop() {

  shutdowncounter(SECONDS_TO_STAY_ON);
  delay(200);

}



// -----------------------------------------------------------------------------------

void shutdowncounter(uint16_t secondsToStayOn) {

  static bool countdown = false;
  static unsigned long timerstart;

  Serial.println(analogRead(POWER_VOLTAGE_ANALOG));

  if( analogRead(POWER_VOLTAGE_ANALOG) < ENGINE_RUNNING_VOLT_THRESHOLD ) {
    if ( countdown == false ) {
      Serial.println("Car engine is stopped, countdown begins...");
      timerstart = millis();                                 // START COUNTDOWN
    }
    countdown = true;
    if ( millis() - timerstart >= secondsToStayOn * 1000 ) {
      digitalWrite(FORCE_KEEP_ON, LOW);                      // TIME TO SHUT DOWN
    }
  }
  else {
    if ( countdown == true ) {
      Serial.println("Car engine is started");
      countdown = false;
    }
  }
}

