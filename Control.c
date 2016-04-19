/**
 *  Control.c
 *
 *  Created on: Aug 31, 2015
 *      Author: sle
 */

#include <string.h>
#include <stdbool.h>
#include "Control.h"
#include ".\LCD\LCD.h"
#include "Board_Joystick.h"
#include ".\Speaker\Speaker.h"
#include ".\Profile\Profile.h"
#include ".\BasalDose\BasalDose.h"
#include ".\BolusDose\BolusDose.h"
#include ".\Glucometer\Glucometer.h"
#include ".\InsulinQueue\InsulinQueue.h"
#include ".\StepperMotor\StepperMotor.h"

extern uint32_t StepperMotor_CurrentBasalDose;
extern uint32_t StepperMotor_CurrentBolusDose;

extern uint32_t *pInsulinQueue_Queue;
extern uint32_t InsulinQueue_CurrentEntryCount;
extern uint32_t InsulinQueue_Queue[INSULIN_QUEUE_SIZE];

extern ProfileOptions Profile_CurrentOptions;

STATUS Control_GlobalStatus;
STATE Control_GlobalState;
REMAINING Control_GlobalRemaining;

uint32_t Control_JoystickState;
uint32_t Control_JoystickStateDebounce;

bool Control_ShowBolusScreen;

int main(void)
{
	uint32_t i;
	
	// Initialize System
	SystemInit();
	
	// Initialize Enums
	Control_InitializeEnums();
	
	// Initialize Clock for Timers
	Control_ClockInitiate();
	
	// Initialize LCD and StepperMotor GPIO
	LCD_Initiate();
	StepperMotor_Initiate();
	
	// Built in Joystick initialization
	Joystick_Initialize();
	
	// Initialize ADC for glucometer
	Glucometer_Initiate();
	
	// Initialize LEDs for indication of current dosage
	Control_LEDInitiate();
	
	// Initialize Speaker
	Speaker_Initiate();
	
	// Initialize Timers 0, 1
	BasalDose_TimingInitiate();
	StepperMotor_SpinInitiate();
	
	// Initialize Timer2 and set up pointer to InsulinQueue array
	pInsulinQueue_Queue = InsulinQueue_Queue;
	InsulinQueue_Initiate();
	
	// Initialize External Interrupt 3
	BolusDose_DoseInitiate();
	
	// Initialize User-Profile
	Profile_Initiate();
	
	LPC_TIM0->TCR |= 1 << 0; // Start Counting Timer0

	while(1)
	{
		if(Control_ShowBolusScreen)
		{
			Control_ShowBolusScreen = false;
			BolusDose_AdministerBolus();
		}
		// Clear out the screen, and update
		LCD_ClearScreen();
		LCD_UpdateScreenStatus();
		LCD_UpdateScreenState();
		LCD_UpdateScreenInsulin();
		LCD_DisplayADC(&Profile_CurrentOptions);
		switch(Control_GlobalState)
		{
			case None_State:
			case Administration_State:
				// Wait for a short period of time before updating
				for(i = 0; i < 15000000; i++);
				break;
			case Empty_State:
				BasalDose_TimingDisable();
				LPC_GPIO2->FIOSET |= 1 << 2; // Signal that syringe is empty P2.2
				do{
					Control_JoystickState = Joystick_GetState(); 
				}while(Control_JoystickState != JOYSTICK_UP);
				Speaker_Stop();
				Control_GlobalStatus = Backward_Status;
				Control_GlobalState = Administration_State;
				Control_LEDClearAdmin();
				StepperMotor_SpinEnable();
				break;
			case Full_State:
				BasalDose_TimingDisable();
				LPC_GPIO2->FIOSET |= 1 << 3; // Signal that syringe can be replaced P2.3
				do{
					Control_JoystickState = Joystick_GetState();
				}while(Control_JoystickState != JOYSTICK_DOWN);
				Control_LEDClearAll();
				BasalDose_TimingEnable();
				switch(Control_GlobalRemaining)
				{
					case None_Remaining:
						StepperMotor_SpinDisable();
						Control_DosageReset();
						break;
					case Basal_Remaining:
						Control_GlobalStatus = Basal_Status;
						Control_GlobalState = Administration_State;
						break;
					case Bolus_Remaining:
						Control_GlobalStatus = Bolus_Status;
						Control_GlobalState = Administration_State;
						break;
				}
				break;
		}
	}
}

void Control_LEDInitiate(void)
{
	// Set pins P1.28, P1.29, P1.31 as output
	LPC_GPIO1->FIODIR |= (0xB0000000);
	LPC_GPIO1->FIOPIN &=~(0xB0000000);
	
	// Set pins P2.2, P2.3, P2.4, P2.5, P2.6 as output
	LPC_GPIO2->FIODIR |= (0x0000007C);
	LPC_GPIO2->FIOPIN &=~(0x0000007C);
}

void Control_LEDClearAdmin(void)
{
	// Clear out LEDs used for Basal, Bolus, and Backward
	LPC_GPIO1->FIOCLR |= 1 << 28; 
 	LPC_GPIO1->FIOCLR |= 1 << 29;
	LPC_GPIO1->FIOCLR |= 1 << 31;
	LPC_GPIO2->FIOCLR |= 1 << 2;
	LPC_GPIO2->FIOCLR |= 1 << 3;
}

void Control_LEDClearAll(void)
{
	Control_LEDClearAdmin();
	LPC_GPIO2->FIOCLR |= 1 << 4;
	LPC_GPIO2->FIOCLR |= 1 << 5;
	LPC_GPIO2->FIOCLR |= 1 << 6;
}

void Control_ClockInitiate(void)
{
	// Power up Timer0, Timer1, Timer2, and Timer3
	LPC_SC->PCONP |= 1 << 1; 
	LPC_SC->PCONP |= 1 << 2;
	LPC_SC->PCONP |= 1 << 22;
	LPC_SC->PCONP |= 1 << 23;
	
	// Clock select Timer0, Timer1, and Timer2 (PCLK = CCLK)
	//LPC_SC->PCLKSEL0 |= 1 << 2;
	LPC_SC->PCLKSEL0 |= 1 << 4;
	LPC_SC->PCLKSEL1 |= 1 << 12;
	//LPC_SC->PCLKSEL1 |= 1 << 14;
}

void Control_DosageReset(void)
{
	Control_GlobalStatus = None_Status;
	Control_GlobalState = None_State;
	StepperMotor_CurrentBasalDose = 0;
	StepperMotor_CurrentBolusDose = 0;
}

void Control_Debounce(void)
{
	int i;
	do{
		Control_JoystickState = Joystick_GetState();
		for(i = 0; i < 2000000; i++);
		Control_JoystickStateDebounce = Joystick_GetState();
	}while(Control_JoystickState != Control_JoystickStateDebounce);
}

void Control_InitializeEnums(void)
{
	// Set default status to None
	Control_GlobalStatus = None_Status;
	
	// Set default state to None
	Control_GlobalState = None_State;
	
	// Set default remaining to None
	Control_GlobalRemaining = None_Remaining;
}
