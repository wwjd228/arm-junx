.thumb
.syntax unified

.global __set_PRIMASK
.global __get_PRIMASK
.global __set_FAULTMASK
.global __get_FAULTMASK
.global __set_BASEPRI
.global __get_BASEPRI
.global __get_MSP
.global __set_MSP
.global __get_PSP
.global __set_PSP
.global __get_CONTROL

__set_PRIMASK:
    /* set the PRIMASK by msr instruction */
    /* msr, mrs instruction used to access system register */
    msr primask, r0
    mov pc, lr

__get_PRIMASK:
    /* get the value of primask */
    mrs r0, primask
    mov pc, lr

__set_FAULTMASK:
    @ PROLOG
    push {r3, r4, r5, lr}

    msr faultmask, r0

    pop {r3, r4, r5, pc}

__get_FAULTMASK:
    @ PROLOG
    push {r3, r4, r5, lr}

    mrs r0, faultmask

    pop {r3, r4, r5, pc}

__set_BASEPRI:
    @ PROLOG
    push {r3, r4, r5, lr}

    msr basepri, r0
   
    pop {r3, r4, r5, pc}

__get_BASEPRI:
    @ PROLOG 
    push {r3, r4, r5, lr}

    mrs r0, basepri

    pop {r3, r4, r5, pc}

__get_MSP:
    @ PROLOG 
    push {r3, r4, r5, lr}

    mrs r0, msp

    pop {r3, r4, r5, pc}

__set_MSP:
    msr msp, r0

    @ return
    mov pc, lr

__get_PSP:
    @ PROLOG 
    push {r3, r4, r5, lr}

    mrs r0, psp

    pop {r3, r4, r5, pc}

__set_PSP:
    msr psp, r0

    @ return
    mov pc, lr

__get_CONTROL:
    mrs r0, control;

    @ return
    mov pc, lr

