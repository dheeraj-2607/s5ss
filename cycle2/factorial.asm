section .data
    msg1 db "Enter a positive integer: ",0xa
    res_msg db "Factorial = ",0
    newline db 0xa

section .bss
    num resb 10
    val resd 1
    result resq 1          
    buffer resb 32        

section .text
    global _start

_start:
    
    mov eax,4
    mov ebx,1
    mov ecx,msg1
    mov edx,27
    int 0x80

    ; Read input string
    mov eax,3
    mov ebx,0
    mov ecx,num
    mov edx,10
    int 0x80
    mov byte [num+eax-1],0    

    mov esi,num
    call str_to_int
    mov [val],eax

    mov eax,[val]     ; n
    cmp eax,0
    jne .calc
    mov dword [result],1
    jmp .done_fact

.calc:
    mov ecx,eax      
    mov eax,1        
.factorial_loop:
    imul eax,ecx     
    loop .factorial_loop
    mov [result],eax

.done_fact:
    mov eax,4
    mov ebx,1
    mov ecx,res_msg
    mov edx,12
    int 0x80

    mov eax,[result]
    call print_int

    ; newline
    mov eax,4
    mov ebx,1
    mov ecx,newline
    mov edx,1
    int 0x80

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
    mov edi,buffer+31
    mov byte [edi],0
    mov ecx,10
    cmp eax,0
    jge .positive
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
    mov edx, buffer+32
    sub edx, edi    
    int 0x80
    ret
