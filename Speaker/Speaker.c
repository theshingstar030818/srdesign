/**
 *  Speaker.c
 *
 *  Created on: Jan 12, 2016
 *      Author: sle
 */

#include ".\Speaker.h"
#include "..\Control.h"

void Speaker_Initiate(void)
{
	// Initialize pin P0.26 to output
	LPC_GPIO0->FIODIR |= 1 << 26;
	
	// Timer3 initialization
	LPC_TIM3->PR = 0x02; // Pre-scalar
	LPC_TIM3->MR0 = 1 << 27; // Match number
	LPC_TIM3->MCR |= 3 << 0; // Interrupt and reset timer on match (MCR = 011)
	NVIC_EnableIRQ(TIMER3_IRQn);
}

void Speaker_Play(int loops, int frequency)
{
	Speaker_Enable();
	// Turn the speaker on and off no. of times specified
	while(loops >= 0)
	{
		LPC_GPIO0->FIOSET |= 1 << 26; // Set P0.26
		Speaker_Wait(frequency);
		LPC_GPIO0->FIOCLR |= 1 << 26; // Clear P0.26
		Speaker_Wait(frequency);
		loops--; // Decrement
	}
	Speaker_Disable();
}

void Speaker_Wait(int frequency) // This could possibly be moved straight into control and used as a universal wait
{												// instead of a class specific wait loop, with parameters that define the number of loops
	int i;
	for(i = 0; i < frequency; i++);
}

void Speaker_Enable(void)
{
	LPC_TIM3->TCR |= 1 << 0; // Start counting (TCR = 01)
}

void Speaker_Disable(void)
{
	LPC_TIM3->TCR &=~(1 << 0); // Stop Timer Counter (TCR = 00)
	LPC_TIM3->TCR |= 1 << 1; // Reset Timer Counter (TCR = 10)
	LPC_TIM3->TCR &=~(1 << 1); // Stop resetting Timer Counter (TCR = 00)
	LPC_TIM3->IR |= 1 << 0; // Reset Timer0 Interrupt
}

void TIMER3_IRQHandler(void)
{
	LPC_TIM3->IR |= 1 << 0; // Clear out Timer3 registers
}
