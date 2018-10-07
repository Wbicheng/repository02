#include "common.h"
#include "include.h"
#include "shizi.h"

uint8 maybeshiziflag;           
uint8 tiaobianhang_sz_left;     //十字左跳变行
uint8 tiaobianhang_sz_right;    //十字右跳变行
float K_sz;                     //十字补线斜率
uint8 buxian_sz_down;           //十字上补线点
uint8 buxian_sz_up;             //十字下补线点
uint8 error_sz;                 //十字补线偏差
uint8 tiaobianhang_nearsz_left; //靠近十字左跳变行
uint8 tiaobianhang_nearsz_right;//靠近十字右跳变行
uint8 nearszflag_left;          //左靠近十字标志
uint8 nearszflag_right;         //右靠近十字标志
uint8 startrow_nearsz;		//靠近十字扫描行
float K_nearsz;                 //靠近十字补线斜率
uint8 maybeshiziflag_right;	//可能斜入右十字标志
uint8 maybeshiziflag_left;	//可能斜入左十字标志
uint8 shiziflag_right;		//右斜入十字标志
uint8 shiziflag_left;		//左斜入十字标志
uint8 baitiaobian_left;		//最左列白跳变点
uint8 baitiaobian_right;	//最右列白跳变点
uint8 shizinum_right;		//右斜入十字延时计数
uint8 shizinum_left;		//左斜入十字延时计数
uint8 whitesum_shizi;           //十字中间列白点数
uint8 xiexian_shang_i;                                    //斜线上点(行)   --算连线判断是否斜入
uint8 xiexian_shang_j;                                    //斜线上点(列)   --算连线判断是否斜入
uint8 xiexian_xia_i;                                    //斜线下点(行)   --算连线判断是否斜入
uint8 xiexian_xia_j;                                    //斜线下点(列)   --算连线判断是否斜入
float xiexian_k;                                      //斜线斜率 
uint8 baitiaobianhang;                                  //白-黑跳变  --界定右边查找斜线上点的范围
uint8 xierushizi_flag_right=0;			        //斜入十字右标志 
uint8 xierushizi_flag_left=0;				//斜入十字左标志 
uint8 farszflag_right;                                  //右远十字标志
uint8 farszflag_left;                                   //左远十字标志
 
