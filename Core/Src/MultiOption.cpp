/*
 * MultiOption.cpp
 *
 *  Created on: 16 Oct 2022
 *      Author: PeterMarczis
 */

#include "MultiOption.h"

MultiOption::MultiOption(uint32_t _max)
 :max(_max)
{

}

MultiOption::~MultiOption() {
	// TODO Auto-generated destructor stub
}

void MultiOption::trigger() {
	act++;
	if (act == max) { act = 0; }
	handler();
}
