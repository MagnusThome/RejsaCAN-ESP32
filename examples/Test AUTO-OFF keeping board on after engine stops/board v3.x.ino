/* 

Board >= v3.0

- Yellow LED show status of power voltage, over or under threshold
- Blue LED turns on during countdown delay until board is shut off

*/


#define SECONDS_TO_STAY_ON   5



// -----------------------------------------------------------------------------------

#define FORCE_ON    17
#define SENSE_V_DIG 8
#define SENSE_V_ANA 9

#define BLUE_LED    10
#define YELLOW_LED  11



void setup() {
  pinMode(BLUE_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(SENSE_V_DIG, INPUT_PULLUP);
  pinMode(FORCE_ON, OUTPUT);
  
  digitalWrite(FORCE_ON, HIGH); // When kept high the board will keep running even if the power 
                                // voltage drops below the threshold (indicating that the car engine 
                                // is stopped and it has stopped charging the car battery)
}


// -----------------------------------------------------------------------------------

void loop() {
  shutdowncounter();
  delay(100);
  digitalWrite(YELLOW_LED, digitalRead(SENSE_V_DIG));  
}



void shutdowncounter(void) {
  static unsigned long timestamp;
  static bool countdown = false;
  unsigned long now = millis();

  if( !digitalRead(SENSE_V_DIG) ) {
    if ( countdown == false ) {
      countdown = true;
      timestamp = now;              
      digitalWrite(BLUE_LED, HIGH);   
     }
  }
  else {
    countdown = false;
    digitalWrite(BLUE_LED, LOW);   
  }
  if ( countdown  &&  now - timestamp >= SECONDS_TO_STAY_ON * 1000 ) {
    digitalWrite(FORCE_ON, LOW);   
  }
}
