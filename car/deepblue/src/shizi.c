#include "common.h"
#include "include.h"
#include "shizi.h"

uint8 maybeshiziflag;           
uint8 tiaobianhang_sz_left;     //ʮ����������
uint8 tiaobianhang_sz_right;    //ʮ����������
float K_sz;                     //ʮ�ֲ���б��
uint8 buxian_sz_down;           //ʮ���ϲ��ߵ�
uint8 buxian_sz_up;             //ʮ���²��ߵ�
uint8 error_sz;                 //ʮ�ֲ���ƫ��
uint8 tiaobianhang_nearsz_left; //����ʮ����������
uint8 tiaobianhang_nearsz_right;//����ʮ����������
uint8 nearszflag_left;          //�󿿽�ʮ�ֱ�־
uint8 nearszflag_right;         //�ҿ���ʮ�ֱ�־
uint8 startrow_nearsz;		//����ʮ��ɨ����
float K_nearsz;                 //����ʮ�ֲ���б��
uint8 maybeshiziflag_right;	//����б����ʮ�ֱ�־
uint8 maybeshiziflag_left;	//����б����ʮ�ֱ�־
uint8 shiziflag_right;		//��б��ʮ�ֱ�־
uint8 shiziflag_left;		//��б��ʮ�ֱ�־
uint8 baitiaobian_left;		//�����а������
uint8 baitiaobian_right;	//�����а������
uint8 shizinum_right;		//��б��ʮ����ʱ����
uint8 shizinum_left;		//��б��ʮ����ʱ����
uint8 whitesum_shizi;           //ʮ���м��а׵���
uint8 xiexian_shang_i;                                    //б���ϵ�(��)   --�������ж��Ƿ�б��
uint8 xiexian_shang_j;                                    //б���ϵ�(��)   --�������ж��Ƿ�б��
uint8 xiexian_xia_i;                                    //б���µ�(��)   --�������ж��Ƿ�б��
uint8 xiexian_xia_j;                                    //б���µ�(��)   --�������ж��Ƿ�б��
float xiexian_k;                                      //б��б�� 
uint8 baitiaobianhang;                                  //��-������  --�綨�ұ߲���б���ϵ�ķ�Χ
uint8 xierushizi_flag_right=0;			        //б��ʮ���ұ�־ 
uint8 xierushizi_flag_left=0;				//б��ʮ�����־ 
uint8 farszflag_right;                                  //��Զʮ�ֱ�־
uint8 farszflag_left;                                   //��Զʮ�ֱ�־
 
uint8 dixiehangnum_left=0;   //��б��ʮ�ֵ�б��    *******************
uint8 dixiehangnum_right=0;	//��б��ʮ�ֵ�б��	*******************
uint8 xieruqushidian1=0;     //б��ʮ�����Ƶ�1
uint8 xieruqushidian2=0;		//б��ʮ�����Ƶ�2
uint8 xieruqushidian3=0;		//б��ʮ�����Ƶ�3
uint8 hang20_mid_xieru=0;    //б��ʮ�ֲ���  *******************
void shizi()
{
 /**********************Զһ���ʮ��*************/
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
if(maybeshiziflag && visvalMid[8]>initcenter)			//��ʮ�ֲ���
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
	for(i=6;i<standardrow-10;i++)						//��ʮ���ϲ��ߵ�
	{
		if(left[i+1]<left[i]-5)
		{
			tiaobianhang_sz_left=i;
			buxian_sz_up=tiaobianhang_sz_left-1;
			break;
		}
	}
	for(i=standardrow-10;i<CAMERA_H-1;i++)				//��ʮ���²��ߵ�
	{
		if(left[i]>left[i+1])
		{
			buxian_sz_down=i;
			break;
		}
	}
	if(buxian_sz_up!=0 && buxian_sz_down!=0)				//����
	{
		error_sz=(int)left[buxian_sz_up]-(int)left[buxian_sz_down];
		K_sz=(float)error_sz/(buxian_sz_down-buxian_sz_up);
		for(i=buxian_sz_up;i<=buxian_sz_down;i++)
		{
			left[i]=left[buxian_sz_down]+K_sz*(buxian_sz_down-i);
		//	img[i][left[i]]=100; //
		}
                for(i=0;i<CAMERA_H;i++)                 //����������
                {
                  visvalMid[i]=(left[i]+right[i])/2;
                  img[i][visvalMid[i]]=red;//
                }
	}
  }
}

