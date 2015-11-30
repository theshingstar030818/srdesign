/**
 *  StepperMotor.c
 *
 *  Created on: Sep 8, 2015
 *      Author: sle
 */

#include "StepperMotor.h"
#include "..\Control.h"
#include "..\BasalDose\BasalDose.h"

extern status Control_GlobalStatus;
extern bool BolusDose_FirstIRQHandle;

uint32_t StepperMotor_CurrentPosition;
uint32_t StepperMotor_GlobalPosition;

uint32_t StepperMotor_CurrentBasalDose;
uint32_t StepperMotor_CurrentBolusDose;

void StepperMotor_Initiate(void)
{
	LPC_GPIO0->FIODIR |= (0x0000000F);
	LPC_GPIO0->FIOPIN &= ~(0x0000000F);

	StepperMotor_CurrentPosition = 0;
	StepperMotor_GlobalPosition = 0;
	
	StepperMotor_CurrentBasalDose = 0;
	StepperMotor_CurrentBolusDose = 0;
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
	
	if((StepperMotor_CurrentBasalDose >= BASAL_STEPS) || (StepperMotor_CurrentBolusDose >= BOLUS_STEPS))
	{
		StepperMotor_CurrentBasalDose = 0;
		StepperMotor_CurrentBolusDose = 0;
		Control_GlobalStatus = None;
		BolusDose_FirstIRQHandle = true;
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
	
	if(StepperMotor_GlobalPosition <= 0)
	{
		StepperMotor_GlobalPosition = 0;
		Control_GlobalStatus = None;
	}
}
