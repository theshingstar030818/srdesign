/*
 * Control.c
 *
 *  Created on: Aug 31, 2015
 *      Author: sle
 */

#include "lpc17xx.h"                 // Device header
#include "StepperMotor.h"

extern StepperMotor_GlobalPosition;

//Create bool
typedef enum {false, true} bool;

#define MAX_TIME 75000
#define STEPS_PER_DOSE 50

//Global variables
uint32_t i = 0;
uint32_t wait = MAX_TIME;

bool Control_IsSyringeEmpty(void);

int main(void)
{
	SystemInit(); //Initialize the device
	
	StepperMotor_Initiate(); //Initialize the stepper motor
	BasalDose_DoseTimingInitiate(); //Initialize Timer0

	while(1);
}

//Test if the syringe is empty
bool Control_IsSyringeEmpty()
{
	if(StepperMotor_GlobalPosition >= 20)
		return true;
	else
		return false;
}



