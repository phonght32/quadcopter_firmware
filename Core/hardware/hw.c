#include "string.h"
#include "tim.h"
#include "spi.h"
#include "gpio.h"
#include "hw_intf.h"
#include "mpu6500_register.h"
#include "ak8963_register.h"

#define HW_MPU6500_SPI_HANDLE		hspi1
#define HW_AK8963_SPI_HANDLE		hspi1

#define HW_MOTORFL_TIM_HANDLE 		htim1
#define HW_MOTORFL_TIM 				TIM1
#define HW_MOTORFL_TIM_CCR 			CCR1
#define HW_MOTORFL_TIM_CHANNEL 		TIM_CHANNEL_1

#define HW_MOTORFR_TIM_HANDLE 		htim1
#define HW_MOTORFR_TIM 				TIM1
#define HW_MOTORFR_TIM_CCR 			CCR2
#define HW_MOTORFR_TIM_CHANNEL 		TIM_CHANNEL_2

#define HW_MOTORBL_TIM_HANDLE 		htim1
#define HW_MOTORBL_TIM 				TIM1
#define HW_MOTORBL_TIM_CCR 			CCR3
#define HW_MOTORBL_TIM_CHANNEL 		TIM_CHANNEL_3

#define HW_MOTORBR_TIM_HANDLE 		htim1
#define HW_MOTORBR_TIM 				TIM1
#define HW_MOTORBR_TIM_CCR 			CCR4
#define HW_MOTORBR_TIM_CHANNEL 		TIM_CHANNEL_4


err_code_t hw_intf_mpu6500_read_bytes(uint8_t reg_addr, uint8_t *buf, uint16_t len, uint32_t timeout_ms)
{
	uint8_t buf_data[1];
	buf_data[0] = reg_addr | 0x80;

	HAL_SPI_Transmit(&HW_MPU6500_SPI_HANDLE, buf_data, 1, timeout_ms);
	HAL_SPI_Receive(&HW_MPU6500_SPI_HANDLE, buf, len, timeout_ms);

	return ERR_CODE_SUCCESS;
}

err_code_t hw_intf_mpu6500_write_bytes(uint8_t reg_addr, uint8_t *buf, uint16_t len, uint32_t timeout_ms)
{
	uint8_t buf_data[len + 1];
	buf_data[0] = reg_addr;
	memcpy(&buf_data[1], buf, len);

	HAL_SPI_Transmit(&HW_MPU6500_SPI_HANDLE, buf_data, 1, timeout_ms);
	HAL_SPI_Transmit(&HW_MPU6500_SPI_HANDLE, &buf_data[1], len, timeout_ms);

	return ERR_CODE_SUCCESS;
}

err_code_t hw_intf_ak8963_read_bytes(uint8_t reg_addr, uint8_t *buf, uint16_t len, uint32_t timeout_ms)
{
	uint8_t byte_data = 0;

	/* Set slave 0 to the AK8963 and set for read */
	byte_data = MPU6500_I2C_SLV0_ADDR | 0x80;
	HAL_SPI_Transmit(&HW_AK8963_SPI_HANDLE, &byte_data, 1, timeout_ms);
	byte_data = AK8963_ADDR;
	HAL_SPI_Transmit(&HW_AK8963_SPI_HANDLE, &byte_data, 1, timeout_ms);

	// set the register to the desired AK8963 sub address
	byte_data = MPU6500_I2C_SLV0_REG;
	HAL_SPI_Transmit(&HW_AK8963_SPI_HANDLE, &byte_data, 1, timeout_ms);
	byte_data = reg_addr;
	HAL_SPI_Transmit(&HW_AK8963_SPI_HANDLE, &byte_data, 1, timeout_ms);

	// enable I2C and request the bytes
	byte_data = MPU6500_I2C_SLV0_CTRL;
	HAL_SPI_Transmit(&HW_AK8963_SPI_HANDLE, &byte_data, 1, timeout_ms);
	byte_data = reg_addr;
	HAL_SPI_Transmit(&HW_AK8963_SPI_HANDLE, &byte_data, 1, timeout_ms);

	/* Takes some time for these registers to fill */

	/* Read the bytes off the MPU9250 EXT_SENS_DATA registers */
	uint8_t buf_data[1];
	buf_data[0] = MPU6500_EXT_SENS_DATA_00 | 0x80;

	HAL_SPI_Transmit(&HW_AK8963_SPI_HANDLE, buf_data, 1, timeout_ms);
	HAL_SPI_Receive(&HW_AK8963_SPI_HANDLE, buf, len, timeout_ms);

	return ERR_CODE_SUCCESS;
}

