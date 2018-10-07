

#ifndef __GLOBAL_VARIABLE_H__
#define __GLOBAL_VARIABLE_H__

#define black  0x00
#define white  0xff
#define red  128

#define duojiMid  4875     //舵机中值 250:4100      300:3600
#define leftLimit 3570     //左极限值 250:2600      300：机械极限：2100
#define rightLimit 6200    //右极限值 250:6100      300：机械极限：5200

#define dianjispeed 1200   //电机速度 (1000：编码器110   1500：编码器170  1200：编码器130）
#define limitspeed 9900    //电机极限速度 

extern uint8 stop_enableflag;
extern uint8 BM1;
extern uint8 BM2;
extern uint8 BM3;
extern uint8 BM4;
extern uint8 deepblue; //模式
extern uint8 fznum;



#endif  //__GLOBAL_VARIABLE_H__
