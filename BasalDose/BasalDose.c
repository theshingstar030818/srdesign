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
	LPC_TIM0->MCR |= 1 << 0; // Interrupt timer on match (MCR = 01)
	LPC_TIM0->MCR |= 1 << 1; // Reset timer on match (MCR = 11)
	LPC_TIM0->TCR |= 1 << 1; // Manually reset Timer0 (TCR = 10)
	LPC_TIM0->TCR &=~(1 << 1); // Stop resetting the Timer0 (TCR = 00)

	NVIC_EnableIRQ(TIMER0_IRQn); // Enable Timer0, but don't start counting
}

void BasalDose_DoseTimingEnable(void)
{
	NVIC_EnableIRQ(TIMER0_IRQn); // Enable Timer0
	BasalDose_DoseDisable(); // Disable and Reset Timer1
	LPC_TIM0->TCR |= 1 << 0; // Start counting (TCR = 01)
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
	LPC_TIM0->IR |= 1 << 0; // Resets all pending Timer0 interrupts and clears out registers
							// I only think we need this line here, but needs to be tested
}

void BasalDose_DoseInitiate(void)
{
	LPC_TIM1->PR = 0x02; // Pre-scalar
	LPC_TIM1->MR0 = 1 << 17; // Match number
	LPC_TIM1->MCR |= 1 << 0; // Interrupt timer on match (MCR = 01)
	LPC_TIM1->MCR |= 1 << 1; // Reset timer on match (MCR = 11)
	LPC_TIM1->TCR |= 1 << 1; // Manually reset Timer1 (TCR = 10)
	LPC_TIM1->TCR &=~(1 << 1); // Stop resetting the Timer0 (TCR = 00)
}

void BasalDose_DoseEnable(void)
{
	NVIC_EnableIRQ(TIMER1_IRQn); // Enable Timer1 IRQ
	BasalDose_DoseTimingDisable(); // Disable and Reset Timer0
	LPC_TIM1->TCR |= 1 << 0; // Start counting (TCR = 01)
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
	LPC_TIM1->IR |= 1 << 1; // Resets all pending Timer1 interrupts and clears out registers
							// I only think we need this line here, but needs to be tested
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
			// Clear out LEDs because nothing is being administered
			LPC_GPIO1->FIOCLR |= 1 << 28; 
			LPC_GPIO1->FIOCLR |= 1 << 29;
			LPC_GPIO1->FIOCLR |= 1 << 31;
			break;
	}
	LPC_TIM1->IR |= 1 << 0; // Clear out Timer1 registers
}
