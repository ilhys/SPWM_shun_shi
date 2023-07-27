#include "pidw.h"
#include "stdio.h"

pid_p pidw;

void pidw_init(void)
{
    printf("pidw_init begin \n");
    pidw.SetVoltage= 0.0;		    //设定值
    pidw.ActualVoltage= 0.0;		// 实际值
    pidw.err= 0.0;				      // 误差
    pidw.err_last=0.0;			    // 上次误差
    pidw.voltage= 0.0;			    // 输出值
    pidw.integral= 0.0;			    // 误差积分
	  pidw.result=0.0;            //计算结果
    pidw.Kp= 0.30;				        // ????
    pidw.Ki= 0.01;				      // ????
    pidw.Kd= 0.0;				        // ????
    printf("pidw_init end \n");
}

float pidw_realize(float v, float v_r)
{
    pidw.SetVoltage = v;				// 设定值
    pidw.ActualVoltage = v_r;	  // 实际值
    pidw.err = pidw.SetVoltage - pidw.ActualVoltage;	//误差
    pidw.integral+= pidw.err;					//误差总和
    pidw.result = pidw.Kp * pidw.err + pidw.Ki * pidw.integral + pidw.Kd * ( pidw.err - pidw.err_last);//输出值
    pidw.err_last = pidw.err;					
    //pidw.ActualVoltage=pidw.result*1.0;			
	  if(pidw.result>=1)  pidw.result=1;
	  if(pidw.result<=-1)  pidw.result=-1;
    return pidw.result;
}

