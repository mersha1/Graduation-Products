/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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

#define TxBufferSize	(countof(TxBuffer) - 1)
#define RxBufferSize	0xFF
#define countof(a)		(sizeof(a) / sizeof(*(a)))

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

uint8_t TxBuffer[] = "\n\rUART Example 1 (Transmission Success !! )\n\r\n\r";
uint8_t RxBuffer[RxBufferSize];




int m1_hall=0, m2_hall=0;

int m1_rev=0, m2_rev=0;
int m1_deg=0, m2_deg=0;
int m1_deg_10=0, m2_deg_10=0;
int m1_deg_1_10=0, m2_deg_1_10=0;
//float m1_deg=0, m2_deg=0;
//float m1_deg_10=0, m2_deg_10=0;
//float m1_deg_1_10=0, m2_deg_1_10=0;
int m1_rpm=0, m2_rpm=0;
int m1_rpm_p=0, m2_rpm_p=0;
int m1_rpm_p_10=0, m2_rpm_p_10=0;




int count_sec = 0;


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM4_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM1_Init(void);
/* USER CODE BEGIN PFP */

void LED_OnOff(int, int);

/* Usart printf() */
#ifdef __cplusplus
extern "C" int _write(int32_t file, uint8_t *ptr, int32_t len) {
#else
int _write(int32_t file, uint8_t *ptr, int32_t len) {
#endif
	if( HAL_UART_Transmit(&huart3, ptr, len, len) == HAL_OK ) return len;
	else return 0;
}

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
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_USART3_UART_Init();
  MX_TIM2_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */

//  LED_OnOff(LED_ALL, 500);
  HAL_TIM_Base_Start_IT(&htim1);

  HAL_TIM_Base_Start_IT(&htim3);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  HAL_TIM_Base_Start_IT(&htim4);
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);

  HAL_TIM_Base_Start_IT(&htim2);
  HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);

  HAL_UART_Transmit(&huart3, (uint8_t*)TxBuffer, TxBufferSize , 0xFFFF);

  /*
  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_12, RESET);	// Motor1 DIR - CCW
  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_13, RESET);	// Motor1 RUN/BRK - RUN
  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_14, RESET);	// Motor1 START/STOP - START

  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_2, RESET);	// Motor2 DIR - CCW
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, RESET);	// Motor2 RUN/BRK - RUN
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, RESET);	// Motor2 START/STOP - START

*/
/* Init Settings */
/*	  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_12, SET);	// Motor1 DIR - CW
	  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_13, SET);	// Motor1 RUN/BRK - BRK
	  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_14, SET);	// Motor1 START/STOP - STOP

	  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_2, SET);	// Motor2 DIR - CW
	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, SET);	// Motor2 RUN/BRK - BRK
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, SET);	// Motor2 START/STOP - STOP*/

/* First movement */
/*	  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_13, RESET);	// Motor1 RUN/BRK - RUN
  	  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_14, RESET);	// Motor1 START/STOP - START
  	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, RESET);	// Motor2 RUN/BRK - RUN
  	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, RESET);	// Motor2 START/STOP - START

  	  HAL_Delay(5000);

  	  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_13, SET);	// Motor1 RUN/BRK - BRK
  	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, SET);	// Motor2 RUN/BRK - BRK

  	  HAL_Delay(5000);

  	  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_13, RESET);	// Motor1 RUN/BRK - RUN
  	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, RESET);	// Motor2 RUN/BRK - RUN

  	  HAL_Delay(5000);

  	  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_14, SET);	// Motor1 START/STOP - STOP
  	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, SET);	// Motor2 START/STOP - STOP

  	  HAL_Delay(5000);*/

 /* Second movement */
