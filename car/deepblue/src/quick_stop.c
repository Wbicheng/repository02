#include "common.h"
#include "include.h"
#include "quick_stop.h" 

uint8 btow_i=0;//黑到白跳变行数
uint8 pre_btow_i=0;//上一行黑到白跳变行数 用于条件四
uint8 quickstop_flag=0;//急停标志位
uint8 allow_quickstop_flag=0;//允许急停标志位
uint8 left_limit_flag=0;//左边极限为白
uint8 right_limit_flag=0;//右边极限为白

void quick_stop()
{
    if(wuxiaohang<=30 && lianxuhangnum_right>18)//条件一：无效行小于20,右边从底向上连续行数大于18///////////
    {
	quickstop_flag=0;//急停标志位
	btownum=0;//黑到白行跳变数
	btow_i=0;//黑到白跳变行数
	pre_btow_i=0;//上一行黑到白跳变行数 用于条件四
	if(left[CAMERA_H-2]-10>=0)//避开底行，底行中线不准
		j=left[CAMERA_H-2]-10;
	else j=0;
	for(i=CAMERA_H-1;i!=20;i--) //20行内不取避免远景与畸变直道干扰
	{
		if(img[i][j]==black &&img[i-1][j]==white)
		{
			if(btow_i==0 && i<45)//控制第一个跳变的位置大于45
			{
				break;
			}
			if(btow_i!=0)
			  pre_btow_i=btow_i;	
			btow_i=i;
			if(pre_btow_i!=0 && pre_btow_i-btow_i>10) //两杠之间距离小于10////////
			{
				quickstop_flag=0;
				break;
			}
			btownum++;		
		}	
	}
	if(btownum==3 || btownum==4) //条件二：左边存在3到4个黑到白跳变行
		quickstop_flag=1;
    }
    if(quickstop_flag) //条件三：第3个黑白跳变行附近存在左右极限边界
    {
	left_limit_flag=0;
	right_limit_flag=0;
	for(i=btow_i-8;i!=btow_i+8;i++)
	{
		if(img[i][0]==white)
			left_limit_flag=1;
		if(img[i][CAMERA_W-1]==white)
			right_limit_flag=1;
		if(left_limit_flag && right_limit_flag)
			break;
	}
	if(!left_limit_flag || !right_limit_flag)
		quickstop_flag=0;

    }
 
    if(quickstop_flag) //条件四：右下为黑 第三杠右边界到CAMERA_W-1全黑
    {
        for(j=right[pre_btow_i]+1;j!=CAMERA_W;j++)
        {
   	   if(img[pre_btow_i][j]==white)
	   {
	       quickstop_flag=0;
		   break;
	   }
          }

    }
/*    if(quickstop_flag)//条件五：右边界只有一个黑to白跳变
    {               
	btownum=0;
	j=CAMERA_W-1;
	for(i=CAMERA_H-1;i!=30;i--)
	{
		if(img[i][j]==black &&img[i-1][j]==white)
			btownum++;
		if(btownum==2)
		{
			quickstop_flag=0;
			break;
		}
	}
	if(btownum!=1)
		quickstop_flag=0;
    }
    if(quickstop_flag) 
      allow_quickstop_flag=1;
   */
}