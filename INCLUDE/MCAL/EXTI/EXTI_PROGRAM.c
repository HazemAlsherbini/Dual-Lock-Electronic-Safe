/*
 * EXTI_PROGRAM.c
 *
 *  Created on: Aug 23, 2026
 *      Author: zom22
 */

#include <util/delay.h>

// Library Directives
#include "../../../INCLUDE/LIB/BIT_MATH.h"
#include "../../../INCLUDE/LIB/STD_TYPES.h"

// DIO Directives
#include "../../../INCLUDE/MCAL/DIO/DIO_INTERFACE.h"
#include "../../../INCLUDE/MCAL/EXTI/EXTI_CFG.h"
#include "../../../INCLUDE/MCAL/EXTI/EXTI_INTERFACE.h"
#include "../../../INCLUDE/MCAL/EXTI/EXTI_PRIVATE.h"

void (* EXTI0_Callback)(void) = NULL;
void (* EXTI1_Callback)(void) = NULL;
void (* EXTI2_Callback)(void) = NULL;


void MEXTI_voidEnable(EXTI_ID A_EXTI_ID)
{
	if((A_EXTI_ID <= EXTI2))
	{
		switch(A_EXTI_ID)
		{
		case EXTI0: SET_BIT(GICR,EXTI0_SENSE_MODE_BITS); break;
		case EXTI1: SET_BIT(GICR,EXTI1_SENSE_MODE_BITS); break;
		case EXTI2: SET_BIT(GICR,EXTI2_SENSE_MODE_BITS); break;
		}
	}
}
void MEXTI_voidDisable(EXTI_ID A_EXTI_ID)
{
	if((A_EXTI_ID <= EXTI2))
		{
			switch(A_EXTI_ID)
			{
			case EXTI0: CLR_BIT(GICR,EXTI0_SENSE_MODE_BITS); break;
			case EXTI1: CLR_BIT(GICR,EXTI1_SENSE_MODE_BITS); break;
			case EXTI2: CLR_BIT(GICR,EXTI2_SENSE_MODE_BITS); break;
			}
		}
}

void MEXTI_voidClearFlag(EXTI_ID A_EXTI_ID)
{
	// We clear the flag by setting the flag to 1

	if((A_EXTI_ID <= EXTI2))
		{
			switch(A_EXTI_ID)
			{
			case EXTI0: SET_BIT(GIFR,EXTI0_FLAG_BIT); break;
			case EXTI1: SET_BIT(GIFR,EXTI1_FLAG_BIT); break;
			case EXTI2: SET_BIT(GIFR,EXTI2_FLAG_BIT); break;
			}
		}
}

void MEXTI_voidConfig(EXTI_ID A_EXTI_ID ,EXTI_SENSE_MODE A_EXTI_SENSE_MODE)
{
	if( (A_EXTI_ID <= EXTI2) && (A_EXTI_SENSE_MODE <= RISING_EDGE))
	{
	switch (A_EXTI_ID) {
	case EXTI0:
		MCUCR &= ~(SENSE_MODE_MASK << EXTI0_SENSE_MODE_BITS);
		MCUCR |= (A_EXTI_SENSE_MODE << EXTI0_SENSE_MODE_BITS);
		break;
	case EXTI1:
		MCUCR &= ~(SENSE_MODE_MASK << EXTI1_SENSE_MODE_BITS);
		MCUCR |= (A_EXTI_SENSE_MODE << EXTI1_SENSE_MODE_BITS);
		break;
	case EXTI2:
		switch(A_EXTI_SENSE_MODE)
		{
		case FALLING_EDGE: CLR_BIT(MCUCR,EXTI2_SENSE_MODE_BITS); break;
		case RISING_EDGE: SET_BIT(MCUCR,EXTI2_SENSE_MODE_BITS); break;
		}
		break;
	}
	}
}

void MEXTI_voidsetCallBack(EXTI_ID A_EXTI_ID , void (*PtrToFunc)(void))
{
	if((A_EXTI_ID <= EXTI2)&&(PtrToFunc != NULL))
	{
		switch(A_EXTI_ID)
		{
		case EXTI0:
			EXTI0_Callback = PtrToFunc;
			break;
		case EXTI1:
			EXTI1_Callback = PtrToFunc;
			break;
		case EXTI2:
			EXTI2_Callback = PtrToFunc;
			break;
		}
	}
}


void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{
	if(EXTI0_Callback != NULL)
	{
		EXTI0_Callback();
	}
}

void __vector_2(void) __attribute__((signal));
void __vector_2(void)
{
	if(EXTI1_Callback != NULL)
	{
		EXTI1_Callback();
	}
}

void __vector_3(void) __attribute__((signal));
void __vector_3(void)
{
	if(EXTI2_Callback != NULL)
	{
		EXTI2_Callback();
	}
}
