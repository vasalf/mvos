.macro  isr_noerror     n
.globl  isr\n
.type   isr\n,  @function
isr\n:
        cli
        push    $0
        push    $\n
        jmp     isr_common_stub
.endm

.macro  isr     n
.globl  isr\n
.type   isr\n,  @function
isr\n:
        cli
        push    $\n
        jmp     isr_common_stub
.endm

isr_noerror 0
isr_noerror 1
isr_noerror 2
isr_noerror 3
isr_noerror 4
isr_noerror 5
isr_noerror 6
isr_noerror 7
isr         8
isr_noerror 9
isr         10
isr         11
isr         12
isr         13
isr         14
isr_noerror 15
isr_noerror 16
isr_noerror 17
isr_noerror 18
isr_noerror 19
isr_noerror 20
isr_noerror 21
isr_noerror 22
isr_noerror 23
isr_noerror 24
isr_noerror 25
isr_noerror 26
isr_noerror 27
isr_noerror 28
isr_noerror 29
isr_noerror 30
isr_noerror 31
isr_noerror 32
isr_noerror 33

isr_common_stub:
        push    $0
        call    panic
        pusha
        
        mov     %ds,        %ax
        push    %eax
        
        mov     $0x10,      %ax
        mov     %ax,        %ds
        mov     %ax,        %es
        mov     %ax,        %fs
        mov     %ax,        %gs
        
        cld
        call    isr_common_handler

        pop     %eax
        mov     %ax,        %ds
        mov     %ax,        %es
        mov     %ax,        %fs
        mov     %ax,        %gs

        popa
        add     $8,         %esp
        sti
        iret

# vim: ft=gas:
