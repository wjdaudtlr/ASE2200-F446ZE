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
/*
 * 코드 설명
 * 현재 timer 3는 1초에 한번씩 period elapsed callback 함수를 발생시키고 if(htim == &htim3) 블록 내부 실행 중
 * main()에서 초기화된 telemetry_data 구조체(ih_telemetry.h 참고)를 GetString 함수(ih_telemetry.c 참고)를 이용하여
 * string 획득한 뒤 이를 uart 통신을 통해 보냄
 * HAL_UART_Transmit_IT() 함수는 정상적으로 송신 성공시 HAL_OK를 반환하고 packet count 증가
 * 또한 송신 성공시마다 1번 led가 깜빡거림
 *
 * 현재 timer 4는 20ms에 한번씩 서보에 맞게 설정된 PWM 입력을 보내고 있음
 * 1ms High(켜짐), 19ms Low(꺼짐)시 -90도, 2ms High, 18ms Low시 +90도 임이 데이터시트에 명시되어 있음
 * 현재 실행 시 충분히 움직이지 않는 모습을 보이며 전원 부족 문제로 추측됨
 *
 * 현재 user button(파란색)은 external interrupt를 발생시키도록 설정되어 있음
 * 버튼을 누르면 HAL_GPIO_EXTI_Callback() 함수가 호출되며, if문을 통해 어떤 핀에 의해 호출되었는지 체크함
 * 버튼을 한번 누를 때마다 30도씩 각도가 변하도록 되어있음
 * IH_Servo_Write() 함수를 통해 현재 연결된 서보를 움직일 수 있음
 * 핀 위치를 바꾸거나 서보를 추가하기 위해서는 약간의 이해가 필요하니 주의할 것
 * ih_servo.h에 구현 방법이 매우 상세히 설명되어 있으니 참고할 것
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "usb_otg.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
IH_TelemetryDataTypeDef telemetry_data;
char telemetry_string[DEF_TELEMETRY_STRING_SIZE];

IH_ServoTypeDef servo;
int deg = 0;
int ccr = 1000;
int isup = 0;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

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
  MX_USART3_UART_Init();
  MX_USB_OTG_FS_PCD_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim3);
  HAL_TIM_Base_Start_IT(&htim4);
  HAL_TIM_PWM_Start_IT(&htim4, TIM_CHANNEL_1);

  // initializing telemetry data
  strcpy(telemetry_data.STATE, "INITIALIZING");
  telemetry_data.TEAM_ID = DEF_TELEMETRY_TEAM_ID;
  telemetry_data.MISSION_TIME.HOUR = 13;
  telemetry_data.MISSION_TIME.MINUTE = 45;
  telemetry_data.MISSION_TIME.SECOND = 57;
  // packet count is zero
  telemetry_data.MODE = 'F';
  // STATE initialized above
  // no sensor data initialization: altitude, airspeed
  telemetry_data.HS_DEPLOYED = 'N';
  telemetry_data.PC_DEPLOYED = 'N';
  // no sensor data initialization: temperature, voltage, pressure, GPS, tilt, rotation
  strcpy(telemetry_data.CMD_ECHO, "NO_CMD");
  // optional data initialization

  // initializing servo

  IH_Servo_Attach(&servo, &(htim4.Instance->CCR1));
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  RCC_OscInitStruct.PLL.PLLR = 2;
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
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if (htim == &htim3){
		IH_UTCTime_AddSecond(&telemetry_data.MISSION_TIME);
		IH_TelemetryData_GetString(telemetry_string, &telemetry_data);
		if(HAL_UART_Transmit_IT(&huart3, telemetry_string, sizeof(telemetry_string))==HAL_OK){
			telemetry_data.PACKET_COUNT++;
			HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
		}
	}
	if (htim == &htim4)
		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	if (GPIO_Pin == USER_Btn_Pin){
		HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
		if (isup == 1){
			// going up
			deg += 90;
//			if (deg >= 90){
//				deg = 90;
//				isup = 0;	// let's go down
//			}
			isup = 0;
		}
		else{
			// going down
			deg -= 90;
//			if (deg <= -90){
//				deg = -90;
//				isup = 1;	// let's go up
//			}
			isup = 1;
		}
		IH_Servo_Write(&servo, deg);
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
