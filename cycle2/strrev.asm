section .data
    msg1 db "Enter a string: ",0xa
    msg1_len equ $-msg1

    msg2 db "Reversed string: ",0xa
    msg2_len equ $-msg2

section .bss
    str1 resb 100     
    rev  resb 100      
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
    mov ecx,eax
    dec ecx
    mov byte[str1+ecx],0   
    ; Setup pointers for reversing
    mov esi,str1          
    mov edi,rev            
    mov eax,[len]
    dec eax             
    dec eax             
    mov ebx,eax           

reverse_loop:
    cmp ebx,-1
    jl reverse_done

    mov al,[str1+ebx]
    mov [edi],al
    inc edi
    dec ebx
    jmp reverse_loop

reverse_done:
    mov byte[edi],0        

    ; Print "Reversed string: "
    mov eax,4
    mov ebx,1
    mov ecx,msg2
    mov edx,msg2_len
    int 0x80

    ; Print reversed string
    mov eax,4
    mov ebx,1
    mov ecx,rev
    mov edx,[len]
    dec edx
    int 0x80

    ; Exit
    mov eax,1
    xor ebx,ebx
    int 0x80
