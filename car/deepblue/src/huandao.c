#include "common.h"
#include "include.h"
#include "huandao.h"

uint8   huandao1flag_right;
uint8	huandao2flag_right;
uint8	huandao1flag_left;
uint8	huandao2flag_left;
uint8	heitiaobian;                             //黑跳变点
uint8	baitiaobian;                             //白跳变点
uint8   heitiaobianhang_right[3];                 //右黑跳变行
uint8   heitiaobianhang_left[3];                  //左黑跳变行
uint8   baitiaobianhang_right[3];                //右白跳变行
uint8   baitiaobianhang_left[3];                 //左白跳变行
uint8   zhidaohuandao2flag;                      //直道环岛2标志位
uint8   chuhuandaoflag_right;                    //出右环岛标志
uint8   chuhuandaoflag_left;                      //出左环岛标志
uint8   huandao1[maxsize]={0};                  //循环数组
uint8   nowpoint=0;                              //循环数组的当前指针
uint8   prepoint=0;                             //vsynnum场数前的指针
uint8   huandao1num=0;                            //vsynnum场内要求满足的一定场数
uint16  huandaonum1_2_right=0;                   //右环岛1激活2计数  huandaocount_right
uint16  huandaonum1_2_left=0;                    //左环岛1激活2计数
uint16  huandaonum2_turn_right=0;               //右环岛2激活转弯计数
uint16  huandaonum2_turn_left=0;                 //左环岛2激活转弯计数
uint8   ruhuandaoflag_right=0;                   //入右环岛标志
uint8   ruhuandaoflag_left=0;                    //入左环岛标志
uint16  rudaonum_right=0;                       //右环岛2转弯延时计数
uint16  rudaonum_left=0;                        //左环岛2转弯延时计数
uint16  chudaonum_right=0;                      //出右环岛计数
uint16  chudaonum_left=0;                       //出左环岛计数
uint16  vsynnum=10;                             //确定环岛1的扫描场数
uint16  huandaocount_right;                     //右环岛计数
uint16  huandaocount_left;                      //左环岛计数
uint8   xieruhuandaoflag_right;                 //斜入右环岛标志
uint8   xieruhuandaoflag_left;                  //斜入左环岛标志
uint8 heitiaobianlienum;                                  //黑跳变列数  
uint8 baitiaobianlienum;				        //白跳变列数 
uint8 baitiaobianlie_leftest;                             //最左的白跳到黑列数 
uint8 heitiaobianlie_rightest;                            //最右的黑跳到白列数  
uint8 kongbaihang;                                        //空白行
uint8 kongbaihang_flag;                                   //左右边界间存在空白行标志  
uint8 yuandihang;                                         //圆的底行  
uint8 yuandihang_flag;                                    //存在圆底行 
uint8 yuanlie;                                            //区别于双十字的特征--圆，判断斜入时用
uint8 yuanlie_ruhuandao;                                  //入环岛时避免在斜入环岛时误入，即避免圆的特征
float   K_huandao;                                      //斜入环岛斜率
float   huandaoMid;                                     //斜入环岛中心
uint8 baitiaobianhang_right_col[CAMERA_W]={0};//右环岛1列白跳变行
uint8 baitiaobianhang_left_col[CAMERA_W]={0};//左环岛1列白跳变行
uint8 shangbanyuancount_right;	//右环岛上半圆下降计数器
uint8 shangbanyuancount_left;	//左环岛上半圆下降计数器
uint8 shangbanyuancount_right_up;//右环岛上半圆上升计数器
uint8 shangbanyuancount_left_up;//左环岛上半圆上升计数器
uint8 tiaobianhang_right_hd;    //右环岛右边界跳变行
uint8 tiaobianhang_left_hd;     //左环岛左边界跳变行

//大环岛
uint8 dahuandaoflag_left=0;     //左大环岛  ………
uint8 dahuandaoflag_right=0;	//右大环岛	………
uint8 dahuandaonum_left=0;           //大环岛识别到计数
uint8 dahuandaonum_right=0;
uint8 rudahuandaoflag_left;   //入左大环岛  ......
uint8 rudahuandaoflag_right;  //入右大环岛	......

uint8 ruhuandao_shang_i_left=0;      //入环岛上补点i  左环岛
uint8 ruhuandao_shang_j_left=0;	//入环岛上补点j
uint8 ruhuandao_xia_i_left=0;		//入环岛下补点i
uint8 ruhuandao_xia_j_left=0;		//入环岛下补点j

uint8 ruhuandao_shang_i_right=0;      //入环岛上补点i  右环岛
uint8 ruhuandao_shang_j_right=0;	//入环岛上补点j
uint8 ruhuandao_xia_i_right=0;		//入环岛下补点i
uint8 ruhuandao_xia_j_right=0;		//入环岛下补点j
float k_ruhuandao;        //入环岛斜率

uint16 indahuandaonum_left=0;   //出大环岛计数：1.入环岛时补线 2.出环岛时补线
uint16 indahuandaonum_right=0;
uint8 chudahuandaoflag_left;        //出左大环岛标志
uint8 chudahuandaoflag_right;		//出右大环岛标志
uint8 chudahuandaonum_left=0;       //出环岛检测计数
uint8 chudahuandaonum_right=0;       //出环岛检测计数

uint8 rudahuandaonum_left=0;            //入大环岛计数   --用于补线。。。。。。。。。。。
uint8 rudahuandaonum_right=0;		//入大环岛计数 ---用于补线。。。。。。。。。。。。
uint8 nearchudahuandaoflag_left;       //靠近出环岛标志  。。。。。。。。。
uint8 nearchudahuandaoflag_right;      //靠近出环岛标志 。。。。。。。。。
uint8	chudaodian_left_i;             //出环岛标志比较点
uint8	chudaodian_right_i;	        //出环岛标志比较点
uint8  nohuandaonum=0;  // 屏蔽环岛计数
uint8 btowhang;   //从下向上的黑到白的跳变行 ............................................
uint8 wtobhang;   //从下向上的白到白的跳变行..................................................

uint8 ruhuandao1num_left=0;  //入左环岛1计数
uint8 ruhuandao1num_right=0;  //入右环岛1计数
uint8 ruhuandao2num_left=0;//入左环岛2计数
uint8 ruhuandao2num_right=0;//入右环岛2计数

uint8 nearhuandaoflag_left; //靠近左环岛标志
uint8 nearhuandaoflag_right;//靠近右环岛标志

uint8 hang20_mid=0;  //在环岛中入环岛1和入环岛2前中线位置
uint8 hang20_mid_hang=0;

uint8 heitiaobianhang_right_hd;
uint8 heitiaobianhang_left_hd;
uint8 baitiaobianhang_right_hd[CAMERA_H];
uint8 baitiaobianhang_left_hd[CAMERA_H];

uint8 baitiaobian_sum;
uint8 btowlie=0;  //黑to白跳变列     ^^^^^^^^^^^^^^^^^^^^^^
uint8 jiange_wai=0;  //避免判断为路障 靠外的间隔  ^^^^^^
uint8 jiange_nei=0;//避免判断为路障 靠内的间隔    ^^^^^^^^^
uint8 ruhuandaohang_left;
uint8 ruhuandaohang_right;

int absint(int a)
{
    if(a<=0) a=-a;
    return a;

}

