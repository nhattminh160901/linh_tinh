#include <Firebase.h>
#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
#include <string.h>
char state;
String mystring = "";

#define FIREBASE_HOST "sieucapvipprono1-default-rtdb.asia-southeast1.firebasedatabase.app" //Thay bằng địa chỉ firebase của bạn
#define FIREBASE_AUTH "2J0OVglVwG2kDeTYE0GgO7aVjvF2jxcAFhjO5vKm"   //Không dùng xác thực nên không đổi
#define WIFI_SSID "HUEUNI"   //Thay wifi và mật khẩu
#define WIFI_PASSWORD "hueuniair"
void setup() {
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void Tat()
{
  Firebase.setString("Thông tin/_Tắt bật điều hòa", "Tắt");
  state = Serial.read();
  mystring = "";
}
void Bat()
{
  Firebase.setString("Thông tin/_Tắt bật điều hòa", "Bật");
  state = Serial.read();
  mystring = "";
}
void loop()
{
  if (Serial.available())
  {
    state = Serial.read();
    mystring.concat(state);
    Serial.println(mystring);
    
    if(mystring=="ABC121")
    {
      Firebase.setString("Thông tin/Hộ gia đình 1/-Địa chỉ công tơ", mystring);
      Firebase.setFloat("Thông tin/Hộ gia đình 1/Điều hòa/Thời gian sử dụng", 0);

      int i = 0;
      for (i = 0; i < 101; i++)
      {
        Firebase.setFloat("Thông tin/Hộ gia đình 1/Điều hòa/Thời gian sử dụng", i);
        if (i==100)
        {
          Serial.println("Có muốn tắt điều hòa trong nhà không");
        }
      }
      state = Serial.read();
      mystring = ""; 
    }
    if(mystring=="Tat")
    {
      Tat();
    }
    if(mystring=="Bat")
    {
      Bat();
    }
    if(mystring=="ABC122")
    {
      Firebase.setString("Thông tin/Hộ gia đình 2/-Địa chỉ công tơ", mystring);
      Firebase.setFloat("Thông tin/Hộ gia đình 2/Điều hòa/Thời gian sử dụng", 0);

      int i = 0;
      for (i = 0; i < 101; i++)
      {
        Firebase.setFloat("Thông tin/Hộ gia đình 2/Điều hòa/Thời gian sử dụng", i);
        if (i==100)
        {
          Serial.println("Có muốn tắt điều hòa trong nhà không");
        }
      }
      state = Serial.read();
      mystring = ""; 
    }
    if(mystring=="ABC123")
    {
      Firebase.setString("Thông tin/Hộ gia đình 3/-Địa chỉ công tơ", mystring);
      Firebase.setFloat("Thông tin/Hộ gia đình 3/Điều hòa/Thời gian sử dụng", 0);

      int i = 0;
      for (i = 0; i < 101; i++)
      {
        Firebase.setFloat("Thông tin/Hộ gia đình 3/Điều hòa/Thời gian sử dụng", i);
        if (i==100)
        {
          Serial.println("Có muốn tắt điều hòa trong nhà không");
        }
      }
      state = Serial.read();
      mystring = ""; 
    }
    if (mystring=="ABC124")
      {
      Firebase.setString("Thông tin/Hộ gia đình 4/-Địa chỉ công tơ", mystring);
      Firebase.setFloat("Thông tin/Hộ gia đình 4/Điều hòa/Thời gian sử dụng", 0);

      int i = 0;
      for (i = 0; i < 101; i++)
      {
        Firebase.setFloat("Thông tin/Hộ gia đình 4/Điều hòa/Thời gian sử dụng", i);
        if (i==100)
        {
          Serial.println("Có muốn tắt điều hòa trong nhà không");
        }
      }
      state = Serial.read();
      mystring = "";
      }
  }
}
