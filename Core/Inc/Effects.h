/*
 * Effects.h
 *
 *  Created on: 16 Oct 2022
 *      Author: PeterMarczis
 */

#ifndef EFFECTS_H_
#define EFFECTS_H_
#include "MultiOption.h"
#include "Display.h"
#include "stm32f4xx_hal.h"

class WaveModifier
{
public:
	enum param_t { PARAM_NO, PARAM_ONE, PARAM_TWO };
private:
	param_t param = PARAM_NO;
public:
	WaveModifier(param_t _param):param(_param) {};
	~WaveModifier() {};
	virtual uint32_t modify(uint32_t i) = 0; //Must return  the value we will copy into the DAC buffer
	param_t get_lednum() { return param; };
};


class NoEffect : public WaveModifier {
public:
	NoEffect():WaveModifier(WaveModifier::PARAM_NO) {};
	uint32_t modify(uint32_t i) { return i; };
};

class EDiode : public WaveModifier {
public:
	EDiode():WaveModifier(WaveModifier::PARAM_ONE) {};
	uint32_t modify(uint32_t i);
};

class Effects : public MultiOption
{
private:
	uint32_t ch;
//Effects
	NoEffect e_no;
	EDiode   e_dio;
	uint32_t &param_a;
	GPIO_TypeDef *led_param_a_gpio;
	uint16_t led_param_a_pin;
	GPIO_TypeDef *led_param_b_gpio;
	uint16_t led_param_b_pin;
	uint32_t &param_b;



	Display &display;
	uint32_t get_ch() { return ch; };
	void error_handler();
	void setLEDs();

public:
	Effects(
			uint32_t ch
		   ,Display &_display
		   ,uint32_t &_param_a
		   ,GPIO_TypeDef *_led_param_a_gpio
		   ,uint16_t _led_param_a_pin
		   ,uint32_t &_param_b
		   ,GPIO_TypeDef *_led_param_b_pgio
		   ,uint16_t _led_param_b_pin
		   );
	~Effects() {};
	void handler();
	WaveModifier& get_modifier();
};

#endif /* EFFECTS_H_ */
