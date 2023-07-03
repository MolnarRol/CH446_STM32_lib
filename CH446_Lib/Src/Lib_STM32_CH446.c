/*
 * Lib_STM32_CH446.c
 *	Library for Analog matrix switch CH446(https://www.wch-ic.com/products/CH446.html)
 *	Dependencies: stm32fxxx_hal.h
 *  Created on: Jul 2, 2023
 *      Author: Roland Molnar
 */
#include "Lib_STM32_CH446.h"

static inline void CH446_Transmit( CH446_Handler_TypeDef* handler );

void CH446_Reset( CH446_Handler_TypeDef* handler )
{
	HAL_GPIO_WritePin( handler->ControlPins.RST.port, handler->ControlPins.RST.pin, GPIO_PIN_SET );
};

enum CH446_Status CH446_Link( CH446_Handler_TypeDef* handler, uint8_t Y_addr, uint8_t X_addr, uint8_t state )
{
	if( (Y_addr > Y_ADDR_MAX) || (X_addr > X_ADDR_MAX) || (state > 1) ) return CH446_Err;		// Safeguard
	handler->ControlData.data = 0;
	handler->ControlData.bit_index = 7;
	handler->ControlData.data = ( ( Y_addr << 5 ) | ( X_addr << 1 ) ) + state;
	CH446_Transmit( handler );
	return CH446_OK;
};

static inline void CH446_Transmit( CH446_Handler_TypeDef* handler )
{
	HAL_GPIO_WritePin( handler->ControlPins.RST.port, handler->ControlPins.RST.pin, GPIO_PIN_RESET );
	HAL_GPIO_WritePin( handler->ControlPins.CLK.port, handler->ControlPins.CLK.pin, GPIO_PIN_SET );
	HAL_GPIO_WritePin( handler->ControlPins.CS.port, handler->ControlPins.CS.pin, GPIO_PIN_SET );		// Not implemented

	CH446_TIM_PeriodElapsed( handler );

	handler->TIM->Instance->CNT = 0;						// Reset timer to 0
	HAL_TIM_OC_Start_IT( handler->TIM, TIM_CHANNEL_1 );
	HAL_TIM_Base_Start_IT( handler->TIM );
};

void CH446_TIM_PeriodElapsed( CH446_Handler_TypeDef* handler )
{
	if( handler->ControlData.bit_index == 255 )
	{
		HAL_TIM_Base_Stop_IT( handler->TIM );
		HAL_TIM_OC_Stop_IT( handler->TIM, TIM_CHANNEL_1 );
		HAL_GPIO_WritePin( handler->ControlPins.CLK.port, handler->ControlPins.CLK.pin, GPIO_PIN_SET );
		HAL_GPIO_WritePin( handler->ControlPins.STB.port, handler->ControlPins.STB.pin, GPIO_PIN_RESET );
		return;
	}

	HAL_GPIO_WritePin( handler->ControlPins.CLK.port, handler->ControlPins.CLK.pin, GPIO_PIN_SET );
	uint8_t bitMask = 1 << handler->ControlData.bit_index;
	uint8_t dataBit = ( (handler->ControlData.data) & bitMask ) > 0 ? 1 : 0;
	HAL_GPIO_WritePin( handler->ControlPins.DAT.port, handler->ControlPins.DAT.pin, dataBit );
};

void CH446_TIM_HalfPeriodElapsed( CH446_Handler_TypeDef* handler )
{
	HAL_GPIO_WritePin( handler->ControlPins.CLK.port, handler->ControlPins.CLK.pin, GPIO_PIN_RESET );
	if( handler->ControlData.bit_index == 0 )
	{
		HAL_GPIO_WritePin( handler->ControlPins.STB.port, handler->ControlPins.STB.pin, GPIO_PIN_SET );
	}
	handler->ControlData.bit_index--;
};

enum CH446_Status CH446_SetSpeed( CH446_Handler_TypeDef* handler, int16_t bps )
{
	const uint32_t TIM_IN_CLK = HAL_RCC_GetPCLK2Freq();
	const float InDivTarget = TIM_IN_CLK / bps;
	handler->TIM->Instance->PSC = (uint16_t) ( InDivTarget / 65536 );
	handler->TIM->Instance->ARR = (uint16_t) ( InDivTarget / (float) ( handler->TIM->Instance->PSC + 1 ));
	handler->TIM->Instance->CCR1 = handler->TIM->Instance->ARR / 2;
	return CH446_OK;
};
