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
#include ".\StepperMotor\StepperMotor.h"

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
	
	// Initialize LEDs for indication of current dosage
	Control_LEDInitiate();
	
	// Initialize Timers 0, 1
	BasalDose_DoseTimingInitiate();
	BasalDose_DoseInitiate();
	
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
			for(j = 0; j < 25; j++);
		}
	}
}

void Control_LEDInitiate(void)
{
	// Set pins P1.28, P1.29, P1.31 as output
	LPC_GPIO1->FIODIR |= (0xD0000000);
	LPC_GPIO1->FIOPIN &=~(0xD0000000);
	
	// Set pins P2.2, P2.3 as output
	//LPC_GPIO2->FIODIR |= (0x00000006);
	//LPC_GPIO2->FIOPIN &=~(0x00000006);
}

void Control_LEDClear(void)
{
	// Clear out LEDs used for Basal, Bolus, and Backward
	LPC_GPIO1->FIOCLR |= 1 << 28; 
 	LPC_GPIO1->FIOCLR |= 1 << 29;
	LPC_GPIO1->FIOCLR |= 1 << 31;
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
