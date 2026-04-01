/*
 * Raspash.c
 *
 *  Created on: Mar 29, 2026
 *      Author: makar
 */

#include "Raspash.h"




extern TIM_HandleTypeDef htim4;






void Raspash_Init() {

	/* Запускаем таймер быстрого реагирования */
	HAL_TIM_Base_Start_IT(&htim4);



	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);

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

	}
}
















