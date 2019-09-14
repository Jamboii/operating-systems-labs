.file    "lab01.c"
.text
.section    .rodata
.LC0:
.string    "Square root of %d is %d\n"
.text
.globl    get_sqrts
.type    get_sqrts, @function
get_sqrts:
.LFB0:
.cfi_startproc
pushq    %rbp
.cfi_def_cfa_offset 16
.cfi_offset 6, -16
movq    %rsp, %rbp
.cfi_def_cfa_register 6
subq    $32, %rsp
movl    %edi, -20(%rbp)
jmp    .L2
.L3:
cvtsi2sd    -20(%rbp), %xmm0
call    sqrt@PLT
cvttsd2si    %xmm0, %eax
movl    %eax, -4(%rbp)
movl    -4(%rbp), %edx
movl    -20(%rbp), %eax
movl    %eax, %esi
leaq    .LC0(%rip), %rdi
movl    $0, %eax
call    printf@PLT
movl    -4(%rbp), %eax
leal    -1(%rax), %edx
movl    -4(%rbp), %eax
subl    $1, %eax
imull    %edx, %eax
movl    %eax, -20(%rbp)
.L2:
cmpl    $1, -20(%rbp)
jg    .L3
nop
leave
.cfi_def_cfa 7, 8
ret
.cfi_endproc
.LFE0:
.size    get_sqrts, .-get_sqrts
.globl    main
.type    main, @function
main:
.LFB1:
.cfi_startproc
pushq    %rbp
.cfi_def_cfa_offset 16
.cfi_offset 6, -16
movq    %rsp, %rbp
.cfi_def_cfa_register 6
subq    $16, %rsp
movl    $25, -4(%rbp)
movl    -4(%rbp), %eax
movl    %eax, %edi
call    get_sqrts
movl    $0, %eax
leave
.cfi_def_cfa 7, 8
ret
.cfi_endproc
.LFE1:
.size    main, .-main
.ident    "GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
.section    .note.GNU-stack,"",@progbits
