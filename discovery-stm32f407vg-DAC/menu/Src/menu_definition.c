/*
 * menu_definition.c
 *
 *  Created on: May 28, 2021
 *      Author: Artur
 */
#include <menu.h>
#include <system.h>
#include "stdbool.h"
#include "menu_definition.h"
#include "waveform_gen.h"

//Prototypy funkcji obs³ugiwanycch w menu

void func_B1();
void func_B2();

void func_A1();
void func_A2();

const struct menuitem  menu_link;
const struct menuitem  menu_link_1;
const struct menuitem  menu_link_A1;
const struct menuitem  menu_link_B1;

const struct menuitem  menu_link_B3 = {PGM_STR("<Back>"), Menu_Back, &menu_link_B1, 0, 0};
const struct menuitem  menu_link_B2 = {PGM_STR("Amplitude"), func_B2, &menu_link_B1, 0, &menu_link_B3};
const struct menuitem  menu_link_B1 = {PGM_STR("Frequency"), func_B1, &menu_link, 0, &menu_link_B2};

const struct menuitem  menu_link_A3 = {PGM_STR("<Back>"), Menu_Back, &menu_link_A1, 0, 0};
const struct menuitem  menu_link_A2 = {PGM_STR("Amplitude"), func_A2, &menu_link_A1, 0, &menu_link_A3};
const struct menuitem  menu_link_A1 = {PGM_STR("Frequency"), func_A1, &menu_link, 0, &menu_link_A2};

const struct menuitem menu_link_1 = {PGM_STR("Sine settings"), 0, &menu_link, &menu_link_B1, 0};
const struct menuitem  menu_link = {PGM_STR("Ramp settings"), 0, 0,  &menu_link_A1, &menu_link_1};

//void menufunc1()
//{
//  UG_WindowShow( &window_1 );
//  UG_Update();
////  button1_1->str =
////  UG_OBJECT* obj = _UG_SearchObject( UG_WINDOW* wnd, UG_U8 type, UG_U8 id );
//}
//

void func_A1() {
	 CHANGE_temperature(&ramp);
}
void func_A2() {
	// CHANGE_amplitude(&ramp);
}

void func_B1(){
	 CHANGE_temperature(&sine);
}

void func_B2() {
	 //CHANGE_frequency(&sine);
}

void waveform_struct_init(	struct waveform *wf,
							TIM_HandleTypeDef *htim,
							uint32_t *LUT,
							uint32_t samples,
							float freq,
							uint8_t vpp,
							uint8_t offset) {

	wf->enableWaveform = true;
	wf->TIM_ptr = htim;
	wf->LUT = LUT;
	wf->samples = samples;
	wf->frequency = freq * 100;
	SET_wave_ARR(wf);
	wf->voltage_pp = vpp;
	wf->offset = offset;
}

void SET_wave_ARR(struct waveform *wf) {

	if(wf->frequency < 1000000 && wf->frequency > 1) {
		uint64_t trigger_frequency = (wf->frequency / 100) * wf->samples;
		double TIMx_ARR;
		TIMx_ARR = APB1_TIM_CLK / trigger_frequency;
		TIMx_ARR = TIMx_ARR/(TIM2_PRESCALER);
		TIMx_ARR = TIMx_ARR - 1;

//		double TIMx_ARR = ( APB1_TIM_CLK - trigger_frequency - (trigger_frequency * TIM2_PRESCALER) ) / ( (trigger_frequency * TIM2_PRESCALER) + trigger_frequency );
		uint64_t TIMx_ARR2 = TIMx_ARR;
		//wf->TIM_ptr->Init.Period = TIMx_ARR;
		__HAL_TIM_SET_AUTORELOAD(wf->TIM_ptr, TIMx_ARR2-1);
		HAL_Delay(20);
	}
	else {
		__HAL_TIM_SET_AUTORELOAD(wf->TIM_ptr, 1);
		HAL_Delay(20);
	}

}

