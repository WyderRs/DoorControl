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

Motor_main_t motor;


float temp; // DELETE!


_Bool Motor_Speed(float sp) {

	motor.motor_encoder.enc_trg			= sp * REDUCTOR_COEF;
	motor.motor_encoder.time_per_trg	= 1.0;

//	motor.pid_reg.Vtg 					= ((float)motor.motor_encoder.enc_trg / motor.motor_encoder.time_per_trg);
//	motor.pid_reg.Vtg					= sp * 5.18;

	motor.pid_reg.Vtg					= REDUCTOR_COEF * sp * 360.0;



	return 0;
}

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
		/* Чистим значение энкодера */
		motor.motor_encoder.enc = 0;
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

	if (motor.side_rot == rp_OPEN) {
		/* Устанавливаем скважность ШИМ */
		htim1.Instance->CCR1 = p;
		htim1.Instance->CCR2 = 0;
	}
	else if (motor.side_rot == rp_CLOSE) {
		/* Устанавливаем скважность ШИМ */
		htim1.Instance->CCR1 = 0;
		htim1.Instance->CCR2 = p;
	}
	else if (motor.side_rot == rp_STOP) {
		/* Устанавливаем скважность ШИМ */
//		htim1.Instance->CCR1 = 0;
//		htim1.Instance->CCR2 = 0;
	}
	motor.duty = p;
}
void Motor_Dir(MoveSide_t sd) {
	motor.side_rot = sd;
}

void Raspash_Init() {

	/* Запускаем таймер быстрого реагирования */
	HAL_TIM_Base_Start_IT(&htim4);
//	HAL_TIM_Base_Start_IT(&htim3);


	motor.pid_reg.Kp = 0.05;


	motor.side_rot = rp_OPEN;


	HAL_NVIC_DisableIRQ(EXTI0_IRQn);
	HAL_Delay(1000);
	Motor_Speed(10);
	Motor_Dir(rp_OPEN);
	htim1.Instance->CCR1 	= 10;
	motor.duty 				= 10;
	Motor_Start();
	HAL_Delay(100);

	HAL_NVIC_EnableIRQ(EXTI0_IRQn);

	while(1)
	{
		LED_IND1_G(1);
		HAL_Delay(100);
		LED_IND2_Y(1);
		HAL_Delay(100);
		LED_IND3_R(1);
		HAL_Delay(100);
	}


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

//			motor.motor_encoder.t2 = motor.speedCounter.cnt;
//			if ((motor.motor_encoder.t2 > motor.motor_encoder.t1) && ((motor.motor_encoder.t2 - motor.motor_encoder.t1) > 60)) {
//				motor.motor_encoder.dt = 10.0 * (motor.motor_encoder.t2 - motor.motor_encoder.t1);
//				motor.motor_encoder.t1 = motor.motor_encoder.t2;
//			}
//			motor.motor_encoder.enc++;


			motor.motor_encoder.t2 = motor.speedCounter.cnt;
			if ((motor.motor_encoder.t2 > motor.motor_encoder.t1) && ((motor.motor_encoder.t2 - motor.motor_encoder.t1) > 60)) {
				motor.motor_encoder.dt = 10.0 * (motor.motor_encoder.t2 - motor.motor_encoder.t1);
				motor.motor_encoder.t1 = motor.motor_encoder.t2;
			}
			motor.motor_encoder.enc++;

			__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0);

			LED_LG_1(1);

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
		if (motor.speedCounter.cnt_sup >= 100) // 10ms / 100
		{
//			if ((motor.motor_encoder.enc > 0) && (motor.motor_encoder.t1 > 0)) {
//				motor.pid_reg.Vcr 				= (1000.0 * 1000.0 * 1.0 / (20.0 * (motor.motor_encoder.dt + 0.0000001)));
//				motor.pid_reg.E_dif 			= motor.pid_reg.Vtg - motor.pid_reg.Vcr;
//				motor.pid_reg.Rp				= motor.pid_reg.Kp * motor.pid_reg.E_dif;
//				temp 							= motor.duty + motor.pid_reg.Rp;
//				if (temp >= 100) temp 			= 100;
//				else if (temp <= 3) temp 		= 3;
//				else  temp 						= temp;
////	//			/* Применяем значение регулирования */
//				Motor_PWM(temp);



			if ((motor.motor_encoder.enc > 0) && (motor.motor_encoder.t1 > 0)) {
				motor.pid_reg.Vcr 				= (motor.motor_encoder.enc * 1000.0 * 1000.0 * 18.0)
						/ (motor.motor_encoder.dt + 0.0000001);
				motor.pid_reg.E_dif 			= motor.pid_reg.Vtg - motor.pid_reg.Vcr;
				motor.pid_reg.Rp				= motor.pid_reg.Kp * motor.pid_reg.E_dif;
				temp 							= motor.duty + motor.pid_reg.Rp;

				if (temp >= 100) temp 			= 100;
				else if (temp <= 3) temp 		= 3;
				else  temp 						= temp;
//	//			/* Применяем значение регулирования */
				Motor_PWM(temp);
				motor.motor_encoder.enc = 0;
			}













//			}
//			/************************************/
		}
//
//		/* Добавляем по 1 каждую 10 us */
		motor.speedCounter.cnt++;
		motor.speedCounter.cnt_sup++;
	}
	else if (htim == &htim3)
	{

	}
}
















