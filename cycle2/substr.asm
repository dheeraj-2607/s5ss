section .data
    msg1 db "Enter main string: ",0xa
    msg1_len equ $-msg1

    msg2 db "Enter substring: ",0xa
    msg2_len equ $-msg2

    msg3 db "Found",0xa
    msg3_len equ $-msg3

    msg4 db "Not Found",0xa
    msg4_len equ $-msg4

section .bss
    mainstr resb 200
    substr  resb 100
    mainlen resd 1
    sublen  resd 1

section .text
    global _start

_start:
    ; Prompt for main string
    mov eax,4
    mov ebx,1
    mov ecx,msg1
    mov edx,msg1_len
    int 0x80

    ; Read main string
    mov eax,3
    mov ebx,0
    mov ecx,mainstr
    mov edx,200
    int 0x80
    mov [mainlen],eax
    dec eax
    mov byte[mainstr+eax],0    

    ; Prompt for substring
    mov eax,4
    mov ebx,1
    mov ecx,msg2
    mov edx,msg2_len
    int 0x80

    ; Read substring
    mov eax,3
    mov ebx,0
    mov ecx,substr
    mov edx,100
    int 0x80
    mov [sublen],eax
    dec eax
    mov byte[substr+eax],0      

    ; Initialize pointers
    mov esi,mainstr            

outer_loop:
    mov al,[esi]
    cmp al,0
    je not_found                

    ; try to match substring starting here
    mov edi,substr
    mov ebx,esi

inner_loop:
    mov al,[ebx]                
    mov dl,[edi]                
    cmp dl,0
    je found                    
    cmp al,0
    je not_found             
    cmp al,dl
    jne no_match
    inc ebx
    inc edi
    jmp inner_loop

no_match:
    inc esi
    jmp outer_loop

found:
    mov eax,4
    mov ebx,1
    mov ecx,msg3
    mov edx,msg3_len
    int 0x80
    jmp exit

not_found:
    mov eax,4
    mov ebx,1
    mov ecx,msg4
    mov edx,msg4_len
    int 0x80

exit:
    mov eax,1
    xor ebx,ebx
    int 0x80
