/**
  ******************************************************************************
  * @file    heartbeat_task.c
  * @brief   System heartbeat task implementation.
  ******************************************************************************
  */

#include "heartbeat_task.h"

#include <stddef.h>

#include "cmsis_os2.h"
#include "gpio.h"

#define HEARTBEAT_TASK_STACK_SIZE_BYTES  512U

static osThreadId_t heartbeatTaskHandle = NULL;

static const osThreadAttr_t heartbeatTaskAttributes =
{
  .name = "heartbeat",
  .stack_size = HEARTBEAT_TASK_STACK_SIZE_BYTES,
  .priority = osPriorityLow
};

static void HeartbeatTask_Run(void *argument)
{
  uint32_t nextWakeTime;
  const uint32_t periodTicks = osKernelGetTickFreq();

  (void)argument;
  nextWakeTime = osKernelGetTickCount();

  for (;;)
  {
    HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
    nextWakeTime += periodTicks;
    (void)osDelayUntil(nextWakeTime);
  }
}

bool HeartbeatTask_Create(void)
{
  if (heartbeatTaskHandle != NULL)
  {
    return false;
  }

  heartbeatTaskHandle = osThreadNew(
      HeartbeatTask_Run,
      NULL,
      &heartbeatTaskAttributes);

  return heartbeatTaskHandle != NULL;
}
