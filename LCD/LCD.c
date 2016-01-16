 /**
 *  LCD.c
 *
 *  Created on: Dec 16, 2015
 *      Author: sle
 */

#include <stdio.h>
#include ".\LCD.h"
#include "..\Control.h"
#include "..\InsulinQueue\InsulinQueue.h"
#include "..\StepperMotor\StepperMotor.h"

extern GLCD_FONT GLCD_Font_16x24; // Font size

extern uint32_t StepperMotor_GlobalPosition;

extern status Control_GlobalStatus;

extern InsulinQueue *globalIQ;

// Used to hold string representation of StepperMotor_GlobalPosition
char stringInsulin[6]; 
char inQueue[10];

void LCD_Initiate(void)
{
	//Initialize the LCD
	GLCD_Initialize();
	
	// Set font size
	GLCD_SetFont(&GLCD_Font_16x24);
	
	// Set background and foreground colors
	GLCD_SetBackgroundColor(GLCD_COLOR_WHITE);
	GLCD_SetForegroundColor(GLCD_COLOR_BLACK);
	
	// Clear the screen for first use
	GLCD_ClearScreen();
}

void LCD_UpdateScreenStatus()
{
	// Display on LCD
	switch(Control_GlobalStatus)
	{
		case Basal:
			GLCD_DrawString(20, 20, "Basal\0");
			break;
		case Bolus:
			GLCD_DrawString(20, 20, "Bolus\0");
			break;
		case Backward:
			GLCD_DrawString(20, 20, "Backward\0");
			break;
		case None:
			GLCD_DrawString(20, 20, "None\0");
			break;
	}
}

void LCD_UpdateScreenInsulin(void)
{
	int k;
	// Format the integer into a string, display on LCD
	sprintf(stringInsulin, "%d", StepperMotor_GlobalPosition);
	GLCD_DrawString(20, 40, stringInsulin);
	for(k = 0; k < 5; k++)
	{
		sprintf(inQueue, "%d", globalIQ->insulinEntry[k]);
		GLCD_DrawString((20 + (k*20)), 60, inQueue);
	}
	
}
