/**
 *  BolusDose.c
 *
 *  Created on: Aug 31, 2015
 *      Author: sle
 */

#include "BolusDose.h"
#include "..\Control.h"
#include "..\BasalDose\BasalDose.h"

extern uint32_t StepperMotor_GlobalPosition;

extern status Control_GlobalStatus;

void BolusDose_DoseInitiate(void)
{
	LPC_PINCON->PINSEL4 &=~ (3<<20); // P2.10 is GPIO
	LPC_GPIO2->FIODIR &=~ (1<<10); // P2.10 in input

	LPC_GPIOINT->IO2IntEnF |= (1 << 10); // Enabling falling edge to P2.10

	NVIC_EnableIRQ(EINT3_IRQn); // Enable External Interrupt 3
}

void EINT3_IRQHandler(void)
{
	LPC_GPIOINT->IO2IntClr |= (1<<10); // Clear the status
	
	/* Check to see if there is enough to do a bolus injection,
	 * if not enough retract the syringe
	 * TODO: Add additional state so that we inject until empty,
	 * then retract syringe.
	 */
	if(StepperMotor_GlobalPosition + BOLUS_STEPS <= SYRINGE_LENGTH)
	{
		Control_GlobalStatus = Bolus;
		LPC_GPIO1->FIOSET |= 1 << 29; // Signal that Bolus is being administered P1.29
	}
	else
	{
		Control_GlobalStatus = Backward;
		LPC_GPIO1->FIOSET |= 1 << 31; // Signal that Backward/Retraction is occuring P1.31
	}
	BasalDose_DoseEnable();	
}
