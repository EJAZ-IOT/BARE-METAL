//APB1 bit 17:USART2


#include "stm32l4xx.h"                  // Device header

void USART2_Init(void);
void USART_WRITE(int ch);
void delayMs(int delay);


int main(void)
{
	USART2_Init();
	while(1){
		USART_WRITE('E');
		USART_WRITE('J');
		USART_WRITE('A');
		USART_WRITE('Z');
		USART_WRITE(' ');
		delayMs(100);
	
	}
}

void USART2_Init(void)
{
	RCC->APB1ENR1 |=0x20000;    //enable apb1 pin 17 clock
	RCC->AHB2ENR  |=1;          // enable AHB2 bcz GPIOA connected to that
	
	GPIOA->AFR[0] = 0x0700;     // enabling alternate function for port a pin 2 PA2 (usart2 tx)
	GPIOA->MODER &=~0x30;       // reset pin 2 of pOrt A
	GPIOA->MODER |=0x0020;      // SETTING MODE TO ALTERNATE(10)
	
	USART2->BRR = 0x341;        // BAUD RATE 4800
	USART2->CR1 = 0x0008;       //SETTING BIT 3 OF CR1 FOR TX
	USART2->CR1 |= 1;           // ENABLING UART BY SETTING BIT 0
}

void USART_WRITE(int ch)
{
	while(!(USART2->ISR & 0x0080)){}     //CHECKING STATUS OF BUFFER
		USART2->TDR = (ch & 0xFF);         // ACCESSING FIRST EIGHT BIT OF TDR REGISTER
	}

	void delayMs(int delay)            // DELAY FUNCTION
	{
		int i;
		for(;delay>0;delay--)
		{
			for(i=0;i<3195;i++);
		}
	}

	
