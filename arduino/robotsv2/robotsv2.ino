#include "WiFi.h"
#include "FirebaseESP32.h"
#include <PubSubClient.h>
#include <SoftwareSerial.h>

SoftwareSerial myPort(03, 01);
WiFiClient espClient;
PubSubClient client(espClient);

#define WIFI_SSID "HUEUNI-OFFICE"
#define WIFI_PASSWORD "hueuniair"
#define FIREBASE_HOST "arduino-firebase-vippro-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "DeRJ5uR1rA5nfPL2FCjdUZTKcttOx2Wim4TpUa2P"
#define IO_USERNAME  "nhtminh160901"
#define IO_KEY       "aio_jFSj73eEWC1BTHY2kNnNY7EwaU3o"

#define ln1 27 //dongco3
#define ln2 26 //dongco3
#define ln3 25 //dongco4
#define ln4 33 //dongco4
#define ln5 15 //dongco2
#define ln6 02 //dongco2
#define ln7 00 //dongco1
#define ln8 04 //dongco1
#define ps 13 // phun
#define voice1 22 //voice1
#define voice2 23 //voice2

FirebaseData fbdt;
char state;
int gt1;
void setup()
{
  pinMode(ln1, OUTPUT);
  pinMode(ln2, OUTPUT);
  pinMode(ln3, OUTPUT);
  pinMode(ln4, OUTPUT);
  pinMode(ln5, OUTPUT);
  pinMode(ln6, OUTPUT);
  pinMode(ln7, OUTPUT);
  pinMode(ln8, OUTPUT);
  pinMode(ps, OUTPUT);
  pinMode(voice1, OUTPUT);
  pinMode(voice2, OUTPUT);
  pinMode(32, INPUT);
  pinMode(35, INPUT);
  pinMode(34, INPUT);
  pinMode(5, INPUT);
  pinMode(18, INPUT);
  pinMode(19, INPUT);
  digitalWrite(ln1, LOW);
  digitalWrite(ln2, LOW);
  digitalWrite(ln3, LOW);
  digitalWrite(ln4, LOW);
  digitalWrite(ln5, LOW);
  digitalWrite(ln6, LOW);
  digitalWrite(ln7, LOW);
  digitalWrite(ln8, LOW);
  digitalWrite(ps, LOW);
  digitalWrite(voice1, LOW);
  digitalWrite(voice2, LOW);
  
  digitalWrite(10, LOW);
  pinMode(10, OUTPUT);
  Serial.begin(115200);
  myPort.begin(9600);
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
  client.setServer("io.adafruit.com", 1883);
  client.setCallback(callback);
  client.connect("dk_mc", IO_USERNAME, IO_KEY);
  client.subscribe("nhtminh160901/feeds/dk_mc");
}

void callback(char* topic, byte* payload, unsigned int length)
{
  if ((char)payload[0] == '1')
  {
    digitalWrite(ps, HIGH);
    Serial.println("Da mo");
  }
  else
  {
    digitalWrite(ps, LOW);
    Serial.println("Da tat");
  }
}

void trai()
{
  Serial.println("Trai");
  digitalWrite(ln3, HIGH);
  digitalWrite(ln5, HIGH);
  digitalWrite(ln2, HIGH);
  digitalWrite(ln8, HIGH);
}

