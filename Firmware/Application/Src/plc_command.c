/*
 * plc_command.c
 *
 *  Created on: Aug 7, 2026
 *      Author: ericlin
 */

#include "plc_command.h"

PlcCommandResult_t PlcCommand_Validate(const PlcCommand_t *pcommand)
{
	if ((pcommand == NULL) || (pcommand ->commandSource == UNKNOWN) || (pcommand ->playload.duty > 1000U))
	{
		return INVALID_ARGUMENT;
	}

	if ((pcommand ->commandType == NONE) || (pcommand ->commandType >= SET_PWM_DUTY))
	{
		return INVALID_TYPE;
	}

	return OK;

}


