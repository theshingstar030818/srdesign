/**
 *  Glucometer.c
 *
 *  Created on: Jan 30, 2016
 *      Author: sle
 */
 
#include "..\Control.h"
#include "..\LCD\LCD.h"

static volatile uint16_t Glucometer_Last;
static volatile uint8_t  Glucometer_Done;
 
void Glucometer_Initiate(void)
{
	LPC_SC->PCONP |= (1 << 12) | (1 << 15);

	LPC_PINCON->PINSEL1 &= ~(3 << 14);
	LPC_PINCON->PINSEL1 |= (1 << 14);

	LPC_ADC->ADCR = (1 << 0) | (4 << 8) | (1 << 21);

	LPC_ADC->ADINTEN =  ( 1 <<  8);

	NVIC_EnableIRQ(ADC_IRQn);
}

void Glucometer_StartConversion(void) 
{
	LPC_ADC->ADCR &= ~( 7 << 24);
	LPC_ADC->ADCR |=  ( 1 << 24);
}

int32_t Glucometer_GetADCReading(void)
{
	if (Glucometer_Done)
	{
		Glucometer_Done = 0;
		return Glucometer_Last;
	}
	return -1;
}

int32_t Glucometer_ConversionDone (void)
{
	return (Glucometer_Done ? 0 : -1);
}

void Glucometer_GetReadings(ProfileOptions* current)
{
	int32_t adcVal;
	double phVal;

	Glucometer_StartConversion();
	while(Glucometer_ConversionDone() != 0);

	adcVal = Glucometer_GetADCReading();
	phVal = (-3*adcVal + 7700) / 200.0;

	current->LastADCReading = adcVal;
	current->LastPHReading = phVal;
}

void ADC_IRQHandler(void) 
{
	volatile uint32_t adstat;

	adstat = LPC_ADC->ADSTAT;

	Glucometer_Last = (LPC_ADC->ADGDR >> 4) & 0xFFF;

	Glucometer_Done = 1;
}
