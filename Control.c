/*
 * Control.c
 *
 *  Created on: Aug 31, 2015
 *      Author: sle
 */

#include "lpc17xx.h"                 // Device header
#include "StepperMotor.h"

typedef enum {false, true} bool;

uint32_t currentPos;
uint32_t globalPos;
uint32_t i = 0;
uint32_t max_time = 1500000;

bool Control_IsSyringeEmpty(void);
void BasalDose_DoseTimingInitiate();
void BasalDose_DoseAmountInitiate();

int main()
{
	SystemInit();
	StepperMotor_Initiate();
	StepperMotor_StepForward();

	return 0;
}

bool Control_IsSyringeEmpty()
{
	if(globalPos >= 20)
		return true;
	else
		return false;
}

void BasalDose_DoseTimingInitiate()
{
	LPC_SC->PCONP    |= 1 << 1; // Set to initialize timer0
	LPC_SC->PCLKSEL0 |= 1 << 2; // Set for divisor of clk to be 2

	LPC_TIM0->TCM = 0x02; 		// Set to resets timer0
	LPC_TIM0->PR  = 0x00; 		// Set so that there is no pre-scaler (pre-scaler = 0)
	LPC_TIM0->MR0 = ; 			// TODO: Insert "match" number here;
	LPC_TIM0->MCR = 3; 			// Set so when there is a match, interrupt is triggered and
								// timer is reset

	BasalDose_DoseAmountInitiate();
	return;

}

void BasalDose_DoseAmountInitate()
{
	LPC_SC->PCONP 	 |= 1 << 2; // This would be the setup to initialize timer1
	LPC_SC->PCLKSEL1 |= 1 << 2; // Same thing, but for divisor

	LPC_TIM1->TCM = 0x02;
	LPC_TIM1->PR  = 0x00;
	LPC_TIM1->MR0 = ;
	LPC_TIM1->MCR = 3;

	return;

}



