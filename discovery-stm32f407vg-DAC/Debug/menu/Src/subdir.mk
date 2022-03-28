################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../menu/Src/GFX_FUNCTIONS.c \
../menu/Src/ST7735.c \
../menu/Src/encoder.c \
../menu/Src/fonts.c \
../menu/Src/menu.c \
../menu/Src/menu_definition.c \
../menu/Src/ugui.c 

OBJS += \
./menu/Src/GFX_FUNCTIONS.o \
./menu/Src/ST7735.o \
./menu/Src/encoder.o \
./menu/Src/fonts.o \
./menu/Src/menu.o \
./menu/Src/menu_definition.o \
./menu/Src/ugui.o 

C_DEPS += \
./menu/Src/GFX_FUNCTIONS.d \
./menu/Src/ST7735.d \
./menu/Src/encoder.d \
./menu/Src/fonts.d \
./menu/Src/menu.d \
./menu/Src/menu_definition.d \
./menu/Src/ugui.d 


# Each subdirectory must supply rules for building sources it contributes
menu/Src/%.o menu/Src/%.su: ../menu/Src/%.c menu/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Artur/Documents/STM32CubeIDE/workspace_1.6.1/discovery-stm32f407vg-DAC/menu/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-menu-2f-Src

clean-menu-2f-Src:
	-$(RM) ./menu/Src/GFX_FUNCTIONS.d ./menu/Src/GFX_FUNCTIONS.o ./menu/Src/GFX_FUNCTIONS.su ./menu/Src/ST7735.d ./menu/Src/ST7735.o ./menu/Src/ST7735.su ./menu/Src/encoder.d ./menu/Src/encoder.o ./menu/Src/encoder.su ./menu/Src/fonts.d ./menu/Src/fonts.o ./menu/Src/fonts.su ./menu/Src/menu.d ./menu/Src/menu.o ./menu/Src/menu.su ./menu/Src/menu_definition.d ./menu/Src/menu_definition.o ./menu/Src/menu_definition.su ./menu/Src/ugui.d ./menu/Src/ugui.o ./menu/Src/ugui.su

.PHONY: clean-menu-2f-Src

