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
        ; 2.) (c+b)-a-(d+d)
        mov eax, [c]
        adc ax, [b] ; eax = 5
        
        mov ebx, eax
        mov eax, 0
        mov al, [a]
        cbw
        cwde
        
        sub ebx, eax ; ebx = -3
        
        mov eax, ebx 
        cdq ; edx:eax = -3
        
        mov ebx, dword [d]
        mov ecx, dword [d+4]
        
        add ebx, dword [d]
        adc ecx, dword [d+4] ; ecx:ebx = -110
        
        sub eax, ebx
        sbb edx, ecx
        ; edx:eax = 107
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
