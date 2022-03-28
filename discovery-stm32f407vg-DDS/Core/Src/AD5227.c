/*
 * AD5227.c
 *
 *  Created on: Jun 23, 2021
 *      Author: Artur
 */

#include "AD5227.h"

void AD5227_Reset(void) {
HAL_GPIO_WritePin(AD5227PORT,AD5227CLK,GPIO_PIN_RESET);
HAL_GPIO_WritePin(AD5227PORT,AD5227CS,GPIO_PIN_SET);
}

void AD5227_StepUp(void) {
	// UD high - direction of stepping is determined by the state of the U/D input
	HAL_GPIO_WritePin(AD5227PORT,AD5227UD,GPIO_PIN_SET);

	// When CS is enabled, changing the resistance settings is achieved by clocking the CLK pin
	// When CS is pulled low, a clock pulse increments or decrements the up/down counter.
	HAL_GPIO_WritePin(AD5227PORT,AD5227CS,GPIO_PIN_RESET);

	//When the wiper reaches the maximum or the minimum setting, additional CLK pulses do
	//not change the wiper setting.
	HAL_GPIO_WritePin(AD5227PORT,AD5227CLK,GPIO_PIN_SET);

	AD5227_Reset();
}
void AD5227_StepDown(void) {
	// UD high - direction of stepping is determined by the state of the U/D input
	HAL_GPIO_WritePin(AD5227PORT,AD5227UD,GPIO_PIN_RESET);

	// When CS is enabled, changing the resistance settings is achieved by clocking the CLK pin
	// When CS is pulled low, a clock pulse increments or decrements the up/down counter.
	HAL_GPIO_WritePin(AD5227PORT,AD5227CS,GPIO_PIN_RESET);

	//When the wiper reaches the maximum or the minimum setting, additional CLK pulses do
	//not change the wiper setting.
	HAL_GPIO_WritePin(AD5227PORT,AD5227CLK,GPIO_PIN_SET);

	AD5227_Reset();
}
