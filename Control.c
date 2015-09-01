/*
 * Control.c
 *
 *  Created on: Aug 31, 2015
 *      Author: sle
 */

#include <stdio.h>

#include "./BasalDose/BasalDose.h"
#include "./BosalDose/BosalDose.h"

int main()
{
	while(1)
	{
		printf("%s\n", BasalDose_PrintStatus());
	}
}
