

#ifndef __DUOJI_H__
#define __DUOJI_H__

extern void duoji();
extern float Kp;
extern float Ki;
extern float Kd;
extern uint8 standardrow; //��׼��
extern int errors;           //��̬ƫ��
extern int perrors;        //��һ��ƫ��
extern uint8 Center;          //������    
extern uint32 duoji_PWM;      //���PWM
extern float Kp_w;
extern float Kd_w;
extern float Kp_z;
extern float Kd_z;
extern uint16 mid_line;



#endif  //__DUOJI_H__

