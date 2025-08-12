section .data
    msg1     db  "string1: ", 0
    msg1_len equ $ - msg1

    msg2     db  "string2: ", 0
    msg2_len equ $ - msg2

    eq   db  "equal", 10, 0
    eq_len   equ $ - eq

    neq db "not equal", 10, 0
    neq_len equ $ - neq

section .bss
    str1 resb 100
    str2 resb 100

section .text
    global _start

_start:

    ; Prompt and read first string
    mov eax, 4          ; sys_write
    mov ebx, 1          ; stdout
    mov ecx, msg1
    mov edx, msg1_len
    int 0x80

    mov eax, 3          ; sys_read
    mov ebx, 0          ; stdin
    mov ecx, str1
    mov edx, 100
    int 0x80
    mov esi, eax        ; save length of first string in esi

    ; Prompt and read second string
    mov eax, 4
    mov ebx, 1
    mov ecx, msg2
    mov edx, msg2_len
    int 0x80

    mov eax, 3
    mov ebx, 0
    mov ecx, str2
    mov edx, 100
    int 0x80
    mov edi, eax        ; save length of second string in edi

    ; Remove newline characters (replace '\n' with 0)
    mov byte [str1 + esi - 1], 0
    mov byte [str2 + edi - 1], 0

    ; Compare strings
    mov esi, str1
    mov edi, str2

cmp_loop:
    mov al, [esi]
    mov bl, [edi]
    cmp al, 0
    jne .ck_chars
    cmp bl, 0
    jne .not_eq
    jmp .eq

.ck_chars:
    cmp al, bl
    jne .not_eq
    inc esi
    inc edi
    jmp cmp_loop

.eq:
    mov eax, 4
    mov ebx, 1
    mov ecx, eq
    mov edx, eq_len
    int 0x80
    jmp .exit

.not_eq:
    mov eax, 4
    mov ebx, 1
    mov ecx, neq
    mov edx, neq_len
    int 0x80

.exit:
    mov eax, 1
    xor ebx, ebx
    int 0x80
