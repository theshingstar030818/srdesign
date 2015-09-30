/*
 * Control.c
 *
 *  Created on: Aug 31, 2015
 *      Author: sle
 */

#include "lpc17xx.h"                 // Device header
#include <stdbool.h>

uint32_t currentPos;
uint32_t globalPos;

void stepForward();
void stepBackward();
void stepInitiate();
bool isSyringeEmpty();

int main()
{
	SystemCoreClockUpdate();

	LPC_GPIO2->FIODIR = 0x000000FF;

	LPC_GPIO2->FIOCLR = 0x000000FF;

	LPC_GPIO2->FIOSET = (1 << 3);

	while(1);
	stepInitiate();

	LPC_GPIO0->FIOSET = 0x0000000F;

	while(1);

	stepForward(currentPos);

	return 0;
}

void stepInitiate()
{

		LPC_GPIO0->FIODIR = 0x0000000F;
		LPC_GPIO0->FIOCLR = 0x0000000F;

		currentPos = 0;
		globalPos = 0;

}

void stepForward()
{
	bool isEmpty = isSyringeEmpty();
	while(!(isEmpty))
	{
		globalPos += 1;
		switch(currentPos)
		{
			case 0:
				LPC_GPIO0->FIOSET |= (0x00000002);
				currentPos += 1;
				break;
			case 1:
				LPC_GPIO0->FIOSET &= (0xFFFFFFF2);
				currentPos += 1;
				break;
			case 2:
				LPC_GPIO0->FIOSET |= (0x00000004);
				currentPos += 1;
				break;
			case 3:
				LPC_GPIO0->FIOSET &= (0xFFFFFFF4);
				currentPos += 1;
				break;
			case 4:
				LPC_GPIO0->FIOSET |= (0x00000008);
				currentPos += 1;
				break;
			case 5:
				LPC_GPIO0->FIOSET &= (0xFFFFFFF8);
				currentPos += 1;
				break;
			case 6:
				LPC_GPIO0->FIOSET |= (0x00000001);
				currentPos += 1;
				break;
			case 7:
				LPC_GPIO0->FIOSET &= (0xFFFFFFF1);
				currentPos = 0;
				break;
		}
	}
	stepBackward();
}

bool isSyringeEmpty()
{
	if(globalPos >= 300)
		return true;
	else
		return false;
}

void stepBackward()
{
	for(; globalPos > 0; globalPos--)
	{
		switch(currentPos)
		{
			case 0:
				LPC_GPIO0->FIOSET |= (0x00000008);
				currentPos = 7;
				break;
			case 1:
				LPC_GPIO0->FIOSET &= (0xFFFFFFF1);
				currentPos--;
				break;
			case 2:
				LPC_GPIO0->FIOSET |= (0x00000001);
				currentPos--;
				break;
			case 3:
				LPC_GPIO0->FIOSET &= (0xFFFFFFF2);
				currentPos--;
				break;
			case 4:
				LPC_GPIO0->FIOSET |= (0x00000002);
				currentPos--;
				break;
			case 5:
				LPC_GPIO0->FIOSET &= (0xFFFFFFF4);
				currentPos--;
				break;
			case 6:
				LPC_GPIO0->FIOSET |= (0x00000004);
				currentPos--;
				break;
			case 7:
				LPC_GPIO0->FIOSET &= (0xFFFFFFF8);
				currentPos--;
				break;
		}
	}
	globalPos = 0;
	stepForward();

}
