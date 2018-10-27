#include "common.h"
#include "include.h"
#include "wd_zd.h" 

uint8 zuotiaobian_left;		//左边界左跳变数
uint8 zuotiaobian_right;	//左边界右跳变数
uint8 youtiaobian_left;		//右边界左跳变数
uint8 youtiaobian_right;	//右边界右跳变数
uint8 youtiaobianhang_left[10];		//右边界左跳变行
uint8 wdflag;
uint8 endflag;
uint8 blackpoint_zd;			//终点行黑点数

void wd_zd()
{
 /***********************弯道********************/
zuotiaobian_left=0;
zuotiaobian_right=0;
youtiaobian_left=0;
youtiaobian_right=0;
wdflag=0;
for(i=55;i>20;i--)
{
	if(left[i]-left[i-1]>11)
	{
		zuotiaobian_left++;
	}
	if(left[i-1]-left[i]>11)
	{
		zuotiaobian_right++;
	}
	if(right[i]-right[i-1]>11)
	{
		youtiaobian_left++;
	}
	if(right[i-1]-right[i]>11	)
	{
		youtiaobian_right++;
	}
}
if(zuotiaobian_left>=2 && zuotiaobian_right>=2 && youtiaobian_right==0 && youtiaobian_left==0)
{
	if(visvalMid[10]<20)
	{
		wdflag=1;
	}
}

/**************************终点线************************/
endflag=0;
if(zuotiaobian_left>=2 && zuotiaobian_right>=2 && youtiaobian_right>=2 && youtiaobian_left>=2)
{
	endflag=1;
}
/*if(endflag)
{
	for(i=0;i<2;i++)
	{
		if(right[youtiaobianhang_left[i]+2]<CAMERA_W-5)
		{
			endflag=0;
		}
	}
}
*/
blackpoint_zd=0;
if(endflag)
{
	i=43;
	for(j=10;j<CAMERA_W-10;j++)
	{
		if(img[i][j]==black)
		{
			blackpoint_zd++;
		}
	}
	if(blackpoint_zd>=3)
		endflag=0;
}

}