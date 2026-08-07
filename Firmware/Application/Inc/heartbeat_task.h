/**
  ******************************************************************************
  * @file    heartbeat_task.h
  * @brief   Public interface for the system heartbeat task.
  ******************************************************************************
  */

#ifndef APPLICATION_HEARTBEAT_TASK_H_
#define APPLICATION_HEARTBEAT_TASK_H_

#include <stdbool.h>

/**
 * @brief Create the system heartbeat task.
 *
 * @return true if the task was created successfully; otherwise, false.
 */
bool HeartbeatTask_Create(void);

#endif /* APPLICATION_HEARTBEAT_TASK_H_ */
