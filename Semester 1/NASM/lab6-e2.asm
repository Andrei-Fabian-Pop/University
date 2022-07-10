bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    s1 db 'a', 'b', 'e', 'g', 'x', 'y'
    l_s1 equ $-s1
    s2 db 'c', 'd', 'f', 'k'
    l_s2 equ $-s2
    res times l_s1+l_s1 db 0 ; abcdefgkxy

; our code starts here
segment code use32 class=code
    start:
        ; 16.) Being given two alphabetical ordered strings of characters, s1 and s2, build using merge sort the ordered string of bytes that contain all characters from s1 and s2.
        
        cld
        mov edi, res
        mov ecx, l_s1+l_s1
        mov ebx, 0 ; s1
        mov edx, 0 ; s2
        repeta:
            cmp ebx, l_s1
            je rest_s2
            
            cmp edx, l_s2
            je rest_s1
        
            mov al, [s1+ebx]
            mov ah, [s2+edx]
            cmp al, ah
            
            jb introdu_s1
            jae introdu_s2
            
            introdu_s1:
                stosb
                inc ebx
                jmp after
            introdu_s2:
                mov al, ah
                stosb
                inc edx
            after:
        loop repeta
        jmp fin
        
        rest_s2:
            mov al, [s2+edx]
            stosb
            inc edx
            cmp edx, l_s2
            je fin
            jmp rest_s2
        
        rest_s1:
            mov al, [s1+ebx]
            stosb
            inc ebx
            cmp ebx, l_s1
            je fin
            jmp rest_s1
        
        fin:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
