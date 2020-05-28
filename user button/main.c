#include "stm32l4xx.h"                  // Device header

int main(void)
{
	RCC->AHB2ENR |=4;       //ENABLE PORT C
	RCC->AHB2ENR |=1;       //ENABLE PORT A
	
	GPIOA->MODER &=~0xC00;
	GPIOC->MODER &=~0xC000000;
	GPIOA->MODER |=0x400;
	
	while(1)
	{
		if(GPIOC->IDR & 0x2000)    // if PC13 is High
		{
			GPIOA->BSRR |=0x002;     // Turn off Led
		}
    else
		{
      GPIOA->BSRR  |= 0x20;      // Turn on the led
		}
   
	}
}	
