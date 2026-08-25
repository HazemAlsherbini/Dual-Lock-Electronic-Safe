/*
 * APP.SECURITY.h
 *
 *  Created on: Aug 25, 2026
 *      Author: S.A
 */

#ifndef SOURCE_APP_APP_SECURITY_H_
#define SOURCE_APP_APP_SECURITY_H_

#include "../../INCLUDE/LIB/BIT_MATH.h"
#include "../../INCLUDE/LIB/STD_TYPES.h"


#define CORRECT_DIAL_VALUE     45
#define PASSWORD_LENGTH        4

void APP_voidDisplayWelcomeScreen(void);//start of the program
void APP_voidGetPasswordFromUser(u8* A_u8PasswordArray);//read the password from the user
u8 APP_u8GetDialValue();//read the dial value from the user (potentiometer) using ADC
u8 APP_u8VerifyDualLock(u8* Local_pu8EnteredPass, u8 Local_u8DialValue);// check the password and dialvalue
void APP_voidChangePassword(void);// if user wants to change password








#endif /* SOURCE_APP_APP_SECURITY_H_ */
