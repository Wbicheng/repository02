


#ifndef __LUZHANG_H__
#define __LUZHANG_H__
 
extern void luzhang();
extern uint8 heitiaobian_lz[CAMERA_H];			//·�Ϻ������
extern uint8 baitiaobian_lz[CAMERA_H];			//·�ϰ������
extern uint8 luzhangflag_left;		                //��·�ϱ�־
extern uint8 luzhangflag_right;		                //��·�ϱ�־
extern int8 blacksum_lz[CAMERA_H];	                //·�Ϻڵ���
extern int16 right_lz[CAMERA_H];		//��·�ϱ߽�
extern int16 left_lz[CAMERA_H];		//��·�ϱ߽�
extern uint8 startrow_lz;                      //·�����߿�ʼ��
extern uint8 endrow_lz;                        //·�����߽�����
extern float K_lz;                             //·������б��
extern uint8 lzflag_right;                   //��·���б�־
extern uint8 lzflag_left;                    //��·���б�־
extern uint8 delaynum_lz_right;                //��·�Ͻ�����������
extern uint8 delaynum_lz_left;                 //��·�Ͻ�����������
extern uint8 clearflag_lz_right;               //����·�ϱ�־
extern uint8 clearflag_lz_left;               //����·�ϱ�־
extern uint8 center_lz;                         //·������
#endif  //__ZHIDAO_H__
