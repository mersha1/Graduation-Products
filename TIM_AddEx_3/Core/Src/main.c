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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim6;

/* USER CODE BEGIN PV */

int led_period_TIM_3 = 1001, led_period_TIM_6 = 1001;
int cnt_TIM_3 = 0, cnt_TIM_6 = 0;
int dir_TIM_3 = 0, dir_TIM_6 = 0;
int flag_TIM_3 = 0, flag_TIM_6 = 0;
int flag_TIM_3_1 = 0, flag_TIM_3_2 = 0, flag_TIM_3_3 = 0, flag_TIM_3_4 = 0, flag_TIM_3_5 = 0, flag_TIM_3_6 = 0, flag_TIM_3_7 = 0, flag_TIM_3_8 = 0;
int flag_TIM_6_1 = 0, flag_TIM_6_2 = 0, flag_TIM_6_3 = 0, flag_TIM_6_4 = 0, flag_TIM_6_5 = 0, flag_TIM_6_6 = 0, flag_TIM_6_7 = 0, flag_TIM_6_8 = 0;
uint16_t LED_TIM3 = 0x0001, LED_TIM6 = 0x0080;
uint16_t LED_pre_TIM3 = 0x00, LED_cur_TIM3 = 0x00;
uint16_t LED_pre_TIM6 = 0x00, LED_cur_TIM6 = 0x00;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM6_Init(void);
/* USER CODE BEGIN PFP */