err_code_t hw_intf_ak8963_write_bytes(uint8_t reg_addr, uint8_t *buf, uint16_t len, uint32_t timeout_ms)
{
	uint8_t byte_data = 0;

	/* Set slave 0 to the AK8963 and set for write */
	byte_data = MPU6500_I2C_SLV0_ADDR;
	HAL_SPI_Transmit(&HW_AK8963_SPI_HANDLE, &byte_data, 1, timeout_ms);
	byte_data = AK8963_ADDR;
	HAL_SPI_Transmit(&HW_AK8963_SPI_HANDLE, &byte_data, 1, timeout_ms);

	/* Set the register to the desired AK8963 sub address */
	byte_data = MPU6500_I2C_SLV0_REG;
	HAL_SPI_Transmit(&HW_AK8963_SPI_HANDLE, &byte_data, 1, timeout_ms);
	byte_data = reg_addr;
	HAL_SPI_Transmit(&HW_AK8963_SPI_HANDLE, &byte_data, 1, timeout_ms);

	/* Store the data for write */
	uint8_t buf_data[len + 1];
	buf_data[0] = MPU6500_I2C_SLV0_DO;
	memcpy(&buf_data[1], buf, len);
	HAL_SPI_Transmit(&HW_AK8963_SPI_HANDLE, buf_data, 1, timeout_ms);
	HAL_SPI_Transmit(&HW_AK8963_SPI_HANDLE, &buf_data[1], len, timeout_ms);

	/* Enable I2C and send 1 byte */
	byte_data = MPU6500_I2C_SLV0_CTRL;
	HAL_SPI_Transmit(&HW_AK8963_SPI_HANDLE, &byte_data, 1, timeout_ms);
	byte_data = 0x80 | 1;
	HAL_SPI_Transmit(&HW_AK8963_SPI_HANDLE, &byte_data, 1, timeout_ms);

	return ERR_CODE_SUCCESS;
}

err_code_t hw_intf_motorfl_set_pwm(float duty)
{
	float timer_compare_value = duty / 100 * (float)HW_MOTORFL_TIM->ARR;
	__HAL_TIM_SET_COMPARE(&HW_MOTORFL_TIM_HANDLE, HW_MOTORFL_TIM_CHANNEL, (uint32_t)timer_compare_value);

	return ERR_CODE_SUCCESS;
}

err_code_t hw_intf_motorfl_start(void)
{
	HAL_TIM_PWM_Start(&HW_MOTORFL_TIM_HANDLE, HW_MOTORFL_TIM_CHANNEL);

	return ERR_CODE_SUCCESS;
}

err_code_t hw_intf_motorfl_stop(void)
{
	HAL_TIM_PWM_Stop(&HW_MOTORFL_TIM_HANDLE, HW_MOTORFL_TIM_CHANNEL);

	return ERR_CODE_SUCCESS;
}

err_code_t hw_intf_motorfr_set_pwm(float duty)
{
	float timer_compare_value = duty / 100 * (float)HW_MOTORFR_TIM->ARR;
	__HAL_TIM_SET_COMPARE(&HW_MOTORFR_TIM_HANDLE, HW_MOTORFR_TIM_CHANNEL, (uint32_t)timer_compare_value);

	return ERR_CODE_SUCCESS;
}

err_code_t hw_intf_motorfr_start(void)
{
	HAL_TIM_PWM_Start(&HW_MOTORFR_TIM_HANDLE, HW_MOTORFR_TIM_CHANNEL);

	return ERR_CODE_SUCCESS;
}

err_code_t hw_intf_motorfr_stop(void)
{
	HAL_TIM_PWM_Stop(&HW_MOTORFR_TIM_HANDLE, HW_MOTORFR_TIM_CHANNEL);

	return ERR_CODE_SUCCESS;
}

err_code_t hw_intf_motorbl_set_pwm(float duty)
{
	float timer_compare_value = duty / 100 * (float)HW_MOTORBL_TIM->ARR;
	__HAL_TIM_SET_COMPARE(&HW_MOTORBL_TIM_HANDLE, HW_MOTORBL_TIM_CHANNEL, (uint32_t)timer_compare_value);

	return ERR_CODE_SUCCESS;
}

err_code_t hw_intf_motorbl_start(void)
{
	HAL_TIM_PWM_Start(&HW_MOTORBL_TIM_HANDLE, HW_MOTORBL_TIM_CHANNEL);

	return ERR_CODE_SUCCESS;
}

err_code_t hw_intf_motorbl_stop(void)
{
	HAL_TIM_PWM_Stop(&HW_MOTORBL_TIM_HANDLE, HW_MOTORBL_TIM_CHANNEL);

	return ERR_CODE_SUCCESS;
}

err_code_t hw_intf_motorbr_set_pwm(float duty)
{
	float timer_compare_value = duty / 100 * (float)HW_MOTORBR_TIM->ARR;
	__HAL_TIM_SET_COMPARE(&HW_MOTORBR_TIM_HANDLE, HW_MOTORBR_TIM_CHANNEL, (uint32_t)timer_compare_value);

	return ERR_CODE_SUCCESS;
}

err_code_t hw_intf_motorbr_start(void)
{
	HAL_TIM_PWM_Start(&HW_MOTORBR_TIM_HANDLE, HW_MOTORBR_TIM_CHANNEL);

	return ERR_CODE_SUCCESS;
}

err_code_t hw_intf_motorbr_stop(void)
{
	HAL_TIM_PWM_Stop(&HW_MOTORBR_TIM_HANDLE, HW_MOTORBR_TIM_CHANNEL);

	return ERR_CODE_SUCCESS;
}
