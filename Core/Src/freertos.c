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
#include "os_service.h"
/* USER CODE END Includes */
/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */
/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */
/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */
/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
/* USER CODE END Variables */
/* Definitions for regular_task */
osThreadId_t regular_taskHandle;
const osThreadAttr_t regular_task_attributes = {
    .name = "regular_task",
    .stack_size = 256 * 4,
    .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for critical_task */
osThreadId_t critical_taskHandle;
const osThreadAttr_t critical_task_attributes = {
    .name = "critical_task",
    .stack_size = 256 * 4,
    .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for cyclic_timer */
osTimerId_t cyclic_timerHandle;
const osTimerAttr_t cyclic_timer_attributes = {
    .name = "cyclic_timer"
};
/* Definitions for OS_EVENT */
osEventFlagsId_t OS_EVENTHandle;
const osEventFlagsAttr_t OS_EVENT_attributes = {
    .name = "OS_EVENT"
};
/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
/* USER CODE END FunctionPrototypes */
void regularTask(void *argument);
extern void critical_task_main(void *argument);
extern void cyclic_timer_callback(void *argument);
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
    regular_taskHandle = osThreadNew(regularTask, NULL, &regular_task_attributes);
    /* creation of critical_task */
    critical_taskHandle = osThreadNew(critical_task_main, NULL, &critical_task_attributes);
    /* USER CODE BEGIN RTOS_THREADS */
    /* add threads, ... */
    /* USER CODE END RTOS_THREADS */
    /* Create the event(s) */
    /* creation of OS_EVENT */
    OS_EVENTHandle = osEventFlagsNew(&OS_EVENT_attributes);
    /* USER CODE BEGIN RTOS_EVENTS */
    /* add events, ... */
    /* USER CODE END RTOS_EVENTS */
}
/* USER CODE BEGIN Header_regularTask */
/**
  * @brief  Function implementing the regular_task thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_regularTask */
void regularTask(void *argument)
{
    /* USER CODE BEGIN regularTask */
    /* Infinite loop */
    regular_task_main(argument);
    /* USER CODE END regularTask */
}
/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
/* USER CODE END Application */
