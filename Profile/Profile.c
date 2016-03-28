/**
 *  Profile.h
 * 
 *  Created on: March 18, 2016
 *      Author: mfeist
 */

#include <stdio.h>
#include <stdlib.h>
#include "Profile.h"
#include "..\LCD\LCD.h"

extern uint32_t Control_JoystickState;

BaseDisplay Profile_BaseDisplay;
BaseDisplay* pProfile_BaseDisplay;
ProfileOptions Profile_CurrentOptions;
uint32_t Profile_BolusSteps;

const uint32_t Profile_DosageRecommendation[48] = {6,  9, 12, 14, /* Child Inactive */ 5,  7,  9, 12, /* Child Moderate */ 4,  6,  8, 10, /* Child Active */
																									21, 30, 40, 50, /* Adolescent Inactive */ 17, 25, 33, 40, /* Adolescent Moderate */ 13, 19, 25, 32, /* Adolescent Active */
																									17, 25, 33, 40, /* Adult Inactive */ 14, 21, 28, 34, /* Adult Moderate */ 10, 15, 21, 27, /* Adult Active */
																									14, 21, 28, 34, /* Elder Inactive */ 10, 15, 21, 27, /* Elder Moderate */ 7,  11, 15, 20 /* Elder Active */};									

uint32_t Profile_AllProfiles[NUM_AGE_GROUP][NUM_ACTIVITY_LEVEL][NUM_OPTIONS];

void Profile_Initiate(void)
{
	AGE Profile_AgeGroup;
  ACTIVITY Profile_ActivityGroup;
	
	int i,j,k;
	for(i = 0; i < NUM_AGE_GROUP; i++)
	{
		for(j = 0; j < NUM_ACTIVITY_LEVEL; j++)
		{
			for(k = 0; k < NUM_OPTIONS; k++)
			{
					Profile_AllProfiles[i][j][k] = Profile_DosageRecommendation[(i*NUM_AGE_GROUP*NUM_ACTIVITY_LEVEL)+(j*NUM_AGE_GROUP)+k];
			}
		}
	}
	
	Profile_BaseDisplay = Profile_CreateBaseDisplay("Age Group", "Child", "Adolescent", "Adult", "Elderly");
	pProfile_BaseDisplay = &Profile_BaseDisplay;
	LCD_DisplayOptions(Profile_BaseDisplay);
	
	do {
		Control_Debounce();
	} while (!(Control_JoystickState & (JOYSTICK_LEFT | JOYSTICK_RIGHT | JOYSTICK_UP | JOYSTICK_DOWN)));
	if (Control_JoystickState == JOYSTICK_LEFT)
	{
		Profile_AgeGroup = Child;
	}
	if (Control_JoystickState == JOYSTICK_RIGHT)
	{
		Profile_AgeGroup = Adolescent;
	}
	if (Control_JoystickState  == JOYSTICK_UP)
	{
		Profile_AgeGroup = Adult;
	}
	if (Control_JoystickState == JOYSTICK_DOWN)
	{
		Profile_AgeGroup = Elderly;
	}
	GLCD_ClearScreen();
	
	Profile_UpdateBaseDisplay(pProfile_BaseDisplay, "Activity Level", "", "Moderately Active", "Very Active", "Mostly Inactive");
	LCD_DisplayOptions(Profile_BaseDisplay);
	do {
		Control_Debounce();
	} while (!(Control_JoystickState & (JOYSTICK_RIGHT | JOYSTICK_UP | JOYSTICK_DOWN)));
	if (Control_JoystickState == JOYSTICK_RIGHT)
	{
		Profile_ActivityGroup = Moderate;
	}
	if (Control_JoystickState == JOYSTICK_UP)
	{
		Profile_ActivityGroup = Active;
	}
	if (Control_JoystickState == JOYSTICK_DOWN)
	{
		Profile_ActivityGroup = Inactive;
	}
	GLCD_ClearScreen();
	
	Profile_CurrentOptions = Profile_CreateProfile(Profile_AgeGroup, Profile_ActivityGroup);
	
	Profile_RecommendDosage();
}

