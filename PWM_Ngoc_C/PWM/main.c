
#include "stm32f4xx.h"
#include "lcd.h"
#include "string.h"

#define ADC3_DR_ADDRESS     ((uint32_t)0x4001224C)
__IO uint16_t ADC3ConvertedValue[4]={0};
#define PWR_UP GPIO_Pin_7


// khai bao cac cau truc GPIO, ngat, UART
GPIO_InitTypeDef       GPIO_InitStructure;
NVIC_InitTypeDef       NVIC_InitStructure;
USART_InitTypeDef 		 USART_InitStructure;
ADC_InitTypeDef ADC_InitStructre;
ADC_CommonInitTypeDef ADC_CommonInitStructure ;

// ham truyen 1 ky tu qua UART tu C#
void Putchar (char x)
{
		USART_SendData(USART3,x);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
}
// ham truyen 1 ky tu qua UART tu SIM
void Putchar1 (char x)
{
		USART_SendData(USART2,x);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
}
// ham truyen 1 chuoi ky tu qua UART
char *mang = "VHKT";
void send_s( char *str_data )
{
  char dodai=0;
  while(*str_data )
  {
		Putchar(*str_data);
    *str_data++;
    //dodai--;
  }
}
void send_s1( char *str_data )
{
  char dodai=0;
  dodai = strlen(str_data);
  while(dodai != 0 )
  {
		Putchar1(*str_data);
    *str_data++;
    dodai--;
  }
}
void send_array( char *str_data )
{
  char dodai=0;
	str_data = mang;
  dodai = strlen(str_data);
  while(dodai != 0 )
  {
		Putchar(*str_data);
    *str_data++;
    dodai--;
  }
}
// ham gui sms (sdt, noi dung sms)
void send_sms(char *p, int n)
{
	send_s1("AT+CMGS=");
	Putchar1(34); //ky tu "
	send_s1(p);
	Putchar1(34); //ky tu "
	Putchar1(13); // ky tu "CR" : Carry Return
	Delay(1500);
	switch(n)
	{
		case 0: {send_s1("He thong khoi dong hoan tat!\n\r");break;}
		case 1: {send_s1("thiet bi 1 da mo!\n\r");break;}
		case 2: {send_s1("thiet bi 1 da tat!\n\r");break;}
		case 3: {send_s1("thiet bi 2 da mo!\n\r");break;}
		case 4: {send_s1("thiet bi 2 da tat!\n\r");break;}
		case 5: {send_s1("thiet bi 3 da mo!\n\r");break;}
		case 6: {send_s1("thiet bi 3 da tat!\n\r");break;}
		case 9: {send_s1("Sorry! Password is wrong! hehe !\n\r");break;}
		default:break;
	}
	GPIO_SetBits(GPIOD,GPIO_Pin_13);
	Delay(1000);
	GPIO_ResetBits(GPIOD,GPIO_Pin_13);
	Putchar1(26);
	Delay(4000);
	sms_mode = 0;
}
//SIM

void USART2_IRQHandler(void)
{
	if( USART_GetITStatus(USART2, USART_IT_RXNE) )
		{	
			while(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET);
		}
		//xoa co nga UART1
	USART_ClearITPendingBit(USART2, USART_IT_RXNE);
}
//ham khai bao cau hinh sim900
void Init_sim900(void)
{
	// bat nguon hoat dong cho module
	GPIO_SetBits(GPIOD,PWR_UP);
	Delay(2000); //delay 2s
	GPIO_ResetBits(GPIOD,PWR_UP);
	Delay(10000);
	// kiem tra ket noi giua module va ARM
	do
	{
		GPIO_SetBits(GPIOD,GPIO_Pin_15);
		send_s1("AT");
		Putchar1(13);
		Delay(800);
		GPIO_ResetBits(GPIOD,GPIO_Pin_15);
		Delay(800);
	}
	while( wait_ok()==0);
		GPIO_SetBits(GPIOD,GPIO_Pin_13);
	// gui sms : cau hinh thanh cong
	GPIO_ResetBits(GPIOD,GPIO_Pin_13);
}
//ham ngat nhan UART t C#
void USART3_IRQHandler(void)
{
	if( USART_GetITStatus(USART3, USART_IT_RXNE) )
		{	
			while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);

		}
		//xoa co nga UART3
	USART_ClearITPendingBit(USART3, USART_IT_RXNE);
}
// Ngat timer 3 cho doc gia tri dong
uint16_t k=0;
void TIM3_IRQHandler(void)
{  
	static uint16_t times = 0;
if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update); 
	}
	
}

int main(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	 		// clock USART
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE); 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); 
	
	GPIO_InitStructure.GPIO_Pin    = GPIO_Pin_7;	
  GPIO_InitStructure.GPIO_Mode   = GPIO_Mode_OUT;
 	GPIO_InitStructure.GPIO_OType  = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd   = GPIO_PuPd_NOPULL;
 	GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOD, &GPIO_InitStructure);	
	//UART3
	GPIO_InitStructure.GPIO_Pin    = GPIO_Pin_8 | GPIO_Pin_9;			// TX-RX UART
  GPIO_InitStructure.GPIO_Mode   = GPIO_Mode_AF;
 	GPIO_InitStructure.GPIO_OType  = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd   = GPIO_PuPd_NOPULL;
 	GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOD, &GPIO_InitStructure);	
		//UART2
	GPIO_InitStructure.GPIO_Pin    = GPIO_Pin_5 | GPIO_Pin_6;			// TX-RX UART
  GPIO_InitStructure.GPIO_Mode   = GPIO_Mode_AF;
 	GPIO_InitStructure.GPIO_OType  = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd   = GPIO_PuPd_NOPULL;
 	GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOD, &GPIO_InitStructure);	
	
	
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_USART3);   // USART3_TX
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_USART3);  // USART3_RX

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2);   // USART1_TX
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2);  // USART1_RX
	// Uart configure
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
  USART_Init(USART3, &USART_InitStructure);	

	USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
  USART_Init(USART2, &USART_InitStructure);	
	
	//enable the USART receive interrupt
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE); 
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;		
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;// this sets the priority group
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; // this sets the subpriority inside the group
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);			
	USART_Cmd(USART3, ENABLE);
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); 
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;		
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;// this sets the priority group
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; // this sets the subpriority inside the group
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);			
	USART_Cmd(USART2, ENABLE);

	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE); 				// bat xung clock port D
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	 if (SysTick_Config(SystemCoreClock / 1000))
  { 
    /* Capture error */ 
    while (1);
  }
