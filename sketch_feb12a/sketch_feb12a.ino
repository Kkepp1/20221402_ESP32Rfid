
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         4
#define SS_PIN          19
#define CLK_PIN         21
#define MOSI_PIN         23
#define MISO_PIN         22
int UID[4], i;
MFRC522 mfrc522(SS_PIN, RST_PIN);
void setup() 
{
 
  Serial.begin(9600);
 while (!Serial);
  SPI.begin(CLK_PIN,MISO_PIN,MOSI_PIN);  
 mfrc522.PCD_Init();
mfrc522.PCD_DumpVersionToSerial(); // Show details of PCD - MFRC522 Card Reader details
Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));

}

void loop() 
{
  
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  { 
    return; 
  }
  
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {  
    return;  
  }
  
  Serial.print("UID của thẻ: ");   
  
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  { 
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
       
    UID[i] = mfrc522.uid.uidByte[i];
    
    Serial.print(UID[i]); 
  }
  
  Serial.println("   ");
  
  mfrc522.PICC_HaltA();  
  mfrc522.PCD_StopCrypto1();
 // delay(1000);

}
