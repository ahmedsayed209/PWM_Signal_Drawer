/*
 * Main.c
 *
 *  Created on: Mar 11, 2024
 *      Author: Ahmed Sayed
 */

#include "GLcd.h"
#include <util/delay.h>
#include "PWM_Signal_img.h"
#include "icu.h"
#include <avr/io.h>
/*=========================================================================================================
 *
 *                              Global Variables Initilizations
 *
 * ======================================================================================================= */
static uint8   g_edges_count=0;
static uint16 T1_Period_Time=0;
static uint16 T2_Period_Time=0;
static uint16 T3_Period_Time=0;
uint8 Char_Display[]={	0x23, 0x13, 0x08, 0x64, 0x62};
/*=========================================================================================================
 *
 *                                 Call_Back_Function For ICU
 *
 * ======================================================================================================= */
void App_DutyCycle(void)
{
	g_edges_count++;

	if(g_edges_count==1)
	{
		ICU_ClearTimerValue();
		ICU_DetectEdgeType(FALLING);
	}
	else if(g_edges_count==2)
	{
		T1_Period_Time=ICU_ReturnInputCaptureValue();
		ICU_DetectEdgeType(RISING);
	}
	else if (g_edges_count==3)
	{
		T2_Period_Time=ICU_ReturnInputCaptureValue();
		ICU_DetectEdgeType(FALLING);
	}
	else if(g_edges_count==4)
	{
		T3_Period_Time=ICU_ReturnInputCaptureValue();
		ICU_ClearTimerValue();
		ICU_DetectEdgeType(RISING);
	}


}

int main(void)
{	uint32 Duty_cycle=0;
uint16 Period_cycle=0;
uint32 Freq_hz=0;
ICU_Config Icu_Conf ={No_Clock,RISING}; /* ICU INITILIZATION */
GLCD_Init(); /* GraphicaL LCD  iNIT */
GLCD_Clear_Display();
GLCD_displayImage(Signal,0);
SetCallBack(App_DutyCycle);
SREG|=(1<<7);
ICU_init(&Icu_Conf);




for(;;)
{
	if(g_edges_count==4)
	{
		De_Init();
		g_edges_count=0;
		Set_Cursor(0,3);
		GLCD_wString("Duty=",Right_Page);
		Duty_cycle=((float)(T3_Period_Time-T2_Period_Time)/(T3_Period_Time-T1_Period_Time))*(100);
		LCD_IntgerToString(Duty_cycle,Right_Page);
		glcd_writeChar(Char_Display,Right_Page);
		Set_Cursor(0,0);
		GLCD_wString("Tperiod=",Left_Page);
		Period_cycle=((T3_Period_Time-T1_Period_Time)/(1000));
		LCD_IntgerToString(Period_cycle,Left_Page);
		GLCD_wString("ms",Left_Page);
		Set_Cursor(0,6);
		GLCD_wString("Freq=",Left_Page);
		Freq_hz=((float)(10/Period_cycle)*(100));
		LCD_IntgerToString(Freq_hz,Left_Page);
		GLCD_wString("Hz",Left_Page);
	}


}
}
