#include "stm32l4xx.h"                  // Device header

void EXTI15_10_IRQHandler(void);
void SystickDelayMs(int n);
void LED_play(int value);
int counter;

int main(void)
 {
	 __disable_irq();                       //disbale all interrupt req
	 RCC->AHB2ENR |=1;                     //enable clock for PA5
	 RCC->AHB2ENR |=2;
	 RCC->AHB2ENR |=4;                     //enable clock for PC13 user button
	 RCC->APB2ENR |=1;                    //enable SYSCFG clock
	 
	 GPIOA->MODER &=~0xc00;
	 GPIOA->MODER |=0x400;
	 GPIOB->MODER &=~0x300000;
	 GPIOC->MODER &=~0xC000000;
	 
	 SYSCFG->EXTICR[3] =0x0020;          //setting pc13 as  interrupt
	 
	 EXTI->IMR1 |=0x2000;               //unmask interrupt at pc13
	 EXTI->FTSR1 |=0x2000;              //setting interrupt at Fallling Trigger
	 
	 GPIOB->PUPDR |=0x100000;           //pill up GPIOB pin10
	 
	 SYSCFG->EXTICR[2] =0x100;         //PB10 as Interrupt
	 
	 EXTI->IMR1 |=0x400;              //Unmask
	 
	 EXTI->FTSR1 |=0x400;             //FAlling trigger
	 
	 NVIC_EnableIRQ(EXTI15_10_IRQn);     //enable NVIC
	 
	 __enable_irq();                    //enable request
	 
	 while(1){}
 }
 
 void EXTI15_10_IRQHandler(void)       //Interrupt Handler Program
 {
	 if(EXTI->PR1==0x2000)               //Checking for Interrupt by Pending Request Register
	 {
		 counter=4;
		 LED_play(counter);
		 EXTI->PR1=0x2000;               //Clearing Pending Reuest bit
	 } 
 else if(EXTI->PR1==0x400)
	 {
		 counter =2;
		 LED_play(counter);
		 EXTI->PR1=0x400;
	 }
 
 }
 
 void LED_play(int value)
{
		  while(value>0){
			GPIOA->BSRR |= 0x020;
			SystickDelayMs(200);
			GPIOA->BSRR |=0x00200000;
			SystickDelayMs(200);
			value--;
		}}
 
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
