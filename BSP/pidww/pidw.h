#ifndef __PIDW_H__
#define __PIDW_H__

typedef struct
{
    float SetVoltage;	  //�趨ֵ
    float ActualVoltage;//ʵ��ֵ
    float err;			    //���
    float err_last;		  //�ϴ����
    float Kp,Ki,Kd;		  //ϵ��
    float result;		    //pid������
    float voltage;		  //���ֵ
    float integral;		  //����ܺ�
	
}pid_p; 

void pidw_init(void);
float pidw_realize(float v, float v_r);

#endif


