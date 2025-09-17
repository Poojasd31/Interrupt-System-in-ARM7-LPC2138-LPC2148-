# Interrupt-System-in-ARM7-LPC2138-LPC2148-

1. Interrupt System in ARM7 (LPC2138/LPC2148)
Vectored Interrupt Controller (VIC) handles all interrupts.
16 vectored interrupts and 16 non-vectored (FIQ/IRQ).
Each interrupt source can be:
Enabled / Disabled
Assigned a vector slot
Routed to IRQ (default) or FIQ

Important VIC Registers:
Register	Purpose
VICIntEnable	Enable specific interrupt
VICVectAddr0–15	Holds ISR address for vectored interrupts
VICVectCntl0–15	Control registers (enable & assign interrupt source)
VICVectAddr	Used to signal end of ISR

