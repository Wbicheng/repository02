#include "common.h"
#include "include.h"
#include "jiwan.h"

int startrow;
uint8 youwanflag=0;
uint8 zuowanflag=0;
uint8 maybeyouwanflag;
uint8 maybezuowanflag;
uint8 swanflag_left;
uint8 swanflag_right;
uint8 jiwanflag;
uint8 blackpoint;
int8 error_zuowan;		        //左弯矫正偏差
int8 error_youwan;		        //右弯矫正偏差
int8 Center_zuowan[CAMERA_H]={0};       //左弯中线
int8 Center_youwan[CAMERA_H]={0};       //右弯中线
uint8 sum_left_left;                    //左边界向左点数
uint8 sum_left_right;                   //左边界向右点数
uint8 sum_right_left;                   //右边界向左点数
uint8 sum_right_right;                  //右边界向右点数
uint8 maynotswanflag_left;
uint8 maynotswanflag_right;
uint8 swanflag;

void jiwan()
{
  /***********************s弯*******************/
sum_left_left=0;
sum_left_right=0;
sum_right_left=0;
sum_right_right=0;
maynotswanflag_right=0;
maynotswanflag_left=0;
swanflag=0;
//if(wuxiaohang<6)
//{
	for(i=0;i<CAMERA_H-1;i++)
	{
		if(left[i+1]<left[i])
		{
			sum_left_left++;
		}
		if(left[i+1]>left[i])
		{
			sum_left_right++;
		}
		if(right[i+1]>right[i])
		{
			sum_right_right++;
		}
		if(right[i+1]<right[i])
		{
			sum_right_left++;
		}
		if(left[i]>=60)
			maynotswanflag_right=1;
		if(right[i]<20)
			maynotswanflag_left=1;
	}
        if(sum_left_right>=7 || sum_right_left>=7)
            zhidaoflag=0;
	if(sum_left_left>10 && sum_left_right>10 && !maynotswanflag_right)
		swanflag=1;
	if(sum_right_left>10 && sum_right_right>10 && !maynotswanflag_left)
		swanflag=1;
        if(tiaobianhang_left>=5 || tiaobianhang_right>=5)
		swanflag=0;
//}
/***********************弯道********************/
  jiwanflag=0;
  blackpoint=0;
  youwanflag=0;
  zuowanflag=0;
  maybezuowanflag=1;
  maybeyouwanflag=1;
  swanflag_left=0;
  swanflag_right=0;
if(tiaobianhang_left>10 || tiaobianhang_right>10)
{
	maybezuowanflag=0;
	maybeyouwanflag=0;
}
if(maybezuowanflag)
for(i=30;i<CAMERA_H;i++)
{
	j=0;
	if(img[i][j]==black)
	{
		maybezuowanflag=0;
		break;
	}
}
if(maybeyouwanflag)
for(i=30;i<CAMERA_H;i++)
{
	j=CAMERA_W-1;
	if(img[i][j]==black)
	{
		maybeyouwanflag=0;
		break;
	}
}
swanflag_left=0;
if(maybezuowanflag)
{
	if(sum_right_left>=10 && sum_right_right>=10)
	swanflag_left=1;
}
swanflag_right=0;
if(maybeyouwanflag)
{
	if(sum_left_left>=10 && sum_left_right>=10)
	swanflag_right=1;
}
if(wuxiaohang>=6)
  {
	if(wuxiaohang>=6)
	{
		if(wuxiaohang+15>CAMERA_H)
		{
			startrow=CAMERA_H-3;
		}
		else
			startrow=wuxiaohang+15;
	}
	if(wuxiaohang_flag<6 && (maybezuowanflag || maybeyouwanflag))
		startrow=40;
/***************右弯******************/
	if(wuxiaohang_flag && left[wuxiaohang+1]>initcenter)                      
	{
		youwanflag=1;
		for(i=CAMERA_H-1;i>startrow;i--)       //下到上  靠右
		{
			if(img[i][CAMERA_W-5]==0)
			{
				youwanflag=0;
				break;
			}
		}
		for(j=CAMERA_W-1;j>left[startrow]+2;j--) // 右到左
		{
			if(img[startrow][j]==0)
			{
				youwanflag=0;
				break;
			}
		}
	        for(i=CAMERA_H-1;i>startrow;i--)         //下到上  靠左
		{
			if(img[i][left[startrow]+2]==0)
			{
				youwanflag=0;
				break;
			}
		}
                /*
                for(j=left[startrow]-2;j>2;j--) // 右到左 靠左 扫黑
		{
			if(img[startrow][j]==white)
			{
				youwanflag=0;
				break;
			}
		}
	        for(i=startrow;i>(startrow+wuxiaohang)/2;i--)         //下到上  靠左  扫黑
		{
			if(img[i][left[startrow]]==white)
			{
				youwanflag=0;
				break;
			}
		}*/
	}
 	if(youwanflag)
	{
		if(wuxiaohang_flag)
			error_youwan=visvalMid[CAMERA_H-1]-left[CAMERA_H-1];
	/*	else
			error_youwan=visvalMid[CAMERA_H-1]-left[CAMERA_H-1]-10;*/
		for(i=CAMERA_H-2;i>wuxiaohang+1;i--)
		{
			if(left[i]+error_youwan>CAMERA_W-1)
				Center_youwan[i]=CAMERA_W-1;
			else
				Center_youwan[i]=left[i]+error_youwan;
			//visvalMid[i]=Center_youwan[i];
			img[i][visvalMid[i]]=red;
		}
	}
/***************左弯******************/
    else if(wuxiaohang_flag && right[wuxiaohang+1]<initcenter)
	{
		zuowanflag=1;
		for(i=CAMERA_H-1;i>startrow;i--)       //下到上  靠左
		{
			if(img[i][5]==0)
			{
				zuowanflag=0;
				break;
			}
		}
		for(j=10;j<right[startrow]-1;j++) // 左到右
		{
			if(img[startrow][j]==0)
			{
				zuowanflag=0;
				break;
			}
		}
	        for(i=CAMERA_H-1;i>startrow;i--)         //下到上  靠右
		{
			if(img[i][right[startrow]-1]==0)
			{
				zuowanflag=0;
				break;
			}
		}
              /*  for(j=right[startrow]+2;j<CAMERA_W-2;j++) // 左到右 靠左 扫黑
		{
			if(img[startrow][j]==white)
			{
				zuowanflag=0;
				break;
			}
		}
		for(i=startrow;i>(startrow+wuxiaohang)/2;i--)         //下到上  靠右 扫黑
		{
			if(img[i][right[startrow]]==white)
			{
				zuowanflag=0;
				break;
			}
		}*/
	} 
  }
	if(zuowanflag)
	{
		if(wuxiaohang_flag)
			error_zuowan=right[CAMERA_H-1]-visvalMid[CAMERA_H-1];
	/*	else
			error_zuowan=right[CAMERA_H-1]-visvalMid[CAMERA_H-1]-10;*/
		for(i=CAMERA_H-2;i>wuxiaohang+1;i--)
		{
			if(right[i]-error_zuowan<0)
				Center_zuowan[i]=0;
			else
				Center_zuowan[i]=right[i]-error_zuowan;
			//visvalMid[i]=Center_zuowan[i];
			img[i][visvalMid[i]]=red;
		}
	}
   
  /*****************急弯判断***********************/
/*if(wuxiaohang>=20)
{
     if(zuowanflag)
     {
         for(i=0;i<CAMERA_H;i++)
         {
            visvalMid[i]=0;
         
         }
          
     }
     if(youwanflag)
     {
          for(i=0;i<CAMERA_H;i++)
          {
            visvalMid[i]=CAMERA_W-1;
          }
     }
    
  }*/

}