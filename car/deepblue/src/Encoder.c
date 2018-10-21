
//****************�Զ������������*********����ɫ����ʦ
#include "common.h"
#include "include.h"
#include "Encoder.h"
#include "MK60_FTM.h"
#include "MK60_pit.h"


//ǿ����һ��ģ��ͬһʱ��ֻ�ܸ�һ�������Ƶ�ʱ�������ͬ�ġ�
//FTM�Ƕ๦�ܵĶ�ʱ������ʵ�ֶ��ֹ��ܡ�
//��ͬһʱ�䣬һ��FTM0��ȥPWM������Ͳ�Ҫ���������������롢���벶׽�������������顣
//���ң�FTM0��ͨ��0���Ƶ��Ϊ20k��ͨ��1Ҳ���룬ֻ�����20k��pwm��


Encoder_flag Encoder_flagextern;//��˫�����������ж�λ������PIT�жϺ���
int Encoder_speed1=0;             //������1���������ֵ����main�����е��ü��ɻ�ü���ֵ
int Encoder_speed2=0;             //������2���������ֵ����main�����е��ü��ɻ�ü���ֵ

 int speedError[3];          //����ٶ����
 int currentspeed;              //��ǰ�ٶ�
 int32 motorPWM = dianjispeed;    //���PWM
 float P_moto = 10; 
 float I_moto = 7; 
 float D_moto = 1; 
int debug_time=0;//����ģʽ


/*!
 *  @brief     ��������������
 *  @param     Encoder_flag  ����������״̬ѡ��
 *  @param     int           ��������ɼ�ʱ��ms
 *  @since     v1.0
 *  @note      FTM �������� ���٣����ֹ���״̬��
 *  @Sample usage     Encoder(double_Encoder,500);   ���ñ�������������������״̬Ϊ˫������ģʽ���ɼ�����Ϊ500ms
 */

void Encoder(Encoder_flag Encoder_n,int Acq_time)
{  
    ASSERT(enter_init());   //�ж��Ƿ������FWD�̼�
    Encoder_flagextern=Encoder_n;
    switch(Encoder_n)
    {
     case 0:
           printf("\nFTM1:\n");
           ftm_quad_init(FTM1);  //FTM1 ���������ʼ�������õĹܽſɲ� port_cfg.h �� FTM1_QDPHA_PIN �� FTM1_QDPHB_PIN
           break;                                               
     case 1: 
           printf("\nFTM2:\n");
           ftm_quad_init(FTM2);   
           break;                //FTM2���������ʼ�������õĹܽſɲ� port_cfg.h
     case 2:
           printf("\nDOUBLE_FTM\n");
           ftm_quad_init(FTM1);  
           ftm_quad_init(FTM2); 
           break;                //FTM1��FTM2���������ʼ�������õĹܽſɲ� port_cfg.h
    }
         pit_init_ms(PIT0, Acq_time);                            //��ʼ��PIT0����ʱʱ��Ϊ�� 500ms
         set_vector_handler(PIT0_VECTORn ,PIT0_IRQHandler);      //����PIT0���жϷ�����Ϊ PIT0_IRQHandler
         enable_irq (PIT0_IRQn);                                 //ʹ��PIT0�ж�
}

/*!
 *  @brief      PIT0�жϷ�����
 *  @since      v1.0
 */
void PIT0_IRQHandler(void)
{
   switch(Encoder_flagextern)
   {
      case 0:
          Encoder_speed1 = ftm_quad_get(FTM1);          //��ȡFTM �������� ��������(������ʾ������)
          ftm_quad_clean(FTM1);
          printf("FTM1:%d\n",Encoder_speed1);
          PIT_Flag_Clear(PIT0);       //���жϱ�־λ
          break;
      case 1:
          Encoder_speed2 = ftm_quad_get(FTM2);
          ftm_quad_clean(FTM2);
          printf("FTM2:%d\n",Encoder_speed2);
          PIT_Flag_Clear(PIT0); 
          break;
      case 2:
          Encoder_speed1 = ftm_quad_get(FTM1);
          Encoder_speed2 = ftm_quad_get(FTM2);
          ftm_quad_clean(FTM1);
          ftm_quad_clean(FTM2);
          printf("FTM1:%d\n",Encoder_speed1);
          printf("FTM2:%d\n",Encoder_speed2);
          PIT_Flag_Clear(PIT0); 
          break;
  
   }
  if(deepblue==2 && debug_time!=1000)
  {
      debug_time++;
  
  }
  if(debug_time==1000)
  {
      ftm_pwm_duty(FTM0, FTM_CH2, 0);
      ftm_pwm_duty(FTM0, FTM_CH3, 0);
  }  
  else
  {
     /*****************************���PID**********************/
   if(Encoder_speed2<0)
     Encoder_speed2 = -Encoder_speed2;
    currentspeed = Encoder_speed2;
    speedError[2] = settingspeed - currentspeed; //��ǰ���
    motorPWM +=  P_moto * (speedError[2]-speedError[1]) +I_moto * speedError[2] + D_moto * (speedError[2] - 2 * speedError[1] + speedError[0]);
    //���ü����ٶ�
    if(motorPWM >limitspeed)
      motorPWM =limitspeed;
   if(motorPWM<0)
      motorPWM = 0;
/*    if(stop_flag && !zdnum)
    {
        if(fznum) //�յ��߷�ת50��10ms=0.5s
        {
           fznum--;
           ftm_pwm_duty(FTM0, FTM_CH2, 0);
           ftm_pwm_duty(FTM0, FTM_CH3, 8000);
        
        }
        else
        ftm_pwm_duty(FTM0, FTM_CH3, 0);
    }*/
   // else
   // ftm_pwm_duty(FTM0, FTM_CH2, motorPWM);
//    else 
     if(motorPWM>0)
    {
      ftm_pwm_duty(FTM0, FTM_CH2, motorPWM);
      ftm_pwm_duty(FTM0, FTM_CH3, 0);
    }
    else
    {
      ftm_pwm_duty(FTM0, FTM_CH2, 0);
      ftm_pwm_duty(FTM0, FTM_CH3, -motorPWM);
    }
      
   
    speedError[0] = speedError[1];//���ϴ����
    speedError[1] = speedError[2];//�ϴ����
  }
}