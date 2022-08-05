#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>       //libreria oled
#include <Adafruit_SSD1306.h>   //libreria oled
#include <RTClib.h>             //manejo del modulo RTC 

#define ANCHO_PANTALLA 128    // Ancho de la pantalla OLED
#define ALTO_PANTALLA 64      // Alto de la pantalla OLED

#define OLED_RESET -1
Adafruit_SSD1306 oled(OLED_RESET);

int uv=A4, lectura;
RTC_DS3231 rtc;    // crea objeto  de tipo RTC_DS3132


void setup(){
  Serial.begin(9600);    // comunicacion de monitor serial a 9600 bps
  Serial2.begin(9600);    // comunicacion serie entre Arduino y el modulo a 38400 bps 
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C); //initialize with the I2C addr 0x3C (128x64)
  oled.clearDisplay();

   if (! rtc.begin()) {        // si falla la inicializacion del modulo
 Serial.println("Modulo RTC no encontrado !");  // muestra mensaje de error
 while (1);         // bucle infinito que detiene ejecucion del programa
 }
 rtc.adjust(DateTime(__DATE__, __TIME__));  // funcion que permite establecer fecha y horario
            // al momento de la compilacion. Comentar esta linea 
  
  }

void loop(){
  
  lectura=analogRead(uv);
  float voltaje=lectura*(3.3/669);
  int longOnda=map(lectura,0,669,0,1023);
  int indice=map(longOnda,0,1023,0,13);  

  
  Serial.println("INDICE UV:"+String(indice)+"-Rango:"+String(longOnda));
  
  delay(500);

  Serial2.println(String(indice));   // lee monitor serial y envia a Bluetooth


 ///////////////////INICIO CONFIGURACION RTC //////////////////////////////////////// 
 DateTime fecha = rtc.now();


    oled.setTextSize(1);
    oled.setCursor(0,25);
    oled.print(fecha.day());
    oled.setCursor(13,25);
    oled.print("/");
    

    oled.setCursor(20,25);
    oled.print(fecha.month());
       oled.setCursor(33,25);
    oled.print("/");


    oled.setCursor(40,25);
    oled.print(fecha.year());
////////////////////////////////////////
    oled.setCursor(75,25);
    oled.print(fecha.hour());
    oled.setCursor(88,25);
    oled.print("/");
    

    oled.setCursor(95,25);
    oled.print(fecha.minute());
      oled.setCursor(108,25);
    oled.print("/");
    


    oled.setCursor(115,25);
    oled.print(fecha.second());
 
 ///////////////////FIN CONFIGURACION RTC ///////////////////////////////////////////


    

    
/////////////////////////////////////////////////////////////////////////////////////

oled.setCursor(20,0);  //oled display
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.println("INDICE UV");
  
  oled.setCursor(10,10);  //oled display
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.println(indice);
  
  oled.setCursor(45,10);  //oled display
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.println("mW/cm^2");
  oled.display();
 
  delay(300);
  oled.clearDisplay();
    
  }
