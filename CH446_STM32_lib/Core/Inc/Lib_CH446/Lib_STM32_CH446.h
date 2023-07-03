/*
 * Lib_STM32_CH446.h
 *	Library for Analog matrix switch CH446(https://www.wch-ic.com/products/CH446.html)
 *	Dependencies: stm32fxxx_hal.h
 *  Created on: Jul 2, 2023
 *      Author: Roland Molnar
 */
#ifndef _LIB_STM32_CH446_
#define _LIB_STM32_CH446_

#include <stdint.h>
#include "stm32f4xx_hal.h"

#ifndef HAL_TIM_MODULE_ENABLED
	#define HAL_TIM_MODULE_ENABLED	// Enable HAL timer module
#endif

/*
 * Sellect switch model:
 */
// #define CH446X

#ifndef CH446Q
	#define X_ADDR_MAX 	15
	#define Y_ADDR_MAX	7
#else
	#define X_ADDR_MAX 	23
	#define Y_ADDR_MAX	4
#endif

enum CH446_Status
{
	CH446_OK = 0,
	CH446_Err
};

typedef struct
{
	GPIO_TypeDef* port;
	uint16_t pin;
}ControlPin_TypeDef;

typedef struct
{
	struct ControlPins
	{
		ControlPin_TypeDef RST;
		ControlPin_TypeDef STB;
		ControlPin_TypeDef DAT;
		ControlPin_TypeDef CLK;
		ControlPin_TypeDef CS;
	} ControlPins;
	struct ControlData
	{
		uint8_t data;
		uint8_t bit_index;
	} ControlData;
	TIM_HandleTypeDef* TIM;
} CH446_Handler_TypeDef;

void CH446_Reset( CH446_Handler_TypeDef* handler );
enum CH446_Status CH446_Link( CH446_Handler_TypeDef* handler, uint8_t Y_addr, uint8_t X_addr, uint8_t state );
enum CH446_Status CH446_SetSpeed( CH446_Handler_TypeDef* handler, int16_t kbps );

void CH446_TIM_PeriodElapsed( CH446_Handler_TypeDef* handler );
void CH446_TIM_HalfPeriodElapsed( CH446_Handler_TypeDef* handler );
#endif

