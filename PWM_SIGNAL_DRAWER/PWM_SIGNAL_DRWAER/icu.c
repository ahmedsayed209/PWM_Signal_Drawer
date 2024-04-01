/*
 * icu.c
 *
 *  Created on: Dec 1, 2023
 *      Author: Ahmed Sayed
 */

#include "icu.h"
#include <avr/io.h>
#include "Gpio.h"
#include "common_macros.h"
#include <avr/interrupt.h>

static volatile void(*g_SETCALLBACKptr)(void)=NULL_PTR;

ISR (TIMER1_CAPT_vect)
{
	(*g_SETCALLBACKptr)();
}


void ICU_init(const ICU_Config *Config_type)
{
	/* To Use Timer1 without PWM Enable This Two Pins */
	TCCR1A = (1<<FOC1A) | (1<<FOC1B);
	/*ICU in AVR Pin Configuration @ PD6 */
	GPIO_setupPinDirection(PORTD_ID,PIN6_ID,PIN_INPUT);
	/* Dynamic Configuration :
	 * Argument of Function -> Is Pointer To Structure
	 * Structure Contain The Data Of Edge Needed From Data Sheet
	 * Also The Clock of timer1 According To Data Sheet
	 *
	 *  */
	TCCR1B=(TCCR1B&0XF8) | (Config_type->edge); /* First Initialization  For Needed Edge @ First */
	TCCR1B=(TCCR1B&0XBF) | ((Config_type->clock)<<6); /* First Initialization  For Needed Clock @ First */
	TCNT1=0; /* Initialize  The Register of Timer1 @ First by Zerog5 */
	ICR1=0;
	SET_BIT(TIMSK,TICIE1);

}
void ICU_DetectEdgeType(const ICU_EdgeConfig edge_type)
{
	TCCR1B=(TCCR1B&0XBF) | ((edge_type)<<6);
}
void ICU_ClockDetectionType(const ICU_ClkConfig clk_type)
{
	TCCR1B=(TCCR1B&0XBF) | (clk_type);
}

void ICU_ClearTimerValue(void)
{
	TCNT1=0;
}
uint16 ICU_ReturnInputCaptureValue(void)
{
	return ICR1;
}

void SetCallBack(void(*ptr_Arg)(void))
{
	g_SETCALLBACKptr=ptr_Arg;
}
void De_Init(void)
{
	TCNT1=0;
	ICR1=0;
	TCCR1A=0;
	TCCR1B=0;
	CLEAR_BIT(TIMSK,TICIE1);

}
