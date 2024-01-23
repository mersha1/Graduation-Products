/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "lwip.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "tcp_echoclient.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim9;

/* USER CODE BEGIN PV */

struct netif gnetif;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM9_Init(void);
static void MX_TIM4_Init(void);
/* USER CODE BEGIN PFP */

void LED_OnOff(int, int);
void User_notification(struct netif *netif);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

//  int Buzzer_flag = 0;

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_TIM9_Init();
  MX_TIM4_Init();
  MX_LWIP_Init();
  /* USER CODE BEGIN 2 */

  LED_OnOff(LED_ALL, 500);
  HAL_TIM_Base_Start(&htim2);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
// HAL_TIM_Base_Start(&htim5);
//  HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_1);
  /*
  HAL_TIM_Base_Start(&htim9);
  HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_2);
  HAL_TIM_Base_Start(&htim4);
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
*/

  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, 1);
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, 1);
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, 0);
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, 1);
  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_13, 1);
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, 0);

  User_notification(&gnetif);
  tcp_echoclient_connect();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  MX_LWIP_Process();

	  if(message_flag==1)
	  {
		  if(mfront == 1)	{
				HAL_GPIO_WritePin(GPIO_LED, LED_ALL, GPIO_PIN_RESET );
				HAL_GPIO_WritePin(GPIO_LED, LED1, GPIO_PIN_SET );
//				HAL_GPIO_TogglePin(GPIO_LED, LED1);
				HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_2);
				HAL_TIM_PWM_Stop(&htim9, TIM_CHANNEL_1);
				HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
				HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
			}
		  else if(mback == 1)	{
				HAL_GPIO_WritePin(GPIO_LED, LED_ALL, GPIO_PIN_RESET );
				HAL_GPIO_WritePin(GPIO_LED, LED2, GPIO_PIN_SET );
//				HAL_GPIO_TogglePin(GPIO_LED, LED2);
				HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_1);
				HAL_TIM_PWM_Stop(&htim9, TIM_CHANNEL_2);
				HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
				HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_4);
			}
		  else if(mleft == 1)	{
				HAL_GPIO_WritePin(GPIO_LED, LED_ALL, GPIO_PIN_RESET );
				HAL_GPIO_WritePin(GPIO_LED, LED3, GPIO_PIN_SET );
//				HAL_GPIO_TogglePin(GPIO_LED, LED3);
				HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_2);
				HAL_TIM_PWM_Stop(&htim9, TIM_CHANNEL_1);
				HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
				HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_4);
			}
		  else if(mright == 1)	{
				HAL_GPIO_WritePin(GPIO_LED, LED_ALL, GPIO_PIN_RESET );
				HAL_GPIO_WritePin(GPIO_LED, LED4, GPIO_PIN_SET );
//				HAL_GPIO_TogglePin(GPIO_LED, LED4);
				HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_1);
				HAL_TIM_PWM_Stop(&htim9, TIM_CHANNEL_2);
				HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
				HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
			}
		  else if(mstop == 1)	{
				HAL_GPIO_WritePin(GPIO_LED, LED_ALL, GPIO_PIN_RESET );
				HAL_GPIO_WritePin(GPIO_LED, LED5, GPIO_PIN_SET );
//				HAL_GPIO_TogglePin(GPIO_LED, LED5);
//			  	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_13, 0);

				HAL_TIM_PWM_Stop(&htim9, TIM_CHANNEL_1);
				HAL_TIM_PWM_Stop(&htim9, TIM_CHANNEL_2);
				HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
				HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_4);
			}


		  message_flag=0;
	  }
	  if(mEmer == 1)	{
			HAL_GPIO_WritePin(GPIO_LED, LED6, GPIO_PIN_SET );
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, 1);
		}
	  else if(mEmer == 0)	{
			HAL_GPIO_WritePin(GPIO_LED, LED6, GPIO_PIN_RESET );
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, 0);

	  }
	  // Stepping Motor On/Off
	  if(mStep_onoff == 1)	{
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
//			mStep=0;
		}
	  else if(mStep_onoff == 0)	{
			HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
//			mStep=1;

	  }
	  // Stepping Motor CCW/CW
	  	  if(mStep_dir == 1)	{
	  		  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, 1);

	  //			mStep=0;
	  		}
	  	  else if(mStep_dir == 0)	{
	  		  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, 0);
	  //			mStep=1;

	  	  }


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 8999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 999;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 499;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 99;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 999;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 499;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */
  HAL_TIM_MspPostInit(&htim4);

}

