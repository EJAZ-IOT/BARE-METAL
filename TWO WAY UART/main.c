#include "stm32l4xx.h"                  // Device header
#include<stdio.h>

void USART2_Init(void);
int USART2_write(int ch);
int USART2_read(void);
int main(void)
{
	int n;
	char str[100];
	USART2_Init();
	printf("HELLO FROM OTHER SIDE\r\n");
	fprintf(stdout," test for stdout\r\n");
	fprintf(stderr,"test for stderr\r\n");
	
	while(1)
	{
		printf("HOW OLD ARE YOU ?");
		scanf("%d",&n);
		printf("YOUR AGE IS : %d\r\n",n);
		printf("ENTER YOUR FIRST NAME :");
		gets(str);
		printf("I LIKE YPUR STYLE:");
		puts(str);
		printf("\r\n");
	}
}
		

void USART2_Init(void)
 {
	RCC->AHB2ENR |=1;                    //Initialize clock for GPIOA
	RCC->APB1ENR1 |= 0x20000;            //Initialize clock for USART2
	
	GPIOA->AFR[0] |=0x7700;              //Enable alternate function for PA2 & PA3 USART2 RX & TX
	GPIOA->MODER  &=~0xF0;               //Reset PA2 & PA3
	GPIOA->MODER  |=0xA0;                //Setting PA2 & PA3 for AF
	
	USART2->BRR = 0x341;                 //Baud RATE 4800
	USART2->CR1 |= 0x000C;                //PIN 2 & 3 FOR RX & TX MODE
	USART2->CR1 |= 1;                    //Enable USART MODE

}

int USART2_write(int ch)
{
	while(!(USART2->ISR & 0x0080)){}     //CHECKING STATUS OF BUFFER
		USART2->TDR = (ch & 0xFF);         // ACCESSING FIRST EIGHT BIT OF TDR REGISTER
		return ch;
	}

	int USART2_read(void)
{
	while(!(USART2->ISR & 0x0020)){}     //WAIT FOR BUFFER
		return USART2->RDR;
	}

	struct __FILE{int handle;};
FILE __stdin ={0};
FILE __stdout ={1};
FILE __stderr ={2};

int fgetc(FILE *f)
{
	int c;
	c = USART2_read();
	if(c=='\r'){
		USART2_write(c);
		c='\n';
	}
		USART2_write(c);
		return c;
	}	

	
int fputc(int c, FILE *f)
{
	return USART2_write(c);
}
		