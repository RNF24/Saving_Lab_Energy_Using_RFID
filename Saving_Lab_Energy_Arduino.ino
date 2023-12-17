#include <SPI.h>//include the SPI bus library
#include <MFRC522.h>//include the RFID reader library

#define SS_1_PIN 10  //slave select pin
#define SS_2_PIN 8  //slave select pin
#define RST_PIN 9  //reset pin
#define NR_OF_READERS 2
#define LED_PINTU 4
#define LED_LAMPU 5
#define LED_LAB 6
#define SOLENOID 3

byte ssPins[] = {SS_1_PIN, SS_2_PIN};
MFRC522 mfrc522a(SS_1_PIN, RST_PIN); // instatiate a MFRC522 reader object.
MFRC522 mfrc522b(SS_2_PIN, RST_PIN);
MFRC522 mfrc522[NR_OF_READERS] = {mfrc522a, mfrc522b };   // Create MFRC522 instance.
MFRC522::MIFARE_Key key; //create a MIFARE_Key struct named 'key', which will hold the card information

byte nuidPICC[4];

uint8_t reader;
void setup() {
  //create A0 as led
  pinMode(LED_PINTU, OUTPUT);
  pinMode(LED_LAMPU, OUTPUT);
  pinMode(LED_LAB, OUTPUT);
  pinMode(SOLENOID, OUTPUT);
  Serial.begin(9600); // Initialize serial communications with the PC
  SPI.begin(); // Init SPI bus
  for (reader = 0; reader < NR_OF_READERS; reader++) {
    mfrc522[reader].PCD_Init(ssPins[reader], RST_PIN); // Init each MFRC522 card
    Serial.print(F("Reader "));
    Serial.print(reader);
    Serial.print(F(": "));
    mfrc522[reader].PCD_DumpVersionToSerial();
  }
  Serial.println("Scan Kartumu");
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF; //keyByte is defined in the "MIFARE_Key" 'struct' definition in the .h file of the library
  }
}

void loop() {
  // Look for new cards (in case you wonder what PICC means: proximity integrated circuit card)
  if (mfrc522a.PICC_IsNewCardPresent() && mfrc522a.PICC_ReadCardSerial()) {
    String content = "";
    byte letter;
    for (byte i = 0; i < mfrc522a.uid.size; i++)
    {
      Serial.print(mfrc522a.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522a.uid.uidByte[i], HEX);
      content.concat(String(mfrc522a.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(mfrc522a.uid.uidByte[i], HEX));
    }
    Serial.println();
    Serial.print("Message : ");
    content.toUpperCase();
    if (content.substring(1) == "D5 A5 0E AD") //change here the UID of the card/cards that you want to give access
    {
      Serial.println("Milik Asisten Praktikum");
      Serial.println();
      delay(500);
      Serial.println("Door Open");
      digitalWrite(LED_PINTU, HIGH);
      digitalWrite(SOLENOID, HIGH);
      digitalWrite(LED_LAMPU, HIGH);
      digitalWrite(LED_LAB, HIGH);
      delay(500);
      Serial.println("Door Closed");
      digitalWrite(LED_PINTU, LOW);
      digitalWrite(SOLENOID, LOW);
    }

    else if (content.substring(1) == "83 AC 0F 0C") //change here the UID of the card/cards that you want to give access
    {
      Serial.println("Milik Mahasiswa");
      Serial.println();
      delay(500);
      Serial.println("Door Open");
      digitalWrite(LED_PINTU, HIGH);
      digitalWrite(SOLENOID, HIGH);
      digitalWrite(LED_LAMPU, HIGH);
      digitalWrite(LED_LAB, LOW);
      delay(500);
      Serial.println("Door Closed");
      digitalWrite(LED_PINTU, LOW);
      digitalWrite(SOLENOID, LOW);
    }
    else if (content.substring(1) == "E3 CE 95 11") //change here the UID of the card/cards that you want to give access
    {
      Serial.println("Milik Petugas Kebersihan");
      Serial.println();
      delay(500);
      Serial.println("Door Open");
      digitalWrite(LED_PINTU, HIGH);
      digitalWrite(SOLENOID, HIGH);
      digitalWrite(LED_LAMPU, HIGH);
      digitalWrite(LED_LAB, LOW);
      delay(500);
      Serial.println("Door Closed");
      digitalWrite(LED_PINTU, LOW);
      digitalWrite(SOLENOID, LOW);
    }
    else   {
      Serial.println("Access denied");
      delay(500);
      Serial.println("Door Closed");
    }

  }
  else if (mfrc522b.PICC_IsNewCardPresent() && mfrc522b.PICC_ReadCardSerial()) {
    String content = "";
    byte letter;
    for (byte i = 0; i < mfrc522a.uid.size; i++)
    {
      Serial.print(mfrc522a.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522a.uid.uidByte[i], HEX);
      content.concat(String(mfrc522a.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(mfrc522a.uid.uidByte[i], HEX));
    }
    Serial.println();
    Serial.print("Message : ");
    content.toUpperCase();
    if (content.substring(1) == "D5 A5 0E AD") //change here the UID of the card/cards that you want to give access
    {
      Serial.println("Milik Asisten Praktikum");
      Serial.println();
      delay(500);
      Serial.println("Door Open");
      digitalWrite(LED_PINTU, HIGH);
      digitalWrite(SOLENOID, HIGH);
      digitalWrite(LED_LAMPU, HIGH);
      digitalWrite(LED_LAB, HIGH);
      delay(500);
      Serial.println("Door Closed");
      digitalWrite(LED_PINTU, LOW);
      digitalWrite(SOLENOID, LOW);
      digitalWrite(LED_LAMPU, LOW);
      digitalWrite(LED_LAB, LOW);
    }

    else if (content.substring(1) == "83 AC 0F 0C") //change here the UID of the card/cards that you want to give access
    {
      Serial.println("Milik Mahasiswa");
      Serial.println();
      delay(500);
      Serial.println("Door Open");
      digitalWrite(LED_PINTU, HIGH);
      digitalWrite(SOLENOID, HIGH);
      digitalWrite(LED_LAMPU, HIGH);
      digitalWrite(LED_LAB, LOW);
      delay(500);
      Serial.println("Door Closed");
      digitalWrite(LED_PINTU, LOW);
      digitalWrite(SOLENOID, LOW);
      digitalWrite(LED_LAMPU, LOW);
    }

    else if (content.substring(1) == "E3 CE 95 11") //change here the UID of the card/cards that you want to give access
    {
      Serial.println("Milik Petugas Kebersihan");
      Serial.println();
      delay(500);
      Serial.println("Door Open");
      digitalWrite(LED_PINTU, HIGH);
      digitalWrite(SOLENOID, HIGH);
      digitalWrite(LED_LAMPU, HIGH);
      digitalWrite(LED_LAB, LOW);
      delay(500);
      Serial.println("Door Closed");
      digitalWrite(LED_PINTU, LOW);
      digitalWrite(SOLENOID, LOW);
      digitalWrite(LED_LAMPU, LOW);
    }
    else {
      Serial.println("Access denied");
      delay(5000);
      Serial.println("Door Closed");
    }

  }
  //Store UID
  for (reader = 0; reader < NR_OF_READERS; reader++) {
    for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = mfrc522[reader].uid.uidByte[i];
    }
  }
  
}
