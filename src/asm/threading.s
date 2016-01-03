.section .data
_asm_threading_remember_eip:
    .long   0
printf_format:
    .string "_asm_run_thread: _asm_threading_remember_eip=%p\n"

.section .text
.globl _asm_run_thread
.type _asm_run_thread, @function
_asm_run_thread:
    popl    %ecx
    popl    %eax
    popl    %ebx
    movl    %ebx,   _asm_threading_remember_eip
    movl    %eax,   %esp
    #popa

    /*pushl   (_asm_threading_remember_eip)
    pushl   $printf_format
    call    printf
  
  _jmp:
    hlt
    jmp _jmp*/

    #jmp      _asm_threading_remember_eip
    pushl    _asm_threading_remember_eip
    #jmp     %ebx
    sti
    ret
     
