/*
 * Timer.c
 *
 *  Created on: Feb 17, 2020
 *      Author: Youssef Harby
 */


/*- INCLUDES -----------------------------------------------*/

#include "Timer.h"


/*- DEFINES ------------------------------------------------*/

#define		TIMER_CLOCK_ON_FALLING_EDGE		6
#define		TIMER_CLOCK_ON_RISING_EDGE		7

#define		TIMER01_NO_CLOCK				0
#define		TIMER01_NO_PRESCALER			1
#define		TIMER01_8_PRESCALER				2
#define		TIMER01_64_PRESCALER			3
#define		TIMER01_256_PRESCALER			4
#define		TIMER01_1024_PRESCALER			5

#define		TIMER2_NO_CLOCK					0
#define		TIMER2_NO_PRESCALER				1
#define		TIMER2_8_PRESCALER				2
#define		TIMER2_32_PRESCALER				3
#define		TIMER2_64_PRESCALER				4
#define		TIMER2_128_PRESCALER			5
#define		TIMER2_256_PRESCALER			6
#define		TIMER2_1024_PRESCALER			7

#define		TIMER_PRESCALER_MASK			0xF8


/*- GLOBAL STATIC VARIABLES --------------------------------*/

/* Two global variables to hold the values of the timers' prescalers */
static uint8_t gu8_timer0Timer1PreScaler = 0;
static uint8_t gu8_timer2PreScaler = 0;

/* The following are pointers to functions to be used in call back operation */
static volatile void (*g_T0_CTC_callBackPtr)(void) = NULL;
static volatile void (*g_T0_OVF_callBackPtr)(void) = NULL;

static volatile void (*g_T1_ICU_callBackPtr)(void) = NULL;
static volatile void (*g_T1_CTC_A_callBackPtr)(void) = NULL;
static volatile void (*g_T1_CTC_B_callBackPtr)(void) = NULL;
static volatile void (*g_T1_OVF_callBackPtr)(void) = NULL;

static volatile void (*g_T2_CTC_callBackPtr)(void) = NULL;
static volatile void (*g_T2_OVF_callBackPtr)(void) = NULL;


/*- INTERRUPT SERVICE ROUTINES -----------------------------*/

ISR(TIMER0_COMP_vect)
{
	if(g_T0_CTC_callBackPtr != NULL)
	{
		g_T0_CTC_callBackPtr();
	}
}

ISR(TIMER0_OVF_vect)
{
	if(g_T0_OVF_callBackPtr != NULL)
	{
		g_T0_OVF_callBackPtr();
	}
}

ISR(TIMER1_CAPT_vect)
{
	if(g_T1_ICU_callBackPtr != NULL)
	{
		g_T1_ICU_callBackPtr();
	}
}

ISR(TIMER1_COMPA_vect)
{
	if(g_T1_CTC_A_callBackPtr != NULL)
	{
		g_T1_CTC_A_callBackPtr();
	}
}

ISR(TIMER1_COMPB_vect)
{
	if(g_T1_CTC_B_callBackPtr != NULL)
	{
		g_T1_CTC_B_callBackPtr();
	}
}

ISR(TIMER1_OVF_vect)
{
	if(g_T1_OVF_callBackPtr != NULL)
	{
		g_T1_OVF_callBackPtr();
	}
}

ISR(TIMER2_COMP_vect)
{
	if(g_T2_CTC_callBackPtr != NULL)
	{
		g_T2_CTC_callBackPtr();
	}
}

ISR(TIMER2_OVF_vect)
{
	if(g_T2_OVF_callBackPtr != NULL)
	{
		g_T2_OVF_callBackPtr();
	}
}


/*- APIs IMPLEMENTATION ------------------------------------*/

