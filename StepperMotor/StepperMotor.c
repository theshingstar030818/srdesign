/*
 * StepperMotor.c
 *
 *  Created on: Sep 8, 2015
 *      Author: sle
 */

static int stepSequence[] = {1, 2, 4, 8};
int position = 0;

void StepperMotor_StepFoward()
{
	PORT1 = stepSequence[position];
	if (position == 3)
	{
		position = 0;
	}
	position += 1;
}

void StepperMotor_StepBackward()
{
	PORT1 = stepSequence[position];
	if (position == 0)
	{
		position = 3;
	}
	position -= 1;
}