if(maybeshiziflag && visvalMid[8]<=initcenter)			//��ʮ�ֲ���
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
	for(i=6;i<standardrow-10;i++)						//��ʮ���ϲ��ߵ�
	{
		if(right[i+1]<right[i]+5)
		{
			tiaobianhang_sz_right=i;
			buxian_sz_up=tiaobianhang_sz_right-1;
			break;
		}
	}
	for(i=standardrow-10;i<CAMERA_H-1;i++)				//��ʮ���²��ߵ�
	{
		if(right[i]<right[i+1])
		{
			buxian_sz_down=i;
			break;
		}
	}
	if(buxian_sz_up!=0 && buxian_sz_down!=0)				//����
	{
		error_sz=(int)right[buxian_sz_down]-(int)right[buxian_sz_up];
		K_sz=(float)error_sz/(buxian_sz_down-buxian_sz_up);
		for(i=buxian_sz_up;i<=buxian_sz_down;i++)
		{
			right[i]=right[buxian_sz_down]-K_sz*(buxian_sz_down-i);
		//	img[i][right[i]]=100;//
		}
                for(i=0;i<CAMERA_H;i++)                 //����������
                {
                  visvalMid[i]=(left[i]+right[i])/2;//
                  img[i][visvalMid[i]]=red;//
                }
	}
}
/***********************����ʮ��*******************/
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
//�󿿽�ʮ��
if(tiaobianhang_nearsz_left!=0 && tiaobianhang_nearsz_right==0)				
{
	nearszflag_left=1;
	if(tiaobianhang_nearsz_left+10>CAMERA_H-1)		//��Խ��
		startrow_nearsz=CAMERA_H-1;
	else
		startrow_nearsz=tiaobianhang_nearsz_left+10;
	for(i=startrow_nearsz;i<CAMERA_H;i++)		
	{
		j=0;
		if(img[i][j]==black)		//ɨ������У��к�����
		{
			nearszflag_left=0;
			break;
		}
		j=CAMERA_W-1;
		if(img[i][j]==black)		//ɨ���ұ��У��к�����
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
			if(img[i][j]==black)		//ɨɨ���У��к�����
			{
				nearszflag_left=0;
				break;
			}
		}
		j=65;
		for(i=10;i<startrow_nearsz;i++)
		{
			if(img[i][j]==black)		//ɨ65�У��к�����
			{
				nearszflag_left=0;
				break;
			}
		}
	}
}
//�ҿ���ʮ��
if(tiaobianhang_nearsz_left==0 && tiaobianhang_nearsz_right!=0)				
{
	nearszflag_right=1;
	if(tiaobianhang_nearsz_right+10>CAMERA_H-1)		//��Խ��
		startrow_nearsz=CAMERA_H-1;
	else
		startrow_nearsz=tiaobianhang_nearsz_right+10;
	for(i=startrow_nearsz;i<CAMERA_H;i++)		
	{
		j=0;
		if(img[i][j]==black)		//ɨ������У��к�����
		{
			nearszflag_right=0;
			break;
		}
		j=CAMERA_W-1;
		if(img[i][j]==black)		//ɨ���ұ��У��к�����
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
			if(img[i][j]==black)		//ɨɨ���У��к�����
			{
				nearszflag_right=0;
				break;
			}
		}
		j=15;
		for(i=10;i<startrow_nearsz;i++)
		{
			if(img[i][j]==black)		//ɨ15�У��к�����
			{
				nearszflag_right=0;
				break;
			}
		}
	}
}

