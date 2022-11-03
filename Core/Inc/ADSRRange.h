/*
 * ADSRRange.h
 *
 *  Created on: 16 Oct 2022
 *      Author: PeterMarczis
 */

#ifndef ADSRRANGE_H_
#define ADSRRANGE_H_

#include "MultiOption.h"
#include "Display.h"

class ADSRRange : public MultiOption
{
private:
	uint32_t ch;
	TIM_HandleTypeDef &tim;
	Display &display;

	void error_handler();
	const uint32_t ranges[8] = {0x000A, 0x000F, 0x00F0, 0x0F00, 0xF000, 0xF0F0, 0xFF00, 0xFFFF};
public:
	ADSRRange(uint32_t ch, TIM_HandleTypeDef &_tim, Display &_display);
	~ADSRRange() {};
	void handler();
	uint32_t  get_ch() { return ch; }
};


#endif /* ADSRRANGE_H_ */
