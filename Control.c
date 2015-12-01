/**
 *  Control.c
 *
 *  Created on: Aug 31, 2015
 *      Author: sle
 */

#include "Control.h"
#include ".\BasalDose\BasalDose.h"
#include ".\BolusDose\BolusDose.h"
#include ".\StepperMotor\StepperMotor.h"


status Control_GlobalStatus;

int main(void)
{
	SystemInit();
	
	// Set default status to None
	Control_GlobalStatus = None;
	
	// Initialize Clock for Timers
	Control_ClockInitiate();
	
	// Initialize LED and StepperMotor GPIO
	Control_LEDInitiate();
	StepperMotor_Initiate();
	
	// Initialize Timers 0, 1
	BasalDose_DoseTimingInitiate();
	BasalDose_DoseInitiate();
	
	// Initialize External Interrupt 3
	BolusDose_DoseInitiate();
	
	LPC_TIM0->TCR |= 1 << 0; // Start Counting Timer0
	
	while(1); // Endless loop, could be used for better things. (Output information to LCD)
}

void Control_LEDInitiate(void)
{
	// Set pins P1.28, P1.29, P1.30, P1.31 as output
	LPC_GPIO1->FIODIR |= (0xF0000000);
	LPC_GPIO1->FIOPIN &=~(0xF0000000);
	
	// Set pins P2.2, P2.3 as output
	LPC_GPIO2->FIODIR |= (0x00000006);
	LPC_GPIO2->FIOPIN &=~(0x00000006);
}

void Control_ClockInitiate(void)
{
	// Power up Timer0 and Timer1
	LPC_SC->PCONP |= 1 << 1; 
	LPC_SC->PCONP |= 1 << 2;
	
	// Clock select Timer0 and Timer1 (PCLK = CCLK)
	LPC_SC->PCLKSEL0 |= 1 << 2;
	LPC_SC->PCLKSEL0 |= 1 << 4;
}
