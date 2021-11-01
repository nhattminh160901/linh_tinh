#include <DHT.h>
#include <ESP8266WiFi.h>
#include <Firebase.h>
#include <FirebaseArduino.h>
#define WIFI_SSID "HUEUNI"   //Thay wifi và mật khẩu
#define WIFI_PASSWORD "hueuniair"
#define loaidht DHT22
#define chandht 14
#define FIREBASE_HOST "arduino-firebase-vippro-default-rtdb.firebaseio.com" //Thay bằng địa chỉ firebase của bạn
#define FIREBASE_AUTH "DeRJ5uR1rA5nfPL2FCjdUZTKcttOx2Wim4TpUa2P"   //Không dùng xác thực nên không đổi

DHT dht(chandht, loaidht);
char state;
void setup()
{
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
  pinMode(chandht, INPUT);
  dht.begin();
}
void nhiet_do_do_am()
{
  float t = dht.readTemperature();

  if (isnan(t))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.println(t);
  Firebase.setFloat("temp", t);
}
void loop()
{
  nhiet_do_do_am();
  delay(5000);
}
