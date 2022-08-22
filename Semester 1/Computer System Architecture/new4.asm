bits 32

global start
extern exit, printf
import exit msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    
    sir dq 1110111b, 100000000h, 0ABCD0002E7FCh, 5
    len equ ($-sir)/8
    rez resd len
    message db "%c"
    
segment code use32 class=code
start:
    cld 
    mov esi, sir
    mov edi, rez
    mov ecx, len
    repeta:
        push ecx
    
        lodsd
        mov ebx, eax ; copy
        mov ecx, 29 ; 32-3
        push eax
        mov eax, 0
        repeta2:
            mov edx, ebx
            and edx, 0111b
            cmp edx, 0111b
            jne after_add1
                add eax, 1
            after_add1:
            shr ebx, 1
            
            cmp ebx, 0
            je after_repeta2
        loop repeta2
        after_repeta2:
        
        cmp eax, 2
        pop eax
        jng after_store
            stosd
        after_store:
        
        lodsd ; second, unimportant half
        pop ecx
    loop repeta
    
    
    push dword 0
    call [exit]