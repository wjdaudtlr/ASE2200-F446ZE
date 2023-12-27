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
	// convert degree to actual CCR value
	// CCR = 1000 when -90, CCR = 2000 when +90
	// CCR = 1000/180*deg + 1500
    int ccr = (float) 1000/180*deg + 1500;
    if (ccr < 1000){
    	ccr = 1000;
    }
    if (ccr > 2000){
    	ccr = 2000;
    }
	*(Servo->CCR_Address) = ccr - 1;
}
