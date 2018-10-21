#include "common.h"
#include "include.h"
uint32 timevar=0;//��������ʱ��΢��;
void PORTC_IRQHandler(void); 
void  main(void)
{ 
   // Site_t sitelcd={0,0};
    uart_init(UART0,115200);
    allinit();
    LCD_clear(RED);
    set_vector_handler(PORTC_VECTORn ,PORTC_IRQHandler);    //����PORTC���жϷ�����Ϊ PORTC_IRQHandler
    enable_irq (PORTC_IRQn); //ʹ��PORTC�ж�
    
    while(1)
    {   
     // pit_time_start  (PIT2);//�����������ʱ��
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
        camera_get_img(&DMA_Over_Flag);            //����ͷ��ȡͼ��
        if(DMA_Over_Flag==1)
        {
        DMA_Over_Flag=0;
        img_extract(img, imgbuff, CAMERA_SIZE);    //��ѹΪ�Ҷ�ͼ������ͼ����
        
        handle_img();         //ͼ����
        LCD_show();           //LCD��ʾ 
        duoji();              //�������
     //   dianji();             //�������
     /*   timevar = pit_time_get_us(PIT2);//�����������ʱ��
        sitelcd.y=32;
        LCD_Str_ENCH (sitelcd,"timevar��",FCOLOUR,BCOLOUR);
        sitelcd.y=48;
        LCD_num(sitelcd,timevar,FCOLOUR,BCOLOUR);
       */
        
        
#if 0  //���ڷ���ͼ��  1ʱ�򿪷���
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
        /******************** ɽ��๦�ܵ������� ���ڰ�ģʽ�� ����ͼ����λ�� ***********************/
        //vcan_sendimg(imgbuff, sizeof(imgbuff));
        /******************** ɽ��๦�ܵ������� ���Ҷ�ģʽ�� ����ͼ����λ�� ***********************/
        //vcan_sendimg(img, sizeof(img));
        
        }

    }
}


void PORTC_IRQHandler(void)
{
    uint8  n = 0;    //���ź�
    n = 8;          
    if(PORTC_ISFR & (1 << n))           //PTC8 �����ж�   LCD��
    {
        PORTC_ISFR  = (1 << n);        //д1���жϱ�־λ
        Kd_z+=50;
    }
    
    n = 16;         
    if(PORTC_ISFR & (1 << n))           //PTC16 �����ж�   LCD��
    {
        PORTC_ISFR  = (1 << n);        //д1���жϱ�־λ
        Kd_z-=50;
    }
        
    n = 18;          
    if(PORTC_ISFR & (1 << n))           //PTC18 �����ж�   LCD��
    {
        PORTC_ISFR  = (1 << n);        //д1���жϱ�־λ
        Kd_z+=10;
    }
        
    n = 17;
    if(PORTC_ISFR & (1 << n))           //PTC17 �����ж�   LCD��
    {
        PORTC_ISFR  = (1 << n);        //д1���жϱ�־λ
        Kd_z-=10;
    }
            
    n = 19;
    if(PORTC_ISFR & (1 << n))           //PTC19 �����ж�   LCD��
    {
        PORTC_ISFR  = (1 << n);        //д1���жϱ�־λ
         LCD_clear(RED);
    }
}
