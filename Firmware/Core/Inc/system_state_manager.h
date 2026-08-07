/*
 * system_state_manager.h
 *
 *  Created on: Aug 6, 2026
 *      Author: ericlin
 */

#ifndef INC_SYSTEM_STATE_MANAGER_H_
#define INC_SYSTEM_STATE_MANAGER_H_

#include <stdbool.h>

typedef enum
{
	SYSTEM_STATE_BOOT = 0,
	SYSTEM_STATE_INIT,
	SYSTEM_STATE_STOPPED,
	SYSTEM_STATE_RUNNING,
	SYSTEM_STATE_FAULT
} SystemState_t;

bool SystemStateManager_Init(void);

bool SystemStateManager_RequestRun(void);
bool SystemStateManager_RequestStop(void);

void SystemStateManager_SetFault(void);
bool SystemStateManager_ClearFault(void);

bool SystemStateManager_IsOutputAllowed(void);

SystemState_t SystemStateManager_GetState(void);

#endif /* INC_SYSTEM_STATE_MANAGER_H_ */
