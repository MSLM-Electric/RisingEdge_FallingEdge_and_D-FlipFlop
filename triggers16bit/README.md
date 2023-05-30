Forward front edge (rising edge), Back front edge (falling edge) and D-Trigger/flip-flop (for "single button ON/OFF switch"-like example)

This library helps you to implement a mentioned functions/triggers for your project. No requires CPU Timers resources, it can be useful for FREERTOS or any RTOS, also for 
any platforms, because it doesn't depend on compiler.
One declarated structure takes uint16_t x 3 = 6 bytes for (ForwardFrontTrigger, BackFrontTrigger) and uint16_t x 4 = 8 bytes for D_Trigger to 16 parallel inputs.
Inputs can be not only a physical signal sources, and as well as variables (true/false).
