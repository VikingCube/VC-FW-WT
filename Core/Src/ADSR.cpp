/*
 * ADSR.cpp
 *
 *  Created on: Jul 13, 2022
 *      Author: PeterMarczis
 */

#include <ADSR.h>

ADSR::ADSR(uint32_t _ch)
	:ch(_ch)
{
}

ADSR::~ADSR() {
	// TODO Auto-generated destructor stub
}


void ADSR::tick()
{
	//Linear ADSR
	t++; //Increase tick
	float res;
	if (t <= a) {
		//Attack phase
		res = 255/a*t;
	} else if (t < (a+d)) {
		uint32_t rt=a+d-t;
		res = (0xFF*float(s)/100)*(float(rt)/float(d))+(0xFF*float(s)/100);
	} else if (output) {
		//Sustain phase
		res = 0xFF*(float(s)/100);
	} else if (relt < r) {
		//Release phase
		relt++;
		uint32_t rt = r-relt;
		res = (0xFF*float(s)/100)*(float(rt)/float(r));
	} else {
		res = 0;
	}

	//Pick DAC
	if (ch == 0) HAL_GPIO_WritePin(DAC_AB_GPIO_Port, DAC_AB_Pin, GPIO_PIN_RESET);
	if (ch == 1) HAL_GPIO_WritePin(DAC_AB_GPIO_Port, DAC_AB_Pin, GPIO_PIN_SET);
	//Write Data
	DAC_DATA_GPIO->ODR = uint32_t(res);
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
