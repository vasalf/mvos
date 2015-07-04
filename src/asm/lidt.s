.section .text

.globl  _asm_lidt
.type   _asm_lidt,   @function

_asm_lidt:
    lidt    idtp
    ret
