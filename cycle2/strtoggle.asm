section .data
    msg1 db "Enter a string: ",0xa
    msg1_len equ $-msg1

    msg2 db "Toggled string: ",0xa
    msg2_len equ $-msg2

section .bss
    str1 resb 200
    len  resd 1

section .text
    global _start

_start:
    ; Print prompt
    mov eax,4
    mov ebx,1
    mov ecx,msg1
    mov edx,msg1_len
    int 0x80

    ; Read input string
    mov eax,3
    mov ebx,0
    mov ecx,str1
    mov edx,200
    int 0x80
    mov [len],eax
    dec eax
    mov byte[str1+eax],0    ; replace newline with null terminator

    ; Toggle loop
    mov esi,str1

toggle_loop:
    mov al,[esi]
    cmp al,0
    je toggle_done

    ; If 'a' <= al <= 'z', convert to uppercase
    cmp al,'a'
    jl check_upper
    cmp al,'z'
    jg check_upper
    sub al,32               ; 'a'→'A'
    mov [esi],al
    jmp next_char

check_upper:
    ; If 'A' <= al <= 'Z', convert to lowercase
    cmp al,'A'
    jl next_char
    cmp al,'Z'
    jg next_char
    add al,32               ; 'A'→'a'
    mov [esi],al

next_char:
    inc esi
    jmp toggle_loop

toggle_done:
    ; Print "Toggled string: "
    mov eax,4
    mov ebx,1
    mov ecx,msg2
    mov edx,msg2_len
    int 0x80

    ; Print modified string
    mov eax,4
    mov ebx,1
    mov ecx,str1
    mov edx,[len]
    int 0x80

    ; Exit
    mov eax,1
    xor ebx,ebx
    int 0x80
