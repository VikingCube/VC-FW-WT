/*
 * Pin.h
 *
 *  Created on: 16 Oct 2022
 *      Author: PeterMarczis
 */

#ifndef PIN_H_
#define PIN_H_

#include "stm32f4xx_hal.h"

class Pin {
private:
	GPIO_TypeDef* gpio;
	uint16_t pin;
public:
	Pin(GPIO_TypeDef* _gpio, uint16_t _pin);
	void set();
	void reset();
	bool is_pressed();
};

#endif /* PIN_H_ */
