#ifndef __PERIPH_MOTOR_H__
#define __PERIPH_MOTOR_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "err_code.h"

/*
 * @brief  	Initialize all motor.
 *
 * @param   None.
 *
 * @return
 *      - ERR_CODE_SUCCESS:	Success.
 *      - Others:   		Fail.
 */
err_code_t periph_motor_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __PERIPH_MOTOR_H__ */