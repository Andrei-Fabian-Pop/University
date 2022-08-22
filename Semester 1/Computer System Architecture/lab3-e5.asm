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
    a db 24
    b db 4
    c db 5
    d dw 652
    e dq 4545

; our code starts here
segment code use32 class=code
    start:
        ; 2/(a+b*c-9)+e-d
        mov al, [b]
        mov bl, [c]
        mul bl
        add al, [a]
        sub al, 9 ; al = 35
        
        mov bl, al
        mov ax, 0
        mov ax, 2
        div bl ; ah = 2, al = 0
        mov ah, 0
        
        cbw
        cwde
        cdq ; eax:edx = 0
        
        mov ebx, dword [e]
        mov ecx, dword [e+4]
        
        add ebx, eax
        adc ecx, edx ; ebx:ecx = 4545
        
        mov ax, [d]
        cwde
        cdq
        
        add ebx, eax
        adc ecx, edx ; ebx:ecx = 5197
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