void LED_OnOff(int, int);

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

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */

  LED_OnOff(LED_ALL, 500);
  HAL_TIM_Base_Start_IT(&htim2);
  HAL_TIM_Base_Start_IT(&htim3);
  HAL_TIM_Base_Start_IT(&htim6);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {



	  if (flag_TIM_3==1){
//		  LED_cur = LED_TIM3 + LED_TIM6;
		  HAL_GPIO_TogglePin(GPIO_LED, LED_pre_TIM3);
		  HAL_GPIO_TogglePin(GPIO_LED, LED_TIM3);
		  flag_TIM_3 = 0;
		  LED_pre_TIM3 = LED_TIM3;
	  }
	  if (flag_TIM_6==1){
		  HAL_GPIO_TogglePin(GPIO_LED, LED_pre_TIM6);
		  HAL_GPIO_TogglePin(GPIO_LED, LED_TIM6);
		  flag_TIM_6 = 0;
		  LED_pre_TIM6 = LED_TIM6;
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

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 8999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
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
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 8999;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 9;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 8999;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 9;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

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
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pins : PG0 PG1 PG2 PG3 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : PD0 PD1 PD2 PD3
                           PD4 PD5 PD6 PD7 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
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
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if ( htim->Instance == TIM3){
		cnt_TIM_3++;
		if (cnt_TIM_3==led_period_TIM_3){

			if (led_period_TIM_3 >= 1001){
				dir_TIM_3=0;
				led_period_TIM_3 = 801;
			}
			else if (led_period_TIM_3 <= 1){
				dir_TIM_3=1;
				led_period_TIM_3 = 201;
			}

			if ((((flag_TIM_3_1==0)&&(flag_TIM_3_2==0))&&((flag_TIM_3_3==0)&&(flag_TIM_3_4==0)))&&(((flag_TIM_3_5==0)&&(flag_TIM_3_6==0))&&((flag_TIM_3_7==0)&&(flag_TIM_3_8==0)))){
				flag_TIM_3_1 = 1,	flag_TIM_3_2 = 0,	flag_TIM_3_3 = 0,	flag_TIM_3_4 = 0,	flag_TIM_3_5 = 0,	flag_TIM_3_6 = 0,	flag_TIM_3_7 = 0,	flag_TIM_3_8 = 0;
				cnt_TIM_3 = 0;
			}
			else if (flag_TIM_3_1==1){

				flag_TIM_3_1 = 0,	flag_TIM_3_2 = 1,	flag_TIM_3_3 = 0,	flag_TIM_3_4 = 0,	flag_TIM_3_5 = 0,	flag_TIM_3_6 = 0,	flag_TIM_3_7 = 0,	flag_TIM_3_8 = 0;
				cnt_TIM_3 = 0;

			}
			else if (flag_TIM_3_2==1){

				flag_TIM_3_1 = 0,	flag_TIM_3_2 = 0,	flag_TIM_3_3 = 1,	flag_TIM_3_4 = 0,	flag_TIM_3_5 = 0,	flag_TIM_3_6 = 0,	flag_TIM_3_7 = 0,	flag_TIM_3_8 = 0;
				cnt_TIM_3 = 0;

			}
			else if (flag_TIM_3_3==1){

				flag_TIM_3_1 = 0,	flag_TIM_3_2 = 0,	flag_TIM_3_3 = 0,	flag_TIM_3_4 = 1,	flag_TIM_3_5 = 0,	flag_TIM_3_6 = 0,	flag_TIM_3_7 = 0,	flag_TIM_3_8 = 0;
				cnt_TIM_3 = 0;

			}
			else if (flag_TIM_3_4==1){

				flag_TIM_3_1 = 0,	flag_TIM_3_2 = 0,	flag_TIM_3_3 = 0,	flag_TIM_3_4 = 0,	flag_TIM_3_5 = 1,	flag_TIM_3_6 = 0,	flag_TIM_3_7 = 0,	flag_TIM_3_8 = 0;
				cnt_TIM_3 = 0;

			}
			else if (flag_TIM_3_5==1){
				flag_TIM_3_1 = 0,	flag_TIM_3_2 = 0,	flag_TIM_3_3 = 0,	flag_TIM_3_4 = 0,	flag_TIM_3_5 = 0,	flag_TIM_3_6 = 1,	flag_TIM_3_7 = 0,	flag_TIM_3_8 = 0;
				cnt_TIM_3 = 0;

			}
			else if (flag_TIM_3_6==1){

				flag_TIM_3_1 = 0,	flag_TIM_3_2 = 0,	flag_TIM_3_3 = 0,	flag_TIM_3_4 = 0,	flag_TIM_3_5 = 0,	flag_TIM_3_6 = 0,	flag_TIM_3_7 = 1,	flag_TIM_3_8 = 0;
				cnt_TIM_3 = 0;

			}
			else if (flag_TIM_3_7==1){

				flag_TIM_3_1 = 0,	flag_TIM_3_2 = 0,	flag_TIM_3_3 = 0,	flag_TIM_3_4 = 0,	flag_TIM_3_5 = 0,	flag_TIM_3_6 = 0,	flag_TIM_3_7 = 0,	flag_TIM_3_8 = 1;
				cnt_TIM_3 = 0;

			}
			else if (flag_TIM_3_8==1){

				flag_TIM_3_1 = 1,	flag_TIM_3_2 = 0,	flag_TIM_3_3 = 0,	flag_TIM_3_4 = 0,	flag_TIM_3_5 = 0,	flag_TIM_3_6 = 0,	flag_TIM_3_7 = 0,	flag_TIM_3_8 = 0;
				cnt_TIM_3 = 0;
				if (dir_TIM_3 == 0){
					led_period_TIM_3=led_period_TIM_3-100;
				}
				else if (dir_TIM_3 == 1){
					led_period_TIM_3=led_period_TIM_3+100;
				}
			}
/*			if (led_period_TIM_3<=0){
				led_period_TIM_3=1000;
			}*/
		}

		if (flag_TIM_3_1 == 1)	LED_TIM3 = LED1;
		else if (flag_TIM_3_2 == 1)	LED_TIM3 = LED2;
		else if (flag_TIM_3_3 == 1)	LED_TIM3 = LED3;
		else if (flag_TIM_3_4 == 1)	LED_TIM3 = LED4;
		else if (flag_TIM_3_5 == 1)	LED_TIM3 = LED5;
		else if (flag_TIM_3_6 == 1)	LED_TIM3 = LED6;
		else if (flag_TIM_3_7 == 1)	LED_TIM3 = LED7;
		else if (flag_TIM_3_8 == 1)	LED_TIM3 = LED8;

		flag_TIM_3=1;

	}
	if ( htim->Instance == TIM6){
		cnt_TIM_6++;
				if (cnt_TIM_6==led_period_TIM_6){

					if (led_period_TIM_6 >= 1001){
						dir_TIM_6=0;
						led_period_TIM_6 = 801;
					}
					else if (led_period_TIM_6 <= 1){
						dir_TIM_6=1;
						led_period_TIM_6 = 201;
					}

					if ((((flag_TIM_6_1==0)&&(flag_TIM_6_2==0))&&((flag_TIM_6_3==0)&&(flag_TIM_6_4==0)))&&(((flag_TIM_6_5==0)&&(flag_TIM_6_6==0))&&((flag_TIM_6_7==0)&&(flag_TIM_6_8==0)))){


						flag_TIM_6_1 = 0,	flag_TIM_6_2 = 0,	flag_TIM_6_3 = 0,	flag_TIM_6_4 = 0,	flag_TIM_6_5 = 0,	flag_TIM_6_6 = 0,	flag_TIM_6_7 = 0,	flag_TIM_6_8 = 1;
						cnt_TIM_6 = 0;

					}
					else if (flag_TIM_6_8==1){

						flag_TIM_6_1 = 0,	flag_TIM_6_2 = 0,	flag_TIM_6_3 = 0,	flag_TIM_6_4 = 0,	flag_TIM_6_5 = 0,	flag_TIM_6_6 = 0,	flag_TIM_6_7 = 1,	flag_TIM_6_8 = 0;
												cnt_TIM_6 = 0;

					}
					else if (flag_TIM_6_7==1){

						flag_TIM_6_1 = 0,	flag_TIM_6_2 = 0,	flag_TIM_6_3 = 0,	flag_TIM_6_4 = 0,	flag_TIM_6_5 = 0,	flag_TIM_6_6 = 1,	flag_TIM_6_7 = 0,	flag_TIM_6_8 = 0;
												cnt_TIM_6 = 0;

					}
					else if (flag_TIM_6_6==1){

						flag_TIM_6_1 = 0,	flag_TIM_6_2 = 0,	flag_TIM_6_3 = 0,	flag_TIM_6_4 = 0,	flag_TIM_6_5 = 1,	flag_TIM_6_6 = 0,	flag_TIM_6_7 = 0,	flag_TIM_6_8 = 0;
												cnt_TIM_6 = 0;

					}
					else if (flag_TIM_6_5==1){

						flag_TIM_6_1 = 0,	flag_TIM_6_2 = 0,	flag_TIM_6_3 = 0,	flag_TIM_6_4 = 1,	flag_TIM_6_5 = 0,	flag_TIM_6_6 = 0,	flag_TIM_6_7 = 0,	flag_TIM_6_8 = 0;												cnt_TIM_6 = 0;

					}
					else if (flag_TIM_6_4==1){

						flag_TIM_6_1 = 0,	flag_TIM_6_2 = 0,	flag_TIM_6_3 = 1,	flag_TIM_6_4 = 0,	flag_TIM_6_5 = 0,	flag_TIM_6_6 = 0,	flag_TIM_6_7 = 0,	flag_TIM_6_8 = 0;
												cnt_TIM_6 = 0;

					}
					else if (flag_TIM_6_3==1){

						flag_TIM_6_1 = 0,	flag_TIM_6_2 = 1,	flag_TIM_6_3 = 0,	flag_TIM_6_4 = 0,	flag_TIM_6_5 = 0,	flag_TIM_6_6 = 0,	flag_TIM_6_7 = 0,	flag_TIM_6_8 = 0;
												cnt_TIM_6 = 0;

					}
					else if (flag_TIM_6_2==1){

						flag_TIM_6_1 = 1,	flag_TIM_6_2 = 0,	flag_TIM_6_3 = 0,	flag_TIM_6_4 = 0,	flag_TIM_6_5 = 0,	flag_TIM_6_6 = 0,	flag_TIM_6_7 = 0,	flag_TIM_6_8 = 0;
												cnt_TIM_6 = 0;

					}
					else if (flag_TIM_6_1==1){
						flag_TIM_6_1 = 0,	flag_TIM_6_2 = 0,	flag_TIM_6_3 = 0,	flag_TIM_6_4 = 0,	flag_TIM_6_5 = 0,	flag_TIM_6_6 = 0,	flag_TIM_6_7 = 0,	flag_TIM_6_8 = 1;
						cnt_TIM_6 = 0;
						if (dir_TIM_6 == 0){
							led_period_TIM_6=led_period_TIM_6-100;
						}
						else if (dir_TIM_6 == 1){
							led_period_TIM_6=led_period_TIM_6+100;
						}
					}
/*					if (led_period_TIM_6<=0){
						led_period_TIM_6=1000;
					}*/
				}
				if (flag_TIM_6_1 == 1)	LED_TIM6 = LED1;
				else if (flag_TIM_6_2 == 1)	LED_TIM6 = LED2;
				else if (flag_TIM_6_3 == 1)	LED_TIM6 = LED3;
				else if (flag_TIM_6_4 == 1)	LED_TIM6 = LED4;
				else if (flag_TIM_6_5 == 1)	LED_TIM6 = LED5;
				else if (flag_TIM_6_6 == 1)	LED_TIM6 = LED6;
				else if (flag_TIM_6_7 == 1)	LED_TIM6 = LED7;
				else if (flag_TIM_6_8 == 1)	LED_TIM6 = LED8;

				flag_TIM_6=1;
	}


}

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
