/**
  ******************************************************************************
  * @file    plc_command_task.h
  * @brief   Queued PLC command task public interface.
  ******************************************************************************
  */

#ifndef APPLICATION_PLC_COMMAND_TASK_H_
#define APPLICATION_PLC_COMMAND_TASK_H_

#include <stdint.h>

#include "FreeRTOS.h"

#include "plc_command.h"

BaseType_t PlcCommandTask_Create(void);

PlcCommandResult_t PlcCommandTask_Submit(
    const PlcCommand_t *command,
    TickType_t waitTicks);

BaseType_t PlcCommandTask_ReceiveResponse(
    PlcCommandResponse_t *response,
    TickType_t waitTicks);

uint32_t PlcCommandTask_GetDroppedResponseCount(void);

#endif /* APPLICATION_PLC_COMMAND_TASK_H_ */
