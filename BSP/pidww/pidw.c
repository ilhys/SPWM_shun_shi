#include "pidw.h"
#include "stdio.h"

pid_p pidw;

void pidw_init(void)
{
    printf("pidw_init begin \n");
    pidw.SetVoltage= 0.0;		    //�趨ֵ
    pidw.ActualVoltage= 0.0;		// ʵ��ֵ
    pidw.err= 0.0;				      // ���
    pidw.err_last=0.0;			    // �ϴ����
    pidw.voltage= 0.0;			    // ���ֵ
    pidw.integral= 0.0;			    // ������
	  pidw.result=0.0;            //������
    pidw.Kp= 0.30;				        // ????
    pidw.Ki= 0.01;				      // ????
    pidw.Kd= 0.0;				        // ????
    printf("pidw_init end \n");
}

float pidw_realize(float v, float v_r)
{
    pidw.SetVoltage = v;				// �趨ֵ
    pidw.ActualVoltage = v_r;	  // ʵ��ֵ
    pidw.err = pidw.SetVoltage - pidw.ActualVoltage;	//���
    pidw.integral+= pidw.err;					//����ܺ�
    pidw.result = pidw.Kp * pidw.err + pidw.Ki * pidw.integral + pidw.Kd * ( pidw.err - pidw.err_last);//���ֵ
    pidw.err_last = pidw.err;					
    //pidw.ActualVoltage=pidw.result*1.0;			
	  if(pidw.result>=1)  pidw.result=1;
	  if(pidw.result<=-1)  pidw.result=-1;
    return pidw.result;
}

