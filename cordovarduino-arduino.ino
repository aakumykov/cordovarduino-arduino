#include <LiquidCrystal_PCF8574.h>
LiquidCrystal_PCF8574 lcd(0x27);

byte piece;
String tempString = "";
String inputData = "";
unsigned long displayInterval = 500;
unsigned long lastDisplay = 0;

void displayString(String msg){
  lcd.home();
  lcd.clear();
  lcd.print(msg);
  Serial.println(msg);
}

void waitForData(){
  if (Serial.available() > 0) {
      piece = Serial.read();
      if (piece != ';') {
        tempString += String(char(piece));
      } else {
        inputData = tempString;
        tempString = "";
      }
  }
}

void setup() {
  Serial.begin(9600);
  while(!Serial);

  lcd.begin(16,2);
  lcd.setBacklight(1);
  lcd.home(); lcd.clear();

  displayString("Setup :-* ");
  delay(1000);
}

void loop() {
  waitForData();

  
  if ((millis() - lastDisplay) > displayInterval) {
    if (inputData != "") {
      if (inputData=="start") {
        displayString("ROCKET LAUNCH");
      } else {
         displayString("R: "+inputData);
      }
    }
    lastDisplay = millis();
  }
}

