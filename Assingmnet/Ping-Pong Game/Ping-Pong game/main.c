/*
 * main.c
 *
 *  Created on: Nov 2, 2023
 *      Author: AHMED FAHEEM
 */

#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "CLCD_interface.h"
#include "GIE_interface.h"
#include "EXTI_interface.h"
#include <util/delay.h>


#define u8BALL_START_POS  1
#define u8BALL_END_POS    14

void vChangePlayerOnePos();
void vChangePlayerTwoPos();
static uint8 Local_u8PlayrOneLine = 0;
static uint8 Local_u8PlayrTwoLine = 0;

void main(void){


	PORT_voidInit();
	CLCD_voidInit();
	GIE_voidEnableGlobal();

	EXTI_voidInit();

	EXTI_u8SetCallBack(INT0, &vChangePlayerOnePos);
	EXTI_u8SetCallBack(INT1, &vChangePlayerTwoPos);

	CLCD_voidGoToXY(0, Local_u8PlayrOneLine);
	CLCD_u8SendString("|");


	CLCD_voidGoToXY(15, Local_u8PlayrTwoLine);
	CLCD_u8SendString("|");


	static uint8 Local_u8PatternRun[8] ={0, 0, 0, 0b00001110, 0b00001110,0,0,0};

	uint8 Local_u8RandomLevel = 0;
	uint8 Local_u8Counter1 = u8BALL_START_POS;


	while(1){


		/* move ball to right*/
		for(; Local_u8Counter1 < u8BALL_END_POS;Local_u8Counter1++){

			GIE_voidDisableGlobal();
			Local_u8RandomLevel = ((Local_u8Counter1) >>Local_u8PlayrTwoLine)%2;

			CLCD_u8SendSpecialCharacter(2,Local_u8PatternRun,Local_u8Counter1,Local_u8RandomLevel);

			_delay_ms(400);


			CLCD_voidGoToXY(Local_u8Counter1,Local_u8RandomLevel);
			CLCD_u8SendString(" ");
			GIE_voidEnableGlobal();



		}

		/*Check if player 2 block the ball  */
		if(Local_u8RandomLevel != Local_u8PlayrTwoLine){

			CLCD_voidSendCmd(CLCD_u8CLEAR_LCD);
			CLCD_voidGoToXY(0, 0);
			CLCD_u8SendString("Player One Win !!");
			break;

		}else{


			/* move ball to left */
			for(Local_u8Counter1 = u8BALL_END_POS -1; Local_u8Counter1 >= u8BALL_START_POS;Local_u8Counter1--){

				GIE_voidDisableGlobal();
				Local_u8RandomLevel = ((Local_u8Counter1) >>Local_u8PlayrOneLine)%2;

				CLCD_u8SendSpecialCharacter(2,Local_u8PatternRun,Local_u8Counter1,Local_u8RandomLevel);

				_delay_ms(400);


				CLCD_voidGoToXY(Local_u8Counter1,Local_u8RandomLevel);
				CLCD_u8SendString(" ");
				GIE_voidEnableGlobal();



			}

			/*Check if player 1 block the ball  */

			if(Local_u8RandomLevel != Local_u8PlayrOneLine){

				CLCD_voidSendCmd(CLCD_u8CLEAR_LCD);
				CLCD_voidGoToXY(0, 0);
				CLCD_u8SendString("Player Two Win !!");
				break;
			}else{
				Local_u8Counter1 = u8BALL_START_POS + 1;
			}



		}



	}



}


void vChangePlayerOnePos(void){
	if(Local_u8PlayrOneLine == 1){
		Local_u8PlayrOneLine = 0;
		CLCD_voidGoToXY(0, 1);
		CLCD_u8SendString(" ");
		CLCD_voidGoToXY(0, 0);
		CLCD_u8SendString("|");

	}else if (Local_u8PlayrOneLine == 0){
		Local_u8PlayrOneLine = 1;
		CLCD_voidGoToXY(0, 0);
		CLCD_u8SendString(" ");
		CLCD_voidGoToXY(0, 1);
		CLCD_u8SendString("|");

	}

}

void vChangePlayerTwoPos(void){
	if(Local_u8PlayrTwoLine == 1){
		Local_u8PlayrTwoLine = 0;
		CLCD_voidGoToXY(15, 1);
		CLCD_u8SendString(" ");
		CLCD_voidGoToXY(15, 0);
		CLCD_u8SendString("|");

	}else if (Local_u8PlayrTwoLine == 0){
		Local_u8PlayrTwoLine = 1;
		CLCD_voidGoToXY(15, 0);
		CLCD_u8SendString(" ");
		CLCD_voidGoToXY(15, 1);
		CLCD_u8SendString("|");

	}

}
