#include "stm32f4xx.h"

void HCSR04_GPIO_Init();
void HCSR04_TIM_Init();
void HCSR04_Trigger1(void) ;
void TIM_CAPTURE();
void Sonic_Read1();
void timeout();

extern volatile float distance1;