################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CH446_Lib/Src/Lib_STM32_CH446.c 

OBJS += \
./CH446_Lib/Src/Lib_STM32_CH446.o 

C_DEPS += \
./CH446_Lib/Src/Lib_STM32_CH446.d 


# Each subdirectory must supply rules for building sources it contributes
CH446_Lib/Src/%.o CH446_Lib/Src/%.su CH446_Lib/Src/%.cyclo: ../CH446_Lib/Src/%.c CH446_Lib/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/roland/git/CH446_STM32_lib/ExampleProject/CH446_Lib/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CH446_Lib-2f-Src

clean-CH446_Lib-2f-Src:
	-$(RM) ./CH446_Lib/Src/Lib_STM32_CH446.cyclo ./CH446_Lib/Src/Lib_STM32_CH446.d ./CH446_Lib/Src/Lib_STM32_CH446.o ./CH446_Lib/Src/Lib_STM32_CH446.su

.PHONY: clean-CH446_Lib-2f-Src

