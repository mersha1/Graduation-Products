/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

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

/* USER CODE BEGIN Private defines */

// -- Definition ver2.0 -- //

#define DEST_IP_ADDR0 192
#define DEST_IP_ADDR1 168
#define DEST_IP_ADDR2 30
#define DEST_IP_ADDR3 41
#define DEST_PORT 7000

#define GPIO_LED GPIOD
#define LED1 GPIO_PIN_0
#define LED2 GPIO_PIN_1
#define LED3 GPIO_PIN_2
#define LED4 GPIO_PIN_3
#define LED5 GPIO_PIN_4
#define LED6 GPIO_PIN_5
#define LED7 GPIO_PIN_6
#define LED8 GPIO_PIN_7
#define LED_ALL GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7
#define GPIO_LED_Nucleo GPIOB
#define LED1_Nucelo GPIO_PIN_0
#define LED2_Nucleo GPIO_PIN_7
#define GPIO_SW GPIOG
#define SW1 GPIO_PIN_0
#define SW2 GPIO_PIN_1
#define SW3 GPIO_PIN_2
#define SW4 GPIO_PIN_3
#define GPIO_SW_Nucleo GPIOC
#define SW_Nucleo GPIO_PIN_13
/*
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim9;
*/
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
