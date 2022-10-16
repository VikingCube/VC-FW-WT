/*
 * BTNHandler.cpp
 *
 *  Created on: 16 Oct 2022
 *      Author: PeterMarczis
 */

#include "BTNHandler.h"

BTNHandler::BTNHandler(
		GPIO_TypeDef *btn0_prt, uint16_t btn0_pin
		,GPIO_TypeDef *btn1_prt, uint16_t btn1_pin
		,GPIO_TypeDef *btn2_prt, uint16_t btn2_pin
		,GPIO_TypeDef *btn3_prt, uint16_t btn3_pin
		,GPIO_TypeDef *btn4_prt, uint16_t btn4_pin
		,GPIO_TypeDef *btn5_prt, uint16_t btn5_pin
		,BTNAction a0
		,BTNAction a1
		,BTNAction a2
		,BTNAction a3
		,BTNAction a4
		,BTNAction a5
		,BTNAction a6
		,BTNAction a7
		,BTNAction a8
		,BTNAction a9
		,BTNAction a10
		,BTNAction a11
		,BTNAction a12
		,BTNAction a13
		,BTNAction a14
		,BTNAction a15
):
	 btns{
		Pin(btn0_prt, btn0_pin)
		,Pin(btn1_prt, btn1_pin)
		,Pin(btn2_prt, btn2_pin)
		,Pin(btn3_prt, btn3_pin)
		,Pin(btn4_prt, btn4_pin)
		,Pin(btn5_prt, btn5_pin)
	},
	actions{
		a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15
	}
{
	// TODO Auto-generated constructor stub
}

BTNHandler::~BTNHandler() {
	// TODO Auto-generated destructor stub
}

void BTNHandler::update() {
	//Check Shift states
	bool s1 = btns[4].is_pressed();
	bool s2 = btns[5].is_pressed();

	int action = -1;

	for(int i = 0; i < 4 ; i++) { //4 button + 2 shift button
		if (btns[i].is_pressed()) {
			action = i + s1?4:0 + s2?8:0;
			actions[action].trigger();
			while(btns[i].is_pressed()) {} //Wait for user to release the btn
			break;
		}
	}
}

