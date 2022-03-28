/*
 * encoder.c
 *
 *  Created on: 11 Apr 2021
 *      Author: Artur
 */

#include <encoder.h>
#include "stm32f4xx_hal.h"
#include "stdbool.h"
#include "tim.h"

void HAL_GPIO_EXTI_Callback (uint16_t GPIO_Pin)
{
	if ( GPIO_Pin == ENCODER_1_BTN ) {
		encoder_toggle_button (&encoder_1);
	}
	else {
		return;
	}
}

void encoder_struct_init(struct encoder *enc, TIM_HandleTypeDef *htim) {
	encoder_reset_flags(enc);
	enc->ptr = htim;
	encoder_check_counter (enc);
}

void encoder_reset_flags(struct encoder *enc) {
	enc->step_clockwise = false;
	enc->step_counterclockwise = false;
	enc->enter = false;
}

void encoder_check_counter (struct encoder *enc) {

	enc->encoderState = __HAL_TIM_GET_COUNTER( enc->ptr );
}

void encoder_toggle_button (struct encoder *enc) {

	if ( enc->enter == true) {
		enc->enter = false;
	}
	else {
		enc->enter = true;
	}


}

void encoder_check_direction(struct encoder *enc) {

	encoder_check_counter (enc);

	int8_t state = (enc->lastEncoderState - enc->encoderState);

	if( state == 1 ) {
		enc->lastEncoderState = enc->encoderState;
		enc->step_clockwise = true;
	}
	else if (state == -1){
		enc->lastEncoderState = enc->encoderState;
		enc->step_counterclockwise = true;
	}
	else if ( (state == enc->lastEncoderState) && (enc->lastEncoderState == htim1.Init.Period) && (enc->encoderState == 0) ) {
		enc->lastEncoderState = enc->encoderState;
		enc->step_counterclockwise = true;
	}
	else if ( (state < 0) && (enc->lastEncoderState == 0) && (enc->encoderState == htim1.Init.Period)) {
		enc->lastEncoderState = enc->encoderState;
		enc->step_clockwise = true;
	}
	else {
		enc->lastEncoderState = enc->encoderState;

	}
}

_Bool encoder_step_clockwise(struct encoder *enc) {
	encoder_check_direction(enc);
	if(enc->step_clockwise == true) {
		encoder_reset_flags(enc);
		return true;
	}
	else {
		return false;
	}

}

_Bool encoder_step_counterclockwise(struct encoder *enc) {
	encoder_check_direction(enc);
	if(enc->step_counterclockwise == true) {
		encoder_reset_flags(enc);
		return true;
	}
	else {
		return false;
	}
}

_Bool encoder_enter(struct encoder *enc) {
	if(enc->enter == true) {
		HAL_Delay(200);
		encoder_reset_flags(enc);
		return true;
	}
	else {
		return false;
	}
}

uint32_t encoder_return_counter(struct encoder *enc) {
	return enc->encoderState;
}
