.globl  _asm_isr_default_noerror
.type   _asm_isr_default_noerror,  @function
_asm_isr_default_noerror:
        cli
        push    $0
        jmp     .isr_common_stub

.globl  _asm_isr_default
.type   _asm_isr_default,  @function
_asm_isr_default:
        cli
        jmp     .isr_common_stub

.isr_common_stub:
        pusha
        
        mov     %ds,        %ax
        push    %eax
        
        mov     $0x10,      %ax
        mov     %ax,        %ds
        mov     %ax,        %es
        mov     %ax,        %fs
        mov     %ax,        %gs

        cld
        call    isr_default_handler

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
