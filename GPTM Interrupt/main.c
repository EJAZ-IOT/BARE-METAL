#include "stm32l4xx.h"                  // Device header

//Toggle Led Using TIM2 at 1Hz using interrupt
//system clock is 16MHz

int main(void)
{
	__disable_irq();
	
	RCC->AHB2ENR |=1;
	GPIOA->MODER &=~0xc00;
	GPIOA->MODER |=0x400;
	
	//TIM2 Config
	
	RCC->APB1ENR1 |=1;    //Enable clock for TIM2
	TIM2->PSC =1600-1;    //16000000 divide by 1600=10000
	TIM2->ARR =10000-1;     //10000 divide by 10000=1
	TIM2->CNT =0;         //clear the counter
	TIM2->CR1 =1;         //Enable TIM2
	TIM2->DIER |=1;
	NVIC_EnableIRQ(TIM2_IRQn);
	
	__enable_irq();
	
	while(1){}
}

void TIM2_IRQHandler(void)
{
	TIM2->SR =0;               //clear status flag
	GPIOA->ODR ^=0x20;
}
