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
    d dw 7

; our code starts here
segment code use32 class=code
    start:
        ; 2.) d*(d+2*a)/(b*c)
        mov al, [a]
        mov bl, 2
        mul bl
        add al, [d]; al = 13
        
        mov bl, [d]
        mul bl; ax = 91
        
        mov dx, ax; dx = 91
        mov ax, [b]
        mov bl, [c]
        mul bl; ax = 20
        
        ; punem deimpartitul inapoi in ax
        mov bx, dx
        mov dx, ax
        mov ax, bx
        
        div dl; 91/20: ah = 11 si al = 4
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
