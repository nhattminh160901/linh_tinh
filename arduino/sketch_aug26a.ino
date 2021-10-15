#include <PS2X_lib.h>  

PS2X ps2x; // create PS2 Controller Class

#define isd_lay_com     A0
#define isd_do_nhiet    A1
#define toi_trai         3
#define lui_trai         5
#define toi_phai         6
#define lui_phai         9

int   error = 0; 
byte  type = 0;
byte  vibrate = 0;

void setup()
{
 Serial.begin(9600);
 pinMode(toi_trai,          OUTPUT);
 pinMode(lui_trai,          OUTPUT);
 pinMode(toi_phai,          OUTPUT);
 pinMode(lui_phai,          OUTPUT);
 pinMode(isd_lay_com,       OUTPUT);
 pinMode(isd_do_nhiet,      OUTPUT);
 analogWrite(toi_trai, 0);
 analogWrite(lui_trai, 0);
 analogWrite(toi_phai, 0);
 analogWrite(lui_phai, 0);
 digitalWrite(isd_lay_com,  LOW);
 digitalWrite(isd_do_nhiet, LOW);

  error = ps2x.config_gamepad(13,11,10,12, true, true);  
 
 if(error == 0)
 {
    Serial.println("Found Controller, configured successful");
 }
  else if(error == 1)
   Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips"); 
  else if(error == 2)
   Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
  else if(error == 3)
   Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
  type = ps2x.readType(); 
  switch(type) 
  {
    case 0:
      Serial.println("Unknown Controller type");
      break;
    case 1:
      Serial.println("DualShock Controller Found");
      break;
    case 2:
      Serial.println("GuitarHero Controller Found");
      break;
  }
}

void toi()
{
  Serial.println("TOI");
  analogWrite(toi_trai, 180);
  analogWrite(lui_trai, 0);
  analogWrite(toi_phai, 255);
  analogWrite(lui_phai, 0);
}

void lui()
{
  Serial.println("LUI");
  analogWrite(toi_trai, 0);
  analogWrite(lui_trai, 180);
  analogWrite(toi_phai, 0);
  analogWrite(lui_phai, 255);
}

void trai()
{
  Serial.println("TRÁI");
  analogWrite(toi_trai, 0);
  analogWrite(lui_trai, 0);
  analogWrite(toi_phai, 255);
  analogWrite(lui_phai, 0);
}

void phai()
{
  Serial.println("PHẢI");
  analogWrite(toi_trai, 255);
  analogWrite(lui_trai, 0);
  analogWrite(toi_phai, 0);
  analogWrite(lui_phai, 0);
}

void toiTrai()
{
  Serial.println("TỚI-TRÁI");
  analogWrite(toi_trai, 105);
  analogWrite(lui_trai, 0);
  analogWrite(toi_phai, 255);
  analogWrite(lui_phai, 0);
}

void toiPhai()
{
  Serial.println("TỚI-PHẢI");
  analogWrite(toi_trai, 255);
  analogWrite(lui_trai, 0);
  analogWrite(toi_phai, 255);
  analogWrite(lui_phai, 0);
}

void luiTrai()
{
  Serial.println("LUI-TRÁI");
  analogWrite(toi_trai, 0);
  analogWrite(lui_trai, 105);
  analogWrite(toi_phai, 0);
  analogWrite(lui_phai, 255);
}

void luiPhai()
{
  Serial.println("LUI-PHẢI");
  analogWrite(toi_trai, 0);
  analogWrite(lui_trai, 255);
  analogWrite(toi_phai, 0);
  analogWrite(lui_phai, 255);
}

void phaiTam()
{
  Serial.println("PHẢI CHÍNH TÂM");
  analogWrite(toi_trai, 150);
  analogWrite(lui_trai, 0);
  analogWrite(toi_phai, 0);
  analogWrite(lui_phai, 255);
}

void traiTam()
{
  Serial.println("TRÁI CHÍNH TÂM");
  analogWrite(toi_trai, 0);
  analogWrite(lui_trai, 150);
  analogWrite(toi_phai, 255);
  analogWrite(lui_phai, 0);
}

