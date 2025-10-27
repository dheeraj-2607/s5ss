section .data
    msg1 db "String:",0xa
    msg1l equ $-msg1
    msg2 db "Toggled:",0xa
    msg2l equ $-msg2

section .bss
    str1 resb 100
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
    mov ecx,str1
    mov edx,100
    int 0x80

    mov[len],eax
    dec eax
    mov byte[str1 + eax],0
    mov esi,str1

toggle_loop:
    mov al,[esi]
    cmp al,0
    je toggle_done
    cmp al,'a'
    jl check_upper
    cmp al,'z'
    jg check_upper
    sub al,32
    mov [esi],al
    jmp next_char

check_upper:
    cmp al,'A'
    jl next_char
    cmp al,'Z'
    jg next_char
    add al,32
    mov [esi],al

next_char:
    inc esi
    jmp toggle_loop

toggle_done:
    mov eax,4
    mov ebx,1
    mov ecx,msg2
    mov edx,msg2l
    int 0x80
    mov eax,4
    mov ebx,1
    mov ecx,str1
    mov edx,[len]
    int 0x80

    mov eax,1
    xor ebx,ebx
    int 0x80