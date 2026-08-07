/**
  ******************************************************************************
  * @file    led_task.c
  * @brief   LED heartbeat task implementation.
  ******************************************************************************
  */

#include "led_task.h"

#include <stddef.h>

#include "gpio.h"

#define LED_TASK_STACK_DEPTH_WORDS  128U
#define LED_TASK_PRIORITY           (tskIDLE_PRIORITY + 1U)
#define LED_TASK_PERIOD_MS          1000U

static void LED_Task(void *argument)
{
  TickType_t lastWakeTime;

  (void)argument;
  lastWakeTime = xTaskGetTickCount();

  for (;;)
  {
    HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
    vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(LED_TASK_PERIOD_MS));
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
