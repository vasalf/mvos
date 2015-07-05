.globl  _asm_irq_default_master
.type   _asm_irq_default_master,    @function
_asm_irq_default_master:
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
        call    irq_default_master_handler

        pop     %eax
        mov     %ax,        %ds
        mov     %ax,        %es
        mov     %ax,        %fs
        mov     %ax,        %gs

        popa
        add     $4,         %esp
        sti
        iret

.globl  _asm_irq_default_slave
.type   _asm_irq_default_slave,     @function
_asm_irq_default_slave:
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
        call    irq_default_slave_handler

        pop     %eax
        mov     %ax,        %ds
        mov     %ax,        %es
        mov     %ax,        %fs
        mov     %ax,        %gs

        popa
        add     $4,         %esp
        sti
        iret

# vim: ft=gas:
