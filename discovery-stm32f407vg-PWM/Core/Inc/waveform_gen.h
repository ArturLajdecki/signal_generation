/*
 * waveform_gen.h
 *
 *  Created on: May 27, 2021
 *      Author: Artur
 */

//The transfer speed from memory to the DAC is limited by several factors,
//among them:

//•the clock cycle of the APB or of the AHB (DAC clock)
//•the DMA transfer cycle from memory to the DAC (includes the AHB to APB bridge)
//•the trigger mechanism itself.

//The DAC on STM32F407x microcontrollers is running on the APB1:
//•three cycles after the trigger, DHR data is moved to the DOR register
//•at the same time a DMA request is generated from DAC to DMA
//•DMA transfer takes at least one APB clock cycle.
//So a total of four APB clock cycles is needed to update the DOR data.
//As APB1 maximum clock is 42MHz (for ST32F407x), 10.5Msps is the maximum update rate for the DAC
//output register when timer trigger and the DMA are used for the data update.
//The minimum transfer clock cycle by DMA to the DAC is not the same for all
//STM32 microcontrollers, because of the different bus configuration.

//In STM32F407 system, some timer can run with a clock frequency twice the one of the APB1 clock,
//so resolution is two times better than APB1 clock. However DAC will capture the trigger signal by APB1 clock,
//so the DAC timing cannot be better than APB1 clock.


#ifndef INC_WAVEFORM_GEN_H_
#define INC_WAVEFORM_GEN_H_

#include "stm32f4xx.h"

#define PI 3.1415926
//#define ASR 0.703125
//#define APB1_TIM_CLK 42000000
//#define TIM2_PRESCALER 1

#define N_s 512
uint32_t sine_val[N_s];
//void calcsin();
//void calcangle();
//float angle;

//#define NS      512
//uint32_t Wave_LUT[NS];

#endif /* INC_WAVEFORM_GEN_H_ */