ERROR_STATUS Timer_Init(Timer_cfg_s* Timer_cfg)
{
	uint8_t au8_Ret = E_OK;
	/* A switch case to decide which timer module to be used */
	switch(Timer_cfg->Timer_CH_NO)
	{
	case TIMER_CH0:
		/* Non-PWM mode */
		SET_BIT(TCCR0_R, FOC0);

		/* Choose CTC mode */
		SET_BIT(TCCR0_R, WGM01);

		/* A switch case to decide which mode to be operating at */
		switch(Timer_cfg->Timer_Mode)
		{
		case TIMER_MODE:
			gu8_timer0Timer1PreScaler = Timer_cfg->Timer_Prescaler;
			break;
		case COUNTER_RISING_MODE:
			gu8_timer0Timer1PreScaler = TIMER_CLOCK_ON_RISING_EDGE;
			break;
		case COUNTER_FALLING_MODE:
			gu8_timer0Timer1PreScaler = TIMER_CLOCK_ON_FALLING_EDGE;
			break;
		default:
			au8_Ret = E_NOK;
			break;
		}
		/* A switch case to decide whether to operate in interrupt mode or polling mode */
		switch(Timer_cfg->Timer_Polling_Or_Interrupt)
		{
		case TIMER_POLLING_MODE:
			CLEAR_BIT(TIMSK_R, OCIE0);
			break;
		case TIMER_INTERRUPT_MODE:
			SET_BIT(TIMSK_R, OCIE0);
			break;
		default:
			au8_Ret = E_NOK;
			break;
		}
		break;
	case TIMER_CH1:
		/* Non-PWM mode */
		SET_BIT(TCCR1A_R, FOC1A);

		/* Choose CTC mode */
		SET_BIT(TCCR1B_R, WGM12);

		/* A switch case to decide which mode to be operating at */
		switch(Timer_cfg->Timer_Mode)
		{
		case TIMER_MODE:
			gu8_timer0Timer1PreScaler = Timer_cfg->Timer_Prescaler;
			break;
		case COUNTER_RISING_MODE:
			gu8_timer0Timer1PreScaler = TIMER_CLOCK_ON_RISING_EDGE;
			break;
		case COUNTER_FALLING_MODE:
			gu8_timer0Timer1PreScaler = TIMER_CLOCK_ON_FALLING_EDGE;
			break;
		default:
			au8_Ret = E_NOK;
			break;
		}
		/* A switch case to decide whether to operate in interrupt mode or polling mode */
		switch(Timer_cfg->Timer_Polling_Or_Interrupt)
		{
		case TIMER_POLLING_MODE:
			CLEAR_BIT(TIMSK_R, OCIE1A);
			break;
		case TIMER_INTERRUPT_MODE:
			SET_BIT(TIMSK_R, OCIE1A);
			break;
		default:
			au8_Ret = E_NOK;
			break;
		}
		break;
	case TIMER_CH2:
		/* Non-PWM mode */
		SET_BIT(TCCR2_R, FOC2);

		/* Choose CTC mode */
		SET_BIT(TCCR2_R, WGM21);

		/* A switch case to decide which mode to be operating at */
		switch(TIMER_MODE)
		{
		case TIMER_MODE:
			gu8_timer2PreScaler = Timer_cfg->Timer_Prescaler;
			break;
		default:
			au8_Ret = E_NOK;
			break;
		}
		/* A switch case to decide whether to operate in interrupt mode or polling mode */
		switch(Timer_cfg->Timer_Polling_Or_Interrupt)
		{
		case TIMER_POLLING_MODE:
			CLEAR_BIT(TIMSK_R, OCIE2);
			break;
		case TIMER_INTERRUPT_MODE:
			SET_BIT(TIMSK_R, OCIE2);
			break;
		default:
			au8_Ret = E_NOK;
			break;
		}
		break;
	default:
		au8_Ret = E_NOK;
		break;
	}

	return au8_Ret;
}

