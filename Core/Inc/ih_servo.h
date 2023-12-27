/*
 * ih_servo.h
 *
 *  Created on: Dec 27, 2023
 *      Author: Jeong Myeong Sik
 *      How to use:
 *      # Software Settings
 *      	Set timer N in .ioc file; Timers -> TIM(N)
 *      		in Mode window
 *      		set clock source 	internal clock
 *      		set Channel M 		PWM Generation CH(M)
 *
 *      		in Configuration window, Parameter settings tab
 *      		set prescaler 		84 - 1
 *      		set Counter Period	20000 - 1
 *      		set pulse 			1000 - 1
 *
 *      		in Configuration window, NVIC settings tab
 *      		enable TIM(N) Global Interrupt
 *
 *      		in Pinout window, search TIM(N)_CH(M)
 *      		remember the pin name PXYY, (alphabet for X, number for Y)
 *
 *      	Include this file in main.h
 *      		#include "ih_servo.h"
 *
 *      	Using IH_ServoTypeDef, define servo structure in main.c
 *				IH_ServoTypeDef servo;
 *
 *			You must start timer and pwm generation between USER CODE BEGIN 2, USER CODE END 2.
 *				HAL_TIM_Base_Start_IT(&htim(N));
 *				HAL_TIM_PWM_Start_IT(&htim(N), TIM_CHANNEL_(M));
 *
 *			Using IH_Servo_Attach, Set CCR address between USER CODE BEGIN 2, USER CODE END 2.
 *				IH_Servo_Attach(&servo, &(htim(N).Instance->CCR(M)));
 *
 *			Using IH_Servo_Write, Set degree(-90 ~ 90)
 *				IH_Servo_Write(&servo, deg);
 *
 *		# Hardware Settings
 *			Check if the board is powered
 *				the board must NOT POWERED WHILE CHANGING WIRING
 *
 *			Connect servo ground(brown) to board ground(GND)
 *				CN8 connector has 5V pin and ground Pin
 *
 *			Connect servo Vcc(red) to board 5V pin
 *				recommend to use external power(computer USB power is too low)
 *				MUST CONNECT ALL GROUNDS WHEN USING VARIOUS POWER SOURCE
 *
 *			Connect servo signal(orange) to board pwm output pin
 *				From pin name PXYY and pinout image, you can find pin to connect
 *
 */
#ifndef INC_IH_SERVO_H_
#define INC_IH_SERVO_H_

// includes
#include "stm32f446xx.h"
// typedefs

typedef struct _IH_ServoTypeDef{
	volatile uint32_t* CCR_Address;
}IH_ServoTypeDef;

// defines
#define DEF_SERVO_MAX_DEG 90	// unit: degree
#define DEF_SERVO_MIN_DEG -90
#define DEF_SERVO_MAX_PW 2400	// unit: microsecond
#define DEF_SERVO_MIN_PW 544
// prototypes
void IH_Servo_Attach(IH_ServoTypeDef* Servo, volatile uint32_t* CCR_Address);
void IH_Servo_Write(IH_ServoTypeDef* Servo, int8_t deg);

#endif /* INC_IH_SERVO_H_ */
