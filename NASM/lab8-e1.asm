bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf, scanf               
import exit msvcrt.dll    
import printf msvcrt.dll
import scanf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    a dw 0
    b dw 0
    result dd 0
    format db "%d", 0
    message db "The division is %d", 0

; our code starts here
segment code use32 class=code
    start:
        ; 2. Read two numbers a and b (in base 10) from the keyboard and calculate a/b. This value will be stored in a variable called "result" (defined in the data segment). The values are considered in signed representation.
        
        push dword a
        push dword format
        call [scanf]
        add esp, 4 * 2
        
        push dword b
        push dword format
        call [scanf]
        add esp, 4 * 2
        
        mov ax, [a]
        mov bl, [b]
        idiv bl
        mov ah, 0
        mov [result], ax
        
        mov eax, 0
        mov eax, [result]
        push dword eax
        push dword message
        call [printf]
        add esp, 4 * 2
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
