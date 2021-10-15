#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "DHTesp.h"
DHTesp dht;
char auth[] = "ZIRW-PXRkTrtbGe4IfVN38aTQWKiMIHy"; //Token cua blynk
char ssid[] = "HUEUNI-OFFICE";     //tên wifi
char pass[] = "hueuniair";      //mật khẩu wifi
float nhiet_do;
int   do_am;
void setup() 
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.setup(0, DHTesp::DHT22); // Connect DHT sensor to GPIO 0
  
  delay(1000);
  Blynk.notify("Đã kết nối wifi");
   pinMode(D0,        INPUT);
}

void doc_DHT()
{
   do_am    = dht.getHumidity();
   nhiet_do = dht.getTemperature();
   delay(100);
  Serial.print("Do am: ");
Serial.print(do_am);
Serial.print(" %\t");
Serial.print("Nhiet do: ");
Serial.print(nhiet_do);
Serial.println(" *C ");
delay(2000);     
}
void loop() 
{
  int tt = digitalRead(D0);
  if(tt == 0)   Blynk.virtualWrite(V0,"MƯA MƯA MƯA MƯA MƯA");
  else          Blynk.virtualWrite(V0,"NHATSUUTUPHAT LEN KHOA LAM MACH");
  doc_DHT();
  Blynk.run(); 
  Blynk.virtualWrite(V3, nhiet_do );
  Blynk.virtualWrite(V2, do_am);
}
