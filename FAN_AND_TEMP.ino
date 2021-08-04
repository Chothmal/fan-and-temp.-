#include "LiquidCrystal_I2C.h"
#include "Wire.h"
int tempPin = A1; 
int fan = 11; 
int temp;
int tempMin = 25;
int tempNormal =50;
int tempMax = 75; 
int fanSpeed;
int fanLCD;
LiquidCrystal_I2C lcd(0x20, 20, 4);
const int buzzer=9;
void setup() {
 
pinMode(fan, OUTPUT);
pinMode(tempPin, INPUT);
pinMode(9,OUTPUT);

}
void loop() {
   temp = readTemp();
   if(temp < tempMin)
  {
    fanSpeed=0;
    digitalWrite(11,LOW);
    
  }
   if(temp >= tempMin)
   { 
      fanSpeed = 50; 
      analogWrite(11, 110); 
    
   }
   if(temp >= tempNormal) 
   { 
    fanSpeed=75;
    analogWrite(11, 180); 
    }
    if(temp < tempMax) 
    { 
      
         fanSpeed=100;
         analogWrite(11,255);
         
      }
      if(temp >=75)
      {
        fanSpeed=0;
       digitalWrite(11,LOW);
       digitalWrite(9,HIGH);
        tone(buzzer,1000);
        delay(1000);
        noTone(buzzer);
        delay(1000);
   
        //delay(100000);
      }
fanSpeed = map(temp, tempMin, tempMax, 25, 100); 
fanLCD = map(temp, tempMin, tempMax, 0, 100);
Serial.begin(9600);
lcd.init();
lcd.backlight();
lcd.setCursor(0,0);
lcd.print("TEMP: ");
lcd.print(temp); 
lcd.print("C ");
lcd.setCursor(0,1); 
lcd.print("FANS: ");
lcd.print(fanLCD); 
lcd.print("%");
delay(100);
lcd.clear();
}
 
int readTemp() 
{ 
temp = analogRead(tempPin);
return temp * 0.48828125;
}
