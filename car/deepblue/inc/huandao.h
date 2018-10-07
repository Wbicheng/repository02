


#ifndef __HUANDAO_H__
#define __HUANDAO_H__


#define maxsize 50
extern uint8   huandao1flag_right;
extern uint8	huandao2flag_right;
extern uint8	huandao1flag_left;
extern uint8	huandao2flag_left;
extern uint8	heitiaobian;          //�������
extern uint8	baitiaobian;          //�������
extern uint8   heitiaobianhang_right[3];                 //�Һ�������
extern uint8   heitiaobianhang_left[3];                  //���������
extern uint8   baitiaobianhang_right[3];                //�Ұ�������
extern uint8   baitiaobianhang_left[3];                 //���������
extern uint8   zhidaohuandao2flag;   //ֱ������2��־λ
extern uint8   chuhuandaoflag_right; //���һ�����־
extern uint8   chuhuandaoflag_left;  //���󻷵���־
extern uint8   huandao1[maxsize];//ѭ������
extern uint8   nowpoint;           //ѭ������ĵ�ǰָ��
extern uint8   prepoint;           //vsynnum����ǰ��ָ��
extern uint8   huandao1num;        //vsynnum����Ҫ�������һ������
extern uint16  huandaonum1_2_right;   //�һ���1����2����  huandaocount_right
extern uint16  huandaonum1_2_left;    //�󻷵�1����2����
extern uint8   ruhuandaoflag_right;                   //���һ�����־
extern uint8   ruhuandaoflag_left;                    //���󻷵���־
extern uint16  huandaonum2_turn_right;  //�һ���2����ת�����
extern uint16  huandaonum2_turn_left;  //�󻷵�2����ת�����
extern uint16  rudaonum_right;//�һ���2ת����ʱ����
extern uint16  rudaonum_left;//�󻷵�2ת����ʱ����
extern uint16  chudaonum_right;//���һ�������
extern uint16  chudaonum_left;//���󻷵�����
extern uint16  vsynnum;   //ȷ������1��ɨ�賡��
extern void huandao();
extern int absint();
extern uint16   huandaocount_right;  //�һ�������
extern uint16   huandaocount_left;   //�󻷵�����
extern uint8   xieruhuandaoflag_right; //б���һ�����־
extern uint8   xieruhuandaoflag_left;  //б���󻷵���־
extern uint8   heitiaobianlienum;                              //����������  
extern uint8   baitiaobianlienum;			      //���������� 
extern uint8   baitiaobianlie_leftest;                         //����İ����������� 
extern uint8   heitiaobianlie_rightest;                        //���ҵĺ�����������  
extern uint8   kongbaihang;                                  //�հ���                                
extern uint8   kongbaihang_flag;                              //���ұ߽����ڿհ��б�־   
extern uint8   yuandihang;                                     //Բ�ĵ���  
extern uint8   yuandihang_flag;                                //����Բ���� 
extern uint8   yuanlie;                                        //������˫ʮ�ֵ�����--Բ���ж�б�뻷��ʱ��
extern uint8 yuanlie_ruhuandao;                                  //�뻷��ʱ������б�뻷��ʱ���룬������Բ������
extern float   K_huandao;            //б�뻷��б��
extern float   huandaoMid;           //б�뻷������
extern uint8 baitiaobianhang_right_col[CAMERA_W];//�һ���1�а�������
extern uint8 baitiaobianhang_left_col[CAMERA_W];//�󻷵�1�а�������
extern uint8 shangbanyuancount_right;	//�һ����ϰ�Բ������
extern uint8 shangbanyuancount_left;	//�󻷵��ϰ�Բ������
//�󻷵�
extern uint8 dahuandaoflag_left;     //��󻷵�  ������
extern uint8 dahuandaoflag_right;	//�Ҵ󻷵�	������
extern uint8 dahuandaonum_left;           //�󻷵�ʶ�𵽼���
extern uint8 dahuandaonum_right;
extern uint8 rudahuandaoflag_left;   //����󻷵�  ......
extern uint8 rudahuandaoflag_right;  //���Ҵ󻷵�	......
extern uint8 ruhuandao_shang_i_left;      //�뻷���ϲ���i  �󻷵�
extern uint8 ruhuandao_shang_j_left;	//�뻷���ϲ���j
extern uint8 ruhuandao_xia_i_left;		//�뻷���²���i
extern uint8 ruhuandao_xia_j_left;		//�뻷���²���j

extern uint8 ruhuandao_shang_i_right;      //�뻷���ϲ���i  �һ���
extern uint8 ruhuandao_shang_j_right;	//�뻷���ϲ���j
extern uint8 ruhuandao_xia_i_right;		//�뻷���²���i
extern uint8 ruhuandao_xia_j_right;		//�뻷���²���j
extern float k_ruhuandao;        //�뻷��б��
extern uint16 indahuandaonum_left;
extern uint16 indahuandaonum_right;
extern uint8 chudahuandaoflag_left;        //����󻷵���־
extern uint8 chudahuandaoflag_right;		//���Ҵ󻷵���־
extern uint8 chudahuandaonum_left;       //������������
extern uint8 chudahuandaonum_right;       //������������

extern uint8 rudahuandaonum_left;            //��󻷵�����   --���ڲ��ߡ���������������������
extern uint8 rudahuandaonum_right;		//��󻷵����� ---���ڲ��ߡ�����������������������
extern uint8 nearchudahuandaoflag_left;       //������������־  ������������������
extern uint8 nearchudahuandaoflag_right;      //������������־ ������������������
extern uint8	chudaodian_left_i;             //��������־�Ƚϵ�
extern uint8	chudaodian_right_i;	        //��������־�Ƚϵ�
extern uint8  nohuandaonum;  // ���λ�������
extern uint8 btowhang;   //�������ϵĺڵ��׵������� ............................................
extern uint8 wtobhang;   //�������ϵİ׵��׵�������..................................................

extern uint8 ruhuandao1num_left;  //���󻷵�1����
extern uint8 ruhuandao1num_right;  //���һ���1����
extern uint8 ruhuandao2num_left;//���󻷵�2����
extern uint8 ruhuandao2num_right;//���һ���2����

extern uint8 nearhuandaoflag_left; //�����󻷵���־
extern uint8 nearhuandaoflag_right;//�����һ�����־

extern uint8 hang20_mid;  //�ڻ������뻷��1���뻷��2ǰ����λ��
extern uint8 hang20_mid_hang;

extern uint8 baitiaobian_sum;
extern uint8 btowlie;  //��to��������     ^^^^^^^^^^^^^^^^^^^^^^
extern uint8 jiange_wai;  //�����ж�Ϊ·�� ����ļ��  ^^^^^^
extern uint8 jiange_nei;//�����ж�Ϊ·�� ���ڵļ��    ^^^^^^^^^



#endif  //__huandao_H__
