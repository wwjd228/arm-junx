.thumb
.syntax unified

.global do_stack_operations

do_stack_operations:
    mov r0, #0x11
    mov r1, #0x22
    mov r2, #0x33
    push {r0, r1, r2}
    mrs r0, control
    orr r0, r0, #0x2
    @ turn to psp by change control SPSEL bit
    msr control, r0
    mrs r0, msp
    msr psp, r0
    pop {r0, r1, r2}

    bx lr
