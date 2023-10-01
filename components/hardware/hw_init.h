#ifndef __HARDWARE_INIT_H__
#define __HARDWARE_INIT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "err_code.h"

/*
 * @brief   Initialize IMU.
 *
 * @param 	None.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t hw_init_imu(void);

/*
 * @brief   Initialize IMU filter.
 *
 * @param 	None.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t hw_init_imu_filter(void);

/*
 * @brief   Initialize BLDC motor.
 *
 * @param 	None.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t hw_init_bldc_motor(void);



#ifdef __cplusplus
}
#endif

#endif /* __HARDWARE_INIT_H__ */