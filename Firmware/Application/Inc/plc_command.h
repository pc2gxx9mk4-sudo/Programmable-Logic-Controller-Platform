/*
 * plc_command.h
 *
 *  Created on: Aug 7, 2026
 *      Author: ericlin
 */

#ifndef INC_PLC_COMMAND_H_
#define INC_PLC_COMMAND_H_

#include <stdint.h>
#include <stddef.h>

typedef enum
{
	UNKNOWN = 0,
	CAN,
	UART,
	INTERNAL

} PlcCommandSource_t;

typedef enum
{
	NONE = 0,
	RUN,
	STOP,
	CLEAR_FAULT,
	GET_STATUS,
	SET_PWM_DUTY

} PlcCommandType_t;

typedef enum
{
	UNPROCESSED = 0,
	OK,
	INVALID_TYPE,
	INVALID_ARGUMENT,
	INVALID_STATE,
	BUSY,
	NOT_SUPPORTED

} PlcCommandResult_t;

typedef union
{
	uint8_t channelID;
	uint16_t duty;


} PlcCommandPlayload_t;

typedef struct
{
	PlcCommandType_t commandType;
	PlcCommandSource_t commandSource;

	uint32_t sequenceNumber;
	PlcCommandPlayload_t playload;

}PlcCommand_t;

PlcCommandResult_t PlcCommand_Validate(const PlcCommand_t *pcommand);

#endif /* INC_PLC_COMMAND_H_ */
