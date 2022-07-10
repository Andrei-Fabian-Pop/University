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
    a db 5
    b dd 15
    c dq 70
; our code starts here
segment code use32 class=code
    start:
        ; ...;c+(a*a-b+7)/(2+a)
        mov al, [a]
        mov cl, [a]
        imul cl
        add ax, 7
        cwde; eax = a*a+7
        mov ebx, dword [b]
        sub eax, ebx; eax = a*a-b+7
        cdq; eax:edx = a*a-b+7
        mov ecx, edx
        mov ebx, eax; ecx:ebx = a*a-b+7
        mov al, [a]
        add al, 2
        cbw
        cwde; eax = 2+a
        mov edx, ebx
        mov ebx, eax; ebx = 2+a 
        mov eax, edx
        mov edx, ecx; edx:eax = a*a-b+7
        idiv ebx; eax = (a*a-b+7)/(2+a)
        cdq
        mov ebx, dword [c]
        mov ecx, dword [c+4]
        add eax, ebx
        adc edx, ecx
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program