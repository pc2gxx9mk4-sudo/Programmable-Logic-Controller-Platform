/**
  ******************************************************************************
  * @file    plc_command.h
  * @brief   Transport-independent PLC command model.
  ******************************************************************************
  */

#ifndef APPLICATION_PLC_COMMAND_H_
#define APPLICATION_PLC_COMMAND_H_

#include <stdint.h>

typedef enum
{
  PLC_COMMAND_SOURCE_UNKNOWN = 0,
  PLC_COMMAND_SOURCE_CAN,
  PLC_COMMAND_SOURCE_UART,
  PLC_COMMAND_SOURCE_INTERNAL
} PlcCommandSource_t;

typedef enum
{
  PLC_COMMAND_TYPE_NONE = 0,
  PLC_COMMAND_TYPE_RUN,
  PLC_COMMAND_TYPE_STOP,
  PLC_COMMAND_TYPE_CLEAR_FAULT,
  PLC_COMMAND_TYPE_GET_STATUS,
  PLC_COMMAND_TYPE_SET_PWM_DUTY
} PlcCommandType_t;

typedef enum
{
  PLC_COMMAND_RESULT_UNPROCESSED = 0,
  PLC_COMMAND_RESULT_OK,
  PLC_COMMAND_RESULT_INVALID_TYPE,
  PLC_COMMAND_RESULT_INVALID_ARGUMENT,
  PLC_COMMAND_RESULT_INVALID_STATE,
  PLC_COMMAND_RESULT_BUSY,
  PLC_COMMAND_RESULT_NOT_SUPPORTED
} PlcCommandResult_t;

typedef struct
{
  uint8_t channelId;
  uint16_t dutyPermille;
} PlcCommandSetPwmDutyPayload_t;

typedef union
{
  PlcCommandSetPwmDutyPayload_t setPwmDuty;
} PlcCommandPayload_t;

typedef struct
{
  PlcCommandType_t type;
  PlcCommandSource_t source;
  uint32_t sequenceNumber;
  PlcCommandPayload_t payload;
} PlcCommand_t;

/**
 * @brief Validate a transport-independent PLC command.
 *
 * This function validates only the command model. Hardware-dependent limits,
 * such as the available PWM channel count, are checked by the target service.
 *
 * @param command Command to validate.
 * @return PLC command validation result.
 */
PlcCommandResult_t PlcCommand_Validate(const PlcCommand_t *command);

#endif /* APPLICATION_PLC_COMMAND_H_ */
