  
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
int UVOUT = A0; //Output from the sensor
int REF_3V3 = A1; //3.3V power on the Arduino board
 
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
 
void setup()
{
 
  pinMode(UVOUT, INPUT);
  pinMode(REF_3V3, INPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //initialize with the I2C addr 0x3C (128x64)
  display.clearDisplay();
  
}
 
void loop()
{
  int uvLevel = averageAnalogRead(UVOUT);
  int refLevel = averageAnalogRead(REF_3V3);
  
  //Use the 3.3V power pin as a reference to get a very accurate output value from sensor
  float outputVoltage = 3.3 / refLevel * uvLevel;
  
  float uvIntensity = mapfloat(outputVoltage, 0.95 , 2.8, 0.0, 15.0); //Convert the voltage to a UV intensity level
 

 
  display.setCursor(20,0);  //oled display
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("INTENSIDAD UV");
  
  display.setCursor(10,10);  //oled display
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println(uvIntensity);
  
  display.setCursor(75,15);  //oled display
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("mW/cm^2");
  display.display();
 
  delay(300);
  display.clearDisplay();
}
 
//Takes an average of readings on a given pin
//Returns the average
int averageAnalogRead(int pinToRead)
{
  byte numberOfReadings = 8;
  unsigned int runningValue = 0; 
 
  for(int x = 0 ; x < numberOfReadings ; x++)
    runningValue += analogRead(pinToRead);
  runningValue /= numberOfReadings;
 
  return(runningValue);
}
 
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
