/**
 *  BasalDose.c
 *
 *  Created on: Aug 31, 2015
 *      Author: sle
 */

#include "BasalDose.h"
#include "..\Control.h"
#include "..\StepperMotor\StepperMotor.h"

extern uint32_t StepperMotor_GlobalPosition;
extern uint32_t StepperMotor_CurrentBasalDose;
extern uint32_t StepperMotor_CurrentBolusDose;

extern status Control_GlobalStatus;
extern state Control_GlobalState;

// Set and enable Timer0 for the time in between Basal doses
void BasalDose_TimingInitiate(void)
{
	LPC_TIM0->PR = 0x02; // Pre-scalar
	LPC_TIM0->MR0 = 1 << 27; // Match number
	LPC_TIM0->MCR |= 3 << 0; // Interrupt and reset timer on match (MCR = 011)
	NVIC_EnableIRQ(TIMER0_IRQn); // Enable Timer0, but don't start counting
}

void BasalDose_TimingEnable(void)
{
	StepperMotor_SpinDisable(); // Disable and Reset Timer1
	LPC_TIM0->TCR |= 1 << 0; // Start counting (TCR = 01)
}

void BasalDose_TimingDisable(void)
{
	LPC_TIM0->TCR &=~(1 << 0); // Stop Timer Counter (TCR = 00)
	LPC_TIM0->TCR |= 1 << 1; // Reset Timer Counter (TCR = 10)
	LPC_TIM0->TCR &=~(1 << 1); // Stop resetting Timer Counter (TCR = 00)
	LPC_TIM0->IR |= 1 << 0; // Reset Timer0 Interrupt
}

void TIMER0_IRQHandler(void)
{
	/* Check to see if there is enough to do a basal injection,
	 * if not enough retract the syringe
	 * TODO: Add additional state so that we inject until empty,
	 * then retract syringe.
	 */
	LPC_GPIO1->FIOSET |= 1 << 28; // Signal that Basal is being administered P1.28
	if(StepperMotor_GlobalPosition  + BASAL_STEPS < SYRINGE_LENGTH)
	{
		Control_GlobalStatus = BasalComplete;
	}
	else if(StepperMotor_GlobalPosition < SYRINGE_LENGTH)
	{
		Control_GlobalStatus = BasalEmptyDuring;
	}
	else
	{
		Control_GlobalStatus = BasalEmptyAfter;
	}
	StepperMotor_SpinEnable();	
}


