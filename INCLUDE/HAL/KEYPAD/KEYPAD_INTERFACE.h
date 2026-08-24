/*
 * KEYPAD_INTERFACE.h
 *
 *  Created on: Aug 22, 2026
 *      Author: zom22
 */

#ifndef INCLUDE_HAL_KEYPAD_KEYPAD_INTERFACE_H_
#define INCLUDE_HAL_KEYPAD_KEYPAD_INTERFACE_H_

#define KEYPAD_PRESSED 		0
#define KEYPAD_NOT_PRESSED  1


void HKEYPAD_voidInit(void);
u8 HKEYPAD_u8GetPressedKey(void);

#endif /* INCLUDE_HAL_KEYPAD_KEYPAD_INTERFACE_H_ */
