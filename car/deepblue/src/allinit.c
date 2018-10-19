#include "common.h"
#include "include.h"
#include "allinit.h"


struct WSNSTATE  
{
unsigned diskok:1; 
unsigned fileok:1; 
unsigned record:1; 
unsigned position:1; 
};
volatile struct WSNSTATE state; 
FATFS fs;            // Work area (file system object) for logical drive
FRESULT res;         // FatFs function common result code
UINT br,bw;         // File Write count
FIL testdata;  
FILINFO* sfil;
FRESULT rc;

/************ͼ��****************/
uint8 imgbuff[CAMERA_SIZE];                             //����洢����ͼ�������
uint8 img[CAMERA_H][CAMERA_W];
int DMA_Over_Flag=0;
uint8 *imgdata;

/*************LCD****************/
Site_t site     = {0, 0};                           //��ʾͼ�����Ͻ�λ��
Size_t imgsize  = {CAMERA_W, CAMERA_H};             //ͼ���С
Size_t size;
   
//��������
void PORTA_IRQHandler();
void DMA0_IRQHandler();
void uart5_test_handler();
void stop_now();
void bluetooth_control();
/*************���뿪��*************/
uint8 BM1=0; //D4
uint8 BM2=0; //D3
uint8 BM3=0; //D2
uint8 BM4=0; //D1
uint8 deepblue=0; //ģʽ
uint8 fznum=0;

/**************����****************/
char bluetooth;
int Kp_change=20;//�ɱ�Kp
int Kd_change=50;//�ɱ�Kd

//������ͣ
void stop_now()
{
    char ch=0;
    DisableInterrupts;
    ftm_pwm_duty(FTM0, FTM_CH2, 0);
    ftm_pwm_duty(FTM0, FTM_CH3, 0);
    while(1)
    {
        uart_getchar (UART5,&ch); 
        if(ch==0x05)
          break;
        if(ch==0x06)
        {
            bluetooth_control();
            break;//һ���˳�ң��ģʽ��һ�лָ�
        } 
    }
    EnableInterrupts;
}
//����ң��ģʽ
void bluetooth_control()
{
    char act=0;
    int speed=0;
    int turning=duojiMid;
    uint8 fz_flag=0;
    uint8 get_over=0;
    DisableInterrupts;
    led (LED1,LED_ON); 
    led (LED2,LED_ON); 
    led (LED0,LED_ON); 
    led (LED3,LED_ON);
    ftm_pwm_duty(FTM0, FTM_CH2, 0);
    ftm_pwm_duty(FTM0, FTM_CH3, 0);
    
    while(1)
    {
        uart_getchar (UART5,&act);
        switch(act)
        {
            case 0x06: get_over=1;break;//�˳�ң��ģʽ
            case 0x07: speed+=500;break;//����
            case 0x08: speed-=500;break;//����
            case 0x09: turning-=200;break;//��ת
            case 0x0a: turning+=200;break;//��ת
            case 0x0b: speed=0;turning=duojiMid;break;//ֹͣ
            case 0x0c: if(fz_flag) fz_flag=0; else fz_flag=1;break;
        }  
        act=0;//cat���㣬�ȴ���һ�ν���
        if(speed>=8000) speed=8000;
        if(speed<=0) speed=0;
        if(turning<=leftLimit)  turning=leftLimit;
        else if(turning>=rightLimit) turning=rightLimit;
        if(!fz_flag)
        {
            ftm_pwm_duty(FTM0, FTM_CH2, speed);
            ftm_pwm_duty(FTM0, FTM_CH3, 0);
        }
        else
        {
            ftm_pwm_duty(FTM0, FTM_CH2, 0);
            ftm_pwm_duty(FTM0, FTM_CH3, speed);
        
        }
        ftm_pwm_duty(FTM3,FTM_CH5,turning);
        if(turning<duojiMid)
        {
             led (LED0,LED_ON); 
             led (LED3,LED_ON); 
             led (LED1,LED_OFF); 
             led (LED2,LED_OFF); 
        } 
        else if(turning>duojiMid)
        {
             led (LED1,LED_ON); 
             led (LED2,LED_ON); 
             led (LED0,LED_OFF); 
             led (LED3,LED_OFF);       
        
        }
        if(get_over==1)
          break;
    }
    if(get_over==1)
    {
        led (LED1,LED_OFF); 
        led (LED2,LED_OFF); 
        led (LED0,LED_OFF); 
        led (LED3,LED_OFF); 
        EnableInterrupts;
    }
}
//SD����ʼ��
void init_disk_fatfs(void)   //state.diskok==1;
{
	if(state.diskok==0)  
	{
		if(disk_initialize(0))
		{
			state.diskok=0;
		}
		else
		{	
			res = f_mount(0,&fs);      //for logical drive 0
//			SCI0_putchar(res);
			state.diskok=1;
		}
	}
}

