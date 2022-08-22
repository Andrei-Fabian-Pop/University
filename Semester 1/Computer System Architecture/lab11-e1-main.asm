bits 32
global start        

extern exit, printf, scanf
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll

%include "printhex.asm"

;extern print_hex

segment data use32 class=data
    a dd 0
    format db "%d", 0

segment code use32 class=code

    start:
        ; An unsigned number a on 32 bits is given. Print the hexadecimal representation of a, but also the results of the circular permutations of its hex digits.
        push dword a
        push dword format
        call [scanf]
        add esp, 4*2
        
        mov ecx, 8
        for_loop:
            push ecx
            push dword [a]
            
            call print_hex
            add esp, 4*2
            
            mov eax, dword [a]
            ror eax, 4
            mov [a], eax
            pop ecx
        loop for_loop
        
        
        push    dword 0
        call    [exit]
