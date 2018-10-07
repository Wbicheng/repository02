#include "common.h"
#include "include.h"
#include "zhidao.h"

uint8 zhidaoflag;
uint8 tiaobianflag_left;
uint8 tiaobianflag_right;
uint8 tiaobianhang_right;
uint8 tiaobianhang_left;
uint8 zhidaohuandaoflag;
int whitesum;
uint8 widthsum;
/******�յ���******/
uint8 stop_enableflag=0;
uint8 stop_flag=0;//�յ��߱�־
uint16 zdnum=0; //ǰ���ٳ�������ʶ��
uint8 btownum=0;//�ض��еĺڰ�����

uint8 lianxuhangnum_left; //��������
uint8 lianxuhangnum_right;


void zhidao()
{
  	zhidaoflag=0;
	tiaobianflag_left=0;
	tiaobianflag_right=0;
        tiaobianhang_left=0;
        tiaobianhang_right=0;       
	for(i=wuxiaohang+1;i<CAMERA_H-1;i++)   //ɨ��߽��Ƿ������� 
	{
		if(left[i+1]-left[i]>=5 || left[i+1]-left[i]<=-5)
		{
			tiaobianflag_left=1;
			tiaobianhang_left=i;
			break;
		}
	}
	for(i=wuxiaohang+1;i<CAMERA_H-1;i++)   //ɨ�ұ߽��Ƿ�������  
	{
		if(right[i]-right[i+1]>=5 || right[i]-right[i+1]<=-5)
		{
			tiaobianflag_right=1;
			tiaobianhang_right=i;
			break;
		}
	}
        
        /****�ӵ���������������***/           
	lianxuhangnum_left=0;
	lianxuhangnum_right=0;
	if(tiaobianflag_left)
	{
		for(i=CAMERA_H-1;i>=tiaobianhang_left;i--)
		{
			if(left[i]-left[i-1]>=5 || left[i]-left[i-1]<=-5)
				break;
			else
			lianxuhangnum_left++;
		}
	}
	else lianxuhangnum_left=CAMERA_H;
	if(tiaobianflag_right)
	{
		for(i=CAMERA_H-1;i>=tiaobianhang_right;i--)
			if(right[i]-right[i-1]>=5 || right[i]-right[i-1]<=-5)
				break;
			else 
			lianxuhangnum_right++;
	}                                    
	else lianxuhangnum_right=CAMERA_H;

	zhidaohuandaoflag=0;
	if(!wuxiaohang_flag)
	{
		for(j=32;j<=48;j++)  /////////////ԭΪ35-45
		{
			whitesum=0;
			for(i=0;i<CAMERA_H;i++)
			{
				if(img[i][j]!=black)
				{
					whitesum++;
				}
                                else
                                  break;
			}
			if(whitesum==CAMERA_H)
			{
				zhidaohuandaoflag=1;
				break;
			}
		}
	}

	if(!wuxiaohang_flag && !tiaobianflag_left && !tiaobianflag_right &&zhidaohuandaoflag)
	{
		zhidaoflag=1;
	}
        widthsum=0;
        if(zhidaoflag)
	{
		for(i=0;i<CAMERA_H-1;i++)
		{
			if(right[i]-left[i]>width[i]+8)
			{
				widthsum++;
			}
		}
		if(widthsum>5)
		{
			zhidaoflag=0;
		}
	}
        
/*        if(zhidaoflag)////////////////////////////////////////
        {
          if(visvalMid[0]<35 || visvalMid[0]>45)
              zhidaoflag=0;        
        }       
*/
        
        
        
/*        if(zhidaoflag)                          
	{
		for(i=0;i<CAMERA_H-1;i++)
		{
			if(left[i]-left[i+1]<-2 || left[i]-left[i+1]>2)
			{
				zhidaoflag=0;
				break;
			}
			if(zhidaoflag)
			{
				if(right[i]-right[i+1]<-2 || right[i]-right[i+1]>2)
				{
					zhidaoflag=0;
					break;
				}
			}
		}
	}*/
        
 //�յ���
       if(!stop_enableflag) //ǰ�ڲ�ɨ���յ�
        {
            zdnum++;
            if(zdnum==300)
            {
              stop_enableflag=1;
              zdnum=5;
            }
        }
        if(stop_enableflag)
        {
            btownum=0;
            i=48;
            for(j=0;j<=CAMERA_W-1;j++)
            {
		if(img[i][j]==white && img[i][j+1]==black)
		btownum++;
            }
            if(btownum>5)
            {
		btownum=0;
		i=52;
		for(j=0;j<=CAMERA_W-1;j++)
		{
                    if(img[i][j]==white && img[i][j+1]==black)
                    btownum++;
		}
		if(btownum>5)
                    stop_flag=1;
	}
        if(stop_flag)
        {
           if(zdnum!=0) 
              zdnum--;
        }
        }
     


        
}