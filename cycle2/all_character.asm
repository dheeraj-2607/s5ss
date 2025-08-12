section .data
	msg1 db "String1: ", 0xa        ; Prompt for string
	msg2 db "Character frequencies:", 0xa
	msg3 db 0xa
	colon db ": "
	
section .bss
	str1 resb 100                  ; Input string
	freq resb 256                  ; Frequency table
	outchar resb 1                ; For outputting a character
	count resb 1                  ; For outputting single-digit count
	
section .text
	global _start
_start:
	; Print "String1: "
	mov eax, 4
	mov ebx, 1
	mov ecx, msg1
	mov edx, 9
	int 0x80

	; Read String
	mov eax, 3
	mov ebx, 0
	mov ecx, str1
	mov edx, 100
	int 0x80
	mov byte[str1 + eax - 1], 0    ; Null-terminate string

	; Print "Character frequencies:"
	mov eax, 4
	mov ebx, 1
	mov ecx, msg2
	mov edx, 24
	int 0x80

	; Zero out freq array (initialize all frequencies to 0)
	mov edi, freq
	mov ecx, 256
	xor eax, eax
	rep stosb

	; Initialize pointer to string
	mov esi, str1

.count_loop:
	mov al, [esi]
	cmp al, 0
	je .print_loop                 ; End of string
	movzx ebx, al                 ; Zero-extend character to use as index
	inc byte [freq + ebx]         ; Increment frequency
	inc esi
	jmp .count_loop

.print_loop:
	mov ecx, 0                    ; Character index (0 to 255)

.next_char:
	cmp ecx, 256
	je .exit

	mov al, [freq + ecx]
	cmp al, 0
	je .skip_print

	; Print character
	mov bl, cl
	mov [outchar], bl
	mov eax, 4
	mov ebx, 1
	mov ecx, outchar
	mov edx, 1
	int 0x80

	; Print ": "
	mov eax, 4
	mov ebx, 1
	mov ecx, colon
	mov edx, 2
	int 0x80

	; Convert count to ASCII (supports 0–9 only for simplicity)
	mov al, [freq + ecx]
	add al, '0'
	mov [count], al

	; Print count
	mov eax, 4
	mov ebx, 1
	mov ecx, count
	mov edx, 1
	int 0x80

	; Print newline
	mov eax, 4
	mov ebx, 1
	mov ecx, msg3
	mov edx, 1
	int 0x80

.skip_print:
	inc ecx
	jmp .next_char

.exit:
	; Exit
	mov eax, 1
	mov ebx, 0
	int 0x80