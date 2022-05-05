#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO


GPIO_InitTypeDef GPIO_InitObject;

int receiver;

void GPIO_Config(){

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);  // Clock enable for B ports
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);	// Clock enable for C ports
	
	GPIO_InitObject.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitObject.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_5;		// PB2: Buzzer + LED, PB5: Laser sensor 
	GPIO_InitObject.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOB,&GPIO_InitObject);
	
	GPIO_InitObject.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitObject.GPIO_Pin = GPIO_Pin_2;		// PC2: Receiver 
	GPIO_InitObject.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOC,&GPIO_InitObject);
	
}


int main()
{

	GPIO_Config();
	
	while(1)
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_5);  // Laser on
	
		// Receiver value becomes 0 when it detects light (default: 1) 
		receiver = GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2);
		
		if(receiver)
			GPIO_SetBits(GPIOB,GPIO_Pin_2);  // Buzzer & LED on
		else
		  GPIO_ResetBits(GPIOB,GPIO_Pin_2);  // Buzzer & LED off

	
	}

}
