// Board >= v2.1

#define BLUE_LED            13  // GPIO13
#define YELLOW_LED          12  // GPIO12
#define FORCE_KEEP_ON       25  // GPIO25 
#define ENGINE_ISRUNNING    14  // GPIO14
#define SECONDS_TO_STAY_ON   5


void setup() {
  pinMode(BLUE_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  
  pinMode(FORCE_KEEP_ON, OUTPUT);
  digitalWrite(FORCE_KEEP_ON, HIGH);

  pinMode(ENGINE_ISRUNNING, INPUT_PULLUP);
}



// -----------------------------------------------------------------------------------

void loop() {

  shutdowncounter();
  delay(100);
  digitalWrite(YELLOW_LED, digitalRead(ENGINE_ISRUNNING));   

}



void shutdowncounter(void) {
  static unsigned long timestamp;
  static bool countdown = false;
  unsigned long now = millis();

  if( !digitalRead(ENGINE_ISRUNNING) ) {
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
    digitalWrite(FORCE_KEEP_ON, LOW);   
  }
}
