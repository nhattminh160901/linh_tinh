#include <SoftwareSerial.h>
SoftwareSerial mySerial(11, 8 ); // chân 2 và chân 3 arduino nối lần lượt với chân TX và RX của bluetooth

#define toi_phai     6
#define lui_phai     5 

#define toi_trai    10
#define lui_trai     9


char state;
void setup()
{
  Serial.begin(9600); //truyền dữ liệu lên máy tính
  mySerial.begin(9600); //truyền dữ liệu với bluetooth
  
  pinMode(toi_trai, OUTPUT);
  pinMode(lui_trai, OUTPUT);
  pinMode(toi_phai, OUTPUT);
  pinMode(lui_phai, OUTPUT);
  
  analogWrite(toi_trai,  0);
  analogWrite(lui_trai,  0);
  analogWrite(toi_phai,  0);
  analogWrite(lui_phai,  0);
  Serial.println("da khoi dong xong");
  delay(1000);
}
void dieu_khien()
{
  //đợi nhận giá trị từ bluetooth
  if (mySerial.available())
  {
    state = mySerial.read();
    Serial.println(state);
    //dừng
    if(state=='S')
    {
      analogWrite(toi_trai, 0); // dừng động cơ bên trái đặt 00
      analogWrite(lui_trai, 0);
      analogWrite(toi_phai, 0); // dừng động cơ bên phải đặt 00
      analogWrite(lui_phai, 0);
      state=' ';
    }
    //chạy tới
    if(state=='F')
    {
      analogWrite(toi_trai, 150); //tiến động cơ bên trái đặt 10
      analogWrite(lui_trai, 0);
      analogWrite(toi_phai, 150); //tiến động cơ bên phải đặt 10
      analogWrite(lui_phai, 0);
      state=' ';
    }
    //chạy lui
    if(state=='B')
    {
      analogWrite(toi_trai, 0); //lùi động cơ bên trái đặt 01
      analogWrite(lui_trai, 150);
      analogWrite(toi_phai, 0); //lùi động cơ bên phải đặt 01
      analogWrite(lui_phai, 150);
      state=' ';
    }
    //rẻ trái
    if(state=='L')
    {
      analogWrite(toi_trai, 0); //dừng động cơ bên trái đặt 00
      analogWrite(lui_trai, 0);
      analogWrite(toi_phai, 150);//tiến động cơ bên phải đặt 10
      analogWrite(lui_phai, 0);
      state=' ';
    }
    //rẻ phải
    if(state=='R')
    {
      analogWrite(toi_trai, 150);
      analogWrite(lui_trai, 0);
      analogWrite(toi_phai, 0);
      analogWrite(lui_phai, 0);
      state=' ';
    }
    //tới - phải
    if(state=='G')
    {
      analogWrite(toi_trai, 150);
      analogWrite(lui_trai, 0);
      analogWrite(toi_phai, 100);
      analogWrite(lui_phai, 0);
      state=' ';
    }
    //tới - trái
    if(state=='I')
    {
      analogWrite(toi_trai, 100);
      analogWrite(lui_trai, 0);
      analogWrite(toi_phai, 150);
      analogWrite(lui_phai, 0);
      state=' ';
    }
    //lui - phải
    if(state=='J')
    {
      analogWrite(toi_trai, 0);
      analogWrite(lui_trai, 150);
      analogWrite(toi_phai, 0);
      analogWrite(lui_phai, 100);
      state=' ';
    }
    //lui - trái
    if(state=='H')
    {
      analogWrite(toi_trai, 0);
      analogWrite(lui_trai, 100);
      analogWrite(toi_phai, 0);
      analogWrite(lui_phai, 150);
      state=' ';
    }
  }
}
void loop()
{
  dieu_khien();
}
