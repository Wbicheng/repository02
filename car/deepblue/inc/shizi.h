


#ifndef __SHIZI_H__
#define __SHIZI_H__

extern void shizi();
extern uint8 xierushiziflag;		//斜入十字标志
extern uint8 shiziflag_right;		//右斜入十字标志
extern uint8 shiziflag_left;		//左斜入十字标志
extern uint8 baitiaobian_left;		//最左列白跳变点
extern uint8 baitiaobian_right;	        //最右列白跳变点
extern uint8 shizinum_right;		//右斜入十字延时计数
extern uint8 shizinum_left;		//左斜入十字延时计数
extern uint8 maybeshiziflag;
extern uint8 tiaobianhang_sz_left;
extern uint8 tiaobianhang_sz_right;
extern float K_sz;
extern uint8 buxian_sz_down;
extern uint8 buxian_sz_up;
extern uint8 error_sz;
extern uint8 tiaobianhang_nearsz_left;
extern uint8 tiaobianhang_nearsz_right;
extern uint8 nearszflag_left;
extern uint8 nearszflag_right;
extern uint8 startrow_nearsz;		//靠近十字扫描行
extern float K_nearsz;
extern uint8 xiexian_shang_i;                                    //斜线上点(行)   --算连线判断是否斜入
extern uint8 xiexian_shang_j;                                    //斜线上点(列)   --算连线判断是否斜入
extern uint8 xiexian_xia_i;                                    //斜线下点(行)   --算连线判断是否斜入
extern uint8 xiexian_xia_j;                                    //斜线下点(列)   --算连线判断是否斜入
extern float xiexian_k;                                      //斜线斜率 
extern uint8 baitiaobianhang;                                  //白-黑跳变  --界定右边查找斜线上点的范围
extern uint8 xierushizi_flag_right;			        //斜入十字右标志 
extern uint8 xierushizi_flag_left;				//斜入十字左标志 
extern uint8 farszflag_right;                                  //右远十字标志
extern uint8 farszflag_left;                                   //左远十字标志
extern uint8 dixiehangnum_left;   //左斜入十字底斜行    
extern uint8 dixiehangnum_right;  //右斜入十字底斜行	
extern uint8 xieruqushidian1;     //斜入十字趋势点1
extern uint8 xieruqushidian2;    //斜入十字趋势点2
extern uint8 xieruqushidian3;	  //斜入十字趋势点3
extern uint8 hang20_mid_xieru;   //斜入十字补点  

#endif  //__SHIZI_H__
