#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 15
#define RST_PIN 16
MFRC522 mfrc522(SS_PIN, RST_PIN);
// Init array that will store new NUID
int UID[4], i;
void setup() {
 
  Serial.begin(9600);
 while (!Serial);
  SPI.begin();  
 mfrc522.PCD_Init();
// mfrc522.PCD_SetAntennaGain(mfrc522.RxGain_max);
mfrc522.PCD_DumpVersionToSerial(); // Show details of PCD - MFRC522 Card Reader details
Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}
void loop() {
    if ( ! mfrc522.PICC_IsNewCardPresent()) 
    {  
      return;   
    }

  if ( ! mfrc522.PICC_ReadCardSerial()) 
    {    
      return;    
    }

mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
 
}
