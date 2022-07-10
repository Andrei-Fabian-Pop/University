bits 32

global start
extern exit
import exit msvcrt.dll

segment data use32 class=data
    x dw -256, 256h
    y dw 256|-256, 256h & 256
    z db $-z, y-x
      db 'y'-'x', 'y-x'
    a db 512>>2, -512<<2
    b dw z-a, !(z-a)
    ; c dd ($-b) + (d-$), $-2*y+3
    d db -128, 128^(-128)
    e times 2 resw 6
    times 2 dd 1234h, 5678h

segment code use32 class=code
start:
    ; mov bh, 7fh
    ; cmp bh, al
    ; rcr ah, 1
    ; sar ah, 7
    ; pushfd
    ; a)
    ; mov eax, 200 ; 256 - 200 = al=-56 ;; eax = 200 ok ;; ax = 200
    ; mov ebx, 254h ; 4+16*5+16*16*2 = 4 + 80 + 512 = 596 - 256 = 340 - 256 => bl=84 ok (54h = 5*16+4 = 84)
    ; idiv bl ; al = 2, ah = 200 - 168 = 32
    
    ; b)
    ; mov ax, 256h ; ax = 0256, ah = 02
    ; mov dx, -1   ; dx = FFFF, dh = FF
    ; add ah, dh   ; ah = 01 => ax = 0156
    
    ; c)
    ; mov bx, 16h
    ; mov cx, 32
    ; or bx, cx
    ; not bx
    ; mov ax, ~(16h|32) ; ~(16h|20h) ; ~(36h) ; ax = FFC9h ; al = C9h = 16*12+9 = 192+9 = 256 - 201 = -55
    ; mov bx, 2000h>>4 ; 2000 -- 1000 -- 0800 -- 0400 -- 0200 ; bx = 0200, bh = 02h = 2
    ; imul bh ; ax = -110 = FF92
    
    ; d) ; yuk
    ; mov al, 10h
    ; xor al, 3
    ; mov ax, 21 << 7 ; ax = 15h << 7 = 0000_1010_1000_0000b => al = 1000_0000b = 80h
    ; mov bh, 10h^3 ; bh = 0001_0000b xor 0000_0011b = 0001_0011b = 13h
    ; sub bh, al ; bh = 93h
    
    ; e)
    ; shl bh, 8 ; bh = 00h
    ; add bx, ax ; impossible to predict a certain result
    ; mov eax, ebx
    push dword 0
    call [exit]