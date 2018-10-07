


#ifndef __JIWAN_H__
#define __JIWAN_H__

extern void jiwan();
extern int startrow;
extern uint8 youwanflag;
extern uint8 zuowanflag;
extern uint8 maybeyouwanflag;
extern uint8 maybezuowanflag;
extern uint8 swanflag_left;
extern uint8 swanflag_right;
extern uint8 jiwanflag;
extern uint8 blackpoint;
extern int8 error_zuowan;		        //左弯矫正偏差
extern int8 error_youwan;		        //右弯矫正偏差
extern int8 Center_zuowan[CAMERA_H];           //左弯中线
extern int8 Center_youwan[CAMERA_H];           //右弯中线
extern uint8 sum_left_left;                    //左边界向左点数
extern uint8 sum_left_right;                   //左边界向右点数
extern uint8 sum_right_left;                   //右边界向左点数
extern uint8 sum_right_right;                  //右边界向右点数
extern uint8 maynotswanflag_left;
extern uint8 maynotswanflag_right;
extern uint8 swanflag;


#endif  //__JIWAN_H__
