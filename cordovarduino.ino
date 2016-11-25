#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>
LiquidCrystal_PCF8574 lcd(0x27);

unsigned long readInterval = 1;
unsigned long displayInterval = 200;
unsigned long lastRead = 0;
unsigned long lastDisplay = 0;
String inputData = "";
char lineEnd = ';';
String bytesPrefix = "inBytes:";
String dataPrefix = "inData:";


//String readInputData(byte len){
String readInputData(){
  int incomingBytes = Serial.available();
  //Serial.println("input bytes: "+String(incomingBytes));
  
  String data = "";
  
  if (incomingBytes > 0) {
    displayBytes(incomingBytes);
    
    for (int i=0; i<incomingBytes; i++) {
      data += String( char(Serial.read()) );
    }
    return data;
  }
  
  return "";
}

void displayBytes(int b){
  String msg = String(b);
  lcd.setCursor(0,msg.length());
  lcd.print(msg);
}

void displayData(String d){
  String msg = String(d);
  lcd.setCursor(0,msg.length());
  lcd.print(msg);
}


void setup() {
    lcd.begin(16,2);
    lcd.setBacklight(255);
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("*screen coords*");
    lcd.setCursor(0,1);
    lcd.print("R:"+String(readInterval)+", D:"+String(displayInterval));

    delay(3000);
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print(bytesPrefix);
    lcd.setCursor(0,1);
    lcd.print(dataPrefix);
    
    Serial.begin(9600);
}
 
void loop() {
  // чтение
  unsigned long currentRead = millis();
  //if ((currentRead - lastRead) > readInterval) {
      String tmpString = "";
      if (Serial.available()) {
        char piece = Serial.read();
        if (piece == lineEnd) {
          inputData = tmpString;
          tmpString = "";
        } else {
          tmpString += piece;
        }
      }
      //lastRead = currentRead;
  //}

  // отображение
  unsigned long currentDisplay = millis();
  if ((currentDisplay - lastDisplay) > displayInterval) {
    if (inputData != "") {
      displayData(inputData);
    }
    lastDisplay = currentDisplay;
  }
}

