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
 *	Rate of Basal
 *
 *  @param void: void 
 *  @return void: void
 */

void Profile_Initiate(void);

/** Function Profile_RecommendDosage()
 *
 *  Function is called at the end of Profile_Initiate().
 *	Based on the users age group and activity level,
 *	the function displays and has the user select between
 *	four different dosage rates.
 *
 *  @param void: void 
 *  @return void: void
 */

void Profile_RecommendDosage(void);

/** Function Profile_AssignBasalSteps()
 *
 *  Function is called at the end of Profile_RecommendDosage().
 *	Based on the users selection of the recommended Basal Doses
 *	the function converts the dosage rate into steps per day and steps per dose.
 *
 *  @param int: int 
 *  @return void: void
 */

void Profile_AssignBasalSteps(int units);

/** Function Profile_Bolus()
 *
 *  When Bolus is activated, allows user to select amount of
 *	insulin for a Bolus dosage.
 *
 *  @param void: void 
 *  @return void: void
 */

void Profile_Bolus(void);

/** Function Profile_CreateBaseDisplay()
 *
 *  Creates BaseDisplay struct
 *
 *  @param 5 char: 5 char 
 *  @return BaseDisplay: BaseDisplay
 */

BaseDisplay Profile_CreateBaseDisplay(char *cat, char *opt1, char *opt2,
																			char *opt3, char *opt4);

/** Function Profile_UpdateBaseDisplay()
 *
 *  Updates BaseDisplay struct
 *
 *  @param BaseDisplay, 5 char: BaseDisplay, 5 char 
 *  @return BaseDisplay: BaseDisplay
 */

BaseDisplay* Profile_UpdateBaseDisplay(BaseDisplay *temp, char *cat, char *opt1, 
																			char *opt2, char *opt3, char *opt4);

/** Function Profile_CreateProfile()
 *
 *  Creates ProfileOptions struct
 *
 *  @param AGE, ACTIVITY: AGE, ACTIVITY 
 *  @return ProfileOptions: ProfileOptions
 */

ProfileOptions Profile_CreateProfile(AGE AgeRange, ACTIVITY ActivityGroup);

/** Function Profile_UpdateProfile()
 *
 *  Updates ProfileOptions struct
 *
 *  @param ProfileOptions, AGE, ACTIVITY: ProfileOptions, AGE, ACTIVITY 
 *  @return ProfileOptions: ProfileOptions
 */

ProfileOptions* Profile_UpdateProfile(ProfileOptions *temp);

#endif /* PROFILE_PROFILE_H_ */
