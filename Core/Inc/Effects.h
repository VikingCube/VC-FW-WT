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
protected:
	uint32_t &param_a;
	uint32_t &param_b;
private:
	param_t param = PARAM_NO;


	uint32_t param_a_old;
	GPIO_TypeDef *led_param_a_gpio;
	uint16_t led_param_a_pin;


	uint32_t param_b_old;
	GPIO_TypeDef *led_param_b_gpio;
	uint16_t led_param_b_pin;

	bool need_update = true;


public:
	WaveModifier(
			param_t _param
		   ,uint32_t &_param_a
		   ,GPIO_TypeDef *_led_param_a_gpio
		   ,uint16_t _led_param_a_pin
		   ,uint32_t &_param_b
		   ,GPIO_TypeDef *_led_param_b_pgio
		   ,uint16_t _led_param_b_pin
    			):
    		param(_param)
		   ,param_a(_param_a)
		   ,led_param_a_gpio(_led_param_a_gpio)
		   ,led_param_a_pin(_led_param_a_pin)
		   ,param_b(_param_b)
		   ,led_param_b_gpio(_led_param_b_pgio)
		   ,led_param_b_pin(_led_param_b_pin)
			    {};

	~WaveModifier() {};
	virtual uint32_t modify(uint32_t i) = 0; //Must return  the value we will copy into the DAC buffer
	void setLEDs();
	bool uptodate(); //Checks if params changed
	void reset() { need_update = true; };
};


class NoEffect : public WaveModifier {
public:
	using WaveModifier::WaveModifier;
	uint32_t modify(uint32_t i) { return i; };
};

class EDiode : public WaveModifier {
public:
	using WaveModifier::WaveModifier;
	uint32_t modify(uint32_t i);
};

class ERDiode : public WaveModifier {
public:
	using WaveModifier::WaveModifier;
	uint32_t modify(uint32_t i);
};

class WFolder : public WaveModifier {
public:
	using WaveModifier::WaveModifier;
	uint32_t modify(uint32_t i);
};



class Effects : public MultiOption
{
private:
	uint32_t ch;

	//Effects
	NoEffect e_no;
	EDiode   e_dio;
	ERDiode  e_rdio;
	WFolder  e_wfold;

	Display &display;
	uint32_t get_ch() { return ch; };
	void error_handler();

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
