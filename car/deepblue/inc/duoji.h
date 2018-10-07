

#ifndef __DUOJI_H__
#define __DUOJI_H__

extern void duoji();
extern float Kp;
extern float Ki;
extern float Kd;
extern uint8 standardrow; //基准行
extern int errors;           //静态偏差
extern int perrors;        //上一场偏差
extern uint8 Center;          //场中心    
extern uint32 duoji_PWM;      //舵机PWM
extern float Kp_w;
extern float Kd_w;
extern float Kp_z;
extern float Kd_z;
extern uint16 mid_line;



#endif  //__DUOJI_H__

