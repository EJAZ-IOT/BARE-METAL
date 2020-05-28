#include "stm32l4xx.h"                  // Device header

int main(void)
{
	RCC->AHB2ENR |=1;
	GPIOA->MODER &=~0xc00;
	GPIOA->MODER |=0x400;
	//config systick timer
	SysTick->LOAD = 160000-1;          //setting value for timer
	SysTick->VAL  = 0;                 //reload value
	SysTick->CTRL = 5;                 //systick control and status register
	
	
	while(1)
	{
		if(SysTick->CTRL & 0x10000)      //checking count flag of systick register
		{
			GPIOA->ODR ^= 0x20;           //toggling led
		}
	}
}

