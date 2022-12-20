/*
 * Effects.cpp
 *
 *  Created on: 16 Oct 2022
 *      Author: PeterMarczis
 */

#include "Effects.h"
#include "Utility.h"

Effects::Effects(
			uint32_t _ch
		   ,Display &_display
		   ,ADSR &_adsr
		   ,uint32_t &_param_a
		   ,GPIO_TypeDef *_led_param_a_gpio
		   ,uint16_t _led_param_a_pin
		   ,uint32_t &_param_b
		   ,GPIO_TypeDef *_led_param_b_gpio
		   ,uint16_t _led_param_b_pin
		   )
	:MultiOption(5) //TODO <<---- THIS IS THE ONE YOU SEARCH FOR WHEN YOU ADD NEW "EFFECTS"
	,ch(_ch)
	,display(_display)
	,e_no(WaveModifier::PARAM_NO, _param_a, _led_param_a_gpio, _led_param_a_pin, _param_b, _led_param_b_gpio, _led_param_b_pin) //TODO make a class for param
	,e_dio(WaveModifier::PARAM_ONE, _param_a, _led_param_a_gpio, _led_param_a_pin, _param_b, _led_param_b_gpio, _led_param_b_pin)
	,e_rdio(WaveModifier::PARAM_ONE, _param_a, _led_param_a_gpio, _led_param_a_pin, _param_b, _led_param_b_gpio, _led_param_b_pin)
	,e_wfold(WaveModifier::PARAM_ONE, _param_a, _led_param_a_gpio, _led_param_a_pin, _param_b, _led_param_b_gpio, _led_param_b_pin)
	,e_fmod(WaveModifier::PARAM_ONE, _param_a, _led_param_a_gpio, _led_param_a_pin, _param_b, _led_param_b_gpio, _led_param_b_pin, _adsr)
{

}

void Effects::handler()
{
	display.set_wt_table(Display::Tables::EFFECTS, get_ch(), get_act());
	get_modifier().setLEDs();
	get_modifier().reset();
}

void Effects::error_handler() {
	__disable_irq();
	while(1) {
	}
}

void WaveModifier::setLEDs()
{
	HAL_GPIO_WritePin(led_param_a_gpio, led_param_a_pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(led_param_b_gpio, led_param_b_pin, GPIO_PIN_RESET);
	switch (param) {
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

bool WaveModifier::uptodate()
{
	if (param == PARAM_NO && !need_update) return true;
	if (need_update
		|| (param_a+50 > param_a_old) || (param_a-50 < param_a_old)
		|| (param_b+50 > param_b_old) || (param_b-50 < param_b_old)
	) {
		need_update = false;
		param_a_old = param_a;
		param_b_old = param_b;
		return false;
	}
	return true;
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
		case 2:
			return e_rdio;
		case 3:
			return e_wfold;
		case 4:
			return e_fmod;
	}
	return e_no;
}

// Modifiers from here on
uint32_t EDiode::modify(uint32_t i) {
	if (i < param_a) { //Note 2047 is 0V output, because of the AC coupling on the output
		return 0;
	}
	return i;
}

uint32_t ERDiode::modify(uint32_t i) {
	if (i > param_a) { //Note 2047 is 0V output, because of the AC coupling on the output
		return 0;
	}
	return i;
}

uint32_t WFolder::modify(uint32_t i) {
	uint32_t x1 = 2047+(param_a>>1);
	uint32_t x2 = 2047-(param_a>>1);

	if (i > 2047) { //Positive
		if ( i < x1 ) return i; //Below the limit
		return x1-(i-x1); //Above the limit flip
	}
	//Negative
	if ( i > param_a ) return i; //Above the limit
	//Below the limit flip
	return x2+(x2-i);
}

bool FMod::uptodate()
{
	if (param == PARAM_NO && !need_update) return true;
	if (need_update
		|| (param_a+50 > param_a_old) || (param_a-50 < param_a_old)
		|| (param_b+50 > param_b_old) || (param_b-50 < param_b_old)
	) {
		need_update = false;
		param_a_old = param_a;
		param_b_old = param_b;
		adsr.set_freq_mod(Utility::p_m_param(param_a));
		return false;
	}
	return false; //This never needs to update the wave
}
