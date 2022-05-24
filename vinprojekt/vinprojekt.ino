#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>

#define SS_PIN 10
#define RST_PIN 9
#define buttonPin 2
#define ledPin 3
bool buttonState = false;
String x[10];
String xime[10];
int index=0;


LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.


void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  lcd.begin(16, 2);
  lcd.print("Dobrodosli");
  lcd.setCursor(0,1);
 
}
void loop() 
{

  if(digitalRead(buttonPin) == HIGH){
    buttonState = true;
     lcd.setCursor(0,1);
    lcd.print("                      ");
    lcd.setCursor(0,1);
    lcd.print("Prisloni kartico");
  }
  
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  
  if(buttonState){
    lcd.setCursor(0,1);
    lcd.print("                      ");
    lcd.setCursor(0,1);
    lcd.print("Enter name");
       while(Serial.available() == 0) {
    }
    String ime = Serial.readString();
    Serial.println(ime);
    addUID(content,ime);
    return;
  }
  
  for(int i=0; i<10;i++){
    content.toUpperCase();
    if (content == x[i]) //change here the UID of the card/cards that you want to give access
    {
      String auth = "Zivjo ";
      auth.concat(xime[i]);
      lcd.setCursor(0,1);
      lcd.print("                      ");
      lcd.setCursor(0,1);
      lcd.print(auth.substring(0,auth.length()-1));
      Serial.println(auth.substring(0));
      digitalWrite(ledPin, HIGH);
      delay(1000);
      digitalWrite(ledPin, LOW);
      lcd.setCursor(0,1);
      lcd.print("                 ");
      return;
    }
  }
  lcd.setCursor(0,1);
  lcd.print("                 ");
  lcd.setCursor(0,1);
  lcd.print("Dostop zavrnjen");
  Serial.println("Dostop zavrnjen");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("                 ");
  lcd.setCursor(0,1);
  digitalWrite(ledPin, LOW);
}

void addUID(String a, String ime){
    a.toUpperCase();
    x[index] = a.substring(0);
    xime[index] = ime.substring(0);
    index++;
    if(index >= 10){
      index=0;
    }
    buttonState = false;
    lcd.setCursor(0,1);
    lcd.print("                       ");
}
 
