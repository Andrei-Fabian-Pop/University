bits 32

global start 
extern exit
import exit msvcrt.dll

segment data use32 class=data
    
segment code use32 class=code
start:

    cld
    push ax
    mov ax, [esp+2]
    stosw
    lea edi, [edi-2]
    add esp, 4

    ; mov ebx, 0
    ; xchg ebx, [ebx+6] ; MEMORY VIOLATION ERROR, most probably
    ; push [ebx+6] ; pop ebx ; OP SIZE NOT SPECIFIED
    ; add ebx, 6 ; 0001_0005h
    ; mov [ebx], dword [bx+6] ; SYNTAX ERROR
    ; add bx, 6 ; 0000_0005h
    ; movzx ebx, [bx+6] ; OP SIZE NOT SPECIFIED
    ; movzx ebx, [ebx+6] ; OP SIZE NOT SPECIFIED
    ; mov ebx, [ebx+6] ; MEMORY VIOLATION ERROR, most probably
    ; mov ebx, ebx+6 ; SYNTAX ERROR
    ; lea bx, [ebx+6] ; 0000_0005h
    ; lea bx, [bx+6] ; 0000_0005h
    ; lea ebx, [bx+6]  ; 0000_0005h
    ; lea ebx, [ebx+6] ; 0001_0005h 
    
    push dword 0
    call [exit]