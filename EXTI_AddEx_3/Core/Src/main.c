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

/* USER CODE BEGIN PV */
int flag_SW1 = 0, flag_SW2 = 0, flag_SW3 = 0, flag_SW4 = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
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
	uint16_t led = 0x01;
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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  //문제 그대로 동작일때
	 /*
	  	led == 0x00;

	  		  if ( flag_SW1 == 1 ) {
	  			  led = 0x01;
	  			  led_c = 0x02;
	  			  if (led == 0x01)
	  				  {
	  					  led_c = led_c << 1;
	  					  led_c = led_c & 0xfe;
	  				  }

	  			  do {
	  						  LED_OnOff(led, 200);
	  						  led = led << 1;
	  						  led = led & 0xfe;
	  					  } while (led != led_c);

	  			  if (led_c == 0x04)
	  						  {
	  							  led_c = 0x02;
	  						  }
	  		  	  }
	  		  if ( flag_SW2 == 1 ) {
	  			  led = 0x01;
	  			  led_c = 0x08;

	  			  if (led == 0x01)
	  			  {
	  				  led_c = led_c << 1;
	  				  led_c = led_c & 0xfe;


	  			  }

	  			  do {
	  					  LED_OnOff(led, 200);
	  					  led = led << 1;
	  					  led = led & 0xfe;
	  				  } while (led != led_c);

	  			  if (led_c == 0x10)
	  					  {
	  						  led_c = 0x08;
	  					  }
	  		  	  }
	  		  if ( flag_SW3 == 1 ) {
	  			  led = 0x01;
	  			  led_c = 0x20;

	  			  if (led == 0x01)
	  				  {
	  					  led_c = led_c << 1;
	  					  led_c = led_c & 0xfe;


	  				  }

	  			  do {
	  						  LED_OnOff(led, 200);
	  						  led = led << 1;
	  						  led = led & 0xfe;
	  					  } while (led != led_c);

	  			  if (led_c == 0x40)
	  						  {
	  							  led_c = 0x20;
	  						  }
	  		  	  }
	  		  if ( flag_SW4 == 1 ) {
	  			  led = 0x01;
	  			  led_c = 0x80;

	  			  if (led == 0x01)
	  			  {
	  				  led_c = led_c << 1;
	  				  led_c = led_c & 0xfe;


	  			  }

	  			  do {
	  					  LED_OnOff(led, 200);
	  					  led = led << 1;
	  					  led = led & 0xfe;
	  			  	  	  } while (led != led_c);

	  			  if (led_c == 0x00)
	  			  {
	  				  led_c = 0x80;
	  			  }
	  		  }
	  	  */

	  //예제 2번과 동일한 동작일때
	  if( flag_SW1 == 1 ){


	  		  led = 0x00;
	  		  LED_OnOff(led, 100);

	  		  led = led | 0x03;
	  		  LED_OnOff(led, 100);


	  	  }
	  	  if( flag_SW2 == 1 ){
	  		  led = 0x00;
	  		  LED_OnOff(led, 100);

	  		  led = led | 0x0c;
	  		  LED_OnOff(led, 100);


	  	  	  }
	  	  if ( flag_SW3 == 1 ) {
	  		  led = 0x00;
	  		  LED_OnOff(led, 100);

	  		  led = led | 0x30;
	  		  LED_OnOff(led, 100);

	  	  	  }
	  	  if ( flag_SW4 == 1 ) {
	  		  led = 0x00;
	  		  LED_OnOff(led, 100);

	  		  led = led | 0xc0;
	  		  LED_OnOff(led, 100);

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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
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
  __HAL_RCC_GPIOG_CLK_ENABLE();
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
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN)
{
	if ( GPIO_PIN == SW1) flag_SW1 = 1, flag_SW2 = 0, flag_SW3 = 0, flag_SW4 = 0;
	if ( GPIO_PIN == SW2) flag_SW1 = 0, flag_SW2 = 1, flag_SW3 = 0, flag_SW4 = 0;
	if ( GPIO_PIN == SW3) flag_SW1 = 0, flag_SW2 = 0, flag_SW3 = 1, flag_SW4 = 0;
	if ( GPIO_PIN == SW4) flag_SW1 = 0, flag_SW2 = 0, flag_SW3 = 0, flag_SW4 = 1;
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
