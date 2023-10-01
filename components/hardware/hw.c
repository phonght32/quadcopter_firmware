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

err_code_t hw_intf_mpu6050_read_bytes(uint8_t reg_addr, uint8_t *buf, uint16_t len, uint32_t timeout_ms)
{
	return ERR_CODE_SUCCESS;
}

err_code_t hw_intf_mpu6050_write_bytes(uint8_t reg_addr, uint8_t *buf, uint16_t len, uint32_t timeout_ms)
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

err_code_t hw_init_imu(void)
{
	return ERR_CODE_SUCCESS;
}

err_code_t hw_init_imu_filter(void)
{
	return ERR_CODE_SUCCESS;
}

err_code_t hw_init_bldc_motor(void)
{
	return ERR_CODE_SUCCESS;
}
