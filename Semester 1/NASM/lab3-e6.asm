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
    a dw 55
    b db 9
    c dw 66
    d db 15
    e dd 100
    x dq 600

; our code starts here
segment code use32 class=code
    start:
        ; 16.) x/2+100*(a+b)-3/(c+d)+e*e
        mov eax, dword [x]
        mov edx, dword [x+4]
        mov ebx, 2
        idiv ebx ; eax = 300, edx = 0
        
        mov ebx, eax ; ebx = 300
        
        mov al, [b]
        cbw
        add ax, [a] ; ax = 64
        mov cx, 100
        imul cx ; eax = 6400
        add ebx, eax ; ebx = 6700
        
        mov al, [d]
        cbw
        add ax, [c] ; ax = 81
        cwde ; eax = 81
        mov ecx, eax
        mov eax, 3
        cdq
        idiv ecx ; eax = 0, edx = 3
        
        sub ebx, eax
        mov eax, [e]
        mov ecx, [e]
        mul ecx ; edx:eax = 10000
        
        add eax, ebx ; 16700
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
