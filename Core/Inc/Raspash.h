/*
 * Raspash.h
 *
 *  Created on: Mar 29, 2026
 *      Author: makar
 */

#ifndef INC_RASPASH_H_
#define INC_RASPASH_H_


#include "stm32f1xx_hal.h"

/* Передаточное число редуктора */
#define REDUCTOR_COEF			5.18
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
	rp_DISABLE = 0,
	rp_AUTO,
	rp_OPENED,
} Work_Mode;
/* Типы направлений */
typedef enum MoveSide {
	rp_STOP = 0,
	rp_OPEN,
	rp_CLOSE,
} MoveSide_t;
typedef struct Motor_encoder {
	//****************//
	float enc;				// Число импульсов энкодера
	float enc_trg;			// Число импульсов энкодера установленное
	float dt;				// Ширина импульса
	float time_per_trg;		// Ширина импульса заданная

	uint32_t t1;			// Метка времени импульса 1
	uint32_t t2;			// Метка времени импульса 2
} Motor_encoder_t;
typedef struct SpeedCounter {
	uint32_t cnt;			// Счетчик таймера
	uint32_t cnt_sup;		// Вспомогательная переменная

} SpeedCounter_t;
typedef struct PID_Reg {
	/* Регулирование по скорости */
	float Vtg;	/* Скорость вращения установленная */
	float Vcr;	/* Скорость вращения текущая */


	float E_dif;		// Ошибка (разница)

	float Kp;			// Коеф. пропорциональный
	float Ki;			// Коуф. интегральный
	float Kd;			// Коеф. дифференциальный
	/* Значения регуляторов */
	float Rp;
	float Ri;
	float Rd;

} PID_Reg_t;

typedef struct Motor_main {
	MoveSide_t 		side_rot;				/* Текущий тип движения */
	uint32_t 		duty;					/* Текущая скважность */
	Motor_encoder_t motor_encoder;			/* Структура энкодера*/
	PID_Reg_t		pid_reg;				/* Структура PID регулятора*/
	SpeedCounter_t	speedCounter;			/* Структура таймера расчетов*/
} Motor_main_t;








void Raspash_Init();					/* Функция инициализации распашного привода */
void Raspash_Loop();					/* Основной рабочий цикл распашного привода */




















#endif /* INC_RASPASH_H_ */