uint8 dixiehangnum_left=0;   //左斜入十字底斜行    *******************
uint8 dixiehangnum_right=0;	//右斜入十字底斜行	*******************
uint8 xieruqushidian1=0;     //斜入十字趋势点1
uint8 xieruqushidian2=0;		//斜入十字趋势点2
uint8 xieruqushidian3=0;		//斜入十字趋势点3
uint8 hang20_mid_xieru=0;    //斜入十字补点  *******************
void shizi()
{
 /**********************远一点的十字*************/
maybeshiziflag=1;
farszflag_right=0;
farszflag_left=0;
for(j=visvalMid[8]-2;j<=visvalMid[8]+2;j++)
{
	for(i=0;i<CAMERA_H;i++)
	{
		if(img[i][j]==black)
		{
			maybeshiziflag=0;
			break;
		}
		if(!maybeshiziflag)
			break;
	}
}
if(maybeshiziflag)
{
	for(i=standardrow-9;i>=standardrow-11;i--)
	{
		for(j=0;j<CAMERA_W;j++)
		{
			if(img[i][j]==black)
			{
				maybeshiziflag=0;
				break;
			}
			if(!maybeshiziflag)
				break;
		}
	}
}
tiaobianhang_sz_left=0;
tiaobianhang_sz_right=0;
buxian_sz_up=0;
buxian_sz_down=0;
if(maybeshiziflag && visvalMid[8]>initcenter)			//右十字补线
{
  farszflag_right=1;
  j=CAMERA_W-1;
  for(i=30;i<CAMERA_H-1;i++)
  {
    if(img[i][j]==black)
    {
      farszflag_right=0;
      break;
    }
  }
  if(farszflag_right)
  {
	for(i=6;i<standardrow-10;i++)						//找十字上补线点
	{
		if(left[i+1]<left[i]-5)
		{
			tiaobianhang_sz_left=i;
			buxian_sz_up=tiaobianhang_sz_left-1;
			break;
		}
	}
	for(i=standardrow-10;i<CAMERA_H-1;i++)				//找十字下补线点
	{
		if(left[i]>left[i+1])
		{
			buxian_sz_down=i;
			break;
		}
	}
	if(buxian_sz_up!=0 && buxian_sz_down!=0)				//补线
	{
		error_sz=(int)left[buxian_sz_up]-(int)left[buxian_sz_down];
		K_sz=(float)error_sz/(buxian_sz_down-buxian_sz_up);
		for(i=buxian_sz_up;i<=buxian_sz_down;i++)
		{
			left[i]=left[buxian_sz_down]+K_sz*(buxian_sz_down-i);
		//	img[i][left[i]]=100; //
		}
                for(i=0;i<CAMERA_H;i++)                 //重新提中线
                {
                  visvalMid[i]=(left[i]+right[i])/2;
                  img[i][visvalMid[i]]=red;//
                }
	}
  }
}

if(maybeshiziflag && visvalMid[8]<=initcenter)			//左十字补线
{
	farszflag_left=1;
	j=0;
	for(i=30;i<CAMERA_H-1;i++)
	{
		if(img[i][j]==black)
		{
			farszflag_left=0;
			break;
		}
	}
	for(i=6;i<standardrow-10;i++)						//找十字上补线点
	{
		if(right[i+1]<right[i]+5)
		{
			tiaobianhang_sz_right=i;
			buxian_sz_up=tiaobianhang_sz_right-1;
			break;
		}
	}
	for(i=standardrow-10;i<CAMERA_H-1;i++)				//找十字下补线点
	{
		if(right[i]<right[i+1])
		{
			buxian_sz_down=i;
			break;
		}
	}
	if(buxian_sz_up!=0 && buxian_sz_down!=0)				//补线
	{
		error_sz=(int)right[buxian_sz_down]-(int)right[buxian_sz_up];
		K_sz=(float)error_sz/(buxian_sz_down-buxian_sz_up);
		for(i=buxian_sz_up;i<=buxian_sz_down;i++)
		{
			right[i]=right[buxian_sz_down]-K_sz*(buxian_sz_down-i);
		//	img[i][right[i]]=100;//
		}
                for(i=0;i<CAMERA_H;i++)                 //重新提中线
                {
                  visvalMid[i]=(left[i]+right[i])/2;//
                  img[i][visvalMid[i]]=red;//
                }
	}
}
/***********************靠近十字*******************/
tiaobianhang_nearsz_left=0;
tiaobianhang_nearsz_right=0;
nearszflag_left=0;
nearszflag_right=0;
for(i=13;i<CAMERA_H-1;i++)
{
	if(left[i+1]<left[i]-5)
	{
		tiaobianhang_nearsz_left=i;
		break;
	}
}
for(i=13;i<CAMERA_H-1;i++)
{
	if(right[i+1]>right[i]+5)
	{
		tiaobianhang_nearsz_right=i;
		break;
	}
}
//左靠近十字
if(tiaobianhang_nearsz_left!=0 && tiaobianhang_nearsz_right==0)				
{
	nearszflag_left=1;
	if(tiaobianhang_nearsz_left+10>CAMERA_H-1)		//防越界
		startrow_nearsz=CAMERA_H-1;
	else
		startrow_nearsz=tiaobianhang_nearsz_left+10;
	for(i=startrow_nearsz;i<CAMERA_H;i++)		
	{
		j=0;
		if(img[i][j]==black)		//扫最左边列，有黑则不是
		{
			nearszflag_left=0;
			break;
		}
		j=CAMERA_W-1;
		if(img[i][j]==black)		//扫最右边列，有黑则不是
		{
			nearszflag_left=0;
			break;
		}
	}
	if(nearszflag_left)
	{
		i=startrow_nearsz;
		for(j=0;j<CAMERA_W-1;j++)
		{
			if(img[i][j]==black)		//扫扫描行，有黑则不是
			{
				nearszflag_left=0;
				break;
			}
		}
		j=65;
		for(i=10;i<startrow_nearsz;i++)
		{
			if(img[i][j]==black)		//扫65列，有黑则不是
			{
				nearszflag_left=0;
				break;
			}
		}
	}
}
//右靠近十字
if(tiaobianhang_nearsz_left==0 && tiaobianhang_nearsz_right!=0)				
{
	nearszflag_right=1;
	if(tiaobianhang_nearsz_right+10>CAMERA_H-1)		//防越界
		startrow_nearsz=CAMERA_H-1;
	else
		startrow_nearsz=tiaobianhang_nearsz_right+10;
	for(i=startrow_nearsz;i<CAMERA_H;i++)		
	{
		j=0;
		if(img[i][j]==black)		//扫最左边列，有黑则不是
		{
			nearszflag_right=0;
			break;
		}
		j=CAMERA_W-1;
		if(img[i][j]==black)		//扫最右边列，有黑则不是
		{
			nearszflag_right=0;
			break;
		}
	}
	if(nearszflag_right)
	{
		i=startrow_nearsz;
		for(j=0;j<CAMERA_W-1;j++)
		{
			if(img[i][j]==black)		//扫扫描行，有黑则不是
			{
				nearszflag_right=0;
				break;
			}
		}
		j=15;
		for(i=10;i<startrow_nearsz;i++)
		{
			if(img[i][j]==black)		//扫15列，有黑则不是
			{
				nearszflag_right=0;
				break;
			}
		}
	}
}

/************************斜入十字*******************/
 /* maybeshiziflag_right=1;
  maybeshiziflag_left=1;
  for(i=20;i<CAMERA_H;i++)      //左上扫到右下 有黑则不是
  {
	if(img[i][2*(i-20)]==black)
	{
		maybeshiziflag_right=0;
		break;
	}
  }
  for(i=20;i<CAMERA_H;i++)	//右上扫到左下 有黑则不是
  {
	if(img[i][CAMERA_W-1-2*(i-20)]==black)
	{
		maybeshiziflag_left=0;
		break;
	}
  }
  baitiaobian_left=0;
  baitiaobian_right=0;
  if(maybeshiziflag_right || maybeshiziflag_left)
  {
	j=0;					
	for(i=20;i<CAMERA_H-1;i++)			//扫最左列白跳变点个数
	{
		if(img[i][j]==white && img[i+1][j]==black)
			baitiaobian_left++;
	}
	j=CAMERA_W-1;					
	for(i=20;i<CAMERA_H-1;i++)			//扫最右列白跳变点个数
	{
		if(img[i][j]==white && img[i+1][j]==black)
			baitiaobian_right++;
	}
        j=40;
	whitesum_shizi=0;
	for(i=0;i<20;i++)					//前20行中间列白点数大于10则不是十字
	{
		if(img[i][j]==white)
		{
			whitesum_shizi++;
		}
	}
	if(whitesum_shizi>10)
	{
		maybeshiziflag_right=0;
		maybeshiziflag_left=0;
	}
  }

//右斜入
  shiziflag_right=0;
  if(baitiaobian_left==1 && maybeshiziflag_right)//条件一：最左列有白跳变	
  {
	shiziflag_right=1;
        for(i=CAMERA_H-1;i>CAMERA_H-1-(CAMERA_W-1-(left[CAMERA_H-1]+3))/2;i--)	//左下扫到右上 有黑则不是
        {
          if(img[i][left[CAMERA_H-1]+3+2*(CAMERA_H-1-i)]==black)
          {
			shiziflag_right=0;
			break;
          }
        }
	j=CAMERA_W-1;
	for(i=20;i<CAMERA_H;i++)	        //条件二：最右列20行以下全白
	{
		if(img[i][j]==black)
		{
			shiziflag_right=0;
			break;
		}
	}
  }

//左斜入
  shiziflag_left=0;
  if(baitiaobian_right==1 && maybeshiziflag_left)		//条件一：最右列有白跳变	
  {
	shiziflag_left=1;
        for(i=CAMERA_H-1;i>CAMERA_H-1-(right[CAMERA_H-1]-3)/2;i--)	//右下扫到左上 有黑则不是
        {
          if(img[i][right[CAMERA_H-1]-3-2*(CAMERA_H-1-i)]==black)
          {
			shiziflag_left=0;
			break;
          }
        }
	j=0;
	for(i=20;i<CAMERA_H;i++)	        //条件二：最左列20行以下全白
	{
		if(img[i][j]==black)
		{
			shiziflag_left=0;
			break;
		}
	}
  }
  
  if(shiziflag_right)
    shizinum_right=10;
  if(shiziflag_left)
    shizinum_left=10;
  if(shizinum_right)
  {
	j=CAMERA_W-1;
	for(i=20;i<CAMERA_H;i++)	      //最右列20行以下有黑则将计数器清零
	{
		if(img[i][j]==black)
		{
			shizinum_right=0;
			break;
		}
	}
  }
  if(shizinum_left)
  {
	j=0;
	for(i=20;i<CAMERA_H;i++)	      //最左列20行以下有黑则将计数器清零
	{
		if(img[i][j]==black)
		{
			shizinum_left=0;
			break;
		}
	}
  }
  //计数器自减
  if(shizinum_right)
    shizinum_right--;
  if(shizinum_left)
    shizinum_left--;
}

*/



/****右斜入***/	
  xierushizi_flag_right=0; 
  heitiaobian=0;
  baitiaobian=0;
  baitiaobianhang=0;
  for(i=2;i<50;i++) //过滤噪点，同时避免下方几行白
  {
	j=CAMERA_W-1;
	if(img[i][j]==black && img[i+1][j]==white )
       {
          heitiaobian++;
	}
	if(img[i][j]==white && img[i+1][j]==black)
	{
          baitiaobian++;
          baitiaobianhang=i;
	}
  }
	
 // if((heitiaobian==1 && (baitiaobian==1||baitiaobian==2) && baitiaobianhang>5)||(heitiaobian==2 && baitiaobian==2))
  if((heitiaobian==1 && (baitiaobian==1||baitiaobian==2) && baitiaobianhang>5)//////////////////////////////////////////////////////////////////
		||(heitiaobian==2 && baitiaobian==2)||(heitiaobian==0 && baitiaobian==0 && img[CAMERA_H-1][CAMERA_W-1]==black)
		||(heitiaobian==2 && baitiaobian==1 && img[CAMERA_H/2][CAMERA_W-1]==white))
	xierushizi_flag_right=1;
  if(xierushizi_flag_right)
  {
	xiexian_shang_i=0;
	xiexian_shang_j=0;
	xiexian_xia_i=0;
	xiexian_xia_j=CAMERA_W-1;
	for(i=baitiaobianhang-2;i<55;i++)
	{
		
		if(right[i]<xiexian_xia_j && img[i][right[i]]==black)//剔除右边界为79行即白的情况
		{
			xiexian_xia_j=right[i];  //下坐标
			xiexian_xia_i=i;
		}	
			
	 }         ////////////////////////
	for(i=xiexian_xia_i;i>0;i--)
	{
		if(right[i]>=xiexian_shang_j && img[i][right[i]]==black )
		{
                    xiexian_shang_j=right[i]; //上坐标
                    xiexian_shang_i=i;
		}
		if((right[i]-right[i-1])>=12||(right[i-1]-right[i])>=12||img[i-1][right[i-1]]==white) //边界跳变，不是完整的左右边界
			break;
	}
	if((xiexian_shang_i-baitiaobianhang)>=5||(baitiaobianhang-xiexian_shang_i)>=5||xiexian_xia_i<=20)
		xierushizi_flag_right=0;
	if(xierushizi_flag_right)
	{
		xiexian_k=0;
		if(xiexian_shang_j!=xiexian_xia_j)
			xiexian_k=(float)(xiexian_shang_i-xiexian_xia_i)/(xiexian_shang_j-xiexian_xia_j);
		else
			xiexian_k=0;
		if(xiexian_k<0)
                  xiexian_k=-xiexian_k;
  		for(j=0;j<=xiexian_shang_j;j++) //右下斜线判断
		{
			i=(int)((xiexian_shang_j-j)*xiexian_k+xiexian_shang_i);
			if(i>CAMERA_H-1)
			{
                          i=CAMERA_H-1;
			}
		//	img[i-4][j]=100;
			if(img[i-4][j]==black)
			{
				xierushizi_flag_right=0;
				break;
			
			}		
		} 		
	}
	if(xierushizi_flag_right)
	{
		for(i=xiexian_xia_i-2;i>0;i--)
		{
			if(img[i][xiexian_xia_j-2]==white && img[i-1][xiexian_xia_j-2]==black)
			{
				xiexian_shang_i=i-2;			
					break;
			}
		}
		for(j=xiexian_xia_j-2;j>=0;j--)
		{
			if(j!=0)
			{
				if(img[xiexian_shang_i-1][j]==black && img[xiexian_shang_i-1][j-1]==white)
				{
					xiexian_shang_j=j;
					xiexian_shang_i=xiexian_shang_i-1;
					break;
				}
			}
			else
			{
				if(img[xiexian_shang_i-1][j]==black)
				{
					for(i=xiexian_shang_i;i<CAMERA_H/2;i++)
					{
						if(img[i][j]==white)
						{
							xiexian_shang_j=j;
							xiexian_shang_i=i; 
							break;
                                                }
					}
				}
			}
		}
	}
	if(xierushizi_flag_right)
	{
		if(xiexian_xia_j<xiexian_shang_j||xiexian_shang_i>20||(xiexian_xia_i-xiexian_shang_i)<=10)
			xierushizi_flag_right=0;	
		if(xierushizi_flag_right)
		{
			for(i=CAMERA_H/2;i<CAMERA_H;i++)
			{
				if(img[i][0]==black)
				{
					xierushizi_flag_right=0;
					break;
				}	
			
			}	
			
		}

	}
	
	if(xierushizi_flag_right)
	{
		if(xiexian_shang_i!=xiexian_xia_i)
		xiexian_k=(float)(xiexian_xia_j-xiexian_shang_j)/(xiexian_xia_i-xiexian_shang_i);
		else
			xiexian_k=0;
		if(xiexian_k<0)
			xiexian_k=-xiexian_k;
		for(i=xiexian_shang_i;i<CAMERA_H;i++)
		{
                    if(i<xiexian_xia_i)
                    {
			j=(int)((i-xiexian_shang_i)*xiexian_k+xiexian_shang_j);
			if(j>CAMERA_W-1)
				j=CAMERA_W-1;
			if(j<=8)
                          j=0;
			else j=j-8;
                    }
                  else
                    j=xiexian_xia_j-1;
                   if(img[i][j]==black)
                  {
			xierushizi_flag_right=0;
			break;
                  } 
		//	img[i][j]=100;
			
		}
		if(xierushizi_flag_right)
		{
			hang20_mid_xieru=0;
			if((int)((20-xiexian_shang_i)*xiexian_k+xiexian_shang_j)>CAMERA_W) ///////////////////
				right[20]=CAMERA_W-1;
			else if((int)((20-xiexian_shang_i)*xiexian_k+xiexian_shang_j)<0)
				right[20]=0;
			else right[20]=(int)((20-xiexian_shang_i)*xiexian_k+xiexian_shang_j);
				hang20_mid_xieru=(right[20]+0)/2;
		}
        }
}
//左斜入
       xierushizi_flag_left=0;
       heitiaobian=0;
       baitiaobian=0;
       baitiaobianhang=0;    
//    if(!xierushizi_flag_right)
 //   {
         
           for(i=2;i<50;i++) //过滤噪点，同时避免下方几行白
           {
              j=0;
              if(img[i][j]==black && img[i+1][j]==white )
              {
                  heitiaobian++;
              }
              if(img[i][j]==white && img[i+1][j]==black)
              {
                  baitiaobian++;
                  baitiaobianhang=i;
              }
            }
        //  if((heitiaobian==1 && (baitiaobian==1||baitiaobian==2) && baitiaobianhang>5)||(heitiaobian==2 && baitiaobian==2))
         if((heitiaobian==1 && (baitiaobian==1||baitiaobian==2) && baitiaobianhang>5)//////////////////////////////////////////////////////////////////
		||(heitiaobian==2 && baitiaobian==2)||(heitiaobian==0 && baitiaobian==0 && img[CAMERA_H-1][0]==black)
		||(heitiaobian==2 && baitiaobian==1 && img[CAMERA_H/2][0]==white))
            xierushizi_flag_left=1;
		
          if(xierushizi_flag_left)
          {
                xiexian_shang_i=0;
		xiexian_shang_j=CAMERA_W-1;
		xiexian_xia_i=0;
		xiexian_xia_j=0;
		for(i=baitiaobianhang-2;i<55;i++)
		{
		
                    if(left[i]>xiexian_xia_j && img[i][left[i]]==black)//剔除右边界为79行即白的情况
                    {
			xiexian_xia_j=left[i];  //下坐标
			xiexian_xia_i=i;
                    }	
		
		}
		for(i=xiexian_xia_i;i>0;i--)
		{
			if(left[i]<=xiexian_shang_j && img[i][left[i]]==black )
			{
					xiexian_shang_j=left[i]; //上坐标
					xiexian_shang_i=i;
					
			}
			if((left[i]-left[i-1])>=12||(left[i-1]-left[i])>=12||img[i-1][left[i-1]]==white) //边界跳变，不是完整的左右边界
				break;
		}
		if((xiexian_shang_i-baitiaobianhang)>=5||(baitiaobianhang-xiexian_shang_i)>=5||xiexian_xia_i<=20)//避免弯道误判：上点应该和白行几乎同行
			xierushizi_flag_left=0;
		if(xierushizi_flag_left)
		{
			xiexian_k=0;
			if(xiexian_shang_j!=xiexian_xia_j)
				xiexian_k=(float)(xiexian_shang_i-xiexian_xia_i)/(xiexian_shang_j-xiexian_xia_j);
			else
				xiexian_k=0;
			if(xiexian_k<0)
				xiexian_k=-xiexian_k;
  			for(j=xiexian_shang_j;j<CAMERA_W;j++) //右下斜线判断
			{
				i=(int)((j-xiexian_shang_j)*xiexian_k+xiexian_shang_i);
				if(i>CAMERA_H-1)
				{
					i=CAMERA_H-1;
				}
		//	img[i-4][j]=100;
				if(img[i-4][j]==black)
				{
					xierushizi_flag_left=0;
					break;
			
				} 
		
			}    		
		}
		
		if(xierushizi_flag_left)
		{
			for(i=xiexian_xia_i-2;i>0;i--)
			{
				if(img[i][xiexian_xia_j+2]==white && img[i-1][xiexian_xia_j+2]==black)
				{
					xiexian_shang_i=i-2;
					break;
				}
			}
			for(j=xiexian_xia_j+2;j<CAMERA_W;j++)
			{
				if(j!=CAMERA_W-1)
				{
					if(img[xiexian_shang_i-1][j]==black && img[xiexian_shang_i-1][j+1]==white)
					{
						xiexian_shang_j=j;
						xiexian_shang_i=xiexian_shang_i-1;
						break;
					}
				}
				else
				{
					if(img[xiexian_shang_i-1][j]==black)
					{
						for(i=xiexian_shang_i;i<CAMERA_H/2;i++)
						{
							if(img[i][j]==white)
							{
								xiexian_shang_j=j;
								xiexian_shang_i=i;
								break;
					
							}
						}
					}
				}
			}
		}
		if(xierushizi_flag_left)
		{
			if(xiexian_shang_j<xiexian_xia_j||xiexian_shang_i>20||(xiexian_xia_i-xiexian_shang_i)<=10)
				xierushizi_flag_left=0;
			
			if(xierushizi_flag_left)
			{
				for(i=CAMERA_H/2;i<CAMERA_H;i++)
				{
					if(img[i][CAMERA_W-1]==black)
					{
						xierushizi_flag_left=0;
						break;
					}
					
				}
			
			
			}
		
		}
		
		if(xierushizi_flag_left)
		{
			if(xiexian_shang_i!=xiexian_xia_i)
				xiexian_k=(float)(xiexian_xia_j-xiexian_shang_j)/(xiexian_xia_i-xiexian_shang_i);
			else
				xiexian_k=0;
			if(xiexian_k<0)
				xiexian_k=-xiexian_k;
			for(i=xiexian_shang_i;i<CAMERA_H;i++)
			{
				if(i<xiexian_xia_i)
				{
					j=xiexian_shang_j-(int)(i-xiexian_shang_i)*xiexian_k;
					if(j>CAMERA_W-1)//无符号数小于0后会大于CAMERA_W
					//if(j<0)
						j=0;
					if(j>CAMERA_W)
						j=CAMERA_W-1;
					else j=j+8;
		
				}
				else j=xiexian_xia_j+1;
		//	img[i][j]=100;
				if(img[i][j]==black)
				{
					xierushizi_flag_left=0;
					break;
				} 
			
			}

		}

		if(xierushizi_flag_left)
		{
			hang20_mid_xieru=0;		
			if(xiexian_shang_j-(int)(20-xiexian_shang_i)*xiexian_k>CAMERA_W-1)
				left[20]=CAMERA_W-1;
			else if (xiexian_shang_j-(int)(20-xiexian_shang_i)*xiexian_k<0)
				left[20]=0;
			else left[20]=xiexian_shang_j-(int)(20-xiexian_shang_i)*xiexian_k;
				hang20_mid_xieru=(left[20]+CAMERA_W-1)/2;
		
		}
	} 
 //   }	
  
 /************************斜入十字补充判断*************************/
    //左斜入十字
if(lianxuhangnum_right>=40 && xierushizi_flag_left==0)//右边连续行数大于一定值
{
	dixiehangnum_left=0; //底斜行数
	//左边界从下到上有一个跳变
	btowhang=0;
	j=0;
	for(i=CAMERA_H-1;i>0;i--)
	{
		if(img[i][j]==black && img[i-1][j]==white)
		{
			btowhang=i;
			break;
		}	
	}
	if(btowhang!=0) //找不到左边界的黑白点
		xierushizi_flag_left=1;
	if(left[btowhang]>CAMERA_W/2) //左边界的黑白跳变点所在行的的左边界小于列数一半
	   xierushizi_flag_left=0;
	if(xierushizi_flag_left)
	{
		for(i=CAMERA_H-1;i>btowhang;i--)
		{
			if(left[i-1]>=left[i])
				dixiehangnum_left++;
			else
				break;	
		}
		if(dixiehangnum_left<=3 || i<=btowhang) //底斜行行数需要大于3行 并且拐点小于黑白跳变点
				xierushizi_flag_left=0;	
	}
	//此时上面留下的i值为左斜入拐点
	if(xierushizi_flag_left) // 左斜入拐点到右边界全白
	{
		for(j=left[i]+1;j<CAMERA_W;j++)
		{
			if(img[i][j]==black)
			{
				xierushizi_flag_left=0;
				break;	
			}
		}
	}
	if(xierushizi_flag_left)//左斜入拐点上方边界递减并且边界上方全白
	{
		for(;i>btowhang;i--)
		{
			if((left[i-1]>left[i])|| img[i-1][left[i]]==black)
			{
				xierushizi_flag_left=0;
				break;			
			}	
		}	
	}
	if(xierushizi_flag_left)//右边界一定行数全白
	{
		j=CAMERA_W-1;
		for(i=CAMERA_H/2;i<CAMERA_H;i++)
		{
			if(img[i][j]==black)
			{
				xierushizi_flag_left=0;
				break;
			}
		
		}	
	}
	//右边界的黑白跳变点()下几行向左扫白-黑跳变点，几行的跳变点都有列数变小的趋势
	if(xierushizi_flag_left)
	{
		j=CAMERA_W-2;
		wtobhang=0;
		xieruqushidian1=0;
		xieruqushidian2=0;
		xieruqushidian3=0;
		for(i=0;i<CAMERA_H/2;i++)
		{
			if(img[i][j]==black && img[i+1][j]==white)
			{
				wtobhang=i+1;
				break;
			}		
		}
                if(i==CAMERA_H/2)    //////////////////////
                  wtobhang=0;
		for(j=CAMERA_W-1;j>0;j--)
		{
			if(img[wtobhang][j]==white && img[wtobhang][j-1]==black && xieruqushidian1==0)
				xieruqushidian1=j-1;
			if(img[wtobhang+1][j]==white && img[wtobhang+1][j-1]==black && xieruqushidian2==0)
				xieruqushidian2=j-1;
			if(img[wtobhang+2][j]==white && img[wtobhang+2][j-1]==black && xieruqushidian3==0)
				xieruqushidian3=j-1;			
		}
		if(!(xieruqushidian1-xieruqushidian2<=5 && xieruqushidian1-xieruqushidian2>=0)
		|| !(xieruqushidian2-xieruqushidian3<=5 && xieruqushidian2-xieruqushidian3>=0)
		|| xieruqushidian3<=10 )
			xierushizi_flag_left=0;
	}
	//补点
	if(xierushizi_flag_left)
	{
		hang20_mid_xieru=0;
		for(j=xieruqushidian2+1;j<CAMERA_W;j++)
		{
			if(img[wtobhang+1][j]==white && img[wtobhang+1][j+1]==black)
			break;	
		}
		hang20_mid_xieru=(xieruqushidian2+1+j)/2;
	}
}
//右斜入十字

if(lianxuhangnum_left>=40 && xierushizi_flag_right==0)//左边连续行数大于一定值
{
	dixiehangnum_right=0; //底斜行数
	//右边界从下到上有一个跳变
	btowhang=0;
	j=CAMERA_W-1;
	for(i=CAMERA_H-1;i>0;i--)
	{
		if(img[i][j]==black && img[i-1][j]==white)
		{
			btowhang=i;
			break;
		}	
	}
	if(btowhang!=0) //找不到右边界的黑白点
		xierushizi_flag_right=1;
	if(right[btowhang]<CAMERA_W/2) //右边界的黑白跳变点所在行的的右边界大于列数一半
	   xierushizi_flag_right=0;
	if(xierushizi_flag_right)
	{
		for(i=CAMERA_H-1;i>btowhang;i--)
		{
			if(right[i-1]<=right[i])
				dixiehangnum_right++;
			else
				break;	
		}
		if(dixiehangnum_right<=3 || i<=btowhang) //底斜行行数需要大于3行 并且拐点小于黑白跳变点
				xierushizi_flag_right=0;	
	}
	//此时上面留下的i值为右斜入拐点
	if(xierushizi_flag_right) // 左边界到右斜入拐点全白
	{
		for(j=0;j<right[i];j++)
		{
			if(img[i][j]==black)
			{
				xierushizi_flag_right=0;
				break;	
			}
		}

	}
	if(xierushizi_flag_right)//右斜入拐点上方边界递增并且边界上方全白
	{
		for(;i>btowhang;i--)
		{
			if((right[i]>right[i-1])|| img[i-1][right[i]]==black)
			{
				xierushizi_flag_right=0;
				break;			
			}	
		}	
	}
	if(xierushizi_flag_right)//左边界一定行数全白
	{
		j=0;
		for(i=CAMERA_H/2;i<CAMERA_H;i++)
		{
			if(img[i][j]==black)
			{
				xierushizi_flag_right=0;
				break;
			}
		
		}	
	}
		//左边界的白黑跳变点下几行向右扫白-黑跳变点，几行的跳变点都有列数变大的趋势
	if(xierushizi_flag_right)
	{
		j=1;
		wtobhang=0;
		xieruqushidian1=0;
		xieruqushidian2=0;
		xieruqushidian3=0;
		for(i=0;i<CAMERA_H/2;i++)
		{
			if(img[i][j]==black && img[i+1][j]==white)
			{
				wtobhang=i+1;
				break;
			}		
		}
                if(i==CAMERA_H/2)  ///////////////////////////////
                  wtobhang=0;
		for(j=0;j<CAMERA_W;j++)
		{
			if(img[wtobhang][j]==white && img[wtobhang][j+1]==black && xieruqushidian1==0)
				xieruqushidian1=j+1;
			if(img[wtobhang+1][j]==white && img[wtobhang+1][j+1]==black && xieruqushidian2==0)
				xieruqushidian2=j+1;
			if(img[wtobhang+2][j]==white && img[wtobhang+2][j+1]==black && xieruqushidian3==0)
				xieruqushidian3=j+1;			
		}
		if(!(xieruqushidian2-xieruqushidian1<=5 && xieruqushidian2-xieruqushidian1>=0) 
		|| !(xieruqushidian3-xieruqushidian2<=5 && xieruqushidian3-xieruqushidian2>=0)
		|| xieruqushidian3>=70 || (xieruqushidian1==0 && xieruqushidian2==0 && xieruqushidian3==0 ))
			xierushizi_flag_right=0;
	}
	//斜入十字补点	
	if(xierushizi_flag_right)
	{
		hang20_mid_xieru=0;
		for(j=xieruqushidian2-1;j>0;j--)
		{
			if(img[wtobhang+1][j]==white && img[wtobhang+1][j-1]==black)
			break;	
		}
		hang20_mid_xieru=(xieruqushidian2-1+j)/2;
	}

}
 
/********************补线*******************/
//靠近十字补线
if(nearszflag_left)		
{
	K_nearsz=(float)(left[tiaobianhang_nearsz_left-5]-left[tiaobianhang_nearsz_left])/5;
	for(i=tiaobianhang_nearsz_left;i<CAMERA_H;i++)
	{
		if(left[tiaobianhang_nearsz_left]-K_nearsz*(i-tiaobianhang_nearsz_left)<0)
			left[i]=0;
		else
			left[i]=left[tiaobianhang_nearsz_left]-K_nearsz*(i-tiaobianhang_nearsz_left);
		img[i][left[i]]=100;
	}
        for(i=0;i<CAMERA_H;i++)                 //重新提中线
        {
          visvalMid[i]=(left[i]+right[i])/2;
          img[i][visvalMid[i]]=red;
        }
}
if(nearszflag_right)		
{
	K_nearsz=(float)(right[tiaobianhang_nearsz_right]-right[tiaobianhang_nearsz_right-5])/5;
	for(i=tiaobianhang_nearsz_right;i<CAMERA_H;i++)
	{
		if(right[tiaobianhang_nearsz_right]+K_nearsz*(i-tiaobianhang_nearsz_right)>CAMERA_W-1)
			right[i]=CAMERA_W-1;
		else
			right[i]=right[tiaobianhang_nearsz_right]+K_nearsz*(i-tiaobianhang_nearsz_right);
		img[i][right[i]]=100;
	}
        for(i=0;i<CAMERA_H;i++)                 //重新提中线
        {
          visvalMid[i]=(left[i]+right[i])/2;
          img[i][visvalMid[i]]=red;
        }
}

}