bits 32

extern _printf

global _printhex

segment data public data use32:

    message db "The hex representation is %x.", 10, 13, 0
    a dd 0

segment code public code use32:
_printhex:
    push ebp
    mov ebp, esp
    sub esp, 4 * 2
    mov eax, 0
    
    mov eax, dword [ebp+8]
    mov [a], eax
        
    push dword eax
    push dword message
    call _printf
    add esp, 4*2
    
    mov eax, dword [a]
    ror eax, 4
    mov [a], eax
    
    add esp, 4 * 2
    mov esp, ebp
    pop ebp
    
    mov eax, [a]
    ret
