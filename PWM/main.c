
#include "stm32f4xx.h"
#include "lcd.h"
#include "string.h"
#include "HCSR04.h"

#define ADC3_DR_ADDRESS     ((uint32_t)0x4001224C)
__IO uint16_t ADC3ConvertedValue[4]={0};
volatile float distance1;
/*

	Define connect sim900 and ARM Discovery
	// UART2 - UART SIM
	PD7 connect to PWR
	PD5 (TX) ----- RX (SIM900)
	PD6 (RX) ----- TX (SIM900)
	
	Define connect to C#
	// UART3 -- UART PC
	PD8 (TX) ----- RX (PC)
	PD9 (RX) ----- TX (PC)
	
	Define connect to Driver
	PA8 (TIM1_CH1) -----  LED1 (DRIVER)
	PA9  (TIM1_CH2) -----  LED2	(DRIVER)
	PA10 (TIM1_CH3) -----  LED3 (DRIVER)
	
	Define connect to Ampmeter
	PA0 (ADC1_CH0) ----- CURRENT LED No1
	PA1 (ADC1_CH1) ----- CURRENT LED No2
	PA2 (ADC1_CH2) ----- CURRENT LED No3
	PA3 (ADC1_CH3) ----- CURRENT SUM
	
	Define connect to Sensor Distance
	PD1 (ARM)-----TRIG
	PC6 (AR)------ECHO
	
	// cu phap tin nhan: ~12345XXX@
	// trong do XXX la cac gia tri sau:
	LED1ON : Turn On LED No1
	LED1OFF : Turn Off LED No1
	LED2ON : Turn On LED No2
	LED2OFF : Turn Off LED No2
	LED3ON : Turn On LED No3
	LED3OFF : Turn Off LED No3

	example: ~123456LED1ON@
	example: ~123456LED1OFF@
*/

// 
#define PWR_UP GPIO_Pin_7


// khai bao cac cau truc GPIO, ngat, UART
GPIO_InitTypeDef       GPIO_InitStructure;
NVIC_InitTypeDef       NVIC_InitStructure;
USART_InitTypeDef 		 USART_InitStructure;
ADC_InitTypeDef ADC_InitStructre;
ADC_CommonInitTypeDef ADC_CommonInitStructure ;

char *ptr1=0;
char *ptr2=0;
char ok[] = "OK";
char MK[] ="123456";
char num1[]="0963739229";

char mo_tb1[]="LED1ON";
char tat_tb1[]="LED1OFF";
char mo_tb2[]="LED2ON";
char tat_tb2[]="LED2OFF";
char mo_tb3[]="LED3ON";
char tat_tb3[]="LED3OFF";
char sensorss[]="sen"; 

__IO uint8_t  data;
static __IO uint32_t TimingDelay;
uint16_t PrescalerValue = 0; 
int sa=0;
char c = 0x00;
char c1 = 0x00;
char d = 0x00;
char d1 = 0x00;
float a_,b_,c_,d_;

//C#
const int buffer_size =100;
int16_t xbuff=0;
short end_buffer=0;
short sms_mode = 0;
char buf_fer[buffer_size];
short receive_value = 0;
short sensor=0;  ////////
//SIM
const int buffer_size1 =1300;
int16_t xbuff1=0;
short end_buffer1=0;
short sms_mode1 = 0;
char buf_fer1[buffer_size1];
// PWM variable
uint16_t PWM_Value[3] = {0,0,0};
// ADC variable
uint32_t ADC_Value[4] = {0,0,0,0};
char ADC_Float_Value_0[4] = { 0,0,0,0};
char ADC_Float_Value_1[4] = { 0,0,0,0};
char ADC_Float_Value_2[4] = { 0,0,0,0};
char ADC_Float_Value_3[4] = { 0,0,0,0};
uint16_t ADCCH0_Temp[80];
uint16_t ADCCH1_Temp[80];
uint16_t ADCCH2_Temp[80];
uint16_t ADCCH3_Temp[80];
uint8_t da_ta[10];
uint16_t kq;

