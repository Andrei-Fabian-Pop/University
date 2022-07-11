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
    a dw 1011_0011_1001_0101b
    b dd 0

; our code starts here
segment code use32 class=code
    start:
        ; ex 30
        mov ebx, 0 ; the result will be in ebx
        
        ; the bits 0-3 of B are the same as the bits 1-4 of the result A XOR 0Ah
        mov ax, [a]
        xor ax, 0Ah
        and ax, 1_1110b
        mov cl, 1
        ror ax, cl
        cwde
        or ebx, eax
        
        ; the bits 4-11 of B are the same as the bits 7-14 of A
        mov eax, [a]
        and eax, 0111_1111_1000_0000b
        mov cl, 3
        ror eax, cl
        or ebx, eax
        
        ; the bits 12-19 of B have the value 0
        and ebx, 1111_1111_1111_0000_0000_1111_1111_1111b
        
        ; the bits 20-25 of B have the value 1
        or ebx, 0000_0011_1111_0000_0000_0000_0000_0000b
        
        ; the bits 26-31 of C are the same as the bits 3-8 of A complemented
        mov eax, [a]
        not eax
        add eax, 1 ; we calculate the complement of A
        and eax, 0000_0001_1111_1000b ; we separated the 3-8 bits of A
        mov cl, 23
        rol eax, cl
        or ebx, eax
        
        ; ebx = 0011_0111_1111_0000_0000_0110_0111_1111b
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
