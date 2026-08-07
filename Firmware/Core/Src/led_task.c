/*
 * led_task.c
 *
 *  Created on: Aug 6, 2026
 *      Author: ericlin
 */


#include "led_task.h"
#include "cmsis_os.h"
#include "gpio.h"

#define LED_TASK_STACK_SIZE 128U
#define LED_TASK_PRIORITY 1U
/**
  * @brief The heartbeat task.
  */
void LED_Task(void *pvParameters)
{
	  (void)pvParameters;

	  TickType_t xLastWakeTime = xTaskGetTickCount();

	  for(;;){
		  HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);

		  vTaskDelayUntil(
				  &xLastWakeTime,
				  pdMS_TO_TICKS(1000U)
		  );
	 }
}

/**
  * @brief Create LED Task
  */
BaseType_t TaskCreate_LEDTask(void)
{
	return xTaskCreate(LED_Task, "LED", LED_TASK_STACK_SIZE, NULL, LED_TASK_PRIORITY, NULL);
}
