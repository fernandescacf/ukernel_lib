.text
.align 4

.global syscall
.func	syscall
// void *syscall(uint32_t sysnum)
syscall:
    // We have to save r7 since it is used to pass the system call number
    push	{r7}
    // Pass system call number to R0
    mov	    r7, r0
    svc	    #0
    pop	    {r7}
    bx      lr
.endfunc

.global syscall1
.func	syscall1
// void *syscall1(uint32_t sysnum, void *arg1)
syscall1:
    // We have to save r7 since it is used to pass the system call number
    push	{r7}
    // Pass system call number to R0
    mov	    r7, r0
    // Move parameters to the rigth registers
    mov     r0, r1
    svc	    #0
    pop	    {r7}
    bx      lr
.endfunc

.global syscall2
.func	syscall2
// void *syscall2(uint32_t sysnum, void *arg1, void *arg2)
syscall2:
    // We have to save r7 since it is used to pass the system call number
    push	{r7}
    // Pass system call number to R0
    mov	    r7, r0
    // Move parameters to the rigth registers
    mov     r0, r1
    mov     r1, r2
    svc	    #0
    pop	    {r7}
    bx      lr
.endfunc

.global syscall3
.func	syscall3
// void *syscall3(uint32_t sysnum, void *arg1, void *arg2, void *arg3)
syscall3:
    // We have to save r7 since it is used to pass the system call number
    push	{r7}
    // Pass system call number to R0
    mov	    r7, r0
    // Move parameters to the rigth registers
    mov     r0, r1
    mov     r1, r2
    mov     r2, r3
    svc	    #0
    pop	    {r7}
    bx      lr
.endfunc

.global syscall4
.func	syscall4
// void *syscall4(uint32_t sysnum, void *arg1, void *arg2, void *arg3, void *arg4)
syscall4:
    // We have to save r7 since it is used to pass the system call number
    push	{r7}
    // Use IP to get the arguments passed through stack
    add     ip, sp, #0
    // Pass system call number to R0
    mov	    r7, r0
    // Move parameters to the rigth registers
    mov     r0, r1
    mov     r1, r2
    mov     r2, r3
    // Get remaining parameters from stack
    ldmib	ip, {r3}
    svc	    #0
    pop	    {r7}
    bx      lr
.endfunc

.global syscall5
.func	syscall5
// void *syscall5(uint32_t sysnum, void *arg1, void *arg2, void *arg3, void *arg4, void *arg5)
syscall5:
    // Save used registers in stack
    push	{r4, r7}
    // Use IP to get the arguments passed through stack
    add     ip, sp, #4
    // Pass system call number to R0
    mov	    r7, r0
    // Move parameters to the rigth registers
    mov     r0, r1
    mov     r1, r2
    mov     r2, r3
    // Get remaining parameters from stack
    ldmib	ip, {r3-r4}
    svc	    #0
    pop	    {r4, r7}
    bx      lr
.endfunc

.global syscall6
.func	syscall6
// void *syscall6(uint32_t sysnum, void *arg1, void *arg2, void *arg3, void *arg4, void *arg5, void *arg6)
syscall6:
    // Save used registers in stack
    push	{r4, r5, r7}
    // Use IP to get the arguments passed through stack
    add     ip, sp, #8
    // Pass system call number to R0
    mov	    r7, r0
    // Move parameters to the rigth registers
    mov     r0, r1
    mov     r1, r2
    mov     r2, r3
    // Get remaining parameters from stack
    ldmib	ip, {r3-r5}
    svc	    #0
    pop	    {r4, r5, r7}
    bx      lr
.endfunc