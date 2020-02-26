/*
 * tmuapp.c
 *
 * Created: 24-Feb-20 11:26:07 AM
 * Author : ahmed
 */

#include "stdio.h"
#include "TMU_TS/TMU.h"
#include "Error_table.h"


st_TMU_init initTest = {
		TMU_TMR_CH0
};

void TMU_initTesting(st_TMU_init *ConfigPtr)
{
	sint8_t output = 0;

	output = TMU_Init(ConfigPtr);

	if(output == ERROR_NULL_PTR_INIT)
	{
		printf("INIT ERROR #1 - NULL POINTER DETECTED\n");
	}

	if(output == ERROR_MULTIPLE_MODULE_INIT)
	{
		printf("INIT ERROR #2 - MULTIPLE MODULE INITIALIZATION\n");
	}

	if(output == INVALID_INIT_PARAMETER)
	{
		printf("INIT ERROR #3 - INVALID PARAMETER\n");
	}

	if(output == 0)
	{
		printf("INIT FUNCTION NO ERRORS\n");
	}
}

// init:		null pointer, not initialized start, multi init, stop without start,
// invalid parameters, multiple stops, mutli starts, buffer full


void TMU_startTesting(TMU_TaskType *Tmu_start)
{
	sint8_t output = 0;

	output = TMU_Start_Timer(Tmu_start);

	if(output == ERROR_NULL_PTR_START)
	{
		printf("START ERROR #1 - NULL POINTER DETECTED\n");
	}

	if(output == ERROR_MULTIPLE_MODULE_START)
	{
		printf("START ERROR #2 - MULTIPLE MODULE START\n");
	}

	if(output == ERROR_START_FULL_BUFFER)
	{
		printf("START ERROR #3 - FULL BUFFER\n");
	}

	if(output == ERROR_MODULE_NOT_INIT)
	{
		printf("START ERROR #4 - MODULE NOT INITIALIZED\n");
	}

	if(output == 0)
	{
		printf("INIT FUNCTION NO ERRORS\n");
	}

	// invalid parameters, module not initialized
}

void TMU_dispatchTesting(void)
{
	sint8_t output = 0;

	output = TMU_Dispatch();

	if(output == ERROR_MODULE_NOT_INIT)
	{
		printf("DISPATCH ERROR #1 - MODULE NOT INITIALIZED\n");
	}
}

void TMU_stopTesting(uint8_t ID)
{
	sint8_t output = 0;

	output = TMU_Stop_Timer(ID);

	if(output == ERROR_MODULE_DIDNOT_START)
	{
		printf("STOP ERROR #1 - TASK NOT STARTED\n");
	}
}

void callBackTest(void)
{

}

int main(void)
{
	/*************************  TMU_INIT_TESTING  *********************/

	/*
	 * TEST 1 Description : inserting a null pointer and checking output
	 * expected: NULL_POINTER_ERROR
	 * please remove comment to check it

	TMU_initTesting(NULL);

	*/


	/*
	 * TEST 2 Description: making multiple init and reading error
	 * expected: multiple init error
	 * please remove comment to check it

	TMU_Init(&initTest);

	TMU_initTesting(&initTest);

	*/


	/*
	 * TEST 3 Description : inserting invalid paramters
	 * expected: error invalid parameters
	 * please remove comment to check it


	TMU_initTesting(&initTest);

	*/


	/*************************  TMU_START_TESTING  *********************/

	/*
	 * TEST 1 Description : inserting a null pointer and checking output
	 * expected: NULL_POINTER_ERROR
	 * please remove comment to check it

	TMU_TaskType test = {
			TMU_PERIODIC,
			1,
			100,
			TASK_STATE_NOTDONE,
			&callBackTest
	};

	TMU_Init(&initTest);

	TMU_startTesting(NULL);

	*/


	/*
	 * TEST 2 Description : making multiple start and reading error
	 * expected: multiple start error
	 * please remove comment to check it

	TMU_TaskType test = {
			TMU_PERIODIC,
			1,
			100,
			TASK_STATE_NOTDONE,
			&callBackTest
	};

	TMU_Init(&initTest);

	TMU_Start_Timer(&test);

	TMU_startTesting(&test);

	 */


	/*
	 * TEST 3 Description : adding tasks while buffer is full
	 * expected: error full buffer
	 * please remove comment to check it

	TMU_TaskType test = {
			TMU_PERIODIC,
			1,
			100,
			TASK_STATE_NOTDONE,
			&callBackTest
	};

	TMU_Init(&initTest);
	TMU_Start_Timer(&test);

	test.u8_id = 2;

	TMU_Start_Timer(&test);

	test.u8_id = 3;

	TMU_startTesting(&test);

	 */


	/*
	 * TEST 4 Description : starting without initialization
	 * expected: error not initialized
	 * please remove comment to check it

	TMU_TaskType test = {
			TMU_PERIODIC,
			1,
			100,
			TASK_STATE_NOTDONE,
			&callBackTest
	};

	TMU_startTesting(&test);

	*/


	/*************************  TMU_DISPATCH_TESTING  *********************/

	/*
	 * TEST 1 Description : Dispatch without initialization
	 * expected: error not initialized
	 * please remove comment to check it



	TMU_dispatchTesting();

	*/

	/*************************  TMU_STOP_TESTING  *********************/

	/*
	 * TEST 1 Description : Stop without starting
	 * expected: error not started
	 * please remove comment to check it
	*/

	TMU_TaskType test = {
			TMU_PERIODIC,
			1,
			100,
			TASK_STATE_NOTDONE,
			&callBackTest
	};

	TMU_Init(&initTest);

	/* TMU_DeInit function wasn't handled yet */
}