/**
  * @brief TIM9 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM9_Init(void)
{

  /* USER CODE BEGIN TIM9_Init 0 */

  /* USER CODE END TIM9_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM9_Init 1 */

  /* USER CODE END TIM9_Init 1 */
  htim9.Instance = TIM9;
  htim9.Init.Prescaler = 99;
  htim9.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim9.Init.Period = 999;
  htim9.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim9.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim9) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim9, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim9) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 499;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM9_Init 2 */

  /* USER CODE END TIM9_Init 2 */
  HAL_TIM_MspPostInit(&htim9);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2|GPIO_PIN_7|GPIO_PIN_15|GPIO_PIN_0, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11|GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2
                          |GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pins : PE2 PE7 PE15 PE0 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_7|GPIO_PIN_15|GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : PF13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : PG0 PG1 PG2 PG3 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : PD11 PD0 PD1 PD2
                           PD3 PD4 PD5 PD6
                           PD7 */
  GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2
                          |GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);

  HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void LED_OnOff(int led, int interval)
{
	HAL_GPIO_WritePin(GPIO_LED, led, GPIO_PIN_SET );
	HAL_GPIO_WritePin(GPIO_LED_Nucleo, led, GPIO_PIN_SET );
	HAL_Delay(interval);
	HAL_GPIO_WritePin(GPIO_LED, led, GPIO_PIN_RESET );
	HAL_GPIO_WritePin(GPIO_LED_Nucleo, led, GPIO_PIN_RESET );
}

void User_notification(struct netif *netif)
{
	if (netif_is_up(netif)) {
		HAL_GPIO_WritePin(GPIO_LED, LED7, GPIO_PIN_SET);
	}
	else {
		HAL_GPIO_WritePin(GPIO_LED, LED8, GPIO_PIN_SET);
	}
}
/*
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN)
{*/
/*	TIM_OC_InitTypeDef sConfigOC_PWM = {0} ;
	sConfigOC_PWM.OCMode = TIM_OCMODE_PWM1;
	if ( GPIO_PIN == SW1) sConfigOC_PWM.Pulse = 999;
	else if ( GPIO_PIN == SW2) sConfigOC_PWM.Pulse = 2999;
	else if ( GPIO_PIN == SW3) sConfigOC_PWM.Pulse = 4999;
	else if ( GPIO_PIN == SW4) sConfigOC_PWM.Pulse = 9999;
	HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC_PWM, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);*/


//	int mp = 0;

//	HAL_GPIO_WritePin(GPIOE, led, GPIO_PIN_SET );

/*	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, 1);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, 1);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, 0);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, 1);
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_13, 1);*/

//	HAL_GPIO_

/*	if ( GPIO_PIN == SW1) mp = 999;
	else if ( GPIO_PIN == SW2) mp = 2999;
	else if ( GPIO_PIN == SW3) mp = 4999;
	else if ( GPIO_PIN == SW4) mp = 9999;*/

/*	if ( GPIO_PIN == SW1)
		{
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
//			HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_1);
			HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_1);
			HAL_TIM_PWM_Stop(&htim9, TIM_CHANNEL_2);
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
			HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_4);

		}
	else if ( GPIO_PIN == SW2)
		{
//			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
			HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_2);
			HAL_TIM_PWM_Stop(&htim9, TIM_CHANNEL_1);
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
			HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
		}
	else if ( GPIO_PIN == SW3)
		{
			HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
			HAL_TIM_PWM_Stop(&htim9, TIM_CHANNEL_1);
			HAL_TIM_PWM_Stop(&htim9, TIM_CHANNEL_2);
			HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
			HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_4);
		}
	else if ( GPIO_PIN == SW4)
		{
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
		}

*/

//	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, mp);


//	  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);


//}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
