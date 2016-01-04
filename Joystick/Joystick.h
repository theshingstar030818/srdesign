/**
 *  Joystick.h
 * 
 *  Created on: Dec 30, 2015
 *      Author: mfeist
 */

#ifndef JOYSTICK_H_
#define JOYSTICK_H_

void Joystick_RetractInitiate(void);

void Joystick_ReplacedSyringeInitiate(void);

void EINT1_IRQHandler(void);

void EINT2_IRQHandler(void);

#endif /* JOYSTICK_H_ */
