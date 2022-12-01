/*
 * Effects.cpp
 *
 *  Created on: 16 Oct 2022
 *      Author: PeterMarczis
 */

#include "Effects.h"

Effects::Effects(
			uint32_t _ch
		   ,Display &_display
		   ,uint32_t &_param_a
		   ,GPIO_TypeDef *_led_param_a_gpio
		   ,uint16_t _led_param_a_pin
		   ,uint32_t &_param_b
		   ,GPIO_TypeDef *_led_param_b_gpio
		   ,uint16_t _led_param_b_pin
		   )
	:MultiOption(2)
	,ch(_ch)
	,display(_display)
	,param_a(_param_a)
	,led_param_a_gpio(_led_param_a_gpio)
	,led_param_a_pin(_led_param_a_pin)
	,param_b(_param_b)
	,led_param_b_gpio(_led_param_b_gpio)
	,led_param_b_pin(_led_param_b_pin)
{

}

void Effects::handler()
{
	display.set_wt_table(Display::Tables::EFFECTS, get_ch(), get_act());
	setLEDs();
}

void Effects::error_handler() {
	__disable_irq();
	while(1) {
	}
}

void Effects::setLEDs() {
	HAL_GPIO_WritePin(led_param_a_gpio, led_param_a_pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(led_param_b_gpio, led_param_b_pin, GPIO_PIN_RESET);
	switch (get_modifier().get_lednum()) {
		case WaveModifier::PARAM_NO:
			return; //They already off
		case WaveModifier::PARAM_ONE:
			HAL_GPIO_WritePin(led_param_a_gpio, led_param_a_pin, GPIO_PIN_SET);
			return;
		case WaveModifier::PARAM_TWO:
			HAL_GPIO_WritePin(led_param_a_gpio, led_param_a_pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(led_param_b_gpio, led_param_b_pin, GPIO_PIN_SET);
			return;
		default:
			return; //Shall not happen
	}
}

WaveModifier& Effects::get_modifier()
{
//So we need this - as we don't have vectors, and we can't have an array of references,
//and we would pretty much shoot ourselves in the foot with pointers.

	switch (get_act()) {
		case 0:
			return e_no;
		case 1:
			return e_dio;
	}
	return e_no;
}

// Modifiers from here on
uint32_t EDiode::modify(uint32_t i) {
	if (i < 2048) { //Note 2047 is 0V output, because of the AC coupling on the output
		return 0;
	}
	return i;
}
