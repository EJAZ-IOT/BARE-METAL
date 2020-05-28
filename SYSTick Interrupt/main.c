#include "stm32l4xx.h"                  // Device header

//configure sytick interrupt to toggle LEd
//at 1Hz, system clock is 16MHz

int main(void)
{
	__disable_irq();
	
	RCC->AHB2ENR |=1;
	GPIOA->MODER &=~0xc00;
	GPIOA->MODER |=0x400;
	
	SysTick->LOAD =16000000-1;
	SysTick->VAL =0;
	SysTick->CTRL=7;                //Enable Counter,Clock source to processor and systick exception request
	
	__enable_irq();
	
	while(1){}
		
	}

void SysTick_Handler(void)
{
	GPIOA->ODR ^=0x20;
}
	