1. UART and CAN tasks genrate command and send to commandTask through Queue

UART ─┐
      ├─> Command Queue ─> Command Task ─> System State Manager
CAN ──┘                         │
                               └─> Response Queue
                               
2. command_task module has 2 responsibilities:
	a. It privately owns the commandQueue and provide APIs for UART and CAN modules to send commands into Queue
	b. The PLC command task processes command, generate response to the sender by sending sending the response into response queue.