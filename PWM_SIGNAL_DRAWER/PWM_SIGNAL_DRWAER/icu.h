/*
 * icu.h
 *
 *  Created on: Dec 1, 2023
 *      Author: Ahmed Sayed
 */

#ifndef ICU_H_
#define ICU_H_
#include "std_types.h"
typedef enum{
	FALLING,RISING
}ICU_EdgeConfig;

typedef enum{
	No_Clock,CLK_PER_1,CLK_PER_8,CLK_PER_64,CLK_PER_256,CLK_PER_1024_EXTERNAL_RISING_T1,EXTERNAL_FALLING_T1
}ICU_ClkConfig;

typedef struct
{
	ICU_EdgeConfig clock;
	ICU_ClkConfig edge;
}ICU_Config;


void ICU_init(const ICU_Config *Config_type);

void ICU_DetectEdgeType(const ICU_EdgeConfig edge_type);

void ICU_ClockDetectionType(const ICU_ClkConfig clk_type);

void ICU_ClearTimerValue(void);

uint16 ICU_ReturnInputCaptureValue(void);

void SetCallBack(void(*ptr_Arg)(void));

void De_Init(void);
#endif /* ICU_H_ */
