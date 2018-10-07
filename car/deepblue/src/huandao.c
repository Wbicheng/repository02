#include "common.h"
#include "include.h"
#include "huandao.h"

uint8   huandao1flag_right;
uint8	huandao2flag_right;
uint8	huandao1flag_left;
uint8	huandao2flag_left;
uint8	heitiaobian;                             //�������
uint8	baitiaobian;                             //�������
uint8   heitiaobianhang_right[3];                 //�Һ�������
uint8   heitiaobianhang_left[3];                  //���������
uint8   baitiaobianhang_right[3];                //�Ұ�������
uint8   baitiaobianhang_left[3];                 //���������
uint8   zhidaohuandao2flag;                      //ֱ������2��־λ
uint8   chuhuandaoflag_right;                    //���һ�����־
uint8   chuhuandaoflag_left;                      //���󻷵���־
uint8   huandao1[maxsize]={0};                  //ѭ������
uint8   nowpoint=0;                              //ѭ������ĵ�ǰָ��
uint8   prepoint=0;                             //vsynnum����ǰ��ָ��
uint8   huandao1num=0;                            //vsynnum����Ҫ�������һ������
uint16  huandaonum1_2_right=0;                   //�һ���1����2����  huandaocount_right
uint16  huandaonum1_2_left=0;                    //�󻷵�1����2����
uint16  huandaonum2_turn_right=0;               //�һ���2����ת�����
uint16  huandaonum2_turn_left=0;                 //�󻷵�2����ת�����
uint8   ruhuandaoflag_right=0;                   //���һ�����־
uint8   ruhuandaoflag_left=0;                    //���󻷵���־
uint16  rudaonum_right=0;                       //�һ���2ת����ʱ����
uint16  rudaonum_left=0;                        //�󻷵�2ת����ʱ����
uint16  chudaonum_right=0;                      //���һ�������
uint16  chudaonum_left=0;                       //���󻷵�����
uint16  vsynnum=10;                             //ȷ������1��ɨ�賡��
uint16  huandaocount_right;                     //�һ�������
uint16  huandaocount_left;                      //�󻷵�����
uint8   xieruhuandaoflag_right;                 //б���һ�����־
uint8   xieruhuandaoflag_left;                  //б���󻷵���־
uint8 heitiaobianlienum;                                  //����������  
uint8 baitiaobianlienum;				        //���������� 
uint8 baitiaobianlie_leftest;                             //����İ����������� 
uint8 heitiaobianlie_rightest;                            //���ҵĺ�����������  
uint8 kongbaihang;                                        //�հ���
uint8 kongbaihang_flag;                                   //���ұ߽����ڿհ��б�־  
uint8 yuandihang;                                         //Բ�ĵ���  
uint8 yuandihang_flag;                                    //����Բ���� 
uint8 yuanlie;                                            //������˫ʮ�ֵ�����--Բ���ж�б��ʱ��
uint8 yuanlie_ruhuandao;                                  //�뻷��ʱ������б�뻷��ʱ���룬������Բ������
float   K_huandao;                                      //б�뻷��б��
float   huandaoMid;                                     //б�뻷������
uint8 baitiaobianhang_right_col[CAMERA_W]={0};//�һ���1�а�������
uint8 baitiaobianhang_left_col[CAMERA_W]={0};//�󻷵�1�а�������
uint8 shangbanyuancount_right;	//�һ����ϰ�Բ�½�������
uint8 shangbanyuancount_left;	//�󻷵��ϰ�Բ�½�������
uint8 shangbanyuancount_right_up;//�һ����ϰ�Բ����������
uint8 shangbanyuancount_left_up;//�󻷵��ϰ�Բ����������
uint8 tiaobianhang_right_hd;    //�һ����ұ߽�������
uint8 tiaobianhang_left_hd;     //�󻷵���߽�������

//�󻷵�
uint8 dahuandaoflag_left=0;     //��󻷵�  ������
uint8 dahuandaoflag_right=0;	//�Ҵ󻷵�	������
uint8 dahuandaonum_left=0;           //�󻷵�ʶ�𵽼���
uint8 dahuandaonum_right=0;
uint8 rudahuandaoflag_left;   //����󻷵�  ......
uint8 rudahuandaoflag_right;  //���Ҵ󻷵�	......

uint8 ruhuandao_shang_i_left=0;      //�뻷���ϲ���i  �󻷵�
uint8 ruhuandao_shang_j_left=0;	//�뻷���ϲ���j
uint8 ruhuandao_xia_i_left=0;		//�뻷���²���i
uint8 ruhuandao_xia_j_left=0;		//�뻷���²���j

uint8 ruhuandao_shang_i_right=0;      //�뻷���ϲ���i  �һ���
uint8 ruhuandao_shang_j_right=0;	//�뻷���ϲ���j
uint8 ruhuandao_xia_i_right=0;		//�뻷���²���i
uint8 ruhuandao_xia_j_right=0;		//�뻷���²���j
float k_ruhuandao;        //�뻷��б��

