int uv=A4, lectura;
void setup(){
  Serial.begin(9600);
  
  }

void loop(){
  lectura=analogRead(uv);
  float voltaje=lectura*(3.3/669);
  int longOnda=map(lectura,0,669,0,1023);
  int indice=map(longOnda,0,1023,0,13);  
  Serial.println(lectura);
  Serial.println("voltaje:"+String(voltaje)+"v");
  Serial.println("INDICE UV:"+String(indice)+"-Rango:"+String(longOnda));
  
  delay(2000);
  
  
  
  }
