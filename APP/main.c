/*
 * main.c
 *
 *  Created on: Feb 17, 2020
 *      Author: Youssef Harby
 */

#include "car_sm.h"
#include "../softwareDelay.h"

int main(void)
{
	softwareDelayMs(500);

	Car_SM_Init();

	while(1)
	{
		Car_SM_Update();
	}
}
