#include "stm32l4xx.h"                  // Device header
 //PA5 Led
 //PC13 Button
 void SystickDelayMs(int n);
 void EXTI15_10_IRQHandler(void);
 
 int main(void)
 {
	 __disable_irq();                       //disbale all interrupt req
	 RCC->AHB2ENR |=1;                     //enable clock for PA5
	 RCC->AHB2ENR |=4;                     //enable clock for PA13 user button
	 RCC->APB2ENR |=1;                    //enable SYSCFG clock
	 
	 GPIOA->MODER &=~0xc00;
	 GPIOA->MODER |=0x400;
	 GPIOC->MODER &=~0xC000000;
	 
	 SYSCFG->EXTICR[3] =0x0020;          //setting pc13 as external interrupt
	 
	 EXTI->IMR1 |=0x2000;               //unmask interrupt at pc13
	 EXTI->FTSR1 |=0x2000;              //setting interrupt at trailing edge
	 
	 NVIC_EnableIRQ(EXTI15_10_IRQn);     //enable NVIC
	 
	 __enable_irq();                    //enable request
	 
	 while(1){}
 }
	 
void EXTI15_10_IRQHandler(void)          //ISR
{
	GPIOA->BSRR |=0x20;                    //set PA5 i.e turn ON LEd
	SystickDelayMs(200);
	GPIOA->BSRR |=0x00200000;              //reset PA5 i.e turn OFF LEd
	SystickDelayMs(200);
	GPIOA->BSRR |=0x20;
	SystickDelayMs(200);
	GPIOA->BSRR |=0x00200000;
	SystickDelayMs(200);
	EXTI->PR1=0x2000;
	
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

	

