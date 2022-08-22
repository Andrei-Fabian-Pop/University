bits 32

global start        

extern exit, fopen, fclose, fread, fprintf
import exit msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fread msvcrt.dll
import fprintf msvcrt.dll

segment data use32 class=data
	in_file db "input.txt", 0
    out_file db "output.txt", 0
    chr db 0
    empty db 0
    read_format db "r", 0
    output_format db "a", 0
    input_file_descriptor dd -1
    output_file_descriptor dd -1
    message db "%c", 0
    
    len equ 100
    buffer resb len
    one equ 1

segment code use32 class=code
    start:
        ; open in file
        push dword read_format
        push dword in_file
        call [fopen]
        add esp, 4*2
        
        cmp eax, dword 0
        je fin
        
        mov [input_file_descriptor], eax
        
        ; open out file
        
        push dword output_format
        push dword out_file
        call [fopen]
        add esp, 4*2
        
        cmp eax, dword 0
        je fin
        
        mov [output_file_descriptor], eax
        
        ; read first chr
        push dword [input_file_descriptor]
        push dword one
        push dword 1
        push dword chr
        call [fread]
        add esp, 4*4
        
        ; read new line
        push dword [input_file_descriptor]
        push dword one
        push dword 1
        push dword empty
        call [fread]
        add esp, 4*4
        
        read_loop:
            push dword [input_file_descriptor]
            push dword len
            push dword 1
            push dword buffer
            call [fread]
            add esp, 4*4
            
            cmp eax, dword 0
            je after_read_loop
            
            ; check the 100 bytes read
            mov ecx, eax
            mov edx, 0
            for_100:
                push ecx
                cmp edx, dword 0
                je new_word
            
                cmp byte[buffer+edx], ' '
                je new_word
                
                jmp end_for_100
                new_word:
                    mov cl, byte[buffer + edx + 1]
                    cmp [chr], cl
                    je print_word
                    jmp end_for_100
                    
                    print_word:
                        mov eax, 0
                        mov al, byte[buffer + edx]
                        
                        pushad
                        push dword eax
                        push dword message
                        push dword [output_file_descriptor]
                        call [fprintf]
                        add esp, 4*3
                        popad
                        
                        inc edx
                        
                        cmp byte[buffer+edx], ' '
                        je end_for_100
                        jmp print_word
                
                end_for_100:
                pop ecx
            loop for_100
        
            jmp read_loop
        after_read_loop:
        
        push dword [input_file_descriptor]
        call [fclose]
        add esp, 4
        
        push dword [output_file_descriptor]
        call [fclose]
        add esp, 4
        
        fin:
        push    dword 0
        call    [exit]
