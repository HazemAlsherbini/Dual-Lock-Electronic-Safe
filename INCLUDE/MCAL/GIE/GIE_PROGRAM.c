/*
 * GIE_PROGRAM.c
 *
 *  Created on: Aug 24, 2026
 *      Author: zom22
 */


// Library Directives
#include "../../../INCLUDE/LIB/BIT_MATH.h"
#include "../../../INCLUDE/LIB/STD_TYPES.h"

// GIE  Directives
#include "../../../INCLUDE/MCAL/DIO/DIO_INTERFACE.h"
#include "../../../INCLUDE/MCAL/GIE/GIE_CFG.h"
#include "../../../INCLUDE/MCAL/GIE/GIE_INTERFACE.h"
#include "../../../INCLUDE/MCAL/GIE/GIE_PRIVATE.h"



void MGIE_voidEnable()
{
	SET_BIT(SREG,GIE_BIT);
}

void MGIE_voidDisable()
{
	CLR_BIT(SREG,GIE_BIT);
}
