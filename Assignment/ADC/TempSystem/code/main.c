/*
 * main.c
 *
 *  Created on: FEB 14, 2024
 *      Author: AHMED FAHEEM
 */

#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "PORT_interface.h"
#include "ADC_interface.h"
#include "LM35_interface.h"
#include <util/delay.h>
#include "ErrType.h"
#include "CLCD_interface.h"
void main(void){

	PORT_voidInit();
	ADC_voidInit();
	CLCD_voidInit();

	uint8 TempVal = 0;
	CLCD_u8SendString("Temperature= ");
	while(1){
		TempVal = LM34_u8GetTempInC(ADC_u8SINGLE_ENDED_ADC7);
		CLCD_voidGoToXY(12,0);
		if(TempVal<10){
			CLCD_u8SendString(" ");
			CLCD_u8SendString(" ");
			CLCD_u8SendString(" ");
			CLCD_voidGoToXY(12,0);
			CLCD_u8SendNumber((uint32)TempVal);
			CLCD_u8SendString("C");
		}else if(TempVal >= 10){
			CLCD_voidGoToXY(12,0);
			CLCD_u8SendNumber((uint32)TempVal);
			CLCD_u8SendString("C");
		}

		_delay_ms(1000);


	}



}


