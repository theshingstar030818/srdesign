/**
 *  Control.h
 * 
 *  Created on: March 18, 2016
 *      Author: mfeist
 */

#include "Profile.h"
#include "..\LCD\LCD.h"

extern uint32_t Control_JoystickState;
extern AGE Control_AgeGroup;
extern ACTIVITY Control_ActivityGroup;

BaseDisplay Profile_BaseDisplay;
BaseDisplay* pProfile_BaseDisplay;
uint32_t Profil_BasalRate;
uint32_t Profile_BasalSteps;
uint32_t Profile_BolusSteps;

void Profile_Initiate(void)
{
	Profile_BaseDisplay = Profile_CreateBaseDisplay("Age Group", "Child", "Adolescent", "Adult", "Elderly");
	pProfile_BaseDisplay = &Profile_BaseDisplay;
	LCD_Options(Profile_BaseDisplay);
	
	do {
		Control_JoystickState = Joystick_GetState(); 
	} while (!(((Control_JoystickState & JOYSTICK_LEFT) == JOYSTICK_LEFT) || ((Control_JoystickState & JOYSTICK_UP) == JOYSTICK_UP) || 
					((Control_JoystickState & JOYSTICK_RIGHT) == JOYSTICK_RIGHT) || ((Control_JoystickState & JOYSTICK_DOWN) == JOYSTICK_DOWN)));
	if ((Control_JoystickState & JOYSTICK_LEFT) == JOYSTICK_LEFT)
	{
		Control_AgeGroup = Child;
	}
	if ((Control_JoystickState & JOYSTICK_UP) == JOYSTICK_UP)
	{
		Control_AgeGroup = Adult;
	}
	if ((Control_JoystickState & JOYSTICK_RIGHT) == JOYSTICK_RIGHT)
	{
		Control_AgeGroup = Adolescent;
	}
	if ((Control_JoystickState & JOYSTICK_DOWN) == JOYSTICK_DOWN)
	{
		Control_AgeGroup = Elderly;
	}
	GLCD_ClearScreen();
	
	Profile_UpdateBaseDisplay(pProfile_BaseDisplay, "Activity Level", "", "Moderately Active", "Very Active", "Mostly Inactive");
	LCD_Options(Profile_BaseDisplay);
	do {
		Control_JoystickState = Joystick_GetState(); 
	} while (!(((Control_JoystickState & JOYSTICK_UP) == JOYSTICK_UP) || 
					((Control_JoystickState & JOYSTICK_RIGHT) == JOYSTICK_RIGHT) || ((Control_JoystickState & JOYSTICK_DOWN) == JOYSTICK_DOWN)));
	if ((Control_JoystickState & JOYSTICK_UP) == JOYSTICK_UP)
	{
		Control_ActivityGroup = Active;
	}
	if ((Control_JoystickState & JOYSTICK_RIGHT) == JOYSTICK_RIGHT)
	{
		Control_ActivityGroup = Moderate;
	}
	if ((Control_JoystickState & JOYSTICK_DOWN) == JOYSTICK_DOWN)
	{
		Control_ActivityGroup = Inactive;
	}
	GLCD_ClearScreen();
	
	switch(Control_AgeGroup)
	{
		case Child:
			switch(Control_ActivityGroup)
			{
				case Inactive:
					Profile_UpdateBaseDisplay(pProfile_BaseDisplay, "Basal Rate", "6 Unit/Day", "9 Unit/Day", "12 Unit/Day", "14 Unit/Day");
					LCD_Options(Profile_BaseDisplay);
					do {
						Control_JoystickState = Joystick_GetState(); 
					} while (!(((Control_JoystickState & JOYSTICK_LEFT) == JOYSTICK_LEFT) || ((Control_JoystickState & JOYSTICK_UP) == JOYSTICK_UP) || 
									((Control_JoystickState & JOYSTICK_RIGHT) == JOYSTICK_RIGHT) || ((Control_JoystickState & JOYSTICK_DOWN) == JOYSTICK_DOWN)));
					/*
					if ((Control_JoystickState & JOYSTICK_LEFT) == JOYSTICK_LEFT)
					{
						Profil_BasalRate = ;
					}
					if ((Control_JoystickState & JOYSTICK_UP) == JOYSTICK_UP)
					{
						Profil_BasalRate = ;
					}
					if ((Control_JoystickState & JOYSTICK_RIGHT) == JOYSTICK_RIGHT)
					{
						Profil_BasalRate = ;
					}
					if ((Control_JoystickState & JOYSTICK_DOWN) == JOYSTICK_DOWN)
					{
						Profil_BasalRate = ;
					}
					*/
					break;
				case Moderate:
					Profile_UpdateBaseDisplay(pProfile_BaseDisplay, "Basal Rate", "5 Unit/Day", "7 Unit/Day", "9 Unit/Day", "12 Unit/Day");
					LCD_Options(Profile_BaseDisplay);
					do {
						Control_JoystickState = Joystick_GetState(); 
					} while (!(((Control_JoystickState & JOYSTICK_LEFT) == JOYSTICK_LEFT) || ((Control_JoystickState & JOYSTICK_UP) == JOYSTICK_UP) || 
									((Control_JoystickState & JOYSTICK_RIGHT) == JOYSTICK_RIGHT) || ((Control_JoystickState & JOYSTICK_DOWN) == JOYSTICK_DOWN)));
					/*
					if ((Control_JoystickState & JOYSTICK_LEFT) == JOYSTICK_LEFT)
					{
						Profil_BasalRate = ;
					}
					if ((Control_JoystickState & JOYSTICK_UP) == JOYSTICK_UP)
					{
						Profil_BasalRate = ;
					}
					if ((Control_JoystickState & JOYSTICK_RIGHT) == JOYSTICK_RIGHT)
					{
						Profil_BasalRate = ;
					}
					if ((Control_JoystickState & JOYSTICK_DOWN) == JOYSTICK_DOWN)
					{
						Profil_BasalRate = ;
					}
					*/
					break;
				case Active:
					Profile_UpdateBaseDisplay(pProfile_BaseDisplay, "Basal Rate", "4 Unit/Day", "6 Unit/Day", "8 Unit/Day", "10 Unit/Day");
					LCD_Options(Profile_BaseDisplay);
					do {
						Control_JoystickState = Joystick_GetState(); 
					} while (!(((Control_JoystickState & JOYSTICK_LEFT) == JOYSTICK_LEFT) || ((Control_JoystickState & JOYSTICK_UP) == JOYSTICK_UP) || 
									((Control_JoystickState & JOYSTICK_RIGHT) == JOYSTICK_RIGHT) || ((Control_JoystickState & JOYSTICK_DOWN) == JOYSTICK_DOWN)));
					/*
					if ((Control_JoystickState & JOYSTICK_LEFT) == JOYSTICK_LEFT)
					{
						Profil_BasalRate = ;
					}
					if ((Control_JoystickState & JOYSTICK_UP) == JOYSTICK_UP)
					{
						Profil_BasalRate = ;
					}
					if ((Control_JoystickState & JOYSTICK_RIGHT) == JOYSTICK_RIGHT)
					{
						Profil_BasalRate = ;
					}
					if ((Control_JoystickState & JOYSTICK_DOWN) == JOYSTICK_DOWN)
					{
						Profil_BasalRate = ;
					}
					*/
					break;
			}
			break;
		case Adolescent:
			switch(Control_ActivityGroup)
			{
				case Inactive:
					Profile_UpdateBaseDisplay(pProfile_BaseDisplay, "Basal Rate", "21 Unit/Day", "31 Unit/Day", "41 Unit/Day", "50 Unit/Day");
					LCD_Options(Profile_BaseDisplay);
					do {
						Control_JoystickState = Joystick_GetState(); 
					} while (!(((Control_JoystickState & JOYSTICK_LEFT) == JOYSTICK_LEFT) || ((Control_JoystickState & JOYSTICK_UP) == JOYSTICK_UP) || 
									((Control_JoystickState & JOYSTICK_RIGHT) == JOYSTICK_RIGHT) || ((Control_JoystickState & JOYSTICK_DOWN) == JOYSTICK_DOWN)));
					/*
					if ((Control_JoystickState & JOYSTICK_LEFT) == JOYSTICK_LEFT)
					{
						Profil_BasalRate = ;
					}
					if ((Control_JoystickState & JOYSTICK_UP) == JOYSTICK_UP)
					{
						Profil_BasalRate = ;
					}
					if ((Control_JoystickState & JOYSTICK_RIGHT) == JOYSTICK_RIGHT)
					{
						Profil_BasalRate = ;
					}
					if ((Control_JoystickState & JOYSTICK_DOWN) == JOYSTICK_DOWN)
					{
						Profil_BasalRate = ;
					}
					*/
					break;
				case Moderate:
					Profile_UpdateBaseDisplay(pProfile_BaseDisplay, "Basal Rate", "17 Unit/Day", "25 Unit/Day", "33 Unit/Day", "40 Unit/Day");
					LCD_Options(Profile_BaseDisplay);
					do {
						Control_JoystickState = Joystick_GetState(); 
					} while (!(((Control_JoystickState & JOYSTICK_LEFT) == JOYSTICK_LEFT) || ((Control_JoystickState & JOYSTICK_UP) == JOYSTICK_UP) || 
									((Control_JoystickState & JOYSTICK_RIGHT) == JOYSTICK_RIGHT) || ((Control_JoystickState & JOYSTICK_DOWN) == JOYSTICK_DOWN)));
					/*
					if ((Control_JoystickState & JOYSTICK_LEFT) == JOYSTICK_LEFT)
					{
						Profil_BasalRate = ;
					}
					if ((Control_JoystickState & JOYSTICK_UP) == JOYSTICK_UP)
					{
						Profil_BasalRate = ;
					}
					if ((Control_JoystickState & JOYSTICK_RIGHT) == JOYSTICK_RIGHT)
					{
						Profil_BasalRate = ;
					}
					if ((Control_JoystickState & JOYSTICK_DOWN) == JOYSTICK_DOWN)
					{
						Profil_BasalRate = ;
					}
					*/
					break;
				case Active:
					Profile_UpdateBaseDisplay(pProfile_BaseDisplay, "Basal Rate", "13 Unit/Day", "19 Unit/Day", "25 Unit/Day", "32 Unit/Day");
					LCD_Options(Profile_BaseDisplay);
					do {
						Control_JoystickState = Joystick_GetState(); 
					} while (!(((Control_JoystickState & JOYSTICK_LEFT) == JOYSTICK_LEFT) || ((Control_JoystickState & JOYSTICK_UP) == JOYSTICK_UP) || 
									((Control_JoystickState & JOYSTICK_RIGHT) == JOYSTICK_RIGHT) || ((Control_JoystickState & JOYSTICK_DOWN) == JOYSTICK_DOWN)));
					/*
					if ((Control_JoystickState & JOYSTICK_LEFT) == JOYSTICK_LEFT)
					{
						Profil_BasalRate = ;
					}
					if ((Control_JoystickState & JOYSTICK_UP) == JOYSTICK_UP)
					{
						Profil_BasalRate = ;
					}
					if ((Control_JoystickState & JOYSTICK_RIGHT) == JOYSTICK_RIGHT)
					{
						Profil_BasalRate = ;
					}
					if ((Control_JoystickState & JOYSTICK_DOWN) == JOYSTICK_DOWN)
					{
						Profil_BasalRate = ;
					}
					*/
					break;
			}
			break;
		case Adult:
			switch(Control_ActivityGroup)
			{
				case Inactive:
					Profile_UpdateBaseDisplay(pProfile_BaseDisplay, "Basal Rate", "17 Unit/Day", "25 Unit/Day", "33 Unit/Day", "40 Unit/Day");
					LCD_Options(Profile_BaseDisplay);
					do {
						Control_JoystickState = Joystick_GetState(); 
					} while (!(((Control_JoystickState & JOYSTICK_LEFT) == JOYSTICK_LEFT) || ((Control_JoystickState & JOYSTICK_UP) == JOYSTICK_UP) || 
									((Control_JoystickState & JOYSTICK_RIGHT) == JOYSTICK_RIGHT) || ((Control_JoystickState & JOYSTICK_DOWN) == JOYSTICK_DOWN)));
					/*
					if ((Control_JoystickState & JOYSTICK_LEFT) == JOYSTICK_LEFT)
					{
						Profil_BasalRate = ;
					}
					if ((Control_JoystickState & JOYSTICK_UP) == JOYSTICK_UP)
					{
						Profil_BasalRate = ;
					}
					if ((Control_JoystickState & JOYSTICK_RIGHT) == JOYSTICK_RIGHT)
					{
						Profil_BasalRate = ;
					}
					if ((Control_JoystickState & JOYSTICK_DOWN) == JOYSTICK_DOWN)
					{
						Profil_BasalRate = ;
					}
					*/
					break;
				case Moderate:
					Profile_UpdateBaseDisplay(pProfile_BaseDisplay, "Basal Rate", "14 Unit/Day", "21 Unit/Day", "28 Unit/Day", "34 Unit/Day");
					LCD_Options(Profile_BaseDisplay);
					do {
						Control_JoystickState = Joystick_GetState(); 
					} while (!(((Control_JoystickState & JOYSTICK_LEFT) == JOYSTICK_LEFT) || ((Control_JoystickState & JOYSTICK_UP) == JOYSTICK_UP) || 
									((Control_JoystickState & JOYSTICK_RIGHT) == JOYSTICK_RIGHT) || ((Control_JoystickState & JOYSTICK_DOWN) == JOYSTICK_DOWN)));
					/*
					if ((Control_JoystickState & JOYSTICK_LEFT) == JOYSTICK_LEFT)
					{
						Profil_BasalRate = ;
					}
					if ((Control_JoystickState & JOYSTICK_UP) == JOYSTICK_UP)
					{
						Profil_BasalRate = ;
					}
					if ((Control_JoystickState & JOYSTICK_RIGHT) == JOYSTICK_RIGHT)
					{
						Profil_BasalRate = ;
					}
					if ((Control_JoystickState & JOYSTICK_DOWN) == JOYSTICK_DOWN)
					{
						Profil_BasalRate = ;
					}
					*/
					break;
				case Active:
					Profile_UpdateBaseDisplay(pProfile_BaseDisplay, "Basal Rate", "10 Unit/Day", "16 Unit/Day", "22 Unit/Day", "27 Unit/Day");
					LCD_Options(Profile_BaseDisplay);
					do {
						Control_JoystickState = Joystick_GetState(); 
					} while (!(((Control_JoystickState & JOYSTICK_LEFT) == JOYSTICK_LEFT) || ((Control_JoystickState & JOYSTICK_UP) == JOYSTICK_UP) || 
									((Control_JoystickState & JOYSTICK_RIGHT) == JOYSTICK_RIGHT) || ((Control_JoystickState & JOYSTICK_DOWN) == JOYSTICK_DOWN)));
					/*
					if ((Control_JoystickState & JOYSTICK_LEFT) == JOYSTICK_LEFT)
					{
						Profil_BasalRate = ;
					}
					if ((Control_JoystickState & JOYSTICK_UP) == JOYSTICK_UP)
					{
						Profil_BasalRate = ;
					}
					if ((Control_JoystickState & JOYSTICK_RIGHT) == JOYSTICK_RIGHT)
					{
						Profil_BasalRate = ;
					}
					if ((Control_JoystickState & JOYSTICK_DOWN) == JOYSTICK_DOWN)
					{
						Profil_BasalRate = ;
					}
					*/
					break;
			}
			break;
		case Elderly:
			switch(Control_ActivityGroup)
			{
				case Inactive:
					Profile_UpdateBaseDisplay(pProfile_BaseDisplay, "Basal Rate", "14 Unit", "21 Units", "28 Units", "34 Units");
					LCD_Options(Profile_BaseDisplay);
					do {
						Control_JoystickState = Joystick_GetState(); 
					} while (!(((Control_JoystickState & JOYSTICK_LEFT) == JOYSTICK_LEFT) || ((Control_JoystickState & JOYSTICK_UP) == JOYSTICK_UP) || 
									((Control_JoystickState & JOYSTICK_RIGHT) == JOYSTICK_RIGHT) || ((Control_JoystickState & JOYSTICK_DOWN) == JOYSTICK_DOWN)));
					/*
					if ((Control_JoystickState & JOYSTICK_LEFT) == JOYSTICK_LEFT)
					{
						Profil_BasalRate = ;
					}
					if ((Control_JoystickState & JOYSTICK_UP) == JOYSTICK_UP)
					{
						Profil_BasalRate = ;
					}
					if ((Control_JoystickState & JOYSTICK_RIGHT) == JOYSTICK_RIGHT)
					{
						Profil_BasalRate = ;
					}
					if ((Control_JoystickState & JOYSTICK_DOWN) == JOYSTICK_DOWN)
					{
						Profil_BasalRate = ;
					}
					*/
					break;
				case Moderate:
					Profile_UpdateBaseDisplay(pProfile_BaseDisplay, "Basal Rate", "10 Unit", "16 Units", "22 Units", "27 Units");
					LCD_Options(Profile_BaseDisplay);
					do {
						Control_JoystickState = Joystick_GetState(); 
					} while (!(((Control_JoystickState & JOYSTICK_LEFT) == JOYSTICK_LEFT) || ((Control_JoystickState & JOYSTICK_UP) == JOYSTICK_UP) || 
									((Control_JoystickState & JOYSTICK_RIGHT) == JOYSTICK_RIGHT) || ((Control_JoystickState & JOYSTICK_DOWN) == JOYSTICK_DOWN)));
					/*
					if ((Control_JoystickState & JOYSTICK_LEFT) == JOYSTICK_LEFT)
					{
						Profil_BasalRate = ;
					}
					if ((Control_JoystickState & JOYSTICK_UP) == JOYSTICK_UP)
					{
						Profil_BasalRate = ;
					}
					if ((Control_JoystickState & JOYSTICK_RIGHT) == JOYSTICK_RIGHT)
					{
						Profil_BasalRate = ;
					}
					if ((Control_JoystickState & JOYSTICK_DOWN) == JOYSTICK_DOWN)
					{
						Profil_BasalRate = ;
					}
					*/
					break;
				case Active:
					Profile_UpdateBaseDisplay(pProfile_BaseDisplay, "Basal Rate", "7 Unit", "11 Units", "15 Units", "20 Units");
					LCD_Options(Profile_BaseDisplay);
					do {
						Control_JoystickState = Joystick_GetState(); 
					} while (!(((Control_JoystickState & JOYSTICK_LEFT) == JOYSTICK_LEFT) || ((Control_JoystickState & JOYSTICK_UP) == JOYSTICK_UP) || 
									((Control_JoystickState & JOYSTICK_RIGHT) == JOYSTICK_RIGHT) || ((Control_JoystickState & JOYSTICK_DOWN) == JOYSTICK_DOWN)));
					/*
					if ((Control_JoystickState & JOYSTICK_LEFT) == JOYSTICK_LEFT)
					{
						Profil_BasalRate = ;
					}
					if ((Control_JoystickState & JOYSTICK_UP) == JOYSTICK_UP)
					{
						Profil_BasalRate = ;
					}
					if ((Control_JoystickState & JOYSTICK_RIGHT) == JOYSTICK_RIGHT)
					{
						Profil_BasalRate = ;
					}
					if ((Control_JoystickState & JOYSTICK_DOWN) == JOYSTICK_DOWN)
					{
						Profil_BasalRate = ;
					}
					*/
					break;
			}
			break;
	}
	GLCD_ClearScreen();
}