void phai()
{
  Serial.println("Phai");
  digitalWrite(ln4, HIGH);
  digitalWrite(ln6, HIGH);
  digitalWrite(ln1, HIGH);
  digitalWrite(ln7, HIGH);
}
void do_line()
{
  digitalWrite(ln1, HIGH);
  digitalWrite(ln3, HIGH);
  digitalWrite(ln5, HIGH);
  digitalWrite(ln7, HIGH);
  int ttcbt = digitalRead(18);
  if (ttcbt == 1)
  {
    trai();
    delay(600);
  }
  ttcbt = digitalRead(35);
  if (ttcbt == 1)
  {
    phai();
  }
}
void dieu_khien_blt()
{
  state = myPort.read();
  if (state=='S')
  {
    Serial.println("Dung");
    digitalWrite(ln1, LOW);
    digitalWrite(ln2, LOW);
    digitalWrite(ln3, LOW);
    digitalWrite(ln4, LOW);
    digitalWrite(ln5, LOW);
    digitalWrite(ln6, LOW);
    digitalWrite(ln7, LOW);
    digitalWrite(ln8, LOW);
    state = ' ';
  }
  //toi
  if (state=='W')
  {
    Serial.println("Toi");
    digitalWrite(ln1, HIGH);
    digitalWrite(ln3, HIGH);
    digitalWrite(ln5, HIGH);
    digitalWrite(ln7, HIGH);
    state = ' ';
  }
  //lui
  if (state=='B')
  {
    Serial.println("Lui");
    digitalWrite(ln2, HIGH);
    digitalWrite(ln4, HIGH);
    digitalWrite(ln6, HIGH);
    digitalWrite(ln8, HIGH);
    state = ' ';
  }
  //xoay1
  if (state=='A')
  {
    Serial.println("Trai");
    trai();
    state = ' ';
  }
  //xoay2
  if (state=='D')
  {
    Serial.println("Phai");
    phai();
    state = ' ';
  }
}

void dieu_khien_wifi()
{
  Firebase.getString(fbdt, "/dieu_khien");
  String val = fbdt.stringData();
  val.remove(0, 2);
  val.remove(1);
  //dung
  if (val=="S")
  {
    Serial.println("Dung");
    digitalWrite(ln1, LOW);
    digitalWrite(ln2, LOW);
    digitalWrite(ln3, LOW);
    digitalWrite(ln4, LOW);
    digitalWrite(ln5, LOW);
    digitalWrite(ln6, LOW);
    digitalWrite(ln7, LOW);
    digitalWrite(ln8, LOW);
    delay(200);
  }
  //toi
  if (val=="W")
  {
    Serial.println("Toi");
    digitalWrite(ln2, HIGH);
    digitalWrite(ln4, HIGH);
    digitalWrite(ln6, HIGH);
    digitalWrite(ln8, HIGH);
    delay(200);
  }
  //lui
  if (val=="B")
  {
    Serial.println("Lui");
    digitalWrite(ln1, HIGH);
    digitalWrite(ln3, HIGH);
    digitalWrite(ln5, HIGH);
    digitalWrite(ln7, HIGH);
    delay(200);
  }
  //xoay1
  if (val=="A")
  {
    Serial.println("Test1");
    digitalWrite(ln3, HIGH);
    digitalWrite(ln5, HIGH);
    digitalWrite(ln2, HIGH);
    digitalWrite(ln8, HIGH);
    delay(200);
  }
  //xoay2
  if (val=="D")
  {
    Serial.println("Test2");
    digitalWrite(ln4, HIGH);
    digitalWrite(ln6, HIGH);
    digitalWrite(ln1, HIGH);
    digitalWrite(ln7, HIGH);
    delay(200);
  }
}
void loop()
{
  
  Firebase.getInt(fbdt, "sv/voice1");
  gt1 = fbdt.intData();
  Firebase.getString(fbdt, "/voice2");
  String gt2 = fbdt.stringData();
  Firebase.getString(fbdt, "/phun");
  String phun = fbdt.stringData();
  Firebase.getString(fbdt, "/typedk");
  String dk = fbdt.stringData();
  if (phun == "0")
  {
    digitalWrite(ps, HIGH);
    Serial.println("mo");
  }
  else if (phun=="1")
  {
    digitalWrite(ps, LOW);
  }
  else
  {
    client.loop();
  }
  dk.remove(0, 2);
  dk.remove(1);
  if (dk == "W")
  {
    dieu_khien_wifi();
  }
  else if (dk == "B")
  {
    dieu_khien_blt();
  }
  else if (dk == "D")
  {
    do_line();
  }
  if (gt1 == 0)
  {
    digitalWrite(voice1, HIGH);
    Serial.println("da_mo1");
  }
  else
  {
    digitalWrite(voice1, LOW);
  }
  if (gt2 == "0")
  {
    digitalWrite(voice2, HIGH);
    Serial.println("da_mo2");
  }
  else
  {
    digitalWrite(voice2, LOW);
  }  
}