/************************б��ʮ��*******************/
 /* maybeshiziflag_right=1;
  maybeshiziflag_left=1;
  for(i=20;i<CAMERA_H;i++)      //����ɨ������ �к�����
  {
	if(img[i][2*(i-20)]==black)
	{
		maybeshiziflag_right=0;
		break;
	}
  }
  for(i=20;i<CAMERA_H;i++)	//����ɨ������ �к�����
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
	for(i=20;i<CAMERA_H-1;i++)			//ɨ�����а���������
	{
		if(img[i][j]==white && img[i+1][j]==black)
			baitiaobian_left++;
	}
	j=CAMERA_W-1;					
	for(i=20;i<CAMERA_H-1;i++)			//ɨ�����а���������
	{
		if(img[i][j]==white && img[i+1][j]==black)
			baitiaobian_right++;
	}
        j=40;
	whitesum_shizi=0;
	for(i=0;i<20;i++)					//ǰ20���м��а׵�������10����ʮ��
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

//��б��
  shiziflag_right=0;
  if(baitiaobian_left==1 && maybeshiziflag_right)//����һ���������а�����	
  {
	shiziflag_right=1;
        for(i=CAMERA_H-1;i>CAMERA_H-1-(CAMERA_W-1-(left[CAMERA_H-1]+3))/2;i--)	//����ɨ������ �к�����
        {
          if(img[i][left[CAMERA_H-1]+3+2*(CAMERA_H-1-i)]==black)
          {
			shiziflag_right=0;
			break;
          }
        }
	j=CAMERA_W-1;
	for(i=20;i<CAMERA_H;i++)	        //��������������20������ȫ��
	{
		if(img[i][j]==black)
		{
			shiziflag_right=0;
			break;
		}
	}
  }

//��б��
  shiziflag_left=0;
  if(baitiaobian_right==1 && maybeshiziflag_left)		//����һ���������а�����	
  {
	shiziflag_left=1;
        for(i=CAMERA_H-1;i>CAMERA_H-1-(right[CAMERA_H-1]-3)/2;i--)	//����ɨ������ �к�����
        {
          if(img[i][right[CAMERA_H-1]-3-2*(CAMERA_H-1-i)]==black)
          {
			shiziflag_left=0;
			break;
          }
        }
	j=0;
	for(i=20;i<CAMERA_H;i++)	        //��������������20������ȫ��
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
	for(i=20;i<CAMERA_H;i++)	      //������20�������к��򽫼���������
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
	for(i=20;i<CAMERA_H;i++)	      //������20�������к��򽫼���������
	{
		if(img[i][j]==black)
		{
			shizinum_left=0;
			break;
		}
	}
  }
  //�������Լ�
  if(shizinum_right)
    shizinum_right--;
  if(shizinum_left)
    shizinum_left--;
}

*/