void TIM3_Read_Config(void);
	TIM3_Read_Config();
	TIM1->CCR1 = 19999;
	TIM1->CCR2 = 19999;
	TIM1->CCR3 = 19999;
	//Init_sim900();
	while(1)
		{
			Delay(200);
		}
}

void TIM_PWM_Configuration(void)
{ 
	TIM_TimeBaseInitTypeDef    TIM_TimeBaseStructure;
	TIM_OCInitTypeDef          TIM_OCInitStructure;
	GPIO_InitTypeDef           GPIO_InitStructure;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; //cung thay doi lien tuc
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOA, &GPIO_InitStructure); 
  
 //cau hinh la timer1, do 1 pin co nhieu timer quan li
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_TIM1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_TIM1); 
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource0, GPIO_AF_TIM1);
  
  /* Time base configuration */
	//PrescalerValue = (uint16_t) ((SystemCoreClock) / 10000000) - 1; //tinh tan so 10Mhz

  TIM_TimeBaseStructure.TIM_Prescaler = 0; // prescaler =0 => max speed
  TIM_TimeBaseStructure.TIM_Period = 20000;   //  f=1khz
  TIM_TimeBaseStructure.TIM_ClockDivision = 0; //giu co dinh de de tinh toan
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //dem len

  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //outut compare
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;// su dung kenh PWM dao.
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High; //uu tien
  TIM_OCInitStructure.TIM_Pulse = 0; // gia tri ban dau bang 0
  //TIM_OCStructInit(&TIM_OCInitStructure);
  
  TIM_OC1Init(TIM1, &TIM_OCInitStructure);  
  TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);

  TIM_OC2Init(TIM1, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);

  TIM_OC3Init(TIM1, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);

  TIM_ARRPreloadConfig(TIM1, ENABLE);

  /* TIM1 enable counter */
  TIM_Cmd(TIM1, ENABLE);
  TIM_CtrlPWMOutputs(TIM1, ENABLE); // neu dung timer1 or 8 thi can dung nay, con lai thi kg can dung den.
}
void TIM3_Read_Config()
{
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	GPIO_InitTypeDef       GPIO_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
   /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = ((SystemCoreClock/8)/10000000)-1;     // frequency = 1000000
  TIM_TimeBaseStructure.TIM_Period = 1000 - 1;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //gan gia tri vao thanh ghi tuong ung
  TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
  TIM_Cmd(TIM3, ENABLE);
    
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure); 
}
void ADC_config()
{
	 ADC_InitTypeDef       ADC_InitStructure;
  ADC_CommonInitTypeDef ADC_CommonInitStructure;
  DMA_InitTypeDef       DMA_InitStructure;
  GPIO_InitTypeDef      GPIO_InitStructure;

  /* Enable ADC3, DMA2 and GPIO clocks ****************************************/
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2 | RCC_AHB1Periph_GPIOC, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);

  /* DMA2 Stream0 channel0 configuration **************************************/
  DMA_InitStructure.DMA_Channel = DMA_Channel_2;  
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC3_DR_ADDRESS ;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&ADC3ConvertedValue;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = 4;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA2_Stream0, &DMA_InitStructure);
  DMA_Cmd(DMA2_Stream0, ENABLE);

  /* Configure ADC3 Channel12 pin as analog input ******************************/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /* ADC Common Init **********************************************************/
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
  ADC_CommonInit(&ADC_CommonInitStructure);

  /* ADC3 Init ****************************************************************/
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfConversion = 4;
  ADC_Init(ADC3, &ADC_InitStructure);

  /* ADC3 regular channel12 configuration *************************************/
  ADC_RegularChannelConfig(ADC3, ADC_Channel_10, 1, ADC_SampleTime_3Cycles);
  ADC_RegularChannelConfig(ADC3, ADC_Channel_11, 2, ADC_SampleTime_3Cycles);
	ADC_RegularChannelConfig(ADC3, ADC_Channel_12, 3, ADC_SampleTime_3Cycles);
  ADC_RegularChannelConfig(ADC3, ADC_Channel_13, 4, ADC_SampleTime_3Cycles);
 /* Enable DMA request after last transfer (Single-ADC mode) */
  ADC_DMARequestAfterLastTransferCmd(ADC3, ENABLE);

  /* Enable ADC3 DMA */
  ADC_DMACmd(ADC3, ENABLE);

  /* Enable ADC3 */
  ADC_Cmd(ADC3, ENABLE);
	
	 ADC_SoftwareStartConv(ADC3);
}



//Program Size: Code=2744 RO-data=424 RW-data=124 ZI-data=2380  