%ifndef _PRINTHEX_ASM_
%define _PRINTHEX_ASM_

print_hex:
    jmp after
        message db "The hex representation is %x \n", 0
    after:

    mov eax, dword [esp+4]
        
    push dword eax
    push dword message
    call [printf]
    add esp, 4*2
        
    ret
    
%endif