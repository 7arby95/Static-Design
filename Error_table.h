/*
 * Error_table.h
 *
 * Created: 25-Feb-20 5:22:48 PM
 *  Author: ahmed
 */ 


#ifndef ERROR_TABLE_H_
#define ERROR_TABLE_H_


/************************************************************************/
/*							INIT DEFINES                                */
/************************************************************************/
#define ERROR_NULL_PTR_INIT		(-1)
#define ERROR_MULTIPLE_MODULE_INIT	(-2)
#define INVALID_INIT_PARAMETER		(-3)
#define ERROR_MODULE_NOT_INIT		(-4)

/************************************************************************/
/*							START DEFINES                               */
/************************************************************************/
#define ERROR_NULL_PTR_START	(-5)
#define ERROR_MULTIPLE_MODULE_START	(-6)
#define ERROR_START_FULL_BUFFER		(-7)

/************************************************************************/
/*							DISPATCH DEFINES                            */
/************************************************************************/
#define ERROR_DISPATCH_NO_TASKS	(-8)

/************************************************************************/
/*							STOP DEFINES                                */
/************************************************************************/
#define ERROR_MODULE_DIDNOT_START		(-9)


#endif /* ERROR_TABLE_H_ */
