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

class MOWaves : public MultiOption
{
private:
	uint32_t ch;
	void copy_table();
	Display &display;
	uint32_t *dac_buffer;

public:
	MOWaves(uint32_t _ch, uint32_t *_dac_buffer, Display &_display);
	~MOWaves() {};
	void handler();
	uint32_t get_ch() { return ch; }
};

#endif /* MOWAVES_H_ */
