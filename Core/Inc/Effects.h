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

class WaveModifier
{
public:
	WaveModifier() {};
	~WaveModifier() {};
	virtual uint32_t modify(uint32_t i) = 0; //Must return  the value we will copy into the DAC buffer
};


class NoEffect : public WaveModifier {
	uint32_t modify(uint32_t i) { return i; };
};

class EDiode : public WaveModifier {
public:
	uint32_t modify(uint32_t i);
};

class Effects : public MultiOption
{
private:
	uint32_t ch;
//Effects
	NoEffect e_no;
	EDiode   e_dio;

	Display &display;
	uint32_t get_ch() { return ch; };
	void error_handler();

public:
	Effects(uint32_t ch, Display &_display);
	~Effects() {};
	void handler();
	WaveModifier& get_modifier();
};

#endif /* EFFECTS_H_ */
