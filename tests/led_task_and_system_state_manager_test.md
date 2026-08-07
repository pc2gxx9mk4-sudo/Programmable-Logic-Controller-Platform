1. Objective:
	Verify that the LED Task changes the LED blinking period according to the current system state.
	
2. Test Environment:
	a. STM32F446RE Development Board NUCLEO
	b. STM32CubeIDE
	c. FreeRTOS
	d. Onboard LED
	
3. Test Cases:
| Test ID | System State | Expected Blink Period | Actual Result | Pass/Fail |
| ------- | ------------ | --------------------- | ------------- | --------- |
| LED-001 | INITIALIZING | 500 ms                | 500 ms        | PASS      |
| LED-002 | STANDBY      | 1000 ms               | 1000 ms       | PASS      |
| LED-003 | RUNNING      | 200 ms                | 200 ms        | PASS      |
| LED-004 | FAULT        | 100 ms                | 100 ms        | PASS      |


4. Test Procudures:

Manually set the system states through APIs in system_state_manager.h and observe LED's blinking states.

5. Boundary Test:

The boundary test will be carried out after command_handler module is completed so that the system can be tested in runtime.
	