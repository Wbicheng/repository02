#ifndef __ENCODER_H__
#define __ENCODER_H__

//�������������״̬
typedef enum
{
    left_Encoder,                //�����������
    right_Encoder,               //�ұ���������
    double_Encoder,              //˫����������
}Encoder_flag;

void PIT0_IRQHandler(void);     //PIT0�������жϷ�����
extern void Encoder(Encoder_flag Encoder_n,int Acq_time);//������������ʼ������
extern Encoder_flag Encoder_flagextern;//�жϹ���״̬��־
extern int Encoder_speed1;//������1���������ֵ����main�����е��ü��ɻ�ü���ֵ
extern int Encoder_speed2;//������2���������ֵ
extern int speedError[3];
extern int currentspeed; 
extern int debug_time;//����ģʽ
extern int wd_time;//���ʱ��
extern int last_motorPWM;//��һ�ε�pwm

#endif
