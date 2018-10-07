


#ifndef __ZHIDAO_H__
#define __ZHIDAO_H__

extern void zhidao();
extern uint8 zhidaoflag;
extern uint8 tiaobianflag_left;
extern uint8 tiaobianflag_right;
extern uint8 tiaobianhang_right;
extern uint8 tiaobianhang_left;
extern uint8 zhidaohuandaoflag;
extern int whitesum;
extern uint8 stop_enableflag;//初始1000场不进行识别
extern uint8 stop_flag;//终点线标志
extern uint16 zdnum; //前几百场不激活识别
extern uint8 btownum;//特定行的黑白跳变
extern uint8 lianxuhangnum_left; //连续行数
extern uint8 lianxuhangnum_right;

#endif  //__ZHIDAO_H__
