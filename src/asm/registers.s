.globl _asm_get_eip
.type  _asm_get_eip, @function
_asm_get_eip:
    popl  %ebx
    pushl %ebx
    ret
