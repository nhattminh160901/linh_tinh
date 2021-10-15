#include <FirebaseArduino.h>
#include <Firebase.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>


#define firebase_led    D3

SoftwareSerial mySerial_0(5, 12);   //D1=RX, D6=TX  : nhận tín hiệu từ nhiệt độ
SoftwareSerial mySerial_2(4, 13);   //D2=RX, D7=TX  : đưa về maika
SoftwareSerial mySerial_1(14, 16);  //D5=RX, D0=TX  : nhận tín hiệu từ spo2
String  inString_0 = "";
String  inString_1 = "";
String  chuoi_ma_rfid;
int     spo2;
float   nhiet_co_the ;
int tam_1, tam_2;
String chuoi_data;
String newRFID;
int tam_3;
String chuoi_nhiet;
void setup() 
{
  Serial.begin(9600);
  
  mySerial_0.begin(115200);     //nhận arduino 1 đo nhiệt
  mySerial_1.begin(19200);      //nhận arduino 2 đo spo2
  mySerial_2.begin(4800);       //truyền về maika
  pinMode(firebase_led,    OUTPUT);
  digitalWrite(firebase_led, LOW);
  WiFi.disconnect();
  WiFi.begin("HUEUNI","hueuniair");/////////////////////////////////////////ghi mật khẩu với pass của  anh
  while (WiFi.waitForConnectResult() != WL_CONNECTED )
  { Serial.println(".");delay(200);}
  Serial.println("da vao duoc Wifi");
  Firebase.begin("sieucapvipprono1-default-rtdb.asia-southeast1.firebasedatabase.app"); ///////////////////////firebase của anh
  Serial.println("da ket noi duuoc voi firebase");
  digitalWrite(firebase_led, HIGH);
//  Firebase.setString("DataFromeEsp/datagiatrido","error done2");
 // Firebase.setString("DataFromeEsp/datathongtin","error done1");
}
void truyen_nhiet_do_qua_maika()
{
  tam_3 = nhiet_co_the*10;
  chuoi_nhiet = String(tam_3);
  mySerial_2.print(chuoi_nhiet); 
  mySerial_2.print("a"); 
}
void loop() 
{
  //newRFID = Firebase.getString("/Flg_newRFID");
  while (mySerial_0.available()>0) 
  {    
    char inChar = mySerial_0.read();
    
    if (inChar == 'a' )
    { 
      chuoi_ma_rfid = String(inString_0);
      inString_0 = "";
      nhiet_co_the = spo2 = 0;
      chuoi_data = chuoi_ma_rfid + "##" + String(spo2) + "##" + String(nhiet_co_the);
      Serial.println(chuoi_data);
      bool ret_false = true;
      int cnt =0;
      /*
      while(ret_false ==true){
      Firebase.setString("DataFromeEsp/datagiatrido",chuoi_data);
      ret_false = Firebase.failed();
      if (ret_false== true) 
      {
        cnt+=1;
        Serial.println("setting /message failed:"+ String(cnt));
      }
      }
      */
      Firebase.setString("DataFromeEsp/datagiatrido",chuoi_data);
      delay(200);
      Firebase.setString("DataFromeEsp/datathongtin",chuoi_data);
      delay(200);
    } 
    else if (inChar == 'b' )
    { 
      tam_1 = inString_0.toInt();
      nhiet_co_the = (tam_1/10.0);
      inString_0 = "";
      truyen_nhiet_do_qua_maika();
      Serial.println(nhiet_co_the);
    } 
    else inString_0 += inChar;
  }  
  
  while (mySerial_1.available()>0) 
  {    
    char inChar = mySerial_1.read();
    
    if (inChar == 'c' )
    { 
      tam_2 = inString_1.toInt();
      spo2  = tam_2;
      inString_1 = "";
      chuoi_data = chuoi_ma_rfid + "##" + String(spo2) + "##" + String(nhiet_co_the);
      Serial.println(chuoi_data);
      nhiet_co_the = spo2 = 0;
      Firebase.setString("DataFromeEsp/datagiatrido",chuoi_data);
      delay(200);
    } 
    else inString_1 += inChar;
  }  
}
