


#ifndef __LUZHANG_H__
#define __LUZHANG_H__
 
extern void luzhang();
extern uint8 heitiaobian_lz[CAMERA_H];			//路障黑跳变点
extern uint8 baitiaobian_lz[CAMERA_H];			//路障白跳变点
extern uint8 luzhangflag_left;		                //左路障标志
extern uint8 luzhangflag_right;		                //右路障标志
extern int8 blacksum_lz[CAMERA_H];	                //路障黑点数
extern int16 right_lz[CAMERA_H];		//右路障边界
extern int16 left_lz[CAMERA_H];		//左路障边界
extern uint8 startrow_lz;                      //路障提线开始行
extern uint8 endrow_lz;                        //路障提线结束行
extern float K_lz;                             //路障提线斜率
extern uint8 lzflag_right;                   //右路障中标志
extern uint8 lzflag_left;                    //左路障中标志
extern uint8 delaynum_lz_right;                //右路障结束场计数器
extern uint8 delaynum_lz_left;                 //左路障结束场计数器
extern uint8 clearflag_lz_right;               //清右路障标志
extern uint8 clearflag_lz_left;               //清左路障标志
extern uint8 center_lz;                         //路障中心
#endif  //__ZHIDAO_H__
