//PA5 led
//AHB2
//RCC_AHB2ENR
//GPIOx_MODER
//GPIOx_ODR

#include "stm32l4xx.h"                  // Device header
void delay(int i);                     //Delay function
int main(void)
{
	RCC->AHB2ENR |=1;                   //Enable AHB2 bus clock
	
	GPIOA->MODER &= ~0x00003C00; 	//Reset Mode Register
	GPIOA->MODER |=0x1400;               //Setting Mode to output
	while(1)
	{
		GPIOA->ODR |=0x60;  		//setting output of port A pin 5      //setting output of port A pin 6
		delay(100);
		GPIOA->ODR &=~0x60; 		//clear output of port A pin 5     //clear output of port A pin 6
		delay(100);
	}
}	
	
 void delay(int i)
 {
	 for( ; i>0;i--){                 //delay using for loop
	  for(int j=0;j<3195;j++);
 }
	} 
