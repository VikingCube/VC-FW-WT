/*
 * Display.h
 *
 *  Created on: 6 Oct 2022
 *      Author: PeterMarczis
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "stm32f4xx_hal.h"
#include <iterator>

#define LED0_Pin GPIO_PIN_0
#define LED0_GPIO_Port GPIOE
#define LED1_Pin GPIO_PIN_1
#define LED1_GPIO_Port GPIOE
#define LED2_Pin GPIO_PIN_2
#define LED2_GPIO_Port GPIOE
#define LED3_Pin GPIO_PIN_3
#define LED3_GPIO_Port GPIOE
#define LED4_Pin GPIO_PIN_4
#define LED4_GPIO_Port GPIOE
#define LED5_Pin GPIO_PIN_5
#define LED5_GPIO_Port GPIOE
#define LED6_Pin GPIO_PIN_6
#define LED6_GPIO_Port GPIOE
#define LED7_Pin GPIO_PIN_7
#define LED7_GPIO_Port GPIOE
#define LED8_Pin GPIO_PIN_8
#define LED8_GPIO_Port GPIOE
#define LED9_Pin GPIO_PIN_9
#define LED9_GPIO_Port GPIOE
#define LED10_Pin GPIO_PIN_10
#define LED10_GPIO_Port GPIOE
#define LED11_Pin GPIO_PIN_11
#define LED11_GPIO_Port GPIOE
#define LED12_Pin GPIO_PIN_12
#define LED12_GPIO_Port GPIOE
#define LED13_Pin GPIO_PIN_13
#define LED13_GPIO_Port GPIOE
#define LED14_Pin GPIO_PIN_14
#define LED14_GPIO_Port GPIOE
#define LED15_Pin GPIO_PIN_15
#define LED15_GPIO_Port GPIOE
#define LED16_Pin GPIO_PIN_14
#define LED16_GPIO_Port GPIOB
#define LED17_Pin GPIO_PIN_15
#define LED17_GPIO_Port GPIOB

class Pin {
private:
	GPIO_TypeDef* gpio;
	uint16_t pin;
public:
	Pin(GPIO_TypeDef* _gpio, uint16_t _pin);
	void set();
	void reset();
};

class Display {
private:
	enum State {
		TABLE, ADSR, UV
	} state = TABLE;
	Pin leds[18];

	uint32_t state_tmr = 0;

	//State storages
	//TABLE - the state for displaying the WT Table selected
	uint32_t table[2]; //One for each channel

	//ADSR
	uint32_t adsr_states[2][8];
	uint32_t adsr_active_pot = 0;
	uint32_t adsr_active_ch  = 0;

	//UV
	uint8_t adsr_gain[2];

	void leds_off();
	void set_state_timer(uint32_t time) { state_tmr = time; };
public:
	Display();
	virtual ~Display();

	void update(); //Interface to call the update from timer callback

	//IF for WT Selection
	void set_wt_table(uint32_t ch, uint32_t val) { state = TABLE; table[ch] = val; }; //Yeah can throw exceptions, but we won't right? :)
	//IF for ADSR Updates
	void adsr(uint32_t ch, uint32_t a, uint32_t d, uint32_t s, uint32_t r);
	void adsr_update_gain(uint32_t ch, uint8_t gain) {adsr_gain[ch] = gain;};
};

#endif /* DISPLAY_H_ */
