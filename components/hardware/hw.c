#include "tim.h"
#include "spi.h"
#include "gpio.h"
#include "hw_intf.h"

#define HW_SPI_MPU6050				hspi1
#define HW_SPI_AK8963				hspi1

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
	return ERR_CODE_SUCCESS;
}

err_code_t hw_intf_mpu6500_write_bytes(uint8_t reg_addr, uint8_t *buf, uint16_t len, uint32_t timeout_ms)
{
	return ERR_CODE_SUCCESS;
}

err_code_t hw_intf_ak8963_read_bytes(uint8_t reg_addr, uint8_t *buf, uint16_t len, uint32_t timeout_ms)
{
	return ERR_CODE_SUCCESS;
}

err_code_t hw_intf_ak8963_write_bytes(uint8_t reg_addr, uint8_t *buf, uint16_t len, uint32_t timeout_ms)
{
	return ERR_CODE_SUCCESS;
}

err_code_t hw_intf_motorfl_set_pwm(float duty)
{
	float cnt = duty * (float)HW_MOTORFL_TIM->ARR;
	HW_MOTORFL_TIM->HW_MOTORFL_TIM_CCR = (uint32_t)cnt;

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
	float cnt = duty * (float)HW_MOTORFR_TIM->ARR;
	HW_MOTORFR_TIM->HW_MOTORFR_TIM_CCR = (uint32_t)cnt;

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
	float cnt = duty * (float)HW_MOTORBL_TIM->ARR;
	HW_MOTORBL_TIM->HW_MOTORBL_TIM_CCR = (uint32_t)cnt;

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
	float cnt = duty * (float)HW_MOTORBR_TIM->ARR;
	HW_MOTORBR_TIM->HW_MOTORBR_TIM_CCR = (uint32_t)cnt;

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