void CHANGE_cursor(struct waveform *wf) {


	while(encoder_enter(&encoder_1) == false) {

		if (encoder_step_clockwise(&encoder_1) == true)
		{
			if((wf->place_value == 0)) {
				wf->place_value = 8;
			}
			else{
				(wf->place_value)--;
			}
		}
		else if (encoder_step_counterclockwise(&encoder_1) == true)
		{
			if( (wf->place_value == 8) ) {
				wf->place_value = 0;
			}
			else {
				(wf->place_value)++;
			}

		}

		SHOW_cursor(wf);
	}
}

void CHANGE_temperature(struct waveform *wf) {
	UG_FillScreen( C_BLACK );
	SHOW_temperature(wf->frequency);
	SHOW_cursor(wf);
	CHANGE_cursor(wf);

	if(wf->place_value != 8){
		while(encoder_enter(&encoder_1) == false) {

			if (encoder_step_clockwise(&encoder_1) == true)
			{
				wf->frequency = CALC_temperature(wf->frequency, 1, wf->place_value);
				SHOW_temperature(wf->frequency);
			}
			if (encoder_step_counterclockwise(&encoder_1) == true)
			{
				wf->frequency = CALC_temperature(wf->frequency, -1,  wf->place_value);
				SHOW_temperature(wf->frequency);
			}
		}
		CHANGE_temperature(wf);
	}
	else {

		SET_wave_ARR(wf);
	}


}

//void CHANGE_amplitude(struct waveform *wf) {
//	if (amplitude != previous_amplitude)
//	{
//		ST7735_PutStr5x7(2, 1, 90, "amplitude    ", COLOR565_DARK_BLUE, COLOR565_WHITE);
//		sprintf(buff, "amplitude %d", amplitude+1);
//		ST7735_PutStr5x7(2, 1, 90, buff, COLOR565_DARK_BLUE, COLOR565_WHITE);
//		previous_amplitude = amplitude;
//	}
//
//	up_down = ROTARY_direction();
//	if (up_down != 0)
//	{
//		LL_TIM_SetCounter(TIM4, 100);
//		start_time = LL_TIM_GetCounter(TIM7);
//		amplitude += up_down;
//		if (amplitude < 0) amplitude = 0;
//		if (amplitude > 15) amplitude = 15;
//
//		if (amplitude & 0x01) LL_GPIO_ResetOutputPin(GPIOE, LL_GPIO_PIN_11);
//		else LL_GPIO_SetOutputPin(GPIOE, LL_GPIO_PIN_11);
//
//		if (amplitude & 0x02) LL_GPIO_ResetOutputPin(GPIOE, LL_GPIO_PIN_12);
//		else LL_GPIO_SetOutputPin(GPIOE, LL_GPIO_PIN_12);
//
//		if (amplitude & 0x04) LL_GPIO_ResetOutputPin(GPIOE, LL_GPIO_PIN_13);
//		else LL_GPIO_SetOutputPin(GPIOE, LL_GPIO_PIN_13);
//
//		if (amplitude & 0x08) LL_GPIO_ResetOutputPin(GPIOE, LL_GPIO_PIN_14);
//		else LL_GPIO_SetOutputPin(GPIOE, LL_GPIO_PIN_14);
//	}
//
//	elapsed_time = LL_TIM_GetCounter(TIM7) - start_time;
//}
//sprintf(buff, "amplitude %d", amplitude+1);
//ST7735_PutStr5x7(2, 1, 90, "             ", COLOR565_WHITE, COLOR565_DARK_BLUE);
//ST7735_PutStr5x7(2, 1, 90, buff, COLOR565_WHITE, COLOR565_DARK_BLUE);
//}

//void CHANGE_offset (struct waveform *wf) {
//	if (previous_offset != offset)
//						{
//							ST7735_PutStr5x7(2, 1, 110, "offset       ", COLOR565_DARK_BLUE, COLOR565_WHITE);
//							sprintf(buff, "offset    %d", offset-25);
//							ST7735_PutStr5x7(2, 1, 110, buff, COLOR565_DARK_BLUE, COLOR565_WHITE);
//							previous_offset = offset;
//						}
//
//						up_down = ROTARY_direction();
//						if (up_down != 0)
//						{
//							LL_TIM_SetCounter(TIM4, 100);
//							start_time = LL_TIM_GetCounter(TIM7);
//							offset += up_down;
//							if (offset < 1) offset = 1;
//							if (offset > 49) offset = 49;
//							LL_TIM_OC_SetCompareCH4(TIM3, ((offset * 20) - 10));
//						}
//						elapsed_time = LL_TIM_GetCounter(TIM7) - start_time;
//					}
//
//					sprintf(buff, "offset    %d", offset-25);
//					ST7735_PutStr5x7(2, 1, 110,"             ", COLOR565_WHITE, COLOR565_DARK_BLUE);
//					ST7735_PutStr5x7(2, 1, 110,buff, COLOR565_WHITE, COLOR565_DARK_BLUE);
//}

