; The code below will print the message „Ana has 17 apples”
bits 32
global start        

; declare extern functions used by the program
extern exit, printf, scanf         ; add printf as extern function            
import exit msvcrt.dll    
import printf msvcrt.dll    ; tell the assembler that function printf can be found in library msvcrt.dll
import scanf msvcrt.dll
                          
segment data use32 class=data
; char arrays are of type byte
format db "%d", 0
result db "Ana has %d apples", 0  ; %d will be replaced with a number
				; char strings for C functions must terminate with 0
a dw 0
segment  code use32 class=code
    start:
        push dword a
        push dword format
        call [scanf]
        add esp, 4*2
        
        mov eax, [a]
        push dword eax
        push dword result
        call [printf]
        add esp, 4*2
        

        ; exit(0)
        push dword 0      ; push on stack the parameter for exit
        call [exit]       ; call exit to terminate the programme
