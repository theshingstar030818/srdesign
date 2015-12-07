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

// Set and enable Timer0 for the time in between Basal doses
void BasalDose_DoseTimingInitiate(void)
{
	LPC_TIM0->PR = 0x02; // Pre-scalar
	LPC_TIM0->MR0 = 1 << 27; // Match number
	LPC_TIM0->MCR |= 3 << 0; // Interrupt and reset timer on match (MCR = 011)
	NVIC_EnableIRQ(TIMER0_IRQn); // Enable Timer0, but don't start counting
}

void BasalDose_DoseTimingEnable(void)
{
	BasalDose_DoseDisable(); // Disable and Reset Timer1
	LPC_TIM0->TCR |= 1 << 0; // Start counting (TCR = 01)
}

void BasalDose_DoseTimingDisable(void)
{
	LPC_TIM0->TCR &=~(1 << 0); // Stop Timer Counter (TCR = 00)
	LPC_TIM0->TCR |= 1 << 1; // Reset Timer Counter (TCR = 10)
	LPC_TIM0->TCR &=~(1 << 1); // Stop resetting Timer Counter (TCR = 00)
	LPC_TIM0->IR |= 1 << 0; // Reset Timer0 Interrupt
}

void BasalDose_DoseInitiate(void)
{
	LPC_TIM1->PR = 0x02; // Pre-scalar
	LPC_TIM1->MR0 = 1 << 20; // Match number
	LPC_TIM1->MCR |= 3 << 0; // Interrupt and reset timer on match (MCR = 011)
	NVIC_EnableIRQ(TIMER1_IRQn);
}

void BasalDose_DoseEnable(void)
{
	BasalDose_DoseTimingDisable(); // Disable and Reset Timer0
	LPC_TIM1->TCR |= 1 << 0; // Start counting (TCR = 01)
}

void BasalDose_DoseDisable(void)
{
	LPC_TIM1->TCR &=~(1 << 0); // Stop Timer Counter (TCR = 00)
	LPC_TIM1->TCR |= 1 << 1; // Reset Timer Counter (TCR = 10)
	LPC_TIM1->TCR &=~(1 << 1); // Stop resetting Timer Counter (TCR = 00)
	LPC_TIM1->IR |= 1 << 1; // Reset Timer1 Interrupt
}

void TIMER0_IRQHandler(void)
{
	/* Check to see if there is enough to do a basal injection,
	 * if not enough retract the syringe
	 * TODO: Add additional state so that we inject until empty,
	 * then retract syringe.
	 */
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
	// Switch on status defined by Timer0 and EINT3 IRQs
	// case None defined within the StepperMotor_Step functions when adminstration is done
	switch(Control_GlobalStatus)
	{
		case Basal: 
			LPC_GPIO1->FIOSET |= 1 << 28; // Signal that Basal is being administered P1.28
			StepperMotor_CurrentBasalDose++; // Keep track of current dosing
			StepperMotor_StepForward();
			break;
		case Bolus:
			LPC_GPIO1->FIOSET |= 1 << 29; // Signal that Bolus is being administered P1.29
			StepperMotor_CurrentBolusDose++; 
			StepperMotor_StepForward();
			break;
		case Backward:
			LPC_GPIO1->FIOSET |= 1 << 31; // Signal that Backward/Retraction is occuring P1.31
			StepperMotor_StepBackward();
			break;
		case None:
			BasalDose_DoseTimingEnable(); // Re-Enable Timer0
			Control_LEDClear(); // Clear out LEDs
			break;
	}
	LPC_TIM1->IR |= 1 << 0; // Clear out Timer1 registers
}
