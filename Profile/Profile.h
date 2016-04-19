/**
 *  Profile.h
 * 
 *  Created on: March 18, 2016
 *      Author: mfeist
 */

#ifndef PROFILE_PROFILE_H_
#define PROFILE_PROFILE_H_

#include "..\Control.h"

/** Function Profile_Initiate()
 *
 *  Initializes Profile to set the Age Group, Activity Level, and
 *  Rate of Basal
 *
 *  @param void: void 
 *  @return void: void
 */

void Profile_Initiate(void);

/** Function Profile_RecommendDosage()
 *
 *  Function is called at the end of Profile_Initiate().
 *  Based on the users age group and activity level,
 *  the function displays and has the user select between
 *  four different dosage rates.
 *
 *  @param void: void 
 *  @return void: void
 */

void Profile_RecommendDosage(void);

/** Function Profile_AssignBasalSteps()
 *
 *  Function is called at the end of Profile_RecommendDosage().
 *  Based on the users selection of the recommended Basal Doses
 *  the function converts the dosage rate into steps per day and steps per dose.
 *
 *  @param int: units 
 *  @return void: void
 */

void Profile_AssignBasalSteps(int units);

/** Function Profile_FillBolusSteps()
 *
 *  Function calculates the desired Bolus units into steps.
 *
 *  @param void: void 
 *  @return void: void
 */
 
void Profile_FillBolusSteps(void);

/** Function Profile_DisplayBolusOptions()
 *
 *  When Bolus is activated, allows user to select amount of
 *  insulin for a Bolus dosage.
 *
 *  @param void: void 
 *  @return void: void
 */

void Profile_DisplayBolusOptions(void);

/** Function Profile_BasalDuringBolus()
 *
 *  Function is called when a Basal occurs during a Bolus.
 *  Function subtracts the number of Basal injecttions from
 *  the StepperMotor_CurrentBolusDose.
 *
 *  @param void: void 
 *  @return void: void
 */

void Profile_BasalDuringBolus(void);

/** Function Profile_CreateBaseDisplay()
 *
 *  Creates BaseDisplay struct.
 *
 *  @param char*, char*, char*, char*, char*: cat, opt1, opt2, opt3, opt4
 *  @return BaseDisplay: temp
 */

BaseDisplay Profile_CreateBaseDisplay(char *cat, char *opt1, char *opt2,
																			char *opt3, char *opt4);

/** Function Profile_UpdateBaseDisplay()
 *
 *  Updates BaseDisplay struct.
 *
 *  @param BaseDisplay*, char*, char*, char*, char*, char*: temp, cat, opt1, opt2, opt3, opt4
 *  @return void: void
 */

void Profile_UpdateBaseDisplay(BaseDisplay *temp, char *cat, char *opt1, 
																			char *opt2, char *opt3, char *opt4);

/** Function Profile_CreateProfile()
 *
 *  Creates ProfileOptions struct.
 *
 *  @param AGE, ACTIVITY: AgeRange, ActivityGroup 
 *  @return ProfileOptions: temp
 */

ProfileOptions Profile_CreateProfile(AGE AgeRange, ACTIVITY ActivityGroup);

#endif /* PROFILE_PROFILE_H_ */
