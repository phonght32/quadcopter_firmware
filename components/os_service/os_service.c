#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "os_service.h"


void regular_task_main(void *argument)
{
	while (1)
	{
		osDelay(5);
	}
	vTaskDelete(NULL);
}

void critical_task_main(void *argument)
{
	while (1)
	{
		osDelay(5);
	}
	vTaskDelete(NULL);
}

void cyclic_timer_callback(void *argument)
{
	
}

