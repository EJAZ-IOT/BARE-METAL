#include "stm32l4xx.h"                  // Device header

int analogValue;
int main(void)
{
	RCC->AHB2ENR |=1;            //PORTA clock
	GPIOA->MODER |=0xc;
  GPIOA->ASCR |=0x2;           //connect analog switch to ADC input recommended in datasheet

	RCC->AHB2ENR |=0x2000;       //Enable clock for ADC
	
	ADC1->CR = 0;
	ADC1->SQR1 =0x180;    //PA1 connected to channel 6 of ADC1
	ADC1->CR |=1;
	
	while(1)
	{
		ADC1->CR |=0x4;     //start conversion
		
		while(!(ADC1->ISR &4)){}
			analogValue = ADC1->DR;
		}
	}
	
