/**
 *  Control.c
 *
 *  Created on: Aug 31, 2015
 *      Author: sle
 */

#include "Control.h"
#include ".\LCD\LCD.h"
#include ".\BasalDose\BasalDose.h"
#include ".\BolusDose\BolusDose.h"
#include ".\StepperMotor\StepperMotor.h"

status Control_GlobalStatus;

uint32_t i, j; // Used for wait loop in main
uint32_t getStateVal;

int main(void)
{
	SystemInit();
	
	// Set default status to None
	Control_GlobalStatus = None;
	
	// Initialize Clock for Timers
	Control_ClockInitiate();
	
	// Initialize LCD and StepperMotor GPIO
	LCD_Initiate();
	StepperMotor_Initiate();
	
	// Built in LED function replaces what we were using before
	Control_LEDInitiate(); 
	
	// Built in Joystick initialization
	Joystick_Initialize();
	
	// Initialize Timers 0, 1
	BasalDose_TimingInitiate();
	StepperMotor_SpinInitiate();
	
	// Initialize External Interrupt 3
	BolusDose_DoseInitiate();
	
	LPC_TIM0->TCR |= 1 << 0; // Start Counting Timer0
	
	while(1)
	{
		// Clear out the screen, and update
		GLCD_ClearScreen();
		LCD_UpdateScreenStatus();
		LCD_UpdateScreenInsulin();
		switch(Control_GlobalStatus)
		{
			case None:
			case Backward:
			case BackwardBasal:
			case BackwardBolus:
			case BasalComplete:
			case BasalEmptyAfter:
			case BasalEmptyDuring:
			case BolusComplete:
			case BolusEmptyAfter:
			case BolusEmptyDuring:
				// Wait for a short period of time before updating
				for(i = 0; i < 150000; i++)
				{
					for(j = 0; j < 25; j++);
				}
				break;
			case Empty:
				LPC_GPIO2->FIOSET |= 1 << 2; // Signal that syringe is empty P2.2
				BasalDose_TimingDisable();
				do {
					getStateVal = Joystick_GetState(); 
				} while((getStateVal & 0x00000008) != 0x00000008);
				Control_GlobalStatus = Backward;
				Control_LEDClear();
				StepperMotor_SpinEnable();
				break;
			case EmptyBasal:
				LPC_GPIO2->FIOSET |= 1 << 2; // Signal that syringe is empty P2.2
				BasalDose_TimingDisable();
				do {
					getStateVal = Joystick_GetState(); 
				} while((getStateVal & 0x00000008) != 0x00000008);
				Control_GlobalStatus = BackwardBasal;
				Control_LEDClear();
				StepperMotor_SpinEnable();
				break;
			case EmptyBolus:
				LPC_GPIO2->FIOSET |= 1 << 2; // Signal that syringe is empty P2.2
				BasalDose_TimingDisable();
				do {
					getStateVal = Joystick_GetState(); 
				} while((getStateVal & 0x00000008) != 0x00000008);
				Control_GlobalStatus = BackwardBolus;
				Control_LEDClear();
				StepperMotor_SpinEnable();
				break;
			case Full:
				do {
					getStateVal = Joystick_GetState();
				} while((getStateVal & 0x00000010) != 0x00000010);
				BasalDose_TimingEnable();
				Control_GlobalStatus = None;
				Control_LEDClear();
				break;
			case FullBasal:
				do {
					getStateVal = Joystick_GetState();
				} while((getStateVal & 0x00000010) != 0x00000010);
				Control_GlobalStatus = BasalComplete;
				Control_LEDClear();
				break;
			case FullBolus:
				do {
					getStateVal = Joystick_GetState();
				} while((getStateVal & 0x00000010) != 0x00000010);
				Control_GlobalStatus = BolusComplete;
				Control_LEDClear();
				break;
		}
	}
}

void Control_LEDInitiate(void)
{
	// Set pins P1.28, P1.29, P1.31 as output
	LPC_GPIO1->FIODIR |= (0xB0000000);
	LPC_GPIO1->FIOPIN &=~(0xB0000000);
	
	// Set pins P2.2 to p2.6 as output
	LPC_GPIO2->FIODIR |= (0x0000007C);
	LPC_GPIO2->FIOPIN &=~(0x0000007C);
}

void Control_LEDClear(void)
{
	// Clear out LEDs used for Basal, Bolus, and Backward
	LPC_GPIO1->FIOCLR |= 1 << 28; 
 	LPC_GPIO1->FIOCLR |= 1 << 29;
	LPC_GPIO1->FIOCLR |= 1 << 31;
	LPC_GPIO2->FIOCLR |= 1 << 2;
	LPC_GPIO2->FIOCLR |= 1 << 3;
	LPC_GPIO2->FIOCLR |= 1 << 4;
	LPC_GPIO2->FIOCLR |= 1 << 5;
	LPC_GPIO2->FIOCLR |= 1 << 6;
}

void Control_ClockInitiate(void)
{
	// Power up Timer0 and Timer1
	LPC_SC->PCONP |= 1 << 1; 
	LPC_SC->PCONP |= 1 << 2;
	
	// Clock select Timer0 and Timer1 (PCLK = CCLK)
	LPC_SC->PCLKSEL0 |= 1 << 2;
	LPC_SC->PCLKSEL0 |= 1 << 4;
}
