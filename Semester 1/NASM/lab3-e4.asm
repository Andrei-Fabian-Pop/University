bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    a db 8
    b dw -9
    c dd 14
    d dq -55

; our code starts here
segment code use32 class=code
    start:
        ; 16.) (d-a)-(a-c)-d
        mov ebx, dword [d]
        mov ecx, dword [d+4]
        
        mov al, [a]
        cbw
        cwde
        cdq
        
        sub ebx, eax
        sbb ecx, edx ; ebx:ecx = -63
        
        mov al, [a]
        cbw
        cwde
        sub eax, [c] ; eax = -6
        cdq
        
        sub ebx, eax
        sbb ecx, edx ; ebx:ecx = -57
        
        mov eax, dword [d]
        mov edx, dword [d+4]
        
        sub ebx, eax
        sbb ecx, edx ; ebx:ecx = -2
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
