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

/*************拔码开关*************/
uint8 BM1=0; //D4
uint8 BM2=0; //D3
uint8 BM3=0; //D2
uint8 BM4=0; //D1
uint8 deepblue=0; //模式
uint8 fznum=0;

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
    if(!BM1 && !BM2 && BM3 && !BM4  )   //模式2  正常165 直道200
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