void huandao()
{
             switch(deepblue)
             {
              case 1: ruhuandaohang_left=45;ruhuandaohang_right=45;break;
   case 2: ruhuandaohang_left=40;ruhuandaohang_right=40;break;
  case 3: ruhuandaohang_left=40;ruhuandaohang_right=40;break;
  case 4: ruhuandaohang_left=40;ruhuandaohang_right=40;break;
  case 5: ruhuandaohang_left=40;ruhuandaohang_right=40;break;
  case 6: ruhuandaohang_left=40;ruhuandaohang_right=40;break;
  case 7: ruhuandaohang_left=40;ruhuandaohang_right=40;break;
  case 8: ruhuandaohang_left=40;ruhuandaohang_right=40;break;
  case 9: ruhuandaohang_left=40;ruhuandaohang_right=40;break;
  case 10: ruhuandaohang_left=40;ruhuandaohang_right=40;break;
  case 11: ruhuandaohang_left=40;ruhuandaohang_right=40;break;
  case 12: ruhuandaohang_left=40;ruhuandaohang_right=40;break;
  case 13: ruhuandaohang_left=40;ruhuandaohang_right=40;break;
             }
  
  
                zhidaohuandao2flag=0;
		for(j=35;j<=45;j++)
		{
			whitesum=0;
			for(i=CAMERA_H-1;i>CAMERA_H/20;i--)
			{
				if(img[i][j]!=black)
				{
					whitesum++;
				}
			}
			if(whitesum==CAMERA_H-4)
			{
				zhidaohuandao2flag=1;
				break;
			}
		}

                for(i=0;i<3;i++)          //每场黑白跳变行清0                
                {
                  heitiaobianhang_right[i]=0;                 
                  heitiaobianhang_left[i]=0;                  
                  baitiaobianhang_right[i]=0;                
                  baitiaobianhang_left[i]=0;
                } 
                
 /******************************************************环岛*********************************************************/


/*****************************************************即将环岛***********************************************************/

//即将右环岛
nearhuandaoflag_right=0;
if(!tiaobianflag_left && zhidaohuandaoflag  && !nohuandaonum && tiaobianflag_right) //入环岛标志：1.左无跳变行，即左连续 2.32-48存在白列
{
	nearhuandaoflag_right=1;
	j=CAMERA_W-1;
	heitiaobian=0;  //右边界从下至上存在1到2个百跳变点，1个黑跳变点
	baitiaobian=0;
	btowhang=0;
	wtobhang=0;
	for(i=CAMERA_H-1;i>3;i--) //过滤上面几行可能噪点
	{
		if(img[i][j]==black && img[i-1][j]==white)
       {
			heitiaobian++;
			btowhang=i;  //黑
		}
		if(img[i][j]==white && img[i-1][j]==black)
		{
			baitiaobian++;
			wtobhang=i;  //白
		}
	}
	if(!((baitiaobian==1 || baitiaobian==2) && heitiaobian==1))
	{
		nearhuandaoflag_right=0;
	}
        if(btowhang==0 || wtobhang==0)
                        nearhuandaoflag_right=0;
	if(nearhuandaoflag_right && wtobhang>=btowhang) //从下至上白跳变应在黑跳变之上
			nearhuandaoflag_right=0;
	if(nearhuandaoflag_right)//白跳变下两行全白
	{
		i=wtobhang;
		for(j=left[wtobhang]+1;j<CAMERA_W;j++)
		{
			if(img[i][j]==black)
			{
				nearhuandaoflag_right=0;
				break;
			}	
		//	img[i][j]=100;
		}
		i++;
		if(nearhuandaoflag_right)
		{	
			for(j=left[i]+1;j<CAMERA_W;j++)
			{
				if(img[i][j]==black)
				{
					nearhuandaoflag_right=0;
					break;		
				}
			}		
		}	
	}
	if(nearhuandaoflag_right)//黑跳变行有向上趋势 跳变行上一行向左边界扫存在一个黑跳变，一个白跳变
	{
		heitiaobian=0;
		baitiaobian=0;
		i=btowhang-1;
		btowlie=0;  //黑to白跳变列 ..................................................................
		for(j=CAMERA_W-1;j>left[i]+1;j--)
		{
			if(img[i][j]==black && img[i][j-1]==white) //...................................
			{
				heitiaobian++;
				if(btowlie==0)
					btowlie=j;
			}
		
			if(img[i][j]==white && img[i][j-1]==black)
				baitiaobian++;
		}
		if(heitiaobian!=1 || baitiaobian!=1)
			nearhuandaoflag_right=0;	
	}
        if(nearhuandaoflag_right)//三角形位置限定
	{
                if(btowhang<=10)
		nearhuandaoflag_right=0;
	
	}
        if(nearhuandaoflag_right) //...................................
	{
		jiange_wai=0;
		jiange_nei=0;
		for(i=btowhang-1;i>0;i--)
		{
			if(img[i][CAMERA_W-1]==black)
				break;
			else 
				jiange_wai++;
			
		}
		for(i=btowhang-1;i>0;i--)
		{
			if(img[i][btowlie]==black && img[i-1][btowlie]==white)
				jiange_nei=1;
			if(jiange_nei)
				jiange_nei++;
			if(img[i][btowlie]==white && img[i-1][btowlie]==black)
				break;
		
		}
		jiange_nei--;//因为从黑点开始计
		if(jiange_nei-jiange_wai>=4)
			nearhuandaoflag_right=0; //内外间隔过大为路障，非即将环岛
	
	}
	if(nearhuandaoflag_right) //避免与s弯冲突，右下角为三角形区域
	{
		for(i=btowhang;i<CAMERA_H;i++)
		{
			if(img[i][right[btowhang]-1]==black)
			{
				nearhuandaoflag_right=0;
				break;
			}
		
		}	
	}
}
//即将左环岛
nearhuandaoflag_left=0;
if(!tiaobianflag_right && zhidaohuandaoflag && !nohuandaonum  && tiaobianflag_left) //入环岛标志：1.右无跳变行  2.32-48存在白列  3.左跳变  //////////////////////////
{
	nearhuandaoflag_left=1;
	j=0;
	heitiaobian=0;  //右边界从下至上存在1到2个白跳变点，1个黑跳变点
	baitiaobian=0;
	btowhang=0;
	wtobhang=0;
	for(i=CAMERA_H-1;i>3;i--) //过滤上面几行可能噪点
	{
		if(img[i][j]==black && img[i-1][j]==white)
       {
			heitiaobian++;
			btowhang=i;  //黑
		}
		if(img[i][j]==white && img[i-1][j]==black)
		{
			baitiaobian++;
			wtobhang=i;  //白
		}
	}
	if(!((baitiaobian==1 || baitiaobian==2) && heitiaobian==1))
	{
		nearhuandaoflag_left=0;
	}
        if(btowhang==0 || wtobhang==0)
                        nearhuandaoflag_left=0;
	if(nearhuandaoflag_left && wtobhang>=btowhang) //从下至上白跳变应在黑跳变之上
			dahuandaoflag_left=0;
	if(nearhuandaoflag_left)//白跳变下两行全白
	{
		i=wtobhang;
		for(j=0;j<right[i]-1;j++)
		{
			if(img[i][j]==black)
			{
				nearhuandaoflag_left=0;
				break;
			}	
		//	img[i][j]=100;
		}
		i++;
		if(nearhuandaoflag_left)
		{	
			for(j=0;j<right[i]-1;j++)
			{
				if(img[i][j]==black)
				{
					nearhuandaoflag_left=0;
					break;		
				}
			}		
		}	
	}
	if(nearhuandaoflag_left)//黑跳变行有向上趋势 跳变行上一行向右边界扫存在一个黑跳变，一个白跳变
	{
		heitiaobian=0;
		baitiaobian=0;
		i=btowhang-1;
		btowlie=0;  //黑to白跳变列 ..................................................................
		for(j=0;j<right[i]-1;j++)
		{
			if(img[i][j]==black && img[i][j+1]==white)//.....................
			{
				heitiaobian++;
				if(btowlie==0)
					btowlie=j;
			}
			if(img[i][j]==white && img[i][j+1]==black) 
			baitiaobian++;
		}
		if(heitiaobian!=1 || baitiaobian!=1)
			nearhuandaoflag_left=0;
	
	}
        if(nearhuandaoflag_left)//三角形位置限定
	{
		if(btowhang<=10)
			nearhuandaoflag_left=0;
	
	}
        if(nearhuandaoflag_left) //....................
	{
		jiange_wai=0;
		jiange_nei=0;
		for(i=btowhang-1;i>0;i--)
		{
			if(img[i][0]==black)
				break;
			else 
				jiange_wai++;
			
		}
		for(i=btowhang-1;i>0;i--)
		{
			if(img[i][btowlie]==black && img[i-1][btowlie]==white)
				jiange_nei=1;
			if(jiange_nei)
				jiange_nei++;
			if(img[i][btowlie]==white && img[i-1][btowlie]==black)
				break;
		
		}
		jiange_nei--;//因为从黑点开始计
		if(jiange_nei-jiange_wai>=4)
			nearhuandaoflag_left=0; //内外间隔过大为路障，非即将环岛
	
	}
	if(nearhuandaoflag_left) //避免与s弯冲突，左下角为三角形区域
	{
		for(i=btowhang;i<CAMERA_H;i++)
		{
			if(img[i][left[btowhang]+1]==black)
			{
				nearhuandaoflag_left=0;
				break;
			}		
		}	
	}
}

  //循环数组运算：
      //  huandao1num=0;//
        nowpoint=(nowpoint+1)%maxsize;
       if(nearhuandaoflag_left||nearhuandaoflag_right)
       //   if(huandao1flag_left||huandao1flag_right)
          huandao1[nowpoint]=1;
        else
          huandao1[nowpoint]=0;
        if(nowpoint-vsynnum<0)
          prepoint=maxsize-absint(nowpoint-vsynnum);	
	else
	prepoint=nowpoint-vsynnum;
        while(prepoint!=nowpoint)
        {
          if(huandao1[prepoint]==1)
            huandao1num++;
          prepoint=(prepoint+1)%maxsize;
              
        }
         if(huandao1num>=5)   //10场里出现任意3场环岛1即可
        {
           if(nearhuandaoflag_left) 
            dahuandaonum_left=50;//入环岛激活允许时间
           if(nearhuandaoflag_right) 
            dahuandaonum_right=50;//入环岛激活允许时间        
        }
 /*       if(huandao1num>=3)   //10场里出现任意3场环岛1即可
        {
           if(huandao1flag_left) 
            huandaonum1_2_left=20;//左环岛二激活允许时间
           if(huandao1flag_right) 
            huandaonum1_2_right=20;//右环岛二激活允许时间
            if(xieruhuandaoflag_left)
             huandaonum1_2_left=50;//左环岛二激活允许时间
           if(xieruhuandaoflag_right)
             huandaonum1_2_right=50;//左环岛二激活允许时间           
        }
   */
/***********************************************************入环岛1***********************************************************************////////////不使用

//原小环岛环岛1+原大环岛识别

/********************************************原小环岛环岛1************************************************/  //入环岛1
//斜入右环岛判断
/*	xieruhuandaoflag_right=0;
	if(!wuxiaohang_flag && tiaobianflag_right &&(!tiaobianflag_left||(tiaobianhang_left<=3)) ) 
	{		//条件：不存在无效行或无效行较高，且左边界无跳变或跳变行小于3行（避免噪点），右边界有跳变
		                           				
	    kongbaihang=0;
		for(i=3;i<30;i++)//找空白行
		{
			kongbaihang_flag=1;
			for(j=left[i]+1;j<=right[i]-1;j++)
			{
				if(img[i][j]==black)
				{
					kongbaihang_flag=0;
					break;
				}
			}
			if(kongbaihang_flag)
			{
				kongbaihang=i;
				break;
			}
		
		}
		yuandihang=0;
		if(kongbaihang_flag)
			yuandihang_flag=1;
		else 
			yuandihang_flag=0;
		xieruhuandaoflag_right=1;	
		baitiaobianlie_leftest=CAMERA_W-1;
		heitiaobianlie_rightest=0; //每场都重新找
		if(kongbaihang_flag)
		{
			for(i=0;i<kongbaihang;i++) //过滤掉前几行的噪点,圆环范围在0至30间，避免不存在圆环，故白底行不能为3
			{
				heitiaobianlienum=0;
				baitiaobianlienum=0;
				for(j=left[i]+1;j<right[i]-3;j++) //找3到30行的跳变点，判断是否满足圆的特征，并提取圆的左右边界跳变点,取为右边界左3列避免噪点
				{
				
					if(img[i][j]==white && img[i][j+1]==black )
					{
						baitiaobianlienum++;
						if(j+1<=baitiaobianlie_leftest)
						{
							baitiaobianlie_leftest=j+1;
						}
					}
					if(img[i][j]==black && img[i][j+1]==white)
					{
						heitiaobianlienum++;
						if(j>=heitiaobianlie_rightest)
						{
							heitiaobianlie_rightest=j;
						}
					}
				}

				if(baitiaobianlienum!=1||heitiaobianlienum!=1)//圆环所在行需满足改列有一个白—黑，一个黑—白
				{
					yuandihang_flag=0;
					xieruhuandaoflag_right=0;
					break;	
				}
			}
		}
		if(yuandihang_flag)
		{
			yuandihang=kongbaihang-1;
		}
		else
			xieruhuandaoflag_right=0;
			
		if(heitiaobianlie_rightest==0)//圆右边界不存在
			xieruhuandaoflag_right=0;
                if(xieruhuandaoflag_right)//在第0列第2行以下应为全白，避免与双十字/入单十字冲突
		{
			j=0;
			for(i=2;i<=CAMERA_H-1;i++)
			{
				if(img[i][j]==black)
				{
					xieruhuandaoflag_right=0;
					break;
				}
			
			}
		
		}
		if(xieruhuandaoflag_right)
		{
			for(j=left[yuandihang+1]+1;j<=right[yuandihang+1]-1;j++) //圆底行左右边界间为白
			{
				if(img[yuandihang+1][j]==black)
				{
					xieruhuandaoflag_right=0;
					break;
				}
			}
		}
	
		if(xieruhuandaoflag_right)	//圆右边界向下扫要有黑白跳变
		{
			heitiaobian=0;														
			baitiaobian=0;
			for(i=yuandihang+1;i<CAMERA_H-1;i++)
			{
				if(img[i][heitiaobianlie_rightest]==black && img[i+1][heitiaobianlie_rightest]==white )
				{
					
					heitiaobian++;
				}
				if(img[i][heitiaobianlie_rightest]==white && img[i+1][heitiaobianlie_rightest]==black)
				{
					baitiaobian++;
				}
			
			}
			if(baitiaobian!=1||heitiaobian>=2) //圆左边界无白—黑跳变肯定不符合;黑—白跳变最多1个
			{
				xieruhuandaoflag_right=0;
			
			}

		
		
		}
		if(xieruhuandaoflag_right)//圆左边界向下扫全为白
		{
			for(i=yuandihang+1;i<=CAMERA_H-1;i++)
			{
				if(img[i][baitiaobianlie_leftest]==black)
				{
					xieruhuandaoflag_right=0;
					break;
				}
			}
		}
		if(xieruhuandaoflag_right)//顶行圆上边界下扫需要有白跳变点，避免和双十字冲突
		{
			yuanlie=0;
			for(j=baitiaobianlie_leftest-2;j<heitiaobianlie_rightest;j++)
			{
				if(img[0][j]==white&&img[0][j+1]==black)
				{
					yuanlie=j;
					break;
				}
			}
			if(yuanlie!=0)
			{
				baitiaobian=0;														
				for(i=0;i<CAMERA_H-1;i++)
				{
					if(img[i][yuanlie]==white && img[i+1][yuanlie]==black )
					{
						baitiaobian++;
					}
			
				}
				if(baitiaobian==0)
				{
					xieruhuandaoflag_right=0;
				}
			}
			else 
				xieruhuandaoflag_right=0;
		}
         }*/
//斜入环岛提线
  /**	if(xieruhuandaoflag_right)
	{
		K_huandao=(initcenter-visvalMid[0])/(float)CAMERA_H;
		huandaoMid=initcenter-K_huandao*(CAMERA_H-standardrow);
	}
    **/
        
        
//斜入左环岛判断
/*	xieruhuandaoflag_left=0;
	if(!wuxiaohang_flag && tiaobianflag_left &&(!tiaobianflag_right||(tiaobianhang_right<=3)) ) 
	{		//条件：不存在无效行，且右边界无跳变或跳变行小于3行，左边界有跳变		                           						
	    kongbaihang=0;
		for(i=3;i<30;i++)//找空白行
		{
			kongbaihang_flag=1;
			for(j=left[i]+1;j<=right[i]-1;j++)
			{
				if(img[i][j]==black)
				{
					kongbaihang_flag=0;
					break;
				}
			}
			if(kongbaihang_flag)
			{
				kongbaihang=i;
				break;
			}
		
		}
		yuandihang=0;
		if(kongbaihang_flag)
			yuandihang_flag=1;
		else 
			yuandihang_flag=0;
		xieruhuandaoflag_left=1;	
		baitiaobianlie_leftest=CAMERA_W-1;
		heitiaobianlie_rightest=0; //每场都重新找
		if(kongbaihang_flag)
		{
			for(i=0;i<kongbaihang;i++) //过滤掉前几行的噪点,圆环范围在0至30间，避免不存在圆环，故白底行不能为3
			{
				heitiaobianlienum=0;
				baitiaobianlienum=0;
				for(j=left[i]+1;j<right[i]-3;j++) //找3到30行的跳变点，判断是否满足圆的特征，并提取圆的左右边界跳变点,取为右边界左3列避免噪点
				{
				
					if(img[i][j]==white && img[i][j+1]==black )
					{
						baitiaobianlienum++;
						if(j+1<=baitiaobianlie_leftest)
						{
							baitiaobianlie_leftest=j+1;
						}
					}
					if(img[i][j]==black && img[i][j+1]==white)
					{
						heitiaobianlienum++;
						if(j>=heitiaobianlie_rightest)
						{
							heitiaobianlie_rightest=j;
						}
					}		 
				}
				if(baitiaobianlienum!=1||heitiaobianlienum!=1)//圆环所在行需满足改列有一个白—黑，一个黑—白
				{
					yuandihang_flag=0;
					xieruhuandaoflag_left=0;
					break;	
				}
			}
		}
		if(yuandihang_flag)
		{
			yuandihang=kongbaihang-1;
		}
		else
			xieruhuandaoflag_left=0;
			
		if(heitiaobianlie_rightest==0)//圆右边界不存在
			xieruhuandaoflag_left=0;
                if(xieruhuandaoflag_left)//在尾列第2行以下应为全白，避免与双十字/入单十字冲突
		{
			j=CAMERA_W-1;
			for(i=2;i<=CAMERA_H-1;i++)
			{
				if(img[i][j]==black)
				{
					xieruhuandaoflag_right=0;
					break;
				}
			
			}
		
		}
		if(xieruhuandaoflag_left)
		{
			for(j=left[yuandihang+1]+1;j<=right[yuandihang+1]-1;j++) //圆底行左右边界间为白
			{
				if(img[yuandihang+1][j]==black)
				{
					xieruhuandaoflag_left=0;
					break;
				}
		
			}
		}
	
		if(xieruhuandaoflag_left)	//圆左边界向下扫要有黑白跳变
		{
			heitiaobian=0;														
			baitiaobian=0;
			for(i=yuandihang+1;i<CAMERA_H-1;i++)
			{
				if(img[i][baitiaobianlie_leftest]==black && img[i+1][baitiaobianlie_leftest]==white )
				{
					heitiaobian++;
				}
				if(img[i][baitiaobianlie_leftest]==white && img[i+1][baitiaobianlie_leftest]==black)
				{
					baitiaobian++;
				}
			}
			if(baitiaobian!=1||heitiaobian>=2) //圆左边界无白—黑跳变肯定不符合;黑—白跳变最多1个
			{
				xieruhuandaoflag_left=0;
			
			}
		}
		if(xieruhuandaoflag_left)//圆右边界向下扫全为白
		{
			for(i=yuandihang+1;i<=CAMERA_H-1;i++)
			{
				if(img[i][heitiaobianlie_rightest]==black)
				{
					xieruhuandaoflag_left=0;
					break;
				}
			}
		}
		if(xieruhuandaoflag_left)//顶行圆上边界下扫需要有白跳变点，避免和双十字冲突
		{
			yuanlie=0;
			for(j=heitiaobianlie_rightest+1;j>baitiaobianlie_leftest;j--)
			{
				if(img[0][j]==white&&img[0][j-1]==black)
				{
					yuanlie=j;
					break;				
				}
			}
			if(yuanlie!=0)
			{
				baitiaobian=0;														
				for(i=0;i<CAMERA_H-1;i++)
				{
					if(img[i][yuanlie]==white && img[i+1][yuanlie]==black )
					{
						baitiaobian++;
					}
			
				}
				if(baitiaobian==0)
				{
					xieruhuandaoflag_left=0;
				}	
			}
			else 	xieruhuandaoflag_left=0;
			
		}
        }*/
//斜入环岛提线
/**	if(xieruhuandaoflag_left)
	{
		K_huandao=(visvalMid[0]-initcenter)/(float)CAMERA_H;
		huandaoMid=initcenter+K_huandao*(CAMERA_H-standardrow);
	}
 **/   
//dahuandaonum_right=1;//调试用        
	//右环岛1判断
/*	huandao1flag_right=0;
	if(!wuxiaohang_flag && !tiaobianflag_left && tiaobianflag_right 
           &&   zhidaohuandaoflag && tiaobianhang_right<20  && dahuandaonum_right) 
	{							     //条件1：不存在无效行或无效行较高，且左边界无跳变，右边界有跳变,存在全白一列
		huandao1flag_right=1;				  //条件2：最右列满足有一个白跳变点，两个黑跳变点
		//for(j=CAMERA_W-1;j>CAMERA_W-3;j--)    //从上至下扫黑白跳变点 扫最右边两列
	//	{																					
			heitiaobian=0;
			baitiaobian=0;
			for(i=0;i<CAMERA_H-1;i++)
			{
				j=CAMERA_W-1;
				if(img[i][j]==black && img[i+1][j]==white && img[i+2][j]==white && i>=2)
				{
					heitiaobianhang_right[heitiaobian]=i;
					heitiaobian++;
				}
				if(img[i][j]==white && img[i+1][j]==black && i>=heitiaobianhang_right[0] && heitiaobianhang_right[0]!=0)
				{
					baitiaobianhang_right[baitiaobian]=i;
					baitiaobian++;
				}
			}
			if(baitiaobian!=1 || heitiaobian!=2 || heitiaobianhang_right[0]>15 ||	heitiaobianhang_right[1]<20		//条件4：黑白跳变行满足一定范围
				|| heitiaobianhang_right[1]>=50 || baitiaobianhang_right[0]<5	|| baitiaobianhang_right[0]>25)
			{
				huandao1flag_right=0;
				//break;
			}
			if(huandao1flag_right)
			{
				for(j=CAMERA_W-1;j>CAMERA_W-40;j--)
				{
					baitiaobianhang_right_col[j]=0;		//清列白跳变行
				}
				for(j=CAMERA_W-1;j>CAMERA_W-40;j--)   //条件3：上半圆存从右至左存在下降的弧段
				{
					for(i=5;i<CAMERA_H;i++)
					{
						if(img[i][j]==white && img[i+1][j]==black && img[i+2][j]==black 
							&& i>=heitiaobianhang_right[0] && heitiaobianhang_right[0]!=0)
						{
							baitiaobianhang_right_col[j]=i;
							break;
						}
					}
					if(i==CAMERA_H-1)				//该列找不到白跳变点则跳出循环
						break;
				}
				/*if(j<=CAMERA_W-35)
					huandao1flag_right=0;	*/		//存在白跳变行的列数<=45，则不是
/*				shangbanyuancount_right=0;
				shangbanyuancount_right_up=0;
				for(j=CAMERA_W-1;j>CAMERA_W-39;j--)
				{
					if(baitiaobianhang_right_col[j]<baitiaobianhang_right_col[j-1])
						shangbanyuancount_right++;
					if(baitiaobianhang_right_col[j]>baitiaobianhang_right_col[j-1])
						shangbanyuancount_right_up++;
					if(baitiaobianhang_right_col[j]==0)
						break;
				}
				if(shangbanyuancount_right<2)
					huandao1flag_right=0;
				if(shangbanyuancount_right_up>5)
					huandao1flag_right=0;
                                if(left[0]-left[3]>5)
					huandao1flag_right=0;
			}
	//	}
	}	
*/
	//左环岛1判断
//dahuandaonum_left=1;//调试用  
/*        huandao1flag_left=0;
	if(!wuxiaohang_flag && tiaobianflag_left && !tiaobianflag_right
           &&zhidaohuandaoflag && tiaobianhang_left<15  && dahuandaonum_left) 
	{				//条件1：不存在无效行或无效行较高，且右边界无跳变，左边界有跳变	,存在全白一列					
		huandao1flag_left=1;	//条件2：最左列满足有一个白跳变点，两个黑跳变点
	//	for(j=0;j<2;j++)	//从上至下扫黑白跳变点 
	//	{
			heitiaobian=0;														
			baitiaobian=0;
			for(i=0;i<CAMERA_H-1;i++)
			{
				j=0;
				if(img[i][j]==black && img[i+1][j]==white && i>=2 )
                {
					heitiaobianhang_left[heitiaobian]=i;
					heitiaobian++;
				}
				if(img[i][j]==white && img[i+1][j]==black && i>=heitiaobianhang_left[0] && heitiaobianhang_left[0]!=0)
				{
					baitiaobianhang_left[baitiaobian]=i;
					baitiaobian++;
				}
			}
			if(baitiaobian!=1 || heitiaobian!=2  || heitiaobianhang_left[0]>15  || heitiaobianhang_left[0]<2 ||	heitiaobianhang_left[1]<20 
                           || heitiaobianhang_left[1]>=50 || baitiaobianhang_left[0]<5 || baitiaobianhang_left[0]>25)
			{
				huandao1flag_left=0;
				//break;
			}
	//	}
                        if(huandao1flag_left)
                       {
                          for(j=0;j<41;j++)
                          {
				baitiaobianhang_left_col[j]=0;		//清列白跳变行
                          }
                          for(j=0;j<41;j++)               //条件4：上半圆存从左至右存在下降的弧段
			{
				for(i=5;i<CAMERA_H-1;i++)
				{
					if(img[i][j]==white && img[i+1][j]==black && img[i+2][j]==black &&
                                           i>=heitiaobianhang_left[0] && heitiaobianhang_left[0]!=0)
					{
						baitiaobianhang_left_col[j]=i;
						break;
					}
				}
				if(i==CAMERA_H-1)				//该列找不到白跳变点则跳出循环
					break;
			}
                     /*   if(j>=35)
				huandao1flag_left=0;	*/		//存在白跳变行的列数>=35，则不是
/*			shangbanyuancount_left=0;
			shangbanyuancount_left_up=0;
			for(j=0;j<40;j++)
			{
				if(baitiaobianhang_left_col[j]<baitiaobianhang_left_col[j+1])
					shangbanyuancount_left++;
				if(baitiaobianhang_left_col[j]>baitiaobianhang_left_col[j+1])
					shangbanyuancount_left_up++;
				if(baitiaobianhang_left_col[j]==0)
					break;
			}
			if(shangbanyuancount_left<2)
				huandao1flag_left=0;
			if(shangbanyuancount_left_up>5)
				huandao1flag_left=0;
                        if(right[3]-right[0]>5)
                                huandao1flag_left=0;
                      }
	}
 */  
/*
if(huandao1flag_left)  //入环岛1计数值
  ruhuandao1num_left=15;
if(huandao1flag_right)  //入环岛1计数值
  ruhuandao1num_right=15; 
*/
        //循环数组运算：
 /*       nowpoint=(nowpoint+1)%maxsize;
       if(huandao1flag_left||huandao1flag_right||xieruhuandaoflag_right||xieruhuandaoflag_left)
       //   if(huandao1flag_left||huandao1flag_right)
          huandao1[nowpoint]=1;
        else
          huandao1[nowpoint]=0;
        if(nowpoint-vsynnum<0)
          prepoint=maxsize-absint(nowpoint-vsynnum);	
	else
	prepoint=nowpoint-vsynnum;
        while(prepoint!=nowpoint)
        {
          if(huandao1[prepoint]==1)
            huandao1num++;
          prepoint=(prepoint+1)%maxsize;
              
        }
        if(huandao1num>=3)   //10场里出现任意2场环岛1即可
        {
           if(huandao1flag_left) 
            huandaonum1_2_left=20;//左环岛二激活允许时间
           if(huandao1flag_right) 
            huandaonum1_2_right=20;//右环岛二激活允许时间
            if(xieruhuandaoflag_left)
             huandaonum1_2_left=50;//左环岛二激活允许时间
           if(xieruhuandaoflag_right)
             huandaonum1_2_right=50;//左环岛二激活允许时间           
        }
*/
                
//原小环岛环岛2   
        //右环岛2判断
/*       huandao2flag_right=0;
	if((wuxiaohang<=CAMERA_H/15 || !wuxiaohang_flag) && !tiaobianflag_left && tiaobianflag_right && zhidaohuandao2flag && huandaonum1_2_right && tiaobianhang_right<20) 
	{						//条件1：不存在无效行或无效行较高，且左边界无跳变，右边界有跳变,无效行以下存在全白一列
		huandao2flag_right=1;			//条件2：最右列都满足有一个白跳变点，一个黑跳变点
	//	for(j=CAMERA_W-1;j>CAMERA_W-3;j--)      //从上至下扫黑白跳变点
	//	{
			heitiaobian=0;
			baitiaobian=0;
			for(i=0;i<CAMERA_H-1;i++)
			{
				j=CAMERA_W-1;
				if(img[i][j]==black && img[i+1][j]==white && i>=5)
                                {
                                  heitiaobianhang_right[heitiaobian]=i;
                                  heitiaobian++;
                                }
				if(img[i][j]==white && img[i+1][j]==black && i>=heitiaobianhang_right[0] && heitiaobianhang_right[0]!=0)

                                {
                                  baitiaobianhang_right[baitiaobian]=i;
                                  baitiaobian++;
                                }
			}

			if(baitiaobian!=1 || heitiaobian<1 || heitiaobian>2 || (heitiaobian==2 && heitiaobianhang_right[1]<40))
			{
				huandao2flag_right=0;
			//	break;
			}
		//	if(!huandao2flag_right)
		//		break;
	//	}
                        
                        
	}
        
        if(huandao2flag_right)
        {
          huandaonum2_turn_right=100;
        }
        if(huandaonum2_turn_right)
        {
            huandaonum2_turn_right--;         
 //入右环岛
            ruhuandaoflag_right=0;
            tiaobianhang_right_hd=0;
            for(i=50;i>=10;i--)
            {
		if(right[i]-right[i-1]>5)
		{
			tiaobianhang_right_hd=i;
			break;
		}
            }
            if(tiaobianhang_right_hd>=12 && tiaobianhang_right_hd<=25)		//条件1：右边界跳变行满足一定范围
            {  
              ruhuandaoflag_right=1;
               if(ruhuandaoflag_right)						//条件2：环岛左边界列有全白列
               {
                    yuanlie_ruhuandao=0;
					i=10;
                    for(j=left[i]+2;j<CAMERA_W-1;j++)
                    {
                        if(img[i][j]==white && img[i][j+1]==black)
                        {
                            yuanlie_ruhuandao=j;
                            break;
                        }
                    
                    }
                    if(yuanlie_ruhuandao==0)
                      ruhuandaoflag_right=0;
                    else
                    {
                        for(i=12;i<CAMERA_H;i++)
                          if(img[i][yuanlie_ruhuandao-2]==black)
                          {
                              ruhuandaoflag_right=0;
                              break;
                          }
                    }
               }
                if(ruhuandaoflag_right)				//条件3:环岛右边界跳变行以下全白
                {
                    j=CAMERA_W-1;
                    for(i=25;i<CAMERA_H;i++)
                    {
			if(img[i][j]==black)
                        {
                          ruhuandaoflag_right=0;
                          break;
			 }
                    }  
                }
	} 
         if(ruhuandaoflag_right)
         {
                  huandaonum2_turn_right=0;
                  huandaonum1_2_right=0;          //找到转弯点，清计数器
                  rudaonum_right=15;              //转弯延时
                  chudaonum_right=500;
         } 
       }

        
 //出右环岛判断
	chuhuandaoflag_right=0;
	if(visvalMid[standardrow]==initcenter && wuxiaohang>=CAMERA_H/4 && chudaonum_right)
	{                                                       //条件一：当前直走且无效行较低，之前出现过右环岛
		for(i=CAMERA_H-1;i>35;i--)                      //条件二：最底下15行全白
		{
			if(left[i]==0 && right[i]==CAMERA_W-1)
				chuhuandaoflag_right=1;
			else
			{
				chuhuandaoflag_right=0;
				break;
			}
		}
	}

        //每场计数器自减
          if(huandaonum1_2_right)
        {
            huandaonum1_2_right--;
        }
         if(huandaonum2_turn_right)
        {
            huandaonum2_turn_right--;
        }
          if(rudaonum_right)
        {
            rudaonum_right--;
        }
         if(chudaonum_right)
        {
            chudaonum_right--;
        }
        
/******************左环岛*****************/
        //左环岛2判断
/*       huandao2flag_left=0;
	if((wuxiaohang<CAMERA_H/15 || !wuxiaohang_flag) && tiaobianflag_left && !tiaobianflag_right &&zhidaohuandao2flag && huandaonum1_2_left  && tiaobianhang_left<20) 
	{				//条件1：不存在无效行或无效行较高，且右边界无跳变，左边界有跳变,无效行以下存在全白一列
		huandao2flag_left=1;	//条件2：最左列都足有一个白跳变点，一个黑跳变点
	//	for(j=0;j<2;j++)	//从上至下扫黑白跳变点
	//	{
			j=0;
			heitiaobian=0;
			baitiaobian=0;
			for(i=0;i<CAMERA_H-1;i++)
			{
				if(img[i][j]==black && img[i+1][j]==white && i>=5)
                                {
                                  heitiaobianhang_left[heitiaobian]=i;
                                  heitiaobian++;
                                }

				if(img[i][j]==white && img[i+1][j]==black && i>=heitiaobianhang_left[0] && heitiaobianhang_left[0]!=0)
                                {
                                  baitiaobianhang_left[baitiaobian]=i;
                                  baitiaobian++;
                                }
			}
			if(baitiaobian!=1 || heitiaobian<1 || heitiaobian>2 || (heitiaobian==2 && heitiaobianhang_left[1]<40))
			{
				huandao2flag_left=0;
			//	break;
			}
                       
                          
	//	}
	}
        
   if(huandao2flag_left)
        {
          huandaonum2_turn_left=100;
        }
        if(huandaonum2_turn_left)
        {
            huandaonum2_turn_left--;                           
            /*for(i=0;i<CAMERA_H-1;i++)                   //扫最左列黑跳变行
            {
              j=0;
              if(img[i][j]==black && img[i+1][j]==white && img[i+2][j]==white)
              {
                heitiaobianhang_left=i;
                break;
              }
            }*/
            
//入左环岛
/*        ruhuandaoflag_left=0;
        tiaobianhang_left_hd=0; 
	for(i=50;i>=10;i--)
	{
		if(left[i]-left[i-1]<-5)
		{
			tiaobianhang_left_hd=i;
			break;
		}
	}
          if(tiaobianhang_left_hd>=12 && tiaobianhang_left_hd<=25)		//条件1：左边界跳变行满足一定范围
          {  
                ruhuandaoflag_left=1;
               if(ruhuandaoflag_left)										//条件2：环岛左边界列有全白列
               {
                    yuanlie_ruhuandao=0;
                    i=10;
                    for(j=right[i]-2;j>0;j--)
                    {
                        if(img[i][j]==black && img[i][j+1]==white)
                        {
                            yuanlie_ruhuandao=j;
                            break;
                        }
                    }
                    if(yuanlie_ruhuandao==0)
                        ruhuandaoflag_left=0;
                    else
                    {
                        for(i=12;i<CAMERA_H;i++)
                          if(img[i][yuanlie_ruhuandao+2]==black)
                          {
                              ruhuandaoflag_left=0;
                              break;
                          }
                    }
               }
			   if(ruhuandaoflag_left)										//条件3:环岛右边界跳变行以下全白
			   {
				   j=0;
				  for(i=25;i<CAMERA_H;i++)
				 {
					if(img[i][j]==black)
					 {
						 ruhuandaoflag_left=0;
						 break;
					 }
				  }  
              }
            }
               if(ruhuandaoflag_left)
               {
                  huandaonum2_turn_left=0;
                  huandaonum1_2_left=0;            //找到转弯点，清计数器
                  rudaonum_left=15;                //转弯延时
                  chudaonum_left=500;
               
               }
          }

//出左环岛判断
	chuhuandaoflag_left=0;
	if(visvalMid[standardrow]==initcenter && wuxiaohang>=CAMERA_H/4 && chudaonum_left )
	{                                                       //条件一：当前直走且无效行较低，之前出现过左环岛
		for(i=CAMERA_H-1;i>35;i--)                      //条件二：最底下15行全白
		{
			if(left[i]==0 && right[i]==CAMERA_W-1)
				chuhuandaoflag_left=1;
			else
			{
				chuhuandaoflag_left=0;
				break;
			}
		}
	}
       
        //每场计数器自减
          if(huandaonum1_2_left)
        {
            huandaonum1_2_left--;
        }
         if(huandaonum2_turn_left)
        {
            huandaonum2_turn_left--;
        }
          if(rudaonum_left)
        {
            rudaonum_left--;
        }
         if(chudaonum_left)
        {
            chudaonum_left--;
        }
*/        

/***********************************************原大环岛识别************************************************/  //入环岛1
//左大环岛
//dahuandaonum_left=2;//调试
/*dahuandaoflag_left=0;
if(!wuxiaohang_flag && zhidaohuandaoflag && !tiaobianflag_right  && tiaobianflag_left &&(tiaobianhang_left<=2)
&& img[CAMERA_H/2][0]!=white && left[20]<=15  && dahuandaonum_left) 
//大环岛判断：1.无无效行 2.中间几列为白 3.右边连续无跳变 4.左跳变行小于2 5.30行左边界为白 6.20行左边界小于15列 5.6用于规避小环岛
//if(!wuxiaohang_flag && zhidaohuandaoflag && !tiaobianflag_right 
 //&&(tiaobianhang_left<=2) && tiaobianflag_left && dahuandaonum_left) //大环岛判断：1.无无效行 2.中间几列为白 3.右边连续无跳变 4.左跳变行小于2
{
	dahuandaoflag_left=1;
}
if(dahuandaoflag_left)
{
	heitiaobian=0;
	baitiaobian=0;
	j=0;//第0列有一个黑跳变，一个或两个白跳变
	for(i=0;i<CAMERA_H-1;i++)
	{
		if(img[i][j]==black && img[i+1][j]==white)
		heitiaobian++;
		if(img[i][j]==white && img[i+1][j]==black)
		baitiaobian++;
	}
	if(!(baitiaobian==1 && (heitiaobian==1 ||heitiaobian==2)))
	dahuandaoflag_left=0;
}
if(dahuandaoflag_left)//第0行到左边界全黑
{
    if(img[0][left[0]]==white)
        dahuandaoflag_left=0;
}

if(dahuandaoflag_left)
{		
	i=0;
	for(j=0;j<=left[0]-1;j++)
	{
		if(img[i][j]==white)
		{
			dahuandaoflag_left=0;
			break;
		}
	}
}
if(dahuandaoflag_left)
{
	btownum=0;
	for(i=CAMERA_H-1;i>0;i--)  //从下向上找白-黑跳变点 此处不把btownum做计数器，作为行位置
	{
		if(img[i][0]==black && img[i-1][0]==white)
		{
			btownum=i-1;
			break;
		}	
	}
	if(btownum==0)
	  dahuandaoflag_left=0;		
	else
	{
		for(j=0;j<=right[btownum]-1;j++)
		{
			if(img[btownum][j]==black)
			{
				dahuandaoflag_left=0;
				break;
			}	
		}
	}
	if(dahuandaoflag_left)
	{
		btownum--;
		for(j=0;j<=right[btownum]-1;j++)
		{
			if(img[btownum][j]==black)
			{
				dahuandaoflag_left=0;
				break;
			}	
		}
	}
}
//右大环岛
//dahuandaonum_right=2;//调试用
dahuandaoflag_right=0;
if(!wuxiaohang_flag && zhidaohuandaoflag && !tiaobianflag_left 
&& tiaobianflag_right &&(tiaobianhang_right<=2)
&& img[CAMERA_H/2][CAMERA_W-1]!=white && right[20]>=65 && dahuandaonum_right) 
//大环岛判断：1.无无效行 2.中间几列为白 3.左边连续无跳变 4.右跳变行小于2 5.30行边界不为白 6.20行右边界大于65(规避小环岛)
//if(!wuxiaohang_flag && zhidaohuandaoflag && !tiaobianflag_left  && tiaobianflag_right &&(tiaobianhang_right<=2) && dahuandaonum_right) //大环岛判断：1.无无效行 2.中间几列为白 3.左边连续无跳变 4.右跳变行小于2
{
	dahuandaoflag_right=1;
}
if(dahuandaoflag_right)
{
	heitiaobian=0;
	baitiaobian=0;
	j=CAMERA_W-1;//第0列有一个黑跳变，一个或两个白跳变
	for(i=0;i<CAMERA_H-1;i++)
	{
		if(img[i][j]==black && img[i+1][j]==white)
		heitiaobian++;
		if(img[i][j]==white && img[i+1][j]==black)
		baitiaobian++;
	}
	if(!(baitiaobian==1 && (heitiaobian==1 ||heitiaobian==2)))
	dahuandaoflag_left=0;
}
if(dahuandaoflag_right)//第0行右边界线到右边界全黑
{
  if(img[0][right[0]]==white)
    dahuandaoflag_right=0;

}
if(dahuandaoflag_right)
{
		
	i=0;
	for(j=CAMERA_W-1;j>right[i];j--)
	{
		if(img[i][j]==white)
		{
			dahuandaoflag_right=0;
			break;
		}
	}
}

if(dahuandaoflag_right)
{	
	btownum=0;
	for(i=CAMERA_H-1;i>0;i--)  //从下向上找白-黑跳变点 此处不把btownum做计数器，作为行位置
	{
		if(img[i][CAMERA_W-1]==black && img[i-1][CAMERA_W-1]==white)
		{
			btownum=i-1;
			break;
		}	
	}
	if(btownum==0)
	  dahuandaoflag_right=0;		
	else
	{
		for(j=left[btownum]+1;j<CAMERA_W;j++)
		{
			if(img[btownum][j]==black)
			{
				dahuandaoflag_right=0;
				break;
			}	
		}
	}
	if(dahuandaoflag_right)
	{
		btownum--;
		for(j=left[btownum]+1;j<CAMERA_W;j++)
		{
			if(img[btownum][j]==black)
			{
				dahuandaoflag_right=0;
				break;
			}	
		}
	}
}

if(dahuandaoflag_left)  //入环岛1计数值
  ruhuandao1num_left=15;
if(dahuandaoflag_right)  //入环岛1计数值
  ruhuandao1num_right=15;
*/
/************************************************入环岛2********************************************************/
//原入大环岛   && dahuandaonum_right && !ruhuandao1num_right && !ruhuandao1num_left
//入左大环岛
/*rudahuandaoflag_left=0;  
//dahuandaonum_left=1;//////////////////////////////调试用
//if(wuxiaohang<=10 && tiaobianflag_left && lianxuhangnum_right>=40 && dahuandaonum_left)//入左大环岛条件：1.无效行小于10；2.左边跳变; 3.右边连续一定行数
if(wuxiaohang<=10 &&(lianxuhangnum_left>=40 || tiaobianflag_left) && lianxuhangnum_right>=40 && dahuandaonum_left && !rudaonum_left)//入左大环岛条件：1.无效行小于10；2.左边跳变或连续一定行数; 3.右边连续一定行数) 4.入小环岛标志不起效，即优先小环岛
{
	i=40;
        rudahuandaoflag_left=1;
	for(j=0;j<right[i]-1;j++) //中间第40行0到右边界全白
	{
		if(img[i][j]==black)
		{
			rudahuandaoflag_left=0;
			break;
		}
	}
	
}
/**if(rudahuandaoflag_left)
{
	for(i=CAMERA_H/2;i<CAMERA_H;i++)//从第30行开始，第0列与第right[30]列向下为白
	{
		//if(img[i][0]==black || img[i][right[CAMERA_H/2]-1]==black)
                 if(img[i][right[CAMERA_H/2]-1]==black) /////////////////////////////////////////////////
		{
			rudahuandaoflag_left=0;
			break;
		}	
	}
}
**/
/*if(rudahuandaoflag_left)
{
	j=0;
	ruhuandao_shang_i_left=0;
	ruhuandao_shang_j_left=0;
	ruhuandao_xia_i_left=0;
	ruhuandao_xia_j_left=0;
	for(i=CAMERA_H-1;i>0;i--)
	{
		if(img[i][j]==white && img[i-1][j]==black)
		{
			ruhuandao_shang_i_left=i-1;
			ruhuandao_shang_j_left=j;
			ruhuandao_xia_i_left=i-1;
			ruhuandao_xia_j_left=j;
			break;
		}
	}
	if(ruhuandao_shang_i_left==0)
		rudahuandaoflag_left=0;//找不到上补点
	if(rudahuandaoflag_left)
	{
		for(i=ruhuandao_shang_i_left+1;i<CAMERA_H;i++)
		{
			for(j=ruhuandao_xia_j_left;j<=right[i];j++)
			{
				if(img[i][j]==white && img[i][j+1]==black)
				{
					if(j-ruhuandao_xia_j_left<20)
					{
						ruhuandao_xia_i_left=i;
						ruhuandao_xia_j_left=j+1;
						break;
					}
					else
						break;
				}
			}
			if(j-ruhuandao_xia_j_left>=20)
				break;
		}
	}
	if(ruhuandao_xia_i_left-ruhuandao_shang_i_left<=1 || ruhuandao_xia_j_left>=65)//下补点的列数大于于65
		rudahuandaoflag_left=0;
	
}
if(rudahuandaoflag_left) 
{
 // dahuandaonum_left=0;
  rudahuandaonum_left=10;

}



//入右大环岛
rudahuandaoflag_right=0;  
//dahuandaonum_right=1;///////////////////////////////调试
//if(wuxiaohang<=10 && tiaobianflag_right && lianxuhangnum_left>=40 && dahuandaonum_right)//入右大环岛条件：1.无效行小于10行；2.左边连续一定行数; 3.右边跳变
if(wuxiaohang<=10 &&(lianxuhangnum_right>=40 || tiaobianflag_right) && lianxuhangnum_left>=40 && dahuandaonum_right  && !rudaonum_right)//入右大环岛条件：1.无效行小于10行；2.左边连续一定行数; 3.右边跳变或连续一定  4.入小环岛标志生效时不入大环岛
{
	i=40;
        rudahuandaoflag_right=1;
	for(j=left[i]+1;j<CAMERA_W;j++) //中间第35行0到右边界全白
	{
		if(img[i][j]==black)
		{
			rudahuandaoflag_right=0;
			break;
		}
	}
	
}
/***if(rudahuandaoflag_right)
{
	for(i=CAMERA_H/2;i<CAMERA_H;i++)//从第30行开始，第0列与第right[30]列向下为白
	{
		//if(img[i][left[CAMERA_H/2]+1]==black || img[i][CAMERA_W-1]==black)
               if(img[i][left[CAMERA_H/2]+1]==black)
		{
			rudahuandaoflag_right=0;
			break;
		}
	}
}
****/
/*
if(rudahuandaoflag_right )//即是入大环岛的判断条件之一：三角点  也是为补线找下补点
{
	j=CAMERA_W-1;
	ruhuandao_shang_i_right=0;
	ruhuandao_shang_j_right=0;
	ruhuandao_xia_i_right=0;
	ruhuandao_xia_j_right=0;
	for(i=CAMERA_H-1;i>0;i--)
	{
		if(img[i][j]==white && img[i-1][j]==black)
		{
			ruhuandao_shang_i_right=i-1;
			ruhuandao_shang_j_right=j;
			ruhuandao_xia_i_right=i-1;
			ruhuandao_xia_j_right=j;
			break;
		}
	}
	if(ruhuandao_shang_i_right==0)
		rudahuandaoflag_right=0;//找不到上补点
	if(rudahuandaoflag_right)

	{
		for(i=ruhuandao_shang_i_right+1;i<CAMERA_H;i++)
		{
		
			for(j=ruhuandao_xia_j_right;j>=left[i];j--)
			{
				if(img[i][j]==white && img[i][j-1]==black)
				{
					if(ruhuandao_xia_j_right-j<20)
					{
						ruhuandao_xia_i_right=i;
						ruhuandao_xia_j_right=j-1;
						break;
					}
					else
						break;
				}
			}
			if(ruhuandao_xia_j_right-j>=20)
				break;
		}
	}
	if(ruhuandao_xia_i_right-ruhuandao_shang_i_right<=1 || ruhuandao_xia_j_right<=15) //下补点的列数不能小于15列
		rudahuandaoflag_right=0;
	
}

if(rudahuandaoflag_right)  //...........................................
{
 // dahuandaonum_right=0;
  rudahuandaonum_right=10;
}
*/
//新入环岛2算法

//入右环岛1
    //    dahuandaonum_right=2;//调试用
	for(i=0;i<3;i++)
	{
		baitiaobianhang_right[i]=0;
		heitiaobianhang_right[i]=0;
	}
	huandao1flag_right=0;
	if(!wuxiaohang_flag && !tiaobianflag_left && tiaobianflag_right  &&	zhidaohuandaoflag	&& tiaobianhang_right<20 && dahuandaonum_right)
	{										  //条件1：不存在无效行或无效行较高，且左边界无跳变，右边界有跳变,存在全白一列
		huandao1flag_right=1;				  //条件2：最右列满足有一个白跳变点，两个黑跳变点																					
			heitiaobian=0;
			baitiaobian=0;
			for(i=2;i<CAMERA_H-1;i++)
			{
				j=CAMERA_W-1;
				if(img[i][j]==black && img[i+1][j]==white )
				{
					heitiaobianhang_right[heitiaobian]=i;
					heitiaobian++;
				}
				if(img[i][j]==white && img[i+1][j]==black && i>=heitiaobianhang_right[0] && heitiaobianhang_right[0]!=0)
				{
					baitiaobianhang_right[baitiaobian]=i;
					baitiaobian++;
				}
			}
			if(baitiaobian>1 || heitiaobian>2 || heitiaobian<1 || heitiaobianhang_right[0]>25 || (heitiaobian==2 && heitiaobianhang_right[1]<ruhuandaohang_right))
				   //条件3：黑白跳变行满足一定范围
			{
				huandao1flag_right=0;
			}
        }
        if(baitiaobian==1 && baitiaobianhang_right[0]<heitiaobianhang_right[0])
          huandao1flag_right=0;
        if(tiaobianhang_right<heitiaobianhang_right[0]-2)
          huandao1flag_right=0;
        baitiaobian_sum=0;
        if(huandao1flag_right)
	{
              if(baitiaobian)
              {
                  
				   for(j=CAMERA_W-1;j>CAMERA_W-11;j--)
				   {
					   baitiaobianhang_right_hd[j]=0;
					   for(i=5;i<CAMERA_H-1;i++)
					   {
						   if(img[i][j]==white && img[i+1][j]==black)
						   {
							   baitiaobianhang_right_hd[j]=i;
							   break;
						   }
					   }
				   }
				   for(j=CAMERA_W-1;j>CAMERA_W-10;j--)
				   {
					   if(baitiaobianhang_right_hd[j]!=0 && baitiaobianhang_right_hd[j-1]!=0 && baitiaobianhang_right_hd[j]>=baitiaobianhang_right_hd[j-1])
					   {
						   baitiaobian_sum++;
					   }
				   }
                                   if(baitiaobian_sum>3)
                                     huandao1flag_right=0;
              }                                             
	}
        		if(huandao1flag_right)
			{
				j=right[0]-1;
				for(i=1;i<10;i++)
				{
					if(img[i][j]==black)
					{
						huandao1flag_right=0;
						break;
					}
				}
			}
       // if(tiaobianhang_right<4)      
        //太早则修改此参数  huandao1flag_right=0;

//入左环岛1
    //      dahuandaonum_left=2;//调试用
	for(i=0;i<3;i++)
	{
		baitiaobianhang_left[i]=0;
		heitiaobianhang_left[i]=0;
	}
	huandao1flag_left=0;
	if(!wuxiaohang_flag && tiaobianflag_left && !tiaobianflag_right  &&	zhidaohuandaoflag	&& tiaobianhang_left<20 && dahuandaonum_left) 
	{										  //条件1：不存在无效行或无效行较高，且左边界有跳变，右边界无跳变,存在全白一列
		huandao1flag_left=1;				  //条件2：最右列满足有一个白跳变点，两个黑跳变点																					
			heitiaobian=0;
			baitiaobian=0;
			for(i=2;i<CAMERA_H-1;i++)
			{
				j=0;
				if(img[i][j]==black && img[i+1][j]==white)
				{
					heitiaobianhang_left[heitiaobian]=i;
					heitiaobian++;
				}
				if(img[i][j]==white && img[i+1][j]==black && i>=heitiaobianhang_left[0] && heitiaobianhang_left[0]!=0)
				{
					baitiaobianhang_left[baitiaobian]=i;
					baitiaobian++;
				}
			}
			if(baitiaobian>1 || heitiaobian>2 || heitiaobian<1 || heitiaobianhang_left[0]>25 || (heitiaobian==2 && heitiaobianhang_left[1]<ruhuandaohang_left))
				   //条件3：黑白跳变行满足一定范围
			{
				huandao1flag_left=0;
			}
        }
        if(baitiaobian==1 && baitiaobianhang_left[0]<heitiaobianhang_left[0])
          huandao1flag_left=0;
        if(tiaobianhang_left<heitiaobianhang_left[0]-2)
          huandao1flag_left=0;
        baitiaobian_sum=0;
        if(huandao1flag_left)
	{
              if(baitiaobian)
              {
                  
				   for(j=0;j<10;j++)
				   {
					   baitiaobianhang_left_hd[j]=0;
					   for(i=5;i<CAMERA_H-1;i++)
					   {
						   if(img[i][j]==white && img[i+1][j]==black)
						   {
							   baitiaobianhang_left_hd[j]=i;
							   break;
						   }
					   }
				   }
				   for(j=0;j<9;j++)
				   {
					   if(baitiaobianhang_left_hd[j]!=0 && baitiaobianhang_left_hd[j-1]!=0 && baitiaobianhang_left_hd[j]>=baitiaobianhang_left_hd[j+1])
					   {
						   baitiaobian_sum++;
					   }
				   }
                                   if(baitiaobian_sum>3)
                                     huandao1flag_left=0;
              }                                             
	}
        		if(huandao1flag_left)
			{
				j=left[0]+1;
				for(i=1;i<10;i++)
				{
					if(img[i][j]==black)
					{
						huandao1flag_left=0;
						break;
					}
				}
			}
         // if(tiaobianhang_left<4)      
        //太早则修改此参数  huandao1flag_left=0;
        
if(huandao1flag_left)
ruhuandao2num_left=10;
if(huandao1flag_right)
ruhuandao2num_right=10;


/***********补线**************/
/*
if(rudahuandaonum_right) //入右环岛补线******************************  //..................................
{	
	if((img[CAMERA_H-1][CAMERA_W-2]==black)|| (lianxuhangnum_left>=32 && img[48][1]==black))//参考下面入左环岛补线原因
	{
		rudahuandaonum_right=2;
		//indahuandaonum_right=200;
	}
	if(rudahuandaonum_right)
	{
                j=CAMERA_W-1;
                ruhuandao_shang_i_right=0;
                ruhuandao_shang_j_right=0;
                for(i=CAMERA_H-1;i>0;i--)
                {
                      if(img[i][j]==white && img[i-1][j]==black)
                      {
                          ruhuandao_shang_i_right=i-1;
                          ruhuandao_shang_j_right=CAMERA_W-1;
                          break;
                      }
                }
                k_ruhuandao=(float)((left[CAMERA_H-1]-ruhuandao_shang_j_right)/(CAMERA_H-1-ruhuandao_shang_i_right));
		for(i=28;i<=48;i++)
		{
                      if(k_ruhuandao*(i-ruhuandao_shang_i_right)+ruhuandao_shang_j_right<=0)
                      left[i]=0;
                      else if(k_ruhuandao*(i-ruhuandao_shang_i_right)+ruhuandao_shang_j_right>CAMERA_W-1)
                      left[i]=CAMERA_W-1;
                      else left[i]=(int)(k_ruhuandao*(i-ruhuandao_shang_i_right))+ruhuandao_shang_j_right;
                      right[i]=CAMERA_W-1;
            //	img[i][left[i]]=100;
                      visvalMid[i]=(left[i]+right[i])/2+4;
                      img[i][visvalMid[i]]=100;
		}	
	}	
}
if(rudahuandaonum_left) //入左环岛补线
{	
	if((img[CAMERA_H-1][2]==black)|| (lianxuhangnum_right>=32 && img[48][CAMERA_W-2]==black))	//在环岛中标志：即不再进行入环岛补线：	
	{
		rudahuandaonum_left=2;//让在环岛计数开始																			//1.左边出现黑，补过头了，该进入环岛了
		//indahuandaonum_left=200;  														//2.右边连续行大于32行了，而且右边48为黑了，即不用再补了（需验证，可能会补线不够）
	}																									//上面的2能右边48为黑则进入环岛与下面出环岛的48为白对应，避免入环岛时识别到出环岛
	if(rudahuandaonum_left)
	{																								
                j=0;
                ruhuandao_shang_i_left=0;
                ruhuandao_shang_j_left=0;
                for(i=CAMERA_H-1;i>0;i--)
                {       
                      if(img[i][j]==white && img[i-1][j]==black)
                      {
			ruhuandao_shang_i_left=i-1;
			ruhuandao_shang_j_left=0;
			break;
                      }
                 }
                k_ruhuandao=(float)((right[CAMERA_H-1]-ruhuandao_shang_j_left)/(CAMERA_H-1-ruhuandao_shang_i_left));	
                // k_ruhuandao=(float)((right[CAMERA_H-1]-ruhuandao_xia_j)/(CAMERA_H-1-ruhuandao_xia_i));
		for(i=28;i<=48;i++)
		{
			if(k_ruhuandao*(i-ruhuandao_shang_i_left)+ruhuandao_shang_j_left<=0)
				right[i]=0;
			else if(k_ruhuandao*(i-ruhuandao_shang_i_left)+ruhuandao_shang_j_left>CAMERA_W-1)
				right[i]=CAMERA_W-1;
			else right[i]=(int)(k_ruhuandao*(i-ruhuandao_shang_i_left))+ruhuandao_shang_j_left;
			left[i]=0;
		//	img[i][right[i]]=100;
			visvalMid[i]=(left[i]+right[i])/2-4;
			img[i][visvalMid[i]]=100;
		}	
	}
}
*/

/********************出大环岛*******************/ 
nearchudahuandaoflag_left=0;
nearchudahuandaoflag_right=0;
//indahuandaonum_left=1;/////调试用
//indahuandaonum_right=1;/////调试用
//靠近出左大环岛
if(indahuandaonum_left && lianxuhangnum_right<=50 && (indahuandaonum_left<=190) )  //小于28也可以
{
	nearchudahuandaoflag_left=1;
	j=0;
	for(i=CAMERA_H/2;i<CAMERA_H;i++) //左边界第30行到底行为白
	{
		if(img[i][j]==black)
		{
			nearchudahuandaoflag_left=0;
			break;
		}
	}
	if(nearchudahuandaoflag_left)
	{
		btownum=0;  //从60到23行存在黑到白的1个跳变点
		for(i=CAMERA_H-1;i>=3;i--)
		{
			if(img[i][CAMERA_W-1]==black && img[i-1][CAMERA_W-1]==white)
				btownum++;
		}		
		if(btownum!=1)
			nearchudahuandaoflag_left=0;
	}
}

//靠近出右大环岛
if(indahuandaonum_right && lianxuhangnum_left<=50 && (indahuandaonum_right<=190))
{
	nearchudahuandaoflag_right=1;
	j=CAMERA_W-1;
	for(i=CAMERA_H/2;i<CAMERA_H;i++) //左边界第30行到底行为白
	{
		if(img[i][j]==black)
		{
			nearchudahuandaoflag_right=0;
			break;
		}
	}
	if(nearchudahuandaoflag_right)
	{
		btownum=0;  //从60到23行存在黑到白的1个跳变点
		for(i=CAMERA_H-1;i>=3;i--)
		{
			if(img[i][0]==black && img[i-1][0]==white)
				btownum++;
		}		
		if(btownum!=1)
			nearchudahuandaoflag_right=0;
	}
}
/*if(nearchudahuandaoflag_left)
  chudahuandaonum_left=50;
if(nearchudahuandaoflag_right)
   chudahuandaonum_right=50;
*/
//出大环岛
chudahuandaoflag_left=0;
chudahuandaoflag_right=0;
//出左大环岛
if(indahuandaonum_left && img[48][0]==white && img[48][CAMERA_W-1]==white && (indahuandaonum_left<=190) && wuxiaohang_flag)
{
	chudahuandaoflag_left=1;
	i=35;
	for(j=0;j<CAMERA_W;j++) //35行和底行全白
	{
		if(img[i][j]==black || img[CAMERA_H-1][j]==black)
		{
			chudahuandaoflag_left=0;
			break;
		}
	}
	if(chudahuandaoflag_left)
	{
		j=CAMERA_W-1;
		for(i=48;i<CAMERA_H;i++)  //右边界48-60行为白
		{
			if(img[i][j]==black)
			{
				chudahuandaoflag_left=0;
				break;
			}
		}
	}
	if(chudahuandaoflag_left)
	{
		j=0;
		for(i=CAMERA_H/2;i<CAMERA_H;i++) //左边界30-60行为白
		{
			if(img[i][j]==black)
			{
				chudahuandaoflag_left=0;
				break;
			}
		}
	}
	if(chudahuandaoflag_left)
	{
		chudaodian_left_i=0;
		chudaodian_right_i=0;
		j=0;
		for(i=CAMERA_H-1;i>0;i--)
		{
			if(img[i][j]==white && img[i-1][j]==black)
			{
				chudaodian_left_i=i-1;
				break;
			}
		}
		j=CAMERA_W-1;
		for(i=CAMERA_H-1;i>0;i--)
		{
			if(img[i][j]==white && img[i-1][j]==black)
			{
				chudaodian_right_i=i-1;
				break;
			}
		}
		if(chudaodian_right_i-chudaodian_left_i>=5 && chudaodian_right_i-chudaodian_left_i<=10 )
			chudahuandaoflag_left=1;
		else if(chudaodian_right_i-chudaodian_left_i>=1 && chudaodian_right_i-chudaodian_left_i<=10 )
			nearchudahuandaoflag_left=1; 
                if(chudahuandaoflag_left)
                {
                     for(i=chudaodian_left_i;i<=chudaodian_right_i;i++)
                    {
                        if(img[i-1][right[i]]==white)
                        {
                             chudahuandaoflag_left=0;
                             break;
                        }
                    }
                
                }

	}
}

//出右大环岛
//nearchudahuandaoflag_right=0;//
if(indahuandaonum_right && img[48][0]==white && img[48][CAMERA_W-1]==white && (indahuandaonum_right<=190) && wuxiaohang_flag)
{ 
	chudahuandaoflag_right=1;
	i=35;
	for(j=0;j<CAMERA_W;j++) //35行和底行全白
	{
		if(img[i][j]==black || img[CAMERA_H-1][j]==black)
		{
			chudahuandaoflag_right=0;
			break;
		}
	}
	if(chudahuandaoflag_right)
	{
		j=CAMERA_W-1;
		for(i=CAMERA_H/2;i<CAMERA_H;i++)  //右边界30-60行为白
		{
			if(img[i][j]==black)
			{
				chudahuandaoflag_right=0;
				break;
			}
		}
	}
	if(chudahuandaoflag_right)
	{
		j=0;
		for(i=48;i<CAMERA_H;i++) //左边界48-60行为白
		{
			if(img[i][j]==black)
			{
				chudahuandaoflag_right=0;
				break;
			}
		}
	}
	if(chudahuandaoflag_right)
	{
		chudaodian_left_i=0;
		chudaodian_right_i=0;
		j=0;
		for(i=CAMERA_H-1;i>0;i--)
		{
			if(img[i][j]==white && img[i-1][j]==black)
			{
				chudaodian_left_i=i-1;
				break;
			}
		}
		j=CAMERA_W-1;
		for(i=CAMERA_H-1;i>0;i--)
		{
			if(img[i][j]==white && img[i-1][j]==black)
			{
				chudaodian_right_i=i-1;
				break;
			}
		}
		if(chudaodian_left_i-chudaodian_right_i>=5 && chudaodian_left_i-chudaodian_right_i<=10 )
			chudahuandaoflag_right=1;
		else if(chudaodian_left_i-chudaodian_right_i>=1  && chudaodian_left_i-chudaodian_right_i<=10 )
			nearchudahuandaoflag_right=1; 
                if(chudahuandaoflag_right)
                {
                     for(i=chudaodian_right_i;i<=chudaodian_left_i;i++)
                    {
                        if(img[i-1][left[i]]==white)
                        {
                             chudahuandaoflag_right=0;
                             break;
                        }
                    }
                
                }
	}
}

/********************小环岛出环岛*************************/
//chudaonum_left=1;//调试
//出左环岛判断
	chuhuandaoflag_left=0;
	if(visvalMid[38]==initcenter && wuxiaohang>=CAMERA_H/4 && chudaonum_left )
	{                                                       //条件一：当前直走且无效行较低，之前出现过左环岛
		for(i=CAMERA_H-1;i>35;i--)                      //条件二：最底下15行全白
		{
			if(left[i]==0 && right[i]==CAMERA_W-1)
				chuhuandaoflag_left=1;
			else
			{
				chuhuandaoflag_left=0;
				break;
			}
		}
	}
//chudaonum_right=1;//调试
 //出右环岛判断
	chuhuandaoflag_right=0;
	if(visvalMid[38]==initcenter && wuxiaohang>=CAMERA_H/4 && chudaonum_right)
	{                                                       //条件一：当前直走且无效行较低，之前出现过右环岛
		for(i=CAMERA_H-1;i>35;i--)                      //条件二：最底下15行全白
		{
			if(left[i]==0 && right[i]==CAMERA_W-1)
				chuhuandaoflag_right=1;
			else
			{
				chuhuandaoflag_right=0;
				break;
			}
		}
	}
/******************出环岛补线*************************/
/***
if(((nearchudahuandaoflag_left || nearchudahuandaoflag_right) && indahuandaonum_left) || ((chudahuandaoflag_left || chudahuandaoflag_right) && indahuandaonum_right))
{
	if(nearchudahuandaoflag_left || chudahuandaoflag_left)
	{
		chudaodian_left_i=0;
		for(i=CAMERA_H-1;i>0;i--)
		{
			if(img[i][0]==white && img[i-1][0]==black)
			{
				chudaodian_left_i=i-1;
				break;
			}
		}
		k_ruhuandao=(float)((right[CAMERA_H-1]-0)/(CAMERA_H-1-chudaodian_left_i));	
		for(i=28;i<=48;i++)
		{
			if(k_ruhuandao*(i-CAMERA_H+1)+right[CAMERA_H-1]<=0)
				right[i]=0;
			else if(k_ruhuandao*(i-CAMERA_H+1)+right[CAMERA_H-1]>CAMERA_W-1)
				right[i]=CAMERA_W-1;
			else right[i]=(int)(k_ruhuandao*(i-CAMERA_H+1))+right[CAMERA_H-1];
			left[i]=0;
		//	img[i][right[i]]=100;
			visvalMid[i]=(left[i]+right[i])/2;
			img[i][visvalMid[i]]=100;
		}
	}
	else if(nearchudahuandaoflag_right || chudahuandaoflag_right)
	{
		chudaodian_right_i=0;
		for(i=CAMERA_H-1;i>0;i--)
		{
			if(img[i][CAMERA_W-1]==white && img[i-1][CAMERA_W-1]==black)
			{
				chudaodian_right_i=i-1;
				break;
			}
		}
		k_ruhuandao=(float)((left[CAMERA_H-1]-CAMERA_W+1)/(CAMERA_H-1-chudaodian_right_i));	
		for(i=28;i<=48;i++)
		{
			if(k_ruhuandao*(i-CAMERA_H+1)+left[CAMERA_H-1]<=0)
			left[i]=0;
			else if(k_ruhuandao*(i-CAMERA_H+1)+left[CAMERA_H-1]>CAMERA_W-1)
			left[i]=CAMERA_W-1;
			else left[i]=(int)k_ruhuandao*(i-CAMERA_H+1)+left[CAMERA_H-1];
			right[i]=CAMERA_W-1;
		//	img[i][left[i]]=100;
			visvalMid[i]=(left[i]+right[i])/2;
			img[i][visvalMid[i]]=100;
		}
	}
}
*/

/******************入环岛前找中点****************************/
//右环岛找点                                                            //改第0行中点
hang20_mid=0;
hang20_mid_hang=i;
if(dahuandaonum_right && !tiaobianflag_left)
{
	j=CAMERA_W-1;//倒数第2列识别，避免噪点
	wtobhang=0;
	for(i=CAMERA_H-1;i>2;i--)
	{
		if(img[i][j]==white && img[i-1][j]==black)
		{
			wtobhang=i-1;
			break;		
		}	
	}	
	if(wtobhang==0) //避免扫不到
		wtobhang=CAMERA_H-1;
	for(i=wtobhang;i>0;i--)
		if(right[i-1]>right[i])
			break; 
	for(j=left[i];j<CAMERA_W-1;j++)//重提中点
	{
		if(img[i][j]==white && img[i][j+1]==black)
				break;
	}
	hang20_mid=(left[i]+j+1)/2;
        hang20_mid_hang=i;
}

//左环岛找点
if(dahuandaonum_left  && !tiaobianflag_right)
{
	j=0;//第3列识别，避免噪点
	wtobhang=0;

	for(i=CAMERA_H-1;i>2;i--)
	{
		if(img[i][j]==white && img[i-1][j]==black)
		{
			wtobhang=i;
			break;		
		}	
	}	
	if(wtobhang==0) //避免扫不到
		wtobhang=CAMERA_H-1;
	for(i=wtobhang;i>0;i--)
                if(left[i-1]<left[i])
                    break; 
	for(j=right[i];j>0;j--)//重提中点
	{
		if(img[i][j]==white && img[i][j-1]==black)
				break;		
	}	
	hang20_mid=(right[i]+j-1)/2;
        hang20_mid_hang=i;
}




/******************计数值处理***********************/
if(ruhuandao1num_left==1 || ruhuandao2num_left==1 )
{
indahuandaonum_left=200;
chudaonum_left=250;//出去不清
}

if(ruhuandao1num_right==1 || ruhuandao2num_right==1)
{
indahuandaonum_right=200;
chudaonum_right=250;//出去不清
}

if(chudahuandaoflag_left)
{
    indahuandaonum_left=0;
  // chudahuandaonum_left=0; //
    nohuandaonum=100;
}
if(chudahuandaoflag_right)
{
   indahuandaonum_right=0; 
  //  chudahuandaonum_right=0; //
    nohuandaonum=100;    //出环岛后一段时间屏蔽环岛判断
}

if(dahuandaonum_left)
  dahuandaonum_left--;
if(dahuandaonum_right)
  dahuandaonum_right--;

if(ruhuandao1num_right)  //////////////////
ruhuandao1num_right--;
if(ruhuandao1num_left)
ruhuandao1num_left--;

if(ruhuandao2num_right)
ruhuandao2num_right--;
if(ruhuandao2num_left)
ruhuandao2num_left--;

if(ruhuandao1num_right || ruhuandao2num_right)  //入环岛时请环岛计数
dahuandaonum_right=0;
if(ruhuandao1num_left || ruhuandao2num_left)
dahuandaonum_left=0;

if(indahuandaonum_right)
indahuandaonum_right--;
if(indahuandaonum_left)
indahuandaonum_left--;   

if(chudahuandaonum_left)
chudahuandaonum_left--;
if(chudahuandaonum_right)
chudahuandaonum_right--;

if(chudaonum_left)
chudaonum_left--;
if(chudaonum_right)
chudaonum_right--;

if(nohuandaonum)
nohuandaonum--;
        
        
}
