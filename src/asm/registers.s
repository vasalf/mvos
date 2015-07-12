.globl get_eip
.type  get_eip, @function
get_eip:
    popl    %eax
    jmp     %eax

.globl get_cr0
.type  get_cr0, @function
get_cr0:
    movl    %cr0,   %eax
    ret