ERROR_STATUS Timer_SetCallBack(Timer_cfg_s* Timer_cfg)
{
	uint8_t au8_Ret = E_OK;
	/* A switch case to check which timer to set its call back operation */
	switch(Timer_cfg->Timer_CH_NO)
	{
	case TIMER_CH0:
		g_T0_CTC_callBackPtr = (volatile void (*)(void))(Timer_cfg->Timer_Cbk_ptr);
		break;
	case TIMER_CH1:
		g_T1_CTC_A_callBackPtr = (volatile void (*)(void))(Timer_cfg->Timer_Cbk_ptr);
		break;
	case TIMER_CH2:
		g_T2_CTC_callBackPtr = (volatile void (*)(void))(Timer_cfg->Timer_Cbk_ptr);
		break;
	default:
		au8_Ret = E_NOK;
		break;
	}

	return au8_Ret;
}

ERROR_STATUS Timer_Start(uint8_t Timer_CH_NO, uint16_t Timer_Count)
{
	uint8_t au8_Ret = E_OK;
	/* Local variables to store the value of the prescaler bits in the timer/counter control registers */
	uint8_t au8_t01PreScaler_temp = 0;
	uint8_t au8_t2PreScaler_temp = 0;

	/* A switch case to choose the prescaler of timer0 and timer1 */
	switch(gu8_timer0Timer1PreScaler)
	{
	case TIMER_NO_CLOCK:
		au8_t01PreScaler_temp = TIMER01_NO_CLOCK;
		break;
	case TIMER_PRESCALER_NO:
		au8_t01PreScaler_temp = TIMER01_NO_PRESCALER;
		break;
	case TIMER_PRESCALER_8:
		au8_t01PreScaler_temp = TIMER01_8_PRESCALER;
		break;
	case TIMER_PRESCALER_64:
		au8_t01PreScaler_temp = TIMER01_64_PRESCALER;
		break;
	case TIMER_PRESCALER_256:
		au8_t01PreScaler_temp = TIMER01_256_PRESCALER;
		break;
	case TIMER_PRESCALER_1024:
		au8_t01PreScaler_temp = TIMER01_1024_PRESCALER;
		break;
	default:
		au8_Ret = E_NOK;
		break;
	}

	/* A switch case to choose the prescaler of timer2 */
	switch(gu8_timer2PreScaler)
	{
	case TIMER_NO_CLOCK:
		au8_t2PreScaler_temp = TIMER2_NO_CLOCK;
		break;
	case TIMER_PRESCALER_NO:
		au8_t2PreScaler_temp = TIMER2_NO_PRESCALER;
		break;
	case TIMER_PRESCALER_8:
		au8_t2PreScaler_temp = TIMER2_8_PRESCALER;
		break;
	case TIMER_PRESCALER_32:
		au8_t2PreScaler_temp = TIMER2_32_PRESCALER;
		break;
	case TIMER_PRESCALER_64:
		au8_t2PreScaler_temp = TIMER2_64_PRESCALER;
		break;
	case TIMER_PRESCALER_128:
		au8_t2PreScaler_temp = TIMER2_128_PRESCALER;
		break;
	case TIMER_PRESCALER_256:
		au8_t2PreScaler_temp = TIMER2_256_PRESCALER;
		break;
	case TIMER_PRESCALER_1024:
		au8_t2PreScaler_temp = TIMER2_1024_PRESCALER;
		break;
	default:
		au8_Ret = E_NOK;
		break;
	}

	/* A switch case to decide which timer to start */
	switch(Timer_CH_NO)
	{
	case TIMER_CH0:
		/* Providing the chosen prescaler value to the timer/counter control register */
		TCCR0_R = (TCCR0_R & TIMER_PRESCALER_MASK) | au8_t01PreScaler_temp;
		/* Providing the output compare value for CTC mode */
		OCR0_R = (uint8_t)Timer_Count;
		break;
	case TIMER_CH1:
		/* Providing the chosen prescaler value to the timer/counter control register */
		TCCR1B_R = (TCCR1B_R & TIMER_PRESCALER_MASK) | au8_t01PreScaler_temp;
		/* Providing the output compare value for CTC mode */
		OCR1A_R = Timer_Count;
		break;
	case TIMER_CH2:
		/* Providing the chosen prescaler value to the timer/counter control register */
		TCCR2_R = (TCCR2_R & TIMER_PRESCALER_MASK) | au8_t2PreScaler_temp;
		/* Providing the output compare value for CTC mode */
		OCR2_R = (uint8_t)Timer_Count;
		break;
	default:
		au8_Ret = E_NOK;
		break;
	}

	return au8_Ret;
}

