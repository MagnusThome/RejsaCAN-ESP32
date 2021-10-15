#define BLUE_LED           4  // GPIO4
#define YELLOW_LED        12  // GPIO12
#define FORCE_KEEP_ON     25  // GPIO25 
#define POWER_IN_VOLTAGE  26  // GPIO26

#define ENGINE_STOPPED_VOLT_THRESHOLD  900
#define SECONDS_TO_STAY_ON             180


void shutdowncounter(unsigned long secondsToStayOn);




// -----------------------------------------------------------------------------------

void setup() {

  pinMode(BLUE_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  
  pinMode(FORCE_KEEP_ON, OUTPUT);
  digitalWrite(FORCE_KEEP_ON, HIGH);

}



// -----------------------------------------------------------------------------------

void loop() {

  shutdowncounter(SECONDS_TO_STAY_ON);

}



// -----------------------------------------------------------------------------------

void shutdowncounter(unsigned long secondsToStayOn) {

  static bool countdown = false;
  static unsigned long timerstart;

  if( analogRead(POWER_IN_VOLTAGE) < ENGINE_STOPPED_VOLT_THRESHOLD ) {
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


// -----------------------------------------------------------------------------------
