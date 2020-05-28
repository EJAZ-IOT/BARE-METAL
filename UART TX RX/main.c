#include "stm32l4xx.h"                  // Device header


void USART_WRITE(int cha);
void USART2_Init(void);
char USART2_read(void);
void delayMs(int delay);
void LED_play(int value);


int main(void)
{
 RCC->AHB2ENR |=1;                    // Intialize clock for gpioa
 GPIOA->MODER &=~0xc00;               // reset
 GPIOA->MODER	|=0x400;                //PA5 led pin output mode
	
	USART2_Init();
	while(1){
		USART_WRITE('P');
		USART_WRITE('R');
		USART_WRITE('E');
		USART_WRITE('S');
		USART_WRITE('S');
		USART_WRITE(' ');
		USART_WRITE('K');
		USART_WRITE('E');
		USART_WRITE('Y');
		USART_WRITE('\n');
		USART_WRITE('\r');
		delayMs(10);
	
	char ch;
	while(1)
	{
		ch=USART2_read();
		LED_play(ch);
		break;
	}
}}	

 void USART2_Init(void)
 {
	RCC->AHB2ENR |=1;                    //Initialize clock for GPIOA
	RCC->APB1ENR1 |= 0x20000;            //Initialize clock for USART2
	
	GPIOA->AFR[0] |=0x7700;              //Enable alternate function for PA2 & PA3 USART2 RX & TX
	GPIOA->MODER  &=~0xF0;               //Reset PA2 & PA3
	GPIOA->MODER  |=0xA0;                //Setting PA2 & PA3 for AF
	
	USART2->BRR = 0x341;                 //Baud RATE 4800
	USART2->CR1 = 0x000C;                //PIN 2 & 3 FOR RX & TX MODE
	USART2->CR1 |= 1;                    //Enable USART MODE

}

void USART_WRITE(int cha)
{
	while(!(USART2->ISR & 0x0080)){}     //CHECKING STATUS OF BUFFER
		USART2->TDR = (cha & 0xFF);         // ACCESSING FIRST EIGHT BIT OF TDR REGISTER
	}

char USART2_read(void)
{
	while(!(USART2->ISR & 0x0020)){}     //WAIT FOR BUFFER
		return USART2->RDR;
	}

void LED_play(int value)
{
		value %=16;
		for(;value>0;value--)
		{
			GPIOA->BSRR = 0x020;
			delayMs(100);
			GPIOA->BSRR =0x00200000;
			delayMs(100);
		}
    delayMs(400);
	}

void delayMs(int delay)
{
	int i;
	for(;delay>0;delay--)
	{
		for(i=0;i<3195;i++);
	}
}	

