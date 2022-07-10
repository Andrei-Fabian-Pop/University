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
    s1 db 'a', 'b', 'c', 'b', 'e', 'f'
    l_s1 equ $-s1
    s2 db '1', '2', '3', '4', '5'
    l_s2 equ $-s2
    d times l_s1/2+l_s2/2+(l_s2-l_s2/2*2) db 0

; our code starts here
segment code use32 class=code
    start:
        ; 16. Two character strings S1 and S2 are given. 
        ; Obtain the string D by concatenating the elements found on odd positions in S2 and the elements found on even positions in S1.
        ; ex 
        ; S1: 'a', 'b', 'c', 'b', 'e', 'f'
        ; S2: '1', '2', '3', '4', '5'
        ; D:  '1', '3', '5', 'b', 'b', 'f'
        
        mov ecx, l_s1/2
        mov esi, 0
        jecxz fin
        
            repeta_s2:
                mov al, [s2+esi*2]
                mov [d+esi], al
                inc esi
            loop repeta_s2
            
            mov ecx, l_s2/2+(l_s2-l_s2/2*2)
            
            repeta_s1:
                mov al, [s1+1+(esi-(l_s2/2+(l_s2-l_s2/2*2)))*2]
                mov [d+esi], al
                inc esi
            loop repeta_s1
        
        fin:
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