/*	  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_12, RESET);	// Motor1 DIR - CCW
	  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_2, RESET);	// Motor2 DIR - CCW
	  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_13, RESET);	// Motor1 RUN/BRK - RUN
	  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_14, RESET);	// Motor1 START/STOP - START
	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, RESET);	// Motor2 RUN/BRK - RUN
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, RESET);	// Motor2 START/STOP - START

	  HAL_Delay(5000);

	  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_13, SET);	// Motor1 RUN/BRK - BRK
	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, SET);	// Motor2 RUN/BRK - BRK

	  HAL_Delay(5000);

	  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_13, RESET);	// Motor1 RUN/BRK - RUN
	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, RESET);	// Motor2 RUN/BRK - RUN

	  HAL_Delay(5000);

	  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_14, SET);	// Motor1 START/STOP - STOP
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, SET);	// Motor2 START/STOP - STOP

	  HAL_Delay(5000);*/



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  /*
	  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_13, RESET);	// Motor1 RUN/BRK - RUN
	  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_14, RESET);	// Motor1 START/STOP - START
	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, RESET);	// Motor2 RUN/BRK - RUN
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, RESET);	// Motor2 START/STOP - START

	  HAL_Delay(5000);

	  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_13, SET);	// Motor1 RUN/BRK - BRK
	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, SET);	// Motor2 RUN/BRK - BRK

	  HAL_Delay(5000);

	  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_13, RESET);	// Motor1 RUN/BRK - RUN
	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, RESET);	// Motor2 RUN/BRK - RUN

	  HAL_Delay(5000);

	  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_14, SET);	// Motor1 START/STOP - STOP
	  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, SET);	// Motor2 START/STOP - STOP

	  HAL_Delay(5000);

	*/














/*	  printf("Degree: %d \n", m1_deg);
	  printf("Revolutions: %d \n", m1_rev);
	  printf("Revolutions per Minute: %d \n", m1_rpm);
	  printf("\n");*/

	  printf("Hall: %d \n", m1_hall);
	  printf("Degree: %d.%d \n", m1_deg, m1_deg_1_10);
	  printf("Revolutions: %d \n", m1_rev);
	  printf("Revolutions per Minute: %d \n", m1_rpm);
	  printf("\n");


	  HAL_Delay(1000);

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
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 8999;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 9999;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

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

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 9;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 100;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_IC_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
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
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 89;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 99;
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
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 3;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

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
  htim4.Init.Prescaler = 89;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 99;
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
  sConfigOC.Pulse = 3;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */
  HAL_TIM_MspPostInit(&htim4);

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

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
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_2|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin : PE3 */
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PF2 PF12 PF13 PF14 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pin : PD7 */
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
/*
void LED_OnOff(int led, int interval)
{
	HAL_GPIO_WritePin(GPIO_LED, led, GPIO_PIN_SET );
	HAL_GPIO_WritePin(GPIO_LED_Nucleo, led, GPIO_PIN_SET );
	HAL_Delay(interval);
	HAL_GPIO_WritePin(GPIO_LED, led, GPIO_PIN_RESET );
	HAL_GPIO_WritePin(GPIO_LED_Nucleo, led, GPIO_PIN_RESET );
}*/
/*
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	HAL_GPIO_TogglePin(GPIO_LED, LED_ALL);
}
*/


void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if ( htim->Instance == TIM2){
		if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
		{
			m1_hall = m1_hall + 1;
			m1_deg_10 = m1_hall * 15;
			m1_deg = m1_deg_10 / 10;
			m1_deg_1_10 = m1_deg_10 % 10;
			if(m1_hall==240)
			{
				m1_hall = 0;



//				m1_deg++;

				m1_rev++;
			}


/*		  	printf("%d \n", m1_deg);
			printf("%d \n", m1_rev);
			printf("\n");*/
		}




	}







}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if ( htim->Instance == TIM1)
	{
		count_sec++;

/*		m1_deg_10 = m1_hall * 15;

		m1_deg = m1_deg_10 / 10;

		m1_rpm = m1_deg_10 * 60 / 10;*/




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
