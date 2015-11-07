/**
 *  BolusDose.h
 *
 *  Created on: Aug 31, 2015
 *      Author: sle
 */

#ifndef BOLUSDOSE_H_
#define BOLUSDOSE_H_ 


/** Function:  BolusDose_DoseInitiate()
 * 
 *  Must be called at the begginging of the main method.
 *  Function is used to set P2.10 (INT0 button) as an input.
 *  The function enables falling edge for P2.10.
 *	The funciton eneables external interrupt 3.
 */
void BolusDose_DoseInitiate(void);

#endif /* BOLUSDOSE_H_ */