void Profile_RecommendDosage(void)
{
	int i;
	char opt[4][25];
	for(i = 0; i < NUM_OPTIONS; i++)
	{
		sprintf(opt[i],"%d Units per Hour", Profile_AllProfiles[Profile_CurrentOptions.Age][Profile_CurrentOptions.Activity][i]);
	}
	Profile_BaseDisplay = Profile_CreateBaseDisplay("Dosage", opt[0], opt[1], opt[2], opt[3]);
	LCD_DisplayOptions(Profile_BaseDisplay);
	
	do {
		Control_Debounce(); 
	} while (!(Control_JoystickState & (JOYSTICK_LEFT | JOYSTICK_RIGHT | JOYSTICK_UP | JOYSTICK_DOWN)));
	if (Control_JoystickState == JOYSTICK_LEFT)
	{
		Profile_AssignBasalSteps(Profile_AllProfiles[Profile_CurrentOptions.Age][Profile_CurrentOptions.Activity][0]);
	}
	if (Control_JoystickState == JOYSTICK_RIGHT)
	{
		Profile_AssignBasalSteps(Profile_AllProfiles[Profile_CurrentOptions.Age][Profile_CurrentOptions.Activity][1]);
	}
	if (Control_JoystickState == JOYSTICK_UP)
	{
		Profile_AssignBasalSteps(Profile_AllProfiles[Profile_CurrentOptions.Age][Profile_CurrentOptions.Activity][2]);
	}
	if (Control_JoystickState == JOYSTICK_DOWN)
	{
		Profile_AssignBasalSteps(Profile_AllProfiles[Profile_CurrentOptions.Age][Profile_CurrentOptions.Activity][3]);
	}
}

void Profile_AssignBasalSteps(int units)
{
	Profile_CurrentOptions.BasalStepsPerDay = (uint32_t)(units * SYRINGE_LENGTH / 100.0);
	Profile_CurrentOptions.BasalStepsPerDose = (uint32_t)(Profile_CurrentOptions.BasalStepsPerDay / 60.0);
}

void Profile_Bolus(void)
{
	GLCD_ClearScreen();
	Profile_UpdateBaseDisplay(pProfile_BaseDisplay, "Bolus Amount", "1 Unit", "4 Units", "7 Units", "10 Units");
	LCD_DisplayOptions(Profile_BaseDisplay);
	do {
		Control_Debounce();
	} while (!(Control_JoystickState & (JOYSTICK_LEFT | JOYSTICK_RIGHT | JOYSTICK_UP | JOYSTICK_DOWN)));
	if (Control_JoystickState == JOYSTICK_LEFT)
	{
		Profile_BolusSteps = (uint32_t)(1 * SYRINGE_LENGTH / 100);
	}
	if (Control_JoystickState == JOYSTICK_RIGHT)
	{
		Profile_BolusSteps = (uint32_t)(4 * SYRINGE_LENGTH / 100);
	}
	if (Control_JoystickState  == JOYSTICK_UP)
	{
		Profile_BolusSteps = (uint32_t)(7 * SYRINGE_LENGTH / 100);
	}
	if (Control_JoystickState == JOYSTICK_DOWN)
	{
		Profile_BolusSteps = (uint32_t)(10 * SYRINGE_LENGTH / 100);
	}
}

BaseDisplay Profile_CreateBaseDisplay(char *cat, char *opt1, char *opt2,
																			char *opt3, char *opt4)
{
	BaseDisplay temp;
	strcpy(temp.ProfileCategory, cat);
	strcpy(temp.ProfileOption1, opt1);
	strcpy(temp.ProfileOption2, opt2);
	strcpy(temp.ProfileOption3, opt3);
	strcpy(temp.ProfileOption4, opt4);
	
	temp.Size1 = strlen(opt1);
	temp.Size2 = strlen(opt2);
	temp.Size3 = strlen(opt3);
	temp.Size4 = strlen(opt4);
	
	return temp;
}

BaseDisplay* Profile_UpdateBaseDisplay(BaseDisplay *temp, char *cat, char *opt1, 
																			char *opt2, char *opt3, char *opt4)
{
	memset(temp->ProfileCategory, 0, 25);
	memset(temp->ProfileOption1, 0, 25);
	memset(temp->ProfileOption2, 0, 25);
	memset(temp->ProfileOption3, 0, 25);
	memset(temp->ProfileOption4, 0, 25);
	
	strcpy(temp->ProfileCategory, cat);
	strcpy(temp->ProfileOption1, opt1);
	strcpy(temp->ProfileOption2, opt2);
	strcpy(temp->ProfileOption3, opt3);
	strcpy(temp->ProfileOption4, opt4);
	
	temp->Size1 = strlen(opt1);
	temp->Size2 = strlen(opt2);
	temp->Size3 = strlen(opt3);
	temp->Size4 = strlen(opt4);
	
	return temp;
}

ProfileOptions Profile_CreateProfile(AGE AgeRange, ACTIVITY ActivityGroup)
{
	ProfileOptions temp;
	
	temp.Age = AgeRange;
	temp.Activity = ActivityGroup;
	
	return temp;
}
