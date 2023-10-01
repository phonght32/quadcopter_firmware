#include "tim.h"
#include "spi.h"
#include "gpio.h"
#include "hw_intf.h"

#define HW_SPI_MPU6050				hspi1
#define HW_SPI_AK8963				hspi1

#define HW_TIM_MOTOR_FRONT_LEFT 	htim1
#define HW_TIM_MOTOR_FRONT_RIGHT 	htim1
#define HW_TIM_MOTOR_BACK_LEFT 		htim1
#define HW_TIM_MOTOR_BACK_RIGHT 	htim1

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
	return ERR_CODE_SUCCESS;
}

err_code_t hw_intf_motorfl_start(void)
{
	return ERR_CODE_SUCCESS;
}

err_code_t hw_intf_motorfl_stop(void)
{
	return ERR_CODE_SUCCESS;
}

err_code_t hw_intf_motorfr_set_pwm(float duty)
{
	return ERR_CODE_SUCCESS;
}

err_code_t hw_intf_motorfr_start(void)
{
	return ERR_CODE_SUCCESS;
}

err_code_t hw_intf_motorfr_stop(void)
{
	return ERR_CODE_SUCCESS;
}

err_code_t hw_intf_motorbl_set_pwm(float duty)
{
	return ERR_CODE_SUCCESS;
}

err_code_t hw_intf_motorbl_start(void)
{
	return ERR_CODE_SUCCESS;
}

err_code_t hw_intf_motorbl_stop(void)
{
	return ERR_CODE_SUCCESS;
}

err_code_t hw_intf_motorbr_set_pwm(float duty)
{
	return ERR_CODE_SUCCESS;
}

err_code_t hw_intf_motorbr_start(void)
{
	return ERR_CODE_SUCCESS;
}

err_code_t hw_intf_motorbr_stop(void)
{
	return ERR_CODE_SUCCESS;
}
