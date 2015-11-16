/**
 *  BasalDose.c
 *
 *  Created on: Aug 31, 2015
 *      Author: sle
 */

#include "BasalDose.h"
#include "StepperMotor.h"
#include "Control.h"

extern uint32_t StepperMotor_GlobalPosition;

// Global variable
uint32_t BasalDose_DoseAmountCounter;

// Set and enable Timer0 for the basal timer in between doses
void BasalDose_DoseTimingInitiate(void)
{
	// Initialize the pins P1.28 to P1.31
	// The pins are used for debugging
	LPC_GPIO1->FIODIR |= (0xF0000000);
	LPC_GPIO1->FIOPIN &=~(0xF0000000);

	LPC_SC->PCONP |= 1 << 1; // Power up Timer0
	LPC_SC->PCLKSEL0 |= 1 << 2; // Clock select
	LPC_TIM0->PR = 0x02; // Pre-scalar
	LPC_TIM0->MR0 = 1 << 27; // Match number
	LPC_TIM0->MCR |= 1 << 0; // Interrupt and reset
	LPC_TIM0->MCR |= 1 << 1; // Reset timer on Match 0.
	LPC_TIM0->TCR |= 1 << 1; // Manually Reset Timer0 (forced)
	LPC_TIM0->TCR &=~(1 << 1); // Stop resetting the timer.
	LPC_TIM0->TCR |= 1 << 0; // Reset Timer0
	
	BasalDose_DoseTimingEnable(); // Enable Timer0
}

// Enable Timer0
void BasalDose_DoseTimingEnable(void)
{
	LPC_TIM0->TCR |= 1 << 1; // Manually Reset Timer0 (forced)
	LPC_TIM0->TCR &=~(1 << 1); // Stop resetting the timer.
	LPC_TIM0->TCR |= 1 << 0; // Reset Timer0
	NVIC_EnableIRQ(TIMER0_IRQn); // Enable Timer0 IRQ
}

// Disable Timer0
void BasalDose_DoseTimingDisable(void)
{
	NVIC_DisableIRQ(TIMER0_IRQn); // Disable Timer0 IRQ
}

// Enable Timer1
void BasalDose_DoseEnable(void)
{
	LPC_TIM0->IR |= 1 << 0; // Clear MR0 interrupt flag

	NVIC_EnableIRQ(TIMER1_IRQn); // Enable Timer1 IRQ
}

// Disable Timer1
void BasalDose_DoseDisable(void)
{
	NVIC_DisableIRQ(TIMER1_IRQn); // Disable Timer1 IRQ
}

// Set up Timer1 for the speed of the stepper motor
void BasalDose_DoseAmountInitiate(void)
{
	LPC_SC->PCONP |= 1 << 2; // Power up Timer1
	LPC_SC->PCLKSEL0 |= 1 << 2; // Clock select
	LPC_TIM1->PR = 0x02; // Pre-scalar
	LPC_TIM1->MR0 = 1 << 17; // Match number
	LPC_TIM1->MCR |= 1 << 0; // Interrupt and reset
	LPC_TIM1->MCR |= 1 << 1; // Reset timer on Match 0.
	LPC_TIM1->TCR |= 1 << 1; // Manually Reset Timer1 (forced)
	LPC_TIM1->TCR &=~(1 << 1); // Stop resetting the timer.
	LPC_TIM1->TCR |= 1 << 0; // Reset Timer1
}

// Function that calls the stepper motor
void BasalDose_DoseInject(void)
{
	LPC_TIM1->IR |= 1 << 0; // Clear MR0 interrupt flag
	
	BasalDose_DoseTimingDisable(); // Disable Timer0
	
	// Turn P1.28 LED on to indicate stepper motor is spinning (forward)
	LPC_GPIO1->FIOSET |= 1 << 28;
	
	StepperMotor_StepForward(); // Call the stepper motor
}

// Function tthat calls the stepper motor in reverse
void BasalDose_RetractSyringe(void)
{
	LPC_TIM1->IR |= 1 << 0; // Clear MR0 interrupt flag
	
	BasalDose_DoseTimingDisable(); // Disable Timer0
	
	// Turn P1.28 LED on to indicate stepper motor is spinning (backward)
	LPC_GPIO1->FIOSET |= 1 << 28;
	
	/**
	 * I have retract currently as the same LED as going forward,
	 * could easily change to another LED
	 */
	LPC_GPIO1->FIOSET |= 1 << 29; 
	
	StepperMotor_StepBackward(); // Call stepper motor
}

// Timer0 IRQ Handler
void TIMER0_IRQHandler(void)
{
	if((LPC_TIM0->IR & 0x01) == 0x01) // If MR0 interrupt
	{
		Control_DosageAmount(BASAL_STEPS); // Calculate the number of steps
		
		// Turn P1.29 LED on to indicate that the basal dose is being administered
		LPC_GPIO1->FIOSET |= 1 << 29;
		
		BasalDose_DoseEnable(); // Enables Timer1
	}
}

// Timer1 IRQ Handler
void TIMER1_IRQHandler(void)
{
	if((LPC_TIM1->IR & 0x01) == 0x01) // if MR0 interrupt
	{
		//BasalDose_DoseInject(); // Call the stepper motor forward
		
		if(!Control_IsSyringeEmpty()) // check if the syringe is empty
		{
			BasalDose_DoseInject(); // Call the stepper motor forward
		}
		else
		{
			// If the syringe empty, clear out bolus LED if it is being adminsitered
			LPC_GPIO1->FIOCLR |= 1 << 31; 
			
			if(StepperMotor_GlobalPosition <= SYRINGE_LENGTH)
				StepperMotor_GlobalPosition += SYRINGE_LENGTH;
			BasalDose_RetractSyringe(); // Call the stepper motor backward
		}
		
	}
}
