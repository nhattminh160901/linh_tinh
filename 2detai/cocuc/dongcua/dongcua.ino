#include <Firebase.h>
#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
#include <Servo.h>

#define WIFI_SSID "HUEUNI"   //Thay wifi và mật khẩu
#define WIFI_PASSWORD "hueuniair"
#define FIREBASE_HOST "arduino-firebase-vippro-default-rtdb.firebaseio.com" //Thay bằng địa chỉ firebase của bạn
#define FIREBASE_AUTH "DeRJ5uR1rA5nfPL2FCjdUZTKcttOx2Wim4TpUa2P"   //Không dùng xác thực nên không đổi
#define ledPin 02
Servo servo;
void setup()
{
  servo.write(70);
  servo.attach(12);
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
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  if (Firebase.getInt("ct/door") == 1)
  {
    servo.write(0);
    digitalWrite(ledPin, LOW);
    delay(15000);
  }
  else
  {
    servo.write(70);
    digitalWrite(ledPin, HIGH);
  }
}
  
