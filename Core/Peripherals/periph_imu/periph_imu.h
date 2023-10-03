#ifndef __PERIPH_IMU_H__
#define __PERIPH_IMU_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "err_code.h"

/*
 * @brief  	Initialize IMU and filter.
 *
 * @param   None.
 *
 * @return
 *      - ERR_CODE_SUCCESS:	Success.
 *      - Others:   		Fail.
 */
err_code_t periph_imu_init(void);

/*
 * @brief  	Update quaternion.
 *
 * @param   None.
 *
 * @return
 *      - ERR_CODE_SUCCESS:	Success.
 *      - Others:   		Fail.
 */
err_code_t periph_imu_update_quat(void);

/*
 * @brief  	Get quaternion.
 *
 * @param   q0 Q0.
 * @param   q1 Q1.
 * @param   q2 Q2.
 * @param   q3 Q3.
 *
 * @return
 *      - ERR_CODE_SUCCESS:	Success.
 *      - Others:   		Fail.
 */
err_code_t periph_imu_get_quat(float *q0, float *q1, float *q2, float* q3);

#ifdef __cplusplus
}
#endif

#endif /* __PERIPH_IMU_H__ */