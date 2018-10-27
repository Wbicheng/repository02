#ifndef __ENCODER_H__
#define __ENCODER_H__

//定义编码器工作状态
typedef enum
{
    left_Encoder,                //左编码器工作
    right_Encoder,               //右编码器工作
    double_Encoder,              //双编码器工作
}Encoder_flag;

void PIT0_IRQHandler(void);     //PIT0编码器中断服务函数
extern void Encoder(Encoder_flag Encoder_n,int Acq_time);//编码器工作初始化函数
extern Encoder_flag Encoder_flagextern;//中断工作状态标志
extern int Encoder_speed1;//编码器1的脉冲计数值，在main函数中调用即可获得计数值
extern int Encoder_speed2;//编码器2的脉冲计数值
extern int speedError[3];
extern int currentspeed; 
extern int debug_time;//调试模式
extern int wd_time;//弯道时间
extern int last_motorPWM;//上一次的pwm

#endif
