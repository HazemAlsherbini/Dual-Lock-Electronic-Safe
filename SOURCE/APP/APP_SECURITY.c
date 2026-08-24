#include "../../INCLUDE/LIB/BIT_MATH.h"
#include "../../INCLUDE/LIB/STD_TYPES.h"

// DIO Directives
#include "../../INCLUDE/MCAL/DIO/DIO_INTERFACE.h"
#include "../../INCLUDE/MCAL/DIO/DIO_PRIVATE.h"
#include "../../INCLUDE/MCAL/DIO/DIO_CFG.h"
#include "../../INCLUDE/HAL/LCD/LCD_INTERFACE.h"
#include "../../INCLUDE/HAL/LCD/LCD_PRIVATE.h"
#include "../../INCLUDE/HAL/LCD/LCD_CFG.h"

#include <stdio.h>
#include "APP_SECURITY.h"

// correct pass array
static const u8 Correct_Password[4] = {'1', '2', '3', '4'};

// arguments are pointer of the input function and the pass array
u8 APP_u8VerifyDualLock(u8* Local_pu8EnteredPass, u8 Local_u8DialValue) {
	// LET THE enterd pass to be correct at first
    u8 Local_u8PassIsCorrect = 1;
    //A COUNTER
    u8 Local_u8Iterator = 0;

    //the checking loop
    for(Local_u8Iterator = 0; Local_u8Iterator < 4; Local_u8Iterator++) {
        if(Local_pu8EnteredPass[Local_u8Iterator] != Correct_Password[Local_u8Iterator]) {
            Local_u8PassIsCorrect = 0;
            break;
        }
    }

// if the dial and the pass are correct return 1 else 0
    if((Local_u8PassIsCorrect == 1) && (Local_u8DialValue == CORRECT_DIAL_VALUE)) {
        return 1;
    } else {
        return 0;
    }
}

