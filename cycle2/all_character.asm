section .data
    msg1 db "String1: ", 0xa        
    msg2 db "Character frequencies:", 0xa
    msg3 db 0xa
    colon db ": "

section .bss
    str1 resb 100                 
    freq resb 256  
    visited resb 256              
    char resb 1                
    count resb 4                  ; enough for multi-digit counts

section .text
    global _start

_start:
    ; Print "String1: "
    mov eax, 4
    mov ebx, 1
    mov ecx, msg1
    mov edx, 9
    int 0x80

    ; Read input string
    mov eax, 3
    mov ebx, 0
    mov ecx, str1
    mov edx, 100
    int 0x80
    mov byte [str1 + eax - 1], 0    ; replace newline with null terminator

    ; clear freq array
    mov edi, freq
    mov ecx, 256
    xor eax, eax
    rep stosb

    ; count frequencies
    mov esi, str1
.count_loop:
    mov al, [esi]
    cmp al, 0
    je .print_loop                              
    movzx ebx, al
    inc byte [freq + ebx]         
    inc esi
    jmp .count_loop

.print_loop:
    ; Print heading
    mov eax,4
    mov ebx,1
    mov ecx,msg2
    mov edx,25
    int 0x80

    mov esi,str1

.loop:
    mov al, [esi]
    cmp al, 0
    je .exit

    movzx ebx, al
    cmp byte [visited + ebx], 1   ; already printed?
    je .next_char

    mov byte [visited + ebx], 1   ; mark visited
    mov [char], al

    ; print char
    mov eax,4
    mov ebx,1
    mov ecx,char
    mov edx,1
    int 0x80

    ; print colon
    mov eax,4
    mov ebx,1
    mov ecx,colon
    mov edx,2
    int 0x80

    movzx ebx, byte [char]        ; get character index
    movzx eax, byte [freq + ebx]  ; get frequency count
    call print_number

    mov eax,4
    mov ebx,1
    mov ecx,msg3
    mov edx,1
    int 0x80

.next_char:
    inc esi
    jmp .loop

.exit:
    mov eax,1
    xor ebx,ebx
    int 0x80
print_number:
    mov ecx, count + 3     
    mov byte [ecx], 0      

.convert_loop:
    mov edx, 0
    mov ebx, 10
    div ebx                
    add dl, '0'
    dec ecx
    mov [ecx], dl
    test eax, eax
    jnz .convert_loop

    ; print string at ecx
    mov eax, 4
    mov ebx, 1
    mov edx, count + 4
    sub edx, ecx
    mov ecx, ecx
    int 0x80
    ret
