/**
 *  Control.c
 *
 *  Created on: Aug 31, 2015
 *      Author: sle
 */

#include "Control.h"
#include ".\StepperMotor\StepperMotor.h"
#include ".\BasalDose\BasalDose.h"
#include ".\BolusDose\BolusDose.h"

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
  Control_LEDInitiate();
	StepperMotor_Initiate(); // Initialize the stepper motor
	BasalDose_DoseTimingInitiate(); // Set up Timer0
	BasalDose_DoseAmountInitiate(); // Set up Timer1
	BolusDose_DoseInitiate(); // Set up external interrupt

	while(1);
}

void Control_LEDInitiate(void)
{
  // Initialize the pins P1.28 to P1.31
  // The pins are used for debugging
  LPC_GPIO1->FIODIR |= (0xF0000000);
  LPC_GPIO1->FIOPIN &=~(0xF0000000);
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
