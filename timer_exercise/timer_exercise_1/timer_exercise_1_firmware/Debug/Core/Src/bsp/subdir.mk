################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/bsp/bsp_gpio.c \
../Core/Src/bsp/bsp_timer.c 

OBJS += \
./Core/Src/bsp/bsp_gpio.o \
./Core/Src/bsp/bsp_timer.o 

C_DEPS += \
./Core/Src/bsp/bsp_gpio.d \
./Core/Src/bsp/bsp_timer.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/bsp/%.o Core/Src/bsp/%.su Core/Src/bsp/%.cyclo: ../Core/Src/bsp/%.c Core/Src/bsp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-bsp

clean-Core-2f-Src-2f-bsp:
	-$(RM) ./Core/Src/bsp/bsp_gpio.cyclo ./Core/Src/bsp/bsp_gpio.d ./Core/Src/bsp/bsp_gpio.o ./Core/Src/bsp/bsp_gpio.su ./Core/Src/bsp/bsp_timer.cyclo ./Core/Src/bsp/bsp_timer.d ./Core/Src/bsp/bsp_timer.o ./Core/Src/bsp/bsp_timer.su

.PHONY: clean-Core-2f-Src-2f-bsp

