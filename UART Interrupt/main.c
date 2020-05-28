#include "stm32l4xx.h"                  // Device header

void USART2_Init(void);
void LED_play(int value);
void SystickDelayMs(int n);
void USART2_IRQHandler(void);

int main(void)
{
	__disable_irq();
	
	RCC->AHB2ENR |=1;
	GPIOA->MODER &=~0xc00;
	GPIOA->MODER |=0x400;
  
	USART2_Init();
	USART2->CR1 |=0x20;                  //Enable UART2 RX Interrupt
   
  NVIC_EnableIRQ(USART2_IRQn);
  
  __enable_irq();
	
	while(1){}
}

void USART2_Init(void)
 {
	RCC->AHB2ENR |=1;                    //Initialize clock for GPIOA
	RCC->APB1ENR1 |= 0x20000;            //Initialize clock for USART2
	
	GPIOA->AFR[0] |=0x7000;              //Enable alternate function for PA3 USART2 RX
	GPIOA->MODER  &=~0xc0;               //Reset PA3
	GPIOA->MODER  |=0x80;                //Setting PA3 for AF
	
	USART2->BRR = 0x341;                 //Baud RATE 4800
	USART2->CR1 |= 0x0004;                //PIN 2 FOR RX MODE
	USART2->CR1 |= 1;                    //Enable USART MODE

}
 
void LED_play(int value)
{
		value %=16;
		for(;value>0;value--)
		{
			GPIOA->BSRR = 0x020;
			SystickDelayMs(100);
			GPIOA->BSRR =0x00200000;
			SystickDelayMs(100);
		}
    SystickDelayMs(400);
	}

void SystickDelayMs(int n)
{
		SysTick->LOAD = 16000-1;          //reload with number of clocks per millisecond
	  SysTick->VAL  = 0;                 //clear current value register
	  SysTick->CTRL = 0x05;                 //systick control and status register enable
		
		for(int i=0;i<n;i++)
		{
			while((SysTick->CTRL & 0x10000) ==0){}
				
			}
		SysTick->CTRL =0;
		}	

void USART2_IRQHandler(void)
{
	  char c;
		if(USART2->ISR & 0x20)                  //WAIT for status BUFFER
		{
			c = USART2->RDR;
			LED_play(c);
		}
}
