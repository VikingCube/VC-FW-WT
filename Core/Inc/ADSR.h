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

//TODO is  there any crazy trick  to get these here without passing them?
#define DAC_DATA_GPIO GPIOD
#define DAC_CS_Pin GPIO_PIN_14
#define DAC_CS_GPIO_Port GPIOC
#define DAC_AB_Pin GPIO_PIN_15
#define DAC_AB_GPIO_Port GPIOC

class ADSR {
private:
	uint32_t ch 	= 0;
	uint32_t t 		= 0; //Number of ticks from the start
	uint32_t relt 	= 0; //Number of ticks from the note off
	float 	 a 		= 0;
	float 	 d 		= 0;
	uint32_t s 		= 0;
	float 	 r 		= 0;
	bool     output = false;

public:
	ADSR(uint32_t  ch);
	virtual ~ADSR();
	void tick();
	void note_on();
	void note_off();
	void setA(float _a);
	void setD(float _d);
	void setS(uint32_t _s);
	void setR(float _r);
};

#endif /* INC_ADSR_H_ */
