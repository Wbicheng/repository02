


#ifndef __HUANDAO_H__
#define __HUANDAO_H__


#define maxsize 50
extern uint8   huandao1flag_right;
extern uint8	huandao2flag_right;
extern uint8	huandao1flag_left;
extern uint8	huandao2flag_left;
extern uint8	heitiaobian;          //黑跳变点
extern uint8	baitiaobian;          //白跳变点
extern uint8   heitiaobianhang_right[3];                 //右黑跳变行
extern uint8   heitiaobianhang_left[3];                  //左黑跳变行
extern uint8   baitiaobianhang_right[3];                //右白跳变行
extern uint8   baitiaobianhang_left[3];                 //左白跳变行
extern uint8   zhidaohuandao2flag;   //直道环岛2标志位
extern uint8   chuhuandaoflag_right; //出右环岛标志
extern uint8   chuhuandaoflag_left;  //出左环岛标志
extern uint8   huandao1[maxsize];//循环数组
extern uint8   nowpoint;           //循环数组的当前指针
extern uint8   prepoint;           //vsynnum场数前的指针
extern uint8   huandao1num;        //vsynnum场内要求满足的一定场数
extern uint16  huandaonum1_2_right;   //右环岛1激活2计数  huandaocount_right
extern uint16  huandaonum1_2_left;    //左环岛1激活2计数
extern uint8   ruhuandaoflag_right;                   //入右环岛标志
extern uint8   ruhuandaoflag_left;                    //入左环岛标志
extern uint16  huandaonum2_turn_right;  //右环岛2激活转弯计数
extern uint16  huandaonum2_turn_left;  //左环岛2激活转弯计数
extern uint16  rudaonum_right;//右环岛2转弯延时计数
extern uint16  rudaonum_left;//左环岛2转弯延时计数
extern uint16  chudaonum_right;//出右环岛计数
extern uint16  chudaonum_left;//出左环岛计数
extern uint16  vsynnum;   //确定环岛1的扫描场数
extern void huandao();
extern int absint();
extern uint16   huandaocount_right;  //右环岛计数
extern uint16   huandaocount_left;   //左环岛计数
extern uint8   xieruhuandaoflag_right; //斜入右环岛标志
extern uint8   xieruhuandaoflag_left;  //斜入左环岛标志
extern uint8   heitiaobianlienum;                              //黑跳变列数  
extern uint8   baitiaobianlienum;			      //白跳变列数 
extern uint8   baitiaobianlie_leftest;                         //最左的白跳到黑列数 
extern uint8   heitiaobianlie_rightest;                        //最右的黑跳到白列数  
extern uint8   kongbaihang;                                  //空白行                                
extern uint8   kongbaihang_flag;                              //左右边界间存在空白行标志   
extern uint8   yuandihang;                                     //圆的底行  
extern uint8   yuandihang_flag;                                //存在圆底行 
extern uint8   yuanlie;                                        //区别于双十字的特征--圆，判断斜入环岛时用
extern uint8 yuanlie_ruhuandao;                                  //入环岛时避免在斜入环岛时误入，即避免圆的特征
extern float   K_huandao;            //斜入环岛斜率
extern float   huandaoMid;           //斜入环岛中心
extern uint8 baitiaobianhang_right_col[CAMERA_W];//右环岛1列白跳变行
extern uint8 baitiaobianhang_left_col[CAMERA_W];//左环岛1列白跳变行
extern uint8 shangbanyuancount_right;	//右环岛上半圆计数器
extern uint8 shangbanyuancount_left;	//左环岛上半圆计数器
//大环岛
extern uint8 dahuandaoflag_left;     //左大环岛  ………
extern uint8 dahuandaoflag_right;	//右大环岛	………
extern uint8 dahuandaonum_left;           //大环岛识别到计数
extern uint8 dahuandaonum_right;
extern uint8 rudahuandaoflag_left;   //入左大环岛  ......
extern uint8 rudahuandaoflag_right;  //入右大环岛	......
extern uint8 ruhuandao_shang_i_left;      //入环岛上补点i  左环岛
extern uint8 ruhuandao_shang_j_left;	//入环岛上补点j
extern uint8 ruhuandao_xia_i_left;		//入环岛下补点i
extern uint8 ruhuandao_xia_j_left;		//入环岛下补点j

extern uint8 ruhuandao_shang_i_right;      //入环岛上补点i  右环岛
extern uint8 ruhuandao_shang_j_right;	//入环岛上补点j
extern uint8 ruhuandao_xia_i_right;		//入环岛下补点i
extern uint8 ruhuandao_xia_j_right;		//入环岛下补点j
extern float k_ruhuandao;        //入环岛斜率
extern uint16 indahuandaonum_left;
extern uint16 indahuandaonum_right;
extern uint8 chudahuandaoflag_left;        //出左大环岛标志
extern uint8 chudahuandaoflag_right;		//出右大环岛标志
extern uint8 chudahuandaonum_left;       //出环岛检测计数
extern uint8 chudahuandaonum_right;       //出环岛检测计数

extern uint8 rudahuandaonum_left;            //入大环岛计数   --用于补线。。。。。。。。。。。
extern uint8 rudahuandaonum_right;		//入大环岛计数 ---用于补线。。。。。。。。。。。。
extern uint8 nearchudahuandaoflag_left;       //靠近出环岛标志  。。。。。。。。。
extern uint8 nearchudahuandaoflag_right;      //靠近出环岛标志 。。。。。。。。。
extern uint8	chudaodian_left_i;             //出环岛标志比较点
extern uint8	chudaodian_right_i;	        //出环岛标志比较点
extern uint8  nohuandaonum;  // 屏蔽环岛计数
extern uint8 btowhang;   //从下向上的黑到白的跳变行 ............................................
extern uint8 wtobhang;   //从下向上的白到白的跳变行..................................................

extern uint8 ruhuandao1num_left;  //入左环岛1计数
extern uint8 ruhuandao1num_right;  //入右环岛1计数
extern uint8 ruhuandao2num_left;//入左环岛2计数
extern uint8 ruhuandao2num_right;//入右环岛2计数

extern uint8 nearhuandaoflag_left; //靠近左环岛标志
extern uint8 nearhuandaoflag_right;//靠近右环岛标志

extern uint8 hang20_mid;  //在环岛中入环岛1和入环岛2前中线位置
extern uint8 hang20_mid_hang;

extern uint8 baitiaobian_sum;
extern uint8 btowlie;  //黑to白跳变列     ^^^^^^^^^^^^^^^^^^^^^^
extern uint8 jiange_wai;  //避免判断为路障 靠外的间隔  ^^^^^^
extern uint8 jiange_nei;//避免判断为路障 靠内的间隔    ^^^^^^^^^



#endif  //__huandao_H__
