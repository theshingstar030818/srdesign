 /**
 *  Joystick.c
 *
 *  Created on: Dec 30, 2015
 *      Author: mfeist
 */

#include "..\Control.h"
#include "Joystick.h"

extern status Control_GlobalStatus;

void Joystick_RetractInitiate(void)
{
	// Already done with the Joystick function
	//LPC_PINCON->PINSEL3 &= ~(3<<14); // P1.23 is GPIO
	//LPC_GPIO1->FIODIR &= ~(1<<23); // P1.23 is input
	
	// Doesn't work for Port 1
	// LPC_GPIOINT->IO1IntEnF |= (1<<23); // Enabling falling edge to P1.23
	NVIC_EnableIRQ(EINT1_IRQn); // Enable External Interrupt 1
}

void Joystick_ReplacedSyringeInitiate(void)
{
	
}

void EINT1_IRQHandler(void)
{
	// Doesn't work for Port 1
	// LPC_GPIOINT->IO1IntClr |= (1<<23);
	
	Control_GlobalStatus = Backward;
}

void EINT2_IRQHandler(void)
{
	
}
