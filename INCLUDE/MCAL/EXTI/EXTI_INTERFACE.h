/*
 * EXTI_INTERFACE.h
 *
 *  Created on: Aug 23, 2026
 *      Author: zom22
 */

#ifndef INCLUDE_MCAL_EXTI_EXTI_INTERFACE_H_
#define INCLUDE_MCAL_EXTI_EXTI_INTERFACE_H_

typedef enum
{
	EXTI0=0,
	EXTI1,
	EXTI2
}EXTI_ID;

typedef enum
{
	LOW_LEVEL=0,
	ON_CAHNGE,
	FALLING_EDGE,
	RISING_EDGE
}EXTI_SENSE_MODE;

void MEXTI_voidEnable(EXTI_ID A_EXTI_ID);
void MEXTI_voidDisable(EXTI_ID A_EXTI_ID);
void MEXTI_voidClearFlag(EXTI_ID A_EXTI_ID);
void MEXTI_voidConfig(EXTI_ID A_EXTI_ID ,EXTI_SENSE_MODE A_EXTI_SENSE_MODE);
void MEXTI_voidsetCallBack(EXTI_ID A_EXTI_ID , void (*PtrToFunc)(void));

void __vector_1(void) __attribute__((signal));
void __vector_2(void) __attribute__((signal));
void __vector_3(void) __attribute__((signal));


#endif /* INCLUDE_MCAL_EXTI_EXTI_INTERFACE_H_ */
