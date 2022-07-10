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
    a db 0110_1001b
    b dw 0101_1010_1111_0000b
    c dd 0

; our code starts here
segment code use32 class=code
    start:
        ; ex 16
        mov ebx, 0 ; the result will be in ebx
        
        ; the bits 0-7 of C have the value 1
        or ebx, 0000_0000_1111_1111b
        
        ; the bits 8-11 of C are the same as the bits 4-7 of A
        mov ax, [a]
        and ax, 1111_0000b
        mov cl, 4
        rol ax, cl
        cwde
        or ebx, eax
        
        ; the bits 12-19 are the same as the bits 2-9 of B
        mov eax, [b]
        and eax, 0000_0011_1111_1100b
        mov cl, 10
        rol eax, cl
        or ebx, eax
        
        ; the bits 20-23 are the same as the bits 0-3 of A
        mov eax, [a]
        and eax, 1111b
        mov cl, 20
        rol eax, cl
        or ebx, eax
        
        ; the bits 24-31 are the same as the high byte of B
        mov eax, [b]
        and eax, 1111_1111_0000_0000b
        mov cl, 16
        rol eax, cl
        or ebx, eax
        
        ; ebx = 0101_1010_1001_1011_1100_0110_1111_1111b
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
