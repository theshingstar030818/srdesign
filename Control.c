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

status Control_GlobalStatus;

int main(void)
{
	SystemInit();
	
	Control_GlobalStatus = None;
	
  Control_LEDInitiate();
	StepperMotor_Initiate();
	
	BasalDose_DoseTimingInitiate();
	BasalDose_DoseAmountInitiate();
	
	BolusDose_DoseInitiate();

	while(1);
}

void Control_LEDInitiate(void)
{
  LPC_GPIO1->FIODIR |= (0xF0000000);
  LPC_GPIO1->FIOPIN &=~(0xF0000000);
}
