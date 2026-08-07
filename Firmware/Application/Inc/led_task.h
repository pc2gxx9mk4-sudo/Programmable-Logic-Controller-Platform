/**
  ******************************************************************************
  * @file    led_task.h
  * @brief   Public interface for the LED heartbeat task.
  ******************************************************************************
  */

#ifndef APPLICATION_LED_TASK_H_
#define APPLICATION_LED_TASK_H_

#include "FreeRTOS.h"
#include "task.h"

/**
 * @brief Create the LED heartbeat task.
 *
 * @return pdPASS if the task was created successfully; otherwise, pdFAIL.
 */
BaseType_t TaskCreate_LEDTask(void);

#endif /* APPLICATION_LED_TASK_H_ */
