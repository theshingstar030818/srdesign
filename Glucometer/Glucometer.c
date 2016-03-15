/**
 *  Glucometer.c
 *
 *  Created on: Jan 30, 2016
 *      Author: sle
 */

#include "Board_ADC.h"
 
void Glucometer_Initiate(void)
{
	ADC_Initialize();
}

uint32_t Glucometer_GetADCReading(void)
{
	return ADC_GetValue();
}

uint32_t Glucometer_GetADCResolution(void)
{
	return ADC_GetResolution();
}