void Delay(__IO uint32_t nTime);
void TimingDelay_Decrement(void);
void TIM_PWM_Configuration();
void ADC_Read();
void ADC_config();
void TIM3_Read_Config();
void check_CB();
void check_cb();
void CheckValueCShap();
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
char *mang = "NhiDoan";
void send_s( char *str_data )
{
  char dodai=0;
  while(*str_data )
  {
		Putchar(*str_data);
    *str_data++;
    dodai--;
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
short wait_ok()
{
	if(strstr(buf_fer1,"OK") != 0)
		return 1;
	else
		return 0;
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
      d = USART_ReceiveData(USART2); 
			// kiem tra cu phap sms: bat dau bang @ ve ket thuc bag ~
			if(d=='?')
			{
				d1 = d; xbuff1=0;
				
			}
			if((d1=='?')&&(d=='@'))
			{
				sms_mode1 = 1;
			}
			if(xbuff1 >= buffer_size1)
			{xbuff1=0;}
			else
			{
				// luu ky tu nhan duoc vao bang buf_fer[]
				buf_fer1[xbuff1++] = d;
			}
		}
		//xoa co nga UART1
	USART_ClearITPendingBit(USART2, USART_IT_RXNE);
}
//ham khai bao cau hinh sim900
void Init_sim900(void)
{
//	// bat nguon hoat dong cho module
	GPIO_SetBits(GPIOD,PWR_UP);
	Delay(2000); //delay 2s
	GPIO_ResetBits(GPIOD,PWR_UP);
	Delay(10000);
//	// kiem tra ket noi giua module va ARM
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
	send_sms(num1,0);
	GPIO_ResetBits(GPIOD,GPIO_Pin_13);
}
void check_cb()//sim
{
	if(sms_mode1 ==1)
	{
		ptr1 = strstr(buf_fer1,MK);
		if(strncmp(ptr1,MK,6)==0)
		{
			ptr2 = strstr(buf_fer1,mo_tb1);
			if(strncmp(ptr2,mo_tb1,3)==0)
			{
				GPIO_SetBits(GPIOD,GPIO_Pin_12);
				//PrintStr("TB 1 dang ON ");
				send_sms(num1,1);
				//send_s1("@LED1ON~");
				send_s("@LED1ON~");
				TIM1->CCR1 = 0* 19999 / 100;
			}
			else
			{
				ptr1 =strstr(buf_fer1,tat_tb1);
				if(strncmp(ptr1,tat_tb1,4)==0)
				{
					GPIO_ResetBits(GPIOD,GPIO_Pin_12);
					//PrintStr("TB 1 dang OFF  ");
					send_sms(num1,2);
					//send_s1("@LED1OFF~");
					send_s("@LED1OFF~");
					TIM1->CCR1 = 100 * 19999 / 100;
				}
			}
			
			ptr2 = strstr(buf_fer1,mo_tb2);
			if(strncmp(ptr2,mo_tb2,3)==0)
			{
				//PrintStr("TB 2 dang ON ");
				GPIO_SetBits(GPIOD,GPIO_Pin_13);
				send_sms(num1,3);
				//send_s1("@LED2ON~");
				send_s("@LED2ON~");
				TIM1->CCR2 = 0* 19999 / 100;
			}
			else
			{
				ptr1 =strstr(buf_fer1,tat_tb2);
				if(strncmp(ptr1,tat_tb2,4)==0)
				{
					//PrintStr("TB 2 dang OFF  ");
					GPIO_ResetBits(GPIOD,GPIO_Pin_13);
					send_sms(num1,4);
					//send_s1("@LED2OFF~");
					send_s("@LED2OFF~");
					TIM1->CCR2 = 100 * 19999 / 100;
				}
			}
			
			ptr2 = strstr(buf_fer1,mo_tb3);
			if(strncmp(ptr2,mo_tb3,3)==0)
			{
				//PrintStr("TB 3 dang ON ");
				GPIO_SetBits(GPIOD,GPIO_Pin_14);
				send_sms(num1,5);
				//send_s1("@LED3ON~");
				send_s("@LED3ON~");
				TIM1->CCR3 = 0* 19999 / 100;
			}
			else
			{
				ptr1 =strstr(buf_fer1,tat_tb3);
				if(strncmp(ptr1,tat_tb3,4)==0)
				{
					//PrintStr("TB 3 dang OFF  ");
					GPIO_ResetBits(GPIOD,GPIO_Pin_14);
					send_sms(num1,6);
					//send_s1("@LED3OFF~");
					send_s("@LED3OFF~");
					TIM1->CCR3 = 100 * 19999 / 100;
				}
			}
		}
		else
		{
			PrintStr("Wrong Password");
			send_sms(num1,9);
		}
		ClearLcmScreen(); // xoa man hinh 
		sms_mode1=0;
	}
}
//ham ngat nhan UART t C#
void USART3_IRQHandler(void)
{
	if( USART_GetITStatus(USART3, USART_IT_RXNE) )
		{	
			while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);
      c = USART_ReceiveData(USART3); 
			// kiem tra cu phap sms: bat dau bang # ve ket thuc bag .
			if(c=='@')
			{
				c1 = c; xbuff=0;
			}
			if((c=='~')&&(c1=='@'))
			{
				sms_mode = 1;
			}
			if((c == '*') && (c1 == '@'))
			{
				receive_value = 1;
			}
			if(xbuff>= buffer_size)
			{xbuff=0;}
			else
			{
				// luu ky tu nhan duoc vao bang buf_fer[]
				buf_fer[xbuff++] = c;
			}
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
		if(times < 80)
		{
			ADCCH0_Temp[times] = ADC3ConvertedValue[0];
			ADCCH1_Temp[times] = ADC3ConvertedValue[1];
			ADCCH2_Temp[times] = ADC3ConvertedValue[3];
			ADCCH3_Temp[times] = ADC3ConvertedValue[2];
		}
		else
		{
			ADC_Value[0]=0;
			ADC_Value[1]=0;
			ADC_Value[2]=0;
			ADC_Value[3]=0;
			for(k=0;k<80;k++)
			{
				ADC_Value[0] += ADCCH0_Temp[k];
				ADC_Value[1] += ADCCH1_Temp[k];
				ADC_Value[2] += ADCCH2_Temp[k];
				ADC_Value[3] += ADCCH3_Temp[k];
			}
			ADC_Value[0] /= 80;
			ADC_Value[1] /= 80;
			ADC_Value[2] /= 80;
			ADC_Value[3] /= 80;
			
			times=0;
		}
		times++;
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update); 
	}
	
}

