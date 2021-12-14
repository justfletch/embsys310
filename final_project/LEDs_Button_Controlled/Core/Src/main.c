/* USER CODE BEGIN Header */
/**
******************************************************************************
* @file           : main.c
* @brief          : Main program body
******************************************************************************
* @attention
*
* Copyright (c) 2021 STMicroelectronics.
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
#include "led_state.h"
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
TIM_HandleTypeDef htim15;

/* USER CODE BEGIN PV */
uint16_t LED_PWM_value = 0;
int16_t increment = 0;
LED_STATE LED1_LED2_STATE = STATE1;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM15_Init(void);
/* USER CODE BEGIN PFP */
void user_pwm_setvalue(uint16_t value, TIM_HandleTypeDef* htim);
void set_GPIO_Mode_PA5_PB14();
void set_AF_Mode_PA5_PB14();
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
  MX_TIM15_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim15, TIM_CHANNEL_1);
  /* USER CODE END 2 */
  
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    
    /* USER CODE BEGIN 3 */
    //switch
    
    //case 1: 
    switch(LED1_LED2_STATE){
      
     //LEDs OFF
    case STATE1 : 
      {
        //make sure we are in GPIO mode
        set_GPIO_Mode_PA5_PB14();
        
        //Set GPIO ODR to zero
        GPIOB->ODR &= ~GPIO_ODR_OD14;
        GPIOA->ODR &= ~GPIO_ODR_OD5;
        break;
      }
      
     //LEDs ON
    case STATE2 :
      {
        //make sure we are in GPIO mode
        set_GPIO_Mode_PA5_PB14();
        
        //Set GPIO ODR to one
        GPIOB->ODR |= GPIO_ODR_OD14;
        GPIOA->ODR |= GPIO_ODR_OD5;
        break;
      }
      
     //LEDs slow blink
    case STATE3 :
      {
        //make sure we are in GPIO mode
        set_GPIO_Mode_PA5_PB14();
        
        //Toggle GPIO OD
        GPIOB->ODR ^= GPIO_ODR_OD14;
        GPIOA->ODR ^= GPIO_ODR_OD5;
        //long delay
        HAL_Delay(1250);
        break;
      }
      
     //LEDs fast blink
    case STATE4 :
      {
        //make sure we are in GPIO mode
        set_GPIO_Mode_PA5_PB14();
        
        //Toggle GPIO OD
        GPIOB->ODR ^= GPIO_ODR_OD14;
        GPIOA->ODR ^= GPIO_ODR_OD5;
        //short delay
        HAL_Delay(300);
        
        break;
      }
      
     //Dim LEDs slowly
    case STATE5 :
      {
        //make sure we are in Alternate Function mode
        set_AF_Mode_PA5_PB14();
        
        
        if(LED_PWM_value == 0){
          increment = 10;
        }
        //stop at 75% (1500 of 2000) - that is bright enough!
        if(LED_PWM_value == 1500) {
          increment = -10;
        }
        LED_PWM_value += increment;
        user_pwm_setvalue(LED_PWM_value, &htim15);
        user_pwm_setvalue(LED_PWM_value, &htim2);
        HAL_Delay(20);
        break;
      }
      
      //Dim LEDs quickly
    case STATE6 :
      {
        //make sure we are in Alternate Function mode
        set_AF_Mode_PA5_PB14();
        if(LED_PWM_value == 0){
          increment = 50;
        }
        //stop at 75% (1500 of 2000) - that is bright enough!!
        if(LED_PWM_value == 1500) {
          increment = -50;
        }
        LED_PWM_value += increment;
        user_pwm_setvalue(LED_PWM_value, &htim15);
        user_pwm_setvalue(LED_PWM_value, &htim2);
        HAL_Delay(20);
        break;
      }
    }
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
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
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
  htim2.Init.Prescaler = 160-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 2000-1;
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
  sConfigOC.Pulse = 600;
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
* @brief TIM15 Initialization Function
* @param None
* @retval None
*/
static void MX_TIM15_Init(void)
{
  
  /* USER CODE BEGIN TIM15_Init 0 */
  
  /* USER CODE END TIM15_Init 0 */
  
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};
  
  /* USER CODE BEGIN TIM15_Init 1 */
  
  /* USER CODE END TIM15_Init 1 */
  htim15.Instance = TIM15;
  htim15.Init.Prescaler = 160-1;
  htim15.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim15.Init.Period = 2000-1;
  htim15.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim15.Init.RepetitionCounter = 0;
  htim15.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim15) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim15, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim15) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim15, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 1200;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim15, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
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
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim15, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM15_Init 2 */
  
  /* USER CODE END TIM15_Init 2 */
  HAL_TIM_MspPostInit(&htim15);
  
}

/**
* @brief GPIO Initialization Function
* @param None
* @retval None
*/
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  
  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  
  /*Configure GPIO pin : BUTTON1_Pin */
  GPIO_InitStruct.Pin = BUTTON1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BUTTON1_GPIO_Port, &GPIO_InitStruct);
  
  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
  
}

/* USER CODE BEGIN 4 */

//set pulse value for PWM duty ratio
void user_pwm_setvalue(uint16_t value, TIM_HandleTypeDef* htim)
{
  TIM_OC_InitTypeDef sConfigOC;
  
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = value;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  HAL_TIM_PWM_ConfigChannel(htim, &sConfigOC, TIM_CHANNEL_1);
  
  //Not sure exactly why, but need to set timer state to Ready via some method. This function happens to do that at some point
  //If state is not Ready, Start doesn't work (LED remains off always).
  if (HAL_TIM_Base_Init(htim) != HAL_OK)
  {
    Error_Handler();
  }
  
  HAL_TIM_PWM_Start(htim, TIM_CHANNEL_1); 
}


void set_GPIO_Mode_PA5_PB14(){
  //GPIO Mode 0x01
  GPIOB->MODER &= ~GPIO_MODER_MODE14_1; //set GPIOB MODER14[1] zero
  GPIOB->MODER |= GPIO_MODER_MODE14_0;  //set GPIOB MODER14[0] one
  
  GPIOA->MODER &= ~GPIO_MODER_MODE5_1; //set GPIOA MODER5[1] zero
  GPIOA->MODER |= GPIO_MODER_MODE5_0; //set GPIOA MODER5[0] one
}
void set_AF_Mode_PA5_PB14()
{
  //Alternate Function (AF) Mode 0x10
  
  //AF selection would be:
  //PA5 TIM2_CH1 selection is AF1 (0001)
  //PB15 TIM15_CH1 selection is AF14 (1110)
  
  //Just need to set back to AF mode, since selection was done via PWM mode in CubeMX
  GPIOB->MODER |= GPIO_MODER_MODE14_1; //set GPIOB MODER14[1] one
  GPIOB->MODER &= ~GPIO_MODER_MODE14_0;  //set GPIOB MODER14[0] zero
  
  GPIOA->MODER |= GPIO_MODER_MODE5_1; //set GPIOA MODER5[1] one
  GPIOA->MODER &= ~GPIO_MODER_MODE5_0; //set GPIOA MODER5[0] zero
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

