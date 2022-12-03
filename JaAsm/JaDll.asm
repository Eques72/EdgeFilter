;NOTATKI
;[+4] przesuwa o 1 index (32bity);
;r9d - 32 bit
;r9b - 8 bit
;r9w - 16 bit
;r9 - 64 bit

.data
center WORD -4
borders WORD 1
zero WORD 0
channels Qword 1
maxrgbvalue WORD 255
;center real4 -4.0
;borders real4 1.0
;zero real4 0.0

.code
MyProc proc ;width=RCX, height-RDX, src-R8, sec_src=R9
;RDX - height
;RCX - width
;R8 -src image
;R9 - output image
;Free TO USE - rax - y, rbx - x, rdi - pos, rsi, r10-15

; PARAMS REGISTERS = RCX, RDX, R8, R9
; USED REGISTERS = RAX, RBX, RDI, R10, R11, R12, R13

PUSH RAX
PUSH RBX
PUSH RDI
PUSH R10
PUSH R11
PUSH R12
PUSH R13


mov rax, 0 ;Y - counter for outer loop
mov rbx, 0 ;X - counter for inner loop

ROWS:		;outer loop, height,Y
COLLUMNS:	;inner loop, width, X
;------------
MOV rdi, rax  ;POS
imul rdi, rcx ;>
add rdi, rbx  ;>this gives pos
;++++++

MOV R10, 0
MOV R10B, BYTE ptr[r8+rdi]	;Read value from tab (from specific adress)  
IMUL R10W, center	

;PREVIOUS (LEFT) PIXEL
MOV R11, 0
MOV R11B, BYTE ptr[R8+RDI-1]
ADD R10W, R11W

;NEXT (RIGHT) PIXEL
MOV R11, 0
MOV R11B, BYTE ptr[R8+RDI+1]
ADD R10W, R11W
;+++++++++++

;BELOW PIXEL
mov r12, rcx
add r12, rdi
MOV R11, 0
MOV R11B, BYTE ptr[r8+r12]
ADD R10W, R11W

;TOP PIXEL
mov r13, rcx 
mov r12, rdi
sub r12, r13
MOV R11B, BYTE ptr[r8+r12]
ADD R10W, R11W

CMP R10W, zero
JL REDUCE_NEG

CMP R10W, 200
JG REDUCE_BIG
END_OF_RED:

MOV BYTE ptr[r9+rdi], R10B	;Insert value to tab (to specific adress)
;mov dword ptr[r8+rdi], r10d	;Insert value to tab (to specific adress)

INC	rbx			;inner loop
CMP	rbx, rcx	;inner loop
JL	COLLUMNS	;inner loop

mov rbx, 0		;reset inner loop
;------------
INC rax			;outer loop
cmp rax, rdx	;outer loop
JL	ROWS  		;outer loop
;------------


POP R13
POP R12
POP R11
POP R10
POP RDI
POP RBX
POP RAX


ret

REDUCE_NEG:		;Accesible only by jump
MOV R10W, zero		;Make color value fit its lower boundary
JMP END_OF_RED	;Jump back to the loop
REDUCE_BIG:		;Accesible only by jump
MOV R10W, maxrgbvalue	;Make color value fit its upper boundary
JMP END_OF_RED	;Jump back to the loop


MyProc endp
end