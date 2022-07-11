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
    s db 'a', '!', '$', 'e'
    l_s equ $-s
    spec_chr db '!', '@', '#', '$', '%', '^', '&', '*'
    l_spec_chr equ $-spec_chr
    d times l_s db 0
    l_d db 0

; our code starts here
segment code use32 class=code
    start:
        ; 2. Given a character string S, obtain the string D containing all special characters (!@#$%^&*) of the string S.
        mov ecx, l_s
        mov esi, 0
        jecxz fin ; in cazul in care avem lungimea de la sting 0, sari la fin
        
        outerLoop:
            push ecx
            mov ecx, l_spec_chr
            mov al, [s+esi]
            push esi
            mov esi, 0
            
            innerLoop:
                mov bl, [spec_chr+esi]
                cmp al, bl
                jne inner_fin
                    push esi
                    mov esi, [l_d]
                    mov [d+esi], al
                    inc esi
                    mov [l_d], esi
                    pop esi
                inner_fin:
                inc esi
            loop innerLoop
            
            pop esi
            inc esi
            pop ecx
        loop outerLoop
        
        fin:
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
