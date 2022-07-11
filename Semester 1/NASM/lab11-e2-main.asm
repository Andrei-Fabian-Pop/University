bits 32

global start        

extern exit
import exit msvcrt.dll

%include "transform.asm"

segment data use32 class=data
    given_str db '10100111b', '01100011b', '110b', '101011b'
    l_given_str equ $-given_str
    obtain_str times l_given_str db 0
    two db 2
	

segment code use32 class=code
    start:
        ; A string containing n binary representations on 8 bits is given as a character string.
        ; Obtain the string containing the numbers corresponding to the given binary representations.
        ; Example:
        ; Given: '10100111b', '01100011b', '110b', '101011b'
        ; Obtain: 10100111b, 01100011b, 110b, 101011b
        ;         A7h        63h        6     2B
        mov edi, obtain_str
        mov eax, 0
        mov edx, 0
        mov ebx, 0
        mov ecx, l_given_str
        cld
        jecxz fin
        
            for_loop:
                push dword [given_str + ebx]
                
                mov dl, [given_str + ebx]
                inc ebx
                
                cmp dl, 'b'
                je en
                    
                    sub dl, '0'
                    mul byte [two]
                    add ax, dx
                
                jmp last
                en:
                    stosb
                    mov eax, 0
                
                last:
            loop for_loop
        
        fin:

        push    dword 0
        call    [exit]
