/*
 * Effects.cpp
 *
 *  Created on: 16 Oct 2022
 *      Author: PeterMarczis
 */

#include "Effects.h"

Effects::Effects(uint32_t _ch, Display &_display)
	:MultiOption(8)
	,ch(_ch)
	,display(_display)
{

}

void Effects::handler()
{
	display.set_wt_table(Display::Tables::EFFECTS, get_ch(), get_act());
}

void Effects::error_handler() {
	__disable_irq();
	while(1) {
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
