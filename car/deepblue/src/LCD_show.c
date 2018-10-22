#include "common.h"
#include "include.h"
#include "LCD_show.h"



void LCD_show()
{
  /**************************KP KD******************/
  Site_t sitelcd={0,0};//字为16*16大小  行宽为80*80 
  if(zuowanflag)
  LCD_Str_ENCH (sitelcd,"这是一个左弯",FCOLOUR,BCOLOUR);
  else if(youwanflag)
  LCD_Str_ENCH (sitelcd,"这是一个右弯",FCOLOUR,BCOLOUR);
  /*else if(stop_flag)
  LCD_Str_ENCH (sitelcd,"这是终点线",FCOLOUR,BCOLOUR);*/
  else if(zhidaoflag)
  LCD_Str_ENCH (sitelcd,"这是一个直道",FCOLOUR,BCOLOUR);
  else
    LCD_clear(RED);
   LCD_Str_ENCH (sitelcd,"Kp：",FCOLOUR,BCOLOUR);
  sitelcd.y=16;
/*  if(jiwanflag)
  LCD_Str_ENCH (sitelcd,"急",FCOLOUR,BCOLOUR);
  else
  LCD_Str_ENCH (sitelcd,"不急",FCOLOUR,BCOLOUR);  
  LCD_num(sitelcd,wuxiaohang,FCOLOUR,BCOLOUR);
 */
  LCD_num(sitelcd,Kp,FCOLOUR,BCOLOUR);
  sitelcd.y=32;
//  LCD_Str_ENCH (sitelcd,"中线值：",FCOLOUR,BCOLOUR); //下行显示中线值          
  LCD_Str_ENCH (sitelcd,"Kp：",FCOLOUR,BCOLOUR);
  
  sitelcd.y=48;
/*
 */
//  LCD_num(sitelcd,Center,FCOLOUR,BCOLOUR); //中线值显示
  LCD_num(sitelcd,Kd,FCOLOUR,BCOLOUR);
  key_init (KEY_MAX);//初始化键盘
  /********************蜂鸣器**************************/

  if(quickstop_flag==1 || wdflag || endflag)
   gpio_set (PTD0, 0);
  else
    gpio_set (PTD0, 1);

  /**************************图像*******************/
  //真实显示
  size.H = CAMERA_H;
  size.W = CAMERA_W;

  //全屏显示
  //size.H = LCD_H;
  //size.W = LCD_W;
    
  //黑白摄像头
  //LCD_Img_Binary_Z(site, size, imgbuff, imgsize);
  //灰度摄像头

  site.y=60;
  imgdata=&img[0][0];
  LCD_Img_gray_Z(site, size, imgdata , imgsize);
  /*************************电机速度*****************/
  sitelcd.x=60; 
  sitelcd.y=0;
  
  LCD_Str_ENCH (sitelcd,"电机速度：",FCOLOUR,BCOLOUR);
  
  if(quickstop_flag==1)
    LCD_Str_ENCH (sitelcd,"前方急停",FCOLOUR,BCOLOUR);
  else if(wdflag)
    LCD_Str_ENCH (sitelcd,"前方弯道",FCOLOUR,BCOLOUR);
  else if(endflag)
    LCD_Str_ENCH (sitelcd,"前方终点",FCOLOUR,BCOLOUR);
  sitelcd.y=16;
  LCD_num(sitelcd,settingspeed,FCOLOUR,BCOLOUR);
 
  sitelcd.y=32;
  LCD_Str_ENCH (sitelcd,"模式：",FCOLOUR,BCOLOUR);
  
  sitelcd.y=48;
  LCD_num(sitelcd,deepblue,FCOLOUR,BCOLOUR);

}

