#include "common.h"
#include "include.h"
#include "quick_stop.h" 

uint8 btow_i=0;//�ڵ�����������
uint8 pre_btow_i=0;//��һ�кڵ����������� ����������
uint8 quickstop_flag=0;//��ͣ��־λ
uint8 allow_quickstop_flag=0;//����ͣ��־λ
uint8 left_limit_flag=0;//��߼���Ϊ��
uint8 right_limit_flag=0;//�ұ߼���Ϊ��

void quick_stop()
{
    if(wuxiaohang<=30 && lianxuhangnum_right>18)//����һ����Ч��С��20,�ұߴӵ�����������������18///////////
    {
	quickstop_flag=0;//��ͣ��־λ
	btownum=0;//�ڵ�����������
	btow_i=0;//�ڵ�����������
	pre_btow_i=0;//��һ�кڵ����������� ����������
	if(left[CAMERA_H-2]-10>=0)//�ܿ����У��������߲�׼
		j=left[CAMERA_H-2]-10;
	else j=0;
	for(i=CAMERA_H-1;i!=20;i--) //20���ڲ�ȡ����Զ�������ֱ������
	{
		if(img[i][j]==black &&img[i-1][j]==white)
		{
			if(btow_i==0 && i<45)//���Ƶ�һ�������λ�ô���45
			{
				break;
			}
			if(btow_i!=0)
			  pre_btow_i=btow_i;	
			btow_i=i;
			if(pre_btow_i!=0 && pre_btow_i-btow_i>10) //����֮�����С��10////////
			{
				quickstop_flag=0;
				break;
			}
			btownum++;		
		}	
	}
	if(btownum==3 || btownum==4) //����������ߴ���3��4���ڵ���������
		quickstop_flag=1;
    }
    if(quickstop_flag) //����������3���ڰ������и����������Ҽ��ޱ߽�
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
 
    if(quickstop_flag) //�����ģ�����Ϊ�� �������ұ߽絽CAMERA_W-1ȫ��
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
/*    if(quickstop_flag)//�����壺�ұ߽�ֻ��һ����to������
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