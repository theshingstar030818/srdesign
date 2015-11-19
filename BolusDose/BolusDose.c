/**
 *  BolusDose.c
 *
 *  Created on: Aug 31, 2015
 *      Author: sle
 */

#include "..\BolusDose\BolusDose.h"
#include "..\Control.h"

// Global variable
uint32_t BolusDose_DoseAmountCounter;

// Set and enable External Interrupt 3
void BolusDose_DoseInitiate(void)
{

	LPC_PINCON->PINSEL4 &=~ (3<<20); // P2.10 is GPIO
	LPC_GPIO2->FIODIR &=~ (1<<10); // P2.10 in input

	LPC_GPIOINT->IO2IntEnF |= (1 << 10); // Enabling falling edge to P2.10

	NVIC_EnableIRQ(EINT3_IRQn); // Enable External Interrupt 3
}

// Enable external interrupt
void EINT3_IRQHandler(void)
{
	LPC_GPIOINT->IO2IntClr |= (1<<10); // Clear the status

	// Turn P1.31 LED on to indicate that the bolus dose is being administered
	LPC_GPIO1->FIOSET |= 1 << 31;

	Control_DosageAmount(BOLUS_STEPS); // Calculate the number of steps

	BasalDose_DoseEnable(); // Enable Timer1
}
