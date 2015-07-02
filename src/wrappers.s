.section .text

.globl _wrap_keyboard_handler
.type _wrap_keyboard_handler, @function

_wrap_keyboard_handler:
    pusha
    cld
    call keyboard_handler
    popa
    iret
