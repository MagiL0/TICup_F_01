#include "PID.h"


void PID_Init(PID_t *sptr, float kp, float ki, float kd, float point)
{
	sptr->SumError = 0;
	sptr->LastError = 0;
	sptr->PrevError = 0;
	sptr->Kp = kp;
	sptr->Ki = ki;
	sptr->Kd = kd;
	sptr->SetPoint = point;
}

float LocPID_Calc(float nextpoint, PID_t *sptr)
{
  	float iError, dError, iLocPid;
	iError = sptr->SetPoint - nextpoint;  //ƫ��
    sptr->SumError += iError;   //����
    dError = iError - sptr->LastError;     //΢��
    sptr->LastError = iError; 
	iLocPid = sptr->Kp * iError  //������
              + sptr->Ki * sptr->SumError  //������
              + sptr->Kd * dError ; //΢����
    return iLocPid;
}
