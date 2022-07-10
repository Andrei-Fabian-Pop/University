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
    a db 3
    b db 4
    c db 5
    d db 7
    e dw 9
    f dw 1
    g dw 5
    h dw 2

; our code starts here
segment code use32 class=code
    start:
        ; 16.) a*a-(e+f)
        mov al, [a]
        mov bl, [a]
        mul bl; ax = 9
        
        mov bx, [e]
        add bx, [f]; bx = 10
        
        sub ax, bx; ax = -1
        ; rez = -1
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