/****��б��***/	
  xierushizi_flag_right=0; 
  heitiaobian=0;
  baitiaobian=0;
  baitiaobianhang=0;
  for(i=2;i<50;i++) //������㣬ͬʱ�����·����а�
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
		
		if(right[i]<xiexian_xia_j && img[i][right[i]]==black)//�޳��ұ߽�Ϊ79�м��׵����
		{
			xiexian_xia_j=right[i];  //������
			xiexian_xia_i=i;
		}	
			
	 }         ////////////////////////
	for(i=xiexian_xia_i;i>0;i--)
	{
		if(right[i]>=xiexian_shang_j && img[i][right[i]]==black )
		{
                    xiexian_shang_j=right[i]; //������
                    xiexian_shang_i=i;
		}
		if((right[i]-right[i-1])>=12||(right[i-1]-right[i])>=12||img[i-1][right[i-1]]==white) //�߽����䣬�������������ұ߽�
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
  		for(j=0;j<=xiexian_shang_j;j++) //����б���ж�
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
//��б��
       xierushizi_flag_left=0;
       heitiaobian=0;
       baitiaobian=0;
       baitiaobianhang=0;    
//    if(!xierushizi_flag_right)
 //   {
         
           for(i=2;i<50;i++) //������㣬ͬʱ�����·����а�
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
		
                    if(left[i]>xiexian_xia_j && img[i][left[i]]==black)//�޳��ұ߽�Ϊ79�м��׵����
                    {
			xiexian_xia_j=left[i];  //������
			xiexian_xia_i=i;
                    }	
		
		}
		for(i=xiexian_xia_i;i>0;i--)
		{
			if(left[i]<=xiexian_shang_j && img[i][left[i]]==black )
			{
					xiexian_shang_j=left[i]; //������
					xiexian_shang_i=i;
					
			}
			if((left[i]-left[i-1])>=12||(left[i-1]-left[i])>=12||img[i-1][left[i-1]]==white) //�߽����䣬�������������ұ߽�
				break;
		}
		if((xiexian_shang_i-baitiaobianhang)>=5||(baitiaobianhang-xiexian_shang_i)>=5||xiexian_xia_i<=20)//����������У��ϵ�Ӧ�úͰ��м���ͬ��
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
  			for(j=xiexian_shang_j;j<CAMERA_W;j++) //����б���ж�
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
					if(j>CAMERA_W-1)//�޷�����С��0������CAMERA_W
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
  
 /************************б��ʮ�ֲ����ж�*************************/
    //��б��ʮ��
if(lianxuhangnum_right>=40 && xierushizi_flag_left==0)//�ұ�������������һ��ֵ
{
	dixiehangnum_left=0; //��б����
	//��߽���µ�����һ������
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
	if(btowhang!=0) //�Ҳ�����߽�ĺڰ׵�
		xierushizi_flag_left=1;
	if(left[btowhang]>CAMERA_W/2) //��߽�ĺڰ�����������еĵ���߽�С������һ��
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
		if(dixiehangnum_left<=3 || i<=btowhang) //��б��������Ҫ����3�� ���ҹյ�С�ںڰ������
				xierushizi_flag_left=0;	
	}
	//��ʱ�������µ�iֵΪ��б��յ�
	if(xierushizi_flag_left) // ��б��յ㵽�ұ߽�ȫ��
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
	if(xierushizi_flag_left)//��б��յ��Ϸ��߽�ݼ����ұ߽��Ϸ�ȫ��
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
	if(xierushizi_flag_left)//�ұ߽�һ������ȫ��
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
	//�ұ߽�ĺڰ������()�¼�������ɨ��-������㣬���е�����㶼��������С������
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
	//����
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
//��б��ʮ��

if(lianxuhangnum_left>=40 && xierushizi_flag_right==0)//���������������һ��ֵ
{
	dixiehangnum_right=0; //��б����
	//�ұ߽���µ�����һ������
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
	if(btowhang!=0) //�Ҳ����ұ߽�ĺڰ׵�
		xierushizi_flag_right=1;
	if(right[btowhang]<CAMERA_W/2) //�ұ߽�ĺڰ�����������еĵ��ұ߽��������һ��
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
		if(dixiehangnum_right<=3 || i<=btowhang) //��б��������Ҫ����3�� ���ҹյ�С�ںڰ������
				xierushizi_flag_right=0;	
	}
	//��ʱ�������µ�iֵΪ��б��յ�
	if(xierushizi_flag_right) // ��߽絽��б��յ�ȫ��
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
	if(xierushizi_flag_right)//��б��յ��Ϸ��߽�������ұ߽��Ϸ�ȫ��
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
	if(xierushizi_flag_right)//��߽�һ������ȫ��
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
		//��߽�İ׺�������¼�������ɨ��-������㣬���е�����㶼��������������
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
	//б��ʮ�ֲ���	
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
 
/********************����*******************/
//����ʮ�ֲ���
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
        for(i=0;i<CAMERA_H;i++)                 //����������
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
        for(i=0;i<CAMERA_H;i++)                 //����������
        {
          visvalMid[i]=(left[i]+right[i])/2;
          img[i][visvalMid[i]]=red;
        }
}

}