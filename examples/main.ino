#define LED_BLUE           4  // GPIO4
#define LED_YELLOW        12  // GPIO12
#define FORCE_KEEP_ON     25  // GPIO25 
#define POWER_IN_VOLTAGE  26  // GPIO26

#define ENGINE_STOPPED_VOLTAGE_THRESHOLD  900
#define SECONDS_TO_FORCE_ON               180


void setup() {

  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  
  pinMode(FORCE_KEEP_ON, OUTPUT);
  digitalWrite(FORCE_KEEP_ON, HIGH);

}




void loop() {

  unsigned long now = millis();
  unsigned long countdown = 0;


  if( analogRead( POWER_IN_VOLTAGE) > ENGINE_STOPPED_VOLTAGE_THRESHOLD ) {
    countdown = 0;
  }
  else {
    if ( countdown == 0 ) {
      countdown = millis();                             // TIMESTAMP OF WHEN ENGINE STOPPED
    }
    if ( countdown >= SECONDS_TO_FORCE_ON * 1000 ) {    // TIME TO SHUT BOARD OFF
      digitalWrite(FORCE_KEEP_ON, LOW);   
    }
  }
 

}
