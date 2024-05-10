%include "io.inc"
section .bss
    result resd 1
section .data
    const1 dq 0.6
    const2 dq 3.0
    const3 dq 2.0
section .text
global main
main:
    mov ebp, esp; for correct debugging
    call f2
    
    fist dword[result]
    mov eax, [result]
    PRINT_DEC 4, eax
    
    xor eax, eax
    ret

f1: ; 0.6x + 3
    push ebp
    mov ebp, esp
    
    fld qword[const2] ; 3
    fld1 ; x
    fld qword[const1] ; 0.6
    fmul ; 0.6x
    fadd
    
    mov esp, ebp
    pop ebp
    ret
f2: ;(x-2)^3 - 1
    push ebp
    mov ebp, esp

    fld qword[const2] ; 3
    fld1 ; x
    fld qword[const3] ; 2
    fsub ; x - 2 in st0
    
    fldz
    fcomp
    fstsw ax ; safe flags
    
    fabs
    fyl2x ; 3 * log2(|x - 2|)
    f2xm1 ; 2^x - 1, x = 3 * log2(x - 2) => (|x-2|)^3 - 1
    fld1
    fadd ; (|x-2|)^3
    
    sahf ; flags in eflags
    jbe .skip ; x - 2 < 0
    fld1
    fchs ; -1 in st0
    fmul ; (x-2)^3
    
    .skip:
    
    fld1
    fsub ; (x-2)^3 - 1
    
    xor eax, eax
    
    mov esp, ebp
    pop ebp
    ret
f3: ; 3/x
    push ebp
    mov ebp, esp
    
    fld qword[const2] ; 3
    fld1 ; x
    fdiv

    mov esp, ebp
    pop ebp
    ret