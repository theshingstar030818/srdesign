/**
 *  StepperMotor.c
 *
 *  Created on: Sep 8, 2015
 *      Author: sle
 */

#include "..\Control.h"
#include "StepperMotor.h"
#include "..\BasalDose\BasalDose.h"

extern status Control_GlobalStatus;
extern state Control_GlobalState;

uint32_t StepperMotor_CurrentPosition;
uint32_t StepperMotor_GlobalPosition;
uint32_t StepperMotor_RemainingDosage;

uint32_t StepperMotor_CurrentBasalDose;
uint32_t StepperMotor_CurrentBolusDose;

void StepperMotor_Initiate(void)
{
	// Initialilze P0.0, P0.1, P0.2, P0.3 to output
	LPC_GPIO0->FIODIR |= (0x0000000F);
	LPC_GPIO0->FIOPIN &= ~(0x0000000F);

	// Initialize globals
	StepperMotor_CurrentPosition = 0;
	StepperMotor_GlobalPosition = 0;
	StepperMotor_CurrentBasalDose = 0;
	StepperMotor_CurrentBolusDose = 0;
	StepperMotor_RemainingDosage = 0;
}

void StepperMotor_StepForward(void)
{
	switch(StepperMotor_CurrentPosition)
	{
		case 0:
			LPC_GPIO0->FIOPIN = (0x00000003);
			StepperMotor_CurrentPosition++;
			break;
		case 1:
			LPC_GPIO0->FIOPIN = (0x00000002);
			StepperMotor_CurrentPosition++;
			break;
		case 2:
			LPC_GPIO0->FIOPIN = (0x00000006);
			StepperMotor_CurrentPosition++;
			break;
		case 3:
			LPC_GPIO0->FIOPIN = (0x00000004);
			StepperMotor_CurrentPosition++;
			break;
		case 4:
			LPC_GPIO0->FIOPIN = (0x0000000C);
			StepperMotor_CurrentPosition++;
			break;
		case 5:
			LPC_GPIO0->FIOPIN = (0x00000008);
			StepperMotor_CurrentPosition++;
			break;
		case 6:
			LPC_GPIO0->FIOPIN = (0x00000009);
			StepperMotor_CurrentPosition++;
			break;
		case 7:
			LPC_GPIO0->FIOPIN = (0x00000001);
			StepperMotor_CurrentPosition = 0;
			break;
	}
	StepperMotor_GlobalPosition++;
	
	if (StepperMotor_GlobalPosition == SYRINGE_LENGTH)
	{
		StepperMotor_CurrentBasalDose = 0;
		StepperMotor_CurrentBolusDose = 0;
		Control_GlobalStatus = Wait;
		Control_GlobalState = Empty;
	}
	
	// Check to see if Basal or Bolus has completed.
	if((StepperMotor_CurrentBasalDose  >= BASAL_STEPS) || (StepperMotor_CurrentBolusDose >= BOLUS_STEPS))
	{
		StepperMotor_CurrentBasalDose = 0;
		StepperMotor_CurrentBolusDose = 0;
		Control_GlobalStatus = None;
		Control_GlobalState = Undefined;
	}
}

void StepperMotor_StepBackward(void)
{
	switch(StepperMotor_CurrentPosition)
	{
		case 0:
			LPC_GPIO0->FIOPIN = (0x00000009);
			StepperMotor_CurrentPosition = 7;
			break;
		case 1:
			LPC_GPIO0->FIOPIN = (0x00000001);
			StepperMotor_CurrentPosition--;
			break;
		case 2:
			LPC_GPIO0->FIOPIN = (0x00000003);
			StepperMotor_CurrentPosition--;
			break;
		case 3:
			LPC_GPIO0->FIOPIN = (0x00000002);
			StepperMotor_CurrentPosition--;
			break;
		case 4:
			LPC_GPIO0->FIOPIN = (0x00000006);
			StepperMotor_CurrentPosition--;
			break;
		case 5:
			LPC_GPIO0->FIOPIN = (0x00000004);
			StepperMotor_CurrentPosition--;
			break;
		case 6:
			LPC_GPIO0->FIOPIN = (0x0000000C);
			StepperMotor_CurrentPosition--;
			break;
		case 7:
			LPC_GPIO0->FIOPIN = (0x00000008);
			StepperMotor_CurrentPosition--;
			break;
	}
	StepperMotor_GlobalPosition--;
	
	// Check to see if syringe is back to original spot
	if(StepperMotor_GlobalPosition <= 0)
	{
		Control_LEDClear();
		StepperMotor_GlobalPosition = 0;
		Control_GlobalStatus = Wait;
		Control_GlobalState = Full;
	}
}

void StepperMotor_SpinInitiate(void)
{
	LPC_TIM1->PR = 0x02; // Pre-scalar
	LPC_TIM1->MR0 = 1 << 20; // Match number
	LPC_TIM1->MCR |= 3 << 0; // Interrupt and reset timer on match (MCR = 011)
	NVIC_EnableIRQ(TIMER1_IRQn);
}

void StepperMotor_SpinEnable(void)
{
	BasalDose_TimingDisable(); // Disable and Reset Timer0
	LPC_TIM1->TCR |= 1 << 0; // Start counting (TCR = 01)
}

void StepperMotor_SpinDisable(void)
{
	LPC_TIM1->TCR &=~(1 << 0); // Stop Timer Counter (TCR = 00)
	LPC_TIM1->TCR |= 1 << 1; // Reset Timer Counter (TCR = 10)
	LPC_TIM1->TCR &=~(1 << 1); // Stop resetting Timer Counter (TCR = 00)
	LPC_TIM1->IR |= 1 << 1; // Reset Timer1 Interrupt
}

void TIMER1_IRQHandler(void)
{
	// Switch on status defined by Timer0 and EINT3 IRQs
	// case None defined within the StepperMotor_Step functions when adminstration is done
	switch(Control_GlobalStatus)
	{
		case Basal: 
			StepperMotor_CurrentBasalDose++; // Keep track of current dosing
			StepperMotor_StepForward();
			break;
		case Bolus:
			StepperMotor_CurrentBolusDose++; 
			StepperMotor_StepForward();
			break;
		case Backward:
			LPC_GPIO1->FIOSET |= 1 << 31; // Signal that Backward is being administered P1.31
			StepperMotor_StepBackward();
			break;
		case None:
			BasalDose_TimingEnable(); // Re-Enable Timer0
			Control_LEDClear(); // Clear out LEDs
			break;
		case Wait:
			BasalDose_TimingDisable();
			LPC_GPIO2->FIOSET |= 1 << 3; // Signal that syringe is replaced P2.3
			break;
	}
	LPC_TIM1->IR |= 1 << 0; // Clear out Timer1 registers
}
