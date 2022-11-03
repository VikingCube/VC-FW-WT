/*
 * MOWaves.cpp
 *
 *  Created on: 16 Oct 2022
 *      Author: PeterMarczis
 */

#include "MOWaves.h"
#include "Defines.h"

MOWaves::MOWaves(uint32_t _ch, uint32_t *_dac_buffer, Display &_display)
 :MultiOption(NR_WAVES),ch(_ch),dac_buffer(_dac_buffer),display(_display)
{
	copy_table();
}

void MOWaves::handler()
{
	copy_table();
    display.set_wt_table(Display::Tables::WT, get_ch(), get_act());
}

void MOWaves::copy_table()
{
    for (int x = 0; x < NS; x++) {
 	   dac_buffer[x] = Wave_LUT[get_act()][x];
    }
}

