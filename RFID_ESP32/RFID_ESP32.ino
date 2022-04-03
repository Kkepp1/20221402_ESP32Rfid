
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         19
#define SS_PIN          12
#define CLK_PIN         21
#define MOSI_PIN         23
#define MISO_PIN         22
int UID[4], i;
MFRC522 mfrc522(SS_PIN, RST_PIN);
void setup() 
{
  Serial.begin(9600);
  pinMode(13,OUTPUT);
 while (!Serial);
  SPI.begin(CLK_PIN,MISO_PIN,MOSI_PIN);  
 mfrc522.PCD_Init();
 mfrc522.PCD_SetAntennaGain(mfrc522.RxGain_max);
 mfrc522.PCD_DumpVersionToSerial(); // Show details of PCD - MFRC522 Card Reader details
 Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
 digitalWrite(13,HIGH);

}

void loop() 
{
 // nhận biết thẻ mới hơi cũ , đọc thẻ cũ
 
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  { 
    return; 
    Serial.println("KO Co");
  }
 // đọc toàn bộ dữ liệu có trong thẻ 
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {  
    return;  
  }
 // gửi lên serial chỉ id của thẻ, 
  Serial.print("UID của thẻ: ");   
  
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  { 
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
       
    UID[i] = mfrc522.uid.uidByte[i];
    
    Serial.print(UID[i],HEX); 
  }
  
  Serial.println("   ");
  
  mfrc522.PICC_HaltA();// tạm ngưng đọc  
  mfrc522.PCD_StopCrypto1();// ngưng sử dụng rc522


}
