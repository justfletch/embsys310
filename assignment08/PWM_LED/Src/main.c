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
TIM_HandleTypeDef htim15;

/* USER CODE BEGIN PV */
int LED2_Value = 0;
int LED2_Value_Rising = 1;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM15_Init(void);
/* USER CODE BEGIN PFP */
void LED1_PWM_SetValue(uint16_t value);
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
        MX_TIM15_Init();
        /* USER CODE BEGIN 2 */
        HAL_TIM_PWM_Start(&htim15, TIM_CHANNEL_1);
        /* USER CODE END 2 */
        
        /* Infinite loop */
        /* USER CODE BEGIN WHILE */
        while (1)
            {
                /* USER CODE END WHILE */
                //raise value to 100% over 0.50 seconds, so 1000/0.5 = 1500 per second
                //200 PWM periods per second (clock is 200kHz, one period is 1000 counts, so 200,000/1000)
                // Since we only have 200 PWM periods in a second, and want to increase 1500 in a second,
                // 1500/200 = 7.5 per period. Period lasts 0.005 seconds, or 5ms
                // Will wait 2 periods so the increase is an integer, 10ms delay, increase of 15
                if(LED2_Value_Rising){
                    //if value is not going to exceed 800, increase by 3
                    if(LED2_Value <= (800-15)){
                        LED2_Value += 15;
                        HAL_Delay(10);
                    }
                    //else start dimming
                    else {
                        LED2_Value_Rising = 0;
                    }
                    
                }
                
                //lower value to 0% over 2 seconds, so 1000/2 = 500 per second
                //200 PWM periods per second (clock is 200kHz, one period is 1000 counts, so 200,000/1000)
                // Since we have 200 PWM periods in a second, and want to decrease 500 in a second,
                // 500/200 = 2.5 per period. Period lasts 0.005 seconds, or 5ms
                // Will wait 2 periods so the increase is an integer, 10ms delay, increase of 5
                else {
                    //if value is not zero, decrease by 1
                    if(LED2_Value >= (0+5)){
                        LED2_Value -= 5;
                        HAL_Delay(10);
                    }
                    //else start dimming
                    else {
                        LED2_Value_Rising = 1;
                    }
                }
                
                
                LED1_PWM_SetValue(LED2_Value);
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
        if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
            {
                Error_Handler();
            }
        /** Initializes the RCC Oscillators according to the specified parameters
        * in the RCC_OscInitTypeDef structure.
        */
        RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
        RCC_OscInitStruct.MSIState = RCC_MSI_ON;
        RCC_OscInitStruct.MSICalibrationValue = 0;
        RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
        RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
        RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
        RCC_OscInitStruct.PLL.PLLM = 1;
        RCC_OscInitStruct.PLL.PLLN = 40;
        RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
        RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
        RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
        if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
            {
                Error_Handler();
            }
        /** Initializes the CPU, AHB and APB buses clocks
        */
        RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
            |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
        RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
        RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
        RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
        RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
        
        if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
            {
                Error_Handler();
            }
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
        
        TIM_MasterConfigTypeDef sMasterConfig = {0};
        TIM_OC_InitTypeDef sConfigOC = {0};
        TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};
        
        /* USER CODE BEGIN TIM15_Init 1 */
        
        /* USER CODE END TIM15_Init 1 */
        htim15.Instance = TIM15;
        htim15.Init.Prescaler = 400-1;
        htim15.Init.CounterMode = TIM_COUNTERMODE_UP;
        htim15.Init.Period = 1000-1;
        htim15.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
        htim15.Init.RepetitionCounter = 0;
        htim15.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
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
        sConfigOC.Pulse = 500;
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
        
        /* GPIO Ports Clock Enable */
        __HAL_RCC_GPIOB_CLK_ENABLE();
        
    }

/* USER CODE BEGIN 4 */
void LED1_PWM_SetValue(uint16_t value)
    {
        //set CCR during runtime
        __HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_1, value);
        
    }
/* USER CODE END 4 */

/**
* @brief  Period elapsed callback in non blocking mode
* @note   This function is called  when TIM17 interrupt took place, inside
* HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
* a global variable "uwTick" used as application time base.
* @param  htim : TIM handle
* @retval None
*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
    {
        /* USER CODE BEGIN Callback 0 */
        
        /* USER CODE END Callback 0 */
        if (htim->Instance == TIM17) {
            HAL_IncTick();
        }
        /* USER CODE BEGIN Callback 1 */
        
        /* USER CODE END Callback 1 */
    }

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
