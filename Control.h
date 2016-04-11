/**
 *  Control.h
 * 
 *  Created on: Nov 11, 2015
 *      Author: mfeist
 */

#ifndef CONTROL_CONTROL_H_
#define CONTROL_CONTROL_H_

#include "lpc17xx.h"     // Device header

// Steps to exhaust syringe
#define SYRINGE_LENGTH 3750


// Indicator levels for syringe
#define WARNING_20 (SYRINGE_LENGTH * .8)
#define WARNING_10 (SYRINGE_LENGTH * .9)
#define WARNING_05 (SYRINGE_LENGTH * .95)

// Number of options for each profile category
#define NUM_OPTIONS 4
#define NUM_AGE_GROUP 4
#define NUM_ACTIVITY_LEVEL 3

// Number of options for Bolus
#define NUM_BOLUS_OPTIONS 12

// Create enums 
typedef enum {Inactive, Moderate, Active} ACTIVITY;
typedef enum {Child, Adolescent, Adult, Elderly} AGE;
typedef enum {None_Remaining, Basal_Remaining, Bolus_Remaining} REMAINING;
typedef enum {None_State, Administration_State, Empty_State, Full_State} STATE;
typedef enum {None_Status, Basal_Status, Bolus_Status, Backward_Status, Wait_Status} STATUS;
typedef enum {Hz_250 = 40000, Hz_440 = 22727, Hz_500 = 20000, kHz_1 = 10000, kHz_2 = 5000, kHz_4 = 2500} FREQ;

// Structure for LCD base display
typedef struct
{
	char ProfileCategory[25];
	char ProfileOption1[25];
	char ProfileOption2[25];
	char ProfileOption3[25];
	char ProfileOption4[25];
	int Size1, Size2, Size3, Size4;
}BaseDisplay;

// Structure for user profile
typedef struct
{
	AGE Age;
	ACTIVITY Activity;
	
	uint32_t BasalStepsPerDay;
	uint32_t BasalStepsPerDose;
	
	uint32_t BolusSteps;
	
	uint32_t LastADCReading;
	double LastPHReading;
}ProfileOptions;

/** Function Control_LEDInitiate()
 *
 *  Function is called in the main loop to initialize the LED pins.
 *  Set pins P1.28, P1.29, P1.31 as output.
 *  Set pins P2.2, P2.3, P2.4, P2.5, P2.6 as output.
 *
 *  @param void: void 
 *  @return void: void
 */

void Control_LEDInitiate(void);

/** Function Control_LEDClearAdmin()
 *
 *	Clear out LEDs P1.28, P1.29, P1.31, P2.2, P2.3
 *	used as Basal, Bolus, Backward, Empty ann Full indicators.
 *
 *  @param void: void 
 *  @return void: void
 */
 
void Control_LEDClearAdmin(void);

/** Function Control_LEDClearAll()
 *
 *	Clear out all LEDs.
 *
 *  @param void: void 
 *  @return void: void
 */
 
void Control_LEDClearAll(void);

/** Function Control_ClockInitiate()
 *
 *	Function is called in the main loop to initialize clock.
 *	Powers up Timer0/1/2/3 and sets PCLK = CCLK / 4 (0), PCLK = CCLK (1/2/3).
 *
 *	@param void: void 
 *	@return void: void
 */
 
void Control_ClockInitiate(void);

/** Function Control_DosageReset()
 *
 *	Function is called in the main loop and StepperMotor_StepForward to
 *	reset all basal and bolus dosage variables.
 *
 *	@param void: void 
 *	@return void: void
 */
 
void Control_DosageReset(void);

/** Function Control_Debounce()
 *
 *	Function is called when the joystick is used to ensure no mistaken entries.
 *
 *	@param void: void 
 *	@return void: void
 */
 
void Control_Debounce(void);

/** Function Control_InitializeEnums()
 *
 *	Function initializes enumeration lists.
 *
 *	@param void: void 
 *	@return void: void
 */

void Control_InitializeEnums(void);

#endif /* CONTROL_CONTROL_H_ */
