.arm
.fpu vfp
.syntax unified
.align(4);

.macro FUNCTION name
    .section .text.\name
    .global \name
    .type \name, %function
    .align 4
\name:
.endm

FUNCTION FixSaveFurn
    STMFD   SP!, {R0-R12,LR}   		@Store All Registers
    LDR   	R0, =fixfurn			@Set game address
    MOV		LR, PC					@Set return address (PC = (current instruction + 8) apparently)
    LDR     PC, [R0]				@Set PC to the game function. It stores LR so it will return to here+4
    LDMFD   SP!, {R0-R12,PC}   		@Restore All Registers