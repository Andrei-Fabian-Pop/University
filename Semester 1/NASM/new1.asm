bits 32

global start

extern exit

import exit msvcrt.dll

segment data use32 class=data
    
    cc dd 0AAh
    sir db 'a', 'b', 'c', 'd', 'e', 0
    len equ ($-sir)
    sir2 times len db 0
    a dd 32
    b dd 68
    ten equ 10
    v db 0ABh

segment code use32 class=code
start:
    ; mov ecx, 0 
    ; mov ecx, len
    ; mov esi, sir
    ; mov edi, sir2
    
    ; rep movsb
    
    ; mov al, 83 ; 83 // 83
    ; mov cl, 115 ; 115 // 115
    ; add al, cl ; + add + = -   -> OF=1
    
    ; mov eax, 0
    ; mov al, 0fah
    ; mov cl, 0dah
    ; mul cl
    
    ; mov al, 0000_1000b
    ; mov cl, 0000_0100b
    ; add al, cl  ;  AF -> 1

    ; mov ax, 1002
    ; mov bl, 3
    ; div bl ; integer overflow --> program terminated
    
    ; mov ebx, cc
    ; lea eax, [ebx] ; not cool :((
    
    ; mov eax, 81
    ; mov eax, -81 ; 2's complement
    ; mov ebx, 81
    ; mov ebx, ~81 ; logical neg, 1's complement
    
    ; mov ecx, 198<<1
    ; mov eax, 198
    ; shl eax, 1 ; same result
    
    ; push word [v]
    ; mov al, 27
    ; cmp eax, 0
    
    ; mov eax, 0
    ; mov ax, -5
    ; mov bx, 10
    ; imul bx ; ax = -50, rez nu va fi pus in eax, ci in ax
    ; mul bx ; eax = FFFB * 000A = 65531 * 10 = 655310
    ; mov eax, [ebx + esp]
    
    push dword 0
    call [exit]