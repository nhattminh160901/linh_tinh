#include <Adafruit_MLX90614.h>
#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
#define SO_LED_TANG_1  64
#define PIN_1       19

#define toi_trai    11
#define lui_trai    10 

#define toi_phai     6
#define lui_phai     7

#define cb_nhiet    17
#define cb_bom       8
#define bom_nuoc    12
#define led_bom     37
#define loa_bao      4

#define isd1        34
#define isd2        35
#define isd3        36

int i = 0;
int cuoi[64] =   {0, 0, 0, 0, 0, 0, 0, 0,
                  0, 2, 2, 0, 0, 2, 2, 0,
                  0, 2, 2, 0, 0, 2, 2, 0,
                  0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 1, 1, 0, 0, 0,
                  0, 3, 3, 3, 3, 3, 3, 0,
                  0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0};
int cuoi_1[64] = {0, 0, 0, 0, 0, 0, 0, 0,
                  0, 2, 2, 0, 0, 2, 2, 0,
                  0, 2, 2, 0, 0, 2, 2, 0,
                  0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 1, 1, 0, 0, 0,
                  0, 3, 3, 3, 3, 3, 3, 0,
                  0, 0, 3, 0, 0, 3, 0, 0,
                  0, 0, 0, 3, 3, 0, 0, 0};                
Adafruit_NeoPixel led_1 = Adafruit_NeoPixel(SO_LED_TANG_1, PIN_1, NEO_GRB + NEO_KHZ800);

