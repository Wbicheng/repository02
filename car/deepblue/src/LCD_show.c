#include "common.h"
#include "include.h"
#include "LCD_show.h"

void LCD_show()
{
  /**************************KP KD******************/
  Site_t sitelcd={0,0};//��Ϊ16*16��С  �п�Ϊ80*80 
  if(zuowanflag)
  LCD_Str_ENCH (sitelcd,"����һ������",FCOLOUR,BCOLOUR);

  /*else if(stop_flag)
  LCD_Str_ENCH (sitelcd,"�����յ���",FCOLOUR,BCOLOUR);*/
  else if(zhidaoflag)
  LCD_Str_ENCH (sitelcd,"����һ��ֱ��",FCOLOUR,BCOLOUR);
  else
    LCD_clear(RED); 
  sitelcd.y=16;
  if(jiwanflag)
  LCD_Str_ENCH (sitelcd,"��",FCOLOUR,BCOLOUR);
  else
  LCD_Str_ENCH (sitelcd,"����",FCOLOUR,BCOLOUR);  
  LCD_num(sitelcd,wuxiaohang,FCOLOUR,BCOLOUR);
  sitelcd.y=32;
/*
*/
 
  sitelcd.y=48;
/*
 */
  LCD_num(sitelcd,Center,FCOLOUR,BCOLOUR);
  key_init (KEY_MAX);//��ʼ������
  /********************������**************************/
/*
  if(        
     )
 
   gpio_set (PTD0, 0);
  else
    gpio_set (PTD0, 1);
 */
  /**************************ͼ��*******************/
  //��ʵ��ʾ
  size.H = CAMERA_H;
  size.W = CAMERA_W;

  //ȫ����ʾ
  //size.H = LCD_H;
  //size.W = LCD_W;
    
  //�ڰ�����ͷ
  //LCD_Img_Binary_Z(site, size, imgbuff, imgsize);
  //�Ҷ�����ͷ

  site.y=60;
  imgdata=&img[0][0];
  LCD_Img_gray_Z(site, size, imgdata , imgsize);
  /*************************����ٶ�*****************/
  sitelcd.x=60; 
  sitelcd.y=16;
  LCD_Str_ENCH (sitelcd,"����ٶȣ�",FCOLOUR,BCOLOUR);
 LCD_Str_ENCH (sitelcd,"ģʽ��",FCOLOUR,BCOLOUR);
 
  sitelcd.x=60;
  sitelcd.y=32;
  LCD_num(sitelcd,currentspeed,FCOLOUR,BCOLOUR);
  
  sitelcd.x=60;
  sitelcd.y=48;
  LCD_num(sitelcd,deepblue,FCOLOUR,BCOLOUR);

}
