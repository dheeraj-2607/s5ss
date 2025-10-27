section .data
    msg1 db "Enter a number: ",0xa
    msg2 db "The number is Even",0xa
    msg3  db "The number is Odd",0xa

section .bss
    num resb 10        
    value resd 1      

section .text
    global _start

_start:
    mov eax,4
    mov ebx,1
    mov ecx,msg1
    mov edx,16
    int 0x80

    mov eax,3
    mov ebx,0
    mov ecx,num
    mov edx,10
    int 0x80
    mov byte [num+eax-1],0   

    mov esi,num
    xor eax,eax
    xor ebx,ebx

.convert_loop:
    mov bl,[esi]
    cmp bl,0
    je .conversion_done
    sub bl,'0'
    imul eax,eax,10
    add eax,ebx
    inc esi
    jmp .convert_loop

.conversion_done:
    mov [value],eax

    mov eax,[value]
    test eax,1

.print_odd:
    mov eax,4
    mov ebx,1
    mov ecx,msg3
    mov edx,18
    int 0x80
    jmp .exit

.print_even:
    mov eax,4
    mov ebx,1
    mov ecx,msg2
    mov edx,20
    int 0x80

.exit:
    mov eax,1
    xor ebx,ebx
    int 0x80