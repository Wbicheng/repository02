#include "common.h"
#include "include.h"
uint32 timevar=0;//程序运行时间微秒;
void PORTC_IRQHandler(void); 
void  main(void)
{ 
   // Site_t sitelcd={0,0};
    uart_init(UART0,115200);
    allinit();
    LCD_clear(RED);
    set_vector_handler(PORTC_VECTORn ,PORTC_IRQHandler);    //设置PORTC的中断服务函数为 PORTC_IRQHandler
    enable_irq (PORTC_IRQn); //使能PORTC中断
    
    while(1)
    {   
     // pit_time_start  (PIT2);//计算程序运行时间
      /*
         uart_init(UART0,115200);
         uart_putchar(UART0,0xff);
         uart_putchar(UART0,0xff);
         if(Encoder_speed2<0)
         Encoder_speed2=-Encoder_speed2;
         uart_putchar(UART0,Encoder_speed2/256);
         uart_putchar(UART0,Encoder_speed2%256);
         for(i=0;i<6;i++)
           uart_putchar(UART0,0);*/
        camera_get_img(&DMA_Over_Flag);            //摄像头获取图像
        if(DMA_Over_Flag==1)
        {
        DMA_Over_Flag=0;
        img_extract(img, imgbuff, CAMERA_SIZE);    //解压为灰度图像，用于图像处理
        
        handle_img();         //图像处理
        LCD_show();           //LCD显示 
        duoji();              //舵机控制
     //   dianji();             //电机控制
     /*   timevar = pit_time_get_us(PIT2);//计算程序运行时间
        sitelcd.y=32;
        LCD_Str_ENCH (sitelcd,"timevar：",FCOLOUR,BCOLOUR);
        sitelcd.y=48;
        LCD_num(sitelcd,timevar,FCOLOUR,BCOLOUR);
       */
        
        
#if 0  //串口发送图像  1时打开发送
          int i,j;
          uart_init(UART4,115200);
          uart_putchar(UART4,0xff);
          LCD_num(site,Center, BLUE,RED);
         /** for(i=0;i<CAMERA_H;i++)
          {
            for(j=0;j<CAMERA_W;j++)
            {    
                 uart_putchar(UART4,img[i][j]);
            }
          }**/

#endif
        /******************** 山外多功能调试助手 【黑白模式】 发送图像到上位机 ***********************/
        //vcan_sendimg(imgbuff, sizeof(imgbuff));
        /******************** 山外多功能调试助手 【灰度模式】 发送图像到上位机 ***********************/
        //vcan_sendimg(img, sizeof(img));
        
        }

    }
}


void PORTC_IRQHandler(void)
{
    uint8  n = 0;    //引脚号
    n = 8;          
    if(PORTC_ISFR & (1 << n))           //PTC8 触发中断   LCD上
    {
        PORTC_ISFR  = (1 << n);        //写1清中断标志位
        Kd_z+=50;
    }
    
    n = 16;         
    if(PORTC_ISFR & (1 << n))           //PTC16 触发中断   LCD下
    {
        PORTC_ISFR  = (1 << n);        //写1清中断标志位
        Kd_z-=50;
    }
        
    n = 18;          
    if(PORTC_ISFR & (1 << n))           //PTC18 触发中断   LCD左
    {
        PORTC_ISFR  = (1 << n);        //写1清中断标志位
        Kd_z+=10;
    }
        
    n = 17;
    if(PORTC_ISFR & (1 << n))           //PTC17 触发中断   LCD右
    {
        PORTC_ISFR  = (1 << n);        //写1清中断标志位
        Kd_z-=10;
    }
            
    n = 19;
    if(PORTC_ISFR & (1 << n))           //PTC19 触发中断   LCD中
    {
        PORTC_ISFR  = (1 << n);        //写1清中断标志位
         LCD_clear(RED);
    }
}
