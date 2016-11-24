#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

unsigned long readInterval = 200;
unsigned long displayInterval = 500;

unsigned long lastRead = 0;
unsigned long lastDisplay = 0;
String inputData = "";
LiquidCrystal_PCF8574 lcd(0x27);

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
  lcd.setCursor(0,0); lcd.print("                ");
  lcd.setCursor(0,0); lcd.print("inBytes: "+String(b));
}

void displayData(String d){
  lcd.setCursor(0,1); lcd.print("                ");
  lcd.setCursor(0,1); lcd.print("inData: "+d);
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

    displayBytes(0);
    displayData("-");
    
    Serial.begin(9600);
}
 
void loop() {
  // чтение
  unsigned long currentRead = millis();
  if ((currentRead - lastRead) > readInterval) {
      //String newData = readInputData(7);
      String newData = readInputData();
      if (newData != "") inputData = newData;
      lastRead = currentRead;
  }

  // отображение
  unsigned long currentDisplay = millis();
  if ((currentDisplay - lastDisplay) > displayInterval) {
    if (inputData != "") {
      displayData(inputData);
    }
    lastDisplay = currentDisplay;
  }
}

