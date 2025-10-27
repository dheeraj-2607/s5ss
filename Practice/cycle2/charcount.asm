section .data
    msg1 db "String",0xa
    msg2 db "Character",0xa
    msg3 db 0xa
section .bss
    str1 resb 100
    chr resb 1
    count resb 1
section .text
    global _start

_start:
    mov eax,4
    mov ebx,1
    mov ecx,msg1
    mov edx,9
    int 0x80

    mov eax,3
    mov ebx,0
    mov ecx,str1
    mov edx,100
    int 0x80

    mov byte[str1 + eax - 1],0

    mov eax,4
    mov ebx,1
    mov ecx,msg2
    mov edx,12
    int 0x80

    mov eax,3
    mov ebx,0
    mov ecx,chr
    mov edx,1
    int 0x80

    mov esi,str1
    mov dl,[chr]
    mov ecx,0

.loop:
    mov al,[esi]
    cmp al,0
    je .done
    cmp al,dl
    jne .skip
    inc ecx

.skip:
    inc esi
    jmp .loop

.done:
    mov eax,ecx
    add eax,'0'
    mov [count],al

    mov eax,4
    mov ebx,1
    mov ecx,count
    mov edx,1
    int 0x80

    mov eax,4
    mov ebx,1
    mov ecx,msg3
    mov edx,1
    int 0x80

    mov eax,1
    mov ebx,0
    int 0x80