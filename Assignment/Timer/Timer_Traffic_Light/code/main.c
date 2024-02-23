/*
 * main.c
 *
 *  Created on: Nov 2, 2023
 *      Author: AHMED FAHEEM
 */

#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "PORT_interface.h"
#include <util/delay.h>
#include "ErrType.h"
#include "BIT_MATH.h"
#include "GIE_interface.h"
#include "TIMER_interface.h"
#include "EXTI_interface.h"
#include "LED_interface.h"
#include "SWITCH_interface.h"

#define RED_LED       0u
#define YELLOW_LED    1u
#define GREEN_LED     2u

#define PRESSED_MODE   0u
#define NORMAL_MODE    1u
void Timer0_Traffic(void);
static LED_Confg_t  Local_u8RedLed = {
		.LED_u8ActiveType =ACT_HIGH,
		.LED_u8Port = DIO_u8PORTC,
		.LED_u8Pin = DIO_u8PIN0
};

static 	LED_Confg_t  Local_u8GreenLed = {
		.LED_u8ActiveType =ACT_HIGH,
		.LED_u8Port = DIO_u8PORTC,
		.LED_u8Pin = DIO_u8PIN2
};

static 	LED_Confg_t  Local_u8YellowLed = {
		.LED_u8ActiveType =ACT_HIGH,
		.LED_u8Port = DIO_u8PORTC,
		.LED_u8Pin = DIO_u8PIN1
};

static LED_Confg_t  Local_s8PedRedLed = {
		.LED_u8ActiveType =ACT_HIGH,
		.LED_u8Port = DIO_u8PORTC,
		.LED_u8Pin = DIO_u8PIN3
};

static 	LED_Confg_t  Local_s8PedGreenLed = {
		.LED_u8ActiveType =ACT_HIGH,
		.LED_u8Port = DIO_u8PORTC,
		.LED_u8Pin = DIO_u8PIN4
};

static 	LED_Confg_t  Local_sPedYellowLed = {
		.LED_u8ActiveType =ACT_HIGH,
		.LED_u8Port = DIO_u8PORTC,
		.LED_u8Pin = DIO_u8PIN5
};

static SW_Config_t Local_sBtn ={
		.SWITCH_u8Type =PULL_UP,
		.SWITCH_u8Port = DIO_u8PORTD,
		.SWITCH_u8Pin = DIO_u8PIN2
};

static uint8 BtnState = SW_RELEASES;

void main(void){


	TIMER0_cfg_t  Local_sTimer0_Cfg = { .WFG_Mode = T0_COMPARE_MATCH,
			.Prescaler = TIMER_PRESCALER_DIVISION_1024,
			.Out_HW_Opt = T0_OC0_DISCONNECT,
			.INT_State =  T0_INT_COMPARE,
	};


	PORT_voidInit();
	TIMER0_u8Init(&Local_sTimer0_Cfg);
	TIMER0_voidSetCompareValue(210);
	TIMER_u8SetCallBackFunc(TIMER0_OC_INT,Timer0_Traffic);
	GIE_voidEnableGlobal();

	while(1){


		SWITCH_u8GetState(&Local_sBtn,&BtnState);


	}


}



void Timer0_Traffic(void){
	volatile static uint16 Ccomp = 371;
	volatile static uint32 Ccomp2 = 0;
	static uint8 BtnFlag = NORMAL_MODE;
	volatile static uint8 CarLedFlag = RED_LED;

	Ccomp++;
	Ccomp2++;



	if(BtnState == SW_PRESSED){
		BtnFlag = PRESSED_MODE;
		Ccomp2 = 0;
	}


	if(BtnFlag == PRESSED_MODE){

		if(CarLedFlag == RED_LED){

			LED_u8SetOn(&Local_u8RedLed);
			LED_u8SetOn(&Local_s8PedGreenLed);

			if(Ccomp2 == 372){  /* After 5 Second */

				Ccomp = 1488; /* Go to ON Yellow for 5 Second*/
				BtnFlag  = NORMAL_MODE;
				Ccomp2 = 0;
			}

		}else if( (CarLedFlag == YELLOW_LED) || (CarLedFlag == GREEN_LED) ){
			LED_u8SetOff(&Local_u8YellowLed);
			LED_u8SetOff(&Local_sPedYellowLed);
			LED_u8SetOff(&Local_u8RedLed);
			LED_u8SetOff(&Local_u8GreenLed);
			LED_u8SetOff(&Local_s8PedGreenLed);
			LED_u8SetOn(&Local_s8PedRedLed);
			/*Blink Yellow every 1 Second */
			if(Ccomp2 == 74){
				LED_u8Toggle(&Local_u8YellowLed);
				LED_u8Toggle(&Local_sPedYellowLed);
			}else if (Ccomp2 == 148){

				LED_u8Toggle(&Local_u8YellowLed);
				LED_u8Toggle(&Local_sPedYellowLed);
			}else if(Ccomp2 == 222){
				LED_u8Toggle(&Local_u8YellowLed);
				LED_u8Toggle(&Local_sPedYellowLed);
			}else if(Ccomp2 == 296){
				LED_u8Toggle(&Local_u8YellowLed);
				LED_u8Toggle(&Local_sPedYellowLed);
			}else if(Ccomp2 == 370){
				LED_u8Toggle(&Local_u8YellowLed);
				LED_u8Toggle(&Local_sPedYellowLed);
			}else if(Ccomp2 == 371){ /* After 5 Second*/
				LED_u8SetOff(&Local_s8PedRedLed);
				LED_u8SetOff(&Local_u8YellowLed);
				LED_u8SetOff(&Local_sPedYellowLed);
				CarLedFlag = YELLOW_LED;
				Ccomp = 1116;   /* Go to ON Yellow for 5 Second*/
				BtnFlag  = NORMAL_MODE;
				Ccomp2 = 0;
			}
		}
	}


/* 5 Second Take 372 Count*/

	if(BtnFlag == NORMAL_MODE){
		if(Ccomp == 372){
			LED_u8SetOff(&Local_u8YellowLed);
			LED_u8SetOff(&Local_sPedYellowLed);
			LED_u8SetOn(&Local_u8GreenLed);
			LED_u8SetOn(&Local_s8PedRedLed);

			CarLedFlag = GREEN_LED;

		}else if(Ccomp == 744){
			LED_u8SetOff(&Local_u8GreenLed);
			LED_u8SetOff(&Local_s8PedRedLed);
			LED_u8SetOn(&Local_u8YellowLed);
			LED_u8SetOn(&Local_sPedYellowLed);
			CarLedFlag = YELLOW_LED;

		}else if(Ccomp == 1116){
			LED_u8SetOff(&Local_u8YellowLed);
			LED_u8SetOff(&Local_sPedYellowLed);
			LED_u8SetOn(&Local_u8RedLed);
			LED_u8SetOn(&Local_s8PedGreenLed);
			CarLedFlag = RED_LED;
		}else if(Ccomp ==1488){
			LED_u8SetOff(&Local_u8RedLed);
			LED_u8SetOff(&Local_s8PedGreenLed);
			LED_u8SetOn(&Local_u8YellowLed);
			LED_u8SetOn(&Local_sPedYellowLed);
			CarLedFlag = YELLOW_LED;
			Ccomp = 0;

		}

	}else{
		Ccomp = 0;
	}


}


