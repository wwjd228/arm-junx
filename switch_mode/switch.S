.thumb
.syntax unified

.global go_to_unpriviledged_access_level
.global go_to_priviledged_access_level

go_to_unpriviledged_access_level:
    mov r0, #1
    @ mrs/msr is reg to reg only
    msr control, r0
    mov pc, lr

go_to_priviledged_access_level:
    mov r0, #0
    @ mrs/msr is reg to reg only
    msr control, r0
    mov pc, lr
