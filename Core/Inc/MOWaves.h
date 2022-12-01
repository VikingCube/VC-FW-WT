/*
 * MOWaves.h
 *
 *  Created on: 16 Oct 2022
 *      Author: PeterMarczis
 */

#ifndef MOWAVES_H_
#define MOWAVES_H_

#include "MultiOption.h"
#include "Display.h"
#include "Defines.h"
#include "Effects.h"

class MOWaves : public MultiOption
{
private:
	uint32_t ch;
	Display &display;
	uint32_t *dac_buffer;
	Effects &effects;

public:
	MOWaves(uint32_t _ch, uint32_t *_dac_buffer, Display &_display, Effects &_effects);
	~MOWaves() {};
	void handler();
	uint32_t get_ch() { return ch; }
	void copy_table();
};

#endif /* MOWAVES_H_ */
