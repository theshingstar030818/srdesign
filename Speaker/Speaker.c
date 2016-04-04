/**
 *  Speaker.c
 *
 *  Created on: Jan 12, 2016
 *      Author: sle
 */

#include ".\Speaker.h"

void Speaker_Initiate(void)
{
	// Initialize pin P0.26 to output
	LPC_GPIO0->FIODIR |= 1 << 26;

	LPC_TIM3->PR = 1 << 2;
	LPC_TIM3->MR0 = Hz_500;
	LPC_TIM3->MCR |= 3 << 0;

	NVIC_EnableIRQ(TIMER3_IRQn);
}

void Speaker_SetFrequency(FREQ frequency)
{
	LPC_TIM3->MR0 = frequency;
}

void Speaker_Play(void)
{
	LPC_TIM3->TCR |= 1 << 0;
}

void Speaker_Stop(void)
{
	LPC_TIM3->TCR &=~(1 << 0);
	LPC_TIM3->TCR |= 1 << 1;
	LPC_TIM3->TCR &=~(1 << 1);
	LPC_TIM3->IR |= 1 << 1;
}

void TIMER3_IRQHandler(void)
{
	LPC_TIM3->IR |= 1 << 0;
	if((LPC_GPIO0->FIOPIN & 0x04000000) == 0x04000000)
		LPC_GPIO0->FIOCLR |= 1 << 26;
	else
		LPC_GPIO0->FIOSET |= 1 << 26;
}

