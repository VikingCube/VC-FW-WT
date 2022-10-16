/*
 * MultiOption.h
 *
 *  Created on: 16 Oct 2022
 *      Author: PeterMarczis
 */

#ifndef MULTIOPTION_H_
#define MULTIOPTION_H_
#include "BTNHandler.h"

class MultiOption : public BTNAction
{
private:
	uint32_t max = 0;
	uint32_t act = 0;

public:
	MultiOption(uint32_t _max = 0);
	void trigger();
	virtual ~MultiOption();
	virtual void handler() = 0;
	uint32_t get_act() {return act;}
};

#endif /* MULTIOPTION_H_ */
