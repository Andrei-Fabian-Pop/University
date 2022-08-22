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
    sir dw 1432h, 8675h, 0ADBCh
    len_sir equ ($-sir)/2 ; length in words
    result times len_sir dd 0
    saispe db 16

; our code starts here
segment code use32 class=code
    start:
        ; 2.) An array of words is given. Write an asm program in order to obtain an array of doublewords, where each doubleword will contain each nibble unpacked on a byte (each 
        ; nibble will be preceded by a 0 digit), arranged in an ascending order within the doubleword.
        
        mov ecx, len_sir
        mov esi, sir
        mov edi, result
        cld
        jecxz fin
        
            repeta_sir:
                lodsb
                mov ah, 0
                div byte [saispe]
                mov bx, ax
                lodsb 
                mov ah, 0
                div byte [saispe]
                push ecx
                mov ecx, 16
                mov dl, 0
                
                repeta_word:
                
                    cmp al, dl
                    je unu
                    
                    cmp ah, dl
                    je doi
                    
                    cmp bl, dl
                    je trei
                    
                    cmp bh, dl
                    je patru
                    
                    jmp after
                    
                        unu:
                            stosb
                            jmp after
                        
                        doi:
                            mov dh, al
                            mov al, ah
                            stosb
                            mov al, dh
                            jmp after
                        
                        trei:
                            push ax
                            mov al, bl
                            stosb
                            pop ax
                            jmp after
                        
                        patru:
                            push ax
                            mov al, bh
                            stosb
                            pop ax
                            jmp after
                    
                    after:
                    inc dl
                loop repeta_word
                
                pop ecx
            
            loop repeta_sir
        
        fin:
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
