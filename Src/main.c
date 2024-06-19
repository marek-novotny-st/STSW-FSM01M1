/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "fsm01m1_eval_pulse_driver.h"
#include "fsm01m1_eval_diagnostic_driver.h"
#include "nucleo_usart_driver.h"
#include "fsm01m1_eval_driver.h"
#include "stest01a1_eval_diagnostic_driver.h"
#include "stest01a1_eval_driver.h"
#include "fsm01m1_eval_exports.h"
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
SPI_HandleTypeDef hspi2;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI2_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM4_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void multi_ctrl_loop() {
	NUCLEO_USART_vCOM_Config(&huart2);

	USART_MessageTypeDef msg = NUCLEO_USART_vCOM_CreateMessage();
	const USART_MessageTypeDef* p_msg = &msg;
	USART_MessageTypeDef cmd = NUCLEO_USART_vCOM_CreateMessage();
	const USART_MessageTypeDef* p_cmd = &cmd;

	STEST01A1_DIAG_InitCmd(p_cmd);
	STEST01A1_DIAG_InitMsg(p_msg);
	FSM01M1_DIAG_InitCmd(p_cmd);
	FSM01M1_DIAG_InitMsg(p_msg);

	msg.Reset(&msg);
	msg.AppendStr("***** MULTI-BOARD CONTROL TOOL *****\n", &msg);
	msg.AppendStr("* Type help for usage information", &msg);
	NUCLEO_USART_vCOM_WriteLine(&msg);
	NUCLEO_USART_vCOM_WriteChar('\n');
	msg.Reset(&msg);

	while(1) {
		if (cmd.flag == ready) {
//			msg.AppendStr("STEST01A1:", &msg);
//			NUCLEO_USART_vCOM_WriteLine(&msg);
//			msg.Reset(&msg);

			STEST01A1_DIAG_resolve(cmd.data, stest01a1_all);

//			msg.AppendStr("FSM01M1:", &msg);
//			NUCLEO_USART_vCOM_WriteLine(&msg);
//			msg.Reset(&msg);
//
//			FSM01M1_DIAG_resolve(cmd.data, fsm01m1_all);

			cmd.Reset(&cmd);
			cmd.flag = idle;
		}
		if (cmd.flag == idle) {
			NUCLEO_USART_vCOM_ReadLine(&cmd);
		}
	}
}
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
  MX_SPI2_Init();
  MX_USART2_UART_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */

  /* release ADC SPI interface */
  HAL_GPIO_WritePin(SPI_NCS_GPIO_Port, SPI_NCS_Pin, GPIO_PIN_SET);


  /* Dummy read to initialize ADC */
  FSM01M1_ADC120_read_blind(&hspi2);

  FSM01M1_initialization();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  /* Turn-ON VCC1 & VCC2 */
  FSM01M1_VCC1_ON();
  FSM01M1_VCC2_ON();

  /* visual led test */
//  HAL_GPIO_TogglePin(OUT2_CTRL_GPIO_Port, OUT2_CTRL_Pin);
//
//  FSM01M1_PULSE_PulseGen_TIM_Config(&htim1, OUT2_TIM, OUT2_TIM_CHANNEL, 1, 65535, 25000);
//  FSM01M1_PULSE_PulseGen_TIM_Start(&htim1, OUT2_TIM_CHANNEL);
//  HAL_Delay(500);
//  FSM01M1_PULSE_PulseGen_TIM_Stop(&htim1, OUT2_TIM_CHANNEL);
//
//  FSM01M1_PULSE_PulseGen_TIM_Config(&htim4, TIM4, TIM_CHANNEL_3, 1, 65535, 25000);
//  FSM01M1_PULSE_PulseGen_TIM_Start(&htim4, TIM_CHANNEL_3);
//  HAL_Delay(500);
//  FSM01M1_PULSE_PulseGen_TIM_Stop(&htim4, TIM_CHANNEL_3);
//
//  FSM01M1_PULSE_PulseGen_TIM_Config(&htim4, TIM4, TIM_CHANNEL_3, 1, 65535, 50000);
//  FSM01M1_PULSE_PulseGen_TIM_Start(&htim4, TIM_CHANNEL_3);
//  HAL_Delay(500);
//  FSM01M1_PULSE_PulseGen_TIM_Stop(&htim4, TIM_CHANNEL_3);
//
//  /* positive test pulse */
//  FSM01M1_PULSE_PulseGen_TIM_Config(&htim4, TIM4, TIM_CHANNEL_3, 1, 300, 50);
//  FSM01M1_PULSE_PulseGen_TIM_Start(&htim4, TIM_CHANNEL_3);
//  HAL_Delay(500);
//  FSM01M1_PULSE_PulseGen_TIM_Stop(&htim4, TIM_CHANNEL_3);
//  // with discharge
//  FSM01M1_PULSE_PulseGen_TIM_Start_IT(&htim4, TIM_CHANNEL_3);
//  HAL_Delay(500);
//  FSM01M1_PULSE_PulseGen_TIM_Stop_IT(&htim4, TIM_CHANNEL_3);
//
//  /* negative test pulse */
//  FSM01M1_PULSE_PulseGen_TIM_Config(&htim4, TIM4, TIM_CHANNEL_3, 1, 300, 250);
//  FSM01M1_PULSE_PulseGen_TIM_Start(&htim4, TIM_CHANNEL_3);
//  HAL_Delay(500);
//  FSM01M1_PULSE_PulseGen_TIM_Stop(&htim4, TIM_CHANNEL_3);
//  // with discharge
//  FSM01M1_PULSE_PulseGen_TIM_Start_IT(&htim4, TIM_CHANNEL_3);
//  HAL_Delay(500);
//  FSM01M1_PULSE_PulseGen_TIM_Stop_IT(&htim4, TIM_CHANNEL_3);
//
//  /* C/D interface Class 1 */
//  // positive
//  FSM01M1_PULSE_PulseGen_TIM_Config(&htim4, TIM4, TIM_CHANNEL_3, 1, 10000, 100);
//  FSM01M1_PULSE_PulseGen_TIM_Start(&htim4, TIM_CHANNEL_3);
//  HAL_Delay(500);
//  FSM01M1_PULSE_PulseGen_TIM_Stop(&htim4, TIM_CHANNEL_3);
//  // with discharge
//  FSM01M1_PULSE_PulseGen_TIM_Start_IT(&htim4, TIM_CHANNEL_3);
//  HAL_Delay(500);
//  FSM01M1_PULSE_PulseGen_TIM_Stop_IT(&htim4, TIM_CHANNEL_3);
//  // negative
//  FSM01M1_PULSE_PulseGen_TIM_Config(&htim4, TIM4, TIM_CHANNEL_3, 1, 10000, 9900);
//  FSM01M1_PULSE_PulseGen_TIM_Start(&htim4, TIM_CHANNEL_3);
//  HAL_Delay(500);
//  FSM01M1_PULSE_PulseGen_TIM_Stop(&htim4, TIM_CHANNEL_3);
//  // with discharge
//  FSM01M1_PULSE_PulseGen_TIM_Start_IT(&htim4, TIM_CHANNEL_3);
//  HAL_Delay(500);
//  FSM01M1_PULSE_PulseGen_TIM_Stop_IT(&htim4, TIM_CHANNEL_3);
//
//  FSM01M1_PULSE_PulseGen_TIM_Config(&htim4, TIM4, TIM_CHANNEL_3, 1, 65535, 0);
//  FSM01M1_PULSE_PulseGen_TIM_Start(&htim4, TIM_CHANNEL_3);

  /* Main loop */
  HAL_TIM_Base_Start_IT(&htim1);
