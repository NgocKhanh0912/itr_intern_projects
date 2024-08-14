################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/drv/drv_button.c \
../Core/Src/drv/drv_led.c 

OBJS += \
./Core/Src/drv/drv_button.o \
./Core/Src/drv/drv_led.o 

C_DEPS += \
./Core/Src/drv/drv_button.d \
./Core/Src/drv/drv_led.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/drv/%.o Core/Src/drv/%.su Core/Src/drv/%.cyclo: ../Core/Src/drv/%.c Core/Src/drv/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-drv

clean-Core-2f-Src-2f-drv:
	-$(RM) ./Core/Src/drv/drv_button.cyclo ./Core/Src/drv/drv_button.d ./Core/Src/drv/drv_button.o ./Core/Src/drv/drv_button.su ./Core/Src/drv/drv_led.cyclo ./Core/Src/drv/drv_led.d ./Core/Src/drv/drv_led.o ./Core/Src/drv/drv_led.su

.PHONY: clean-Core-2f-Src-2f-drv

