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
        ; 16.) (a+b)/2 + (10-a/c)+b/4
        mov ax, 0
        mov al, [a]
        add al, [b]
        mov bx, 0
        mov bl, 2
        div bl; al = 3, ah = 1
        
        mov bl, al; bl = 3
        
        mov ax, 0
        mov al, [a]
        mov dx, 0
        mov dl, [c]
        div dl; al = 0, ah = 3
        mov dl, 10
        sub dl, al ; dl = 10
        
        add bl, dl; bl = 13
        
        mov ax, 0
        mov al, [b]
        mov dx, 0
        mov dl, 4
        div dl; al = 1, ah = 0
        
        add bl, al; bl = 14
        mov ax, 0
        mov al, bl
        mov bx, [d]
        div bx
        ;rez = 14
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
