bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf, fopen, fclose, fread
import exit msvcrt.dll    
import printf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fread msvcrt.dll


; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fisier db "input.txt", 0
    mod_acces db "r", 0
    descriptor_fisier dd -1
    nr_car_citite dd 0
    len equ 100
    buffer resb len
    consoane_mici db "qwrtypsdfghjklzxcvbnm"
    l_consoane_mici db 21
    result dd 0
    print_rez db "Rezultatul este %d", 0
    ; a-A

; our code starts here
segment code use32 class=code
    start:
        ; 2. A text file is given. Read the content of the file, count the number of consonants and display the result on the screen. The name of text file is defined in the data segment.
        ; raspuns: edx = 5
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp, 4*2
        
        cmp eax, 0
        je final
        
        mov [descriptor_fisier], eax
        
        mov edx, 0
        
        bucla_citire:
            push dword [descriptor_fisier]
            push dword len
            push dword 1
            push dword buffer
            call [fread]
            add esp, 4*4
            
            cmp eax, 0
            je cleanup
            
            mov [nr_car_citite], eax
            
            mov ecx, [nr_car_citite]
            mov esi, 0
            bucla_litera_citita:
                mov bl, [buffer+esi]
                push esi
                push ecx
                mov ecx, 0
                mov ecx, dword [l_consoane_mici]
                mov esi, 0
                ver_daca_e_consoana:
                    mov bh, [consoane_mici+esi]
                    inc esi
                    
                    cmp bl, bh
                    je este_consoana
                    
                    add bh, 'a'-'A'
                    
                    cmp bl, bh
                    je este_consoana
                loop ver_daca_e_consoana
                jmp continua
                
                este_consoana:
                    inc edx
                
                continua:
                
                pop ecx
                pop esi
                inc esi
            loop bucla_litera_citita
            
            add [result], edx
            jmp bucla_citire
        
        
        cleanup:
            push dword [descriptor_fisier]
            call [fclose]
            add esp, 4
        
        mov eax, 0
        mov eax, [result]
        push dword eax
        push dword print_rez
        call [printf]
        add esp, 4 * 2
        
        final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
