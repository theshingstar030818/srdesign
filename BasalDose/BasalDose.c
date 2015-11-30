/**
 *  BasalDose.c
 *
 *  Created on: Aug 31, 2015
 *      Author: sle
 */

#include "BasalDose.h"
#include "..\StepperMotor\StepperMotor.h"
#include "..\Control.h"

extern uint32_t StepperMotor_GlobalPosition;
extern uint32_t StepperMotor_CurrentBasalDose;
extern uint32_t StepperMotor_CurrentBolusDose;

extern status Control_GlobalStatus;

void BasalDose_DoseTimingInitiate(void)
{
	LPC_TIM0->PR = 0x02; // Pre-scalar
	LPC_TIM0->MR0 = 1 << 27; // Match number
	LPC_TIM0->MCR |= 1 << 0; // Interrupt and reset
	LPC_TIM0->MCR |= 1 << 1; // Reset timer on Match 0.
	LPC_TIM0->TCR |= 1 << 1; // Manually Reset Timer0 (forced)
	LPC_TIM0->TCR &=~(1 << 1); // Stop resetting the timer.

	NVIC_EnableIRQ(TIMER0_IRQn);
}

void BasalDose_DoseTimingEnable(void)
{
	NVIC_EnableIRQ(TIMER0_IRQn); // Enable Timer0 IRQ
	BasalDose_DoseDisable();
	LPC_TIM0->TCR |= 1 << 0;
}

void BasalDose_DoseTimingDisable(void)
{
	NVIC_DisableIRQ(TIMER0_IRQn); // Disable Timer0 IRQ
	BasalDose_DoseTimingReset();
}

void BasalDose_DoseTimingReset(void)
{
	LPC_TIM0->TCR &=~(1 << 0);
	LPC_TIM0->TCR |= 1 << 1;
	LPC_TIM0->TCR &=~(1 << 1);
	LPC_TIM0->IR |= 1 << 0;
}

void BasalDose_DoseInitiate(void)
{
	LPC_TIM1->PR = 0x02; // Pre-scalar
	LPC_TIM1->MR0 = 1 << 17; // Match number
	LPC_TIM1->MCR |= 1 << 0; // Interrupt and reset
	LPC_TIM1->MCR |= 1 << 1; // Reset timer on Match 0.
	LPC_TIM1->TCR |= 1 << 1; // Manually Reset Timer1 (forced)
	LPC_TIM1->TCR &=~(1 << 1); // Stop resetting the timer.s
}

void BasalDose_DoseEnable(void)
{
	NVIC_EnableIRQ(TIMER1_IRQn); // Enable Timer1 IRQ
	BasalDose_DoseTimingDisable();
	LPC_TIM1->TCR |= 1 << 0;
}

void BasalDose_DoseDisable(void)
{
	NVIC_DisableIRQ(TIMER1_IRQn); // Disable Timer1 IRQ
	BasalDose_DoseReset();
}

void BasalDose_DoseReset(void)
{
	LPC_TIM1->TCR &=~(1 << 0);
	LPC_TIM1->TCR |= 1 << 1;
	LPC_TIM1->TCR &=~(1 << 1);
	LPC_TIM1->IR |= 1 << 1;
}

void TIMER0_IRQHandler(void)
{
	if(StepperMotor_GlobalPosition + BASAL_STEPS <= SYRINGE_LENGTH)
	{
		Control_GlobalStatus = Basal;
	}
	else
	{
		Control_GlobalStatus = Backward;
	}
	BasalDose_DoseEnable();	
}

void TIMER1_IRQHandler(void)
{
	switch(Control_GlobalStatus)
	{
		case Basal:
			LPC_GPIO1->FIOSET |= 1 << 28;
			StepperMotor_CurrentBasalDose++;
			StepperMotor_StepForward();
			break;
		case Bolus:
			LPC_GPIO1->FIOSET |= 1 << 29;
			StepperMotor_CurrentBolusDose++;
			StepperMotor_StepForward();
			break;
		case Backward:
			LPC_GPIO1->FIOSET |= 1 << 31;
			StepperMotor_StepBackward();
			break;
		case None:
			BasalDose_DoseTimingEnable();
			LPC_GPIO1->FIOCLR |= 1 << 28;
			LPC_GPIO1->FIOCLR |= 1 << 29;
			LPC_GPIO1->FIOCLR |= 1 << 31;
			NVIC_EnableIRQ(EINT3_IRQn);
			break;
	}
	LPC_TIM1->IR |= 1 << 0;
}
