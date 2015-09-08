/*
 * Control.c
 *
 *  Created on: Aug 31, 2015
 *      Author: sle
 */

#include <stdio.h>


#include "../LPC17xx.h"
#include "./BasalDose/BasalDose.h"
#include "./BosalDose/BosalDose.h"
#include "./StepperMotor/StepperMotor.h"

int main()
{
	while(1)
	{
		StepperMotor_StepFoward();
	}
}
