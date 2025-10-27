section .data
    msg1 db "String1:",0xa
    msg1l equ $-msg1
    msg2 db "String2:",0xa
    msg2l equ $-msg2
    msg3 db "Concatenated: ",0xa
    msg3l equ $-msg3
    int 0x80

section .bss
    str1 resb 100
    str2 resb 100
    result resb 200

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
    mov ecx,str1
    mov edx,100
    int 0x80
    mov esi,eax
    dec esi
    mov byte[str1 + esi],0

    mov eax,4
    mov ebx,1
    mov ecx,msg2
    mov edx,msg2l
    int 0x80

    mov eax,3
    mov ebx,0
    mov ecx,str2
    mov edx,100
    int 0x80
    mov edi,eax
    dec edi
    mov byte[str2 + edi],0

    mov esi,str1
    mov edi,result

._str1:
    mov al,[esi]
    cmp al,0
    je ._str2
    mov [edi],al
    inc esi
    inc edi
    jmp ._str1

._str2:
    mov esi,str2

._loop:
    mov al,[esi]
    cmp al,0
    je .print
    mov [edi],al
    inc esi
    inc edi
    jmp ._loop

.print:
    mov byte[edi],0
    mov eax,4
    mov ebx,1
    mov ecx,msg3
    mov edx,msg3l
    int 0x80

    mov eax,4
    mov ebx,1
    mov ecx,result
    mov edx,edi
    sub edx,result
    int 0x80
    int 0x80


    mov eax,1
    xor ebx,ebx
    int 0x80