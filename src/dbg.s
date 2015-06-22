.globl get_eip
.type get_eip, @function
get_eip:
    popl %ebx
    pushl %ebx
    ret

