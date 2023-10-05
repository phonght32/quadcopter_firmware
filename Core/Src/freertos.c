/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "serial_log.h"
#include "periph_imu.h"
#include "math.h"
/* USER CODE END Includes */
/* Private typedef -----------------------------------------------------------*/
typedef StaticEventGroup_t osStaticEventGroupDef_t;
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */
/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define OS_CYCLIC_TIMER_TICK    1

#define OS_TASK_BLOCKING        portMAX_DELAY
#define OS_TASK_NON_BLOCKING    0

#define OS_EVENT_CYCLIC_1MS     1
#define OS_EVENT_CYCLIC_5MS     2
#define OS_EVENT_CYCLIC_500MS   3
/* USER CODE END PD */
/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */
/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
float roll, pitch, yaw;
/* USER CODE END Variables */
/* Definitions for regular_task */
osThreadId_t regular_taskHandle;
const osThreadAttr_t regular_task_attributes = {
    .name = "regular_task",
    .stack_size = 512 * 4,
    .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for cyclic_timer */
osTimerId_t cyclic_timerHandle;
const osTimerAttr_t cyclic_timer_attributes = {
    .name = "cyclic_timer"
};
/* Definitions for regular_event */
osEventFlagsId_t regular_eventHandle;
osStaticEventGroupDef_t regular_event_ctrl;
const osEventFlagsAttr_t regular_event_attributes = {
    .name = "regular_event",
    .cb_mem = &regular_event_ctrl,
    .cb_size = sizeof(regular_event_ctrl),
};
/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
/* USER CODE END FunctionPrototypes */
void regular_task_main(void *argument);
void cyclic_timer_callback(void *argument);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */
/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
    /* USER CODE BEGIN Init */
    /* USER CODE END Init */
    /* USER CODE BEGIN RTOS_MUTEX */
    /* add mutexes, ... */
    /* USER CODE END RTOS_MUTEX */
    /* USER CODE BEGIN RTOS_SEMAPHORES */
    /* add semaphores, ... */
    /* USER CODE END RTOS_SEMAPHORES */
    /* Create the timer(s) */
    /* creation of cyclic_timer */
    cyclic_timerHandle = osTimerNew(cyclic_timer_callback, osTimerPeriodic, NULL, &cyclic_timer_attributes);
    /* USER CODE BEGIN RTOS_TIMERS */
    /* start timers, add new ones, ... */
    /* USER CODE END RTOS_TIMERS */
    /* USER CODE BEGIN RTOS_QUEUES */
    /* add queues, ... */
    /* USER CODE END RTOS_QUEUES */
    /* Create the thread(s) */
    /* creation of regular_task */
    regular_taskHandle = osThreadNew(regular_task_main, NULL, &regular_task_attributes);
    /* USER CODE BEGIN RTOS_THREADS */
    /* add threads, ... */
    /* USER CODE END RTOS_THREADS */
    /* Create the event(s) */
    /* creation of regular_event */
    regular_eventHandle = osEventFlagsNew(&regular_event_attributes);
    /* USER CODE BEGIN RTOS_EVENTS */
    /* add events, ... */
    /* USER CODE END RTOS_EVENTS */
}
/* USER CODE BEGIN Header_regular_task_main */
/**
  * @brief  Function implementing the regular_task thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_regular_task_main */
void regular_task_main(void *argument)
{
    /* USER CODE BEGIN regular_task_main */
    uint32_t regular_event;
    osTimerStart(cyclic_timerHandle, OS_CYCLIC_TIMER_TICK);
    /* Infinite loop */
    for (;;)
    {
        regular_event = osEventFlagsWait(regular_eventHandle,
                                         OS_EVENT_CYCLIC_1MS | OS_EVENT_CYCLIC_5MS,
                                         pdTRUE,
                                         OS_TASK_BLOCKING);
        if (regular_event & OS_EVENT_CYCLIC_1MS)
        {

        }
        if (regular_event & OS_EVENT_CYCLIC_5MS)
        {
            float q0, q1, q2, q3;
            periph_imu_update_quat();
            periph_imu_get_quat(&q0, &q1, &q2, &q3);

            roll = 180.0 / 3.14 * atan2(2 * (q0 * q1 + q2 * q3), 1 - 2 * (q1 * q1 + q2 * q2));
            pitch = 180.0 / 3.14 * asin(2 * (q0 * q2 - q3 * q1));
            yaw = 180.0 / 3.14 * atan2f(q0 * q3 + q1 * q2, 0.5f - q2 * q2 - q3 * q3);
        }
        if (regular_event & OS_EVENT_CYCLIC_500MS)
        {
        	SERIAL_LOGI("RTOS", "roll: %7.4f\t\tpitch: %7.4f\t\tyaw: %7.4f\t", roll, pitch, yaw);
        }
    }
    /* USER CODE END regular_task_main */
}
/* cyclic_timer_callback function */
void cyclic_timer_callback(void *argument)
{
    /* USER CODE BEGIN cyclic_timer_callback */
    static uint16_t cnt_cycle;

    osEventFlagsSet(regular_eventHandle, OS_EVENT_CYCLIC_1MS);

    if (cnt_cycle == 4)
    {
        osEventFlagsSet(regular_eventHandle, OS_EVENT_CYCLIC_5MS);
    }
    else if (cnt_cycle == 499)
    {
        osEventFlagsSet(regular_eventHandle, OS_EVENT_CYCLIC_5MS | OS_EVENT_CYCLIC_500MS);
    }
    else
    {

    }

    cnt_cycle++;
    if (cnt_cycle == 8)
    {
        cnt_cycle = 0;
    }

    /* USER CODE END cyclic_timer_callback */
}
/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
/* USER CODE END Application */