//  HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_2);
//  FSM01M1_DIAG_IO_Loop(&huart2);

  multi_ctrl_loop();
  while (1) {
	  /* USER_LED_GREEN test */
	  FSM01M1_user_LED_green_ON();
//	  FSM01M1_TimeLoop_Short();

	  FSM01M1_user_LED_green_OFF();
//	  FSM01M1_TimeLoop_Short();

	  FSM01M1_DIAG_IO_Loop(&huart2);
  }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

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
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_16BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi2.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

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
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 160;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 65535;
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
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

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

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 0;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 65535;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
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
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */
  HAL_TIM_MspPostInit(&htim4);

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
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 4294967295;
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
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, D12_USER_LED_GREEN_Pin|D13_USER_LED_RED_Pin|COFF2_CTRL_Pin|OUT_CTRL_Pin
                          |VCC1_DSC_Pin|OUT2_DSC_Pin|OUT1_DSC_Pin|VCC2_DSC_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LD2_USER_Pin|VCC1_CTRL_Pin|TP1_CTRL_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SPI_NCS_Pin|TP2_CTRL_Pin|VCC2_CTRL_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(COFF1_CTRL_GPIO_Port, COFF1_CTRL_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : B1_USER_Pin OUT2_DIAG_Pin OUT1_DIAG_Pin */
  GPIO_InitStruct.Pin = B1_USER_Pin|OUT2_DIAG_Pin|OUT1_DIAG_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : OUTP2_Pin */
  GPIO_InitStruct.Pin = OUTP2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(OUTP2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : OUTP1_Pin */
  GPIO_InitStruct.Pin = OUTP1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(OUTP1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : D12_USER_LED_GREEN_Pin D13_USER_LED_RED_Pin COFF2_CTRL_Pin OUT_CTRL_Pin
                           VCC1_DSC_Pin OUT2_DSC_Pin OUT1_DSC_Pin VCC2_DSC_Pin */
  GPIO_InitStruct.Pin = D12_USER_LED_GREEN_Pin|D13_USER_LED_RED_Pin|COFF2_CTRL_Pin|OUT_CTRL_Pin
                          |VCC1_DSC_Pin|OUT2_DSC_Pin|OUT1_DSC_Pin|VCC2_DSC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : LD2_USER_Pin VCC1_CTRL_Pin TP1_CTRL_Pin */
  GPIO_InitStruct.Pin = LD2_USER_Pin|VCC1_CTRL_Pin|TP1_CTRL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : OUT_FLT1_Pin OUT_FLT2_Pin */
  GPIO_InitStruct.Pin = OUT_FLT1_Pin|OUT_FLT2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : SPI_NCS_Pin */
  GPIO_InitStruct.Pin = SPI_NCS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(SPI_NCS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : COFF1_CTRL_Pin */
  GPIO_InitStruct.Pin = COFF1_CTRL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(COFF1_CTRL_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : TP2_CTRL_Pin VCC2_CTRL_Pin */
  GPIO_InitStruct.Pin = TP2_CTRL_Pin|VCC2_CTRL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI4_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	FSM01M1_PULSE_PeriodElapsedCallback(htim);
	if (htim->Instance == TIM1) {
		HAL_GPIO_TogglePin(LD2_USER_GPIO_Port, LD2_USER_Pin);
	}
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim) {
	FSM01M1_PULSE_PulseFinishedCallback(htim);
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
