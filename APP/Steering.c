/*
 * Steering.c
 *
 *  Created on: Feb 18, 2020
 *      Author: Youssef Harby
 */


/*- INCLUDES -----------------------------------------------*/

#include "Steering.h"
#include "../ECUAL/motor.h"


/*- APIs IMPLEMENTATION ------------------------------------*/

ERROR_STATUS Steering_Init(void)
{
	/* Initialization of the required motors */
	Motor_Init(MOTOR_1 | MOTOR_2);

	return E_OK;
}

ERROR_STATUS Steering_SteerCar(uint8_t Steering_CarCmd, uint8_t speed)
{
	uint8_t au8_Ret = E_OK;

	/* A switch case to determine the required state of the car motors */
	switch(Steering_CarCmd)
	{
	case CAR_STOP:
		/* Stop the car in the case of stop */
		au8_Ret |= Motor_Stop(MOTOR_1 | MOTOR_2);
		break;
	case CAR_FORWARD:
		/* The two motors are driven in the same direction (forward) */
		au8_Ret |= Motor_Direction((MOTOR_1 | MOTOR_2), MOTOR_FORWARD);
		au8_Ret |= Motor_Start((MOTOR_1 | MOTOR_2), speed);
		break;
	case CAR_BACKWARD:
		/* The two motors are driven in the other direction (backward) */
		au8_Ret |= Motor_Direction((MOTOR_1 | MOTOR_2), MOTOR_BACKWARD);
		au8_Ret |= Motor_Start((MOTOR_1 | MOTOR_2), speed);
		break;
	case CAR_RIGHT:
		/* The two motors are driven in different directions (right) */
		au8_Ret |= Motor_Direction(MOTOR_1, MOTOR_BACKWARD);
		au8_Ret |= Motor_Start(MOTOR_1, speed);
		au8_Ret |= Motor_Direction(MOTOR_2, MOTOR_FORWARD);
		au8_Ret |= Motor_Start(MOTOR_2, speed);
		break;
	case CAR_LEFT:
		/* the two motors are driven in different directions (left) */
		au8_Ret |= Motor_Direction(MOTOR_1, MOTOR_FORWARD);
		au8_Ret |= Motor_Start(MOTOR_1, speed);
		au8_Ret |= Motor_Direction(MOTOR_2, MOTOR_BACKWARD);
		au8_Ret |= Motor_Start(MOTOR_2, speed);
		break;
	default:
		au8_Ret = E_NOK;
		break;
	}

	return au8_Ret;
}
