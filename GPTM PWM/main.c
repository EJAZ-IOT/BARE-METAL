#include "stm32l4xx.h"                  // Device header

int main(void)
{

  RCC->AHB2ENR |=1;
	GPIOA->MODER &=~0xc00;
	GPIOA->MODER |=0x800;
	GPIOA->AFR[0] |=0x00100000;
	
	//configuring TIM2
	
  RCC->APB1ENR1 |=1;
	TIM2->PSC      = 10-1;         //1.6MHz
	TIM2->ARR      = 26667-1;
	TIM2->CCMR1    =0x60;         //Enable PWM mode
	TIM2->CCR1     =8889-1;       //Pulse width 1/3 of period
	TIM2->CCER    |=1;            //Enable PWM channel 1
	TIM2->CNT      =0;            //clear counter
	TIM2->CR1      =1;            //Enable TIM2
	while(1){}
	
	}