char state;
float nhiet_moi_truong, nhiet_co_the;
int nhiet_do_dat = 38;
void setup()
{
  Serial.begin(9600); //truyền dữ liệu lên máy tính
  Serial3.begin(9600); //truyền dữ liệu với bluetooth
  mlx.begin();
  pinMode(cb_nhiet, INPUT);
  pinMode(cb_bom,   INPUT);
  pinMode(bom_nuoc, OUTPUT);
  pinMode(led_bom,  OUTPUT);
  pinMode(loa_bao,  OUTPUT);
  pinMode(toi_trai, OUTPUT);
  pinMode(lui_trai, OUTPUT);
  pinMode(toi_phai, OUTPUT);
  pinMode(lui_phai, OUTPUT);
  pinMode(isd1,     OUTPUT);
  pinMode(isd2,     OUTPUT);
  pinMode(isd3,     OUTPUT);
  
  analogWrite(toi_trai,  0);
  analogWrite(lui_trai,  0);
  analogWrite(toi_phai,  0);
  analogWrite(lui_phai,  0);
  digitalWrite(bom_nuoc,  HIGH);
  digitalWrite(led_bom,   HIGH);
  digitalWrite(loa_bao,   HIGH);
  digitalWrite(isd1,      LOW);
  digitalWrite(isd2,      LOW);
  digitalWrite(isd3,      LOW);
  Serial.println("da khoi dong xong");
  led_1.begin();  
  led_1.show();
  tat_led();
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" RBOT COVID-19  ");
  lcd.setCursor(0, 1);
  lcd.print("KHOA KTCN - HUE "); 
  delay(1000);
  led_mat_cuoi();
}
void tat_led()
{
  for(int i=0; i<SO_LED_TANG_1; i++)
  {
    led_1.setPixelColor(i,0,0,0);
    led_1.show(); 
  }
}
void led_mat_cuoi()
{
  for(int i=0; i<SO_LED_TANG_1; i++)
  {
    if(cuoi[i] == 0)    led_1.setPixelColor(i,0,0,0);
    if(cuoi[i] == 1)    led_1.setPixelColor(i,0,0,255);
    if(cuoi[i] == 2)    led_1.setPixelColor(i,0,255,0);
    if(cuoi[i] == 3)    led_1.setPixelColor(i,255,0,0);
    led_1.show(); 
  }
}
void led_mat_cuoi_2()
{ 
  for(int i=0; i < SO_LED_TANG_1; i++)
  {
    if(cuoi[i] == 0)    led_1.setPixelColor(i,0,0,0);
    if(cuoi[i] == 1)    led_1.setPixelColor(i,0,0,255);
    if(cuoi[i] == 2)    led_1.setPixelColor(i,0,255,0);
    if(cuoi[i] == 3)    led_1.setPixelColor(i,255,0,0);
    led_1.show();  
  }
  delay(500);
  for(int i=0; i < SO_LED_TANG_1; i++)
  {
    if(cuoi_1[i] == 0)    led_1.setPixelColor(i,0,0,0);
    if(cuoi_1[i] == 1)    led_1.setPixelColor(i,0,0,255);
    if(cuoi_1[i] == 2)    led_1.setPixelColor(i,0,255,0);
    if(cuoi_1[i] == 3)    led_1.setPixelColor(i,255,0,0);
    led_1.show();  
  }
  delay(500);
}
void do_nhiet_do()
{
  nhiet_moi_truong  = mlx.readAmbientTempC();
  nhiet_co_the      = mlx.readObjectTempC(); 
  nhiet_co_the      = nhiet_co_the + 1.5; 
  //Serial.println(nhiet_co_the);
}
void hien_thi_1()
{
  lcd.setCursor(0, 0);
  lcd.print(" ROBOT COVID-19 ");
  lcd.setCursor(0, 1);
  lcd.print("KHOA KTCN-DH HUE");  
}
void hien_thi_2()
{
  lcd.setCursor(0, 0);
  lcd.print("Nhiet do do duoc");
  lcd.setCursor(0, 1);
  lcd.print("          *C    "); 
  lcd.setCursor(5, 1);
  lcd.print(nhiet_co_the);
}
void truyen_nhiet_dien_thoai()
{
  Serial3.println(nhiet_co_the);
}
void dieu_khien()
{
  
  //đợi nhận giá trị từ bluetooth
  if (Serial3.available())
  {
    state = Serial3.read();
    Serial.println(state);
    //dừng
    if(state=='S')
    {
      analogWrite(toi_trai, 0);
      analogWrite(lui_trai, 0);
      analogWrite(toi_phai, 0);
      analogWrite(lui_phai, 0);
      state=' ';
    }
    //chạy tới
    if(state=='F')
    {
      analogWrite(toi_trai, 255);
      analogWrite(lui_trai, 0);
      analogWrite(toi_phai, 255);
      analogWrite(lui_phai, 0);
      state=' ';
    }
    //chạy lui
    if(state=='B')
    {
      analogWrite(toi_trai, 0);
      analogWrite(lui_trai, 255);
      analogWrite(toi_phai, 0);
      analogWrite(lui_phai, 255);
      state=' ';
    }
    //rẻ trái
    if(state=='L')
    {
      analogWrite(toi_trai, 0);
      analogWrite(lui_trai, 0);
      analogWrite(toi_phai, 255);
      analogWrite(lui_phai, 0);
      state=' ';
    }
    //rẻ phải
    if(state=='R')
    {
      analogWrite(toi_trai, 255);
      analogWrite(lui_trai, 0);
      analogWrite(toi_phai, 0);
      analogWrite(lui_phai, 0);
      state=' ';
    }
    //tới - phải
    if(state=='G')
    {
      analogWrite(toi_trai, 250);
      analogWrite(lui_trai, 0);
      analogWrite(toi_phai, 180);
      analogWrite(lui_phai, 0);
      state=' ';
    }
    //tới - trái
    if(state=='I')
    {
      analogWrite(toi_trai, 180);
      analogWrite(lui_trai, 0);
      analogWrite(toi_phai, 250);
      analogWrite(lui_phai, 0);
      state=' ';
    }
    //lui - phải
    if(state=='J')
    {
      analogWrite(toi_trai, 0);
      analogWrite(lui_trai, 255);
      analogWrite(toi_phai, 0);
      analogWrite(lui_phai, 160);
      state=' ';
    }
    //lui - trái
    if(state=='H')
    {
      analogWrite(toi_trai, 0);
      analogWrite(lui_trai, 160);
      analogWrite(toi_phai, 0);
      analogWrite(lui_phai, 255);
      state=' ';
    }
    //nút tam giác
    if(state=='X')  //nút tam giác
    {
      digitalWrite(isd1, HIGH);
      delay(100);
      digitalWrite(isd1, LOW);
      state=' ';
    }
    //nút đèn
    if(state=='V')  
    {
      digitalWrite(isd2, HIGH);
      delay(100);
      digitalWrite(isd2, LOW);
      state=' ';
    }
    //nút đèn đỏ
    if(state=='U')  
    {
      digitalWrite(isd3, HIGH);
      delay(100);
      digitalWrite(isd3, LOW);
      state=' ';
    }
    
    //nút đèn xanh
    if(state=='W')  
    {
      for(int i=0; i < 5; i++)
      {
        led_mat_cuoi_2();
      }
      led_mat_cuoi();
      state=' ';
    }
    
  }
}
void loop()
{
  truyen_nhiet_dien_thoai();
  dieu_khien();
  
  if(digitalRead(cb_bom) == LOW)
  {
    digitalWrite(led_bom,   LOW);
    digitalWrite(bom_nuoc,  LOW);
    delay(200);
    digitalWrite(bom_nuoc,  HIGH);
    digitalWrite(led_bom,   HIGH);
    delay(200);
    while(digitalRead(cb_bom) == LOW);
  }
  
  if(digitalRead(cb_nhiet) == LOW)
  {
    do_nhiet_do();
    digitalWrite(loa_bao,   LOW);
    delay(500);
    digitalWrite(loa_bao,   HIGH);
    hien_thi_2();
    while(digitalRead(cb_nhiet) == LOW);
    delay(3000);
    hien_thi_1();
  }
}
