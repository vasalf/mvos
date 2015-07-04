.section .text

.globl _asm_keyboard_isr
.type _asm_keyboard_isr, @function

_asm_keyboard_isr:
    pusha
    movl $0xdeadbeef, 0x0
    hlt
    popa
    iret
