#ifndef __OS_SERVICE_H__
#define __OS_SERVICE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "err_code.h"

/*
 * @brief   Regular task main.
 *
 * @param   argument Pointer argument.
 *
 * @return 	None.
 */
void regular_task_main(void *argument);

/*
 * @brief   Critical task main.
 *
 * @param   argument Pointer argument.
 *
 * @return 	None.
 */
void critical_task_main(void *argument);

/*
 * @brief   Cyclic timer callback.
 *
 * @param   argument Pointer argument.
 *
 * @return 	None.
 */
void cyclic_timer_callback(void *argument);

#ifdef __cplusplus
}
#endif

#endif  /* __OS_SERVICE_H__ */




