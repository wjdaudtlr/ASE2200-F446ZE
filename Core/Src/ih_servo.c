/*
 * ih_servo.c
 *
 *  Created on: Dec 27, 2023
 *      Author: SURFACE
 */


// includes
#include <stdint.h>
#include "ih_servo.h"
// types

// variables

// constants

// function prototypes

// functions
void IH_Servo_Attach(IH_ServoTypeDef* Servo, volatile uint32_t* CCR_Address){
	Servo->CCR_Address = CCR_Address;
}
void IH_Servo_Write(IH_ServoTypeDef* Servo, int8_t deg){
	// angle saturation
	if (deg > (DEF_SERVO_MAX_DEG)){
		deg = (DEF_SERVO_MAX_DEG);
	}
	if (deg < (DEF_SERVO_MIN_DEG)){
		deg = (DEF_SERVO_MIN_DEG);
	}
	// calculate ccr
    int ccr = (float) ((DEF_SERVO_MAX_PW)-(DEF_SERVO_MIN_PW))/((DEF_SERVO_MAX_DEG)-(DEF_SERVO_MIN_DEG))*(deg - DEF_SERVO_MIN_DEG)+DEF_SERVO_MIN_PW;
    // pulse width saturation
    if (ccr < DEF_SERVO_MIN_PW){
    	ccr = DEF_SERVO_MIN_PW;
    }
    if (ccr > DEF_SERVO_MAX_PW){
    	ccr = DEF_SERVO_MAX_PW;
    }
	*(Servo->CCR_Address) = ccr - 1;
}
