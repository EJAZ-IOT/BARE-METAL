#include "stm32l4xx.h"                  // Device header

//Toggle led PA5 using TIM2 Compare Mode

int main(void)
{
	RCC->AHB2ENR |=1;
	GPIOA->MODER &=~0xc00;
	GPIOA->MODER |=0x800;
	GPIOA->AFR[0] |=0x00100000;
	
	//configuring TIM2
	
  RCC->APB1ENR1 |=1;
	TIM2->PSC      = 1600-1;
	TIM2->ARR      = 1000;
	TIM2->CCMR1    =0x30;    //set output toggle on match
	TIM2->CCR1     =0;       //set match mode
	TIM2->CCER    |=1;       //Enable channel1 compare mode
	TIM2->CNT      =0;       //clear counter
	TIM2->CR1      =1;       //Enable TIM2
	
	while(1){}
	}

	
