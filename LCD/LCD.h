 /**
 *  LCD.h
 *
 *  Created on: Dec 16, 2015
 *      Author: sle
 */
 
#ifndef LCD_LCD_H_
#define LCD_LCD_H_

#include "..\Control.h"

/** Function LCD_Initiate()
 *
 *  Initializes LCD screen with Font Size, Background, and
 *  foreground colors then clears out screen.
 *
 *  @param void: void 
 *  @return void: void
 */

void LCD_Initiate(void);

/** Function LCD_UpdateScreenStatus()
 *
 *  Updates the LCD with current status of the controller.
 *
 *  @param void: void 
 *  @return void: void
 */

void LCD_UpdateScreenStatus(void);

/** Function LCD_UpdateScreenState()
 *
 *  Updates the LCD with current state of the controller.
 *
 *  @param void: void 
 *  @return void: void
 */
 
void LCD_UpdateScreenState(void);

/** Function LCD_UpdateScreenInsulin()
 *
 *  Updates the LCD with current insulin percentage.
 *
 *  @param void: void 
 *  @return void: void
 */

void LCD_UpdateScreenInsulin(void);
 
/** Function LCD_DisplayOptions()
 *
 *  Displays the options that are passed in as parameters.
 *
 *  @param BaseDisplay: current 
 *  @return void: void
 */
 
void LCD_DisplayOptions(BaseDisplay current);

/** Function LCD_ClearScreen()
 *
 *  Clears LCD.
 *
 *  @param void: void 
 *  @return void: void
 */
 
void LCD_ClearScreen(void);

/** Function LCD_SetUpCommon()
 *
 *  Updates the LCD with base display for option selection.
 *
 *  @param void: void 
 *  @return void: void
 */

void LCD_SetUpCommon(void);

/** Function LCD_DisplayADC()
 *
 *  Updates the LCD with the last ADC reading.
 *
 *  @param current: ProfileOptions* - structure with ADC reading
 *  @return void: void
 */
 
void LCD_DisplayADC(ProfileOptions* current);

/** Function LCD_InsulinOverDosePrevention()
 *
 *  Updates the LCD with overdose prevention screen.
 *
 *  @param current: STATUS - current status
 *  @return void: void
 */

void LCD_InsulinOverDosePrevention(STATUS current);

#endif /* LCD_LCD_H_ */
