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
#include "dac.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <system.h>
#include "waveform_gen.h"
#include "menu_definition.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define  UART1_rxBuffer_len  12


/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t UART1_rxBuffer[UART1_rxBuffer_len];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
int32_t CALC_temperature(int32_t freq_in, int8_t direction, uint8_t dec);

void menu_encoder_event(void);

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);


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
//  char buff[20];
//  uint32_t counter = 0;
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
  MX_DMA_Init();
  MX_DAC_Init();
  MX_TIM7_Init();
  MX_TIM2_Init();
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  MX_TIM5_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */

/* -------------------------------------------------------------------------------- */
/* -- TIMERS START -- */
/* -------------------------------------------------------------------------------- */
  HAL_TIM_Base_Start(&htim2);
  HAL_TIM_Base_Start(&htim5);
  HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);

/* -------------------------------------------------------------------------------- */
/* -- CREATE ENCODER -- */
/* -------------------------------------------------------------------------------- */
  encoder_struct_init(&encoder_1, &htim1);

/* -------------------------------------------------------------------------------- */
/* -- LCD ST7735 SCREEN INIT -- */
/* -------------------------------------------------------------------------------- */
  ST7735_Init(1);

/* -------------------------------------------------------------------------------- */
/* -- MENU INIT -- */
/* -------------------------------------------------------------------------------- */
  GUI_init();
  Menu_Show();

/* -------------------------------------------------------------------------------- */
/* -- WAVEFORMS INIT -- */
/* -------------------------------------------------------------------------------- */
  calcsin();
  waveform_struct_init(&sine,&htim2,sine_val,N_s,1000,1,0);

  //HAL_Delay(500);
/* -------------------------------------------------------------------------------- */
/* -- DAC START -- */
/* -------------------------------------------------------------------------------- */


HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, sine_val, N_s, DAC_ALIGN_12B_R);

//HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_2, sine_val, N_s, DAC_ALIGN_12B_R);


// DEBUG
//  HAL_UART_Receive_DMA (&huart1, UART1_rxBuffer, UART1_rxBuffer_len); 	//handler located in main.c file
//  uint8_t data[] = "HELLO WORLD \r\n";
//  HAL_UART_Transmit (&huart2, data, sizeof (data), 10);






  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	menu_encoder_event();

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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void menu_encoder_event(void) {

	  if( encoder_step_clockwise(&encoder_1) == true) {
		Menu_SelectNext();

	  }
	  if(encoder_step_counterclockwise(&encoder_1) == true) {
		Menu_SelectPrev();
	  }
	  if(encoder_enter(&encoder_1) == true) {
	  		Menu_Click();
	   }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {


	static float result = 0;

			 switch(UART1_rxBuffer[1])
			 {
			 case 1:

				 for(int i=1; i<sizeof(UART1_rxBuffer); i++) {
					 result = result * 10 + ( UART1_rxBuffer[i]);
					 //----------------------
					 }
			     break;

			 case 2:

				 for(int i=1; i<sizeof(UART1_rxBuffer); i++) {
					 result = result * 10 + ( UART1_rxBuffer[i]);
					 }
			     break;

			 default:
				 break;
			 }


		 HAL_UART_Receive_DMA(&huart1, UART1_rxBuffer, sizeof(UART1_rxBuffer)); // Ponowne włączenie nasłuchiwania

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
