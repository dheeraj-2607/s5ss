section .data
    msg1 db "Enter a string: ",0xa
    msg1_len equ $-msg1

    palindrome_msg db "Palindrome",0xa
    palindrome_len equ $-palindrome_msg

    not_palindrome_msg db "Not Palindrome",0xa
    not_palindrome_len equ $-not_palindrome_msg

section .bss
    str1 resb 100
    len  resd 1          

section .text
    global _start

_start:
    ; Print "Enter a string: "
    mov eax,4
    mov ebx,1
    mov ecx,msg1
    mov edx,msg1_len
    int 0x80

    ; Read string
    mov eax,3
    mov ebx,0
    mov ecx,str1
    mov edx,100
    int 0x80
    mov [len],eax       
    cmp eax,1
    jle .skip_newline
    mov byte [str1+eax-1], 0 
    dec dword [len]           
.skip_newline:

    ; Setup pointers
    mov esi, str1          
    mov edi, str1
    add edi, [len]
    dec edi               

check_loop:
    cmp esi,edi
    jae is_palindrome      

    mov al,[esi]
    mov bl,[edi]

    cmp al,'a'
    jl .skip1
    cmp al,'z'
    jg .skip1
    sub al,32              
.skip1:

    cmp bl,'a'
    jl .skip2
    cmp bl,'z'
    jg .skip2
    sub bl,32
.skip2:

    cmp al,bl
    jne not_palindrome     

    inc esi
    dec edi
    jmp check_loop

is_palindrome:
    ; Print "Palindrome"
    mov eax,4
    mov ebx,1
    mov ecx,palindrome_msg
    mov edx,palindrome_len
    int 0x80
    jmp exit

not_palindrome:
    ; Print "Not Palindrome"
    mov eax,4
    mov ebx,1
    mov ecx,not_palindrome_msg
    mov edx,not_palindrome_len
    int 0x80

exit:
    mov eax,1
    xor ebx,ebx
    int 0x80
