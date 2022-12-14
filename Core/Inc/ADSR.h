/*
 * ADSR.h
 *
 *  Created on: Jul 13, 2022
 *      Author: PeterMarczis
 */

#ifndef INC_ADSR_H_
#define INC_ADSR_H_

#include "stm32f4xx_hal.h"
#include "defines.h"
#include "Display.h"

#define DAC_DATA_GPIO GPIOD
#define DAC_CS_Pin GPIO_PIN_14
#define DAC_CS_GPIO_Port GPIOC
#define DAC_AB_Pin GPIO_PIN_15
#define DAC_AB_GPIO_Port GPIOC

class ADSR {
private:
	bool     onoff     = 0; //1 on 0 off
	uint32_t ch 	   = 0;
	TIM_HandleTypeDef &tim;
	uint32_t t 		   = 0; //Number of ticks from the start
	uint32_t relt 	   = 0; //Number of ticks from the note off
	float 	 a 		   = 0;
	float 	 d 		   = 0;
	uint32_t s 		   = 0;
	float 	 r 		   = 0;
	bool     output    = false;
	uint32_t vel       = 0;
	float    value     = 0; //The last written value of the ADSR output used for release part
	float    rvalue    = 0; //Release value, so if we re-trigger from the middle of the release we don't go to 0
	uint8_t  lastnote  = 0; //This is for a case when we trigger notes over and over and we don't want to go silent if the previous note is lifted
	int32_t  freq_mod  = 0; //Set by the FM effect

	GPIO_TypeDef *led_a_gpio,*led_d_gpio,*led_s_gpio,*led_r_gpio;
	uint16_t	  led_a_pin,led_d_pin,led_s_pin,led_r_pin;
	Display       &display;
	uint32_t      &ad_a,&ad_d,&ad_s,&ad_r;

	enum LEDS { LED_OFF, LED_A, LED_D, LED_S, LED_R };

	void setLED(LEDS led);
	void set_freq(uint8_t note);
	void error_handler();

public:
	ADSR(uint32_t  ch
		,TIM_HandleTypeDef &_tim
		,GPIO_TypeDef  *_led_a_gpio
		,uint16_t	   _led_a_pin
		,GPIO_TypeDef  *_led_d_gpio
		,uint16_t	   _led_d_pin
		,GPIO_TypeDef  *_led_s_gpio
		,uint16_t	   _led_s_pin
		,GPIO_TypeDef  *_led_r_gpio
		,uint16_t	   _led_r_pin
		,Display       &_display
		,uint32_t      &_ad_a
		,uint32_t      &_ad_d
		,uint32_t      &_ad_s
		,uint32_t      &_ad_r
	);
	virtual ~ADSR();
	void tick();
	void note_on(uint8_t _note, uint8_t _vel);
	void note_off(uint8_t _note);
	void update_display();
	void set_onoff(bool state) { onoff = state; }
	void set_freq_mod(int32_t x);
};

#endif /* INC_ADSR_H_ */
