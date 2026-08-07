/**
  ******************************************************************************
  * @file    led_task.c
  * @brief   LED heartbeat task implementation.
  ******************************************************************************
  */

#include "led_task.h"

#include <stddef.h>

#include "gpio.h"

#include "system_state_manager.h"

#define LED_TASK_STACK_DEPTH_WORDS  128U
#define LED_TASK_PRIORITY           (tskIDLE_PRIORITY + 1U)
#define LED_TASK_PERIOD_MS_BOOT		5000U
#define LED_TASK_PERIOD_MS_INIT		500U
#define LED_TASK_PERIOD_MS_STOPPED	1000U
#define LED_TASK_PERIOD_MS_RUNNING	0U
#define LED_TASK_PERIOD_MS_FAULT	50U


static void LED_Task(void *argument)
{
  TickType_t lastWakeTime;
  TickType_t periodTicks;
  SystemState_t currentState;

  (void)argument;
  lastWakeTime = xTaskGetTickCount();

  for (;;)
  {
	currentState = SystemStateManager_GetState();
	/**
	 * LED has different blinking period according to the system states.
	 */
	switch (currentState)
	{
	case SYSTEM_STATE_BOOT:
		periodTicks = pdMS_TO_TICKS(LED_TASK_PERIOD_MS_BOOT);
		break;

	case SYSTEM_STATE_INIT:
		periodTicks = pdMS_TO_TICKS(LED_TASK_PERIOD_MS_INIT);
		break;

	case SYSTEM_STATE_STOPPED:
		periodTicks = pdMS_TO_TICKS(LED_TASK_PERIOD_MS_STOPPED);
		break;

	case SYSTEM_STATE_RUNNING:
		periodTicks = pdMS_TO_TICKS(LED_TASK_PERIOD_MS_RUNNING);
		break;

	case SYSTEM_STATE_FAULT:
		periodTicks = pdMS_TO_TICKS(LED_TASK_PERIOD_MS_FAULT);
	}

    HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
    vTaskDelayUntil(&lastWakeTime, periodTicks);
  }
}

BaseType_t TaskCreate_LEDTask(void)
{
  return xTaskCreate(
      LED_Task,
      "LED",
      LED_TASK_STACK_DEPTH_WORDS,
      NULL,
      LED_TASK_PRIORITY,
      NULL);
}
