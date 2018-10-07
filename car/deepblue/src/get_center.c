#include "common.h"
#include "include.h"
#include "get_center.h"

int8 left[CAMERA_H]={0};           //定义左边界
int8 right[CAMERA_H]={0};          //定义右边界
int8 visvalMid[CAMERA_H]={0};      //定义中线
uint8 row=CAMERA_H;                //定义行
uint8 col=CAMERA_W;                //定义列
uint8 initcenter=CAMERA_W/2-1;     //定义列中心
uint8 MIDCOLOR=100;                //中线灰度
uint8 wuxiaohang_flag=0;  //无效行标志位
uint8 wuxiaohang=0;
unsigned char *p;
int i,j;

void get_center()
{
      int sum=0;//计算黑像素数量，判断是否为无效行
      int i_center=0;//保护i值，让中线直接向上
      uint8 iflag=0;//中线直接向上，不再通过左右判断  
      wuxiaohang=0;//避免上一帧图像的印象
     iflag=0;
     /* uint8 i1=0;
      for(i1=0;i1<60;i1++)
      right[i1]=79; */
/*     for(i=row-1;i>=0;i--)//逐行扫描
	{

		if(i==row-1)//底行，提供左右边界初始值
		{
			for(j=initcenter;j>=0;j--)
			{
				//if((ImageData[i][j]==black &&ImageData[i][j+1]==black &&ImageData[i][j+2]==white))
				if((img[i][j]==black &&img[i][j+1]==white))
				{
					left[i]=j;
					break;
				}
				else	left[i]=0;
				
			}
		//	ImageData[i][left[i]]=100; //
			for(j=initcenter;j<=col-1;j++)
			{
				//if((ImageData[i][j-2]==white &&ImageData[i][j-1]==black &&ImageData[i][j]==black))
				if((img[i][j-1]==white &&img[i][j]==black))

				{
					right[i]=j;
					
					break;
				}
				else	right[i]=col-1;
				
			}
		//	ImageData[i][right[i]]=100; //
			visvalMid[i]=(left[i]+right[i])/2;//底行为标准
			img[i][visvalMid[i]]=100;
		}	

		else
		{
			if(img[i][left[i+1]]==white)//左边缘为白找左
			{
				for(j=left[i+1];j>=0;j--)
				{
					if(j==0) //防止越界
						left[i]=0;
					else if(img[i][j]==white &&img[i][j-1]==black)
					//	if(ImageData[i][j]==black &&ImageData[i][j+1]==black &&ImageData[i][j+2]==white)
						
					{
						left[i]=j-1;
					
						break;
					}
					else  left[i]=0;
				}
			
		//		ImageData[i][left[i]]=100; //	
			}
			
			if(img[i][left[i+1]]==black)//左边缘为黑找左
			{
				for(j=left[i+1];j<=right[i+1];j++)//避免找过头，使左大于右
				{
					if(j==col-1) //防止越界
						right[i]=col-1;
					//	if(ImageData[i][j-2]==black&&ImageData[i][j-1]==black &&ImageData[i][j]==white)
					else if(img[i][j]==black&&img[i][j+1]==white)
					{
						left[i]=j;
						
						break;
					}
					else 	left[i]=0;
				}
				//	ImageData[i][left[i]]=100;  //
			}
			if(img[i][right[i+1]]==white)//右边缘为白找右
			{
				for(j=right[i+1];j<=col-1;j++)
				{
					if(j==col-1)
						right[i]=col-1;
					//if(ImageData[i][j]==white &&ImageData[i][j+1]==black &&ImageData[i][j]==black)
					else if(img[i][j]==white &&img[i][j+1]==black )
					{
						right[i]=j+1;
						
						break;
					}	
					else 
						right[i]=col-1;
				}
				//	ImageData[i][right[i]]=100; //
			}
			if(img[i][right[i+1]]==black)//右边缘为黑找右
			{
				for(j=right[i+1];j>=left[i+1];j--)//避免找过头，使左大于右
				{
					if(j==0) //防止越界
						right[i]=col-1;
					//	if(ImageData[i][j]==white &&ImageData[i][j+1]==black &&ImageData[i][j+2]==black)
					else if(img[i][j-1]==white &&img[i][j]==black)
					{
						right[i]=j;
					
						break;
					}
					else right[i]=col-1;
				}
				//	ImageData[i][right[i]]=100; //
			}
		
	    //计算中值 
			if((left[i]<=right[i])&&!iflag)//左右相反时中线为原来
                      //  if(left[i]<right[i])
                       {
				if((left[i]!=0)&&(right[i]!=col-1))
					visvalMid[i]=(left[i]+right[i])/2;
				if((left[i]==0)&&(right[i]!=col-1))//左边找不到
				{
					visvalMid[i]=(left[i+1]+right[i])/2;
					if (visvalMid[i]>col-1) visvalMid[i]=2;
				}	
				if((left[i]!=0)&&(right[i]==col-1))//右边找不到
                                {
					visvalMid[i]=(left[i]+right[i+1])/2;
					if(visvalMid[i]>col-1) visvalMid[i]=col-2;//为无符号，小于0会变成较大的整数会对于col-1
		
				}

                         }
			 if((left[i]==0)&&(right[i]==col-1))
			{
                            if(i>=row/3) 
                            {
				visvalMid[i]=visvalMid[i+1];
                            }
                            else	
                            {
				i_center=i;
				iflag=1;
				for(;i_center>=0;i_center--)
				{	
                                    visvalMid[i_center]=visvalMid[i_center+1];
                                 //   img[i_center][visvalMid[i_center]]=100;
				}
				
                            }

			}
                        	
                         // img[i][visvalMid[i]]=100;//每行计算完中值后统一赋值，避免对i行0列赋值，即没有中值
                        
//无效行
                        wuxiaohang_flag=0;
                         if((left[i]>=right[i]-col/2))//缩一半
                        {
                            sum=0;
                            for(j=left[i];j<right[i];j++)
                           {
                                if((img[i-1][j]!=0)&&(img[i-1][j]!=100))
				  break;
				else  sum++;
				
                            }
				if((sum==right[i]-left[i])&&i)
				{
					wuxiaohang=i-1;
                                        wuxiaohang_flag=1;
					break;
				}
				
		   
                        }	
		}
        }
        if(wuxiaohang)
	{
		for(i=0;i<=wuxiaohang;i++)
		{
                          if(visvalMid[wuxiaohang+2]<40)
			 {
				right[i]=0;
				left[i]=0;
				visvalMid[i]=0;
			 }
			 if(visvalMid[wuxiaohang+2]>40)
			{
				right[i]=CAMERA_W-1;
				left[i]=CAMERA_W-1;
				visvalMid[i]=CAMERA_W-1;
			}
                }
        }
  */
     
//提线
    for (i = row-1;i >= 0; i -- )//初始化
    {
         left[i] = 0;
         right[i] = col-1;
         visvalMid[i] = col/2;
    }
    for(i=row-1;i>=0;i--)//逐行扫描
    {
                if(i==row-1)//底行，提供左右边界初始值
		{
			for(j=initcenter;j>=0;j--)
			{
				if((img[i][j]==black &&img[i][j+1]==white))
				{
					left[i]=j;
					break;
				}
				else	left[i]=0;
				
			}
			for(j=initcenter;j<=col-1;j++)
			{
				if((img[i][j-1]==white &&img[i][j]==black))

				{
					right[i]=j;
					
					break;
				}
				else	right[i]=col-1;				
			}
                        visvalMid[i]=(left[i]+right[i])/2;
		}	
		else
		{
			if(img[i][left[i+1]]==white)//左边缘为白找左
			{
				for(j=left[i+1];j>=0;j--)
				{
					if(j==0) //防止越界
						left[i]=0;
					else if(img[i][j]==white &&img[i][j-1]==black)						
					{
						left[i]=j-1;
					
						break;
					}
					else  left[i]=0;
				}				
			}
			
			if(img[i][left[i+1]]==black)//左边缘为黑找左
			{
				for(j=left[i+1];j<=right[i+1];j++)//避免找过头，使左大于右
				{
					if(j==col-1) //防止越界
						right[i]=col-1;
					else if(img[i][j]==black&&img[i][j+1]==white)
					{
						left[i]=j;
						
						break;
					}
					else 	left[i]=0;
				}
			}
			if(img[i][right[i+1]]==white)//右边缘为白找右
			{
				for(j=right[i+1];j<=col-1;j++)
				{
					if(j==col-1)
						right[i]=col-1;
					else if(img[i][j]==white &&img[i][j+1]==black )
					{
						right[i]=j+1;
						
						break;
					}	
					else 
						right[i]=col-1;
				}
			}
			if(img[i][right[i+1]]==black)//右边缘为黑找右
			{
				for(j=right[i+1];j>=left[i+1];j--)//避免找过头，使左大于右
				{
					if(j==0) //防止越界
						right[i]=col-1;
					else if(img[i][j-1]==white &&img[i][j]==black)
					{
						right[i]=j;
					
						break;
					}
					else right[i]=col-1;
				}

			}
		
		
	    //计算中值 
			if((left[i]<right[i])&&!iflag)//左右相反时中线为原来
                      //  if(left[i]<right[i])
                        {
				if((left[i]!=0)&&(right[i]!=col-1))
					visvalMid[i]=(left[i]+right[i])/2;
				if((left[i]==0)&&(right[i]!=col-1))//左边找不到
				{
					visvalMid[i]=(left[i+1]+right[i])/2;
					if (visvalMid[i]>col-1) visvalMid[i]=2;
				}	
				if((left[i]!=0)&&(right[i]==col-1))//右边找不到
                                {
					visvalMid[i]=(left[i]+right[i+1])/2;
					if(visvalMid[i]>col-1) visvalMid[i]=col-2;//为无符号，小于0会变成较大的整数会对于col-1
		
				}

                        }


			 if((left[i]==0)&&(right[i]==col-1))
			{
                              if(i>=row/3) 
                              {
                                    visvalMid[i]=visvalMid[i+1];
                              }
                              else	
                              {
                                    i_center=i;
                                    iflag=1;
                                    for(;i_center>=0;i_center--)
                                    {	
                                        visvalMid[i_center]=visvalMid[i_center+1];//中线固定，左右边界继续找
                                    }
				
                              }

                          }
		}
           //    img[i][left  [i]]=128; // 
           //    img[i][right[i]]=128; //
           //    img[i][visvalMid[i]]=100;//每行计算完中值后统一赋值，避免对i行0列赋值，即没有中值


//无效行判断
		   wuxiaohang_flag=0;
		   if(left[i]>=right[i]-initcenter)  //缩一半
		   {
			    sum=0;
			    for(j=left[i];j<right[i];j++)
                            {
					if(img[i-1][j]!=0 && img[i-1][j]!=100)
					{
						
						break;
					}
					else
						sum++;
                            }
                            if(sum==right[i]-left[i] && i)
                            {
				wuxiaohang=i-1;
				wuxiaohang_flag=1;

				break;
                            }
		   
		   }	
		
	}	
	if(wuxiaohang_flag)
	{
		for(i=i-1;i>=0;i--)
		{
		    visvalMid[i]=visvalMid[i+1];
                    left[i]=left[i+1];//
                    right[i]=right[i+1];//
                   // img[i][left[i]]=128; // 
                   // img[i][right[i]]=128; //
                    //img[i][visvalMid[i]]=100;//		
		}	
	}
}

void cleanpoint()     //除噪
{
  int CCD_V,CCD_H;
   for(CCD_V=1;CCD_V<CAMERA_H-1;CCD_V++)       //整场去噪
    for(CCD_H=1;CCD_H<CAMERA_W-1;CCD_H++)
    {
      if(img[CCD_V][CCD_H]==white)
      {  
        if((img[CCD_V-1][CCD_H]==white ||img[CCD_V+1][CCD_H]==white) && (img[CCD_V][CCD_H-1]==white || img[CCD_V][CCD_H+1]==white))
        {
              img[CCD_V][CCD_H]=white; 
        }
         else 
        {
              img[CCD_V][CCD_H]=0;
        }
      }
      if(img[CCD_V][CCD_H]==0)
      {
         if((img[CCD_V-1][CCD_H]==0 || img[CCD_V+1][CCD_H]==0) && (img[CCD_V][CCD_H-1]==0 || img[CCD_V][CCD_H+1]==0))
        {
               img[CCD_V][CCD_H]=0; 
        }
         else  
        {
              img[CCD_V][CCD_H]=white;
        }

      }
    }
}