#include "TIM7.h"

u16 count_10ms, target_10ms;
u8 flag = 0;

void TIM7_Init () {
    TIM_TimeBaseInitTypeDef TIM_InitStruct;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);

    TIM_DeInit(TIM7);
    TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_InitStruct.TIM_Period = 1439;
    TIM_InitStruct.TIM_Prescaler = 499; //10ms
    TIM_TimeBaseInit(TIM7, &TIM_InitStruct);

    TIM_ClearITPendingBit(TIM7,TIM_IT_Update);
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE); //ʹ��ָ����TIM6�ж�,��������ж�

    NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;  //TIM6�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�2�� ����USART TIM6
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���

    //�Ȳ�ʹ��

}

void TIM7_IRQHandler(void) {
   if(TIM_GetITStatus(TIM7, TIM_IT_Update)) {
       count_10ms ++;
       if (count_10ms >= target_10ms) {
           flag = 0;
           //USART_SendData(USART3, count_10ms);
           TIM_Cmd(TIM7, DISABLE);
           }
   }
   TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
}


void Delay_10ms (u16 n10ms) {
    flag = 1;
    count_10ms = 0;
    target_10ms = n10ms;
    TIM_Cmd(TIM7, ENABLE);
    
    while (flag);
}
