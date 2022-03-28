/*
 * AD5227.h
 *
 *  Created on: Jun 23, 2021
 *      Author: Artur
 */

#ifndef INC_AD5227_H_
#define INC_AD5227_H_

#include <math.h>
#include "stm32f4xx_hal.h"

// ------------------------- Defines -------------------------
#define CLK 4000000        // Master Clock On AD5227
#define AD5227PORT GPIOC      // PORT OF AD5227
#define AD5227UD GPIO_PIN_0   // SPI DATA PIN
#define AD5227CLK GPIO_PIN_1  // SPI Clock PIN
#define AD5227CS GPIO_PIN_3   // SPI Chip Select
#define ASM_NOP() asm("NOP")  // Assembly NOPE (Little Delay)


// ------------------ Functions  ---------------------
void AD5227_Reset(void); 		// Set all pins to disable
void AD5227_StepUp(void);    	 // Increases resistance by one step
void AD5227_StepDown(void);      // Decreases resistance by one step

#endif /* INC_AD5227_H_ */
