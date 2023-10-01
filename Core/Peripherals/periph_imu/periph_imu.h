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

#ifdef __cplusplus
}
#endif

#endif /* __PERIPH_IMU_H__ */