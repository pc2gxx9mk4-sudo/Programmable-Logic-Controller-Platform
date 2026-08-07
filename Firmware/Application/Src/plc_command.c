/**
  ******************************************************************************
  * @file    plc_command.c
  * @brief   Transport-independent PLC command validation.
  ******************************************************************************
  */

#include "plc_command.h"

#include <stdbool.h>
#include <stddef.h>

#define PLC_COMMAND_MAX_DUTY_PERMILLE  1000U

static bool PlcCommand_IsSourceValid(PlcCommandSource_t source)
{
  switch (source)
  {
    case PLC_COMMAND_SOURCE_CAN:
    case PLC_COMMAND_SOURCE_UART:
    case PLC_COMMAND_SOURCE_INTERNAL:
      return true;

    case PLC_COMMAND_SOURCE_UNKNOWN:
    default:
      return false;
  }
}

PlcCommandResult_t PlcCommand_Validate(const PlcCommand_t *command)
{
  if (command == NULL)
  {
    return PLC_COMMAND_RESULT_INVALID_ARGUMENT;
  }

  if (!PlcCommand_IsSourceValid(command->source))
  {
    return PLC_COMMAND_RESULT_INVALID_ARGUMENT;
  }

  switch (command->type)
  {
    case PLC_COMMAND_TYPE_RUN:
    case PLC_COMMAND_TYPE_STOP:
    case PLC_COMMAND_TYPE_CLEAR_FAULT:
    case PLC_COMMAND_TYPE_GET_STATUS:
      return PLC_COMMAND_RESULT_OK;

    case PLC_COMMAND_TYPE_SET_PWM_DUTY:
      if (command->payload.setPwmDuty.dutyPermille >
          PLC_COMMAND_MAX_DUTY_PERMILLE)
      {
        return PLC_COMMAND_RESULT_INVALID_ARGUMENT;
      }

      return PLC_COMMAND_RESULT_OK;

    case PLC_COMMAND_TYPE_NONE:
    default:
      return PLC_COMMAND_RESULT_INVALID_TYPE;
  }
}
