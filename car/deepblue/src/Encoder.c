
//****************自定义编码器函数*********深蓝色工程师
#include "common.h"
#include "include.h"
#include "Encoder.h"
#include "MK60_FTM.h"
#include "MK60_pit.h"


//强调：一个模块同一时间只能干一个活，而且频率必须是相同的。
//FTM是多功能的定时器，可实现多种功能。
//但同一时间，一个FTM0拿去PWM输出，就不要再用来做正交解码、输入捕捉，或者其他事情。
//而且，FTM0的通道0输出频率为20k，通道1也必须，只能输出20k的pwm。


Encoder_flag Encoder_flagextern;//单双编码器工作判断位，用于PIT中断函数
int Encoder_speed1=0;             //编码器1的脉冲计数值，在main函数中调用即可获得计数值
int Encoder_speed2=0;             //编码器2的脉冲计数值，在main函数中调用即可获得计数值

 int speedError[3];          //电机速度误差
 int currentspeed;              //当前速度
 int32 motorPWM = dianjispeed;    //电机PWM
 float P_moto = 10; 
 float I_moto = 7; 
 float D_moto = 1; 
int debug_time=0;//调试模式


/*!
 *  @brief     编码器工作函数
 *  @param     Encoder_flag  编码器工作状态选择
 *  @param     int           脉冲计数采集时间ms
 *  @since     v1.0
 *  @note      FTM 正交解码 测速（三种工作状态）
 *  @Sample usage     Encoder(double_Encoder,500);   调用编码器工作函数，工作状态为双编码器模式，采集周期为500ms
 */

void Encoder(Encoder_flag Encoder_n,int Acq_time)
{  
    ASSERT(enter_init());   //判断是否加载了FWD固件
    Encoder_flagextern=Encoder_n;
    switch(Encoder_n)
    {
     case 0:
           printf("\nFTM1:\n");
           ftm_quad_init(FTM1);  //FTM1 正交解码初始化，所用的管脚可查 port_cfg.h 的 FTM1_QDPHA_PIN 和 FTM1_QDPHB_PIN
           break;                                               
     case 1: 
           printf("\nFTM2:\n");
           ftm_quad_init(FTM2);   
           break;                //FTM2正交解码初始化，所用的管脚可查 port_cfg.h
     case 2:
           printf("\nDOUBLE_FTM\n");
           ftm_quad_init(FTM1);  
           ftm_quad_init(FTM2); 
           break;                //FTM1，FTM2正交解码初始化，所用的管脚可查 port_cfg.h
    }
         pit_init_ms(PIT0, Acq_time);                            //初始化PIT0，定时时间为： 500ms
         set_vector_handler(PIT0_VECTORn ,PIT0_IRQHandler);      //设置PIT0的中断服务函数为 PIT0_IRQHandler
         enable_irq (PIT0_IRQn);                                 //使能PIT0中断
}

/*!
 *  @brief      PIT0中断服务函数
 *  @since      v1.0
 */
void PIT0_IRQHandler(void)
{
   switch(Encoder_flagextern)
   {
      case 0:
          Encoder_speed1 = ftm_quad_get(FTM1);          //获取FTM 正交解码 的脉冲数(负数表示反方向)
          ftm_quad_clean(FTM1);
          printf("FTM1:%d\n",Encoder_speed1);
          PIT_Flag_Clear(PIT0);       //清中断标志位
          break;
      case 1:
          Encoder_speed2 = ftm_quad_get(FTM2);
          ftm_quad_clean(FTM2);
          printf("FTM2:%d\n",Encoder_speed2);
          PIT_Flag_Clear(PIT0); 
          break;
      case 2:
          Encoder_speed1 = ftm_quad_get(FTM1);
          Encoder_speed2 = ftm_quad_get(FTM2);
          ftm_quad_clean(FTM1);
          ftm_quad_clean(FTM2);
          printf("FTM1:%d\n",Encoder_speed1);
          printf("FTM2:%d\n",Encoder_speed2);
          PIT_Flag_Clear(PIT0); 
          break;
  
   }
  if(deepblue==2 && debug_time!=1000)
  {
      debug_time++;
  
  }
  if(debug_time==1000)
  {
      ftm_pwm_duty(FTM0, FTM_CH2, 0);
      ftm_pwm_duty(FTM0, FTM_CH3, 0);
  }  
  else
  {
     /*****************************电机PID**********************/
   if(Encoder_speed2<0)
     Encoder_speed2 = -Encoder_speed2;
    currentspeed = Encoder_speed2;
    speedError[2] = settingspeed - currentspeed; //当前误差
    motorPWM +=  P_moto * (speedError[2]-speedError[1]) +I_moto * speedError[2] + D_moto * (speedError[2] - 2 * speedError[1] + speedError[0]);
    //设置极限速度
    if(motorPWM >limitspeed)
      motorPWM =limitspeed;
   if(motorPWM<0)
      motorPWM = 0;
/*    if(stop_flag && !zdnum)
    {
        if(fznum) //终点线反转50乘10ms=0.5s
        {
           fznum--;
           ftm_pwm_duty(FTM0, FTM_CH2, 0);
           ftm_pwm_duty(FTM0, FTM_CH3, 8000);
        
        }
        else
        ftm_pwm_duty(FTM0, FTM_CH3, 0);
    }*/
   // else
   // ftm_pwm_duty(FTM0, FTM_CH2, motorPWM);
//    else 
     if(motorPWM>0)
    {
      ftm_pwm_duty(FTM0, FTM_CH2, motorPWM);
      ftm_pwm_duty(FTM0, FTM_CH3, 0);
    }
    else
    {
      ftm_pwm_duty(FTM0, FTM_CH2, 0);
      ftm_pwm_duty(FTM0, FTM_CH3, -motorPWM);
    }
      
   
    speedError[0] = speedError[1];//上上次误差
    speedError[1] = speedError[2];//上次误差
  }
}