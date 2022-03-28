/*
 * encoder.h
 *
 *  Created on: 11 Apr 2021
 *      Author: Artur
 */


#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_

#include "stm32f4xx.h"

/**TIM4 GPIO Configuration
PE9     ------> TIM4_CH1
PD11     ------> TIM4_CH2
Function and pins define file tim.c line 300

*/

#define ENCODER_1_BTN 	GPIO_PIN_10

struct encoder {
	uint32_t lastEncoderState;
	uint32_t encoderState;
	_Bool step_clockwise;
	_Bool step_counterclockwise;
	_Bool enter;
	TIM_HandleTypeDef *ptr;

};

struct encoder encoder_1;

void encoder_struct_init(struct encoder *enc, TIM_HandleTypeDef *htim);
void encoder_reset_flags(struct encoder *enc);
void encoder_check_counter (struct encoder *enc);
void encoder_toggle_button (struct encoder *enc);
void encoder_check_direction(struct encoder *enc);
_Bool encoder_step_clockwise(struct encoder *enc);
_Bool encoder_step_counterclockwise(struct encoder *enc);
_Bool encoder_enter(struct encoder *enc);


#endif /* INC_ENCODER_H_ */
