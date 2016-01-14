/**
 *  Speaker.c
 *
 *  Created on: Jan 12, 2016
 *      Author: sle
 */

void Speaker_Initiate(void)
{
	// Initialize pin P0.26 to output
	LPC_GPIO->FIODIR |= 1 << 26;
}

void Speaker_Play(int loops)
{
	// Turn the speaker on and off no. of times specified
	while(num_times >= 0)
	{
		LPC_GPIO0->FIOSET |= 1 << 26; // Set P0.26
		Speaker_Wait();
		LPC_GPIO0->FIOCLR |= 1 << 26; // Clear P0.26
		Speaker_Wait();
		num_times--; // Decrement
	}
}

void Speaker_Wait(void) // This could possibly be moved straight into control and used as a universal wait
{												// instead of a class specific wait loop, with parameters that define the number of loops
	int i, j;
	for(i = 0; i < 250000; i++);
}
