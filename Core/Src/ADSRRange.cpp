/*
 * ADSRRange.cpp
 *
 *  Created on: 16 Oct 2022
 *      Author: PeterMarczis
 */

#include "ADSRRange.h"

ADSRRange::ADSRRange(uint32_t _ch, TIM_HandleTypeDef &_tim, Display &_display)
:MultiOption(8), ch(_ch), tim(_tim), display(_display)
{
}

void ADSRRange::handler()
{
	display.set_wt_table(Display::Tables::ADSR_RANGE, get_ch(), get_act());
	HAL_TIM_Base_Stop_IT(&tim);
	tim.Init.Prescaler = ranges[get_act()];
	if (HAL_TIM_Base_Init(&tim) != HAL_OK) { error_handler(); }
	HAL_TIM_Base_Start_IT(&tim);
}

void ADSRRange::error_handler() {
	__disable_irq();
	while(1) {
	}
}
