#include "stm32l4xx.h"                  // Device header

int period;
float freq;


int main(void)
{
	int last_value =0;
	int current_value=0;
	
	
	RCC->AHB2ENR |=1;
	GPIOA->MODER &=~0xc00;
	GPIOA->MODER |=0x800;
	GPIOA->AFR[0] |=0x00100000;
	
	//configuring TIM2
	
  RCC->APB1ENR1 |=1;
	TIM2->PSC      = 1600-1;
	TIM2->ARR      = 10000;
	TIM2->CCMR1    =0x30;    //set output toggle on match
	TIM2->CCR1     =0;       //set match mode
	TIM2->CCER    |=1;       //Enable channel1 compare mode
	TIM2->CNT      =0;       //clear counter
	TIM2->CR1      =1;       //Enable TIM2
	
	//config PA6
	RCC->AHB2ENR |=1;           //Enabling clock for PA6
	GPIOA->MODER &=~0x3000;
	GPIOA->MODER |=0x2000;       //setting PA6 mode to AF
	GPIOA->AFR[0] |=0x2000000;   //Setting PA6 to AF2 which is TIM3 CH 1
	//config TIM3
	RCC->APB1ENR1  |=2;          //Enable clock for TIM3
	TIM3->PSC = 16000-1;    	
	TIM3->CCMR1 =0x41;      //set channel 1 to capture at every edge at frequency dts/2
	TIM3->CCER |=0x0B;         //Enable capture mode and capture at both edges
	TIM3->CR1  =1;          //Enable TIM3
	
	while(1){
		while(!(TIM3->SR &2)){}            //Status register bit1 set when input captured
			current_value = TIM3->CCR1;  
      period = current_value-last_value;    //time period calculation
      last_value = current_value;            
      freq = 1000.0f/period	;		           //frequency calculation
		}
	}
