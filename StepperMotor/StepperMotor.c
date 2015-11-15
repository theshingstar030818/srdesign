/**
 *  StepperMotor.c
 *
 *  Created on: Sep 8, 2015
 *      Author: sle
 */

#include "StepperMotor.h"
#include "Control.h"

extern uint32_t Control_AmountPerDose;
extern uint32_t BasalDose_DoseAmountCounter;

// Global variables
uint32_t StepperMotor_CurrentPosition;
uint32_t StepperMotor_GlobalPosition;

// Initializes the stepper motor
void StepperMotor_Initiate(void)
{
	// Initialize the pins P0.0 to P0.3
	// These are the leads for the stepper motor
	LPC_GPIO0->FIODIR |= (0x0000000F);
	LPC_GPIO0->FIOPIN &= ~(0x0000000F);
	
	// Declaring the global variables
	StepperMotor_CurrentPosition = 0;
	StepperMotor_GlobalPosition = 0;
	BasalDose_DoseAmountCounter = 0;
}

// Function that will drive the stepper motor forward
void StepperMotor_StepForward(void)
{
	BasalDose_DoseAmountCounter++; // Increase Basal counter
	
	// Compare and keep track of the current position of the stepper motor
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
	
	StepperMotor_GlobalPosition++; // Increment stepper motors global variable
	
	// Compare if the amount injecfted is more than amount that is able to be recieved
	if(BasalDose_DoseAmountCounter >= Control_AmountPerDose)
	{
		LPC_GPIO1->FIOCLR |= 1 << 28;
		LPC_GPIO1->FIOCLR |= 1 << 29;
		LPC_GPIO1->FIOCLR |= 1 << 31;
		BasalDose_DoseDisable(); // Disable Timer1 IRQ
		BasalDose_DoseTimingEnable(); // Enable Timer0
		BasalDose_DoseAmountCounter = 0; // Set to 0
	}
}

// Function that will drive the stepper motor backward
void StepperMotor_StepBackward(void)
{
	// Compare and keep track of the current position of the stepper motor
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
	
	StepperMotor_GlobalPosition--; // Decrement stepper motors global variable
	
	if(StepperMotor_GlobalPosition <= SYRINGE_LENGTH)
	{
		StepperMotor_GlobalPosition = 0;
		BasalDose_DoseDisable(); // Disable Timer1 IRQ
		BasalDose_DoseTimingEnable(); // Enable Timer0 IRQ
	}
}
