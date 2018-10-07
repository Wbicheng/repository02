


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
extern int8 error_zuowan;		        //�������ƫ��
extern int8 error_youwan;		        //�������ƫ��
extern int8 Center_zuowan[CAMERA_H];           //��������
extern int8 Center_youwan[CAMERA_H];           //��������
extern uint8 sum_left_left;                    //��߽��������
extern uint8 sum_left_right;                   //��߽����ҵ���
extern uint8 sum_right_left;                   //�ұ߽��������
extern uint8 sum_right_right;                  //�ұ߽����ҵ���
extern uint8 maynotswanflag_left;
extern uint8 maynotswanflag_right;
extern uint8 swanflag;


#endif  //__JIWAN_H__