uint16 indahuandaonum_left=0;   //���󻷵�������1.�뻷��ʱ���� 2.������ʱ����
uint16 indahuandaonum_right=0;
uint8 chudahuandaoflag_left;        //����󻷵���־
uint8 chudahuandaoflag_right;		//���Ҵ󻷵���־
uint8 chudahuandaonum_left=0;       //������������
uint8 chudahuandaonum_right=0;       //������������

uint8 rudahuandaonum_left=0;            //��󻷵�����   --���ڲ��ߡ���������������������
uint8 rudahuandaonum_right=0;		//��󻷵����� ---���ڲ��ߡ�����������������������
uint8 nearchudahuandaoflag_left;       //������������־  ������������������
uint8 nearchudahuandaoflag_right;      //������������־ ������������������
uint8	chudaodian_left_i;             //��������־�Ƚϵ�
uint8	chudaodian_right_i;	        //��������־�Ƚϵ�
uint8  nohuandaonum=0;  // ���λ�������
uint8 btowhang;   //�������ϵĺڵ��׵������� ............................................
uint8 wtobhang;   //�������ϵİ׵��׵�������..................................................

uint8 ruhuandao1num_left=0;  //���󻷵�1����
uint8 ruhuandao1num_right=0;  //���һ���1����
uint8 ruhuandao2num_left=0;//���󻷵�2����
uint8 ruhuandao2num_right=0;//���һ���2����

uint8 nearhuandaoflag_left; //�����󻷵���־
uint8 nearhuandaoflag_right;//�����һ�����־

uint8 hang20_mid=0;  //�ڻ������뻷��1���뻷��2ǰ����λ��
uint8 hang20_mid_hang=0;

uint8 heitiaobianhang_right_hd;
uint8 heitiaobianhang_left_hd;
uint8 baitiaobianhang_right_hd[CAMERA_H];
uint8 baitiaobianhang_left_hd[CAMERA_H];

uint8 baitiaobian_sum;
uint8 btowlie=0;  //��to��������     ^^^^^^^^^^^^^^^^^^^^^^
uint8 jiange_wai=0;  //�����ж�Ϊ·�� ����ļ��  ^^^^^^
uint8 jiange_nei=0;//�����ж�Ϊ·�� ���ڵļ��    ^^^^^^^^^
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

                for(i=0;i<3;i++)          //ÿ���ڰ���������0                
                {
                  heitiaobianhang_right[i]=0;                 
                  heitiaobianhang_left[i]=0;                  
                  baitiaobianhang_right[i]=0;                
                  baitiaobianhang_left[i]=0;
                } 
                
 /******************************************************����*********************************************************/


/*****************************************************��������***********************************************************/

