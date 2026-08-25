/*
 * MOTOR_PROGRAM.c
 *
 *  Created on: Aug 24, 2026
 *      Author: zom22
 */

// Library Directives
#include "../../../INCLUDE/LIB/BIT_MATH.h"
#include "../../../INCLUDE/LIB/STD_TYPES.h"

// DIO Directives
#include "../../../INCLUDE/MCAL/DIO/DIO_INTERFACE.h"
#include "../../../INCLUDE/HAL/MOTOR/MOTOR_CFG.h"
#include "../../../INCLUDE/HAL/MOTOR/MOTOR_INTERFACE.h"
#include "../../../INCLUDE/HAL/MOTOR/MOTOR_PRIVATE.h"

void HMOTOR_voidOpenSafe(void)
{
	MDIO_voidSetPinValue(RELAY_PORT,RELAY_PIN,DIO_HIGH);
}

void HMOTOR_voidCloseSafe(void)
{
	MDIO_voidSetPinValue(RELAY_PORT,RELAY_PIN,DIO_LOW);
}
