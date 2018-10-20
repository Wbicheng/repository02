#include "common.h"
#include "include.h"
#include "duoji.h"


float Kp=40;
float Ki=0;
float Kd=90;
float Kp_w=0;
float Kd_w=0;
float Kp_z=0;
float Kd_z=180;
uint8 Center;          //场中心    
uint32 duoji_PWM;      //舵机PWM
int errors;           //静态偏差
int perrors=0;        //上一场偏差
uint8 standardrow=38; //基准行  差不多为2个车身位
uint16 mid_line=0;

void duoji()
{ 
  mid_line=0;
  for(i=standardrow-10;i<standardrow+10;i++)
  {
      mid_line+=visvalMid[i];
  
  }
  mid_line/=20;
/*  switch (deepblue)//基准行
  {
  case 1: mid_line=visvalMid[20];break;
  case 2: mid_line=visvalMid[15];break;
  case 3: mid_line=visvalMid[15];break;
  case 4: mid_line=visvalMid[15];break;
  case 5: mid_line=visvalMid[15];break;
  case 6: mid_line=visvalMid[15];break;
  case 7: mid_line=visvalMid[15];break;
  case 8: mid_line=visvalMid[15];break;
  case 9: mid_line=visvalMid[15];break;
  case 10: mid_line=visvalMid[15];break;
  case 11: mid_line=visvalMid[15];break;
  case 12: mid_line=visvalMid[15];break;
  case 13: mid_line=visvalMid[15];break;
  
  }
 */
 // mid_line=visvalMid[15];


  /************************弯道**********************/
  if(zuowanflag || youwanflag)
  {
     switch(deepblue)
    {
      case 1: Kp=40;Kd=90;break;
      case 2: Kp=35;Kd=90;break;
      case 3: Kp=35;Kd=90;break;
      case 4: Kp=35;Kd=90;break;
      case 5: Kp=35;Kd=90;break;
      case 6: Kp=35;Kd=90;break;
      case 7: Kp=35;Kd=90;break;
      case 8: Kp=35;Kd=90;break;
      case 9: Kp=35;Kd=90;break;
      case 10: Kp=35;Kd=90;break;
      case 11: Kp=35;Kd=90;break;
      case 12: Kp=35;Kd=90;break;
      case 13: Kp=35;Kd=90;break;
      
    
    
    }
    Center=mid_line;
  }
    /************************直道**********************/
  else if(zhidaoflag)
  {
      Kp=20;Kd=50;
      Center=mid_line;
  }
  /************************正常**********************/
  else
  {
    switch(deepblue)
    {
      case 1: Kp=40;Kd=90;break;
      case 2: Kp=35;Kd=90;break;
      case 3: Kp=35;Kd=90;break;
      case 4: Kp=35;Kd=90;break;
      case 5: Kp=35;Kd=90;break;
      case 6: Kp=35;Kd=90;break;
      case 7: Kp=35;Kd=90;break;
      case 8: Kp=35;Kd=90;break;
      case 9: Kp=35;Kd=90;break;
      case 10: Kp=35;Kd=90;break;
      case 11: Kp=35;Kd=90;break;
      case 12: Kp=35;Kd=90;break;
      case 13: Kp=35;Kd=90;break;
    
    
    }
    Center=mid_line;
  }
  Kp=Kp_change;///蓝牙调Kp
  Kd=Kd_change;///蓝牙调Kd
  errors=Center-initcenter;
  duoji_PWM=duojiMid+Kp*errors+Kd*(errors-perrors);    //计算打角
  if(duoji_PWM>rightLimit)
    duoji_PWM=rightLimit;
  if(duoji_PWM<leftLimit)
    duoji_PWM=leftLimit;                      //保护舵机
  ftm_pwm_duty(FTM3,FTM_CH5,duoji_PWM);            
  perrors=errors;
}




