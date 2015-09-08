/*
 * StepperMotor.c
 *
 *  Created on: Sep 8, 2015
 *      Author: sle
 */

//static int stepSequence[] = {1, 2, 4, 8};
int curPosition = 0;

void StepperMotor_StepFoward()
{
	switch (curPosition)
	{
		case 0:
			P0[0] = 1;
			P0[1] = 0;
			P0[2] = 0;
			P0[3] = 0;
			curPosition += 1;
			break;
		case 1:
			P0[0] = 0;
			P0[1] = 1;
			P0[2] = 0;
			P0[3] = 0;
			curPosition += 1;
			break;
		case 2:
			P0[0] = 0;
			P0[1] = 0;
			P0[2] = 1;
			P0[3] = 0;
			curPosition += 1;
			break;
		case 3:
			P0[0] = 0;
			P0[1] = 0;
			P0[2] = 0;
			P0[3] = 1;
			curPosition = 0;
			break;
	}
}

void StepperMotor_StepBackward()
{
}
