section .data
    prompt              db "Enter a string: ", 0
    prompt_len          equ $ - prompt

    newline             db 10
    newline_len         equ $ - newline

    palindrome_msg      db "Palindrome", 10
    palindrome_msg_len  equ $ - palindrome_msg

    not_palindrome_msg      db "Not a palindrome", 10
    not_palindrome_msg_len  equ $ - not_palindrome_msg

section .bss
    input   resb 100       ; Buffer for input
    length  resd 1         ; Store input length

section .text
    global _start

_start:
    ; --- Print prompt ---
    mov eax, 4              ; sys_write
    mov ebx, 1              ; stdout
    mov ecx, prompt
    mov edx, prompt_len
    int 0x80

    ; --- Read input ---
    mov eax, 3              ; sys_read
    mov ebx, 0              ; stdin
    mov ecx, input
    mov edx, 100
    int 0x80

    ; --- Remove newline and save length ---
    dec eax                 ; Remove newline from length
    mov [length], eax       ; Store length
    mov edi, eax
    dec edi                 ; edi = length - 1 (last index)

    xor esi, esi            ; esi = 0 (first index)

check_loop:
    cmp esi, edi
    jge is_palindrome       ; If pointers cross, it's a palindrome

    ; Load input[esi] into al
    mov al, [input + esi]

    ; Load input[edi] into bl
    mov bl, [input + edi]

    ; Compare characters
    cmp al, bl
    jne not_palindrome

    ; Optional: Debug print current chars
    ; Uncomment to see characters compared
    ; mov eax, 4
    ; mov ebx, 1
    ; lea ecx, [input + esi]
    ; mov edx, 1
    ; int 0x80
    ; lea ecx, [input + edi]
    ; mov edx, 1
    ; int 0x80
    ; mov ecx, newline
    ; mov edx, newline_len
    ; int 0x80

    ; Move inward
    inc esi
    dec edi
    jmp check_loop

is_palindrome:
    ; --- Print "Palindrome" ---
    mov eax, 4
    mov ebx, 1
    mov ecx, palindrome_msg
    mov edx, palindrome_msg_len
    int 0x80
    jmp exit

not_palindrome:
    ; --- Print "Not a palindrome" ---
    mov eax, 4
    mov ebx, 1
    mov ecx, not_palindrome_msg
    mov edx, not_palindrome_msg_len
    int 0x80

exit:
    mov eax, 1              ; sys_exit
    xor ebx, ebx
    int 0x80
