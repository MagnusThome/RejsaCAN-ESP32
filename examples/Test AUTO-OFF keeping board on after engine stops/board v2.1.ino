// Board v2.1

#define BLUE_LED            13  // GPIO13
#define YELLOW_LED          12  // GPIO12
#define FORCE_KEEP_ON       25  // GPIO25 
#define ENGINE_RUNNING      14  // GPIO14
#define SECONDS_TO_STAY_ON   5

void setup() {
  pinMode(BLUE_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(FORCE_KEEP_ON, OUTPUT);
  digitalWrite(FORCE_KEEP_ON, HIGH);
  pinMode(ENGINE_RUNNING, INPUT_PULLUP);
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

  digitalWrite(YELLOW_LED, countdown);

  if( !digitalRead(ENGINE_RUNNING) ) {
    if ( countdown == false ) {
      timerstart = millis();                                 // START COUNTDOWN
    }
    countdown = true;
    if ( millis() - timerstart >= secondsToStayOn * 1000 ) {
      digitalWrite(FORCE_KEEP_ON, LOW);                      // TIME TO SHUT DOWN
    }
  }
  else {
    countdown = false;
  }
}

