/**
  ******************************************************************************
  * @file    plc_command_task.c
  * @brief   Queued PLC command task implementation.
  ******************************************************************************
  */

#include "plc_command_task.h"

#include <stddef.h>
#include <string.h>

#include "queue.h"
#include "task.h"

#include "system_state_manager.h"

#define COMMAND_QUEUE_ELEMENT_COUNT   8U
#define RESPONSE_QUEUE_ELEMENT_COUNT  8U
#define PLC_COMMAND_TASK_STACK_DEPTH  256U
#define PLC_COMMAND_TASK_PRIORITY     (tskIDLE_PRIORITY + 2U)

static QueueHandle_t commandQueue = NULL;
static QueueHandle_t responseQueue = NULL;
static uint32_t droppedResponseCount = 0U;

static PlcCommandResult_t PlcCommandTask_ProcessCommand(
    const PlcCommand_t *command,
    PlcCommandResponse_t *response);
static void PlcCommandTask_GenerateResponse(
    const PlcCommand_t *command,
    PlcCommandResponse_t *response);
static BaseType_t PlcCommandTask_SendResponse(
    const PlcCommandResponse_t *response);
static void PlcCommandTask_Run(void *argument);

static PlcCommandResult_t PlcCommandTask_ProcessCommand(
    const PlcCommand_t *command,
    PlcCommandResponse_t *response)
{
  PlcCommandResult_t validationResult = PlcCommand_Validate(command);

  if (validationResult != PLC_COMMAND_RESULT_OK)
  {
    return validationResult;
  }

  switch (command->type)
  {
    case PLC_COMMAND_TYPE_STOP:
      if (SystemStateManager_RequestStop())
      {
        return PLC_COMMAND_RESULT_OK;
      }

      return PLC_COMMAND_RESULT_INVALID_STATE;

    case PLC_COMMAND_TYPE_GET_STATUS:
      response->payload.getStatus.systemState =
          SystemStateManager_GetState();
      return PLC_COMMAND_RESULT_OK;

    case PLC_COMMAND_TYPE_RUN:
    case PLC_COMMAND_TYPE_CLEAR_FAULT:
    case PLC_COMMAND_TYPE_SET_PWM_DUTY:
      return PLC_COMMAND_RESULT_NOT_SUPPORTED;

    case PLC_COMMAND_TYPE_NONE:
    default:
      return PLC_COMMAND_RESULT_INVALID_TYPE;
  }
}

static void PlcCommandTask_GenerateResponse(
    const PlcCommand_t *command,
    PlcCommandResponse_t *response)
{
  (void)memset(response, 0, sizeof(*response));

  response->destination = command->source;
  response->commandType = command->type;
  response->sequenceNumber = command->sequenceNumber;
  response->result = PLC_COMMAND_RESULT_UNPROCESSED;
}

static BaseType_t PlcCommandTask_SendResponse(
    const PlcCommandResponse_t *response)
{
  return xQueueSendToBack(responseQueue, response, 0U);
}

static void PlcCommandTask_Run(void *argument)
{
  PlcCommand_t command;
  PlcCommandResponse_t response;

  (void)argument;

  for (;;)
  {
    if (xQueueReceive(commandQueue, &command, portMAX_DELAY) == pdPASS)
    {
      PlcCommandTask_GenerateResponse(&command, &response);
      response.result = PlcCommandTask_ProcessCommand(&command, &response);

      if (PlcCommandTask_SendResponse(&response) != pdPASS)
      {
        droppedResponseCount++;
      }
    }
  }
}

BaseType_t PlcCommandTask_Create(void)
{
  BaseType_t taskCreateResult;

  if ((commandQueue != NULL) || (responseQueue != NULL))
  {
    return pdFAIL;
  }

  commandQueue = xQueueCreate(
      COMMAND_QUEUE_ELEMENT_COUNT,
      sizeof(PlcCommand_t));

  if (commandQueue == NULL)
  {
    return pdFAIL;
  }

  responseQueue = xQueueCreate(
      RESPONSE_QUEUE_ELEMENT_COUNT,
      sizeof(PlcCommandResponse_t));

  if (responseQueue == NULL)
  {
    vQueueDelete(commandQueue);
    commandQueue = NULL;
    return pdFAIL;
  }

  droppedResponseCount = 0U;

  taskCreateResult = xTaskCreate(
      PlcCommandTask_Run,
      "PlcCommand",
      PLC_COMMAND_TASK_STACK_DEPTH,
      NULL,
      PLC_COMMAND_TASK_PRIORITY,
      NULL);

  if (taskCreateResult != pdPASS)
  {
    vQueueDelete(responseQueue);
    vQueueDelete(commandQueue);
    responseQueue = NULL;
    commandQueue = NULL;
    return pdFAIL;
  }

  return pdPASS;
}

PlcCommandResult_t PlcCommandTask_Submit(
    const PlcCommand_t *command,
    TickType_t waitTicks)
{
  PlcCommandResult_t validationResult;

  if (command == NULL)
  {
    return PLC_COMMAND_RESULT_INVALID_ARGUMENT;
  }

  validationResult = PlcCommand_Validate(command);

  if (validationResult != PLC_COMMAND_RESULT_OK)
  {
    return validationResult;
  }

  if (commandQueue == NULL)
  {
    return PLC_COMMAND_RESULT_BUSY;
  }

  if (xQueueSendToBack(commandQueue, command, waitTicks) != pdPASS)
  {
    return PLC_COMMAND_RESULT_BUSY;
  }

  return PLC_COMMAND_RESULT_OK;
}

BaseType_t PlcCommandTask_ReceiveResponse(
    PlcCommandResponse_t *response,
    TickType_t waitTicks)
{
  if ((response == NULL) || (responseQueue == NULL))
  {
    return pdFAIL;
  }

  return xQueueReceive(responseQueue, response, waitTicks);
}

uint32_t PlcCommandTask_GetDroppedResponseCount(void)
{
  return droppedResponseCount;
}
