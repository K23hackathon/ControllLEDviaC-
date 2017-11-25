#include "stm32f4xx.h"
#include "lcd.h"

// Data output 
#define     LCM_OUT               GPIOD->ODR
// Pin R/W connect GND
#define     LCM_PIN_RS            GPIO_Pin_0          // D0
#define     LCM_PIN_EN            GPIO_Pin_1          // D1
#define     LCM_PIN_D7            GPIO_Pin_7          // D7
#define     LCM_PIN_D6            GPIO_Pin_6          // D6
#define     LCM_PIN_D5            GPIO_Pin_5          // D5
#define     LCM_PIN_D4            GPIO_Pin_4          // D4

#define     LCM_PIN_MASK  ((LCM_PIN_RS | LCM_PIN_EN | LCM_PIN_D7 | LCM_PIN_D6 | LCM_PIN_D5 | LCM_PIN_D4))
#define     FALSE                 0
#define     TRUE                  1

void __delay_cycles(int a)
{
    int i = 0;
    int f = 0;
    while(f<a)
    {
            while(i<60)
                {i++;}
        f++;
    }
}
void PulseLcm(void)
{
    LCM_OUT &= ~LCM_PIN_EN;
    __delay_cycles(500);
    LCM_OUT |= LCM_PIN_EN;
    __delay_cycles(500);
    LCM_OUT &= (~LCM_PIN_EN);
    __delay_cycles(500);
}

void SendByte(char ByteToSend, int IsData)
{
    LCM_OUT &= (~LCM_PIN_MASK);
    LCM_OUT |= (ByteToSend & 0xF0);

    if (IsData == TRUE)
    {
        LCM_OUT |= LCM_PIN_RS;		// data
    }
    else
    {
        LCM_OUT &= ~LCM_PIN_RS;		// instruction
    }
    PulseLcm();
    LCM_OUT &= (~LCM_PIN_MASK);
    LCM_OUT |= ((ByteToSend & 0x0F) << 4);

    if (IsData == TRUE)
    {
        LCM_OUT |= LCM_PIN_RS;
    }
    else
    {
        LCM_OUT &= ~LCM_PIN_RS;
    }

    PulseLcm();
}
void Cursor(char Row, char Col)
{
    char address;
    if (Row == 0)
    {
        address = 0;			// first row
    }
    else
    {
        address = 0x40;		// second row
    }

    address |= Col;
    SendByte(0x80 | address, FALSE);
}

void ClearLcmScreen(void)
{
    SendByte(0x01, FALSE); // clear display
    SendByte(0x02, FALSE);	// return home
}
void InitializeLcm(void)
{
GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_4 | GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    LCM_OUT &= ~(LCM_PIN_MASK);
    __delay_cycles(32000);
    __delay_cycles(32000);
    __delay_cycles(32000);

    LCM_OUT &= ~LCM_PIN_RS;
    LCM_OUT &= ~LCM_PIN_EN;
    LCM_OUT = 0x20;
    PulseLcm();
    SendByte(0x28, FALSE);
    SendByte(0x0E, FALSE);
    SendByte(0x06, FALSE);
}
void PrintStr(char *Text)
{
    char *c;

    c = Text;

    while ((c != 0) && (*c != 0))
    {
        SendByte(*c, TRUE);
        c++;
    }
}
