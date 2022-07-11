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
a DB 0A2h ;se declara variabila a de tip BYTE si se initializeaza cu valoarea 0A2h
b DW 'ab' ;se declara variabila a de tip WORD si se initializeaza cu valoarea 'ab'
c DD 12345678h ;se declara variabila a de tip DOUBLE WORD si se initializeaza cu valoarea 12345678h
d DQ 1122334455667788h ;se declara variabila a de tip QUAD WORD si se initializeaza cu valoarea 1122334455667788h

a3 dw 0AA11h; -> 03h; 00 03 -> 03 00

a1 DB 600h;
b1 DB 2h;

; our code starts here
segment code use32 class=code
    start:
        ; ...
        ;mov al, 3;
        ;mov bl, 4;
        ;add al, bl;
        
        ;mov ax, 0; or mov ah, 0
        ;mov al, [a1]
        ;mov bx, [a3]
        ;add ax, bx
        
        mov ax,0;
        mov al, [a1]

        mov bl, [b1]
        div bl
        
        
            
        ;mov al, [a1];
        ;mov bx, [b1];
        ;mov edx, [a1];
        
        ;to redo
        ;sub bx, al
        
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
