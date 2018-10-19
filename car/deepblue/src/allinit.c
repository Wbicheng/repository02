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

/************图像****************/
uint8 imgbuff[CAMERA_SIZE];                             //定义存储接收图像的数组
uint8 img[CAMERA_H][CAMERA_W];
int DMA_Over_Flag=0;
uint8 *imgdata;

/*************LCD****************/
Site_t site     = {0, 0};                           //显示图像左上角位置
Size_t imgsize  = {CAMERA_W, CAMERA_H};             //图像大小
Size_t size;
   
//函数声明
void PORTA_IRQHandler();
void DMA0_IRQHandler();
void uart5_test_handler();
void stop_now();
void bluetooth_control();
/*************拔码开关*************/
uint8 BM1=0; //D4
uint8 BM2=0; //D3
uint8 BM3=0; //D2
uint8 BM4=0; //D1
uint8 deepblue=0; //模式
uint8 fznum=0;

/**************蓝牙****************/
char bluetooth;
int Kp_change=20;//可变Kp
int Kd_change=50;//可变Kd

//蓝牙控停
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
            break;//一旦退出遥控模式，一切恢复
        } 
    }
    EnableInterrupts;
}
//蓝牙遥控模式
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
            case 0x06: get_over=1;break;//退出遥控模式
            case 0x07: speed+=500;break;//加速
            case 0x08: speed-=500;break;//减速
            case 0x09: turning-=200;break;//左转
            case 0x0a: turning+=200;break;//右转
            case 0x0b: speed=0;turning=duojiMid;break;//停止
            case 0x0c: if(fz_flag) fz_flag=0; else fz_flag=1;break;
        }  
        act=0;//cat清零，等待下一次接收
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
//SD卡初始化
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
    ASSERT(enter_init());           //检查是否烧录FWD
   /********************拨码开关*************************/
      //拨码开关初始化
    gpio_init (PTD4,GPI,0);  //1
    gpio_init (PTD3,GPI,0);  //2
    gpio_init (PTD2,GPI,0); //3
    gpio_init (PTD1,GPI,0); //4
      
    //读取拨码开关状态
    BM1=gpio_get(PTD4);
    BM2=gpio_get(PTD3);
    BM3=gpio_get(PTD2);
    BM4=gpio_get(PTD1);
    
    //拨码开关对应模式   
    if(!BM1 && !BM2 && !BM3 && BM4  )      //模式1  正常160 直道200
    { 
       deepblue=1; 
    }
    if(!BM1 && !BM2 && BM3 && !BM4  )   //模式2  调试档位 运行10s后电机停止 
    {
       deepblue=2;
    }
    if(!BM1 && !BM2 && BM3 && BM4  )    //模式3 正常165 直道220
    {
       deepblue=3;
    }
     if(!BM1 && BM2 && !BM3 && !BM4  )  //模式4 正常165 直道250
    {
       deepblue=4;
    }
     if(!BM1 && BM2 && !BM3 && BM4  )      //模式5 正常170 直道200
    {
       deepblue=5;
    }
   if(!BM1 && BM2 && BM3 && !BM4  )   //模式6 正常170 直道220
    {
       deepblue=6;
    }
    if(!BM1 && BM2 && BM3 && BM4  )    //模式7 正常170 直道250
    {
       deepblue=7;
    }
     if(BM1 && !BM2 && !BM3 && !BM4  )  //模式8 正常175 直道200
    {
       deepblue=8; 
    }
        if(BM1 && !BM2 && !BM3 && BM4  )  //模式9 正常175 直道220
    {
       deepblue=9;
    }
        if(BM1 && !BM2 && BM3 && !BM4  )  //模式10 正常175 直道250
    {
       deepblue=10;
    }
        if(BM1 && !BM2 && BM3 && BM4  )  //模式11 正常180 直道200
    {
       deepblue=11; 
    }
        if(BM1 && BM2 && !BM3 && !BM4  )  //模式12 正常180 直道220
    {
       deepblue=12;
    }
        if(BM1 && BM2 && !BM3 && BM4  )  //模式13 正常180 直道250
    {
       deepblue=13;
    }

    LCD_init();
   // LCD_Str_ENCH            (site,"鹰眼正在初始化",FCOLOUR,BCOLOUR);
    led_init (LED0);
    led (LED0,LED_OFF);
    led_init (LED1);
    led (LED1,LED_OFF);
    led_init (LED2);
    led (LED2,LED_OFF);
    led_init (LED3);
    led (LED3,LED_OFF);
    camera_init(imgbuff);
    //LCD_Str_ENCH            (site,"鹰眼初始化成功,准备采集",FCOLOUR,BCOLOUR);
    site.y = 110;
    LCD_FSTR_CH(site,vcan_str,FCOLOUR,BCOLOUR);
    site.y = 0;
    /*******************反转场数***********************/
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
   
    /*****************舵机************************/
    ftm_pwm_init(FTM3,FTM_CH5,300,duojiMid);
    /*****************电机************************/
    ftm_pwm_init(FTM0,FTM_CH2,10000,dianjispeed);
    ftm_pwm_init(FTM0,FTM_CH3,10000,0);
    /*****************摄像头**********************/
        //配置中断服务函数
    set_vector_handler(PORTA_VECTORn , PORTA_IRQHandler);   //设置 PORTA 的中断服务函数为 PORTA_IRQHandler
    set_vector_handler(DMA0_VECTORn , DMA0_IRQHandler);     //设置 DMA0 的中断服务函数为 PORTA_IRQHandler
    /*****************编码器**********************/
    Encoder(right_Encoder,10);
    /******************蜂鸣器***********************/
     gpio_init (PTD0,GPO,1);
     /******************蓝牙***********************/
     uart_init (UART5, 9600); //HC-31初始设定为9600
     set_vector_handler(UART5_RX_TX_VECTORn , uart5_test_handler);//设置接收发送中断
     uart_rx_irq_en(UART5);//使能接收中断 ！！
    /******************sd卡***********************/
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
 *  @brief      PORTA中断服务函数
 *  @since      v6.0
 */
void PORTA_IRQHandler()
{
    uint8  n;    //引脚号
    uint32 flag;

    while(!PORTA_ISFR);
    flag = PORTA_ISFR;
    PORTA_ISFR  = ~0;                                   //清中断标志位

    n = 29;                                             //场中断
    if(flag & (1 << n))                                 //PTA29触发中断
    {
        camera_vsync();
    }
#if ( CAMERA_USE_HREF == 1 )                            //使用行中断
    n = 28;
    if(flag & (1 << n))                                 //PTA28触发中断
    {
        camera_href();
    }
#endif


}

/*!
 *  @brief      DMA0中断服务函数
 *  @since      v6.0
 */
void DMA0_IRQHandler()
{
    camera_dma();
}

//uart5 中断服务函数
void uart5_test_handler()
{ 
    UARTn_e uratn = UART5;
    if(UART_S1_REG(UARTN[uratn]) & UART_S1_RDRF_MASK)   //接收数据寄存器满  访问数据寄存器后主动清理中断标志位
    {
         bluetooth =  UART_D_REG(UARTN[uratn]);  //bluetooth取值：0x01、0x02、
   /*      if(bluetooth!=0x00)
        {
            led_turn (LED0);  //串口接收指示灯
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