int32_t CALC_temperature(int32_t freq_in, int8_t direction, uint8_t dec) {
	int32_t freq_out = 0;

	switch (dec)
	{
	case 0:
		freq_out = freq_in + (direction * 1);
		break;
	case 1:
		freq_out = freq_in + (direction * 10);
		break;
	case 2:
		freq_out = freq_in + (direction * 100);
		break;
	case 3:
		freq_out = freq_in + (direction * 1000);
		break;
	case 4:
		freq_out = freq_in + (direction * 10000);
		break;
	case 5:
		freq_out = freq_in + (direction * 100000);
		break;
	case 6:
		freq_out = freq_in + (direction * 1000000);
		break;
	case 7:
		freq_out = freq_in + (direction * 10000000);
		break;
	default:
		break;
	}
	if (freq_out < 0) freq_out = 0;
	if (freq_out > 99999999) freq_out = 99999999;
	return freq_out;
}

void SHOW_temperature(uint32_t freq) {
	char buffer[20];
	uint8_t cijfer[8];

	if (freq <= 99999999)
	{
		for (uint8_t i = 0; i < 8; i++)
		{
			cijfer[i] = (uint8_t) (freq % 10) + 48;
			freq /= 10;
		}
		sprintf(buffer, "%c%c%c %c%c%c.%c%c Hz", cijfer[7], cijfer[6], cijfer[5], cijfer[4], cijfer[3], cijfer[2], cijfer[1], cijfer[0]);
		UG_FillFrame(0, 10+(0*10), UG_GetXDim(), (gui1.font.char_height)+(10+(0*10)), C_BLACK);
		UG_PutString(2, 10+(0*10), buffer );

	}
	else {
		UG_PutString( 2, 50, "   Error");

	}

}

void SHOW_cursor(struct waveform *wf) {
	uint8_t cursor_position = 0;

	switch (wf->place_value)
	{
	case 0:
		cursor_position = 2+(9*gui1.font.char_width+gui1.font.char_h_space);
		break;
	case 1:
		cursor_position = 2+(8*gui1.font.char_width+gui1.font.char_h_space);
		break;
	case 2:
		cursor_position = 2+(6*gui1.font.char_width+gui1.font.char_h_space);
		break;
	case 3:
		cursor_position = 2+(5*gui1.font.char_width+gui1.font.char_h_space);
		break;
	case 4:
		cursor_position = 2+(4*gui1.font.char_width+gui1.font.char_h_space);
		break;
	case 5:
		cursor_position = 2+(2*gui1.font.char_width+gui1.font.char_h_space);
		break;
	case 6:
		cursor_position = 2+(1*gui1.font.char_width+gui1.font.char_h_space);
		break;
	case 7:
		cursor_position = 2+(0*gui1.font.char_width+gui1.font.char_h_space);
		break;
	case 8:
		cursor_position = 2+(0*gui1.font.char_width+gui1.font.char_h_space);
		break;
	default:
		break;
	}

	if(wf->place_value != wf->previous_place_value) {
		UG_FillFrame(0, 10+(1*10), UG_GetXDim(), (gui1.font.char_height)+(10+(1*10)), C_BLACK);
		UG_PutString( cursor_position, 10+(1*10), "^" );
		wf->previous_place_value = wf->place_value;
	}
	else if(wf->place_value == 8) {
		UG_PutString( cursor_position, 10+(1*10), "<Back>" );
	}
	else {
		UG_PutString( cursor_position, 10+(1*10), "^" );
	}

}
