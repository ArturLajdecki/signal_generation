/*
 * waveform_gen.c
 *
 *  Created on: May 27, 2021
 *      Author: Artur
 */


#include "waveform_gen.h"
#include "math.h"
#include "stm32f4xx.h"



void calcsin ()
{
	for (int i=0; i<N_s; i++)
	{
		sine_val[i] = ((sin(i*2*PI/N_s) + 1.1)*(4096/2.6));
	}
}

