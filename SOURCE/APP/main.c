/*
 * main.c
 *
 *  Created on: Aug 18, 2026
 *      Author: zom22
 */
// Library Directives
#include "../../INCLUDE/LIB/BIT_MATH.h"
#include "../../INCLUDE/LIB/STD_TYPES.h"

// DIO Directives
#include "../../INCLUDE/MCAL/DIO/DIO_INTERFACE.h"
#include "../../INCLUDE/MCAL/DIO/DIO_PRIVATE.h"
#include "../../INCLUDE/MCAL/DIO/DIO_CFG.h"
//#include <stdio.h>
#include <util/delay.h>

// ADC Directives
#include "../../INCLUDE/MCAL/ADC/ADC_INTERFACE.h"
#include "../../INCLUDE/MCAL/ADC/ADC_PRIVATE.h"
#include "../../INCLUDE/MCAL/ADC/ADC_CFG.h"

u8 APP_u8GetDialValue()
{
	u16 L_u16ADCReading = 0;
	u8 L_u8DialValue = 0;


	L_u16ADCReading = MADC_u16GetChannelReading(ADC_CHANNEL_0);

	// Mapping
	// UL --> Unsigned Long  32-bit
	L_u8DialValue = (u8) (((u32) L_u16ADCReading * 99UL) / 1023UL);

	return L_u8DialValue;
}


int main(void)
{


}

