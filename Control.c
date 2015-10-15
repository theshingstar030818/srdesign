/*
 * Control.c
 *
 *  Created on: Aug 31, 2015
 *      Author: sle
 */

#include "lpc17xx.h"                 // Device header
#include <stdbool.h>
#include "StepperMotor.h"

uint32_t currentPos;
uint32_t globalPos;

bool isSyringeEmpty(void);


uint32_t i = 0;
uint32_t max_time = 1500000;

int main()
{
	SystemInit();
	StepperMotor_Initiate();
	StepperMotor_StepForward();

	return 0;
}

bool isSyringeEmpty()
{
	if(globalPos >= 20)
		return true;
	else
		return false;
}

