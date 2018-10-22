#ifndef __QUICK_STOP_H__
#define __QUICK_STOP_H__

extern void quick_stop();
extern uint8 btow_i;//黑到白跳变行数
extern uint8 pre_btow_i;//上一行黑到白跳变行数 用于条件四
extern uint8 quickstop_flag;//急停标志位
extern uint8 allow_quickstop_flag;//允许急停标志位
extern uint8 left_limit_flag;//左边极限为白
extern uint8 right_limit_flag;//右边极限为白


#endif  //__QUICK_STOP_H__