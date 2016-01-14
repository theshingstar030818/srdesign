/**
 *  Speaker.h
 *
 *  Created on: Jan 12, 2016
 *      Author: sle
 */
 
#ifndef SPEAKER_SPEAKER_H_
#define SPEAKER_SPEAKER_H_

/** Speaker_Initiate()
 *
 *  Function is called in the main loop to initialize the Speaker pin
 *  Set pins P0.26 as output
 *
 *  @param void: void 
 *  @return void: void
 */
void Speaker_Initiate(void);
 
/** Speaker_Initiate()
 *
 *  Function is called to activate the Speaker
 *	Parameter loops dictates how long the Speaker is on for
 *
 *  @param int: loops - number of loops to play sound
 *  @return void: void
 */
void Speaker_Play(int loops);

/** Speaker_Wait()
 *
 *  Function is called to wait between oscillations
 *
 *  @param void: void
 *  @return void: void
 */
void Speaker_Wait(void);

#endif /* SPEAKER_SPEAKER_H_ */
 
