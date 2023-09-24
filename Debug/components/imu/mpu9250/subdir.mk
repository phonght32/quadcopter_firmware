################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../components/imu/mpu9250/mpu9250_private.c 

OBJS += \
./components/imu/mpu9250/mpu9250_private.o 

C_DEPS += \
./components/imu/mpu9250/mpu9250_private.d 


# Each subdirectory must supply rules for building sources it contributes
components/imu/mpu9250/%.o components/imu/mpu9250/%.su components/imu/mpu9250/%.cyclo: ../components/imu/mpu9250/%.c components/imu/mpu9250/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/phong/Documents/stm32/quadcopter_firmware/components/imu/mpu9250" -I"/home/phong/Documents/stm32/quadcopter_firmware/components/imu" -I"/home/phong/Documents/stm32/quadcopter_firmware/components/mcu_port" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-components-2f-imu-2f-mpu9250

clean-components-2f-imu-2f-mpu9250:
	-$(RM) ./components/imu/mpu9250/mpu9250_private.cyclo ./components/imu/mpu9250/mpu9250_private.d ./components/imu/mpu9250/mpu9250_private.o ./components/imu/mpu9250/mpu9250_private.su

.PHONY: clean-components-2f-imu-2f-mpu9250

