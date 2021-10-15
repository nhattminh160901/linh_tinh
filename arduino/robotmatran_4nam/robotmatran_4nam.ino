#define toi_phai     6
#define lui_phai     5 

#define toi_trai    10
#define lui_trai     9

int sensor[6]={0, 0, 0, 0, 0, 0};
int error,previous_error;
float P,I,D,kp=10,ki=0.0001,kd=70;
int PID_value,PID_phai,PID_trai;
int gia_tri_dau_trai = 100;
int gia_tri_dau_phai = 100;
int dem = 0;
void setup()
{
 pinMode(toi_trai,OUTPUT); //PWM Pin 1
 pinMode(lui_trai,OUTPUT); //PWM Pin 2
 pinMode(toi_phai,OUTPUT); //Left Motor Pin 1
 pinMode(lui_phai,OUTPUT); //Left Motor Pin 2

 pinMode(A0, INPUT);
 pinMode(A1, INPUT);
 pinMode(A2, INPUT);
 pinMode(A3, INPUT);
 pinMode(A4, INPUT);
 pinMode(A5, INPUT);
 Serial.begin(9600); //Enable Serial Communications
 analogWrite(toi_trai,0);   
 analogWrite(lui_trai,0);   
 analogWrite(toi_phai,0);
 analogWrite(lui_phai,0);
 delay(5000);
}
void dung_xe()
{
  analogWrite(toi_trai,0);   
  analogWrite(lui_trai,0);   
  analogWrite(toi_phai,0);
  analogWrite(lui_phai,0);
}
void xoay_phai()
{
  int ttcb;
  analogWrite(toi_trai,70);   
  analogWrite(lui_trai,0);   
  analogWrite(toi_phai,40);
  analogWrite(lui_phai,0);
  do
  {
    ttcb =digitalRead(A4);  //kiểm tra cảm biến phải
  }while(ttcb == 0);
  analogWrite(toi_trai,0);   
  analogWrite(lui_trai,0);   
  analogWrite(toi_phai,0);
  analogWrite(lui_phai,0);
}
void xoay_trai()
{
  int ttcb;
  analogWrite(toi_trai,40);   
  analogWrite(lui_trai,0);   
  analogWrite(toi_phai,70);
  analogWrite(lui_phai,0);
  do
  {
    ttcb =digitalRead(A1);  //kiểm tra cảm biến phải
  }while(ttcb == 0);
  analogWrite(toi_trai,0);   
  analogWrite(lui_trai,0);   
  analogWrite(toi_phai,0);
  analogWrite(lui_phai,0);
}
void loop()
{
    do_line();
    PID_bam_xung();
    int ttcbt =digitalRead(A5);  //kiểm tra cảm biến phải
    if(ttcbt == 1)
    {
      dem++;
      analogWrite(toi_trai,100);   
      analogWrite(lui_trai,0);   
      analogWrite(toi_phai,100);
      analogWrite(lui_phai,0);
      delay(150);
      if(dem == 2)
      {
        dung_xe();
        delay(150);
        xoay_phai();
        delay(150);
      }
      if(dem == 3)
      {
        dung_xe();
        delay(150);
        xoay_phai();
        delay(150);
        dem = 0;
      }
    }
}
void do_line()
{
  //kết nối sensor: trai 0-1-2-3-4 phai
  
  sensor[0]=digitalRead(A0);
  sensor[1]=digitalRead(A1);
  sensor[2]=digitalRead(A2);
  sensor[3]=digitalRead(A3);
  sensor[4]=digitalRead(A4);
  sensor[5]=digitalRead(A5);
  
  //lệch phải
    if     ((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==1)) error= 6;
    else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==1)&&(sensor[5]==1)) error= 5;
    else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==1)&&(sensor[5]==0)) error= 4;
    else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==1)&&(sensor[4]==1)&&(sensor[5]==0)) error= 3;
    else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==1)&&(sensor[4]==0)&&(sensor[5]==0)) error= 2;
    else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==1)&&(sensor[4]==1)&&(sensor[5]==1)) error= 1;
    //ở giữa
    else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==1)&&(sensor[3]==1)&&(sensor[4]==0)&&(sensor[5]==0)) error=0;
    //lệch trái
    else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==1)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==0)) error= -1;
    else if((sensor[0]==0)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==0)) error= -2;
    else if((sensor[0]==0)&&(sensor[1]==1)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==0)) error= -3;
    else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==0)) error= -4;
    else if((sensor[0]==1)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==0)) error= -5;
    else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==0)) error= -6;
    //trường hợp khác
    else  error = 0;
}
void PID_bam_xung()
{
  P = error;
  I = I + error;
  D = error-previous_error;
  PID_value = (kp*P) + (ki*I) +(kd*D);//kp kd ki gia tri can dua ban dau <=255
  previous_error=error;

  PID_phai =  gia_tri_dau_phai - PID_value;
  PID_trai =  gia_tri_dau_trai + PID_value;
  PID_phai = constrain(gia_tri_dau_phai-PID_value,0,255);
  PID_trai = constrain(gia_tri_dau_trai+PID_value,0,255);
  analogWrite(toi_trai, PID_trai);
  analogWrite(toi_phai, PID_phai);
}
