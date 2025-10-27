section .data
    msg1 db "String:",0xa
    msg1l equ $-msg1
    newline db 10
    newline_len equ $-newline
    msg2 db "Palindrome",10
    msg2l equ $-msg2
    msg3 db "Not Palindrome",10
    msg3l equ $-msg3

section .bss
    inp resb 100
    len resd 1

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
    mov ecx,inp
    mov edx,100
    int 0x80
    dec eax
    mov [len],eax
    mov edi,eax
    dec edi
    xor esi,esi

_loop:
    cmp esi,edi
    je is_pal
    mov al,[inp + esi]
    mov bl,[inp + edi]
    cmp al,bl
    jne not_pal
    inc esi
    inc edi
    jmp _loop

is_pal:
    mov eax,4
    mov ebx,1
    mov ecx,msg2
    mov edx,msg2l
    int 0x80
    jmp exit

not_pal:
    mov eax,4
    mov ebx,1
    mov ecx,msg3
    mov edx,msg3l
    int 0x80

exit:
    mov eax,1
    xor ebx,ebx
    int 0x80