/**
 *  BolusDose.c
 *
 *  Created on: Aug 31, 2015
 *      Author: sle
 */
 
#include "lpc17xx.h"  
#include "BolusDose.h"

// Amount of steps for Bolus
#define BOLUS_STEPS 200

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
	LPC_GPIO1->FIOPIN ^= 1 << 31; // Toggle the LED
	
	Control_DosageAmount(BOLUS_STEPS); // Calculate the number of steps
	
	BasalDose_DoseEnable(); // Enable Timer1
}