ERROR_STATUS Timer_Stop(uint8_t Timer_CH_NO)
{
	uint8_t au8_Ret = E_OK;
	/* A switch case to decide which timer to be stopped */
	switch(Timer_CH_NO)
	{
	case TIMER_CH0:
		/* Clearing the prescaler bits the timer/counter control register */
		CLEAR_BIT(TCCR0_R, CS00);
		CLEAR_BIT(TCCR0_R, CS01);
		CLEAR_BIT(TCCR0_R, CS02);
		/* Zeroing the timer/counter ticks for the next start operation */
		TCNT0_R = 0;
		break;
	case TIMER_CH1:
		/* Clearing the prescaler bits the timer/counter control register */
		CLEAR_BIT(TCCR1B_R, CS10);
		CLEAR_BIT(TCCR1B_R, CS11);
		CLEAR_BIT(TCCR1B_R, CS12);
		/* Zeroing the timer/counter ticks for the next start operation */
		TCNT1_R = 0;
		break;
	case TIMER_CH2:
		/* Clearing the prescaler bits the timer/counter control register */
		CLEAR_BIT(TCCR2_R, CS20);
		CLEAR_BIT(TCCR2_R, CS21);
		CLEAR_BIT(TCCR2_R, CS22);
		/* Zeroing the timer/counter ticks for the next start operation */
		TCNT2_R = 0;
		break;
	default:
		au8_Ret = E_NOK;
		break;
	}

	return au8_Ret;
}

ERROR_STATUS Timer_GetStatus(uint8_t Timer_CH_NO, bool* Data)
{
	uint8_t au8_Ret = E_OK;
	/* A switch case to decide which timer to get its status */
	switch(Timer_CH_NO)
	{
	case TIMER_CH0:
		*Data = BIT_IS_SET(TIFR_R, OCF0);
		break;
	case TIMER_CH1:
		*Data = BIT_IS_SET(TIFR_R, OCF1A);
		break;
	case TIMER_CH2:
		*Data = BIT_IS_SET(TIFR_R, OCF2);
		break;
	default:
		au8_Ret = E_NOK;
		break;
	}

	return au8_Ret;
}

ERROR_STATUS Timer_GetValue(uint8_t Timer_CH_NO, uint16_t* Data)
{
	uint8_t au8_Ret = E_OK;
	/* A switch case to decide which timer to get its counter current value */
	switch(Timer_CH_NO)
	{
	case TIMER_CH0:
		*Data = TCNT0_R;
		break;
	case TIMER_CH1:
		*Data = TCNT1_R;
		break;
	case TIMER_CH2:
		*Data = TCNT2_R;
		break;
	default:
		au8_Ret = E_NOK;
		break;
	}

	return au8_Ret;
}

ERROR_STATUS Timer_SetValue(uint8_t Timer_CH_NO, uint16_t Data)
{
	uint8_t au8_Ret = E_OK;
	/* A switch case to decide which timer to set its counter value */
	switch(Timer_CH_NO)
	{
	case TIMER_CH0:
		TCNT0_R = (uint8_t)Data;
		break;
	case TIMER_CH1:
		TCNT1_R = Data;
		break;
	case TIMER_CH2:
		TCNT2_R = (uint8_t)Data;
		break;
	default:
		au8_Ret = E_NOK;
		break;
	}

	return au8_Ret;
}





