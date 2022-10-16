/*
 * Pin.cpp
 *
 *  Created on: 16 Oct 2022
 *      Author: PeterMarczis
 */

#include "Pin.h"

Pin::Pin(GPIO_TypeDef* _gpio, uint16_t _pin)
	:gpio(_gpio)
	,pin(_pin)
{}

void Pin::set()
{
	HAL_GPIO_WritePin(gpio, pin, GPIO_PIN_SET);
}

void Pin::reset()
{
	HAL_GPIO_WritePin(gpio, pin, GPIO_PIN_RESET);
}

bool Pin::is_pressed()
{
	return !HAL_GPIO_ReadPin(gpio, pin);
}
