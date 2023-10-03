#ifndef __HARDWARE_INTF_H__
#define __HARDWARE_INTF_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "err_code.h"

/*
 * @brief   AK8963 read bytes function.
 *
 * @param   reg_addr Register address.
 * @param 	buf Buffer data.
 * @param 	len Length.
 * @param 	timeout_ms Timeout in miliseconds.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t hw_intf_ak8963_read_bytes(uint8_t reg_addr, uint8_t *buf, uint16_t len, uint32_t timeout_ms);

/*
 * @brief   AK8963 write bytes function.
 *
 * @param   reg_addr Register address.
 * @param 	buf Buffer data.
 * @param 	len Length.
 * @param 	timeout_ms Timeout in miliseconds.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t hw_intf_ak8963_write_bytes(uint8_t reg_addr, uint8_t *buf, uint16_t len, uint32_t timeout_ms);

/*
 * @brief   MPU6500 read bytes function.
 *
 * @param   reg_addr Register address.
 * @param 	buf Buffer data.
 * @param 	len Length.
 * @param 	timeout_ms Timeout in miliseconds.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t hw_intf_mpu6500_read_bytes(uint8_t reg_addr, uint8_t *buf, uint16_t len, uint32_t timeout_ms);

/*
 * @brief   MPU6500 write bytes function.
 *
 * @param   reg_addr Register address.
 * @param 	buf Buffer data.
 * @param 	len Length.
 * @param 	timeout_ms Timeout in miliseconds.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t hw_intf_mpu6500_write_bytes(uint8_t reg_addr, uint8_t *buf, uint16_t len, uint32_t timeout_ms);

/*
 * @brief   MPU6050 read bytes function.
 *
 * @param   reg_addr Register address.
 * @param 	buf Buffer data.
 * @param 	len Length.
 * @param 	timeout_ms Timeout in miliseconds.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t hw_intf_mpu6050_read_bytes(uint8_t reg_addr, uint8_t *buf, uint16_t len, uint32_t timeout_ms);

/*
 * @brief   MPU6050 write bytes function.
 *
 * @param   reg_addr Register address.
 * @param 	buf Buffer data.
 * @param 	len Length.
 * @param 	timeout_ms Timeout in miliseconds.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t hw_intf_mpu6050_write_bytes(uint8_t reg_addr, uint8_t *buf, uint16_t len, uint32_t timeout_ms);

/*
 * @brief   Set PWM for BLDC motor front left.
 *
 * @param   duty Duty cycle.
 *
 * @return
 *      - Handle structure: Success.
 *      - Others:           Fail.
 */
err_code_t hw_intf_motorfl_set_pwm(float duty);

/*
 * @brief   Start BLDC motor front left.
 *
 * @param   None.
 *
 * @return
 *      - Handle structure: Success.
 *      - Others:           Fail.
 */
err_code_t hw_intf_motorfl_start(void);

/*
 * @brief   Stop BLDC motor front left.
 *
 * @param   None.
 *
 * @return
 *      - Handle structure: Success.
 *      - Others:           Fail.
 */
err_code_t hw_intf_motorfl_stop(void);

/*
 * @brief   Set PWM for BLDC motor front right.
 *
 * @param   duty Duty cycle.
 *
 * @return
 *      - Handle structure: Success.
 *      - Others:           Fail.
 */
err_code_t hw_intf_motorfr_set_pwm(float duty);

/*
 * @brief   Start BLDC motor front right.
 *
 * @param   None.
 *
 * @return
 *      - Handle structure: Success.
 *      - Others:           Fail.
 */
err_code_t hw_intf_motorfr_start(void);

/*
 * @brief   Stop BLDC motor front right.
 *
 * @param   None.
 *
 * @return
 *      - Handle structure: Success.
 *      - Others:           Fail.
 */
err_code_t hw_intf_motorfr_stop(void);

/*
 * @brief   Set PWM for BLDC motor back left.
 *
 * @param   duty Duty cycle.
 *
 * @return
 *      - Handle structure: Success.
 *      - Others:           Fail.
 */
err_code_t hw_intf_motorbl_set_pwm(float duty);

/*
 * @brief   Start BLDC motor back left.
 *
 * @param   None.
 *
 * @return
 *      - Handle structure: Success.
 *      - Others:           Fail.
 */
err_code_t hw_intf_motorbl_start(void);

/*
 * @brief   Stop BLDC motor back left.
 *
 * @param   None.
 *
 * @return
 *      - Handle structure: Success.
 *      - Others:           Fail.
 */
err_code_t hw_intf_motorbl_stop(void);

/*
 * @brief   Set PWM for BLDC motor back right.
 *
 * @param   duty Duty cycle.
 *
 * @return
 *      - Handle structure: Success.
 *      - Others:           Fail.
 */
err_code_t hw_intf_motorbr_set_pwm(float duty);

/*
 * @brief   Start BLDC motor back right.
 *
 * @param   None.
 *
 * @return
 *      - Handle structure: Success.
 *      - Others:           Fail.
 */
err_code_t hw_intf_motorbr_start(void);

/*
 * @brief   Stop BLDC motor back right.
 *
 * @param   None.
 *
 * @return
 *      - Handle structure: Success.
 *      - Others:           Fail.
 */
err_code_t hw_intf_motorbr_stop(void);

#ifdef __cplusplus
}
#endif

#endif /* __HARDWARE_INTF_H__ */