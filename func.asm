global f1
global f2
global f3

section .data
    const1 dq 0.6
    const2 dq 3.0
    const3 dq 2.0

section .text
f1: ; 0.6x + 3
    push ebp
    mov ebp, esp
    
    finit
    fld qword[const2] ; 3
    fld qword[ebp + 8] ; x
    fld qword[const1] ; 0.6
    fmul ; 0.6x
    faddp ; 0.6x + 3
    
    mov esp, ebp
    pop ebp
    ret
f2: ;(x-2)^3 - 1
    push ebp
    mov ebp, esp

    finit
    fld qword[const2] ; 3
    fld qword[ebp + 8] ; x
    fld qword[const3] ; 2
    fsub ; x - 2 in st0
    
    fst st1
    fst st2

    fmul ; (x - 2) ^ 2
    fmul ; (x - 2) ^ 3
    
    fld1
    fsubp ; (x-2)^3 - 1
    
    xor eax, eax
    
    mov esp, ebp
    pop ebp
    ret
f3: ; 3/x
    push ebp
    mov ebp, esp
    
    finit
    fld qword[const2] ; 3
    fld qword[ebp + 8] ; x
    fdivp

    mov esp, ebp
    pop ebp
    ret