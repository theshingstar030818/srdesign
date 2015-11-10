/**
 *  Control.c
 *
 *  Created on: Aug 31, 2015
 *      Author: sle
 */

#include "lpc17xx.h"                 // Device header
#include "StepperMotor.h"
#include "BasalDose.h"
#include "BolusDose.h"

// Global variables declared in other files
extern uint32_t StepperMotor_GlobalPosition;
extern uint32_t BasalDose_DoseAmountCounter;
extern uint32_t BolusDose_DoseAmountCounter;

// Create bool
typedef enum {false, true} bool;

// Time between steps, now obsolete
#define MAX_TIME 75000

// Global variables
uint32_t i = 0;
uint32_t wait = MAX_TIME;
uint32_t Control_AmountPerDose;

// Control functions
bool Control_IsSyringeEmpty(void);
void Control_DosageAmount(uint32_t amount);

int main(void)
{
	SystemInit(); // Initialize the device
	
	StepperMotor_Initiate(); // Initialize the stepper motor
	BasalDose_DoseTimingInitiate(); // Initialize Timer0
	BasalDose_DoseAmountInitiate(); // Set up Timer1
	BolusDose_DoseInitiate(); //Initialize external interrupt

	while(1);
}

// Test if the syringe is empty
bool Control_IsSyringeEmpty(void)
{
	if(StepperMotor_GlobalPosition + 50 >= 20)
		return true;
	else
		return false;
}
// Function to assign the value of steps
void Control_DosageAmount(uint32_t amount)
{
	Control_AmountPerDose = amount;
}
