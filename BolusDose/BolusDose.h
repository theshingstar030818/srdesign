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
 *  Must be called at the beginning of the main method.
 *  Function is used to set P2.10 (INT0 button) as an input.
 *  The function enables falling edge for P2.10.
 *	The funciton enables external interrupt 3.
 *  
 *  @param void: void
 *  @return void: void
 */
void BolusDose_DoseInitiate(void);

/** Function: EINT3_IRQHandler()
 *
 *  The function enables external interrupt.
 *  
 *  @param void: void
 *  @return void: void
 */
void EINT3_IRQHandler(void);

#endif /* BOLUSDOSE_H_ */
