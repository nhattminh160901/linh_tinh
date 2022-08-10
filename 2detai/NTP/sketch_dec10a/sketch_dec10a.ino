#include <ESP8266WiFi.h>
#include <Wire.h>
#include "Adafruit_SGP30.h"
#include <Firebase.h>
#include <FirebaseArduino.h>
#include <Servo.h>
#include <DHT.h>

Adafruit_SGP30 sgp;

#define WIFI_SSID "HUEUNI"
#define WIFI_PASSWORD "hueuniair"
#define FIREBASE_HOST "detaintp-default-rtdb.firebaseio.com" //Thay bằng địa chỉ firebase của bạn
#define FIREBASE_AUTH "hh57Wo2BQk2RmMMIHh15bgvgMy1I502c3npVKD6V"   //Không dùng xác thực nên không đổi
#define role1 12
#define role2 13
#define chandht 00
#define loaidht DHT11

Servo servo;
DHT dht(chandht, loaidht);

//uint32_t getAbsoluteHumidity(float temperature, float humidity)
//{
//    // approximation formula from Sensirion SGP30 Driver Integration chapter 3.15
//    const float absoluteHumidity = 216.7f * ((humidity / 100.0f) * 6.112f * exp((17.62f * temperature) / (243.12f + temperature)) / (273.15f + temperature)); // [g/m^3]
//    const uint32_t absoluteHumidityScaled = static_cast<uint32_t>(1000.0f * absoluteHumidity); // [mg/m^3]
//    return absoluteHumidityScaled;
//}

void setup()
{
  servo.write(0);
  servo.attach(14);
  
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  if (! sgp.begin())
  {
    Serial.println("Sensor not found :(");
    while (1);
  }
  Serial.print("Found SGP30 serial #");
  Serial.print(sgp.serialnumber[0], HEX);
  Serial.print(sgp.serialnumber[1], HEX);
  Serial.println(sgp.serialnumber[2], HEX);
  pinMode(role1, OUTPUT);
  pinMode(role2, OUTPUT);
  pinMode(chandht, INPUT);
  dht.begin();
}

void nhiet_do_do_am()
{
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  if (isnan(t))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Firebase.setFloat("NDMT", t);
  Firebase.setFloat("DoAm", h);
  Serial.print(t);
  Serial.println(" °C");
  Serial.print(h);
  Serial.println(" %");

}

void loop()
{
  if (Firebase.getInt("ct/controlall") >= 1)
  {
    digitalWrite(role1, HIGH);
    servo.write(0);
    digitalWrite(role2, LOW);
    Firebase.setFloat("TVOC", sgp.TVOC);
    Firebase.setFloat("eCO2", sgp.eCO2);
    nhiet_do_do_am();
    delay(2000);
  }
  else
  {
    
    if (! sgp.IAQmeasure()) {
      Serial.println("Measurement failed");
    }
    Firebase.setFloat("TVOC", sgp.TVOC);
    Firebase.setFloat("eCO2", sgp.eCO2);
    Serial.print("TVOC: "); Serial.print(sgp.TVOC); Serial.println(" ppb");
    Serial.print("eCO2: "); Serial.print(sgp.eCO2); Serial.println(" ppm");
    if (sgp.TVOC > Firebase.getInt("muc1"))
    {
      digitalWrite(role1, HIGH);
      servo.write(90);
    }
    else
    {
      digitalWrite(role1, LOW);
      servo.write(0);
    }
    if (sgp.TVOC > Firebase.getInt("muc2"))
    {
      digitalWrite(role1, HIGH);
      servo.write(90);
      digitalWrite(role2, HIGH);
    }
    else
    {
      digitalWrite(role2, LOW);
    }
    delay(1000);
  }
}
