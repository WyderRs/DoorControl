/*
 * Raspash.c
 *
 *  Created on: Mar 29, 2026
 *      Author: makar
 */

#include "Raspash.h"




extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;

_Bool Motor_Start() {

	/* Если показатель скважности ШИМ равен нулю на обоих линиях */
	if ((htim1.Instance->CCR1 == 0) && (htim1.Instance->CCR1 == 0)) {
		/* Имитируем ошибку */
		return 0;
	}
	/* Иначе запускаем двигатель */
	else  {
		/* Запускаем генерацию импульсов */
		HAL_TIM_PWM_Start_IT(&htim1, TIM_CHANNEL_1);
		HAL_TIM_PWM_Start_IT(&htim1, TIM_CHANNEL_2);
	}
	return 1;
}
_Bool Motor_Stop() {
	/* Чистим значение скважности ШИМ */
	htim1.Instance->CCR1 = 0;
	htim1.Instance->CCR2 = 0;
	/* Останавливаем генерацию импульсов */
	HAL_TIM_PWM_Stop_IT(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop_IT(&htim1, TIM_CHANNEL_2);
	return 1;
}
void Motor_PWM(uint32_t p) {
	/* Проверка */
	if (p >= 100) p = 100;

	if (Motor_main.side_rot == rp_OPEN) {
		/* Устанавливаем скважность ШИМ */
		htim1.Instance->CCR1 = p;
		htim1.Instance->CCR2 = 0;
	}
	else if (Motor_main.side_rot == rp_CLOSE) {
		/* Устанавливаем скважность ШИМ */
		htim1.Instance->CCR1 = 0;
		htim1.Instance->CCR2 = p;
	}
	else if (Motor_main.side_rot == rp_STOP) {
		/* Устанавливаем скважность ШИМ */
//		htim1.Instance->CCR1 = 0;
//		htim1.Instance->CCR2 = 0;
	}
	Motor_main.duty = p;
}
void Motor_Dir(MoveSide sd) {
	Motor_main.side_rot = sd;
}

void Raspash_Init() {

	/* Запускаем таймер быстрого реагирования */
	HAL_TIM_Base_Start_IT(&htim4);
//	HAL_TIM_Base_Start_IT(&htim3);


	Motor_main.side_rot = rp_OPEN;

	HAL_Delay(1000);


}
void Raspash_Loop() {

	while(1) {

		/* Светодиоды */
		LED_LG_1(1);
		HAL_Delay(100);
		LED_LG_2(1);
		HAL_Delay(100);
		LED_ERR(1);
		HAL_Delay(100);

		LED_IND1_G(1);
		HAL_Delay(100);
		LED_IND2_Y(1);
		HAL_Delay(100);
		LED_IND3_R(1);
		HAL_Delay(100);

		LED_LG_1(0);
		HAL_Delay(100);
		LED_LG_2(0);
		HAL_Delay(100);
		LED_ERR(0);
		HAL_Delay(100);

		LED_IND1_G(0);
		HAL_Delay(100);
		LED_IND2_Y(0);
		HAL_Delay(100);
		LED_IND3_R(0);
		HAL_Delay(100);

		/* реле */
//		HAL_Delay(1000);
//		SOL_RELEY(1);
//		HAL_Delay(1000);
//		SOL_RELEY(0);


	}

}




void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	/* Сигнал аварии */
	if (GPIO_Pin == GPIO_PIN_6) {


	}
	/* Обработчик энкодера  */
	else if (GPIO_Pin == GPIO_PIN_0) {
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7) == GPIO_PIN_SET) {
//			SpeedCounter.t2 	= SpeedCounter.cnt;
//			SpeedCounter.t1_t2 	= SpeedCounter.t2 - SpeedCounter.t1;
			/* НЕПРАВИЛЬНО РАСЧИТАН, УЧТИ ИМПУЛЬСЫ И ВРЕМЯ МЕЖДУ ИМПУЛЬСАМИ А ТАКЖЕ ПЕРЕВЕДИ ВСЕ В СКОРОСТЬ */
//			PID_Reg.E_dif 		= SpeedCounter.t1_t2;
//			PID_Reg.Rp 			= PID_Reg.Kp * PID_Reg.E_dif;
			/* Применяем значение регулирования */
			Motor_PWM(Motor_main.duty + PID_Reg.Rp);
			/************************************/
			SpeedCounter.t1 	= SpeedCounter.t2;
		}
		else {

		}

	}
	/* Автоматическая пожарная сигнализация 2 */
	else if (GPIO_Pin == GPIO_PIN_10) {


	}
	/* Автоматическая пожарная сигнализация 1 */
	else if (GPIO_Pin == GPIO_PIN_11) {


	}
	/* Автоматическая пожарная сигнализация */
	else if (GPIO_Pin == GPIO_PIN_12) {


	}
	/* Вход ночь / банк */
	else if (GPIO_Pin == GPIO_PIN_13) {


	}
	/* Датчик движения 2 */
	else if (GPIO_Pin == GPIO_PIN_14) {


	}
	/* Датчик движения 1 */
	else if (GPIO_Pin == GPIO_PIN_15) {


	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {

	/* Таймер отвечающий за контроль и изменение параметров и переменных */
	if (htim == &htim4)
	{
		/* Добавляем по 1 каждую 1 мс */
		SpeedCounter.cnt++;
	}
	else if (htim == &htim3)
	{

	}
}
















