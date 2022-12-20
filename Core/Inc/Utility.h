/*
 * MOWaves.h
 *
 *  Created on: 16 Oct 2022
 *      Author: PeterMarczis
 */

#ifndef UTILITY_H_
#define UTILITY_H_

namespace Utility {

int32_t p_m_param(uint32_t x) {
	//Converts the 0-4096 range to a +-2048 range
	if (x < 2048) return -1*(2048-x);
	return x-2048; //Positive range
}

}


#endif
