section .data
    msg1 db "String:",0xa
    msg1l equ $-msg1
    msg2 db "Substring:",0xa
    msg2l equ $-msg2
    msg3 db "Found",0xa
    msg3l equ $-msg3
    msg4 db "Not Found",0xa
    msg4l equ $-msg4

section .bss
    str: resb 100
    substr resb 50
    len resd 1
    sublen resd 1

section .text
    global _start

_start:
    mov eax,4
    mov ebx,1
    mov ecx,msg1
    mov edx,msg1l
    int 0x80

    mov eax,3
    mov ebx,0
    mov ecx,str
    mov edx,200
    int 0x80

    mov [len],eax
    dec eax
    mov byte[str + eax],0

    mov eax,4
    mov ebx,1
    mov ecx,msg2
    mov edx,msg2l
    int 0x80

    mov eax,3
    mov ebx,0
    mov ecx,substr
    mov edx,200
    int 0x80

    mov [sublen],eax
    dec eax
    mov byte[substr + eax],0
    mov esi,str

outer_loop:
    mov al,[esi]
    cmp al,0
    je not_found
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
    mov edx,msg3l
    int 0x80
    jmp exit

not_found:
    mov eax,4
    mov ebx,1
    mov ecx,msg4
    mov edx,msg4l
    int 0x80

exit:
    mov eax,1
    mov ebx,0
    int 0x80
    