void allinit()
{
  
    DisableInterrupts;
  /*********************LCD************************/
    ASSERT(enter_init());           //����Ƿ���¼FWD
   /********************���뿪��*************************/
      //���뿪�س�ʼ��
    gpio_init (PTD4,GPI,0);  //1
    gpio_init (PTD3,GPI,0);  //2
    gpio_init (PTD2,GPI,0); //3
    gpio_init (PTD1,GPI,0); //4
      
    //��ȡ���뿪��״̬
    BM1=gpio_get(PTD4);
    BM2=gpio_get(PTD3);
    BM3=gpio_get(PTD2);
    BM4=gpio_get(PTD1);
    
    //���뿪�ض�Ӧģʽ   
    if(!BM1 && !BM2 && !BM3 && BM4  )      //ģʽ1  ����160 ֱ��200
    { 
       deepblue=1; 
    }
    if(!BM1 && !BM2 && BM3 && !BM4  )   //ģʽ2  ���Ե�λ ����10s����ֹͣ 
    {
       deepblue=2;
    }
    if(!BM1 && !BM2 && BM3 && BM4  )    //ģʽ3 ����165 ֱ��220
    {
       deepblue=3;
    }
     if(!BM1 && BM2 && !BM3 && !BM4  )  //ģʽ4 ����165 ֱ��250
    {
       deepblue=4;
    }
     if(!BM1 && BM2 && !BM3 && BM4  )      //ģʽ5 ����170 ֱ��200
    {
       deepblue=5;
    }
   if(!BM1 && BM2 && BM3 && !BM4  )   //ģʽ6 ����170 ֱ��220
    {
       deepblue=6;
    }
    if(!BM1 && BM2 && BM3 && BM4  )    //ģʽ7 ����170 ֱ��250
    {
       deepblue=7;
    }
     if(BM1 && !BM2 && !BM3 && !BM4  )  //ģʽ8 ����175 ֱ��200
    {
       deepblue=8; 
    }
        if(BM1 && !BM2 && !BM3 && BM4  )  //ģʽ9 ����175 ֱ��220
    {
       deepblue=9;
    }
        if(BM1 && !BM2 && BM3 && !BM4  )  //ģʽ10 ����175 ֱ��250
    {
       deepblue=10;
    }
        if(BM1 && !BM2 && BM3 && BM4  )  //ģʽ11 ����180 ֱ��200
    {
       deepblue=11; 
    }
        if(BM1 && BM2 && !BM3 && !BM4  )  //ģʽ12 ����180 ֱ��220
    {
       deepblue=12;
    }
        if(BM1 && BM2 && !BM3 && BM4  )  //ģʽ13 ����180 ֱ��250
    {
       deepblue=13;
    }

    LCD_init();
   // LCD_Str_ENCH            (site,"ӥ�����ڳ�ʼ��",FCOLOUR,BCOLOUR);
    led_init (LED0);
    led (LED0,LED_OFF);
    led_init (LED1);
    led (LED1,LED_OFF);
    led_init (LED2);
    led (LED2,LED_OFF);
    led_init (LED3);
    led (LED3,LED_OFF);
    camera_init(imgbuff);
    //LCD_Str_ENCH            (site,"ӥ�۳�ʼ���ɹ�,׼���ɼ�",FCOLOUR,BCOLOUR);
    site.y = 110;
    LCD_FSTR_CH(site,vcan_str,FCOLOUR,BCOLOUR);
    site.y = 0;
    /*******************��ת����***********************/
 //   fznum=50;
   switch(deepblue)
    {
    case 1:fznum=50;
    case 2:fznum=60;
    case 3:fznum=60;
    case 4:fznum=60;
    case 5:fznum=60;
    case 6:fznum=60;
    case 7:fznum=60;
    case 8:fznum=60;
    case 9:fznum=60;
    case 10:fznum=60;
    case 11:fznum=60;
    case 12:fznum=60;
    case 13:fznum=60;
    
    
    } 
   
    /*****************���************************/
    ftm_pwm_init(FTM3,FTM_CH5,300,duojiMid);
    /*****************���************************/
    ftm_pwm_init(FTM0,FTM_CH2,10000,dianjispeed);
    ftm_pwm_init(FTM0,FTM_CH3,10000,0);
    /*****************����ͷ**********************/
        //�����жϷ�����
    set_vector_handler(PORTA_VECTORn , PORTA_IRQHandler);   //���� PORTA ���жϷ�����Ϊ PORTA_IRQHandler
    set_vector_handler(DMA0_VECTORn , DMA0_IRQHandler);     //���� DMA0 ���жϷ�����Ϊ PORTA_IRQHandler
    /*****************������**********************/
    Encoder(right_Encoder,10);
    /******************������***********************/
     gpio_init (PTD0,GPO,1);
     /******************����***********************/
     uart_init (UART5, 9600); //HC-31��ʼ�趨Ϊ9600
     set_vector_handler(UART5_RX_TX_VECTORn , uart5_test_handler);//���ý��շ����ж�
     uart_rx_irq_en(UART5);//ʹ�ܽ����ж� ����
    /******************sd��***********************/
    //SPI_Configuration();
    Site_t sitelcd={0,0};
    LCD_Str_ENCH(sitelcd,"UartInit is OK!",FCOLOUR,BCOLOUR);
    uart_putchar(UART0,0xff);
    uart_putstr(UART0,"UartInit is OK!");
  /* init_disk_fatfs();
    if(state.diskok)
    {
      sitelcd.y=10;
      LCD_Str_ENCH(sitelcd,"init_disk is OK!",FCOLOUR,BCOLOUR); 
      uart_putstr(UART0,"init_disk is OK!");
    } 

     rc =f_open(&testdata,"0:/data2.txt",FA_OPEN_ALWAYS|FA_WRITE | FA_READ);
      if(FR_OK == rc)
      {
        sitelcd.y=20;
        LCD_Str_ENCH(sitelcd,"f_open is ok",FCOLOUR,BCOLOUR);
        uart_putstr(UART0,"f_open is OK!");
      }
      else 
      {
        sitelcd.y=30;
        LCD_Str_ENCH(sitelcd,"no SDsave!",FCOLOUR,BCOLOUR);
        uart_putstr(UART0,"no SDsave!");
      }
       LCD_num(sitelcd,rc,FCOLOUR,BCOLOUR);
      while(1);
    */
    EnableInterrupts;
}

