#include <SPI.h>
#include <SD.h>

#define MISO  41
#define MOSI  40
#define SCK   39
#define CS    45

File root;


void setup() {
  Serial.begin(115200);
  Serial.setTxTimeoutMs(0);    // Prevent overflows that slow down Serial.print()
  delay(200);
  SPI.begin( SCK, MISO, MOSI, CS );
}



void loop() {
  if (SD.begin(CS)) {
    root = SD.open("/");
    printDirectory(root, 0);
  }
  else {
    Serial.println("no card... ");
  }
  delay(5000);
}



void printDirectory(File dir, int numTabs) {
   while(true) {
     File entry =  dir.openNextFile();
     if (! entry) {
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');
     }
     Serial.print(entry.name());
     if (entry.isDirectory()) {
       Serial.println("/");
       printDirectory(entry, numTabs+1);
     } else {
       // files have sizes, directories do not
       Serial.print("\t\t");
       Serial.println(entry.size(), DEC);
     }
     entry.close();
   }
}
