.section .text

.globl  _asm_lgdt
.type   _asm_lgdt,   @function

_asm_lgdt:
        lgdt    gdtp
        mov     $0x10,      %ax
        mov     %ax,        %ds
        mov     %ax,        %es
        mov     %ax,        %fs
        mov     %ax,        %ss
        jmp     $0x08,      $.Lret
.Lret:  ret
