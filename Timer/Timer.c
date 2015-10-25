/*
 * Timer.c
 *
 *  Created on: Oct 25, 2015
 *      Author: sle
 */

#include "BasalDose.h"

//Timer0 IRQ Handler
void TIMER0_IRQHandler(void)
{
	if((LPC_TIM0->IR & 0x01) == 0x01) // if MR0 interrupt
	{
		BasalDose_DoseEnable(); //Call to enable Timer1
	}
}

//Timer1 IRQ Handler
void TIMER1_IRQHandler(void)
{
	if((LPC_TIM1->IR & 0x01) == 0x01) // if MRO interrupt
	{
		BasalDose_DoseInject(); //Call for the stepper motor to rotate
	}
}
