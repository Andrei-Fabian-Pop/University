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
    a dw 0110110010110011b
    b dw 1110001010101100b
    c dd 0

; our code starts here
segment code use32 class=code
    start:
        ; ex 2
        mov ebx, 0 ; we store the result in bx
        
        ; the bits 0-3 of C are the same as the bits 5-8 of B
        mov ax, [b]
        and ax, 0000000111100000b
        mov cl, 5
        ror ax, cl
        cwde
        or ebx, eax ; ebx = ...0101b
        
        ; the bits 4-8 of C are the same as the bits 0-4 of A
        mov ax, [a]
        and ax, 0000000000001111b
        mov cl, 4
        rol ax, cl
        cwde
        or ebx, eax ; ebx = ...00110101b
        
        ; the bits 9-15 of C are the same as the bits 6-12 of A
        mov ax, [a]
        and ax, 0001_1111_1100_0000b
        mov cl, 3
        cwde
        rol ax, cl
        or ebx, eax
        
        ; the bits 16-31 of C are the same as the bits of B
        mov eax, [b]
        mov cl, 16
        rol eax, cl
        or ebx, eax
        ; ebx = 1110_0010_1010_1100_0110_0100_0011_0101
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
