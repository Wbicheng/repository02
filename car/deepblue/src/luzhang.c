#include "common.h"
#include "include.h"
#include "luzhang.h"

uint8 heitiaobian_lz[CAMERA_H];		//路障黑跳变点
uint8 baitiaobian_lz[CAMERA_H];		//路障白跳变点
int8 heitiaobian_row_lz[2];		//路障黑跳变行
int8 baitiaobian_row_lz;		//路障白跳变行
uint8 luzhangflag_left;		        //左路障检测标志
uint8 luzhangflag_right;		//右路障检测标志
uint8 startcol_lz;                      //路障开始列
int8 blacksum_lz[CAMERA_H];	        //路障黑点数
int16 right_lz[CAMERA_H];		//右路障边界
int16 left_lz[CAMERA_H];	         //左路障边界
uint8 startrow_lz;                      //路障提线开始行
uint8 endrow_lz;                        //路障提线结束行
float K_lz;                            //路障提线斜率
uint8 lzflag_right=0;                   //右路障中标志
uint8 lzflag_left=0;                    //左路障中标志
uint8 delaynum_lz_right=0;                //右路障结束场计数器
uint8 delaynum_lz_left=0;                 //左路障结束场计数器
uint8 clearflag_lz_right;               //清右路障标志
uint8 clearflag_lz_left;              //清左路障标志
uint8 clearnum_lz_right=0;               //清右路障计数
uint8 clearnum_lz_left=0;              //清左路障计数
uint8 cleardelay_lz_right=0;               //清右路障延时计数
uint8 cleardelay_lz_left=0;              //清左路障延时计数
uint8 center_lz;                         //路障中心
uint8 tiaobianhang_left_lz;
uint8 tiaobianhang_right_lz;

