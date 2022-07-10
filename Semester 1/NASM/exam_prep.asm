bits 32

global start        

extern exit, fopen, fclose, scanf, fprintf
import exit msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import scanf msvcrt.dll
import fprintf msvcrt.dll

segment data use32 class=data
    out_file_name db "exam_prep.txt", 0
    out_file_open_format db "a", 0
    out_file_open_descriptor db -1
    read_chr_num dd 0
    len equ 100
    num dd 1
    read_format db "%d"
	message db "The number %d has %d bits of 1 in its representation.", 0Ah, 0
    numbers resd 10

segment code use32 class=code
    start:
    ; read numbers from keyboard until the num 0 is found and print the number of 1's in the binary rep  +  read them all and store them, print later  +  do it from text file next
    
    mov ecx, 0
    mov esi, numbers
    mov edi, numbers
    cld
    
    loop1:
        ; read and store
        cmp [num], dword 0
        je before_loop11
    
        pushad
        push dword num
        push dword read_format
        call [scanf]
        add esp, 4*2
        popad
        
        mov eax, [num]
        stosd
        inc ecx
        
        jmp loop1

    before_loop11:

    dec ecx
    push ecx
    ; open file
    push dword out_file_open_format
    push dword out_file_name
    call [fopen]
    add esp, 4*2
    
    cmp eax, dword 0
    je fin
    
    mov [out_file_open_descriptor], eax
        
    pop ecx
    loop11:
        ; count bits
        push ecx
        
        mov ecx, 32
        mov ebx, 0
        lodsd
        
        mov [num], eax
        loop2:
            cmp eax, dword 0
            je after_loop2
            
            shr eax, 1
            adc ebx, 0
        loop loop2
        after_loop2:
        
        ; print
        ;pushad
        push dword ebx
        push dword [num]
        push dword message
        push dword [out_file_open_descriptor]
        call [fprintf]
        add esp, 4*4
        ;popad
        
        pop ecx
    loop loop11 
    
    cleanup:
    push dword [out_file_open_descriptor]
    call [fclose]
    
    fin:

    push    dword 0
    call    [exit]
