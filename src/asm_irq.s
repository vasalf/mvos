.macro  irq     n i
.globl  irq\n
.type   irq\n,  @function
irq\n:
        cli
        push    $0
        push    $\i
        jmp     irq_common_stub
.endm

irq 0,      32
irq 1,      33
irq 2,      34
irq 3,      35
irq 4,      36
irq 5,      37
irq 6,      38
irq 7,      39
irq 8,      40
irq 9,      41
irq 10,     42
irq 11,     43
irq 12,     44
irq 13,     45
irq 14,     46
irq 15,     47

irq_common_stub:
        pusha
        
        mov     %ds,        %ax
        push    %eax
        
        mov     $0x10,      %ax
        mov     %ax,        %ds
        mov     %ax,        %es
        mov     %ax,        %fs
        mov     %ax,        %gs
        
        cld
        call    irq_common_handler

        pop     %ebx
        mov     %bx,        %ds
        mov     %bx,        %es
        mov     %bx,        %fs
        mov     %bx,        %gs

        popa
        add     $8,         %esp
        sti
        iret

# vim: ft=gas:
