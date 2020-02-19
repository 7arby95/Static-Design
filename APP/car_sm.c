/*
 * car_sm.c
 *
 *  Created on: Feb 18, 2020
 *      Author: Youssef Harby
 */


/*- INCLUDES -----------------------------------------------*/

#include "car_sm.h"
#include "Steering.h"
#include "../ECUAL/Us.h"


/*- DEFINES ------------------------------------------------*/

#define		MOT_BCK_DIR				1
#define		MOT_RGT_DIR				2
#define		MOT_FOR_DIR				3

#define		MOT_TURN_DELAY			125
#define		MOT_DELAY				125

#define		MOT_SPEED_PERCENTAGE	35

#define		MOT_MIN_DISTANCE		25
#define		MOT_MAX_DISTANCE		45


/*- APIs IMPLEMENTATION ------------------------------------*/

ERROR_STATUS Car_SM_Init(void)
{
	uint8_t au8_Ret = E_OK;

	/* Initialization of steering (motors initialization) */
	au8_Ret = Steering_Init();
	/* Initialization of ultrasonic sensor driver */
	au8_Ret = Us_Init();

	return au8_Ret;
}

ERROR_STATUS Car_SM_Update(void)
{
	uint8_t au8_Ret = E_OK;
	/* A variable used to apply state machine cases */
	uint8_t au8_SM_value = 0;
	/* A variable to store distance in it */
	uint16_t au16_Distance = 0;
	/* A variable used as a flag */
	uint8_t au8_rotationflag = 0;

	/* Sending trigger signal */
	au8_Ret |= Us_Trigger();
	/* Reading the distance from ultrasonic driver */
	au8_Ret |= Us_GetDistance(&au16_Distance);

	/* In case the car is too close to the obstacle */
	if(au16_Distance <= MOT_MIN_DISTANCE)
	{
		au8_SM_value = MOT_BCK_DIR;
	}
	/* In case the car is in the range to rotate */
	else if((au16_Distance >=MOT_MIN_DISTANCE && au16_Distance <= MOT_MAX_DISTANCE) || au8_rotationflag == 1)
	{
		au8_SM_value = MOT_RGT_DIR;
	}
	/* In case the car is far from the obstacle */
	else if(au16_Distance >= MOT_MAX_DISTANCE && au8_rotationflag == 0)
	{
		au8_SM_value = MOT_FOR_DIR;
	}

	/* A switch case on machine states */
	switch(au8_SM_value)
	{
	/* In case the motors are to be driven backwards */
	case MOT_BCK_DIR:
		au8_Ret |= Steering_SteerCar(CAR_BACKWARD, MOT_SPEED_PERCENTAGE);
		au8_rotationflag = 1;
		break;
	case MOT_RGT_DIR:
		/* In case the motors are to be driven rotationally */
		au8_Ret |= Steering_SteerCar(CAR_RIGHT, MOT_SPEED_PERCENTAGE);
		softwareDelayMs(MOT_TURN_DELAY);
		au8_rotationflag = 0;
		break;
	case MOT_FOR_DIR:
		/* In case the motors are to be driven forwards */
		au8_Ret |= Steering_SteerCar(CAR_FORWARD, MOT_SPEED_PERCENTAGE);
		break;
	default:
		au8_Ret = E_NOK;
		break;
	}

	softwareDelayMs(MOT_DELAY);

	return au8_Ret;
}
