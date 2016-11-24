#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

unsigned long readInterval = 5;
unsigned long displayInterval = 200;

unsigned long lastRead = 0;
unsigned long lastDisplay = 0;
String inputData = "";
LiquidCrystal_PCF8574 lcd(0x27);

String readInputData(){
  int incomingBytes = Serial.available();
  String data = "";
  if (incomingBytes > 0) {
    for (int i=0; i<incomingBytes; i++){
      data += String( char(Serial.read()) );
    }
  } else {
    data = "*no*";
  }
  return data;
}


void setup() {
    lcd.begin(16,2);
    lcd.setBacklight(255);
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("*screen coords*");
    
    lcd.setCursor(0,1);
    lcd.print("R:"+String(readInterval)+"ms, D:"+String(displayInterval)+" ms");
    
    delay(2000);
    // стираю первую строку
    lcd.setCursor(0,0); lcd.print("                ");
    
    Serial.begin(9600);
}
 
void loop() {
  unsigned long currentRead = millis();
  if ((currentRead - lastRead) > readInterval) {
      inputData = readInputData();
      lastRead = currentRead;
  }

  unsigned long currentDisplay = millis();
  if ((currentDisplay - lastDisplay) > displayInterval) {
//    lcd.setCursor(0,0); lcd.print("                ");
//    lcd.setCursor(0,0); lcd.print("inBytes:"+String(incomingBytes));
    lcd.setCursor(0,1); lcd.print("                ");
    lcd.setCursor(0,1); lcd.print("inData:"+String(inputData));
    lastDisplay = currentDisplay;
  }
}
