/**
 *  Glucometer.c
 *
 *  Created on: Jan 30, 2016
 *      Author: sle
 */
 
#include "..\Control.h"
 
void Glucometer_Initiate(void)
{
	LPC_PINCON->PINSEL1 &= ~(3 << 14);
	LPC_PINCON->PINSEL1 |= (1 << 14);
	
	LPC_SC->PCONP |= (1 << 12);
	
	LPC_ADC->ADCR = (1 << 0) | (4 << 8) | (1 << 21);
}

uint32_t Glucometer_GetADCReading(void)
{
	uint32_t temp;
	
	LPC_ADC->ADCR |= (1 << 24);
	while((LPC_ADC->ADDR0 & 0x8000) == 0);
	temp = (LPC_ADC->ADDR0 >> 4) & 0xFFF;
	
	return temp;
}

