%ifndef _TRANSFORM_ASM_
%define _TRANSFORM_ASM_

transform:
    jmp transform_start
    
    transform_start:
    
    mov dl, [esp + 4]
    inc ebx
    
    cmp dl, 'b'
    je t_en
        
        sub dl, '0'
        mul byte [two]
        add ax, dx
    
    jmp t_last
    t_en:
        stosd
        mov eax, 0
    
    t_last:
    
    ret

%endif