/*!
 *  @brief      PORTA�жϷ�����
 *  @since      v6.0
 */
void PORTA_IRQHandler()
{
    uint8  n;    //���ź�
    uint32 flag;

    while(!PORTA_ISFR);
    flag = PORTA_ISFR;
    PORTA_ISFR  = ~0;                                   //���жϱ�־λ

    n = 29;                                             //���ж�
    if(flag & (1 << n))                                 //PTA29�����ж�
    {
        camera_vsync();
    }
#if ( CAMERA_USE_HREF == 1 )                            //ʹ�����ж�
    n = 28;
    if(flag & (1 << n))                                 //PTA28�����ж�
    {
        camera_href();
    }
#endif


}

/*!
 *  @brief      DMA0�жϷ�����
 *  @since      v6.0
 */
void DMA0_IRQHandler()
{
    camera_dma();
}

//uart5 �жϷ�����
void uart5_test_handler()
{ 
    UARTn_e uratn = UART5;
    if(UART_S1_REG(UARTN[uratn]) & UART_S1_RDRF_MASK)   //�������ݼĴ�����  �������ݼĴ��������������жϱ�־λ
    {
         bluetooth =  UART_D_REG(UARTN[uratn]);  //bluetoothȡֵ��0x01��0x02��
   /*      if(bluetooth!=0x00)
        {
            led_turn (LED0);  //���ڽ���ָʾ��
           led_turn (LED1); 
         
         } 
    */
        switch(bluetooth)
        {
            case 0x01:Kp_change++; led_turn (LED0);led_turn (LED1);break;
            case 0x02:Kp_change--; led_turn (LED0);led_turn (LED1);break;
            case 0x03:Kd_change++; led_turn (LED2);led_turn (LED3);break; 
            case 0x04:Kd_change--; led_turn (LED2);led_turn (LED3);break;
            case 0x05:stop_now();break;
            case 0x06:bluetooth_control();break;
        }
    }

}



