/*
 * Timer.c
 *
 *  Created on: Oct 25, 2015
 *      Author: sle
 */

#include "BasalDose.h"

void TIMER0_IRQHandler(void)
{
	if((LPC_TIM0->IR & 0x01) == 0x01) // if MR0 interrupt
	{
		BasalDose_DoseEnable();
	}
}

void TIMER1_IRQHandler(void)
{
	if((LPC_TIM1->IR & 0x01) == 0x01) // if MR0 interrupt
	{
		BasalDose_DoseInject();
	}
}

void EINT3_IRQHandler(void)
{
	LPC_GPIOINT->IO2IntClr |= (1<<10); // Clear the status
	LPC_GPIO1->FIOPIN ^= 1 << 31; // Toggle the LED

	NVIC_EnableIRQ(TIMER1_IRQn);
}
