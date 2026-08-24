/*
 * ADC_PROGRAM.c
 *
 *  Created on: Aug 24, 2026
 *      Author: zom22
 */


#include "../../INCLUDE/LIB/STD_TYPES.h"
#include "../../INCLUDE/LIB/BIT_MATH.h"

// ADC Directives
#include "../../INCLUDE/MCAL/ADC/ADC_CFG.h"
#include "../../INCLUDE/MCAL/ADC/ADC_INTERFACE.h"
#include "../../INCLUDE/MCAL/ADC/ADC_PRIVATE.h"

void MADC_voidInit(void)
{

	//1.Voltage Reference Selection
	switch(ADC_VREF)
	{
	case ADC_AREF:
		CLR_BIT(ADMUX_REG, 6);
		CLR_BIT(ADMUX_REG, 7);
		break;
	case ADC_AVCC:
		SET_BIT(ADMUX_REG, 6);
		CLR_BIT(ADMUX_REG, 7);
		break;
	case ADC_RESERVED:
		CLR_BIT(ADMUX_REG, 6);
		SET_BIT(ADMUX_REG, 7);
			break;
	case ADC_INTERNAL:
		SET_BIT(ADMUX_REG, 6);
		SET_BIT(ADMUX_REG, 7);
			break;
	}

	// 2.Right Adjust Result: ADLAR = 0
	CLR_BIT(ADMUX_REG, 5);


	// 3. Enable ADC: ADEN = 1
	SET_BIT(ADCSRA_REG, 7);


	// 4.Disable Interrupt and auto trigger for now
	CLR_BIT(ADCSRA_REG, 3);
	CLR_BIT(ADCSRA_REG, 5);

	// 5.Set Prescaler
    ADCSRA_REG &= 0xF8;
    ADCSRA_REG |= ADC_PRESCALER;
}

u16 MADC_u16GetChannelReading(u8 A_u8Channel)
{
	// Set 0 to Bits 0-->4 : To clear the ADMUX from the current channel
	ADMUX_REG &= 0b11100000;

	// Combine the new channel
	ADMUX_REG |= (A_u8Channel & 0b00011111);

	// Start reading/Conversation
	SET_BIT(ADCSRA_REG, 6);

	while (GET_BIT(ADCSRA_REG, 4) == 0) {
		// Wait until the register finish reading
	}

	// Clear the ADIF bit - To delete the last reading
	// We set the flag to 1
	SET_BIT(ADCSRA_REG, 4);

	return ADC_DATA_REG;
}
