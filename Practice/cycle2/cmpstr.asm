section .data
    msg1 db "String1:",0
    msg1l equ $-msg1
    msg2 db "String2:",0
    msg2l equ $-msg2
    msg3 db "Equal",0
    msg3l equ $-msg3
    msg4 db "Not Equal",0
    msg4l equ $-msg4

section .bss
    str1 resb 100
    str2 resb 100

section .text
    global _start

_start:
    mov eax,4
    mov ebx,1
    mov ecx,msg1
    mov edx,msg1l
    int 0x80
    mov eax,3
    mov ebx,0
    mov ecx,str1
    mov edx,100
    int 0x80
    
    mov esi,eax

    mov eax,4
    mov ebx,1
    mov ecx,msg2
    mov edx,msg2l
    int 0x80
    mov eax,3
    mov ebx,0
    mov ecx,str2
    mov edx,100
    int 0x80

    mov edi,eax

    mov byte[str1 + esi - 1],0
    mov byte[str2 + edi - 1],0

    mov esi,str1
    mov edi,str2

cmp_loop:
    mov al,[esi]
    mov bl,[edi]
    cmp al,0
    jne .ck_char
    cmp bl,0
    jne .not_equal
    jmp .eq

.ck_char:
    cmp al,bl
    jne .not_equal
    inc esi
    inc edi
    jmp cmp_loop

.eq:
    mov eax,4
    mov ebx,1
    mov ecx,msg3
    mov edx,msg3l
    int 0x80
    jmp .exit

.not_equal:
    mov eax,4
    mov ebx,1
    mov ecx,msg4
    mov edx,msg4l
    int 0x80

.exit:
    mov eax,1
    xor ebx,ebx
    int 0x80