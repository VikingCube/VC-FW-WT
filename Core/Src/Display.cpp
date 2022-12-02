/*
 * Display.cpp
 *
 *  Created on: 6 Oct 2022
 *      Author: PeterMarczis
 */

#include "Display.h"

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
}

void Display::update()
{
	leds_off();
	state_tmr--;
	if (state_tmr == 0) {
		state=UV;
	}
	switch (state) {
		case TABLE:
		{
			if (act_table == ADSR_RANGE) leds[17].set();
			if (act_table == EFFECTS) leds[16].set();
			//Set CH0
			leds[table[act_table][0]].set();
			//Set CH1
			leds[table[act_table][1]+8].set();
			break;
		}
		case ADSR:
		{
			int32_t x = 7-uint32_t(adsr_states[adsr_active_ch][adsr_active_pot]/512);
			for(int32_t i = 7; i >= x; i--) {
					leds[i].set();
					leds[i+8].set();
			}
			break;
		}
		case UV:
		{
			int32_t x = 7-uint32_t(adsr_gain[0]/32);
			for(int32_t i = 7; i >= x; i--) {
				leds[i].set();
			}
			int32_t x2 = 7-uint32_t(adsr_gain[1]/32);
			for(int32_t i = 7; i >= x2; i--) {
				leds[i+8].set();
			}
			break;
		}
	}
}

void Display::leds_off()
{
	for (Pin i : leds) {
		i.reset();
	}
}

void Display::adsr(uint32_t ch, uint32_t a, uint32_t d, uint32_t s, uint32_t r)
{
	adsr_states[ch][0] = a;
	adsr_states[ch][1] = d;
	adsr_states[ch][2] = s;
	adsr_states[ch][3] = r;

	for (int i = 0; i < 4 ; i++) {
		if (abs(adsr_states[ch][i] - adsr_states[ch][i+4]) > 1024) {
			state = ADSR;
			set_state_timer(0x0FFF);
			adsr_states[ch][i+4] = adsr_states[ch][i];
			adsr_active_pot=i;
			adsr_active_ch=ch;
			break;
		}
	}
}
