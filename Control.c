/**
 *  Control.c
 *
 *  Created on: Aug 31, 2015
 *      Author: sle
 */

#include "Control.h"
#include "StepperMotor.h"
#include "BasalDose.h"
#include "BolusDose.h"

// Global variables declared in other files
extern uint32_t StepperMotor_GlobalPosition;
extern uint32_t BasalDose_DoseAmountCounter;
extern uint32_t BolusDose_DoseAmountCounter;

// Global variables
uint32_t i = 0;
uint32_t Control_AmountPerDose;

int main(void)
{
	SystemInit(); // Initialize the device
	
	StepperMotor_Initiate(); // Initialize the stepper motor
	BasalDose_DoseTimingInitiate(); // Set up Timer0
	BasalDose_DoseAmountInitiate(); // Set up Timer1
	BolusDose_DoseInitiate(); // Set up external interrupt

	while(1);
}

// Test if the syringe is empty
bool Control_IsSyringeEmpty(void)
{
	if(StepperMotor_GlobalPosition >= SYRINGE_LENGTH)
		return true;
	else
		return false;
}

// Assign Amount of steps
void Control_DosageAmount(uint32_t amount)
{
	Control_AmountPerDose = amount;
}