void Profile_Bolus(void)
{
	Profile_UpdateBaseDisplay(pProfile_BaseDisplay, "Bolus Amount", "1 Unit", "2 Units", "4 Units", "8 Units");
	LCD_Options(Profile_BaseDisplay);
	do {
		Control_JoystickState = Joystick_GetState(); 
	} while (!(((Control_JoystickState & JOYSTICK_LEFT) == JOYSTICK_LEFT) || ((Control_JoystickState & JOYSTICK_UP) == JOYSTICK_UP) || 
					((Control_JoystickState & JOYSTICK_RIGHT) == JOYSTICK_RIGHT) || ((Control_JoystickState & JOYSTICK_DOWN) == JOYSTICK_DOWN)));
	/*
					if ((Control_JoystickState & JOYSTICK_LEFT) == JOYSTICK_LEFT)
					{
						Profile_BolusSteps = ;
					}
					if ((Control_JoystickState & JOYSTICK_UP) == JOYSTICK_UP)
					{
						Profile_BolusSteps = ;
					}
					if ((Control_JoystickState & JOYSTICK_RIGHT) == JOYSTICK_RIGHT)
					{
						Profile_BolusSteps = ;
					}
					if ((Control_JoystickState & JOYSTICK_DOWN) == JOYSTICK_DOWN)
					{
						Profile_BolusSteps = ;
					}
					*/
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

ProfileOptions* Profile_UpdateProfile(ProfileOptions *temp, BasalRate Basal)
{
	
	
	return temp;
}
