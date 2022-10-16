/*
 * BTNHandler.h
 *
 *  Created on: 16 Oct 2022
 *      Author: PeterMarczis
 */

#ifndef BTNHANDLER_H_
#define BTNHANDLER_H_

#include "Pin.h"

#define NUM_OF_BTNS 6

class BTNAction {
public:
	BTNAction();
	virtual ~BTNAction();
	virtual void trigger(); //When the button pressed this will be called
};

class BTNHandler {
private:
	Pin btns[NUM_OF_BTNS];
	BTNAction actions[16];

public:
	BTNHandler(
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
	);
	virtual ~BTNHandler();
	void update();
};

#endif /* BTNHANDLER_H_ */