//�����һ���
nearhuandaoflag_right=0;
if(!tiaobianflag_left && zhidaohuandaoflag  && !nohuandaonum && tiaobianflag_right) //�뻷����־��1.���������У��������� 2.32-48���ڰ���
{
	nearhuandaoflag_right=1;
	j=CAMERA_W-1;
	heitiaobian=0;  //�ұ߽�������ϴ���1��2��������㣬1���������
	baitiaobian=0;
	btowhang=0;
	wtobhang=0;
	for(i=CAMERA_H-1;i>3;i--) //�������漸�п������
	{
		if(img[i][j]==black && img[i-1][j]==white)
       {
			heitiaobian++;
			btowhang=i;  //��
		}
		if(img[i][j]==white && img[i-1][j]==black)
		{
			baitiaobian++;
			wtobhang=i;  //��
		}
	}
	if(!((baitiaobian==1 || baitiaobian==2) && heitiaobian==1))
	{
		nearhuandaoflag_right=0;
	}
        if(btowhang==0 || wtobhang==0)
                        nearhuandaoflag_right=0;
	if(nearhuandaoflag_right && wtobhang>=btowhang) //�������ϰ�����Ӧ�ں�����֮��
			nearhuandaoflag_right=0;
	if(nearhuandaoflag_right)//������������ȫ��
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
	if(nearhuandaoflag_right)//������������������ ��������һ������߽�ɨ����һ�������䣬һ��������
	{
		heitiaobian=0;
		baitiaobian=0;
		i=btowhang-1;
		btowlie=0;  //��to�������� ..................................................................
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
        if(nearhuandaoflag_right)//������λ���޶�
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
		jiange_nei--;//��Ϊ�Ӻڵ㿪ʼ��
		if(jiange_nei-jiange_wai>=4)
			nearhuandaoflag_right=0; //����������Ϊ·�ϣ��Ǽ�������
	
	}
	if(nearhuandaoflag_right) //������s���ͻ�����½�Ϊ����������
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
//�����󻷵�
nearhuandaoflag_left=0;
if(!tiaobianflag_right && zhidaohuandaoflag && !nohuandaonum  && tiaobianflag_left) //�뻷����־��1.����������  2.32-48���ڰ���  3.������  //////////////////////////
{
	nearhuandaoflag_left=1;
	j=0;
	heitiaobian=0;  //�ұ߽�������ϴ���1��2��������㣬1���������
	baitiaobian=0;
	btowhang=0;
	wtobhang=0;
	for(i=CAMERA_H-1;i>3;i--) //�������漸�п������
	{
		if(img[i][j]==black && img[i-1][j]==white)
       {
			heitiaobian++;
			btowhang=i;  //��
		}
		if(img[i][j]==white && img[i-1][j]==black)
		{
			baitiaobian++;
			wtobhang=i;  //��
		}
	}
	if(!((baitiaobian==1 || baitiaobian==2) && heitiaobian==1))
	{
		nearhuandaoflag_left=0;
	}
        if(btowhang==0 || wtobhang==0)
                        nearhuandaoflag_left=0;
	if(nearhuandaoflag_left && wtobhang>=btowhang) //�������ϰ�����Ӧ�ں�����֮��
			dahuandaoflag_left=0;
	if(nearhuandaoflag_left)//������������ȫ��
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
	if(nearhuandaoflag_left)//������������������ ��������һ�����ұ߽�ɨ����һ�������䣬һ��������
	{
		heitiaobian=0;
		baitiaobian=0;
		i=btowhang-1;
		btowlie=0;  //��to�������� ..................................................................
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
        if(nearhuandaoflag_left)//������λ���޶�
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
		jiange_nei--;//��Ϊ�Ӻڵ㿪ʼ��
		if(jiange_nei-jiange_wai>=4)
			nearhuandaoflag_left=0; //����������Ϊ·�ϣ��Ǽ�������
	
	}
	if(nearhuandaoflag_left) //������s���ͻ�����½�Ϊ����������
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

  //ѭ���������㣺
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
         if(huandao1num>=5)   //10�����������3������1����
        {
           if(nearhuandaoflag_left) 
            dahuandaonum_left=50;//�뻷����������ʱ��
           if(nearhuandaoflag_right) 
            dahuandaonum_right=50;//�뻷����������ʱ��        
        }
 /*       if(huandao1num>=3)   //10�����������3������1����
        {
           if(huandao1flag_left) 
            huandaonum1_2_left=20;//�󻷵�����������ʱ��
           if(huandao1flag_right) 
            huandaonum1_2_right=20;//�һ�������������ʱ��
            if(xieruhuandaoflag_left)
             huandaonum1_2_left=50;//�󻷵�����������ʱ��
           if(xieruhuandaoflag_right)
             huandaonum1_2_right=50;//�󻷵�����������ʱ��           
        }
   */
/***********************************************************�뻷��1***********************************************************************////////////��ʹ��

//ԭС��������1+ԭ�󻷵�ʶ��

/********************************************ԭС��������1************************************************/  //�뻷��1
//б���һ����ж�
/*	xieruhuandaoflag_right=0;
	if(!wuxiaohang_flag && tiaobianflag_right &&(!tiaobianflag_left||(tiaobianhang_left<=3)) ) 
	{		//��������������Ч�л���Ч�нϸߣ�����߽��������������С��3�У�������㣩���ұ߽�������
		                           				
	    kongbaihang=0;
		for(i=3;i<30;i++)//�ҿհ���
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
		heitiaobianlie_rightest=0; //ÿ����������
		if(kongbaihang_flag)
		{
			for(i=0;i<kongbaihang;i++) //���˵�ǰ���е����,Բ����Χ��0��30�䣬���ⲻ����Բ�����ʰ׵��в���Ϊ3
			{
				heitiaobianlienum=0;
				baitiaobianlienum=0;
				for(j=left[i]+1;j<right[i]-3;j++) //��3��30�е�����㣬�ж��Ƿ�����Բ������������ȡԲ�����ұ߽������,ȡΪ�ұ߽���3�б������
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

				if(baitiaobianlienum!=1||heitiaobianlienum!=1)//Բ�������������������һ���ס��ڣ�һ���ڡ���
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
			
		if(heitiaobianlie_rightest==0)//Բ�ұ߽粻����
			xieruhuandaoflag_right=0;
                if(xieruhuandaoflag_right)//�ڵ�0�е�2������ӦΪȫ�ף�������˫ʮ��/�뵥ʮ�ֳ�ͻ
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
			for(j=left[yuandihang+1]+1;j<=right[yuandihang+1]-1;j++) //Բ�������ұ߽��Ϊ��
			{
				if(img[yuandihang+1][j]==black)
				{
					xieruhuandaoflag_right=0;
					break;
				}
			}
		}
	
		if(xieruhuandaoflag_right)	//Բ�ұ߽�����ɨҪ�кڰ�����
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
			if(baitiaobian!=1||heitiaobian>=2) //Բ��߽��ްס�������϶�������;�ڡ����������1��
			{
				xieruhuandaoflag_right=0;
			
			}

		
		
		}
		if(xieruhuandaoflag_right)//Բ��߽�����ɨȫΪ��
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
		if(xieruhuandaoflag_right)//����Բ�ϱ߽���ɨ��Ҫ�а�����㣬�����˫ʮ�ֳ�ͻ
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
//б�뻷������
  /**	if(xieruhuandaoflag_right)
	{
		K_huandao=(initcenter-visvalMid[0])/(float)CAMERA_H;
		huandaoMid=initcenter-K_huandao*(CAMERA_H-standardrow);
	}
    **/
        
        
//б���󻷵��ж�
/*	xieruhuandaoflag_left=0;
	if(!wuxiaohang_flag && tiaobianflag_left &&(!tiaobianflag_right||(tiaobianhang_right<=3)) ) 
	{		//��������������Ч�У����ұ߽��������������С��3�У���߽�������		                           						
	    kongbaihang=0;
		for(i=3;i<30;i++)//�ҿհ���
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
		heitiaobianlie_rightest=0; //ÿ����������
		if(kongbaihang_flag)
		{
			for(i=0;i<kongbaihang;i++) //���˵�ǰ���е����,Բ����Χ��0��30�䣬���ⲻ����Բ�����ʰ׵��в���Ϊ3
			{
				heitiaobianlienum=0;
				baitiaobianlienum=0;
				for(j=left[i]+1;j<right[i]-3;j++) //��3��30�е�����㣬�ж��Ƿ�����Բ������������ȡԲ�����ұ߽������,ȡΪ�ұ߽���3�б������
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
				if(baitiaobianlienum!=1||heitiaobianlienum!=1)//Բ�������������������һ���ס��ڣ�һ���ڡ���
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
			
		if(heitiaobianlie_rightest==0)//Բ�ұ߽粻����
			xieruhuandaoflag_left=0;
                if(xieruhuandaoflag_left)//��β�е�2������ӦΪȫ�ף�������˫ʮ��/�뵥ʮ�ֳ�ͻ
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
			for(j=left[yuandihang+1]+1;j<=right[yuandihang+1]-1;j++) //Բ�������ұ߽��Ϊ��
			{
				if(img[yuandihang+1][j]==black)
				{
					xieruhuandaoflag_left=0;
					break;
				}
		
			}
		}
	
		if(xieruhuandaoflag_left)	//Բ��߽�����ɨҪ�кڰ�����
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
			if(baitiaobian!=1||heitiaobian>=2) //Բ��߽��ްס�������϶�������;�ڡ����������1��
			{
				xieruhuandaoflag_left=0;
			
			}
		}
		if(xieruhuandaoflag_left)//Բ�ұ߽�����ɨȫΪ��
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
		if(xieruhuandaoflag_left)//����Բ�ϱ߽���ɨ��Ҫ�а�����㣬�����˫ʮ�ֳ�ͻ
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
//б�뻷������
/**	if(xieruhuandaoflag_left)
	{
		K_huandao=(visvalMid[0]-initcenter)/(float)CAMERA_H;
		huandaoMid=initcenter+K_huandao*(CAMERA_H-standardrow);
	}
 **/   
//dahuandaonum_right=1;//������        
	//�һ���1�ж�
/*	huandao1flag_right=0;
	if(!wuxiaohang_flag && !tiaobianflag_left && tiaobianflag_right 
           &&   zhidaohuandaoflag && tiaobianhang_right<20  && dahuandaonum_right) 
	{							     //����1����������Ч�л���Ч�нϸߣ�����߽������䣬�ұ߽�������,����ȫ��һ��
		huandao1flag_right=1;				  //����2��������������һ��������㣬�����������
		//for(j=CAMERA_W-1;j>CAMERA_W-3;j--)    //��������ɨ�ڰ������ ɨ���ұ�����
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
			if(baitiaobian!=1 || heitiaobian!=2 || heitiaobianhang_right[0]>15 ||	heitiaobianhang_right[1]<20		//����4���ڰ�����������һ����Χ
				|| heitiaobianhang_right[1]>=50 || baitiaobianhang_right[0]<5	|| baitiaobianhang_right[0]>25)
			{
				huandao1flag_right=0;
				//break;
			}
			if(huandao1flag_right)
			{
				for(j=CAMERA_W-1;j>CAMERA_W-40;j--)
				{
					baitiaobianhang_right_col[j]=0;		//���а�������
				}
				for(j=CAMERA_W-1;j>CAMERA_W-40;j--)   //����3���ϰ�Բ�������������½��Ļ���
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
					if(i==CAMERA_H-1)				//�����Ҳ����������������ѭ��
						break;
				}
				/*if(j<=CAMERA_W-35)
					huandao1flag_right=0;	*/		//���ڰ������е�����<=45������
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
	//�󻷵�1�ж�
//dahuandaonum_left=1;//������  
/*        huandao1flag_left=0;
	if(!wuxiaohang_flag && tiaobianflag_left && !tiaobianflag_right
           &&zhidaohuandaoflag && tiaobianhang_left<15  && dahuandaonum_left) 
	{				//����1����������Ч�л���Ч�нϸߣ����ұ߽������䣬��߽�������	,����ȫ��һ��					
		huandao1flag_left=1;	//����2��������������һ��������㣬�����������
	//	for(j=0;j<2;j++)	//��������ɨ�ڰ������ 
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
				baitiaobianhang_left_col[j]=0;		//���а�������
                          }
                          for(j=0;j<41;j++)               //����4���ϰ�Բ��������Ҵ����½��Ļ���
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
				if(i==CAMERA_H-1)				//�����Ҳ����������������ѭ��
					break;
			}
                     /*   if(j>=35)
				huandao1flag_left=0;	*/		//���ڰ������е�����>=35������
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
if(huandao1flag_left)  //�뻷��1����ֵ
  ruhuandao1num_left=15;
if(huandao1flag_right)  //�뻷��1����ֵ
  ruhuandao1num_right=15; 
*/
        //ѭ���������㣺
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
        if(huandao1num>=3)   //10�����������2������1����
        {
           if(huandao1flag_left) 
            huandaonum1_2_left=20;//�󻷵�����������ʱ��
           if(huandao1flag_right) 
            huandaonum1_2_right=20;//�һ�������������ʱ��
            if(xieruhuandaoflag_left)
             huandaonum1_2_left=50;//�󻷵�����������ʱ��
           if(xieruhuandaoflag_right)
             huandaonum1_2_right=50;//�󻷵�����������ʱ��           
        }
*/
                
//ԭС��������2   
        //�һ���2�ж�
/*       huandao2flag_right=0;
	if((wuxiaohang<=CAMERA_H/15 || !wuxiaohang_flag) && !tiaobianflag_left && tiaobianflag_right && zhidaohuandao2flag && huandaonum1_2_right && tiaobianhang_right<20) 
	{						//����1����������Ч�л���Ч�нϸߣ�����߽������䣬�ұ߽�������,��Ч�����´���ȫ��һ��
		huandao2flag_right=1;			//����2�������ж�������һ��������㣬һ���������
	//	for(j=CAMERA_W-1;j>CAMERA_W-3;j--)      //��������ɨ�ڰ������
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
 //���һ���
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
            if(tiaobianhang_right_hd>=12 && tiaobianhang_right_hd<=25)		//����1���ұ߽�����������һ����Χ
            {  
              ruhuandaoflag_right=1;
               if(ruhuandaoflag_right)						//����2��������߽�����ȫ����
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
                if(ruhuandaoflag_right)				//����3:�����ұ߽�����������ȫ��
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
                  huandaonum1_2_right=0;          //�ҵ�ת��㣬�������
                  rudaonum_right=15;              //ת����ʱ
                  chudaonum_right=500;
         } 
       }

        
 //���һ����ж�
	chuhuandaoflag_right=0;
	if(visvalMid[standardrow]==initcenter && wuxiaohang>=CAMERA_H/4 && chudaonum_right)
	{                                                       //����һ����ǰֱ������Ч�нϵͣ�֮ǰ���ֹ��һ���
		for(i=CAMERA_H-1;i>35;i--)                      //�������������15��ȫ��
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

        //ÿ���������Լ�
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
        
/******************�󻷵�*****************/
        //�󻷵�2�ж�
/*       huandao2flag_left=0;
	if((wuxiaohang<CAMERA_H/15 || !wuxiaohang_flag) && tiaobianflag_left && !tiaobianflag_right &&zhidaohuandao2flag && huandaonum1_2_left  && tiaobianhang_left<20) 
	{				//����1����������Ч�л���Ч�нϸߣ����ұ߽������䣬��߽�������,��Ч�����´���ȫ��һ��
		huandao2flag_left=1;	//����2�������ж�����һ��������㣬һ���������
	//	for(j=0;j<2;j++)	//��������ɨ�ڰ������
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
            /*for(i=0;i<CAMERA_H-1;i++)                   //ɨ�����к�������
            {
              j=0;
              if(img[i][j]==black && img[i+1][j]==white && img[i+2][j]==white)
              {
                heitiaobianhang_left=i;
                break;
              }
            }*/
            
//���󻷵�
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
          if(tiaobianhang_left_hd>=12 && tiaobianhang_left_hd<=25)		//����1����߽�����������һ����Χ
          {  
                ruhuandaoflag_left=1;
               if(ruhuandaoflag_left)										//����2��������߽�����ȫ����
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
			   if(ruhuandaoflag_left)										//����3:�����ұ߽�����������ȫ��
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
                  huandaonum1_2_left=0;            //�ҵ�ת��㣬�������
                  rudaonum_left=15;                //ת����ʱ
                  chudaonum_left=500;
               
               }
          }

//���󻷵��ж�
	chuhuandaoflag_left=0;
	if(visvalMid[standardrow]==initcenter && wuxiaohang>=CAMERA_H/4 && chudaonum_left )
	{                                                       //����һ����ǰֱ������Ч�нϵͣ�֮ǰ���ֹ��󻷵�
		for(i=CAMERA_H-1;i>35;i--)                      //�������������15��ȫ��
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
       
        //ÿ���������Լ�
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

/***********************************************ԭ�󻷵�ʶ��************************************************/  //�뻷��1
//��󻷵�
//dahuandaonum_left=2;//����
/*dahuandaoflag_left=0;
if(!wuxiaohang_flag && zhidaohuandaoflag && !tiaobianflag_right  && tiaobianflag_left &&(tiaobianhang_left<=2)
&& img[CAMERA_H/2][0]!=white && left[20]<=15  && dahuandaonum_left) 
//�󻷵��жϣ�1.����Ч�� 2.�м伸��Ϊ�� 3.�ұ����������� 4.��������С��2 5.30����߽�Ϊ�� 6.20����߽�С��15�� 5.6���ڹ��С����
//if(!wuxiaohang_flag && zhidaohuandaoflag && !tiaobianflag_right 
 //&&(tiaobianhang_left<=2) && tiaobianflag_left && dahuandaonum_left) //�󻷵��жϣ�1.����Ч�� 2.�м伸��Ϊ�� 3.�ұ����������� 4.��������С��2
{
	dahuandaoflag_left=1;
}
if(dahuandaoflag_left)
{
	heitiaobian=0;
	baitiaobian=0;
	j=0;//��0����һ�������䣬һ��������������
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
if(dahuandaoflag_left)//��0�е���߽�ȫ��
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
	for(i=CAMERA_H-1;i>0;i--)  //���������Ұ�-������� �˴�����btownum������������Ϊ��λ��
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
//�Ҵ󻷵�
//dahuandaonum_right=2;//������
dahuandaoflag_right=0;
if(!wuxiaohang_flag && zhidaohuandaoflag && !tiaobianflag_left 
&& tiaobianflag_right &&(tiaobianhang_right<=2)
&& img[CAMERA_H/2][CAMERA_W-1]!=white && right[20]>=65 && dahuandaonum_right) 
//�󻷵��жϣ�1.����Ч�� 2.�м伸��Ϊ�� 3.������������� 4.��������С��2 5.30�б߽粻Ϊ�� 6.20���ұ߽����65(���С����)
//if(!wuxiaohang_flag && zhidaohuandaoflag && !tiaobianflag_left  && tiaobianflag_right &&(tiaobianhang_right<=2) && dahuandaonum_right) //�󻷵��жϣ�1.����Ч�� 2.�м伸��Ϊ�� 3.������������� 4.��������С��2
{
	dahuandaoflag_right=1;
}
if(dahuandaoflag_right)
{
	heitiaobian=0;
	baitiaobian=0;
	j=CAMERA_W-1;//��0����һ�������䣬һ��������������
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
if(dahuandaoflag_right)//��0���ұ߽��ߵ��ұ߽�ȫ��
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
	for(i=CAMERA_H-1;i>0;i--)  //���������Ұ�-������� �˴�����btownum������������Ϊ��λ��
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

if(dahuandaoflag_left)  //�뻷��1����ֵ
  ruhuandao1num_left=15;
if(dahuandaoflag_right)  //�뻷��1����ֵ
  ruhuandao1num_right=15;
*/
/************************************************�뻷��2********************************************************/
//ԭ��󻷵�   && dahuandaonum_right && !ruhuandao1num_right && !ruhuandao1num_left
//����󻷵�
/*rudahuandaoflag_left=0;  
//dahuandaonum_left=1;//////////////////////////////������
//if(wuxiaohang<=10 && tiaobianflag_left && lianxuhangnum_right>=40 && dahuandaonum_left)//����󻷵�������1.��Ч��С��10��2.�������; 3.�ұ�����һ������
if(wuxiaohang<=10 &&(lianxuhangnum_left>=40 || tiaobianflag_left) && lianxuhangnum_right>=40 && dahuandaonum_left && !rudaonum_left)//����󻷵�������1.��Ч��С��10��2.������������һ������; 3.�ұ�����һ������) 4.��С������־����Ч��������С����
{
	i=40;
        rudahuandaoflag_left=1;
	for(j=0;j<right[i]-1;j++) //�м��40��0���ұ߽�ȫ��
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
	for(i=CAMERA_H/2;i<CAMERA_H;i++)//�ӵ�30�п�ʼ����0�����right[30]������Ϊ��
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
		rudahuandaoflag_left=0;//�Ҳ����ϲ���
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
	if(ruhuandao_xia_i_left-ruhuandao_shang_i_left<=1 || ruhuandao_xia_j_left>=65)//�²��������������65
		rudahuandaoflag_left=0;
	
}
if(rudahuandaoflag_left) 
{
 // dahuandaonum_left=0;
  rudahuandaonum_left=10;

}



//���Ҵ󻷵�
rudahuandaoflag_right=0;  
//dahuandaonum_right=1;///////////////////////////////����
//if(wuxiaohang<=10 && tiaobianflag_right && lianxuhangnum_left>=40 && dahuandaonum_right)//���Ҵ󻷵�������1.��Ч��С��10�У�2.�������һ������; 3.�ұ�����
if(wuxiaohang<=10 &&(lianxuhangnum_right>=40 || tiaobianflag_right) && lianxuhangnum_left>=40 && dahuandaonum_right  && !rudaonum_right)//���Ҵ󻷵�������1.��Ч��С��10�У�2.�������һ������; 3.�ұ����������һ��  4.��С������־��Чʱ����󻷵�
{
	i=40;
        rudahuandaoflag_right=1;
	for(j=left[i]+1;j<CAMERA_W;j++) //�м��35��0���ұ߽�ȫ��
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
	for(i=CAMERA_H/2;i<CAMERA_H;i++)//�ӵ�30�п�ʼ����0�����right[30]������Ϊ��
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
if(rudahuandaoflag_right )//������󻷵����ж�����֮һ�����ǵ�  Ҳ��Ϊ�������²���
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
		rudahuandaoflag_right=0;//�Ҳ����ϲ���
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
	if(ruhuandao_xia_i_right-ruhuandao_shang_i_right<=1 || ruhuandao_xia_j_right<=15) //�²������������С��15��
		rudahuandaoflag_right=0;
	
}

if(rudahuandaoflag_right)  //...........................................
{
 // dahuandaonum_right=0;
  rudahuandaonum_right=10;
}
*/
//���뻷��2�㷨

//���һ���1
    //    dahuandaonum_right=2;//������
	for(i=0;i<3;i++)
	{
		baitiaobianhang_right[i]=0;
		heitiaobianhang_right[i]=0;
	}
	huandao1flag_right=0;
	if(!wuxiaohang_flag && !tiaobianflag_left && tiaobianflag_right  &&	zhidaohuandaoflag	&& tiaobianhang_right<20 && dahuandaonum_right)
	{										  //����1����������Ч�л���Ч�нϸߣ�����߽������䣬�ұ߽�������,����ȫ��һ��
		huandao1flag_right=1;				  //����2��������������һ��������㣬�����������																					
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
				   //����3���ڰ�����������һ����Χ
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
        //̫�����޸Ĵ˲���  huandao1flag_right=0;

//���󻷵�1
    //      dahuandaonum_left=2;//������
	for(i=0;i<3;i++)
	{
		baitiaobianhang_left[i]=0;
		heitiaobianhang_left[i]=0;
	}
	huandao1flag_left=0;
	if(!wuxiaohang_flag && tiaobianflag_left && !tiaobianflag_right  &&	zhidaohuandaoflag	&& tiaobianhang_left<20 && dahuandaonum_left) 
	{										  //����1����������Ч�л���Ч�нϸߣ�����߽������䣬�ұ߽�������,����ȫ��һ��
		huandao1flag_left=1;				  //����2��������������һ��������㣬�����������																					
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
				   //����3���ڰ�����������һ����Χ
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
        //̫�����޸Ĵ˲���  huandao1flag_left=0;
        
if(huandao1flag_left)
ruhuandao2num_left=10;
if(huandao1flag_right)
ruhuandao2num_right=10;


/***********����**************/
/*
if(rudahuandaonum_right) //���һ�������******************************  //..................................
{	
	if((img[CAMERA_H-1][CAMERA_W-2]==black)|| (lianxuhangnum_left>=32 && img[48][1]==black))//�ο��������󻷵�����ԭ��
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
if(rudahuandaonum_left) //���󻷵�����
{	
	if((img[CAMERA_H-1][2]==black)|| (lianxuhangnum_right>=32 && img[48][CAMERA_W-2]==black))	//�ڻ����б�־�������ٽ����뻷�����ߣ�	
	{
		rudahuandaonum_left=2;//���ڻ���������ʼ																			//1.��߳��ֺڣ�����ͷ�ˣ��ý��뻷����
		//indahuandaonum_left=200;  														//2.�ұ������д���32���ˣ������ұ�48Ϊ���ˣ��������ٲ��ˣ�����֤�����ܻᲹ�߲�����
	}																									//�����2���ұ�48Ϊ������뻷���������������48Ϊ�׶�Ӧ�������뻷��ʱʶ�𵽳�����
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

/********************���󻷵�*******************/ 
nearchudahuandaoflag_left=0;
nearchudahuandaoflag_right=0;
//indahuandaonum_left=1;/////������
//indahuandaonum_right=1;/////������
//��������󻷵�
if(indahuandaonum_left && lianxuhangnum_right<=50 && (indahuandaonum_left<=190) )  //С��28Ҳ����
{
	nearchudahuandaoflag_left=1;
	j=0;
	for(i=CAMERA_H/2;i<CAMERA_H;i++) //��߽��30�е�����Ϊ��
	{
		if(img[i][j]==black)
		{
			nearchudahuandaoflag_left=0;
			break;
		}
	}
	if(nearchudahuandaoflag_left)
	{
		btownum=0;  //��60��23�д��ںڵ��׵�1�������
		for(i=CAMERA_H-1;i>=3;i--)
		{
			if(img[i][CAMERA_W-1]==black && img[i-1][CAMERA_W-1]==white)
				btownum++;
		}		
		if(btownum!=1)
			nearchudahuandaoflag_left=0;
	}
}

//�������Ҵ󻷵�
if(indahuandaonum_right && lianxuhangnum_left<=50 && (indahuandaonum_right<=190))
{
	nearchudahuandaoflag_right=1;
	j=CAMERA_W-1;
	for(i=CAMERA_H/2;i<CAMERA_H;i++) //��߽��30�е�����Ϊ��
	{
		if(img[i][j]==black)
		{
			nearchudahuandaoflag_right=0;
			break;
		}
	}
	if(nearchudahuandaoflag_right)
	{
		btownum=0;  //��60��23�д��ںڵ��׵�1�������
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
//���󻷵�
chudahuandaoflag_left=0;
chudahuandaoflag_right=0;
//����󻷵�
if(indahuandaonum_left && img[48][0]==white && img[48][CAMERA_W-1]==white && (indahuandaonum_left<=190) && wuxiaohang_flag)
{
	chudahuandaoflag_left=1;
	i=35;
	for(j=0;j<CAMERA_W;j++) //35�к͵���ȫ��
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
		for(i=48;i<CAMERA_H;i++)  //�ұ߽�48-60��Ϊ��
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
		for(i=CAMERA_H/2;i<CAMERA_H;i++) //��߽�30-60��Ϊ��
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

//���Ҵ󻷵�
//nearchudahuandaoflag_right=0;//
if(indahuandaonum_right && img[48][0]==white && img[48][CAMERA_W-1]==white && (indahuandaonum_right<=190) && wuxiaohang_flag)
{ 
	chudahuandaoflag_right=1;
	i=35;
	for(j=0;j<CAMERA_W;j++) //35�к͵���ȫ��
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
		for(i=CAMERA_H/2;i<CAMERA_H;i++)  //�ұ߽�30-60��Ϊ��
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
		for(i=48;i<CAMERA_H;i++) //��߽�48-60��Ϊ��
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

/********************С����������*************************/
//chudaonum_left=1;//����
//���󻷵��ж�
	chuhuandaoflag_left=0;
	if(visvalMid[38]==initcenter && wuxiaohang>=CAMERA_H/4 && chudaonum_left )
	{                                                       //����һ����ǰֱ������Ч�нϵͣ�֮ǰ���ֹ��󻷵�
		for(i=CAMERA_H-1;i>35;i--)                      //�������������15��ȫ��
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
//chudaonum_right=1;//����
 //���һ����ж�
	chuhuandaoflag_right=0;
	if(visvalMid[38]==initcenter && wuxiaohang>=CAMERA_H/4 && chudaonum_right)
	{                                                       //����һ����ǰֱ������Ч�нϵͣ�֮ǰ���ֹ��һ���
		for(i=CAMERA_H-1;i>35;i--)                      //�������������15��ȫ��
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
/******************����������*************************/
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

/******************�뻷��ǰ���е�****************************/
//�һ����ҵ�                                                            //�ĵ�0���е�
hang20_mid=0;
hang20_mid_hang=i;
if(dahuandaonum_right && !tiaobianflag_left)
{
	j=CAMERA_W-1;//������2��ʶ�𣬱������
	wtobhang=0;
	for(i=CAMERA_H-1;i>2;i--)
	{
		if(img[i][j]==white && img[i-1][j]==black)
		{
			wtobhang=i-1;
			break;		
		}	
	}	
	if(wtobhang==0) //����ɨ����
		wtobhang=CAMERA_H-1;
	for(i=wtobhang;i>0;i--)
		if(right[i-1]>right[i])
			break; 
	for(j=left[i];j<CAMERA_W-1;j++)//�����е�
	{
		if(img[i][j]==white && img[i][j+1]==black)
				break;
	}
	hang20_mid=(left[i]+j+1)/2;
        hang20_mid_hang=i;
}

//�󻷵��ҵ�
if(dahuandaonum_left  && !tiaobianflag_right)
{
	j=0;//��3��ʶ�𣬱������
	wtobhang=0;

	for(i=CAMERA_H-1;i>2;i--)
	{
		if(img[i][j]==white && img[i-1][j]==black)
		{
			wtobhang=i;
			break;		
		}	
	}	
	if(wtobhang==0) //����ɨ����
		wtobhang=CAMERA_H-1;
	for(i=wtobhang;i>0;i--)
                if(left[i-1]<left[i])
                    break; 
	for(j=right[i];j>0;j--)//�����е�
	{
		if(img[i][j]==white && img[i][j-1]==black)
				break;		
	}	
	hang20_mid=(right[i]+j-1)/2;
        hang20_mid_hang=i;
}




/******************����ֵ����***********************/
if(ruhuandao1num_left==1 || ruhuandao2num_left==1 )
{
indahuandaonum_left=200;
chudaonum_left=250;//��ȥ����
}

if(ruhuandao1num_right==1 || ruhuandao2num_right==1)
{
indahuandaonum_right=200;
chudaonum_right=250;//��ȥ����
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
    nohuandaonum=100;    //��������һ��ʱ�����λ����ж�
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

if(ruhuandao1num_right || ruhuandao2num_right)  //�뻷��ʱ�뻷������
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
