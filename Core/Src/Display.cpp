/*
 * Display.cpp
 *
 *  Created on: 6 Oct 2022
 *      Author: PeterMarczis
 */

#include "Display.h"

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

Display::Display()
	:leds{
		 Pin(LED0_GPIO_Port, LED0_Pin)
		,Pin(LED1_GPIO_Port, LED1_Pin)
		,Pin(LED2_GPIO_Port, LED2_Pin)
		,Pin(LED3_GPIO_Port, LED3_Pin)
		,Pin(LED4_GPIO_Port, LED4_Pin)
		,Pin(LED5_GPIO_Port, LED5_Pin)
		,Pin(LED6_GPIO_Port, LED6_Pin)
		,Pin(LED7_GPIO_Port, LED7_Pin)

		,Pin(LED8_GPIO_Port,  LED8_Pin)
		,Pin(LED9_GPIO_Port,  LED9_Pin)
		,Pin(LED10_GPIO_Port, LED10_Pin)
		,Pin(LED11_GPIO_Port, LED11_Pin)
		,Pin(LED12_GPIO_Port, LED12_Pin)
		,Pin(LED13_GPIO_Port, LED13_Pin)
		,Pin(LED14_GPIO_Port, LED14_Pin)
		,Pin(LED15_GPIO_Port, LED15_Pin)

		,Pin(LED16_GPIO_Port, LED16_Pin)
		,Pin(LED17_GPIO_Port, LED17_Pin)
	}
{
	leds_off();
}

Display::~Display() {
	// TODO Auto-generated destructor stub
}

void Display::update()
{
	leds_off();
	switch (state) {
		case TABLE:
			//Set CH0
			leds[table[0]].set();
			leds[table[1]+8].set();
			break;
		case ADSR:
			break;
		default:
			leds_off();
	}
}

void Display::leds_off()
{
	HAL_GPIO_TogglePin(LED16_GPIO_Port, LED16_Pin);
	for (Pin i : leds) {
		i.reset();
	}
}
