/*
 * Raspash.h
 *
 *  Created on: Mar 29, 2026
 *      Author: makar
 */

#ifndef INC_RASPASH_H_
#define INC_RASPASH_H_


#include "stm32f1xx_hal.h"

/* Светодиоды отладки */
#define LED_LG_1(X)				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, X)
#define LED_LG_2(X)				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, X)
#define LED_ERR(X)				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, X)
/* Светодиоды рабочие */
#define LED_IND1_G(X)			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, X)
#define LED_IND2_Y(X)			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, X)
#define LED_IND3_R(X)			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, X)
/* Реле соленоида для разблокировки / блокировки двери */
#define SOL_RELEY(X)			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, X)

/* Режимы работы привода */
enum {
	rp_DISABLE,
	rp_AUTO,
	rp_OPENED,
} Work_Mode;











void Raspash_Init();					/* Функция инициализации распашного привода */
void Raspash_Loop();					/* Основной рабочий цикл распашного привода */




















#endif /* INC_RASPASH_H_ */
