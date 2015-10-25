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
