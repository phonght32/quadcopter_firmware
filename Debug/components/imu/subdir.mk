################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../components/imu/imu_public.c 

OBJS += \
./components/imu/imu_public.o 

C_DEPS += \
./components/imu/imu_public.d 


# Each subdirectory must supply rules for building sources it contributes
components/imu/%.o components/imu/%.su components/imu/%.cyclo: ../components/imu/%.c components/imu/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/phong/Documents/stm32/quadcopter_firmware/components/imu/mpu9250" -I"/home/phong/Documents/stm32/quadcopter_firmware/components/imu" -I"/home/phong/Documents/stm32/quadcopter_firmware/components/mcu_port" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-components-2f-imu

clean-components-2f-imu:
	-$(RM) ./components/imu/imu_public.cyclo ./components/imu/imu_public.d ./components/imu/imu_public.o ./components/imu/imu_public.su

.PHONY: clean-components-2f-imu

