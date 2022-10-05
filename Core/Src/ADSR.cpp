/*
 * ADSR.cpp
 *
 *  Created on: Jul 13, 2022
 *      Author: PeterMarczis
 */

#include <ADSR.h>

ADSR::ADSR(uint32_t _ch
		,GPIO_TypeDef  *_led_a_gpio
		,uint16_t	   _led_a_pin
		,GPIO_TypeDef  *_led_d_gpio
		,uint16_t	   _led_d_pin
		,GPIO_TypeDef  *_led_s_gpio
		,uint16_t	   _led_s_pin
		,GPIO_TypeDef  *_led_r_gpio
		,uint16_t	   _led_r_pin
	)
		:ch(_ch)
		,led_a_gpio(_led_a_gpio)
		,led_a_pin(_led_a_pin)
		,led_d_gpio(_led_d_gpio)
		,led_d_pin(_led_d_pin)
		,led_s_gpio(_led_s_gpio)
		,led_s_pin(_led_s_pin)
		,led_r_gpio(_led_r_gpio)
		,led_r_pin(_led_r_pin)
{
}

ADSR::~ADSR() {
	// TODO Auto-generated destructor stub
}

void ADSR::setLED(LEDS led)
{
	//Turn off all
	HAL_GPIO_WritePin(led_a_gpio, led_a_pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(led_d_gpio, led_d_pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(led_s_gpio, led_s_pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(led_r_gpio, led_r_pin, GPIO_PIN_RESET);

	switch (led) {
		case LED_A:
			HAL_GPIO_WritePin(led_a_gpio, led_a_pin, GPIO_PIN_SET);
			break;

		case LED_D:
			HAL_GPIO_WritePin(led_d_gpio, led_d_pin, GPIO_PIN_SET);
			break;

		case LED_S:
			HAL_GPIO_WritePin(led_s_gpio, led_s_pin, GPIO_PIN_SET);
			break;

		case LED_R:
			HAL_GPIO_WritePin(led_r_gpio, led_r_pin, GPIO_PIN_SET);
			break;
	}
}

void ADSR::tick()
{
	//Linear ADSR
	t++; //Increase tick
	float res;
	if (t <= a) {
		//Attack phase
		res = 255/a*t;
		setLED(LED_A);
	} else if ((t-a) < d) {
		//Decay phase
		res = 255-((255-(0xFF*float(s)/100))/d*(t-a));
		setLED(LED_D);
	} else if (output) {
		//Sustain phase
		res = 0xFF*(float(s)/100);
		setLED(LED_S);
	} else if (relt < r) {
		//Release phase
		relt++;
		uint32_t rt = r-relt;
		res = (0xFF*float(s)/100)*(float(rt)/float(r));
		setLED(LED_R);
	} else {
		res = 0;
	}

	//Pick DAC
	if (ch == 0) HAL_GPIO_WritePin(DAC_AB_GPIO_Port, DAC_AB_Pin, GPIO_PIN_RESET);
	if (ch == 1) HAL_GPIO_WritePin(DAC_AB_GPIO_Port, DAC_AB_Pin, GPIO_PIN_SET);
	//Write Data
	DAC_DATA_GPIO->ODR = uint32_t(res);
	//DAC_DATA_GPIO->ODR = 0x00FF;
	//CS
	HAL_GPIO_WritePin(DAC_CS_GPIO_Port, DAC_CS_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DAC_CS_GPIO_Port, DAC_CS_Pin, GPIO_PIN_SET);
}

void ADSR::note_on()
{
	output = true;
	t = 0;
}

void ADSR::note_off()
{
	output = false;
	relt = 0;
	t = a+d+1; //So it jumps to release phase
}

void ADSR::setA(float _a) { a = _a; }
void ADSR::setD(float _d) { d = _d; }
void ADSR::setS(uint32_t _s) { s = _s; }
void ADSR::setR(float _r) { r = _r; }
