bits 32

global start        

extern exit
import exit msvcrt.dll

segment data use32 class=data

        a dw 0

segment code use32 class=code
    start:
        ; mov ax, 0FAFAh
        ; mov [a], ax
        stc
        clc
        stc
        clc
        cmc
        

        push    dword 0
        call    [exit]
