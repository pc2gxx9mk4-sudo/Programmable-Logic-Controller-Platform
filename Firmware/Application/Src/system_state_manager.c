/*
 * system_state_manager.c
 *
 *  Created on: Aug 6, 2026
 *      Author: ericlin
 */

#include "system_state_manager.h"

static SystemState_t systemCurrentState = SYSTEM_STATE_BOOT;

/**
 * @brief Initialize system state manager.
 *
 * After initializing, system state will be set to SYSTEM_STATE_STOPPED.
 *
 * @retval true Initialization completed.
 */
bool SystemStateManager_Init(void)
{
	systemCurrentState = SYSTEM_STATE_INIT;

	return true;
}

/**
 * @biref Request the system to enter the running state.
 *
 * The system can only enter the running state
 * if and only if the current state is SYSTEM_STATE_STOPPED.
 *
 * @retval true State transition completed.
 * @retval false State transition rejected.
 */
bool SystemStateManager_RequestRun(void)
{
	if (systemCurrentState == SYSTEM_STATE_STOPPED){
		systemCurrentState = SYSTEM_STATE_RUNNING;
		return true;

	}
	else
	{
		return false;
	}
}

/**
 * @brief Request the system to enter the stopped state.
 *
 * The system can only enter the stopped state if and only if
 * the current system state is SYSTEM_STATE_RUNNING.
 *
 * @retval true State transition completed.
 * @retval false State transition rejected.
 */
bool SystemStateManager_RequestStop(void)
{
	if (systemCurrentState == SYSTEM_STATE_RUNNING){
		systemCurrentState = SYSTEM_STATE_STOPPED;
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * @brief set the system state to be fault.
 *
 * System state will be set to fault once this function
 * is called regardless of what the sysytem state currently is.
 */
void SystemStateManager_SetFault(void)
{
	systemCurrentState = SYSTEM_STATE_FAULT;
}

/**
 * @brief set the system state to be SYSTEM_STATE_STOPPED.
 *
 * System state can only transition from fault to stopped.
 *
 *
 * @retval true State transition completed.
 * @retval false State transition rejected.
 */
bool SystemStateManager_ClearFault(void)
{
	if (systemCurrentState == SYSTEM_STATE_FAULT){
		systemCurrentState = SYSTEM_STATE_STOPPED;
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * @brief Check is currentSystemState is valid for output.
 *
 * System allows output if the system is in running state.
 *
 * @retval true Output is allowed.
 * @retval false Output is not allowed.
 */
bool SystemStateManager_IsOutputAllowed(void)
{
	if (systemCurrentState == SYSTEM_STATE_RUNNING){
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * @brief Get current system state
 */
SystemState_t SystemStateManager_GetState(void)
{
	return systemCurrentState;
}

bool SystemStateManager_CompleteInitialization(void)
{
	if (systemCurrentState == SYSTEM_STATE_INIT){
		systemCurrentState = SYSTEM_STATE_STOPPED;
		return true;
	}
	else
	{
		return false;
	}
}
