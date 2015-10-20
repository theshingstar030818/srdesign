/*
 * TimerTest.c
 *
 *  Created on: Oct 19, 2015
 *      Author: sle
 */

#include "lpc17xx.h"

uint32_t i = 0;

int main(void)
{
	SystemInit();
	LPC_GPIO1->FIODIR |= (0xF0000000); // Set pins for output
	LPC_GPIO1->FIOPIN &=~(0xF0000000); // Set pins to 0
	LPC_SC->PCONP |= 1 << 1; //Power up Timer0
	LPC_SC->PCLKSEL0 |= 1 << 2; // Clock select
	LPC_TIM0->TCR = 0x02;
	LPC_TIM0->PR = 0x00; // Pre-scalar
	LPC_TIM0->MR0 = 40000000; // Match number
	LPC_TIM0->MCR = 3; // Interrupt and reset

	while(1)
	{
		NVIC_EnableIRQ(TIMER0_IRQn); // Enable Timer0 IRQ
		LPC_TIM0->TCR = 1; // Reset Timer0
		for(i = 0; i < 1000000; i++);
	}

	return 0;
}

void TIMER0_IRQHandler(void)
{
	// Flip a bit on the board when interrupt triggered
	if((LPC_GPIO1->FIOPIN & 0xF0000000) == 0)
	{
		LPC_GPIO1->FIOPIN = 0xF0000000;
	}
	else
	{
		LPC_GPIO1->FIOPIN = 0x00000000;
	}
}

/*
 * Control.c
 *
 *  Created on: Aug 31, 2015
 *      Author: sle


#include "lpc17xx.h"                 // Device header

uint32_t currentPos;
uint32_t globalPos;

void stepForward(void);
void stepBackward(void);
void stepInitiate(void);
bool isSyringeEmpty(void);


unsigned int i = 0;
unsigned int max_time = 150000;

int main()
{
	SystemInit();
	stepInitiate();
	stepForward();

	return 0;
}

void stepInitiate()
{
	LPC_GPIO0->FIODIR |= (0x0000000F);
	LPC_GPIO0->FIOPIN &= ~(0x0000000F);

	currentPos = 0;
	globalPos = 0;
}

void stepForward()
{
while(1)
{
	if(isSyringeEmpty())
		break;
	globalPos += 1;
	switch(currentPos)
	{
		case 0:
			LPC_GPIO0->FIOPIN = (0x00000003);
			currentPos += 1;
			break;
		case 1:
			LPC_GPIO0->FIOPIN = (0x00000002);
			currentPos += 1;
			break;
		case 2:
			LPC_GPIO0->FIOPIN = (0x00000006);
			currentPos += 1;
			break;
		case 3:
			LPC_GPIO0->FIOPIN = (0x00000004);
			currentPos += 1;
			break;
		case 4:
			LPC_GPIO0->FIOPIN = (0x0000000C);
			currentPos += 1;
			break;
		case 5:
			LPC_GPIO0->FIOPIN = (0x00000008);
			currentPos += 1;
			break;
		case 6:
			LPC_GPIO0->FIOPIN = (0x00000009);
			currentPos += 1;
			break;
		case 7:
			LPC_GPIO0->FIOPIN = (0x00000001);
			currentPos = 0;
			break;
	}
	for(i=0; i<max_time; i++);
	}
	stepBackward();
}

bool isSyringeEmpty()
{
	if(globalPos >= 395)
		return true;
	else
		return false;
}

void stepBackward()
{
	for(; globalPos > 0; globalPos--)
	{
		switch(currentPos)
		{
			case 0:
				LPC_GPIO0->FIOPIN = (0x00000009);
				currentPos = 7;
				break;
			case 1:
				LPC_GPIO0->FIOPIN = (0x00000001);
				currentPos--;
				break;
			case 2:
				LPC_GPIO0->FIOPIN = (0x00000003);
				currentPos--;
				break;
			case 3:
				LPC_GPIO0->FIOPIN = (0x00000002);
				currentPos--;
				break;
			case 4:
				LPC_GPIO0->FIOPIN = (0x00000006);
				currentPos--;
				break;
			case 5:
				LPC_GPIO0->FIOPIN = (0x00000004);
				currentPos--;
				break;
			case 6:
				LPC_GPIO0->FIOPIN = (0x0000000C);
				currentPos--;
				break;
			case 7:
				LPC_GPIO0->FIOPIN = (0x00000008);
				currentPos--;
				break;
		}
		for(i=0; i<max_time; i++);
	}
	globalPos = 0;
	stepForward();
}*/
