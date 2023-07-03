################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Lib_CH446/Lib_STM32_CH446.c 

OBJS += \
./Core/Src/Lib_CH446/Lib_STM32_CH446.o 

C_DEPS += \
./Core/Src/Lib_CH446/Lib_STM32_CH446.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Lib_CH446/%.o Core/Src/Lib_CH446/%.su Core/Src/Lib_CH446/%.cyclo: ../Core/Src/Lib_CH446/%.c Core/Src/Lib_CH446/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Lib_CH446

clean-Core-2f-Src-2f-Lib_CH446:
	-$(RM) ./Core/Src/Lib_CH446/Lib_STM32_CH446.cyclo ./Core/Src/Lib_CH446/Lib_STM32_CH446.d ./Core/Src/Lib_CH446/Lib_STM32_CH446.o ./Core/Src/Lib_CH446/Lib_STM32_CH446.su

.PHONY: clean-Core-2f-Src-2f-Lib_CH446

