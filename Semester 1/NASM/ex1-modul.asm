bits 32

extern _printf

global _asmStore

segment data public data use32
    
    mem_sir times 101 db 0
    message db "printed from asm: %c"

segment code public code use32
_asmStore:
    push ebp
    mov ebp, esp
    sub esp, 4 * 3
    
    ; first parameter
    mov eax, [ebp + 8]
    
    push dword eax
    push dword message
    call _printf
    
    ret
    
