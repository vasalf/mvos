.globl  _asm_panic
.type   _asm_panic, @function

_asm_panic:
        cli
.Lhlt:  hlt
        jmp .Lhlt
