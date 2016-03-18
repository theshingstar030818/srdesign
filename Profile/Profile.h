/**
 *  Control.h
 * 
 *  Created on: March 18, 2016
 *      Author: mfeist
 */

#ifndef PROFILE_PROFILE_H_
#define PROFILE_PROFILE_H_

#include "..\Control.h"


void Profile_Initiate(void);

void Profile_Bolus(void);

BaseDisplay Profile_CreateBaseDisplay(char *cat, char *opt1, char *opt2,
																			char *opt3, char *opt4);

BaseDisplay* Profile_UpdateBaseDisplay(BaseDisplay *temp, char *cat, char *opt1, 
																			char *opt2, char *opt3, char *opt4);

ProfileOptions Control_CreateProfile(AGE AgeRange, ACTIVITY ActivityGroup);

ProfileOptions* Control_UpdateProfile(ProfileOptions *temp, BasalRate Basal);

#endif /* PROFILE_PROFILE_H_ */
