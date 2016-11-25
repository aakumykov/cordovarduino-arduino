#include <LiquidCrystal_PCF8574.h>
LiquidCrystal_PCF8574 lcd(0x27);

byte piece;
String tempString = "";
String inputData = "";
unsigned long displayInterval = 200;
unsigned long lastDisplay = 0;
String bytesPrefix = "bytes:";
String dataPrefix = "data:";
int bytesPrefixLength = bytesPrefix.length();
int dataPrefixLength = dataPrefix.length();

void displayBytes(int b){
  String msg = String(b);
  lcd.setCursor(bytesPrefixLength, 0);
  lcd.print(msg);
  String spacer = "";
  for (byte i=0; i<(16-(dataPrefixLength+msg.length())); i++) spacer.concat(" ");
  lcd.print(spacer);
}

void displayData(String d){
  lcd.setCursor(dataPrefixLength, 1);
  lcd.print(d);
  String spacer = "";
  for (byte i=0; i<(16-(dataPrefixLength+d.length())); i++) spacer.concat(" ");
  lcd.print(spacer);
}

void setup() {
  Serial.begin(9600);
  while(!Serial);

  lcd.begin(16,2);
  lcd.setBacklight(1);
  lcd.home(); lcd.clear();
  lcd.setCursor(0,0); lcd.print(bytesPrefix);
  lcd.setCursor(0,1); lcd.print(dataPrefix);
}

void loop() {
  if (Serial.available() > 0) {
      piece = Serial.read();
      if (piece != ';') {
        tempString += String(char(piece));
      } else {
        inputData = tempString;
        tempString = "";
      }
  }
  
  
  if ((millis() - lastDisplay) > displayInterval) {
    if (inputData != "") {
      Serial.print(" RECIEVED: "+inputData);
      displayBytes(inputData.length());
      displayData(inputData);
    }
    lastDisplay = millis();
  }
}

