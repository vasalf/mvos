.section .text

.globl idt_load
.type idt_load, @function

idt_load:
    lidt idtp
    ret
