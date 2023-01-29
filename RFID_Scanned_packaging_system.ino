#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN D8
#define RST_PIN D0
#define white D2
#define red D4
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;
// Init array that will store new NUID
byte nuidPICC[4];
String mystr;
int lastval;
int a=0;
int b=0;
int c=0;
int d=0;

void setup() {
 Serial.begin(115200);
 pinMode(white,OUTPUT);
 pinMode(red,OUTPUT);
 SPI.begin(); // Init SPI bus
 rfid.PCD_Init(); // Init MFRC522
 Serial.println();
 Serial.print(F("Reader :"));
 rfid.PCD_DumpVersionToSerial();
 for (byte i = 0; i < 6; i++) {
   key.keyByte[i] = 0xFF;
 }
 Serial.println();
 Serial.println(F("This code scan the MIFARE Classic NUID."));
 Serial.print(F("Using the following key:"));
// printHex(key.keyByte, MFRC522::MF_KEY_SIZE);
}

void loop() {
 // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
 if ( ! rfid.PICC_IsNewCardPresent())
   return;
 // Verify if the NUID has been readed
 if ( ! rfid.PICC_ReadCardSerial())
   return;
// Serial.print(F("PICC type: "));
 MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
// Serial.println(rfid.PICC_GetTypeName(piccType));
 // Check is the PICC of Classic MIFARE type
 if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
     piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
     piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
   Serial.println(F("Your tag is not of type MIFARE Classic."));
   return;
 }
lastval = int(rfid.uid.uidByte[0]);
Serial.println(lastval);
switch (rfid.uid.uidByte[0]){
  case 119:
     mystr = "Package 1: abc";
     digitalWrite(white,HIGH);
     delay(500);
     digitalWrite(white,LOW);
     a=a+1;
     b=0;
     c=0;
     d=0;
     break;
  case 231:
     mystr = "Package 2: abc";
     digitalWrite(white,HIGH);
     delay(500);
     digitalWrite(white,LOW);
     b=b+1;
     a=0;
     c=0;
     d=0;
     break;
  case 103:
     mystr = "Package 3: abc";
     digitalWrite(white,HIGH);
     delay(500);
     digitalWrite(white,LOW);
     c=c+1;
     a=0;
     b=0;
     d=0;
     break;
  case 198:
     mystr = "Package 4: abc";
     digitalWrite(white,HIGH);
     delay(500);
     digitalWrite(white,LOW);
     d=d+1;
     a=0;
     b=0;
     c=0;
     break;
  default:
     a=0;
     b=0;
     c=0;
     d=0;
     mystr = "Wrong Package";
     digitalWrite(red,HIGH);
     delay(500);
     digitalWrite(red,LOW);
     break;
}
if(a>1||b>1||c>1||d>1){
  Serial.println("Package Repeated");
}
 Serial.println(mystr);
 rfid.PICC_HaltA();
 // Stop encryption on PCD
 rfid.PCD_StopCrypto1();
}
