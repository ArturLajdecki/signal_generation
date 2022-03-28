/*
 * Copyright (c) 2021 Artur Lajdecki
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * This file is part of Application.
 *
 * Author:          Artur Lajdecki <249116@student.pwr.edu.pl>
 */

#ifndef INC_MENU_DEFINITION_H_
#define INC_MENU_DEFINITION_H_

/* Include headers */
#include "stm32f4xx.h"

/* Private define */
#define PGM_STR(X) ((char[]) { X })

struct waveform {
	_Bool enableWaveform;

	TIM_HandleTypeDef *TIM_ptr;
	uint32_t *LUT;

	uint32_t samples;
	uint32_t frequency;
	uint8_t voltage_pp;
	uint8_t offset;
	uint8_t place_value;
	uint8_t previous_place_value;
};

struct waveform ramp;
struct waveform sine;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Function prototypes, name aligned, lowercase names */
void waveform_struct_init(	struct waveform *wf,
							TIM_HandleTypeDef *htim,
							uint32_t *LUT,
							uint32_t samples,
							float freq,
							uint8_t vpp,
							uint8_t offset);

void SET_wave_ARR(struct waveform *wf);

void CHANGE_cursor(struct waveform *wf);
void CHANGE_temperature(struct waveform *wf);

int32_t CALC_temperature(int32_t freq_in, int8_t direction, uint8_t dec);
void SHOW_temperature(uint32_t freq);
void SHOW_cursor(struct waveform *wf);

int32_t CALC_temperature(int32_t freq_in, int8_t direction, uint8_t dec);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* INC_MENU_DEFINITION_H_ */
