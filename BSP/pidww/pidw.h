#ifndef __PIDW_H__
#define __PIDW_H__

typedef struct
{
    float SetVoltage;	  //设定值
    float ActualVoltage;//实际值
    float err;			    //误差
    float err_last;		  //上次误差
    float Kp,Ki,Kd;		  //系数
    float result;		    //pid计算结果
    float voltage;		  //输出值
    float integral;		  //误差总和
	
}pid_p; 

void pidw_init(void);
float pidw_realize(float v, float v_r);

#endif


