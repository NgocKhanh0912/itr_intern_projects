################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/system/sys_button.c \
../Core/Src/system/sys_led.c \
../Core/Src/system/sys_manage.c 

OBJS += \
./Core/Src/system/sys_button.o \
./Core/Src/system/sys_led.o \
./Core/Src/system/sys_manage.o 

C_DEPS += \
./Core/Src/system/sys_button.d \
./Core/Src/system/sys_led.d \
./Core/Src/system/sys_manage.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/system/%.o Core/Src/system/%.su Core/Src/system/%.cyclo: ../Core/Src/system/%.c Core/Src/system/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-system

clean-Core-2f-Src-2f-system:
	-$(RM) ./Core/Src/system/sys_button.cyclo ./Core/Src/system/sys_button.d ./Core/Src/system/sys_button.o ./Core/Src/system/sys_button.su ./Core/Src/system/sys_led.cyclo ./Core/Src/system/sys_led.d ./Core/Src/system/sys_led.o ./Core/Src/system/sys_led.su ./Core/Src/system/sys_manage.cyclo ./Core/Src/system/sys_manage.d ./Core/Src/system/sys_manage.o ./Core/Src/system/sys_manage.su

.PHONY: clean-Core-2f-Src-2f-system

