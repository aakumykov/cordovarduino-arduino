#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x27);
unsigned long readTimeout = 5;
unsigned long displayTimeout = 200;

String readInputData(){
  int incomingBytes = Serial.available();
  if (incomingBytes > 0) {
    String data = "";
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
    lcd.home();
    lcd.clear();
    lcd.print("*CordovArduino*");
    delay(1000);
    
    Serial.begin(9600);
}
 
void loop() {
  unsigned long currentRead = millis();
  if (currentRead - lastRead > readTimeout) {
      String inputData = readInputData();
  } else {
    lastRead = currentRead;
  }
  
    lcd.setCursor(0,0); lcd.print("                ");
    lcd.setCursor(0,0); lcd.print("inBytes:"+String(incomingBytes));
    
    lcd.setCursor(0,1); lcd.print("                ");
    lcd.setCursor(0,1); lcd.print("inData:"+String(inputData));
    
    delay(loopTimeout);
}
