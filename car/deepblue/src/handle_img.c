#include "common.h"
#include "include.h"
#include "handle_img.h"

int8 width[CAMERA_H]={24,25,26,28,29,31,32,33,35,36,37,39,39,41,42,43,45,46,48,49,50,51,52,54,
55,56,56,58,59,60,62,62,64,64,66,66,68,68,70,71,72,73,75,75,75,77,77,79,79,79,79,79,79,79,79,79,79,79,79,79};

void handle_img()
{
 // cleanpoint();             //除噪
  get_center();             //中线提取
  zhidao();                 //直道识别
  if(stop_enableflag)//过渡一定场数后开始识别
  {
  //    if(allow_quickstop_flag==0) //急停标志位生效后不再识别急停，即不清理
      if(quickstop_flag==0)
        quick_stop();             //急停识别
  //    else quickstop_flag=0;   //允许急停标志位生效时下一场清掉急停识别标志位，故蜂鸣器警报只有一次
      if(endflag==0)
        wd_zd();                  //弯道与终点识别  
  }
  
  /******************赛道宽度补线****************/
 /* if(wuxiaohang_flag && (youwanflag || zuowanflag))
  {
    for(i=10;i<=wuxiaohang;i++)
    {
      if(visvalMid[wuxiaohang+2]<40)
      {
	right[i]=0;
      }
      if(visvalMid[wuxiaohang+2]>40)
      {    
        left[i]=CAMERA_W-1;
      }
    }
    for(i=10;i<=50;i++)
    {
	if(left[i]!=0 && right[i]==CAMERA_W-1)
	{
		right[i]=left[i]+width[i];
	}
	if(left[i]==0 && right[i]!=CAMERA_W-1)
	{
		left[i]=right[i]-width[i];
	}
	visvalMid[i]=(right[i]+left[i])/2;
	if(visvalMid[i]<0)
		visvalMid[i]=0;
	if(visvalMid[i]>=CAMERA_W-1)
		visvalMid[i]=CAMERA_W-1;
	img[i][visvalMid[i]]=100;
    }
  }*/
}

