section .data
    msg1 db "Enter an integer: ",0xa
    res_msg db "Sum of digits = ",0
    newline db 0xa

section .bss
    num resb 20        
    buffer resb 32    

section .text
    global _start

_start:
   
    mov eax,4
    mov ebx,1
    mov ecx,msg1
    mov edx,19
    int 0x80

    ; Read input string
    mov eax,3
    mov ebx,0
    mov ecx,num
    mov edx,20
    int 0x80
    mov byte [num+eax-1],0   

    
    mov esi,num
    xor ecx,ecx              
.skip_sign:
    mov al,[esi]
    cmp al,'-'
    jne .digit_loop
    inc esi                  

.digit_loop:
    mov al,[esi]
    cmp al,0
    je .done_sum

    sub al,'0'                
    add ecx,eax              

    inc esi
    jmp .digit_loop

.done_sum:
    
    mov eax,4
    mov ebx,1
    mov ecx,res_msg
    mov edx,17
    int 0x80

    mov eax,ecx
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
    mov edx,buffer+32-edi
    int 0x80
    ret
