#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>       //libreria oled
#include <Adafruit_SSD1306.h>   //libreria oled
#include <RTClib.h>             //manejo del modulo RTC 
#include <Servo.h>              //libreria servo

#define ANCHO_PANTALLA 128    // Ancho de la pantalla OLED
#define ALTO_PANTALLA 64      // Alto de la pantalla OLED

#define OLED_RESET -1
Adafruit_SSD1306 oled(OLED_RESET);


//Definiendo Servos
Servo servohori;
int servoh = 0;
int servohLimitHigh = 160;
int servohLimitLow = 20;

Servo servoverti; 
int ban = 0;
int servov = 0; 
int servovLimitHigh = 160;
int servovLimitLow = 20;

//Asignando LDRs
int ldrtopl = A2; //top left LDR
int ldrtopr = A1; //top right LDR
int ldrbotl = A3; // bottom left LDR
int ldrbotr = A0; // bottom right LDR


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


servohori.attach(10);
    servohori.write(0);
    servoverti.attach(9);
    servoverti.write(0);
    delay(500);
  
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

 ////////////////////INICIO DE SOLAR TRCKER //////////////////////////////////////////

    servoh = servohori.read();
  servov = servoverti.read();
  
  //capturando valores analogicos
  int topl = analogRead(ldrtopl);
  int topr = analogRead(ldrtopr);
  int botl = analogRead(ldrbotl);
  int botr = analogRead(ldrbotr);
  
  // calculando el Promedio
  int avgtop = (topl + topr)   /2;       //Promedio del top
  int avgbot = (botl + botr)   /2;       //Promedio del bottom
  int avgleft = (topl + botl)  /2;      //Promedio del left
  int avgright = (topr + botr) /2;     //Promedio del right

  if (avgtop < avgbot)
  {
    servoverti.write(servov +1);
    if (servov > servovLimitHigh) 
     { 
      servov = servovLimitHigh;
     }
    delay(10);
  }
  else if (avgbot < avgtop)
  {
    servoverti.write(servov -1);
    if (servov < servovLimitLow)
  {
    servov = servovLimitLow;
  }
    delay(10);
  }
  else 
  {
    servoverti.write(servov);
  }
  
  if (avgleft > avgright)
  {
    servohori.write(servoh +1);
    if (servoh > servohLimitHigh)
    {
    servoh = servohLimitHigh;
    }
    delay(10);
  }
  else if (avgright > avgleft)
  {
    servohori.write(servoh -1);
    if (servoh < servohLimitLow)
     {
     servoh = servohLimitLow;
     }
    delay(10);
  }
  else 
  {
    servohori.write(servoh);
  }
  delay(50);
  
////////////// FIN DE SOLAR TRCKER ////////////////////////////////////////

    
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
