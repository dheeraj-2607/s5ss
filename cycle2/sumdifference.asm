section .data
    msg1 db "Enter first number: ",0xa
    msg2 db "Enter second number: ",0xa
    msg3 db "Sum = ",0
    msg4 db "Difference = ",0
    newline db 0xa

section .bss
    num1 resb 10
    num2 resb 10
    val1 resd 1
    val2 resd 1
    result resb 12         

section .text
    global _start

_start:
  
    mov eax,4
    mov ebx,1
    mov ecx,msg1
    mov edx,21
    int 0x80

    mov eax,3
    mov ebx,0
    mov ecx,num1
    mov edx,10
    int 0x80
    mov byte [num1+eax-1],0   
    mov esi,num1
    call str_to_int
    mov [val1],eax

    mov eax,4
    mov ebx,1
    mov ecx,msg2
    mov edx,22
    int 0x80

    mov eax,3
    mov ebx,0
    mov ecx,num2
    mov edx,10
    int 0x80
    mov byte [num2+eax-1],0
    mov esi,num2
    call str_to_int
    mov [val2],eax

    mov eax,[val1]
    add eax,[val2]
    push eax

    mov eax,4
    mov ebx,1
    mov ecx,msg3
    mov edx,6
    int 0x80

    pop eax
    call print_int

    mov eax,4
    mov ebx,1
    mov ecx,newline
    mov edx,1
    int 0x80

    mov eax,[val1]
    sub eax,[val2]
    push eax

    mov eax,4
    mov ebx,1
    mov ecx,msg4
    mov edx,13
    int 0x80

    pop eax
    call print_int
    mov eax,4
    mov ebx,1
    mov ecx,newline
    mov edx,1
    int 0x80

    ; Exit
    mov eax,1
    xor ebx,ebx
    int 0x80

str_to_int:
    xor eax,eax
    xor ebx,ebx
.next_digit:
    mov bl,[esi]
    cmp bl,0
    je .done
    sub bl,'0'
    imul eax,eax,10
    add eax,ebx
    inc esi
    jmp .next_digit
.done:
    ret


print_int:
    mov edi,result+11
    mov byte [edi],0
    mov ecx,10
    cmp eax,0
    jge .positive
    ; handle negative
    neg eax
    push eax
    dec edi
    mov byte [edi],'-'
    pop eax
.positive:
    mov ebx,10
.repeat:
    xor edx,edx
    div ebx          
    add dl,'0'
    dec edi
    mov [edi],dl
    test eax,eax
    jnz .repeat
    mov eax,4
    mov ebx,1
    mov ecx,edi
    mov edx, result+12
    sub edx, edi
    int 0x80
    ret
