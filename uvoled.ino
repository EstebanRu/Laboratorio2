#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>       //libreria oled
#include <Adafruit_SSD1306.h>   //libreria oled

#define OLED_RESET -1
Adafruit_SSD1306 oled(OLED_RESET);


int uv=A4, lectura;    //pin lectura sensor

void setup(){
  Serial.begin(9600);    // comunicacion de monitor serial a 9600 bps
  Serial2.begin(9600);    // comunicacion serie entre Arduino
                          //y bluetooth a 38400 bps 
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C); //iniciamos I2C 
                                          //posicion de memoria 0x3C
  oled.clearDisplay();
  
  
  }

void loop(){
  
  lectura=analogRead(uv);
  float voltaje=lectura*(3.3/669);
  int longOnda=map(lectura,0,669,0,1023);
  int indice=map(longOnda,0,1023,0,15);  

  
  Serial.println("INDICE UV:"+String(indice)+"-Rango:"+String(longOnda));
  
  delay(2000);

  Serial2.println(String(indice));   // lee monitor serial
                                     //y envia a Bluetooth


oled.setCursor(20,0);  //oled display
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.println("INDICE UV");
  
  oled.setCursor(10,10);  //oled display
  oled.setTextSize(1);
  oled.println(indice);
  
  oled.setCursor(45,10);  //oled display
  oled.setTextSize(1);
  oled.println("mW/cm^2");
  oled.display();
 
  delay(300);
  oled.clearDisplay();
  }
