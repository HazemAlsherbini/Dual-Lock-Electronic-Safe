#ifndef APP_SECURITY_H_
#define APP_SECURITY_H_

#include "../../INCLUDE/LIB/BIT_MATH.h"
#include "../../INCLUDE/LIB/STD_TYPES.h"

#define CORRECT_DIAL_VALUE    45

u8 APP_u8VerifyDualLock(u8* Local_pu8EnteredPass, u8 Local_u8DialValue);

#endif /* APP_SECURITY_H_ */
