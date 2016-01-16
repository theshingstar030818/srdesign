/**
 *  Control.c
 *
 *  Created on: Aug 31, 2015
 *      Author: sle
 */

#include "Control.h"
#include ".\LCD\LCD.h"
#include ".\BasalDose\BasalDose.h"
#include ".\BolusDose\BolusDose.h"
#include ".\InsulinQueue\InsulinQueue.h"
#include ".\StepperMotor\StepperMotor.h"

extern InsulinQueue *globalIQ;

status Control_GlobalStatus;

uint32_t i, j; // Used for wait loop in main

int main(void)
{
	SystemInit();
	
	// Set default status to None
	Control_GlobalStatus = None;
	
	// Initialize Clock for Timers
	Control_ClockInitiate();
	
	// Initialize LCD and StepperMotor GPIO
	LCD_Initiate();
	StepperMotor_Initiate();
	
	// Built in LED function replaces what we were using before
	LED_Initialize();
	
	// Initialize Timers 0, 1
	BasalDose_DoseTimingInitiate();
	BasalDose_DoseInitiate();
	
	// Initialize Timer2 and Insulin Queue
	globalIQ = InsulinQueue_Create(5);
	InsulinQueue_Initiate();

	// Initialize External Interrupt 3
	BolusDose_DoseInitiate();
	
	LPC_TIM0->TCR |= 1 << 0; // Start Counting Timer0
	
	while(1)
	{
		// Clear out the screen, and update
		GLCD_ClearScreen();
		LCD_UpdateScreenStatus();
		LCD_UpdateScreenInsulin();
		
		// Wait for a short period of time before updating
		for(i = 0; i < 150000; i++)
		{
			for(j = 0; j < 30; j++);
		}
	}
}

void Control_LEDClear(void)
{
	// Clear out LEDs used for Basal, Bolus, and Backward
	LED_Off(0);
	LED_Off(1);
	LED_Off(2);
}

void Control_ClockInitiate(void)
{
	// Power up Timer0, Timer1, and Timer2
	LPC_SC->PCONP |= 1 << 1; 
	LPC_SC->PCONP |= 1 << 2;
	LPC_SC->PCONP |= 1 << 22;
	
	// Clock select Timer0, Timer1, and Timer2 (PCLK = CCLK)
	LPC_SC->PCLKSEL0 |= 1 << 2;
	LPC_SC->PCLKSEL0 |= 1 << 4;
	LPC_SC->PCLKSEL1 |= 1 << 12;
}