void luzhang()
{
  luzhangflag_left=1;
  luzhangflag_right=1;
  startrow_lz=0;
  endrow_lz=0;
  K_lz=0;
//远右路障
baitiaobian_row_lz=0;
heitiaobian_row_lz[0]=0;
heitiaobian_row_lz[1]=0;
startcol_lz=0;
if(sum_right_left>=5)
{
  luzhangflag_right=0;
}
for(j=left[3];j<right[3];j++)
{
	for(i=3;i<40;i++)
	{
		if(img[i][j]==white && img[i][j+1]==black)
		{
			startcol_lz=j;
			break;
		}
	}
	if(startcol_lz!=0)
	{
		break;
	}
}
if(startcol_lz<=10)
{
	luzhangflag_right=0;
}
if(right[3]-left[3]>40)
{
	luzhangflag_right=0;
}
for(i=3;i<40;i++)
{
	if(img[i][startcol_lz+5]==white && img[i+1][startcol_lz+5]==black)
	{
		baitiaobian_row_lz=i;
		break;
	}
}
for(i=40;i>10;i--)
{
	if(img[i][startcol_lz+5]==black && img[i+1][startcol_lz+5]==white)
	{
		heitiaobian_row_lz[0]=i+1;
		break;
	}
}
for(i=40;i>10;i--)
{
	if(img[i][startcol_lz+10]==black && img[i+1][startcol_lz+10]==white)
	{
		heitiaobian_row_lz[1]=i+1;
		break;
	}
}
if(heitiaobian_row_lz[0]-baitiaobian_row_lz<=8 || baitiaobian_row_lz==0)
{
	luzhangflag_right=0;
}
if(heitiaobian_row_lz[1]-heitiaobian_row_lz[0]>1 || heitiaobian_row_lz[1]-heitiaobian_row_lz[0]<-1)
{
	luzhangflag_right=0;
}
if(luzhangflag_right)
{
  for(i=heitiaobian_row_lz[0]+1;i<=heitiaobian_row_lz[0]+3;i++)
  {
    if(right[i]-left[i]>=width[i]+5)
    {
      luzhangflag_right=0;
      break;
    }
  }
}
if(luzhangflag_right)
{
	for(i=0;i<30;i++)
	{
          for(j=startcol_lz-1;j>=startcol_lz-5;j--)
          {
		if(img[i][j]==black)
		{
			luzhangflag_right=0;
			break;
		}
          }
          if(luzhangflag_right==0)
            break;
	}
}
if(luzhangflag_right)
{
	for(i=baitiaobian_row_lz+1;i<heitiaobian_row_lz[0];i++)
	{
		if(img[i][startcol_lz+10]==white)
		{
			luzhangflag_right=0;
			break;
		}
	}
}
if(luzhangflag_right)
{
	for(j=startcol_lz+10;j<=startcol_lz-5;j--)
	{
		if(img[heitiaobian_row_lz[1]+2][j]==black)
		{
			luzhangflag_right=0;
			break;
		}
	}
}
if(luzhangflag_right)
{
	for(i=baitiaobian_row_lz;i<heitiaobian_row_lz[0];i++)
	{
		if(img[i][startcol_lz-5]==black)
		{
			luzhangflag_right=0;
			break;
		}
	}
}
//近右路障
if(luzhangflag_right==0)
{
for(i=30;i<35;i++)
{
	baitiaobian_lz[i]=0;
	heitiaobian_lz[i]=0;
	blacksum_lz[i]=0;
}
for(i=30;i<35;i++)
{
	for(j=right[i]-1;j>30;j--)
	{
		if(img[i][j]==white && img[i][j-1]==black)
			baitiaobian_lz[i]=j;
		if(img[i][j]==black && img[i][j-1]==white)
			heitiaobian_lz[i]=j;
	}
	if(baitiaobian_lz[i]==0 || heitiaobian_lz[i]==0)
	{
		luzhangflag_right=0;
		break;
	}
	else
		luzhangflag_right=1;
	if(right[i]-baitiaobian_lz[i]>10)
		luzhangflag_right=0;
}
if(luzhangflag_right)
{
	for(i=5;i<30;i++)
	{
		if(img[i][heitiaobian_lz[30]-10]==black)
		{
			luzhangflag_right=0;
			break;
		}
	}
}
if(luzhangflag_right)
{
	for(i=30;i<35;i++)
	{
		blacksum_lz[i]=baitiaobian_lz[i]-heitiaobian_lz[i];
		if(blacksum_lz[i]<10)
		{
			luzhangflag_right=0;
			break;
		}
	}
}
if(luzhangflag_right)
{
	for(i=30;i<34;i++)
	{
		if(blacksum_lz[i]-blacksum_lz[i+1]<-3 || blacksum_lz[i]-blacksum_lz[i+1]>3)
		{
			luzhangflag_right=0;
			break;
		}
	}
}
}
//远左路障
baitiaobian_row_lz=0;
heitiaobian_row_lz[0]=0;
heitiaobian_row_lz[1]=0;
startcol_lz=0;
if(sum_left_right>=5)
{
  luzhangflag_left=0;
}
for(j=right[3];j>left[3];j--)
{
	for(i=3;i<40;i++)
	{
		if(img[i][j]==white && img[i][j-1]==black)
		{
			startcol_lz=j;
			break;
		}
	}
	if(startcol_lz!=0)
	{
		break;
	}
}
if(startcol_lz>=70)
{
	luzhangflag_left=0;
}
if(right[3]-left[3]>40)
{
	luzhangflag_left=0;
}
for(i=3;i<40;i++)
{
	if(img[i][startcol_lz-5]==white && img[i+1][startcol_lz-5]==black)
	{
		baitiaobian_row_lz=i;
		break;
	}
}
for(i=40;i>10;i--)
{
	if(img[i][startcol_lz-5]==black && img[i+1][startcol_lz-5]==white)
	{
		heitiaobian_row_lz[0]=i+1;
		break;
	}
}
for(i=40;i>10;i--)
{
	if(img[i][startcol_lz-10]==black && img[i+1][startcol_lz-10]==white)
	{
		heitiaobian_row_lz[1]=i+1;
		break;
	}
}
if(heitiaobian_row_lz[0]-baitiaobian_row_lz<=8 || baitiaobian_row_lz==0)
{
	luzhangflag_left=0;
}
if(heitiaobian_row_lz[1]-heitiaobian_row_lz[0]>1 || heitiaobian_row_lz[1]-heitiaobian_row_lz[0]<-1)
{
	luzhangflag_left=0;
}
if(luzhangflag_left)
{
  for(i=heitiaobian_row_lz[0]+1;i<=heitiaobian_row_lz[0]+3;i++)
  {
    if(right[i]-left[i]>=width[i]+5)
    {
      luzhangflag_left=0;
      break;
    }
  }
}
if(luzhangflag_left)
{
	for(i=0;i<30;i++)
	{
          for(j=startcol_lz+1;j<=startcol_lz+5;j++)
          {
		if(img[i][j]==black)
		{
			luzhangflag_left=0;
			break;
		}
          }
	}
}
if(luzhangflag_left)
{
	for(i=baitiaobian_row_lz+1;i<heitiaobian_row_lz[0];i++)
	{
		if(img[i][startcol_lz-10]==white)
		{
			luzhangflag_left=0;
			break;
		}
	}
}
if(luzhangflag_left)
{
	for(j=startcol_lz-10;j>=startcol_lz+5;j++)
	{
		if(img[heitiaobian_row_lz[1]+2][j]==black)
		{
			luzhangflag_left=0;
			break;
		}
	}
}
if(luzhangflag_left)
{
	for(i=baitiaobian_row_lz;i<heitiaobian_row_lz[0];i++)
	{
		if(img[i][startcol_lz+5]==black)
		{
			luzhangflag_left=0;
			break;
		}
	}
}
//近左路障
if(luzhangflag_left==0)
{
for(i=30;i<35;i++)
{
	baitiaobian_lz[i]=0;
	heitiaobian_lz[i]=0;
	blacksum_lz[i]=0;
}
for(i=30;i<35;i++)
{
	for(j=left[i]+1;j<50;j++)
	{
		if(img[i][j]==white && img[i][j+1]==black)
			baitiaobian_lz[i]=j;
		if(img[i][j]==black && img[i][j+1]==white)
			heitiaobian_lz[i]=j;
	}
	if(baitiaobian_lz[i]==0 || heitiaobian_lz[i]==0)
	{
		luzhangflag_left=0;
		break;
	}
	else
		luzhangflag_left=1;
	if(baitiaobian_lz[i]-left[i]>10)
		luzhangflag_left=0;
}
if(luzhangflag_left)
{
	for(i=5;i<30;i++)
	{
		if(img[i][heitiaobian_lz[30]+10]==black)
		{
			luzhangflag_left=0;
			break;
		}
	}
}
if(luzhangflag_left)
{
	for(i=30;i<35;i++)
	{
		blacksum_lz[i]=heitiaobian_lz[i]-baitiaobian_lz[i];
		if(blacksum_lz[i]<10)
		{
			luzhangflag_left=0;
			break;
		}
	}
}
if(luzhangflag_left)
{
	for(i=30;i<34;i++)
	{
		if(blacksum_lz[i]-blacksum_lz[i+1]<-3 || blacksum_lz[i]-blacksum_lz[i+1]>3)
		{
			luzhangflag_left=0;
			break;
		}
	}
}
}
//右路障提中心
  if(luzhangflag_right)
  {
    	for(i=1;i<CAMERA_H;i++)				//重提左边界
	{
		for(j=left[i-1]+1;j>2;j--)
		{
			if(img[i][j]==white && img[i][j-1]==black && img[i][j-2]==black)
			{
				left[i]=j;
				break;
			}
			else
				left[i]=0;
		}
	}
	for(i=0;i<CAMERA_H;i++)
	{
		right_lz[i]=CAMERA_W-1;
	}
	for(i=5;i<CAMERA_H;i++)
	{
		for(j=left[i];j<CAMERA_W-1;j++)
		{
			if(img[i][j]==white && img[i][j+1]==black && img[i][j+1]==black)
			{
				right_lz[i]=j;
				break;
			}
		}
	}
	for(i=6;i<CAMERA_H;i++)
	{
		if(right_lz[i]-right_lz[i-1]<-5)
		{
			startrow_lz=i;
			break;
		}
	}
        if(startrow_lz<7)
          startrow_lz=7;
        center_lz=(left[startrow_lz+5]+right_lz[startrow_lz+5])/2;
        img[startrow_lz+5][center_lz]=red;
/*	for(i=CAMERA_H-1;i>10;i--)
	{
		if(right_lz[i]-right_lz[i-1]>5)
		{
			endrow_lz=i-1;
			break;
		}
	}
        if(endrow_lz<14 && endrow_lz!=0)
          endrow_lz=14;
	if(endrow_lz==0)
		endrow_lz=CAMERA_H-1;
	K_lz=(float)(right_lz[endrow_lz-2]-right_lz[startrow_lz+2])/(float)(endrow_lz-startrow_lz-4);
	for(i=startrow_lz;i<CAMERA_H;i++)
	{
		right[i]=right_lz[startrow_lz+2]+K_lz*(i-startrow_lz-2);
                if(right[i]>CAMERA_W-1)
                  right[i]=CAMERA_W-1;
	}
	if(startrow_lz+2>10)
	{
		for(i=10;i<=startrow_lz+2;i++)
		{
			right[i]=right_lz[startrow_lz+2];
		}
	}*/
  }
//左路障提中心
  if(luzhangflag_left)
  {
    	for(i=1;i<CAMERA_H;i++)				//重提右边界
	{
		for(j=right[i-1]-1;j<CAMERA_W-2;j++)
		{
			if(img[i][j]==white && img[i][j+1]==black && img[i][j+2]==black)
			{
				right[i]=j;
				break;
			}
			else
				right[i]=CAMERA_W-1;
		}
	}
	for(i=0;i<CAMERA_H;i++)
	{
		left_lz[i]=0;
	}
	for(i=5;i<CAMERA_H;i++)
	{
		for(j=right[i];j>1;j--)
		{
			if(img[i][j]==white && img[i][j-1]==black && img[i][j-2]==black)
			{
				left_lz[i]=j;
				break;
			}
		}
	}
	for(i=6;i<CAMERA_H;i++)
	{
		if(left_lz[i]-left_lz[i-1]>5)
		{
			startrow_lz=i;
			break;
		}
	}
        if(startrow_lz<7)
		startrow_lz=7;
        center_lz=(right[startrow_lz+5]+left_lz[startrow_lz+5])/2;
        img[startrow_lz+5][center_lz]=red;
	/*for(i=CAMERA_H-1;i>10;i--)
	{
		if(left_lz[i]-left_lz[i-1]<-5)
		{
			endrow_lz=i-1;
			break;
		}
	}
        if(endrow_lz!=0 && endrow_lz<14)
		endrow_lz=14;
	if(endrow_lz==0)
		endrow_lz=CAMERA_H-1;
	K_lz=(float)(left_lz[startrow_lz+2]-left_lz[endrow_lz-2])/(float)(endrow_lz-startrow_lz-4);
	for(i=startrow_lz+2;i<CAMERA_H;i++)
	{
		left[i]=left_lz[startrow_lz+2]-K_lz*(i-startrow_lz-2);
                if(left[i]<0)
                  left[i]=0;
	}
	if(startrow_lz+2>10)
	{
		for(i=10;i<=startrow_lz+2;i++)
		{
			left[i]=left_lz[startrow_lz+2];
		}
	}    */   
  }
//右路障
lzflag_right=0;
if(luzhangflag_right==0 && wuxiaohang==0)
{
		tiaobianhang_right_lz=0;
		for(i=0;i<CAMERA_H-1;i++)
		{
			if(right[i]-right[i+1]>=6)
			{
				tiaobianhang_right_lz=i;
				break;
			}
		}
	if(tiaobianhang_left==0 && tiaobianhang_right_lz>=2)
	{
		lzflag_right=1;
		for(i=tiaobianhang_right_lz+2;i<=tiaobianhang_right_lz+5;i++)
		{
			if(right[i]-left[i]>=width[i]-7)
			{
				lzflag_right=0;
				break;
			}
			if(right[i]<30)
			{
				lzflag_right=0;
				break;
			}
		}
	}
}
if(lzflag_right)
{
  center_lz=visvalMid[tiaobianhang_right_lz+5];
}
//左路障
lzflag_left=0;
if(luzhangflag_left==0 && wuxiaohang==0)
{
	tiaobianhang_left=0;
	for(i=0;i<CAMERA_H-1;i++)
	{
		if(left[i+1]-left[i]>=6)
		{
			tiaobianhang_left_lz=i;
			break;
		}
	}
	if(tiaobianhang_right==0 && tiaobianhang_left_lz>=2)
	{
		lzflag_left=1;
		for(i=tiaobianhang_left_lz+2;i<=tiaobianhang_left_lz+8;i++)
		{
			if(right[i]-left[i]>=width[i]-7)
			{
				lzflag_left=0;
				break;
			}
			if(left[i]>50)
			{
				lzflag_left=0;
				break;
			}
		}
	}
}
if(lzflag_left)
{
  center_lz=visvalMid[tiaobianhang_left_lz+5];
}
//重新提中线
 /* if(luzhangflag_right || luzhangflag_left)
  {
    for(i=10;i<CAMERA_H;i++)
    {
      visvalMid[i]=(left[i]+right[i])/2;
      img[i][visvalMid[i]]=100;
    }
  }*/
  
}