#include "HCSR04.h"

int K1Number = 0, K2Number = 0, K3Number = 0,K4Number = 0;
__IO uint16_t K1Value1 = 0,  K3Value1 = 0,K4Value1 = 0;
__IO uint16_t K1Value2 = 0,  K3Value2 = 0,K4Value2 = 0;
__IO uint16_t K1Capture = 0, K3Capture = 0,K4Capture = 0;
int Trigger_Time=0, Trigger1=0,ok12=0;
void timeout()
{
	Trigger_Time+=10;
}
void HCSR04_GPIO_Init()//Port c vs e
{	

GPIO_InitTypeDef   				GPIO_InitStruct;
	///////////////////////////////////
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//Trigger pin port D
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_13|GPIO_Pin_12|GPIO_Pin_14;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_25MHz;
  GPIO_Init(GPIOD, &GPIO_InitStruct);	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//Echo pin port A
 /* TIM8 channel 1 pin (PC6) configuration */
  GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_6;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStruct);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM8);	
	/* TIM8 channel 4 pin (PE.14) configuration */
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//Echo pin port E
//	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_14;
//  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
//  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
//  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
//  GPIO_Init(GPIOE, &GPIO_InitStruct);
//  GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF_TIM8);	
	/* TIM8 channel 3 pin (PA.10) configuration */
//	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_10;
//  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
//  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
//  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
//  GPIO_Init(GPIOA, &GPIO_InitStruct);
//  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_TIM8);

}
void HCSR04_TIM_Init()///Timer  Init 
{
	TIM_TimeBaseInitTypeDef 	TIM_BaseStruct; 	 
	TIM_OCInitTypeDef  				TIM_OCStruct;
	TIM_ICInitTypeDef 				TIM_ICInitStruct;
	NVIC_InitTypeDef   				NVIC_InitStruct;	 
	//Timer5 interrupt Ultrasonic trigger pin 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
  TIM_BaseStruct.TIM_Period=10-1;
  TIM_BaseStruct.TIM_Prescaler=((SystemCoreClock/2)/1000000)-1; //1us
  TIM_BaseStruct.TIM_ClockDivision=TIM_CKD_DIV1;
  TIM_BaseStruct.TIM_CounterMode=TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM5, &TIM_BaseStruct);
	
  NVIC_InitStruct.NVIC_IRQChannel = TIM5_IRQn;
  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 15;
  NVIC_InitStruct.NVIC_IRQChannelSubPriority = 15;
  NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStruct);
  TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE);
//Timer1 Input Capture 3 channel on Echo pin 	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE); 	 /* TIM8 clock enable */
	TIM_BaseStruct.TIM_Prescaler = 167;  //1us //((SystemCoreClock)/1000000)-1;
  TIM_BaseStruct.TIM_Period = 0xFFFF; 
  TIM_BaseStruct.TIM_ClockDivision = 0;
  TIM_BaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM8, &TIM_BaseStruct); 
	//Channel 1
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;
  TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_BothEdge;
  TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStruct.TIM_ICFilter = 15;
  TIM_ICInit(TIM8, &TIM_ICInitStruct);
	//Channel 3
//	TIM_ICInitStruct.TIM_Channel = TIM_Channel_3;
//  TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_BothEdge;
//  TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
//  TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
//  TIM_ICInitStruct.TIM_ICFilter = 15;
//  TIM_ICInit(TIM8, &TIM_ICInitStruct);
//		//Channel 4
//	TIM_ICInitStruct.TIM_Channel = TIM_Channel_4;
//  TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_BothEdge;
//  TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
//  TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
//  TIM_ICInitStruct.TIM_ICFilter = 15;
//  TIM_ICInit(TIM8, &TIM_ICInitStruct);  
  /* TIM enable counter */
  TIM_Cmd(TIM8, ENABLE);
  /* Enable the CC1, CC4, CC3 Interrupt Request */
  TIM_ITConfig(TIM8, TIM_IT_CC1, ENABLE);
	//TIM_ITConfig(TIM8, TIM_IT_CC2, ENABLE);
	//TIM_ITConfig(TIM8, TIM_IT_CC3, ENABLE); 
	//TIM_ITConfig(TIM8, TIM_IT_CC4, ENABLE);  
	
  /* Enable the TIM8 global Interrupt */
  NVIC_InitStruct.NVIC_IRQChannel = TIM8_CC_IRQn;
  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;
  NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStruct);

////////////delay_us timer 10/////////////////////////
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE);
	TIM_TimeBaseStructInit(&TIM_BaseStruct);
  TIM_BaseStruct.TIM_Period= 65535;	//recount
  TIM_BaseStruct.TIM_Prescaler=100-1; //frequency
  TIM_BaseStruct.TIM_ClockDivision=0;
  TIM_BaseStruct.TIM_CounterMode=TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM10, &TIM_BaseStruct);
	TIM_Cmd(TIM10, ENABLE);
}
void Delay_us(int us)
{
	TIM10->CNT = 0;
	while((TIM10->CNT) <= us);
}

void HCSR04_Trigger(void) //Set 10us trigger pin
{
  Trigger_Time=0;
	GPIO_SetBits(GPIOD,GPIO_Pin_3|GPIO_Pin_2|GPIO_Pin_1);
//  TIM_Cmd(TIM5, ENABLE);
//	
//  while(Trigger_Time > 20);
//	GPIO_SetBits(GPIOD,GPIO_Pin_12);
//  TIM_Cmd(TIM5, DISABLE);
	Delay_us(15);
	GPIO_ResetBits(GPIOD,GPIO_Pin_3|GPIO_Pin_2|GPIO_Pin_1);

}
void TIM_CAPTURE()
{
	 if(TIM_GetITStatus(TIM8, TIM_IT_CC1) == SET) 
  {
    /* Clear TIM8 Capture compare interrupt pending bit */
    TIM_ClearITPendingBit(TIM8, TIM_IT_CC1);
    if(K1Number == 0)
    {
      /* Get the Input Capture value */
      K1Value1 = TIM_GetCapture1(TIM8);
      K1Number = 1;
    }
    else if(K1Number == 1)
    {
      /* Get the Input Capture value */
      K1Value2 = TIM_GetCapture1(TIM8); 
      
      /* Capture computation */
      if (K1Value2 > K1Value1)
      {
        K1Capture = (K1Value2 - K1Value1); 
      }
      else if (K1Value2 < K1Value1)
      {
        K1Capture = ((0xFFFF - K1Value1) + K1Value2); 
      }
      else
      {
        K1Capture = 0;
      }
      K1Number = 0;
    }
  }

}
void Sonic_Read1()//Read data from ultrasonic sensor
{
//	
//			TIM_Cmd(TIM8, ENABLE);
//	//GPIO_SetBits(GPIOD,GPIO_Pin_14);
//			HCSR04_Trigger();//10us set trigger pin
//	
//			ok12 = 0;
//			Trigger_Time = 0;
//			TIM_Cmd(TIM5, ENABLE);
//	
//			do
//				{	
//						
//					if(Trigger_Time >= 30000)  
//					{ok12=4;}
//					else{ok12=3;}
//				}
//				
//				while(ok12==0); 
//				
//				TIM_Cmd(TIM5, DISABLE);
//				Trigger_Time=0;			
//				distance1=(float)(K1Capture)*(0.017);				
//				Trigger_Time=0;
				
				
				/////
	HCSR04_Trigger();
	distance1=(float)(K1Capture)*(0.017);				

}