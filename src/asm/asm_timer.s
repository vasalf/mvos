.globl  _asm_timer_irq
.type   _asm_timer_irq,  @function
_asm_timer_irq:
        cli
        push    $0
        pusha
        
        mov     %ds,        %ax
        push    %eax
        
        mov     $0x10,      %ax
        mov     %ax,        %ds
        mov     %ax,        %es
        mov     %ax,        %fs
        mov     %ax,        %gs

        cld
        call    timer_irq

        pop     %eax
        mov     %ax,        %ds
        mov     %ax,        %es
        mov     %ax,        %fs
        mov     %ax,        %gs

        mov     $0x20,      %al
        outb    %al,        $0x20

        popa
        add     $4,         %esp
        sti
        iret

# vim: ft=gas:
