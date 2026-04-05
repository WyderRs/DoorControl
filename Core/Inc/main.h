/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DB_LG_1_Pin GPIO_PIN_13
#define DB_LG_1_GPIO_Port GPIOC
#define ERR_LED_Pin GPIO_PIN_14
#define ERR_LED_GPIO_Port GPIOC
#define DB_LG_2_Pin GPIO_PIN_15
#define DB_LG_2_GPIO_Port GPIOC
#define GREEN_IND1_Pin GPIO_PIN_2
#define GREEN_IND1_GPIO_Port GPIOA
#define YELLOW_IND2_Pin GPIO_PIN_3
#define YELLOW_IND2_GPIO_Port GPIOA
#define RED_IND3_Pin GPIO_PIN_4
#define RED_IND3_GPIO_Port GPIOA
#define RELEY_KEY_Pin GPIO_PIN_5
#define RELEY_KEY_GPIO_Port GPIOA
#define AVARY_ALARM_Pin GPIO_PIN_6
#define AVARY_ALARM_GPIO_Port GPIOA
#define AVARY_ALARM_EXTI_IRQn EXTI9_5_IRQn
#define MOTOR_ENC_2_Pin GPIO_PIN_7
#define MOTOR_ENC_2_GPIO_Port GPIOA
#define MOTOR_ENC_1_Pin GPIO_PIN_0
#define MOTOR_ENC_1_GPIO_Port GPIOB
#define MOTOR_ENC_1_EXTI_IRQn EXTI0_IRQn
#define MODE_1_Pin GPIO_PIN_1
#define MODE_1_GPIO_Port GPIOB
#define MODE_2_Pin GPIO_PIN_2
#define MODE_2_GPIO_Port GPIOB
#define INPUT_APS2_Pin GPIO_PIN_10
#define INPUT_APS2_GPIO_Port GPIOB
#define INPUT_APS2_EXTI_IRQn EXTI15_10_IRQn
#define INPUT_APS1_Pin GPIO_PIN_11
#define INPUT_APS1_GPIO_Port GPIOB
#define INPUT_APS1_EXTI_IRQn EXTI15_10_IRQn
#define INPUT_APS_Pin GPIO_PIN_12
#define INPUT_APS_GPIO_Port GPIOB
#define INPUT_APS_EXTI_IRQn EXTI15_10_IRQn
#define INPUT_NIGHT_BANK_Pin GPIO_PIN_13
#define INPUT_NIGHT_BANK_GPIO_Port GPIOB
#define INPUT_NIGHT_BANK_EXTI_IRQn EXTI15_10_IRQn
#define INPUT_POS2_Pin GPIO_PIN_14
#define INPUT_POS2_GPIO_Port GPIOB
#define INPUT_POS2_EXTI_IRQn EXTI15_10_IRQn
#define INPUT_POS1_Pin GPIO_PIN_15
#define INPUT_POS1_GPIO_Port GPIOB
#define INPUT_POS1_EXTI_IRQn EXTI15_10_IRQn

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
