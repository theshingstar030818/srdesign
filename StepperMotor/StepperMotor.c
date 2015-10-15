/*
 * StepperMotor.c
 *
 *  Created on: Sep 8, 2015
 *      Author: sle
 */

void StepperMotor_Initiate()
{
	LPC_GPIO0->FIODIR |= (0x0000000F);
	LPC_GPIO0->FIOPIN &= ~(0x0000000F);

	currentPos = 0;
	globalPos = 0;
}

void StepperMotor_StepFoward()
{
	while(1)
	{
		if(isSyringeEmpty())
			break;
		globalPos += 1;
		switch(currentPos)
		{
			case 0:
				LPC_GPIO0->FIOPIN = (0x00000003);
				currentPos += 1;
				break;
			case 1:
				LPC_GPIO0->FIOPIN = (0x00000002);
				currentPos += 1;
				break;
			case 2:
				LPC_GPIO0->FIOPIN = (0x00000006);
				currentPos += 1;
				break;
			case 3:
				LPC_GPIO0->FIOPIN = (0x00000004);
				currentPos += 1;
				break;
			case 4:
				LPC_GPIO0->FIOPIN = (0x0000000C);
				currentPos += 1;
				break;
			case 5:
				LPC_GPIO0->FIOPIN = (0x00000008);
				currentPos += 1;
				break;
			case 6:
				LPC_GPIO0->FIOPIN = (0x00000009);
				currentPos += 1;
				break;
			case 7:
				LPC_GPIO0->FIOPIN = (0x00000001);
				currentPos = 0;
				break;
		}
		for(i=0; i<max_time; i++);
	}
	stepBackward();
}

void StepperMotor_StepBackward()
{
	for(; globalPos > 0; globalPos--)
	{
		switch(currentPos)
		{
			case 0:
				LPC_GPIO0->FIOPIN = (0x00000009);
				currentPos = 7;
				break;
			case 1:
				LPC_GPIO0->FIOPIN = (0x00000001);
				currentPos--;
				break;
			case 2:
				LPC_GPIO0->FIOPIN = (0x00000003);
				currentPos--;
				break;
			case 3:
				LPC_GPIO0->FIOPIN = (0x00000002);
				currentPos--;
				break;
			case 4:
				LPC_GPIO0->FIOPIN = (0x00000006);
				currentPos--;
				break;
			case 5:
				LPC_GPIO0->FIOPIN = (0x00000004);
				currentPos--;
				break;
			case 6:
				LPC_GPIO0->FIOPIN = (0x0000000C);
				currentPos--;
				break;
			case 7:
				LPC_GPIO0->FIOPIN = (0x00000008);
				currentPos--;
				break;
		}
		for(i=0; i<max_time; i++);
	}
	globalPos = 0;
	stepForward();
}
