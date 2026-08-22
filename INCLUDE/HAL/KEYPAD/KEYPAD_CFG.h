/*
 * KEYPAD_CFG.h
 *
 *  Created on: Aug 22, 2026
 *      Author: zom22
 */

#ifndef INCLUDE_HAL_KEYPAD_KEYPAD_CFG_H_
#define INCLUDE_HAL_KEYPAD_KEYPAD_CFG_H_

#define KEYPAD_PRESSED 		0
#define KEYPAD_NOT_PRESSED  1
#define ROW_NO  4
#define COL_NO  3

u8 Global_u8ArrOfKeyValues [ROW_NO][COL_NO] = {
		{'1','2','3'},
		{'4','5','6'},
		{'7','8','9'},
		{'*','0','#'}
};

#define KEYPAD_PORT    PORTB

#define ROW0 		   PIN0
#define ROW1 		   PIN1
#define ROW2 		   PIN2
#define ROW3 		   PIN3

#define COL0 		   PIN4
#define COL1  		   PIN5
#define COL2   		   PIN6

#define KEYPAD_ROWS   {ROW0,ROW1,ROW2,ROW3}
#define KEYPAD_COLS   {COL0,COL1,COL2}

#define KEYPAD_DEBOUNCE_DELAY 30 //ms

#endif /* INCLUDE_HAL_KEYPAD_KEYPAD_CFG_H_ */