int main(void)
{
		 if (SysTick_Config(SystemCoreClock / 1000))
  { 
    /* Capture error */ 
    while (1);
  }
//	Init_sim900();
//	HCSR04_GPIO_Init();
//	HCSR04_TIM_Init();///Timer  Init 
//	Init_sim900();
	
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
	

//	

		TIM_PWM_Configuration();
		ADC_config();
		TIM3_Read_Config();
		if(sensor!=2){
		TIM1->CCR1 = 19999;
	TIM1->CCR2 = 19999;
	TIM1->CCR3 = 19999;}
		//Init_sim900();
		GPIO_SetBits(GPIOD,GPIO_Pin_12);
	HCSR04_GPIO_Init();
	HCSR04_TIM_Init();///Timer  Init 
	while(1)
		{
			Sonic_Read1();
			ADC_Read();
			check_CB();
			check_cb();
			CheckValueCShap();	
		//	Delay(100);
		}
}

void check_CB()//c#
{
	if(sms_mode == 1)
	{
			if(strstr(buf_fer,mo_tb1) != 0)
			{
					GPIO_SetBits(GPIOD,GPIO_Pin_12);
					send_s("@LED1ON~");
					TIM1->CCR1 =0; 
			}
			if(strstr(buf_fer,tat_tb1) != 0)
			{
					GPIO_ResetBits(GPIOD,GPIO_Pin_12);
					send_s("@LED1OFF~");
					TIM1->CCR1 =19999;
				  ADC_Cmd(ADC3, DISABLE);

			}
			if(strstr(buf_fer,mo_tb2) != 0)
			{
					GPIO_SetBits(GPIOD,GPIO_Pin_13);
					send_s("@LED2ON~");
					TIM1->CCR2 =0;
			}
			if(strstr(buf_fer,tat_tb2) != 0)
			{
					GPIO_ResetBits(GPIOD,GPIO_Pin_13);
					send_s("@LED2OFF~");
					TIM1->CCR2 =19999;
								  ADC_Cmd(ADC3, DISABLE);
 
			}
			if(strstr(buf_fer,mo_tb3) != 0)
			{
					GPIO_SetBits(GPIOD,GPIO_Pin_14);	
					send_s("@LED3ON~");
					TIM1->CCR3 = 0;
			}
			if(strstr(buf_fer,tat_tb3) != 0)
			{
					GPIO_ResetBits(GPIOD,GPIO_Pin_14);
					send_s("@LED3OFF~");
					TIM1->CCR3 =19999;
												  ADC_Cmd(ADC3, DISABLE);

			}
		if(strstr(buf_fer,sensorss) != 0)
		{
			sensor=sensor+1;
			if(sensor==3)
				sensor=1;
			sa=sensor;
		}
			sms_mode = 0;
	}
}
void CheckValueCShap() 
{
	
	unsigned char n=0;
//if(bien gui tu C==1)
	if(sensor==1)
	{
//	{
if(receive_value == 1)
	{

		for(n=0;n<buffer_size-10;n++)
		{
			if(buf_fer[n] == '@' && buf_fer[n+10] == '*')
			{
				PWM_Value[0] = (buf_fer[n+1] - 48)*100 + (buf_fer[n+2] - 48)*10 + (buf_fer[n+3] - 48);
				buf_fer[n+1] = buf_fer[n+2] = buf_fer[n+3] =0;
				PWM_Value[1] = (buf_fer[n+4] - 48)*100 + (buf_fer[n+5] - 48)*10 + (buf_fer[n+6] - 48);
				buf_fer[n+4] = buf_fer[n+5] = buf_fer[n+6] =0;
				PWM_Value[2] = (buf_fer[n+7] - 48)*100 + (buf_fer[n+8] - 48)*10 + (buf_fer[n+9] - 48);
				buf_fer[n+7] = buf_fer[n+8] = buf_fer[n+9] =0;
				buf_fer[n] = buf_fer[n + 10] = 0; 
			}
		}
		receive_value=0;

		if(PWM_Value[0] < 0 || PWM_Value[0] >100)
		{ 
			PWM_Value[0] =19999 - 0;
		}
		else
		{
			TIM1->CCR1 = 19999 - PWM_Value[0] * 19999 / 100;//gtri c# gan vo tghi
		}
		if(PWM_Value[1] < 0 || PWM_Value[1] >100)
		{ 
			PWM_Value[1] =19999 - 0;
		}
		else
		{
			TIM1->CCR2 =19999 - PWM_Value[1] * 19999 / 100;//gtri c# gan vo tghi
		}
		if(PWM_Value[2] < 0 || PWM_Value[2] >100)
		{ 
			PWM_Value[2] =19999 - 0;
		}
		else
		{
			TIM1->CCR3 =19999 -  PWM_Value[2] * 19999 / 100;//gtri c# gan vo tghi
		}
		receive_value=0;
		}
	}
// }
//	}
//	if(du lieu tu C =0)
	else if(sensor ==2)
//		{
	{if(distance1<=5)
		{
			TIM1->CCR3=0*19999/100;
			TIM1->CCR2=0*19999/100;
			TIM1->CCR1=0*19999/100;
			GPIO_SetBits(GPIOD,GPIO_Pin_13);	

			
		}
		else if(distance1<=20)
		{
			TIM1->CCR3=40*19999/100;
			TIM1->CCR2=40*19999/100;
			TIM1->CCR1=40*19999/100;
						GPIO_ResetBits(GPIOD,GPIO_Pin_13);	

		}
		else if(distance1<=30)
			{
			TIM1->CCR3=80*19999/100;
				TIM1->CCR2=80*19999/100;
				TIM1->CCR1=80*19999/100;
								GPIO_SetBits(GPIOD,GPIO_Pin_14);	

//		receive_value=0;
			}
	else if(distance1>30)
		{
			TIM1->CCR3=100*19999/100;
			TIM1->CCR2=100*19999/100;
			TIM1->CCR1=100*19999/100;
						GPIO_SetBits(GPIOD,GPIO_Pin_15);	

		}
//				receive_value=0;

	}
}

	
void ADC_Read( void)
{
	
	uint32_t a1;
	char m=0;
	// transfer from voltages to amperes
	if(PWM_Value[0] <= 10) a_ = ADC_Value[0] * 0.108351033;
	if(PWM_Value[0] <= 20 && PWM_Value[0] > 10) a_ = ADC_Value[0] * 0.17387868;
	if(PWM_Value[0] <= 30 && PWM_Value[0] > 20) a_ = ADC_Value[0] * 0.245406171;
	if(PWM_Value[0] <= 40 && PWM_Value[0] > 30) a_ = ADC_Value[0] * 0.2960305;
	if(PWM_Value[0] <= 50 && PWM_Value[0] > 40) a_ = ADC_Value[0] * 0.334137407;
	if(PWM_Value[0] <= 60 && PWM_Value[0] > 50) a_ = ADC_Value[0] * 0.388366653;
	if(PWM_Value[0] <= 70 && PWM_Value[0] > 60) a_ = ADC_Value[0] * 0.425494505;
	if(PWM_Value[0] <= 80 && PWM_Value[0] > 70) a_ = ADC_Value[0] * 0.477783086;
	if(PWM_Value[0] <= 90 && PWM_Value[0] > 80) a_ = ADC_Value[0] * 0.501283493;
	if(PWM_Value[0] <= 100 && PWM_Value[0] > 90) a_ = ADC_Value[0] * 0.537240537;
	
	if(PWM_Value[1] <= 10) b_ = ADC_Value[1] * 0.108351033;
	if(PWM_Value[1] <= 20 && PWM_Value[1] > 10) b_ = ADC_Value[1] * 0.17387868;
	if(PWM_Value[1] <= 30 && PWM_Value[1] > 20) b_ = ADC_Value[1] * 0.245406171;
	if(PWM_Value[1] <= 40 && PWM_Value[1] > 30) b_ = ADC_Value[1] * 0.2960305;
	if(PWM_Value[1] <= 50 && PWM_Value[1] > 40) b_ = ADC_Value[1] * 0.334137407;
	if(PWM_Value[1] <= 60 && PWM_Value[1] > 50) b_ = ADC_Value[1] * 0.388366653;
	if(PWM_Value[1] <= 70 && PWM_Value[1] > 60) b_ = ADC_Value[1] * 0.425494505;
	if(PWM_Value[1] <= 80 && PWM_Value[1] > 70) b_ = ADC_Value[1] * 0.477783086;
	if(PWM_Value[1] <= 90 && PWM_Value[1] > 80) b_ = ADC_Value[1] * 0.501283493;
	if(PWM_Value[1] <= 100 && PWM_Value[1] > 90) b_ = ADC_Value[1] * 0.537240537;
	
	if(PWM_Value[2] <= 10) c_ = ADC_Value[2] * 0.108351033;
	if(PWM_Value[2] <= 20 && PWM_Value[2] > 10) c_ = ADC_Value[2] * 0.17387868;
	if(PWM_Value[2] <= 30 && PWM_Value[2] > 20) c_ = ADC_Value[2] * 0.245406171;
	if(PWM_Value[2] <= 40 && PWM_Value[2] > 30) c_ = ADC_Value[2] * 0.2960305;
	if(PWM_Value[2] <= 50 && PWM_Value[2] > 40) c_ = ADC_Value[2] * 0.334137407;
	if(PWM_Value[2] <= 60 && PWM_Value[2] > 50) c_ = ADC_Value[2] * 0.388366653;
	if(PWM_Value[2] <= 70 && PWM_Value[2] > 60) c_ = ADC_Value[2] * 0.425494505;
	if(PWM_Value[2] <= 80 && PWM_Value[2] > 70) c_ = ADC_Value[2] * 0.477783086;
	if(PWM_Value[2] <= 90 && PWM_Value[2] > 80) c_ = ADC_Value[2] * 0.501283493;
	if(PWM_Value[2] <= 100 && PWM_Value[2] > 90) c_ = ADC_Value[2] * 0.537240537;
	
	d_ = a_ + b_ + c_;
	
	if(PWM_Value[0] == 0) a_ = 0;
	if(PWM_Value[1] == 0) b_ = 0;
	if(PWM_Value[2] == 0) c_ = 0;
	if(PWM_Value[0] == 0 && PWM_Value[1] == 0 && PWM_Value[2] == 0) d_ = 0;
	
//	a = ADC_Value[0] * 1.61;
//	b = ADC_Value[1] * 1.61;
//	c = ADC_Value[2] * 1.61;
//	d = ADC_Value[3] * 1.61;
	//
	a1 = a_*10;
	ADC_Float_Value_0[0] = a1/10000;
	a1 = a1 - ADC_Float_Value_0[0] * 10000;
	ADC_Float_Value_0[1] = a1/1000;
	a1 = a1 - ADC_Float_Value_0[1] * 1000;
	ADC_Float_Value_0[2] = a1/100;
	a1 = a1 - ADC_Float_Value_0[2] * 100;
	ADC_Float_Value_0[3] = a1/10;
	//
	a1 = b_*10;
	ADC_Float_Value_1[0] = a1/10000;
	a1 = a1 - ADC_Float_Value_1[0] * 10000;
	ADC_Float_Value_1[1] = a1/1000;
	a1 = a1 - ADC_Float_Value_1[1] * 1000;
	ADC_Float_Value_1[2] = a1/100;
	a1 = a1 - ADC_Float_Value_1[2] * 100;
	ADC_Float_Value_1[3] = a1/10;
	//
	a1 = c_*10;
	ADC_Float_Value_2[0] = a1/10000;
	a1 = a1 - ADC_Float_Value_2[0] * 10000;
	ADC_Float_Value_2[1] = a1/1000;
	a1 = a1 - ADC_Float_Value_2[1] * 1000;
	ADC_Float_Value_2[2] = a1/100;
	a1 = a1 - ADC_Float_Value_2[2] * 100;
	ADC_Float_Value_2[3] = a1/10;
	//
	a1 = d_*10;
	ADC_Float_Value_3[0] = a1/10000;
	a1 = a1 - ADC_Float_Value_3[0] * 10000;
	ADC_Float_Value_3[1] = a1/1000;
	a1 = a1 - ADC_Float_Value_3[1] * 1000;
	ADC_Float_Value_3[2] = a1/100;
	a1 = a1 - ADC_Float_Value_3[2] * 100;
	ADC_Float_Value_3[3] = a1/10;
	// send back data
	for(m=0;m<4;m++)
	{
		ADC_Float_Value_0[m] = ADC_Float_Value_0[m] + 48;
		ADC_Float_Value_1[m] = ADC_Float_Value_1[m] + 48;
		ADC_Float_Value_2[m] = ADC_Float_Value_2[m] + 48;
		ADC_Float_Value_3[m] = ADC_Float_Value_3[m] + 48;
	}
	Putchar('@');
	for (m =0;m<4;m++)
	{
		Putchar(ADC_Float_Value_0[m]);
		Delay(5);
	}
	for (m =0;m<4;m++)
	{
		Putchar(ADC_Float_Value_1[m]);
		Delay(5);
	}
	for (m =0;m<4;m++)
	{
		Putchar(ADC_Float_Value_2[m]);
		Delay(5);
	}
	for (m =0;m<4;m++)
	{
		Putchar(ADC_Float_Value_3[m]);
		Delay(5);
	}
	Putchar('*');
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
	PrescalerValue = (uint16_t) ((SystemCoreClock) / 10000000) - 1; //tinh tan so 10Mhz

  TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue; // prescaler =0 => max speed
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
void Delay(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
}
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}
void TIM8_CC_IRQHandler(void)//
{
		TIM_CAPTURE();
}
void TIM5_IRQHandler(void)//Interrupt Set Trigger Pin 
{
	//GPIO_SetBits(GPIOD,GPIO_Pin_14);
  if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) 
		{
			
			TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
			//Trigger_Time += 10; //when 10us			
			timeout();
		}
		
}
