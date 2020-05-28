#include "stm32l4xx.h"                  // Device header


void SystickDelayMs(int n);

int main(void)
{
	RCC->AHB2ENR |=1;
	GPIOA->MODER &=~0xc00;
	GPIOA->MODER |=0x400;
	while(1)
	{
		SystickDelayMs(10);            ///10ms delay
		GPIOA->ODR ^=0x20;
	}
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
