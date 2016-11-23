#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x27);
int loopTimeout = 500;
 
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
    int incomingBytes = Serial.available();
    String inputData = "";
    
    if (incomingBytes > 0) {
        for (int i=0; i<incomingBytes; i++){
          inputData += String(Serial.read());
        }
    } else {
      inputData = "*no input data*";
    }
    
    lcd.clear();
    lcd.home();
    lcd.print(inputData);
    
    delay(loopTimeout);
}