void dung()
{
  analogWrite(toi_trai, 0);
  analogWrite(lui_trai, 0);
  analogWrite(toi_phai, 0);
  analogWrite(lui_phai, 0);
}

void tatLoa()
{
  digitalWrite(isd_lay_com,  LOW);
  digitalWrite(isd_do_nhiet, LOW);
}
void layCom()
{
  digitalWrite(isd_lay_com,  HIGH);
  delay(1000);
  tatLoa();
}

void doNhiet()
{
  digitalWrite(isd_do_nhiet, HIGH);
  delay(1000);
  tatLoa();
}
void loop()
{
  if(type == 2)
  { 
    ps2x.read_gamepad();          //read controller 
  }
  else 
  { 
    ps2x.read_gamepad(false, vibrate);          
    //**** 2 NÚT START, SELECT ****
    if(ps2x.Button(PSB_START))                   
         Serial.println("Start is being held");
    if(ps2x.Button(PSB_SELECT))
         Serial.println("Select is being held");
         
    //BẤM NÚT R2 (PHẢI DƯỚI) KẾT HỢP NÚT TRÁI PHẢI ĐỂ XOAY)
    if(ps2x.Button(PSB_R2))
    {
      if (ps2x.Button(PSB_PAD_RIGHT))
      {
        phaiTam();
      }
      else if (ps2x.Button(PSB_PAD_LEFT))
      {
        traiTam();
      }
      else
      {
        dung();
      }
    }
    
    else if(ps2x.Button(PSB_PAD_UP))
    {
      if(ps2x.Button(PSB_PAD_RIGHT))
      {
        toiPhai();
      }
      else if(ps2x.Button(PSB_PAD_LEFT))
      {
        toiTrai();
      }
      else if(ps2x.Button(PSB_PAD_UP))
      {
        toi();
      }
      else
      {
        dung();
      }
    }
    
    else if(ps2x.Button(PSB_PAD_DOWN))
    {
      if(ps2x.Button(PSB_PAD_RIGHT))
      {
        luiPhai();
      }
      else if(ps2x.Button(PSB_PAD_LEFT))
      {
        luiTrai();
      }
      else if(ps2x.Button(PSB_PAD_DOWN))
      {
        lui();
      }
      else
      {
        dung();
      }
    }

    else if (ps2x.Button(PSB_PAD_RIGHT))
    {
      if(ps2x.Button(PSB_PAD_UP))
      {
        toiPhai();
      }
      else if(ps2x.Button(PSB_PAD_DOWN))
      {
        luiPhai();
      }
      else if(ps2x.Button(PSB_R2))
      {
        phaiTam();
      }
      else if(ps2x.Button(PSB_PAD_RIGHT))
      {
      phai();
      }
      else
      {
        dung();
      }
    }
    
    else if(ps2x.Button(PSB_PAD_LEFT))
    {
      if(ps2x.Button(PSB_PAD_UP))
      {
        toiTrai();
      }
      else if(ps2x.Button(PSB_PAD_DOWN))
      {
        luiTrai();
      }
      else if(ps2x.Button(PSB_R2))
      {
        traiTam();
      }
      else if(ps2x.Button(PSB_PAD_LEFT))
      {
        trai();
      }
      else
      {
        dung();
      }
    }
    
    //**** 4 NÚT TRÒN, VUÔNG, X, TAM GIÁC ****
    else if(ps2x.Button(PSB_PINK)) 
    {          
       Serial.println("NUT VUONG");     
       layCom();
    }
    else if(ps2x.Button(PSB_GREEN))
    {
      Serial.println("NUT TAM GIAC");  
      doNhiet();
    }
    else if(ps2x.ButtonReleased(PSB_START))
    {
      Serial.println("DA KHOI DONG");
    }
    else
    {
      dung();
    }
  }
  delay(50);
}
// CODE BY NHAT MINH & MINH TRI
