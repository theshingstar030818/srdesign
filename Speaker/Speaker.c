 /**
 *  Speaker.c
 *
 *  Created on: Dec 18, 2015
 *      Author: mfeist
 */

#include "..\Control.h"
#include "Speaker.h"

void Speaker_Initiate(void)
{
	// Initialize P0.26 as output
	LPC_PINCON->PINSEL1 &= ~(3<<20);
	LPC_PINCON->PINSEL1 |= (2<<20);
	LPC_PINCON->PINMODE1 &= ~(3<<20);
	LPC_PINCON->PINMODE1 |= (2<<20);
}

void Speaker_Play(void)
{
	//LPC_DAC->DACR = ;
}

