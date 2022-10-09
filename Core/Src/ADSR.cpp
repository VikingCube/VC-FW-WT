/*
 * ADSR.cpp
 *
 *  Created on: Jul 13, 2022
 *      Author: PeterMarczis
 */

#include <ADSR.h>

ADSR::ADSR(uint32_t _ch
		,TIM_HandleTypeDef &_tim
		,GPIO_TypeDef  *_led_a_gpio
		,uint16_t	   _led_a_pin
		,GPIO_TypeDef  *_led_d_gpio
		,uint16_t	   _led_d_pin
		,GPIO_TypeDef  *_led_s_gpio
		,uint16_t	   _led_s_pin
		,GPIO_TypeDef  *_led_r_gpio
		,uint16_t	   _led_r_pin
		,Display      &_display
		,uint32_t      &_ad_a
		,uint32_t      &_ad_d
		,uint32_t      &_ad_s
		,uint32_t      &_ad_r
	)
		:ch(_ch)
		,tim(_tim)
		,led_a_gpio(_led_a_gpio)
		,led_a_pin(_led_a_pin)
		,led_d_gpio(_led_d_gpio)
		,led_d_pin(_led_d_pin)
		,led_s_gpio(_led_s_gpio)
		,led_s_pin(_led_s_pin)
		,led_r_gpio(_led_r_gpio)
		,led_r_pin(_led_r_pin)
		,display(_display)
		,ad_a(_ad_a)
		,ad_d(_ad_d)
		,ad_s(_ad_s)
		,ad_r(_ad_r)
{
}

ADSR::~ADSR() {
	// TODO Auto-generated destructor stub
}

void ADSR::setLED(LEDS led)
{
	//Update display about our changes
	return; //TODO until we get the new LEDS
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

		case LED_OFF:
			break;
	}
}

void ADSR::tick()
{
	//Read the AD Values
	a = float(ad_a/10);
	d = float(ad_d/10);
	s = float(ad_s)/4096*100;
	r = float(ad_r/10);

	//Update display from here
	display.adsr(ch, ad_a, ad_d, ad_s, ad_r);
	//Linear ADSR
	t++; //Increase tick
	float res;
	if (t <= a) {
		//Attack phase
		res = vel/a*t;
		setLED(LED_A);
	} else if ((t-a) < d) {
		//Decay phase
		res = vel-((vel-(vel*float(s)/100))/d*(t-a));
		setLED(LED_D);
	} else if (output) {
		//Sustain phase
		res = vel*(float(s)/100);
		setLED(LED_S);
	} else if (relt < r) {
		//Release phase
		relt++;
		uint32_t rt = r-relt;
		res = (vel*float(s)/100)*(float(rt)/float(r));
		setLED(LED_R);
	} else {
		res = 0;
		setLED(LED_OFF);
		osc_on = false;
	}

	//Pick DAC
	if (ch == 0) HAL_GPIO_WritePin(DAC_AB_GPIO_Port, DAC_AB_Pin, GPIO_PIN_RESET);
	if (ch == 1) HAL_GPIO_WritePin(DAC_AB_GPIO_Port, DAC_AB_Pin, GPIO_PIN_SET);
	//Write Data
	HAL_GPIO_WritePin(DAC_CS_GPIO_Port, DAC_CS_Pin, GPIO_PIN_RESET);
	DAC_DATA_GPIO->ODR = uint8_t(res);
	HAL_GPIO_WritePin(DAC_CS_GPIO_Port, DAC_CS_Pin, GPIO_PIN_SET);
	display.adsr_update_gain(ch, uint8_t(res));
	//DAC_DATA_GPIO->ODR = 0x00FF;
	//CS

}

void ADSR::note_on(uint8_t _note, uint8_t _vel)
{
	output = true;
	t = 0;
	vel = _vel*2;
	HAL_TIM_Base_Stop_IT(&tim);
	tim.Init.Period = midi_to_cnt[_note];
	if (HAL_TIM_Base_Init(&tim) != HAL_OK) { error_handler(); }
    HAL_TIM_Base_Start_IT(&tim);
    osc_on = true;
}

void ADSR::note_off(uint8_t _note)
{
	output = false;
	relt = 0;
	t = a+d+1; //So it jumps to release phase
}

void ADSR::error_handler() {
	__disable_irq();
	while(1) {
		//TODO Just for debug
	}
}

