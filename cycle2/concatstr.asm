section .data
    msg1     db  "string1: ", 0
    msg1l equ $ - msg1

    msg2     db  "string2: ", 0
    msg2l equ $ - msg2

    rmsg  db  "Concatenated string: ", 0
    rlen  equ $ - rmsg
    int 0x80

section .bss
    str1    resb 100
    str2    resb 100
    rslt  resb 200

section .text
    global _start

_start:

    ; Prompt for first string
    mov eax, 4
    mov ebx, 1
    mov ecx, msg1
    mov edx, msg1l
    int 0x80

    ; Read first string
    mov eax, 3
    mov ebx, 0
    mov ecx, str1
    mov edx, 100
    int 0x80
    mov esi, eax            ; store length of str1
    dec esi                 ; remove newline
    mov byte [str1 + esi], 0

    ; Prompt for second string
    mov eax, 4
    mov ebx, 1
    mov ecx, msg2
    mov edx, msg2l
    int 0x80

    ; Read second string
    mov eax, 3
    mov ebx, 0
    mov ecx, str2
    mov edx, 100
    int 0x80
    mov edi, eax            ; store length of str2
    dec edi                 ; remove newline
    mov byte [str2 + edi], 0

    ; Copy str1 to rslt
    mov esi, str1
    mov edi, rslt

.copy_str1:
    mov al, [esi]
    cmp al, 0
    je .copy_str2
    mov [edi], al
    inc esi
    inc edi
    jmp .copy_str1

.copy_str2:
    mov esi, str2

.copy_loop2:
    mov al, [esi]
    cmp al, 0
    je .print_rslt
    mov [edi], al
    inc esi
    inc edi
    jmp .copy_loop2

.print_rslt:
    ; Null terminate rslt string
    mov byte [edi], 0

    ; Print message
    mov eax, 4
    mov ebx, 1
    mov ecx, rmsg
    mov edx, rlen
    int 0x80

    ; Print rslt string
    mov eax, 4
    mov ebx, 1
    mov ecx, rslt
    ; Calculate length
    mov edx, edi
    sub edx, rslt
    int 0x80

    ; Exit
    mov eax, 1
    xor ebx, ebx
    int 0x80
